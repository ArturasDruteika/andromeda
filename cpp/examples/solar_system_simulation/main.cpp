#include "andromeda/application/i_application.hpp"
#include "andromeda/space/scene/i_scene_update_hooks.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"
#include "space/objects/include/sphere.hpp"
#include "space/scene/include/scene.hpp"
#include "space/scene_graph/include/scene_node.hpp"
#include "space/scene_graph/include/object_component.hpp"
#include "space/transformations/include/transformable.hpp"
#include "space/camera/include/camera.hpp"
#include "space/materials/include/materials_library.hpp"

#include "spdlog/spdlog.h"

#include <cmath>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>


struct OrbitalBody
{
    int id;
    int parent_id;
    float orbit_radius;
    float orbit_speed;
};

struct SolarSystem
{
    int sun_id;
    std::vector<OrbitalBody> planets;
    std::vector<OrbitalBody> moons;
};

struct SolarSystemState
{
    float time = 0.0f;
};

constexpr float kPi = 3.1415926535f;
constexpr float kTwoPi = 2.0f * kPi;
constexpr float kEarthOrbitRadius = 10.0f;
constexpr float kSecondsPerMinute = 60.0f;
constexpr float kEarthDaysPerMinute = 365.0f;
constexpr float kKmPerAu = 149597870.7f;
// Inflate moon distances so they remain visible while preserving relative spacing.
constexpr float kMoonOrbitScale = 80.0f;

float orbit_speed_from_days(float period_days)
{
    const float period_seconds =
        kSecondsPerMinute * (period_days / kEarthDaysPerMinute);

    return kTwoPi / period_seconds;
}

int add_sphere_object(
    andromeda::space::Scene& scene,
    const andromeda::IMaterial* p_material,
    int id,
    float radius,
    const andromeda::Color& color,
    const andromeda::math::Vec3& position
)
{
    andromeda::space::Sphere* p_sphere =
        new andromeda::space::Sphere(radius, color);

    if (p_material)
    {
        p_sphere->set_material(p_material);
    }

    std::unique_ptr<andromeda::space::SceneNode> node =
        std::make_unique<andromeda::space::SceneNode>(
            std::make_unique<andromeda::Transformable>(position)
        );

    node->add_component(
        std::make_unique<andromeda::space::ObjectComponent>(id, p_sphere)
    );

    scene.attach_node(std::move(node));

    return id;
}

