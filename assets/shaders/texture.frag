#version 330 core
out vec4 FragColor;

in vec2 m_TexCoord;
uniform float u_time;
uniform sampler2D u_texture;
uniform vec3 lightColor;

void main() {
    vec4 objectColor = texture(u_texture, m_TexCoord);
    FragColor = vec4(lightColor, 1.0f) * objectColor; 
}
