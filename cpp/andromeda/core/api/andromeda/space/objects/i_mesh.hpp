#ifndef API__OBJECTS__I_MESH__HPP
#define API__OBJECTS__I_MESH__HPP


#include "andromeda/space/vertices/vertex.hpp"
#include <vector>


namespace andromeda
{
    /// @brief Defines the interface for a mesh.
    ///
    /// A mesh stores the vertex and index data that describes the geometry of
    /// a renderable object.
    class IMesh
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IMesh() = default;

        // Getters

        /// @brief Retrieves the number of indices in the mesh.
        ///
        /// @return Total number of indices.
        virtual unsigned int get_index_count() const = 0;

        /// @brief Retrieves the number of vertices in the mesh.
        ///
        /// @return Total number of vertices.
        virtual unsigned int get_vertex_count() const = 0;

        /// @brief Retrieves the mesh index buffer.
        ///
        /// @return Reference to the index array.
        virtual const std::vector<unsigned int>& get_indices() const = 0;

        /// @brief Retrieves the mesh vertex buffer.
        ///
        /// @return Reference to the vertex array.
        virtual const std::vector<Vertex>& get_vertices() const = 0;
    };
}


#endif // API__OBJECTS__I_MESH__HPP