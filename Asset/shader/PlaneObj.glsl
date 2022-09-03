/*!
 * @author	chenghua.wang
 * @brief This shader for plane Object only. This program should be hold
 * in Plane Object class. Shader manager should discare this part.
 */
##shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 d_ViewProjection;
uniform mat4 d_Transform;

void main() {
	gl_Position = d_ViewProjection * d_Transform * vec4(a_Position, 1.0);
}

##shader fragment
#version 330 core

/*!
 * The render part of rederence will using the most simple Bulin-Phong model.
 * The BRDF and Shadow mapping will coming soon.
 */

layout(location = 0) out vec4 FragColor;

void main() {
	FragColor = vec4(0.6)
}