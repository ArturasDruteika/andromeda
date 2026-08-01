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
    /// @brief Stores the geometry of a single cube face.
    ///
    /// Contains the face normal and the four corner vertices used to construct
    /// one side of a cube.
    struct CubeFaceData
    {
        /// @brief Surface normal of the face.
        math::Vec3 normal;

        /// @brief Corner vertices of the face.
        std::array<math::Vec3, 4> vertices;
    };

    /// @brief Represents a cube geometric object.
    ///
    /// Generates and stores the mesh for a cube with a configurable size and
    /// surface color.
    class SPACE_API Cube
        : public ICube
        , public GeometricObject
        , public SurfaceObject
    {
    public:
        /// @brief Constructs a cube.
        ///
        /// @param half_extent Half of the cube edge length.
        /// @param color Surface color of the cube.
        Cube(float half_extent, const Color& color);

        /// @brief Destroys the cube.
        ~Cube();

        // Getters

        /// @brief Retrieves the cube half-extent.
        ///
        /// @return Half of the cube edge length.
        float get_half_extent() const override;

        // Setters

        /// @brief Sets the cube half-extent.
        ///
        /// @param half_extent New half-edge length.
        void set_half_extent(float half_extent);

    private:
        /// @brief Builds the cube mesh.
        ///
        /// @param half_extent Half of the cube edge length.
        /// @param color Surface color of the cube.
        void construct_cube(float half_extent, const Color& color);

        /// @brief Builds the geometric description of all cube faces.
        ///
        /// @param half_extent Half of the cube edge length.
        /// @return Array containing all six cube faces.
        static std::array<CubeFaceData, 6> build_cube_faces(float half_extent);

        /// @brief Reserves memory for cube mesh buffers.
        ///
        /// @param vertices Vertex buffer.
        /// @param indices Index buffer.
        static void reserve_cube_buffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

        /// @brief Appends a face to the cube mesh buffers.
        ///
        /// @param face Face geometry.
        /// @param color Face color.
        /// @param out_vertices Destination vertex buffer.
        /// @param out_indices Destination index buffer.
        /// @param index_offset Current index offset.
        static void append_face(
            const CubeFaceData& face,
            const Color& color,
            std::vector<Vertex>& out_vertices,
            std::vector<unsigned int>& out_indices,
            unsigned int& index_offset
        );

    private:
        /// @brief Half of the cube edge length.
        float m_half_extent;
    };
}


#endif // SPACE__OBJECTS__CUBE__HPP