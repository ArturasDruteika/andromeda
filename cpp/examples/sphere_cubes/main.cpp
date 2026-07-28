#include "andromeda/application/i_application.hpp"
#include "space/objects/include/sphere.hpp"
#include "space/scene/include/scene.hpp"
#include "space/scene_graph/include/scene_node.hpp"
#include "space/scene_graph/include/object_component.hpp"
#include "space/scene_graph/include/light_component.hpp"
#include "space/transformations/include/transformable.hpp"
#include "space/camera/include/camera.hpp"
#include "space/materials/include/materials_library.hpp"
#include "space/light/include/directional_light.hpp"

#include "spdlog/spdlog.h"

#include <filesystem>
#include <random>
#include <string>
#include <vector>


void populate_scene_with_dummy_objects(
    andromeda::space::Scene& scene,
    const andromeda::space::MaterialLibrary& material_library
)
{
    // Precompute available material types for random selection
    std::vector<andromeda::space::MaterialType> material_types =
        material_library.get_all_material_types();

    if (material_types.empty())
    {
        spdlog::warn(
            "PopulateSceneWithDummyObjects - MaterialLibrary is empty; spheres will have no materials set."
        );
    }

    std::mt19937 rng(1337);
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
    std::uniform_real_distribution<float> color_dist(0.1f, 0.9f);

    std::uniform_int_distribution<size_t> material_dist(
        0,
        material_types.empty() ? 0 : material_types.size() - 1
    );

    // Sun
    andromeda::space::DirectionalLight* p_sun =
        new andromeda::space::DirectionalLight(
            andromeda::math::Vec3{ 10.0f, 10.0f, 10.0f },
            andromeda::math::Vec3{ 1.0f, 1.0f, 1.0f },
            1.0f
        );

    {
        std::unique_ptr<andromeda::space::SceneNode> sun_node =
            std::make_unique<andromeda::space::SceneNode>(
                std::make_unique<andromeda::Transformable>(
                    andromeda::math::Vec3{ 10.0f, 10.0f, 10.0f }
                )
            );

        sun_node->add_component(
            std::make_unique<andromeda::space::LightComponent>(0, p_sun)
        );

        scene.attach_node(std::move(sun_node));
    }

    andromeda::space::Sphere* p_center_sphere =
        new andromeda::space::Sphere(
            0.1f,
            andromeda::Color{ 0.2f, 0.9f, 1.0f, 1.0f }
        );

    {
        std::unique_ptr<andromeda::space::SceneNode> center_node =
            std::make_unique<andromeda::space::SceneNode>(
                std::make_unique<andromeda::Transformable>(
                    andromeda::math::Vec3{ 0.0f, 0.0f, 0.0f }
                )
            );

        center_node->add_component(
            std::make_unique<andromeda::space::ObjectComponent>(
                1,
                p_center_sphere
            )
        );

        scene.attach_node(std::move(center_node));
    }

    if (!material_types.empty())
    {
        andromeda::space::MaterialType sphere_center_mat_type =
            material_types[material_dist(rng)];

        const andromeda::IMaterial* p_sphere_center_mat =
            material_library.get_material_ptr(sphere_center_mat_type);

        if (p_sphere_center_mat)
        {
            p_center_sphere->set_material(p_sphere_center_mat);
        }
    }

    const int kSphereCount = 1000;

    for (int i = 2; i < kSphereCount; ++i)
    {
        andromeda::math::Vec3 pos{
            dist(rng),
            dist(rng),
            dist(rng)
        };

        andromeda::Color color{
            color_dist(rng),
            color_dist(rng),
            color_dist(rng),
            1.0f
        };

        andromeda::space::Sphere* p_sphere =
            new andromeda::space::Sphere(
                1.0f,
                color
            );

        // Assign random material
        if (!material_types.empty())
        {
            andromeda::space::MaterialType mat_type =
                material_types[material_dist(rng)];

            const andromeda::IMaterial* p_mat =
                material_library.get_material_ptr(mat_type);

            if (p_mat)
            {
                p_sphere->set_material(p_mat);
            }
        }

        {
            std::unique_ptr<andromeda::space::SceneNode> sphere_node =
                std::make_unique<andromeda::space::SceneNode>(
                    std::make_unique<andromeda::Transformable>(pos)
                );

            sphere_node->add_component(
                std::make_unique<andromeda::space::ObjectComponent>(
                    i,
                    p_sphere
                )
            );

            scene.attach_node(std::move(sphere_node));
        }
    }
}


int main(void)
{
    unsigned int width = 800;
    unsigned int height = 600;
    std::string title = "andromeda - SphereCubes";

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
            andromeda::math::Vec3{ 0.0f, 0.0f, 10.0f }
        );

    p_scene->set_active_camera(p_camera);

    p_scene->set_background_color(
        andromeda::math::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f }
    );

    populate_scene_with_dummy_objects(*p_scene, material_library);

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