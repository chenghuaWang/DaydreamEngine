##shader vertex
#version 330 core

    layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 d_ViewProjection;
uniform mat4 d_Transform;

out vec2 TexCoord;

void main() {
  TexCoord = a_TexCoord;
  gl_Position = d_ViewProjection * d_Transform * vec4(a_Position, 1.0);
}

##shader fragment
#version 330 core
#define SCALE 16
    layout(location = 0) out vec4 FragColor;
in vec2 TexCoord;

void main() {
  vec2 uv = floor(SCALE * TexCoord.xy);
  vec4 color_tmp = vec4(vec3(mod(uv.x + uv.y, 2.)), 1);
  FragColor = 0.5 * color_tmp + 0.5 * vec4(0.6, 0.6, 0.6, 1.0);
}