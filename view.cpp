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
	}
}

View::View(Model& model,Camera& camera) :model(model),camera(camera) {
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

    glDrawArrays(GL_TRIANGLES, 0, (*scene_loader).number_of_vertices_in_scene);

    glFlush();

    SDL_GL_SwapWindow(window);
}

View::~View()
{
    delete scene_loader;
}

void View::SceneLoader::loadAllRectangles(){
    loadRectangle(view.model.scene_floor);
    loadRectangle(view.model.scene_ceiling);
    loadRectangle(view.model.scene_back_wall);
    loadRectangle(view.model.scene_right_wall);
    loadRectangle(view.model.scene_left_wall);
    loadBlock(view.model.tall_block);
    loadBlock(view.model.short_block);
}

void View::SceneLoader::loadBlock(const Block& block){
    for (size_t i = 0; i < block.block_sides.size(); i++){
        loadRectangle(block.block_sides[i]);
    }
}

void View::SceneLoader::loadRectangle(const Rectangle& rectangle) {
    glm::vec3 rectangle_normal = glm::normalize(glm::cross(
        (rectangle[0] - rectangle[1]), rectangle[0] - rectangle[2]));
    loadRectangleVertex(0, rectangle, rectangle_normal);
    loadRectangleVertex(1, rectangle, rectangle_normal);
    loadRectangleVertex(2, rectangle, rectangle_normal);
    loadRectangleVertex(0, rectangle, rectangle_normal);
    loadRectangleVertex(2, rectangle, rectangle_normal);
    loadRectangleVertex(3, rectangle, rectangle_normal);
}

void View::SceneLoader::loadRectangleVertex(const int& vertex_number, const Rectangle& rectangle,
    const glm::vec3& vertex_normal) {
    for (size_t j = 0; j < 3; j++) {
        rectangle_data_vector.push_back(rectangle[vertex_number][j]);
    }
    for (size_t i = 0; i < 3; i++) {
        rectangle_data_vector.push_back(rectangle.RGB_color[i]);
    }
    for (size_t i = 0; i < 3; i++) {
        rectangle_data_vector.push_back(vertex_normal[i]);
    }
}
View::SceneLoader::SceneLoader(View& view) :view(view) {
    loadAllRectangles();
    float* rectangle_data_array = new float[rectangle_data_vector.size()];
    for (size_t i = 0; i < rectangle_data_vector.size(); i++){
        rectangle_data_array[i] = rectangle_data_vector[i];
    }
 
    number_of_vertices_in_scene = rectangle_data_vector.size() / 2; //half of the data is color data
 
    GLuint vertex_array_object;
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
     
    GLuint rectangle_buffer;
    glGenBuffers(1, &rectangle_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, rectangle_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*rectangle_data_vector.size(), rectangle_data_array, GL_STATIC_DRAW);
 
    delete[] rectangle_data_array;
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
