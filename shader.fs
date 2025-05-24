#version 330 core
out vec4 FragColor;

in vec3 vecColor;

void main()
{
   FragColor = vec4(vecColor, 1.0f);
}

