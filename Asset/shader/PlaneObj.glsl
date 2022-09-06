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
#define MAX_LIGHT_NUM 10

    layout(location = 0) out vec4 FragColor;

struct Light {
  vec3 Color;
  vec3 Position;
  float Intensity;
};

struct DirLight {
  vec3 Color;
  vec3 Direction;
  float Intensity;
};

struct PointLight {
  vec3 Color;
  vec3 Position;
  float Constant;
  float Linear;
  float Quadratic;
  float Intensity;
};

struct SpotLight {
  vec3 Color;
  vec3 Position;
  vec3 Direction;
  float CutOff;
  float OutCutOff;
  float Intensity;
};

uniform Light d_Light[MAX_LIGHT_NUM];
uniform DirLight d_Light_direct[MAX_LIGHT_NUM];
uniform PointLight d_Light_point[MAX_LIGHT_NUM];
uniform SpotLight d_Light_spot[MAX_LIGHT_NUM];

uniform int BasicNum;
uniform int DirLightNum;
uniform int PointLightNum;
uniform int SpotLightNum;

in vec2 TexCoord;

void main() {
  vec2 uv = floor(SCALE * TexCoord.xy);
  vec4 color_tmp = vec4(vec3(mod(uv.x + uv.y, 2.)), 1);
  FragColor = 0.5 * color_tmp + 0.5 * vec4(0.6, 0.6, 0.6, 1.0);
}