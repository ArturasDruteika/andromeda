#ifndef RENDERING__OPENGL__SUPPORT__MESH_CACHE_OPEN_GL__HPP
#define RENDERING__OPENGL__SUPPORT__MESH_CACHE_OPEN_GL__HPP


#include "../../geometry/include/gpu_mesh_open_gl.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
	class MeshCacheOpenGL
	{
	public:
		MeshCacheOpenGL();
		~MeshCacheOpenGL();

		MeshCacheOpenGL(const MeshCacheOpenGL& other) = delete;
		MeshCacheOpenGL& operator=(const MeshCacheOpenGL& other) = delete;
		MeshCacheOpenGL(MeshCacheOpenGL&& other) noexcept = delete;
		MeshCacheOpenGL& operator=(MeshCacheOpenGL&& other) noexcept = delete;

		void sync(
			const std::unordered_map<int, IGeometricObject*>& objects,
			const VertexLayout& default_layout
		);

		const GpuMeshOpenGL* try_get(int object_id) const;

		void clear();

	protected:
		std::unordered_map<int, GpuMeshOpenGL> m_meshes;
	};
}


#endif // RENDERING__OPENGL__SUPPORT__MESH_CACHE_OPEN_GL__HPP