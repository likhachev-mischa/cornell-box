#include <fstream>
#include <iostream>

#include "view.h"

GLuint LoadShader(const std::string& shader_file_name, GLenum shader_type)
{
	std::ifstream my_stream(shader_file_name);
	std::string contents = std::string((std::istreambuf_iterator<char>(my_stream)), std::istreambuf_iterator<char>());
	const GLchar* shader_code = contents.c_str();

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_code, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		std::cout << "shader compile error in: " << shader_file_name << std::endl;
		char buffer[512];
		glGetShaderInfoLog(shader, 512, nullptr, buffer);
		std::cout << buffer << std::endl;
	}
	return shader;
}

void CheckLinkStatus(GLuint& shader_program)
{
	GLint link_status;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE)
	{
		std::cout << "shader linker error in View constructor" << std::endl;
		char buffer[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, buffer);
		std::cout << buffer << std::endl;
	}
}

View::View(Model& model, Camera& camera) : model(model), camera(camera) {
    glEnable(GL_DEPTH_TEST);

    vertex_shader = LoadShader(std::string("./vertex.vert"), GL_VERTEX_SHADER);
    fragment_shader = LoadShader(std::string("./fragment.frag"), GL_FRAGMENT_SHADER);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);

    glBindFragDataLocation(shader_program, 0, "color_out");
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);
    CheckLinkStatus(shader_program);

    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(shader_program);

    mvp_uniform_attribute = glGetUniformLocation(shader_program, "mvp");
    light_position_uniform_attribute = glGetUniformLocation(shader_program, "light_position");
    camera_position_uniform_attribute = glGetUniformLocation(shader_program, "camera_position");

    scene_loader = new SceneLoader(*this);
}

void View::render(SDL_Window* window) {
    glClearColor(model.background_color[0],
        model.background_color[1], model.background_color[2], model.background_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.updateViewMatrix();
    glm::mat4 model_view_projection = camera.projection_matrix * camera.view_matrix;
    glUniformMatrix4fv(mvp_uniform_attribute, 1, GL_FALSE, &model_view_projection[0][0]);
    glUniform3fv(light_position_uniform_attribute, 1, &light_position[0]);
    glUniform3fv(camera_position_uniform_attribute, 1, &camera.position[0]);

    // Bind the VAO before drawing
    glBindVertexArray(scene_loader->vertex_array_object);
    
    // Draw using vertex indices with glDrawElements
    glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, 0);
    
    glFlush();
    SDL_GL_SwapWindow(window);
}

View::~View()
{
    delete scene_loader;
}

void View::SceneLoader::loadModel(const Model& model) {
    // For each vertex in the model
    for (size_t i = 0; i < model.vertices.size(); i++) {
        // Position (xyz)
        model_data_vector.push_back(model.vertices[i].x);
        model_data_vector.push_back(model.vertices[i].y);
        model_data_vector.push_back(model.vertices[i].z);
        
        // Color (rgb)
        model_data_vector.push_back(model.color.r);
        model_data_vector.push_back(model.color.g);
        model_data_vector.push_back(model.color.b);
        
        // Normal (xyz)
        if (i < model.normals.size()) {
            model_data_vector.push_back(model.normals[i].x);
            model_data_vector.push_back(model.normals[i].y);
            model_data_vector.push_back(model.normals[i].z);
        } else {
            // Default normal if not provided
            model_data_vector.push_back(0.0f);
            model_data_vector.push_back(1.0f);
            model_data_vector.push_back(0.0f);
        }
    }
}

void View::SceneLoader::setupBuffers() {
    // Generate a vertex array object
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
    
    // Create and fill the vertex buffer
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 
                 sizeof(float) * model_data_vector.size(), 
                 model_data_vector.data(), 
                 GL_STATIC_DRAW);
    
    // Create and fill the element buffer object (EBO)
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(unsigned int) * view.model.indices.size(),
                 view.model.indices.data(),
                 GL_STATIC_DRAW);
    
    // Set up vertex attribute pointers
    GLint vertex_position_attribute = glGetAttribLocation(view.shader_program, "vertex_position");
    glVertexAttribPointer(vertex_position_attribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
    glEnableVertexAttribArray(vertex_position_attribute);

    GLint color_input_attribute = glGetAttribLocation(view.shader_program, "color_input");
    glVertexAttribPointer(color_input_attribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(color_input_attribute);

    GLint vertex_normal_attribute = glGetAttribLocation(view.shader_program, "vertex_normal_in");
    glVertexAttribPointer(vertex_normal_attribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
        (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(vertex_normal_attribute);
}

View::SceneLoader::SceneLoader(View& view) :view(view) {
    loadModel(view.model);
    setupBuffers();
}