SolarSystem add_solar_system(
    andromeda::space::Scene& scene,
    const andromeda::space::MaterialLibrary& material_library
)
{
    const andromeda::IMaterial* p_material = nullptr;

    if (material_library.get_size() > 0)
    {
        const std::vector<andromeda::space::MaterialType> material_types =
            material_library.get_all_material_types();

        if (!material_types.empty())
        {
            p_material =
                material_library.get_material_ptr(material_types.front());
        }
    }

    SolarSystem system{};
    int next_id = 1001;

    system.sun_id = next_id++;

    add_sphere_object(
        scene,
        p_material,
        system.sun_id,
        1.5f,
        andromeda::Color{ 1.0f, 0.8f, 0.2f, 1.0f },
        andromeda::math::Vec3{ 0.0f, 0.0f, 0.0f }
    );

    auto add_planet = [&](
        int& out_id,
        float radius,
        const andromeda::Color& color,
        float orbit_au,
        float period_days
    )
    {
        const float orbit_radius = kEarthOrbitRadius * orbit_au;
        const float orbit_speed = orbit_speed_from_days(period_days);

        out_id = next_id++;

        add_sphere_object(
            scene,
            p_material,
            out_id,
            radius,
            color,
            andromeda::math::Vec3{ orbit_radius, 0.0f, 0.0f }
        );

        system.planets.push_back(
            OrbitalBody{
                out_id,
                system.sun_id,
                orbit_radius,
                orbit_speed
            }
        );
    };

    int mercury_id = 0;
    int venus_id = 0;
    int earth_id = 0;
    int mars_id = 0;
    int jupiter_id = 0;
    int saturn_id = 0;
    int uranus_id = 0;
    int neptune_id = 0;

    add_planet(
        mercury_id,
        0.18f,
        andromeda::Color{ 0.6f, 0.6f, 0.6f, 1.0f },
        0.387f,
        87.969f
    );

    add_planet(
        venus_id,
        0.45f,
        andromeda::Color{ 0.9f, 0.8f, 0.6f, 1.0f },
        0.723f,
        224.701f
    );

    add_planet(
        earth_id,
        0.5f,
        andromeda::Color{ 0.2f, 0.5f, 1.0f, 1.0f },
        1.0f,
        365.256f
    );

    add_planet(
        mars_id,
        0.35f,
        andromeda::Color{ 0.8f, 0.3f, 0.2f, 1.0f },
        1.524f,
        686.98f
    );

    add_planet(
        jupiter_id,
        1.0f,
        andromeda::Color{ 0.85f, 0.6f, 0.4f, 1.0f },
        5.203f,
        4332.59f
    );

    add_planet(
        saturn_id,
        0.9f,
        andromeda::Color{ 0.9f, 0.85f, 0.6f, 1.0f },
        9.537f,
        10759.22f
    );

    add_planet(
        uranus_id,
        0.7f,
        andromeda::Color{ 0.6f, 0.85f, 0.9f, 1.0f },
        19.191f,
        30688.5f
    );

    add_planet(
        neptune_id,
        0.7f,
        andromeda::Color{ 0.2f, 0.3f, 0.8f, 1.0f },
        30.07f,
        60182.0f
    );

    auto add_moon = [&](
        int parent_id,
        float parent_orbit_radius,
        float radius,
        const andromeda::Color& color,
        float distance_km,
        float period_days
    )
    {
        const float distance_au = distance_km / kKmPerAu;
        const float orbit_radius =
            distance_au * kEarthOrbitRadius * kMoonOrbitScale;

        const float orbit_speed = orbit_speed_from_days(period_days);
        const int moon_id = next_id++;

        add_sphere_object(
            scene,
            p_material,
            moon_id,
            radius,
            color,
            andromeda::math::Vec3{
                parent_orbit_radius + orbit_radius,
                0.0f,
                0.0f
            }
        );

        system.moons.push_back(
            OrbitalBody{
                moon_id,
                parent_id,
                orbit_radius,
                orbit_speed
            }
        );
    };

    add_moon(
        earth_id,
        kEarthOrbitRadius,
        0.16f,
        andromeda::Color{ 0.8f, 0.8f, 0.9f, 1.0f },
        384400.0f,
        27.3217f
    );

    add_moon(
        mars_id,
        kEarthOrbitRadius * 1.524f,
        0.08f,
        andromeda::Color{ 0.5f, 0.4f, 0.4f, 1.0f },
        9376.0f,
        0.3189f
    );

    add_moon(
        mars_id,
        kEarthOrbitRadius * 1.524f,
        0.06f,
        andromeda::Color{ 0.6f, 0.5f, 0.5f, 1.0f },
        23463.0f,
        1.2624f
    );

    add_moon(
        jupiter_id,
        kEarthOrbitRadius * 5.203f,
        0.16f,
        andromeda::Color{ 0.9f, 0.8f, 0.4f, 1.0f },
        421700.0f,
        1.769f
    );

    add_moon(
        jupiter_id,
        kEarthOrbitRadius * 5.203f,
        0.16f,
        andromeda::Color{ 0.8f, 0.8f, 0.9f, 1.0f },
        671100.0f,
        3.551f
    );

    add_moon(
        jupiter_id,
        kEarthOrbitRadius * 5.203f,
        0.2f,
        andromeda::Color{ 0.7f, 0.7f, 0.7f, 1.0f },
        1070400.0f,
        7.155f
    );

    add_moon(
        jupiter_id,
        kEarthOrbitRadius * 5.203f,
        0.18f,
        andromeda::Color{ 0.4f, 0.4f, 0.4f, 1.0f },
        1882700.0f,
        16.689f
    );

    add_moon(
        saturn_id,
        kEarthOrbitRadius * 9.537f,
        0.2f,
        andromeda::Color{ 0.9f, 0.7f, 0.4f, 1.0f },
        1221870.0f,
        15.945f
    );

    add_moon(
        saturn_id,
        kEarthOrbitRadius * 9.537f,
        0.12f,
        andromeda::Color{ 0.9f, 0.9f, 0.95f, 1.0f },
        237948.0f,
        1.37f
    );

    add_moon(
        saturn_id,
        kEarthOrbitRadius * 9.537f,
        0.14f,
        andromeda::Color{ 0.7f, 0.7f, 0.7f, 1.0f },
        527108.0f,
        4.518f
    );

    add_moon(
        saturn_id,
        kEarthOrbitRadius * 9.537f,
        0.14f,
        andromeda::Color{ 0.6f, 0.6f, 0.6f, 1.0f },
        3560820.0f,
        79.3215f
    );

    add_moon(
        uranus_id,
        kEarthOrbitRadius * 19.191f,
        0.1f,
        andromeda::Color{ 0.7f, 0.7f, 0.75f, 1.0f },
        129390.0f,
        1.414f
    );

    add_moon(
        uranus_id,
        kEarthOrbitRadius * 19.191f,
        0.12f,
        andromeda::Color{ 0.7f, 0.75f, 0.8f, 1.0f },
        191020.0f,
        2.52f
    );

    add_moon(
        uranus_id,
        kEarthOrbitRadius * 19.191f,
        0.12f,
        andromeda::Color{ 0.6f, 0.65f, 0.7f, 1.0f },
        266300.0f,
        4.144f
    );

    add_moon(
        uranus_id,
        kEarthOrbitRadius * 19.191f,
        0.14f,
        andromeda::Color{ 0.75f, 0.75f, 0.8f, 1.0f },
        435910.0f,
        8.706f
    );

    add_moon(
        uranus_id,
        kEarthOrbitRadius * 19.191f,
        0.14f,
        andromeda::Color{ 0.65f, 0.65f, 0.7f, 1.0f },
        583520.0f,
        13.463f
    );

    add_moon(
        neptune_id,
        kEarthOrbitRadius * 30.07f,
        0.16f,
        andromeda::Color{ 0.7f, 0.7f, 0.8f, 1.0f },
        354759.0f,
        5.877f
    );

    add_moon(
        neptune_id,
        kEarthOrbitRadius * 30.07f,
        0.12f,
        andromeda::Color{ 0.6f, 0.6f, 0.7f, 1.0f },
        5513818.0f,
        360.13f
    );

    add_moon(
        neptune_id,
        kEarthOrbitRadius * 30.07f,
        0.1f,
        andromeda::Color{ 0.5f, 0.55f, 0.6f, 1.0f },
        117647.0f,
        1.122f
    );

    return system;
}

