#version 330 core

// this comes from vert shader
in struct Vertex
{
    vec4 normal;
    vec4 color;
} vertex;

out vec4 outColor;



void main()
{
    outColor = vertex.color;
}
