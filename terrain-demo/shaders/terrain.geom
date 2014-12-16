#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(triangles) in;
layout(line_strip, max_vertices=8) out;


// this comes from vert shader
in struct Vertex
{
    vec4 normal;
} vertex[];



//
//
//
void main()
{
    int i;
    float normal_length = 0.2;
    
    //
    // draw original triangles mesh
    //
    for (i = 0; i < gl_in.length(); i++)
    {
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
    
    //
    // draw 3 vertex normals
    //
    for (i = 0; i < gl_in.length(); i++)
    {
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[i].gl_Position;
        EmitVertex();
        
        vec4 P = gl_in[i].gl_Position;
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(gl_in[i].gl_Position.xyz + vertex[i].normal.xyz * normal_length, 1.0);
        EmitVertex();
        
        EndPrimitive();
    }
    
    //
    // draw face normal
    //
    vec3 P0 = gl_in[0].gl_Position.xyz;
    vec3 P1 = gl_in[1].gl_Position.xyz;
    vec3 P2 = gl_in[2].gl_Position.xyz;
    
    vec3 V0 = P0 - P1;
    vec3 V1 = P2 - P1;
    
    vec3 N = cross(V1, V0);
    N = normalize(N);
    
    // Center of the triangle
    vec3 P = (P0 + P1 + P2) / 3.0;
    
    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(P, 1.0);
    EmitVertex();
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(P + N * normal_length, 1.0);
    EmitVertex();
    
    EndPrimitive();
    
}

