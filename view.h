#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "model.h"
#include "camera.h"

GLuint LoadShader(const std::string& shader_file_name, GLenum shader_type);
void CheckLinkStatus(GLuint& shader_program);

class View {
private:
    GLuint light_position_uniform_attribute;
    GLuint camera_position_uniform_attribute;

    GLuint mvp_uniform_attribute;
    GLuint triangle_settings;
    GLuint triangle_buffer;
    GLuint color_buffer;
    GLuint shader_program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint element_buffer;

    Model& model;
public:
    glm::vec3 light_position = glm::vec3(250.0f, 250.0f, 250.0f);

    Camera& camera;
    View(Model& model, Camera& camera);
    void render(SDL_Window* window);
    ~View();
private:
    class SceneLoader {
    private:
        View& view;
        std::vector<float> model_data_vector;
        void loadModel(const Model& model);
        void setupBuffers();
    public:
        GLuint number_of_vertices_in_scene;
        GLuint vertex_array_object;
        GLuint vertex_buffer;
        GLuint element_buffer;
        SceneLoader(View& view);
    };
    SceneLoader* scene_loader; 
};

