#pragma once
#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "model_geometry.h"

class Model {
public:
    // Model data
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texture_coords;
    std::vector<unsigned int> indices;
    glm::vec3 color;
    std::string name;

    // Background color (for scene settings)
    std::vector<double> background_color;

    // Default constructor
    Model();
    
    // Constructor with path to .obj file
    Model(const std::string& obj_path, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));
    
    // Load model from .obj file
    bool loadFromOBJ(const std::string& path);
};

