#ifndef H_CORE_SHADER
#define H_CORE_SHADER

#if _MSC_VER > 1000
#pragma once
#pragma warnind( disable: 4251 ) // For disable warning of template-class in dll export.
#endif // _MSC_VER > 1000

#include "_gl_head.hpp"

#define SCREEN_SPACE_SHADER_VERT_SRC "\
#version 330 core\
layout(location = 0) in vec3 aPos;\
void main() {\
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\
}"\

namespace daydream {
namespace renderer {
	
	enum class D_API_EXPORT ShaderType {
		None = 0,
		Vertex = 1,
		Fragment = 2,
	};

	struct D_API_EXPORT ShaderProgramSource {
		std::string VertexSource{};
		std::string FragmentSource{};
	};

	const std::string&	D_API_EXPORT ParseOneShader(const std::string& FilePath);
	ShaderProgramSource D_API_EXPORT ParseShader(const std::string& FilePath);
	uint32_t			D_API_EXPORT CompileShader(unsigned int type, const std::string& source);
	uint32_t			D_API_EXPORT CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	class D_API_EXPORT Shader {
	public:
		Shader(const std::string &all_src);
		Shader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);
		~Shader();

		void	Bind() const;
		void    UnBind() const ;
		const   std::string& getName() const;

		void setInt(const std::string& name, int value)                             const;
		void setFloat(const std::string& name, float value)                         const;
		void setVec2(const std::string& name, const glm::vec2& value)               const;
		void setVec2(const std::string& name, float x, float y)                     const;
		void setVec3(const std::string& name, const glm::vec3& value)               const;
		void setVec3(const std::string& name, float x, float y, float z)            const;
		void setVec4(const std::string& name, const glm::vec4& value)               const;
		void setVec4(const std::string& name, float x, float y, float z, float w)   const;
		void setMat2(const std::string& name, const glm::mat2& mat)                 const;
		void setMat3(const std::string& name, const glm::mat3& mat)                 const;
		void setMat4(const std::string& name, const glm::mat4& mat)                 const;
		void setBool(const std::string& name, bool value)                           const;


		static std::shared_ptr<Shader> create(const std::string& all_src);
		static std::shared_ptr<Shader> create(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);

	private:
		uint32_t	m_idx = 0;

		std::string m_name;
	};


	class D_API_EXPORT ScreenSpaceShader :public Shader {
	public:
		ScreenSpaceShader(const std::string& name, const std::string& fragment_path);
	};

}
}

#endif // !H_CORE_SHADER
