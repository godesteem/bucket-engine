#pragma once
#include "bepch.h"
#include "math/matrix.h"

namespace Engine {
  /**
   * uint8_t enum with different data types for Engine::Shader
   */
  enum class ShaderDataType: uint8_t {
    None = 0,
    Float, Float2, Float3, Float4,
    Int, Int2, Int3, Int4,
    Mat3, Mat4, Bool,
  };

  /**
   * Method to determine size of data type `type`
   * @param type shader data type
   * @return size of shader data type
   */
  static uint32_t ShaderDataTypeSize(ShaderDataType type){
    switch(type){
      case ShaderDataType::None: return 0;
      case ShaderDataType::Float: return 4;
      case ShaderDataType::Float2: return 2*4;
      case ShaderDataType::Float3: return 3*4;
      case ShaderDataType::Float4: return 4*4;
      case ShaderDataType::Mat3: return 3*3*4;
      case ShaderDataType::Mat4: return 4*4*4;
      case ShaderDataType::Int: return 4;
      case ShaderDataType::Int2: return 2*4;
      case ShaderDataType::Int3: return 3*4;
      case ShaderDataType::Int4: return 4*4;
      case ShaderDataType::Bool: return 1;
    }
    BE_CORE_ASSERT(false, "Unknown ShaderDataType");
    return 0;
  };

  /**
   * Describes a part of a buffer and keeps track of
   * it's position within the buffer data. It also
   * contains necessary information which will be later
   * used for rendering.
   */
  struct BufferElement {
    std::string Name = "";                      //! <Debugging name
    uint32_t Offset = 0;                        //! <Offset within the buffer data
    uint32_t Size = 0;                          //! <size per
    ShaderDataType Type = ShaderDataType::None;
    bool Normalized = false;                    //! < flag to determine weather the data is normalized or not
    size_t BufferIndex = 0;                     //! <index in VertexBuffer's list of buffers

    BufferElement() {};

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false, size_t index = 0)
      : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized), BufferIndex(index)
    {
    };

    /**
     * Getter for component count of buffer element.
     * @return number of components for the element
     */
    uint32_t GetComponentCount() const
    {
      switch(Type){
        case ShaderDataType::None:
          BE_CORE_ERROR("ShaderDataType::None");
          return 0;
        case ShaderDataType::Float: return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Mat3: return 3*3;
        case ShaderDataType::Mat4: return 4*4;
        case ShaderDataType::Int: return 1;
        case ShaderDataType::Int2: return 2;
        case ShaderDataType::Int3: return 3;
        case ShaderDataType::Int4: return 4;
        case ShaderDataType::Bool: return 1;
      };
      BE_CORE_ASSERT(false, "Unknown ShaderDataType.");
      return 0;
    }
  };

  /**
   * Layout of a buffer contains information about the elements
   * within a buffer
   */
  class BufferLayout
  {
    public:
      BufferLayout() {};
      BufferLayout(const std::initializer_list<BufferElement>& elements)
      : m_Elements(elements)
      {
        CalculateOffsetAndStride();
      }

      /**
       * Getter for elements within the layout.
       * @return layout elements
       */
      inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

      /**
       * Getter for stride
       * @return current stride
       */
      inline uint32_t GetStride() const { return m_Stride; };

      /**
       * iterator implementation, to allow iteration of layout elements
       */
      std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); };
      std::vector<BufferElement>::iterator end() { return m_Elements.end(); };
      std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); };
      std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); };

    private:
      /**
       * Calculates and sets offset values for each element,
       * also recalculates the total stride
       */
      void CalculateOffsetAndStride()
      {
        uint32_t offset = 0;
        m_Stride = 0;
        for(auto& element: m_Elements){
          element.Offset = offset;
          offset += element.Size;
          m_Stride += element.Size;
        }
      }
    private:
      std::vector<BufferElement> m_Elements;
      uint32_t m_Stride = 0;                  //! < distance between elements within the buffer
  };

  /**
   * An index buffer is a buffer which holds index pointers
   * to data in a VertexBuffer. Having a IndexBuffer allows you
   * to reuse, reorder and redefine objects using the same VertexBuffer
   */
  class IndexBuffer {
  public:
      virtual ~IndexBuffer() {};

      /**
       * Enable IndexBuffer
       */
      virtual void Bind() const = 0;

      /**
       * Disable IndexBuffer
       */
      virtual void Unbind() const = 0;

      /**
       * Size getter
       * @return buffer size
       */
      virtual uint32_t GetCount() const = 0;

      /**
       * Creates static IndexBuffer
       * @param indices array of indices
       * @param count size of array `indices`
       * @return static IndexBuffer object
       */
      static IndexBuffer* Create(uint32_t* indices, uint32_t count);

      /**
       * Creates static IndexBuffer
       * @param indices vector of indices
       * @param count size of array `indices`
       * @return static IndexBuffer object
       */
      static IndexBuffer* Create(std::vector<unsigned short> indices, uint32_t count);
  };

  /**
   * A buffer filled with vertex data
   *
   */
  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {};

    /**
     * Enables VertexBuffer
     */
    virtual void Bind() const = 0;

    /**
     * Enable part of a buffer
     * This is for splitted buffers only
     * see way1 of https://stackoverflow.com/a/39684775/6904543
     * and yet part of the OpenGL platform only implementation.
     * @param index
     */
    virtual void EnableBufferPart(size_t index) const = 0;

    /**
     * Disables VertexBuffer
     */
    virtual void Unbind() const = 0;

    /**
     * Attach layout to VertexBuffer
     * @param layout the layout of the stored data
     */
    virtual void SetLayout(const BufferLayout& layout) = 0;

    /**
     * Getter for attached `Engine::BufferLayout`
     * @return layout
     */
    virtual const BufferLayout& GetLayout() const = 0;

    /**
     * Create static VertexBuffer
     * @param vertices array of vertices
     * @param size size of array `vertices`
     * @return static VertexBuffer object
     */
    static VertexBuffer* Create(float* vertices, uint32_t size);
    static VertexBuffer* Create(const std::vector<Engine::Math::vec2> &vertices, uint32_t size);
    static VertexBuffer* Create(const std::vector<Engine::Math::vec3> &vertices, uint32_t size);
    static VertexBuffer* Create(const std::vector<Engine::Math::vec4> &vertices, uint32_t size);

    static VertexBuffer* Create(float* vertices, uint32_t verticeSize,
                                float* normals, uint32_t normalsSize,
                                float* textures, uint32_t texturesSize);

    static VertexBuffer* Create(const std::vector<Engine::Math::vec3> &vertices, uint32_t verticeSize,
                                const std::vector<Engine::Math::vec3> &normals, uint32_t normalsSize,
                                const std::vector<Engine::Math::vec2> &textures, uint32_t texturesSize);
  };

}
