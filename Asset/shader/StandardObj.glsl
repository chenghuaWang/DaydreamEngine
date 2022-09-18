##shader vertex
#version 450 core

    layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

uniform mat4 d_ViewProjection;
uniform mat4 d_Transform;

// Below is for Fragment shader to use.
out vec2 TexCoord;
out vec3 WorldPos;
out vec3 Normal;
out vec3 Bitangent;

void main() {
  TexCoord = a_TexCoord;
  Normal = mat3(d_Transform) * a_Normal;
  Bitangent = mat3(d_Transform) * a_Bitangent;
  WorldPos = vec3(d_Transform * vec4(a_Position, 1.0));
  gl_Position = d_ViewProjection * vec4(WorldPos, 1.0);
}

##shader fragment
#version 450 core
#define SCALE 16
#define MAX_LIGHT_NUM 10

    /*
     * A standard shader for texture. That shader support Various Texture. Mostly focus on PBR.
     * I will try my best to avoid conditional branch in the shader.
     */

    layout(location = 0) out vec4 FragColor;

float PI = 3.14159265358;

in vec2 TexCoord;
in vec3 WorldPos;
in vec3 Normal;
in vec3 Bitangent;

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

struct Material {
  bool isMetallic;
  bool isNormalMap;
  bool isAoMap;
  sampler2D baseColorMap;
  sampler2D normalMap;
  sampler2D metallicMap;
  sampler2D roughnessMap;
  sampler2D aoMap;
};

uniform Light d_Light[MAX_LIGHT_NUM];
uniform DirLight d_Light_direct[MAX_LIGHT_NUM];
uniform PointLight d_Light_point[MAX_LIGHT_NUM];
uniform SpotLight d_Light_spot[MAX_LIGHT_NUM];

uniform int d_BasicNum;
uniform int d_DirLightNum;
uniform int d_PointLightNum;
uniform int d_SpotLightNum;

uniform Material d_Material;
uniform vec3 d_camPos;

// ********************************** PBR Impl ************************************
// 1. Normal transform to TBN Space.
vec3 getNormalFromMap() {
  if (d_Material.isNormalMap) {
    return Bitangent;
  } else {
    vec3 tangentNormal = texture(d_Material.normalMap, TexCoord).xyz * 2.0 - 1.0;

    vec3 Q1 = dFdx(WorldPos);
    vec3 Q2 = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoord);
    vec2 st2 = dFdy(TexCoord);

    vec3 N = normalize(Normal);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
  }
}

// 2. NDF(Normal Distribution Function) GGTXTR.
float DistributionGGX(vec3 N, vec3 H, float roughness) {
  float a = roughness * roughness;
  float a2 = a * a;
  float NdotH = max(dot(N, H), 0.0);
  float NdotH2 = NdotH * NdotH;

  float nom = a2;
  float denom = (NdotH2 * (a2 - 1.0) + 1.0);
  denom = PI * denom * denom;

  return nom / denom;
}

// 3. Geometry Function. G schlick GGX and smith.
float GeometrySchlickGGX(float NdotV, float roughness) {
  float r = (roughness + 1.0);
  float k = (r * r) / 8.0;

  float nom = NdotV;
  float denom = NdotV * (1.0 - k) + k;

  return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
  float NdotV = max(dot(N, V), 0.0);
  float NdotL = max(dot(N, L), 0.0);
  float ggx2 = GeometrySchlickGGX(NdotV, roughness);
  float ggx1 = GeometrySchlickGGX(NdotL, roughness);

  return ggx1 * ggx2;
}

// 4. Fresnel requation.
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
  return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main() {
  // Read Basci parameters from Textures.
  vec3 baseColor = pow(texture(d_Material.baseColorMap, TexCoord.xy).rgb, vec3(2.2));
  float metallic = texture(d_Material.metallicMap, TexCoord.xy).r;
  float roughness = texture(d_Material.roughnessMap, TexCoord.xy).r;
  float ao = 1.0;
  if (d_Material.isAoMap) { ao = texture(d_Material.aoMap, TexCoord.xy).r; }

  vec3 N = getNormalFromMap();
  vec3 V = normalize(d_camPos - WorldPos);

  vec3 F0 = vec3(0.04);
  if (d_Material.isMetallic) { F0 = mix(F0, baseColor, metallic); }

  // The reflection out
  vec3 Lo = vec3(0.0);

  // Render Basic Lights
  for (int i = 0; i < d_BasicNum; ++i) {
    // get Lights radience
    vec3 L = normalize(d_Light[i].Position - WorldPos);
    vec3 H = normalize(V + L);
    float distance = length(d_Light[i].Position - WorldPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = d_Light[i].Position * attenuation * d_Light[i].Intensity;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular = numerator / denominator;

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;

    kD *= 1.0 - metallic;

    float NdotL = max(dot(N, L), 0.0);

    Lo += (kD * baseColor / PI + specular) * radiance * NdotL;
  }

  // Render Direct Lights
  // Redner Point Lights
  // Render Spot Lights

  vec3 ambient = vec3(0.03) * baseColor * ao;

  vec3 color = ambient + Lo;

  // HDR tonemapping
  color = color / (color + vec3(1.0));
  // gamma correct
  color = pow(color, vec3(1.0 / 2.2));

  FragColor = vec4(color, 1.0);
}
