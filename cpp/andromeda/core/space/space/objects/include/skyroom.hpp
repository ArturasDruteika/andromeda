#pragma once


#include "geometric_object.hpp"
#include "surface_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "andromeda/space/objects/i_skyroom.hpp"
#include "andromeda/space/colors/colors.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    /// @brief Stores the geometry of a single skyroom face.
    ///
    /// Contains the face normal and the four corner vertices used to construct
    /// one inward-facing side of the skyroom.
    struct SkyroomFaceData
    {
        /// @brief Surface normal of the face.
        math::Vec3 normal;

        /// @brief Corner vertices of the face.
        std::array<math::Vec3, 4> vertices;
    };

    /// @brief Represents a skyroom enclosing the scene.
    ///
    /// Generates inward-facing geometry used as a surrounding environment for
    /// rendering backgrounds or sky effects.
    class SPACE_API Skyroom
        : public ISkyroom
        , public GeometricObject
        , public SurfaceObject
    {
    public:
        /// @brief Constructs a skyroom.
        ///
        /// @param half_extent Half of the skyroom edge length.
        /// @param color Surface color of the skyroom.
        Skyroom(float half_extent, const Color& color);

        /// @brief Destroys the skyroom.
        ~Skyroom();

        // Getters

        /// @brief Retrieves the skyroom half-extent.
        ///
        /// @return Half of the skyroom edge length.
        float get_half_extent() const override;

        // Setters

        /// @brief Sets the skyroom half-extent.
        ///
        /// @param half_extent New half-edge length.
        void set_half_extent(float half_extent) override;

    private:
        /// @brief Builds the skyroom mesh.
        ///
        /// @param half_extent Half of the skyroom edge length.
        /// @param color Surface color of the skyroom.
        void construct_skyroom(float half_extent, const Color& color);

        /// @brief Validates skyroom construction parameters.
        ///
        /// @param half_extent Half of the skyroom edge length.
        void validate_skyroom_params(float half_extent) const;

        /// @brief Builds the geometric description of all skyroom faces.
        ///
        /// @param half_extent Half of the skyroom edge length.
        /// @return Array containing all six skyroom faces.
        static std::array<SkyroomFaceData, 6> build_skyroom_faces(float half_extent);

        /// @brief Reserves memory for skyroom mesh buffers.
        ///
        /// @param vertices Vertex buffer.
        /// @param indices Index buffer.
        static void reserve_skyroom_buffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

        /// @brief Appends an inward-facing face to the skyroom mesh.
        ///
        /// @param face Face geometry.
        /// @param color Face color.
        /// @param out_vertices Destination vertex buffer.
        /// @param out_indices Destination index buffer.
        /// @param index_offset Current index offset.
        static void append_face_inside(
            const SkyroomFaceData& face,
            const Color& color,
            std::vector<Vertex>& out_vertices,
            std::vector<unsigned int>& out_indices,
            unsigned int& index_offset
        );

    private:
        /// @brief Half of the skyroom edge length.
        float m_half_extent;
    };
}
