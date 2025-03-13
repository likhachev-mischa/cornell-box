#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

// Class for loading .obj model files
class ObjLoader {
public:
    // Load a model from a .obj file
    static bool loadObj(const std::string& path, 
                        std::vector<glm::vec3>& out_vertices,
                        std::vector<glm::vec3>& out_normals,
                        std::vector<glm::vec2>& out_uvs,
                        std::vector<unsigned int>& out_indices);
};