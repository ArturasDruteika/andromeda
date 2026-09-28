#pragma once


#include "vertex_format.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
    /// @brief Specifies how vertex data is consumed during rendering.
    enum class InputRate
    {
        /// @brief Advance to the next element for every vertex.
        PerVertex,

        /// @brief Advance to the next element for every rendered instance.
        PerInstance
    };

    /// @brief Describes a single attribute within a vertex layout.
    ///
    /// Defines the semantic meaning, data format, and memory location of a
    /// vertex attribute.
    struct VertexAttributeDesc
    {
        /// @brief Semantic meaning of the attribute.
        VertexSemantic semantic = VertexSemantic::Position;

        /// @brief Underlying component data type.
        ComponentType component_type = ComponentType::Float32;

        /// @brief Number of components in the attribute.
        uint32_t component_count = 0;

        /// @brief Indicates whether integer values should be normalized.
        bool normalized = false;

        /// @brief Byte offset of the attribute within the vertex.
        std::size_t offset_bytes = 0;
    };

    /// @brief Describes the memory layout of vertex data.
    ///
    /// Stores a collection of vertex attributes together with the vertex stride
    /// and input rate used by the graphics pipeline.
    class VertexLayout
    {
    public:
        /// @brief Constructs an empty vertex layout.
        VertexLayout();

        /// @brief Constructs a vertex layout from a collection of attributes.
        ///
        /// @param attributes Vertex attribute descriptions.
        /// @param input_rate Vertex input rate.
        explicit VertexLayout(
            const std::vector<VertexAttributeDesc>& attributes,
            InputRate input_rate = InputRate::PerVertex
        );

        /// @brief Retrieves the vertex attribute descriptions.
        ///
        /// @return Collection of vertex attributes.
        const std::vector<VertexAttributeDesc>& get_attributes() const;

        /// @brief Retrieves the vertex stride.
        ///
        /// @return Size of a single vertex in bytes.
        std::size_t get_stride_bytes() const;

        /// @brief Retrieves the vertex input rate.
        ///
        /// @return Vertex input rate.
        InputRate get_input_rate() const;

    private:
        /// @brief Calculates attribute offsets and vertex stride.
        void calculate_offsets_and_stride();

    private:
        /// @brief Vertex attribute descriptions.
        std::vector<VertexAttributeDesc> m_attributes;

        /// @brief Size of a single vertex in bytes.
        std::size_t m_stride_bytes;

        /// @brief Vertex input rate.
        InputRate m_input_rate;
    };
}
