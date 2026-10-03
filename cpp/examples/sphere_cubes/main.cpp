#include "andromeda/application/i_application.hpp"
#include "andromeda/space/scene/i_scene_update_hooks.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"
#include "andromeda/space/objects/sphere.hpp"
#include "andromeda/space/scene/scene.hpp"
#include "andromeda/space/scene_graph/scene_node.hpp"
#include "andromeda/space/scene_graph/object_component.hpp"
#include "andromeda/space/scene_graph/light_component.hpp"
#include "andromeda/space/transformations/transformable.hpp"
#include "andromeda/space/camera/camera.hpp"
#include "andromeda/space/materials/materials_library.hpp"
#include "andromeda/space/light/point_light.hpp"

#include "spdlog/spdlog.h"

#include <cmath>
#include <filesystem>
#include <random>
#include <string>
#include <vector>


constexpr float kPi = 3.1415926535f;
constexpr float kTwoPi = 2.0f * kPi;


/*
 * Information required to animate one sphere.
 *
 * Each sphere keeps its original position relative to the point light
 * and gets independent rotation speeds around X, Y and Z.
 */
struct OrbitingSphere
{
    int id;

    andromeda::math::Vec3 initial_position;

    float angle_x;
    float angle_y;
    float angle_z;

    float speed_x;
    float speed_y;
    float speed_z;
};


/*
 * Mutable animation state.
 */
struct SphereCubeState
{
    std::vector<OrbitingSphere> spheres;
};


/*
 * Creates the point light and all surrounding spheres.
 */
SphereCubeState populate_scene_with_dummy_objects(
    andromeda::space::Scene& scene,
    const andromeda::space::MaterialLibrary& material_library
)
{
    SphereCubeState state{};

    // ---------------------------------------------------------------------
    // Materials
    // ---------------------------------------------------------------------

    std::vector<andromeda::space::MaterialType> material_types =
        material_library.get_all_material_types();

    if (material_types.empty())
    {
        spdlog::warn(
            "PopulateSceneWithDummyObjects - "
            "MaterialLibrary is empty; spheres will have no materials set."
        );
    }


    // ---------------------------------------------------------------------
    // Random generators
    // ---------------------------------------------------------------------

    std::mt19937 rng(1337);

    std::uniform_real_distribution<float> dist(
        -100.0f,
        100.0f
    );

    std::uniform_real_distribution<float> color_dist(
        0.1f,
        0.9f
    );

    /*
     * Angular velocity in radians / second.
     *
     * Every sphere receives independent speeds for X, Y and Z.
     */
    std::uniform_real_distribution<float> speed_dist(
        0.05f,
        0.25f
    );

    std::uniform_int_distribution<size_t> material_dist(
        0,
        material_types.empty()
            ? 0
            : material_types.size() - 1
    );


    // =====================================================================
    // Point light at the origin
    // =====================================================================

    const andromeda::math::Vec3 light_position{
        0.0f,
        0.0f,
        0.0f
    };

    andromeda::space::PointLight* p_point_light =
        new andromeda::space::PointLight(
            light_position,

            // Color
            andromeda::math::Vec3{
                1.0f,
                0.95f,
                0.8f
            },

            // Intensity
            2.0f,

            // Ambient
            andromeda::math::Vec3{
                0.05f,
                0.05f,
                0.05f
            },

            // Diffuse
            andromeda::math::Vec3{
                1.0f,
                0.95f,
                0.8f
            },

            // Specular
            andromeda::math::Vec3{
                1.0f,
                1.0f,
                1.0f
            },

            // Attenuation constant
            1.0f,

            // Attenuation linear
            0.007f,

            // Attenuation quadratic
            0.0002f,

            // Shadow near plane
            0.1f,

            // Shadow far plane
            300.0f
        );


    // =====================================================================
    // Visible sphere representing the point light
    // =====================================================================

    andromeda::space::Sphere* p_center_sphere =
        new andromeda::space::Sphere(
            3.0f,
            andromeda::Color{
                1.0f,
                0.9f,
                0.6f,
                1.0f
            }
        );

    p_center_sphere->set_luminous(true);


    // =====================================================================
    // Center scene node
    // =====================================================================

    {
        std::unique_ptr<andromeda::space::SceneNode> light_node =
            std::make_unique<andromeda::space::SceneNode>(
                std::make_unique<andromeda::Transformable>(
                    light_position
                )
            );

        light_node->add_component(
            std::make_unique<andromeda::space::LightComponent>(
                0,
                p_point_light
            )
        );

        light_node->add_component(
            std::make_unique<andromeda::space::ObjectComponent>(
                1,
                p_center_sphere
            )
        );

        scene.attach_node(
            std::move(light_node)
        );
    }


    // =====================================================================
    // Create surrounding spheres
    // =====================================================================

    const int kSphereCount = 1000;

    state.spheres.reserve(kSphereCount - 2);

    for (int i = 2; i < kSphereCount; ++i)
    {
        // -------------------------------------------------------------
        // Initial random position
        // -------------------------------------------------------------

        const andromeda::math::Vec3 pos{
            dist(rng),
            dist(rng),
            dist(rng)
        };


        // -------------------------------------------------------------
        // Random color
        // -------------------------------------------------------------

        const andromeda::Color color{
            color_dist(rng),
            color_dist(rng),
            color_dist(rng),
            1.0f
        };


        // -------------------------------------------------------------
        // Create sphere
        // -------------------------------------------------------------

        andromeda::space::Sphere* p_sphere =
            new andromeda::space::Sphere(
                1.0f,
                color
            );


        // -------------------------------------------------------------
        // Assign random material
        // -------------------------------------------------------------

        if (!material_types.empty())
        {
            const andromeda::space::MaterialType mat_type =
                material_types[
                    material_dist(rng)
                ];

            const andromeda::IMaterial* p_mat =
                material_library.get_material_ptr(
                    mat_type
                );

            if (p_mat)
            {
                p_sphere->set_material(
                    p_mat
                );
            }
        }


        // -------------------------------------------------------------
        // Add sphere to scene
        // -------------------------------------------------------------

        {
            std::unique_ptr<andromeda::space::SceneNode> sphere_node =
                std::make_unique<andromeda::space::SceneNode>(
                    std::make_unique<andromeda::Transformable>(
                        pos
                    )
                );

            sphere_node->add_component(
                std::make_unique<andromeda::space::ObjectComponent>(
                    i,
                    p_sphere
                )
            );

            scene.attach_node(
                std::move(sphere_node)
            );
        }


        // -------------------------------------------------------------
        // Store animation state.
        //
        // The original XYZ position is kept. Every frame that position
        // is rotated around the origin.
        // -------------------------------------------------------------

        state.spheres.push_back(
            OrbitingSphere{
                i,

                // Original position
                pos,

                // Initial angles
                0.0f,
                0.0f,
                0.0f,

                // Independent X/Y/Z angular velocities
                speed_dist(rng),
                speed_dist(rng),
                speed_dist(rng)
            }
        );
    }


    return state;
}


