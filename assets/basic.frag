#version 330 core
out vec4 FragColor;

in vec3 m_Color;
uniform float u_time;

void main() {
    FragColor = vec4(m_Color * sin(u_time), 1.0f);
}
