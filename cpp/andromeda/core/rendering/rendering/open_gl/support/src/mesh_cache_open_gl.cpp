#include "../include/mesh_cache_open_gl.hpp"
#include "../../../vertices/include/vertex_layouts.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
    MeshCacheOpenGL::MeshCacheOpenGL() = default;

    MeshCacheOpenGL::~MeshCacheOpenGL() = default;

    void MeshCacheOpenGL::sync(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const VertexLayout& default_layout
    )
    {
        std::unordered_set<int> obj_ids;
        obj_ids.reserve(objects.size());

        for (const auto& [scene_key, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            const int obj_id = obj->get_id();
            obj_ids.insert(obj_id);

            std::unordered_map<int, GpuMeshOpenGL>::iterator it = m_meshes.find(obj_id);
            if (it == m_meshes.end())
            {
                GpuMeshOpenGL gpu_mesh;
                gpu_mesh.create(obj->get_mesh(), default_layout);
                m_meshes.emplace(obj_id, std::move(gpu_mesh));
            }
        }

        for (std::unordered_map<int, GpuMeshOpenGL>::iterator it = m_meshes.begin(); it != m_meshes.end();)
        {
            if (obj_ids.find(it->first) == obj_ids.end())
            {
                it = m_meshes.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    const GpuMeshOpenGL* MeshCacheOpenGL::try_get(int object_id) const
    {
        std::unordered_map<int, GpuMeshOpenGL>::const_iterator it = m_meshes.find(object_id);
        if (it == m_meshes.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    void MeshCacheOpenGL::clear()
    {
        m_meshes.clear();
    }
}