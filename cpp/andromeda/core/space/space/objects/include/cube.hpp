#ifndef SPACE__OBJECTS__CUBE__HPP
#define SPACE__OBJECTS__CUBE__HPP


#include "geometric_object.hpp"
#include "surface_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "andromeda/space/colors/colors.hpp"
#include "andromeda/space/objects/i_cube.hpp"


namespace andromeda::space
{
    struct CubeFaceData
    {
        math::Vec3 normal;
        std::array<math::Vec3, 4> vertices;
    };

    class SPACE_API Cube
        : public ICube
        , public GeometricObject
        , public SurfaceObject
    {
    public:
        Cube(float half_extent, const Color& color);
        ~Cube();

        // Getters
        float get_half_extent() const override;
        // Setters
        void set_half_extent(float half_extent);

    private:
        void construct_cube(float half_extent, const Color& color);
        static std::array<CubeFaceData, 6> build_cube_faces(float half_extent);
        static void reserve_cube_buffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
        static void append_face(
            const CubeFaceData& face,
            const Color& color,
            std::vector<Vertex>& out_vertices,
            std::vector<unsigned int>& out_indices,
            unsigned int& index_offset
        );

    private:
        float m_half_extent;
    };
}


#endif // SPACE__OBJECTS__CUBE__HPP