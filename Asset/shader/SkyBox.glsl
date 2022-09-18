##shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

uniform mat4 d_ViewProjection;
uniform mat4 d_Transform;

out vec2 TexCoord;

void main() {
  TexCoord = a_TexCoord;
  gl_Position = d_ViewProjection * d_Transform * vec4(a_Position, 1.0);
}

##shader fragment
#version 450 core

layout(location = 0) out vec4 FragColor;
in vec2 TexCoord;

void main() {
	FragColor = vec4(TexCoord.xy, 1.0, 1.0);
}