/*
 * Called every frame.
 *
 * Each sphere's original position vector is rotated around:
 *
 *      X axis
 *          ↓
 *      Y axis
 *          ↓
 *      Z axis
 *
 * Because these rotations are around (0,0,0), the distance between
 * each sphere and the point light remains constant.
 */
void update_orbiting_spheres(
    andromeda::space::Scene& scene,
    SphereCubeState& state,
    float dt
)
{
    const auto& transforms =
        scene.get_object_transforms();


    for (OrbitingSphere& sphere : state.spheres)
    {
        auto transform_it =
            transforms.find(
                sphere.id
            );


        if (
            transform_it == transforms.end() ||
            !transform_it->second
        )
        {
            continue;
        }


        // =============================================================
        // Update rotation angles
        // =============================================================

        sphere.angle_x +=
            sphere.speed_x * dt;

        sphere.angle_y +=
            sphere.speed_y * dt;

        sphere.angle_z +=
            sphere.speed_z * dt;


        // Prevent the angles from becoming extremely large.
        sphere.angle_x =
            std::fmod(
                sphere.angle_x,
                kTwoPi
            );

        sphere.angle_y =
            std::fmod(
                sphere.angle_y,
                kTwoPi
            );

        sphere.angle_z =
            std::fmod(
                sphere.angle_z,
                kTwoPi
            );


        // =============================================================
        // Start with the ORIGINAL position
        // =============================================================

        float x =
            sphere.initial_position[0];

        float y =
            sphere.initial_position[1];

        float z =
            sphere.initial_position[2];


        // =============================================================
        // X AXIS ROTATION
        //
        //     | 1    0       0  |
        //     | 0   cos    -sin |
        //     | 0   sin     cos |
        //
        // =============================================================

        {
            const float c =
                std::cos(
                    sphere.angle_x
                );

            const float s =
                std::sin(
                    sphere.angle_x
                );


            const float new_y =
                y * c -
                z * s;

            const float new_z =
                y * s +
                z * c;


            y = new_y;
            z = new_z;
        }


        // =============================================================
        // Y AXIS ROTATION
        //
        //     | cos   0   sin |
        //     |  0    1    0  |
        //     |-sin   0   cos |
        //
        // =============================================================

        {
            const float c =
                std::cos(
                    sphere.angle_y
                );

            const float s =
                std::sin(
                    sphere.angle_y
                );


            const float new_x =
                x * c +
                z * s;

            const float new_z =
                -x * s +
                z * c;


            x = new_x;
            z = new_z;
        }


        // =============================================================
        // Z AXIS ROTATION
        //
        //     | cos   -sin   0 |
        //     | sin    cos   0 |
        //     |  0      0    1 |
        //
        // =============================================================

        {
            const float c =
                std::cos(
                    sphere.angle_z
                );

            const float s =
                std::sin(
                    sphere.angle_z
                );


            const float new_x =
                x * c -
                y * s;

            const float new_y =
                x * s +
                y * c;


            x = new_x;
            y = new_y;
        }


        // =============================================================
        // Final XYZ position
        // =============================================================

        const andromeda::math::Vec3 position{
            x,
            y,
            z
        };


        // =============================================================
        // Update transform
        // =============================================================

        transform_it->second->set_position(
            position
        );
    }
}


