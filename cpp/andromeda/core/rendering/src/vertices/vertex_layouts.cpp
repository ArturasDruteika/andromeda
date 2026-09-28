#include "../include/vertex_layouts.hpp"


namespace andromeda::rendering
{
    VertexLayout::VertexLayout()
        : m_attributes{}
        , m_stride_bytes{ 0 }
        , m_input_rate{ InputRate::PerVertex }
    {
    }

    VertexLayout::VertexLayout(
        const std::vector<VertexAttributeDesc>& attributes,
        InputRate input_rate
    )
        : m_attributes{ attributes }
        , m_stride_bytes{ 0 }
        , m_input_rate{ input_rate }
    {
        calculate_offsets_and_stride();
    }

    const std::vector<VertexAttributeDesc>& VertexLayout::get_attributes() const
    {
        return m_attributes;
    }

    std::size_t VertexLayout::get_stride_bytes() const
    {
        return m_stride_bytes;
    }

    InputRate VertexLayout::get_input_rate() const
    {
        return m_input_rate;
    }

    void VertexLayout::calculate_offsets_and_stride()
    {
        std::size_t offset = 0;

        for (VertexAttributeDesc& attr : m_attributes)
        {
            attr.offset_bytes = offset;
            offset +=
                static_cast<std::size_t>(attr.component_count)
                * component_type_size_bytes(attr.component_type);
        }

        m_stride_bytes = offset;
    }
}