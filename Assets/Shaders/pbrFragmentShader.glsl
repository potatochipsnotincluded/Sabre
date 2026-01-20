#version 410 core

in vec2 vUV;
in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;

uniform sampler2D uTexture;

// Directional light
uniform vec3 lightDir;     // must be normalized: direction FROM fragment TO light
uniform vec3 lightColour;
uniform float lightIntensity;

// Material
uniform float metallic;    
uniform float smoothness;  

uniform vec3 viewPos;      // camera position

// Ambient intensity (can be adjusted)
uniform float ambientIntensity = 0.1;

// ---- Helper functions ----

// Schlick Fresnel approximation
vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// Normal Distribution Function (GGX/Trowbridge-Reitz)
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = 3.14159265 * denom * denom;

    return num / denom;
}

// Geometry (Smith's method, Schlick-GGX)
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r*r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

// ---- Main ----

void main()
{
    vec3 albedo = texture(uTexture, vUV).rgb;
    vec3 N = normalize(vNormal);
    vec3 V = normalize(viewPos - vFragPos);
    vec3 L = normalize(lightDir);
    vec3 H = normalize(V + L);

    float NdotL = max(dot(N, L), 0.0);
    float NdotV = max(dot(N, V), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    float VdotH = max(dot(V, H), 0.0);

    // ---- Cook-Torrance BRDF ----
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F = FresnelSchlick(VdotH, F0);
    float D = DistributionGGX(N, H, 1.0 - smoothness);  // roughness = 1 - smoothness
    float G = GeometrySmith(N, V, L, 1.0 - smoothness);

    vec3 numerator = D * G * F;
    float denominator = 4.0 * NdotV * NdotL + 0.001;
    vec3 specular = numerator / denominator;

    // ---- kS/kD for energy conservation ----
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    vec3 diffuse = kD * albedo / 3.14159265;

    // ---- Ambient (basic hack) ----
    vec3 ambient = albedo * ambientIntensity;

    vec3 color = ambient + (diffuse + specular) * lightColour * lightIntensity * NdotL;

    FragColor = vec4(color, 1.0);
}
