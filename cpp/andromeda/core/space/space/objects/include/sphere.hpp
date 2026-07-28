#ifndef ANDROMEDA__SPACE__OBJECTS__SPHERE__HPP
#define ANDROMEDA__SPACE__OBJECTS__SPHERE__HPP


#include "geometric_object.hpp"
#include "surface_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/colors/colors.hpp"
#include "andromeda/space/objects/i_sphere.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
    class SPACE_API Sphere
        : public ISphere
        , public GeometricObject
        , public SurfaceObject
    {
    public:
        Sphere(float radius, const Color& color);
        ~Sphere();

        // Getters
        float get_radius() const override;
        // Setters
        void set_radius(float radius);

    private:
        void construct_sphere(float radius, int sector_count, int stack_count, const Color& color);
        void validate_sphere_params(int& sector_count, int& stack_count) const;
        void generate_sphere_vertices(
            float radius,
            int sector_count,
            int stack_count,
            const Color& color,
            std::vector<Vertex>& out_vertices
        ) const;

        void generate_sphere_indices(
            int sector_count,
            int stack_count,
            std::vector<unsigned int>& out_indices
        ) const;

        static math::Vec3 compute_sphere_normal(float x, float y, float z);

    private:
        float m_radius;
    };
}


#endif // ANDROMEDA__SPACE__OBJECTS__SPHERE__HPP