void update_solar_system(
    andromeda::space::Scene& scene,
    SolarSystemState& state,
    const SolarSystem& system,
    float dt
)
{
    state.time += dt;

    const auto& transforms = scene.get_object_transforms();

    auto sun_it = transforms.find(system.sun_id);
    if (sun_it == transforms.end() || !sun_it->second)
    {
        return;
    }

    std::unordered_map<int, andromeda::math::Vec3> positions;

    const andromeda::math::Vec3 sun_pos =
        sun_it->second->get_position();

    positions[system.sun_id] = sun_pos;

    for (const auto& planet : system.planets)
    {
        auto planet_it = transforms.find(planet.id);
        if (planet_it == transforms.end() || !planet_it->second)
        {
            continue;
        }

        const andromeda::math::Vec3 parent_pos =
            positions[planet.parent_id];

        const float angle = state.time * planet.orbit_speed;

        const andromeda::math::Vec3 planet_pos{
            parent_pos[0] + std::cos(angle) * planet.orbit_radius,
            parent_pos[1],
            parent_pos[2] + std::sin(angle) * planet.orbit_radius
        };

        planet_it->second->set_position(planet_pos);
        positions[planet.id] = planet_pos;
    }

    for (const auto& moon : system.moons)
    {
        auto moon_it = transforms.find(moon.id);
        if (moon_it == transforms.end() || !moon_it->second)
        {
            continue;
        }

        auto parent_pos_it = positions.find(moon.parent_id);
        if (parent_pos_it == positions.end())
        {
            continue;
        }

        const andromeda::math::Vec3 parent_pos =
            parent_pos_it->second;

        const float angle = state.time * moon.orbit_speed;

        const andromeda::math::Vec3 moon_pos{
            parent_pos[0] + std::cos(angle) * moon.orbit_radius,
            parent_pos[1],
            parent_pos[2] + std::sin(angle) * moon.orbit_radius
        };

        moon_it->second->set_position(moon_pos);
    }
}


int main(void)
{
    unsigned int width = 800;
    unsigned int height = 600;
    std::string title = "andromeda - Solar System Simulation";

    // Load materials once and reuse
    andromeda::space::MaterialLibrary material_library(
        std::filesystem::path(
            "material_properties/material_properties.json"
        )
    );

    if (material_library.get_size() == 0)
    {
        spdlog::warn(
            "No materials loaded from assets/materials.json; spheres will fall back to having no materials."
        );
    }

    andromeda::space::Scene* p_scene =
        new andromeda::space::Scene();

    andromeda::space::Camera* p_camera =
        new andromeda::space::Camera(
            andromeda::math::Vec3{ 0.0f, 40.0f, 220.0f }
        );

    p_scene->set_active_camera(p_camera);
    p_scene->set_background_color(
        andromeda::math::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f }
    );

    const SolarSystem solar_system =
        add_solar_system(*p_scene, material_library);

    SolarSystemState solar_system_state{};

    andromeda::ISceneUpdateHooks::Handle handle =
        p_scene->add_update_callback(
            [p_scene, solar_system_state, solar_system](float dt) mutable
            {
                update_solar_system(
                    *p_scene,
                    solar_system_state,
                    solar_system,
                    dt
                );
            }
        );

    std::unique_ptr<andromeda::IApplication> p_app =
        andromeda::create_app(andromeda::GraphicsBackend::OpenGL);

    if (!p_app->init(width, height, title))
    {
        spdlog::error("Failed to initialize Application.");
        return -1;
    }

    p_app->set_scene(p_scene);

    andromeda::IRenderer* p_renderer =
        p_app->get_renderer();

    p_renderer->set_illumination_mode(false);
    p_app->run();

    return 0;
}