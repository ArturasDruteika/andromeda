#ifndef RENDERING__OPENGL__SUPPORT__MESH_CACHE_OPEN_GL__HPP
#define RENDERING__OPENGL__SUPPORT__MESH_CACHE_OPEN_GL__HPP


#include "../../geometry/include/gpu_mesh_open_gl.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
	/// @brief Caches GPU meshes for geometric objects.
	///
	/// Maintains a mapping between scene object identifiers and their
	/// corresponding GPU mesh resources to avoid recreating GPU buffers
	/// unnecessarily.
	class MeshCacheOpenGL
	{
	public:
		/// @brief Constructs an empty mesh cache.
		MeshCacheOpenGL();

		/// @brief Destroys the mesh cache and its cached GPU resources.
		~MeshCacheOpenGL();

		MeshCacheOpenGL(const MeshCacheOpenGL& other) = delete;
		MeshCacheOpenGL& operator=(const MeshCacheOpenGL& other) = delete;
		MeshCacheOpenGL(MeshCacheOpenGL&& other) noexcept = delete;
		MeshCacheOpenGL& operator=(MeshCacheOpenGL&& other) noexcept = delete;

		/// @brief Synchronizes the cache with the current scene objects.
		///
		/// Creates GPU meshes for objects that are not yet cached and removes
		/// entries for objects that no longer exist.
		///
		/// @param objects Collection of scene objects indexed by object ID.
		/// @param default_layout Vertex layout used when creating GPU meshes.
		void sync(
			const std::unordered_map<int, IGeometricObject*>& objects,
			const VertexLayout& default_layout
		);

		/// @brief Retrieves a cached GPU mesh.
		///
		/// @param object_id Identifier of the scene object.
		/// @return Pointer to the cached GPU mesh, or `nullptr` if the object is
		/// not present in the cache.
		const GpuMeshOpenGL* try_get(int object_id) const;

		/// @brief Removes all cached GPU meshes.
		void clear();

	protected:
		/// @brief Cached GPU meshes indexed by scene object identifier.
		std::unordered_map<int, GpuMeshOpenGL> m_meshes;
	};
}


#endif // RENDERING__OPENGL__SUPPORT__MESH_CACHE_OPEN_GL__HPP