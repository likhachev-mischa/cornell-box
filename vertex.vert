#version 330 core
 
in vec3 vertex_position;
 
uniform mat4 mvp;
 
// Pass by variables
in vec3 color_input;
out vec3 fragment_color;
in vec3 vertex_normal_in;
out vec3 vertex_normal;
out vec3 fragment_position;
 
void main(){    
    gl_Position = mvp*vec4(vertex_position,1);
    fragment_color = color_input;
    fragment_position = vertex_position;
    vertex_normal = vertex_normal_in;
}