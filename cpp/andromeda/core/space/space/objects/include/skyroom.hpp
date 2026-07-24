#ifndef ANDROMEDA__SPACE__OBJECTS__SKYROOM__HPP
#define ANDROMEDA__SPACE__OBJECTS__SKYROOM__HPP


#include "geometric_object.hpp"
#include "surface_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "andromeda/space/objects/i_skyroom.hpp"
#include "andromeda/space/colors/colors.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    struct SkyroomFaceData
    {
        math::Vec3 normal;
        std::array<math::Vec3, 4> vertices;
    };

    class SPACE_API Skyroom
        : public ISkyroom
        , public GeometricObject
        , public SurfaceObject
    {
    public:
        Skyroom(float half_extent, const Color& color);
        ~Skyroom();

        // Getters
        float get_half_extent() const override;
        // Setters
        void set_half_extent(float half_extent) override;

    private:
        void construct_skyroom(float half_extent, const Color& color);
        void validate_skyroom_params(float half_extent) const;

        static std::array<SkyroomFaceData, 6> build_skyroom_faces(float half_extent);
        static void reserve_skyroom_buffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

        static void append_face_inside(
            const SkyroomFaceData& face,
            const Color& color,
            std::vector<Vertex>& out_vertices,
            std::vector<unsigned int>& out_indices,
            unsigned int& index_offset
        );

    private:
        float m_half_extent;
    };
}


#endif // ANDROMEDA__SPACE__OBJECTS__SKYROOM__HPP