#version 330 core

in vec3 v_FragPos;               // world-space fragment position
in vec3 v_Normal;                // world-space interpolated normal (VS: model-only normal matrix)
in vec4 v_FragPosLightSpace;     // lightVP * worldPos

out vec4 outColor;

// ===== material =====
uniform vec3  u_material_ambient;
uniform vec3  u_material_diffuse;
uniform vec3  u_material_specular;
uniform float u_material_shininess;

// ===== camera =====
uniform vec3 u_cameraPosWS;

// ===== shadow samplers =====
uniform sampler2D         u_dir_shadow_map;     // manual compare (no compare mode)
uniform samplerCube       u_point_shadow_cube;  // manual compare (COMPARE_MODE = GL_NONE)

// ===== directional lights =====
uniform int      u_num_dir_lights;
uniform vec3     u_dir_light_directions[8];     // EXPECTED: light -> scene (ray dir)
uniform vec3     u_dir_light_ambient[8];
uniform vec3     u_dir_light_diffuse[8];
uniform vec3     u_dir_light_specular[8];

// ===== point lights =====
uniform int   u_num_point_lights;
uniform vec3  u_point_light_positions[16];
uniform vec3  u_point_light_ambient[16];
uniform vec3  u_point_light_diffuse[16];
uniform vec3  u_point_light_specular[16];
uniform float u_point_light_constant[16];
uniform float u_point_light_linear[16];
uniform float u_point_light_quadratic[16];
uniform float u_point_light_far_planes[16];
uniform float u_point_light_intensity[16];


const vec3 kSampleDirs[20] = vec3[](
  vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1),
  vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
  vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
  vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
  vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);

// ----------------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------------
float DirShadowVisibility(vec4 fragPosLightSpace, vec3 normalWS, vec3 lightDirWS)
{
    // Project to [0,1] texture space
    vec3 projCoords = fragPosLightSpace.xyz / max(fragPosLightSpace.w, 1e-6);
    projCoords = projCoords * 0.5 + 0.5;

    // Outside the map => lit (prevents edge PCF poisoning)
    if (projCoords.z > 1.0 ||
        projCoords.x < 0.0 || projCoords.x > 1.0 ||
        projCoords.y < 0.0 || projCoords.y > 1.0)
    {
        return 1.0;
    }

    // Bias from same N·L used for shading
    vec3 n = normalize(normalWS);
    vec3 l = normalize(lightDirWS);          // light -> scene
    float NdotL = max(dot(n, l), 0.0);

    const float constBias   = 0.0005;
    const float slopeFactor = 0.001;
    float bias = max(constBias, slopeFactor * (1.0 - NdotL));

    // 3x3 PCF
    vec2 texelSize = 1.0 / vec2(textureSize(u_dir_shadow_map, 0));
    float vis = 0.0;
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            vec2 o = vec2(dx, dy) * texelSize;
            float mapDepth = texture(u_dir_shadow_map, projCoords.xy + o).r;
            float current  = projCoords.z - bias;
            vis += (current <= mapDepth) ? 1.0 : 0.0;
        }
    }
    return vis / 9.0;
}

float PointShadowVisibilitySingle(vec3 fragPosWS, vec3 normalWS, vec3 lightPosWS, float farPlane)
{
    vec3  toFrag      = fragPosWS - lightPosWS;           // light -> frag
    float currentDist = length(toFrag);

    // Normal-dependent bias (tune numbers as needed)
    vec3  L    = normalize(-toFrag);
    float ndl  = max(dot(normalize(normalWS), L), 0.0);
    float bias = max(0.002, 0.02 * (1.0 - ndl));

    // Simple PCF over a small “disk” in direction space
    float shadow  = 0.0;
    int   samples = 20;
    float radius  = (1.0 + currentDist / farPlane) * 0.05;  // distance-based radius

    for (int i = 0; i < samples; ++i)
    {
        // Sample stored normalized depth from the cubemap
        float stored = texture(u_point_shadow_cube, toFrag + kSampleDirs[i] * radius).r;
        float closestDepth = stored * farPlane; // de-normalize

        if (currentDist - bias > closestDepth)
            shadow += 1.0;
    }

    // Return visibility in [0,1]
    return 1.0 - (shadow / float(samples));
}

