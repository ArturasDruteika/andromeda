#ifndef API__OBJECTS__I_MESH__HPP
#define API__OBJECTS__I_MESH__HPP


#include "andromeda/space/vertices/vertex.hpp"
#include <vector>


namespace andromeda
{
	class IMesh
	{
	public:
		virtual ~IMesh() = default;
		
		virtual unsigned int get_index_count() const = 0;
		virtual unsigned int get_vertex_count() const = 0;
		virtual const std::vector<unsigned int>& get_indices() const = 0;
		virtual const std::vector<Vertex>& get_vertices() const = 0;
	};
}


#endif // API__OBJECTS__I_MESH__HPP