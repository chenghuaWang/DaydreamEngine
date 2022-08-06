#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>

namespace daydream {
namespace renderer {

	_obj_texture::_obj_texture(uint32_t w, uint32_t h, uint32_t c, COLOR_SPACE cs):
		m_w(w), m_h(h), m_c(c), m_type(cs) {
	}

	Texture2D::Texture2D(uint32_t w, uint32_t h):
		_obj_texture(w, h, 4, COLOR_SPACE::RGBA) {

		m_name = "No data";
		m_path = "default";

		GLenum internalFormat = GL_RGBA8;
		m_format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_idx);
		glTextureStorage2D(m_idx, 1, internalFormat, m_w, m_h);

		glTextureParameteri(m_idx, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_idx, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_idx, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_idx, GL_TEXTURE_WRAP_T, GL_REPEAT);

		m_hasImage = true;
	}

	Texture2D::Texture2D(const std::string& file_path, bool hdr) {
		m_path = file_path;
		stbi_set_flip_vertically_on_load(1);
		int w, h, c;
		GLenum internalFormat = GL_RGBA8;
		if (!hdr) {
			stbi_uc* data = stbi_load(m_path.c_str(), &w, &h, &c, 0);
			if (data == nullptr) {
				m_hasImage = false;
				LOG_ERROR("Failed when loading Texture. path=" + m_path);
				return;
			}
			m_hasImage = true;
			m_w = (uint32_t)w, m_h = (uint32_t)h, m_c = (uint32_t)c;
			switch (m_c) {
			case 1:
				m_type = COLOR_SPACE::RED;
				m_format = GL_RED;
				internalFormat = GL_RED;
				break;
			case 3:
				m_type = COLOR_SPACE::RGB;
				m_format = GL_RGB8;
				internalFormat = GL_RGB8;
				break;
			case 4:
				m_type = COLOR_SPACE::RGBA;
				m_format = GL_RGBA8;
				internalFormat = GL_RGBA8;
				break;
			default:
				m_type = COLOR_SPACE::None;
				m_format = 0;
				LOG_ERROR("When loading texture. Found channel is " + std::to_string(m_c) + ". can't handle.");
				break;
			}
			glGenTextures(1, &m_idx);
			glBindTexture(GL_TEXTURE_2D, m_idx);

			glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_w, m_h, 0, m_format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else {
			m_type = COLOR_SPACE::HDR;
			float* data = stbi_loadf(file_path.c_str(), &w, &h, &c, 0);
			if (data == nullptr) {
				m_hasImage = false;
				LOG_ERROR("Failed when loading Texture. path=" + m_path);
				return;
			}
			m_hasImage = true;
			m_w = (uint32_t)w, m_h = (uint32_t)h, m_c = (uint32_t)c;
			glGenTextures(1, &m_idx);
			glBindTexture(GL_TEXTURE_2D, m_idx);
			///< Note. Significant for load HDR.
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_w, m_h, 0, GL_RGB, GL_FLOAT, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_idx);
	}

	void Texture2D::Bind(uint32_t b) const {
		glBindTextureUnit(b, m_idx);
	}

	void Texture2D::UnBind(uint32_t b) const {
		glBindTextureUnit(b, 0);
	}

	void Texture2D::resetData(void* data, uint32_t size) {
		uint32_t channelNum = m_format == GL_RGBA ? 4 : 3;
		glTextureSubImage2D(m_idx, 0, 0, 0, m_w, m_h, m_format, GL_UNSIGNED_BYTE, data);
	}

	bool Texture2D::isEmpty() {
		return m_hasImage;
	}

	REF(Texture2D) Texture2D::create(uint32_t w, uint32_t h) {
		return CREATE_REF(Texture2D)(w, h);
	}

	REF(Texture2D) Texture2D::create(const std::string& file_path, bool hdr) {
		return CREATE_REF(Texture2D)(file_path, hdr);
	}



} //! namespace renderer
} //! namespace daydream
