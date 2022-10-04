##shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 d_ViewProjection;
uniform mat4 d_Transform;

void main() {
  gl_Position = d_ViewProjection * d_Transform * vec4(a_Position, 1.0);
}

##shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

uniform vec3 d_Color;

void main() {
	FragColor = vec4(d_Color, 1.0);
}