int main(void)
{
    // =====================================================================
    // Window
    // =====================================================================

    unsigned int width = 800;
    unsigned int height = 600;

    std::string title =
        "andromeda - 3D Orbiting Spheres";


    // =====================================================================
    // Materials
    // =====================================================================

    andromeda::space::MaterialLibrary material_library(
        std::filesystem::path(
            "../res/material_properties/material_properties.json"
        )
    );


    if (material_library.get_size() == 0)
    {
        spdlog::warn(
            "No materials loaded from "
            "res/materials.json; spheres will fall back "
            "to having no materials."
        );
    }


    // =====================================================================
    // Scene
    // =====================================================================

    andromeda::space::Scene* p_scene =
        new andromeda::space::Scene();


    // =====================================================================
    // Camera
    //
    // The original example used Z = 25, but the sphere cloud extends
    // approximately +/-100 units, so moving the camera farther away
    // makes the complete 3D motion much easier to see.
    // =====================================================================

    andromeda::space::Camera* p_camera =
        new andromeda::space::Camera(
            andromeda::math::Vec3{
                0.0f,
                0.0f,
                250.0f
            }
        );


    p_scene->set_active_camera(
        p_camera
    );


    // =====================================================================
    // Background
    // =====================================================================

    p_scene->set_background_color(
        andromeda::math::Vec4{
            0.0f,
            0.0f,
            0.0f,
            1.0f
        }
    );


    // =====================================================================
    // Populate scene
    // =====================================================================

    SphereCubeState sphere_state =
        populate_scene_with_dummy_objects(
            *p_scene,
            material_library
        );


    // =====================================================================
    // Per-frame update
    //
    // This uses the same scene update mechanism as your solar-system
    // simulation.
    // =====================================================================

    andromeda::ISceneUpdateHooks::Handle update_handle =
        p_scene->add_update_callback(
            [
                p_scene,
                sphere_state
            ]
            (float dt) mutable
            {
                update_orbiting_spheres(
                    *p_scene,
                    sphere_state,
                    dt
                );
            }
        );


    // =====================================================================
    // Application
    // =====================================================================

    std::unique_ptr<andromeda::IApplication> p_app =
        andromeda::create_app(
            andromeda::GraphicsBackend::OpenGL
        );


    if (!p_app->init(
        width,
        height,
        title
    ))
    {
        spdlog::error(
            "Failed to initialize Application."
        );

        return -1;
    }


    p_app->set_scene(
        p_scene
    );


    // =====================================================================
    // Renderer
    // =====================================================================

    andromeda::IRenderer* p_renderer =
        p_app->get_renderer();


    p_renderer->set_illumination_mode(
        true
    );


    // =====================================================================
    // Run
    // =====================================================================

    p_app->run();


    return 0;
}