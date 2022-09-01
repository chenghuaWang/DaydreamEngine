#include "ds.hpp"

namespace daydream {
namespace renderer {

static GLenum ShaderDataTypeToOpenGLBaseType(const ElementType& type) {
  switch (type) {
    case ElementType::Float:
    case ElementType::Vecf2:
    case ElementType::Vecf3:
    case ElementType::Vecf4:
    case ElementType::Mat3:
    case ElementType::Mat4: return GL_FLOAT;
    case ElementType::Int:
    case ElementType::Veci2:
    case ElementType::Veci3:
    case ElementType::Veci4: return GL_INT;
    case ElementType::Bool: return GL_BOOL;
  }
  return 0;
}

FrameBuffer::FrameBuffer(float w, float h, float samples, bool swapChain)
    : m_w(w), m_h(h), m_sampels(samples), m_swapChain(swapChain), m_idx(0) {
  Invalidate();
}

FrameBuffer::~FrameBuffer() {
  // Release memory from opengl state machine
  glDeleteFramebuffers(1, &m_idx);
  glDeleteTextures(1, &m_ColorAttach);
  glDeleteTextures(1, &m_DepthAttach);
}

void FrameBuffer::Invalidate() {
  // Delete current buffers if exists.
  if (m_idx) {
    glDeleteFramebuffers(1, &m_idx);
    glDeleteTextures(1, &m_ColorAttach);
    glDeleteTextures(1, &m_DepthAttach);
  }
  // For FrameBuffers.
  glCreateFramebuffers(1, &m_idx);
  glBindFramebuffer(GL_FRAMEBUFFER, m_idx);
  // Create Color Buffers
  glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttach);
  glBindTexture(GL_TEXTURE_2D, m_ColorAttach);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttach, 0);
  // Create Depth Buffers
  glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttach);
  glBindTexture(GL_TEXTURE_2D, m_DepthAttach);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_w, m_h);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttach,
                         0);
  // Unbind to 0.
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_idx);
  glViewport(0, 0, m_w, m_h);
}

void FrameBuffer::UnBind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void FrameBuffer::Resize(float w, float h) {
  m_w = w, m_h = h;
  Invalidate();
}

uint32_t FrameBuffer::FrameIdx() { return m_ColorAttach; }

REF(FrameBuffer) FrameBuffer::create(float w, float h) { return CREATE_REF(FrameBuffer)(w, h); }

uint32_t D_API_EXPORT ElementSize(const ElementType& rhs) {
  switch (rhs) {
    case ElementType::None: return 0;
    case ElementType::Float:
    case ElementType::Int: return 4;
    case ElementType::Vecf2:
    case ElementType::Veci2: return 8;
    case ElementType::Vecf3:
    case ElementType::Veci3: return 12;
    case ElementType::Vecf4:
    case ElementType::Veci4: return 16;
    case ElementType::Mat3: return 36;
    case ElementType::Mat4: return 64;
    case ElementType::Bool: return 1;
    default: return 0; break;
  }
  return 0;
}

uint32_t D_API_EXPORT ElementComponentsNum(const ElementType& rhs) {
  switch (rhs) {
    case ElementType::None: return 0;
    case ElementType::Float:
    case ElementType::Int: return 1;
    case ElementType::Vecf2:
    case ElementType::Veci2: return 2;
    case ElementType::Vecf3:
    case ElementType::Veci3: return 3;
    case ElementType::Vecf4:
    case ElementType::Veci4: return 4;
    case ElementType::Mat3: return 9;
    case ElementType::Mat4: return 16;
    case ElementType::Bool: return 1;
    default: return 0; break;
  }
  return 0;
}

VertexBuffer::VertexBuffer(uint32_t size) {
  glCreateBuffers(1, &m_idx);
  glBindBuffer(GL_ARRAY_BUFFER, m_idx);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* v, uint32_t size) {
  glCreateBuffers(1, &m_idx);
  glBindBuffer(GL_ARRAY_BUFFER, m_idx);
  glBufferData(GL_ARRAY_BUFFER, size, v, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_idx); }

void VertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_idx); }

void VertexBuffer::UnBind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::setLayout(const BufferLayout& rhs) { m_layout = rhs; }

const BufferLayout& VertexBuffer::getLayout() const { return m_layout; }

REF(VertexBuffer) VertexBuffer::create(uint32_t size) { return CREATE_REF(VertexBuffer)(size); }

REF(VertexBuffer) VertexBuffer::create(float* v, uint32_t size) {
  return CREATE_REF(VertexBuffer)(v, size);
}

IndexBuffer::IndexBuffer(uint32_t* indicies, uint32_t count) : m_count(count), m_idx(0) {
  glCreateBuffers(1, &m_idx);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idx);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(count), indicies, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_idx); }

void IndexBuffer::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idx); }

void IndexBuffer::UnBind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

REF(IndexBuffer) IndexBuffer::create(uint32_t* indicies, uint32_t count) {
  return CREATE_REF(IndexBuffer)(indicies, count);
}

VertexArray::VertexArray() { glCreateVertexArrays(1, &m_idx); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_idx); }

void VertexArray::Bind() const { glBindVertexArray(m_idx); }

void VertexArray::UnBind() const { glBindVertexArray(0); }

void VertexArray::addVertexBuffer(const REF(VertexBuffer) & vb) {
  glBindVertexArray(m_idx);
  vb->Bind();
  if (vb->getLayout().GetElements().size() == 0) {
    vb->UnBind();
    LOG_ERROR("The VerexBuffer don't have correct Layout!");
    return;
  }
  uint32_t _index = 0;
  for (const auto& element : vb->getLayout()) {
    glEnableVertexAttribArray(_index);
    glVertexAttribPointer(_index, ElementComponentsNum(element.Type),
                          ShaderDataTypeToOpenGLBaseType(element.Type),
                          element.Normalized ? GL_TRUE : GL_FALSE, vb->getLayout().GetStride(),
                          (const void*)(element.Offset));
    _index++;
  }
  m_VBO.push_back(vb);
}

void VertexArray::addIndexBuffer(const REF(IndexBuffer) & ib) {
  glBindVertexArray(m_idx);
  ib->Bind();
  m_IBO = ib;
}

}  // namespace renderer
}  // namespace daydream
