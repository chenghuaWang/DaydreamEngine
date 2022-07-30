#ifndef H_DCORE_DS
#define H_DCORE_DS

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_gl_head.hpp"

namespace daydream {
namespace renderer {


	enum class D_API_EXPORT ElementType : uint8_t {
		None = 0,
		Int, Veci2, Veci3, Veci4,
		Float, Vecf2, Vecf3, Vecf4,
		Mat3, Mat4,
		Bool
	};

	///< return Bytes 
	uint32_t D_API_EXPORT ElementSize(const ElementType& rhs);
	uint32_t D_API_EXPORT ElementComponentsNum(const ElementType& rhs);


	struct D_API_EXPORT BufferLayoutElement {
		BufferLayoutElement(ElementType e, bool n) :
			Size(ElementSize(e)), Offset(0), Type(e), Normalized(n) {};
		uint32_t	Size;
		uint32_t	Offset;
		ElementType	Type;
		bool		Normalized;
	};


	class D_API_EXPORT BufferLayout {
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
			:m_Elements(elements) {
			CalculateOffsetAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }

		std::vector<BufferLayoutElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferLayoutElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferLayoutElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferLayoutElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferLayoutElement> m_Elements;
		uint32_t m_Stride = 0;
	};


	class D_API_EXPORT VertexBuffer {
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(float* v, uint32_t size);

		~VertexBuffer();

		void Bind();
		void UnBind();

		void setLayout(const BufferLayout& rhs);
		const BufferLayout& getLayout() const;

		static REF(VertexBuffer) create(uint32_t size);
		static REF(VertexBuffer) create(float* v, uint32_t size);

	private:
		uint32_t		m_idx = 0;
		BufferLayout	m_layout;
	};


	class D_API_EXPORT IndexBuffer {

	};


	class D_API_EXPORT FrameBuffer {
	public:
		FrameBuffer(float w, float h, float samples = 1, bool swapChain = false);
		~FrameBuffer();

		void Invalidate();
		void Bind();
		void UnBind();
		void Resize(float w, float h);

		uint32_t FrameIdx();

	private:
		float	m_w, m_h;
		float	m_sampels = 1;
		bool	m_swapChain = false;

		uint32_t	m_idx = 0;
		uint32_t	m_ColorAttach = 0;
		uint32_t	m_DepthAttach = 0;
	};

}
}


#endif // !H_DCORE_DS
