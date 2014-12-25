#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec4 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec4 lightPositionWorldspace;


// model space data
out struct VertexModelspace {
    vec4 normal;
    vec4 color;
} vertex;


// camera space data
out struct VertexCameraspace {
    vec4 position;
    vec4 normal;
    vec4 lightPosition;
} vertexCameraspace;




void main() {
    
    vec4 vertexPositionModelspace = vec4(vertexPosition, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexPositionModelspace;

    // model space
    vertex.normal = vec4(vertexNormal, 0.0);
    vertex.color = vertexColor;
    
    // camera space
    vertexCameraspace.position = viewMatrix * modelMatrix * vertexPositionModelspace;
    vertexCameraspace.normal = viewMatrix * modelMatrix * vertex.normal;
    vertexCameraspace.lightPosition = viewMatrix * lightPositionWorldspace;
}


