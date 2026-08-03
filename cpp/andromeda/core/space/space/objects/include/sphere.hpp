#pragma once


#include "geometric_object.hpp"
#include "surface_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/colors/colors.hpp"
#include "andromeda/space/objects/i_sphere.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
    /// @brief Represents a sphere geometric object.
    ///
    /// Generates and stores the mesh for a sphere with a configurable radius
    /// and surface color.
    class SPACE_API Sphere
        : public ISphere
        , public GeometricObject
        , public SurfaceObject
    {
    public:
        /// @brief Constructs a sphere.
        ///
        /// @param radius Sphere radius.
        /// @param color Surface color of the sphere.
        Sphere(float radius, const Color& color);

        /// @brief Destroys the sphere.
        ~Sphere();

        // Getters

        /// @brief Retrieves the sphere radius.
        ///
        /// @return Sphere radius.
        float get_radius() const override;

        // Setters

        /// @brief Sets the sphere radius.
        ///
        /// @param radius New sphere radius.
        void set_radius(float radius);

    private:
        /// @brief Builds the sphere mesh.
        ///
        /// @param radius Sphere radius.
        /// @param sector_count Number of longitudinal subdivisions.
        /// @param stack_count Number of latitudinal subdivisions.
        /// @param color Surface color of the sphere.
        void construct_sphere(float radius, int sector_count, int stack_count, const Color& color);

        /// @brief Validates and adjusts sphere tessellation parameters.
        ///
        /// @param sector_count Number of longitudinal subdivisions.
        /// @param stack_count Number of latitudinal subdivisions.
        void validate_sphere_params(int& sector_count, int& stack_count) const;

        /// @brief Generates the sphere vertices.
        ///
        /// @param radius Sphere radius.
        /// @param sector_count Number of longitudinal subdivisions.
        /// @param stack_count Number of latitudinal subdivisions.
        /// @param color Surface color.
        /// @param out_vertices Destination vertex buffer.
        void generate_sphere_vertices(
            float radius,
            int sector_count,
            int stack_count,
            const Color& color,
            std::vector<Vertex>& out_vertices
        ) const;

        /// @brief Generates the sphere index buffer.
        ///
        /// @param sector_count Number of longitudinal subdivisions.
        /// @param stack_count Number of latitudinal subdivisions.
        /// @param out_indices Destination index buffer.
        void generate_sphere_indices(
            int sector_count,
            int stack_count,
            std::vector<unsigned int>& out_indices
        ) const;

        /// @brief Computes the surface normal for a sphere vertex.
        ///
        /// @param x X-coordinate.
        /// @param y Y-coordinate.
        /// @param z Z-coordinate.
        /// @return Normalized surface normal.
        static math::Vec3 compute_sphere_normal(float x, float y, float z);

    private:
        /// @brief Sphere radius.
        float m_radius;
    };
}