// ----------------------------------------------------------------------------
// Blinn–Phong with seam-free specular:
//  - Diffuse uses interpolated normal (smooth if your vertices are smooth).
//  - Specular uses a flat normal computed from derivatives -> no triangle seam.
// ----------------------------------------------------------------------------
vec3 ShadeBlinnPhong(
    vec3 normalSmoothWS,     // interpolated normal
    vec3 viewDirWS,          // camera - frag
    vec3 lightDirWS,         // light -> scene (or light->frag for point)
    float intensity,
    vec3 ambientColor,
    vec3 diffuseColor,
    vec3 specularColor,
    float attenuation, 
    float shadowVisibility
)
{
    // Diffuse normal (keeps smoothing if your mesh wants it)
    vec3 n_diffuse = normalize(normalSmoothWS);

    // Flat per-face normal for specular to avoid diagonal seams
    vec3 n_flat = normalize(cross(dFdx(v_FragPos), dFdy(v_FragPos)));
    // Make sure it faces the same hemi-sphere as the interpolated normal
    if (dot(n_flat, n_diffuse) < 0.0) n_flat = -n_flat;

    vec3 v = normalize(viewDirWS);
    vec3 l = normalize(lightDirWS);

    // Ambient (not shadowed)
    vec3 ambientTerm = ambientColor * u_material_ambient;

    // Diffuse
    float NdotL = max(dot(n_diffuse, l), 0.0);
    vec3  diffuseTerm = diffuseColor * u_material_diffuse * NdotL;

    // Blinn–Phong specular with flat normal (seam-free)
    float shin = clamp(u_material_shininess, 1.0, 128.0);
    float specStrength = 0.9;
    if (NdotL > 0.0)
    {
        vec3 h = normalize(l + v);
        float NdotH = max(dot(n_flat, h), 0.0);
        specStrength = pow(NdotH, shin);
        // tame grazing spikes
        specStrength *= NdotL;
    }
    vec3 specularTerm = specularColor * u_material_specular * specStrength;

    // Apply shadowing to direct terms only
    return ambientTerm + intensity * attenuation * shadowVisibility * (diffuseTerm + specularTerm);
}

void main()
{
    vec3 normalWS = normalize(v_Normal);
    vec3 viewDir  = normalize(u_cameraPosWS - v_FragPos);

    vec3 colorAccum = vec3(0.0);

    // ----- Directional lights -----
    for (int i = 0; i < u_num_dir_lights; ++i)
    {
        // If your engine stores scene->light, flip here: vec3 lightDirWS = -u_dir_light_directions[i];
        vec3 lightDirWS = normalize(-u_dir_light_directions[i]); // light -> scene

        float visibility = 1.0;
        // TODO: later implement visibility if multiple directional shadows exist
        if (i == 0)
            visibility = DirShadowVisibility(v_FragPosLightSpace, normalWS, lightDirWS);

        colorAccum += ShadeBlinnPhong(
            normalWS, 
            viewDir, 
            lightDirWS,
            1.0,
            u_dir_light_ambient[i], 
            u_dir_light_diffuse[i], 
            u_dir_light_specular[i],
            1.0,
            visibility
        );
    }

    // ----- Point lights -----
    for (int i = 0; i < u_num_point_lights; ++i)
    {
        vec3 lightPosWS = u_point_light_positions[i];
        vec3 lightDirWS = lightPosWS - v_FragPos;   // light -> frag
        float dist      = length(lightDirWS);

        float attenuation = 1.0 / (u_point_light_constant[i] +
                                   u_point_light_linear[i] * dist +
                                   u_point_light_quadratic[i] * dist * dist);

        float visibility = 1.0;
        // TODO: later implement visibility if multiple point shadows exist
        if (i == 0)
            visibility = PointShadowVisibilitySingle(
                v_FragPos, 
                normalWS, 
                u_point_light_positions[i], 
                u_point_light_far_planes[i]
            );

        colorAccum += ShadeBlinnPhong(
            normalWS, 
            viewDir, 
            lightDirWS,
            u_point_light_intensity[i], 
            u_point_light_ambient[i], 
            u_point_light_diffuse[i], 
            u_point_light_specular[i],
            attenuation,
            visibility
        );
    }

    outColor = vec4(colorAccum, 1.0);
}
