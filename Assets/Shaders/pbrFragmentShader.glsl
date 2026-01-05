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

void main()
{
    vec3 albedo = texture(uTexture, vUV).rgb;
    vec3 N = normalize(vNormal);
    vec3 L = normalize(lightDir);      // directional light
    vec3 V = normalize(viewPos - vFragPos);
    vec3 H = normalize(L + V);

    // Diffuse
    float NdotL = max(dot(N, L), 0.0);
    vec3 diffuse = albedo * NdotL;

    // Specular
    float NdotH = max(dot(N, H), 0.0);
    float spec = pow(NdotH, smoothness * 128.0);
    vec3 specular = mix(vec3(0.04), albedo, metallic) * spec;

    vec3 color = (diffuse + specular) * lightColour * lightIntensity;

    FragColor = vec4(color, 1.0);
}
