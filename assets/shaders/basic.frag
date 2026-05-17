#version 330 core
out vec4 FragColor;

in vec2 m_TexCoord;
uniform float u_time;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main() {
    // FragColor = texture(u_texture, m_TexCoord); 
    FragColor = mix(texture(u_texture1, m_TexCoord), texture(u_texture2, m_TexCoord), sin(u_time));
}
