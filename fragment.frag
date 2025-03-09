#version 330 core
 
in vec3 fragment_color;
in vec3 fragment_position;
in vec3 vertex_normal;
uniform vec3 light_position;
uniform vec3 camera_position;
 
out vec3 color_out;
 
void main(){
    vec3 ambient = vec3(1.0f,1.0f,1.0f);
 
    vec3 normal = normalize(vertex_normal);
    vec3 vertex_to_light = normalize(light_position - fragment_position);  
    vec3 diffuse = max(dot(normal, vertex_to_light), 0.0)*vec3(1.0f,1.0f,1.0f);
     
    vec3 camera_direction = normalize(camera_position - fragment_position);
    vec3 reflection_direction = reflect(-vertex_to_light, normal);  
    vec3 specular = pow(max(dot(camera_direction, reflection_direction), 0.0), 32)*vec3(1.0f,1.0f,1.0f); 
     
    color_out = (0.2f*ambient + 0.7f*diffuse + 0.3f*specular)*fragment_color;
}