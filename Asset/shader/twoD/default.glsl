##shader vertex
#version 330 core

void main() {
    gl_Position = vec4(0.5, 0.5, 0.5, 1.0);
}

##shader fragment
#version 330 core

out vec4 FragColor;

void main() {
	FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}