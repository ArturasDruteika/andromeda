#ifndef RENDERING__VERTICES__VERTEX_LAYOUTS__HPP
#define RENDERING__VERTICES__VERTEX_LAYOUTS__HPP


#include "vertex_format.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
    enum class InputRate
    {
        PerVertex,
        PerInstance
    };

    struct VertexAttributeDesc
    {
        VertexSemantic semantic = VertexSemantic::Position;
        ComponentType component_type = ComponentType::Float32;
        uint32_t component_count = 0;
        bool normalized = false;

        std::size_t offset_bytes = 0;
    };

    class VertexLayout
    {
    public:
        VertexLayout();

        explicit VertexLayout(
            const std::vector<VertexAttributeDesc>& attributes,
            InputRate input_rate = InputRate::PerVertex
        );

        const std::vector<VertexAttributeDesc>& get_attributes() const;
        std::size_t get_stride_bytes() const;
        InputRate get_input_rate() const;

    private:
        void calculate_offsets_and_stride();

    private:
        std::vector<VertexAttributeDesc> m_attributes;
        std::size_t m_stride_bytes;
        InputRate m_input_rate;
    };
}

#endif // RENDERING__VERTICES__VERTEX_LAYOUTS__HPP