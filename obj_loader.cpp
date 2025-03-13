#include "obj_loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

bool ObjLoader::loadObj(
    const std::string& path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec3>& out_normals,
    std::vector<glm::vec2>& out_uvs,
    std::vector<unsigned int>& out_indices
) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return false;
    }

    // Temporary storage for the data in the .obj file
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_uvs;
    
    // Temporary face indices
    std::vector<unsigned int> vertex_indices;
    std::vector<unsigned int> normal_indices;
    std::vector<unsigned int> uv_indices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            // Vertex position
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        else if (prefix == "vn") {
            // Vertex normal
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (prefix == "vt") {
            // Texture coordinate
            glm::vec2 uv;
            iss >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        }
        else if (prefix == "f") {
            // Face definition
            unsigned int v_idx[3], uv_idx[3], n_idx[3];
            char slash;
            
            // Parse face vertices, texture coordinates, and normals
            for (int i = 0; i < 3; i++) {
                // Handle "v/vt/vn" format
                if (line.find("//") == std::string::npos) {
                    // We have texture coordinates
                    iss >> v_idx[i] >> slash >> uv_idx[i] >> slash >> n_idx[i];
                    vertex_indices.push_back(v_idx[i] - 1); // OBJ indices start at 1
                    uv_indices.push_back(uv_idx[i] - 1);
                    normal_indices.push_back(n_idx[i] - 1);
                } 
                else {
                    // No texture coordinates, format "v//vn"
                    iss >> v_idx[i] >> slash >> slash >> n_idx[i];
                    vertex_indices.push_back(v_idx[i] - 1);
                    normal_indices.push_back(n_idx[i] - 1);
                }
            }
        }
    }

    // Process the parsed data to fill the output vectors
    for (size_t i = 0; i < vertex_indices.size(); i++) {
        out_indices.push_back(i); // Simple indexing for GL_TRIANGLES
        out_vertices.push_back(temp_vertices[vertex_indices[i]]);
        if (!temp_normals.empty() && i < normal_indices.size())
            out_normals.push_back(temp_normals[normal_indices[i]]);
        if (!temp_uvs.empty() && i < uv_indices.size())
            out_uvs.push_back(temp_uvs[uv_indices[i]]);
    }

    // Generate normals if none were provided
    if (out_normals.empty() && !out_vertices.empty()) {
        out_normals.resize(out_vertices.size());
        for (size_t i = 0; i < out_indices.size(); i += 3) {
            glm::vec3 v0 = out_vertices[out_indices[i]];
            glm::vec3 v1 = out_vertices[out_indices[i + 1]];
            glm::vec3 v2 = out_vertices[out_indices[i + 2]];
            
            glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
            
            out_normals[out_indices[i]] = normal;
            out_normals[out_indices[i + 1]] = normal;
            out_normals[out_indices[i + 2]] = normal;
        }
    }

    return true;
}