#include "model.h"
#include "obj_loader.h"
#include <iostream>

//Model::Model()// :
/*    background_color(std::vector<double>{0, 0, 0, 1}),
    scene_floor(Rectangle(std::vector<glm::vec3>{
    glm::vec3(552.8f, 0, 0), glm::vec3(0, 0, 0),
        glm::vec3(0, 0, 559.2f), glm::vec3(549.6f, 0, 559.2f)}, glm::vec3(1.0f, 1.0f, 1.0f))),
    scene_ceiling(Rectangle(std::vector<glm::vec3>{
    glm::vec3(556.0f, 548.8f, 0), glm::vec3(556.0f, 548.8f, 559.2f),
        glm::vec3(0, 548.8f, 559.2f), glm::vec3(0, 548.8f, 0)}, glm::vec3(1.0f, 1.0f, 1.0f))),
    scene_back_wall(Rectangle(std::vector<glm::vec3>{
    glm::vec3(549.6f, 0, 559.2f), glm::vec3(0, 0, 559.2f),
        glm::vec3(0, 548.8f, 559.2f), glm::vec3(556.0f, 548.8f, 559.2f)}, glm::vec3(1.0f, 1.0f, 1.0f))),
    scene_right_wall(Rectangle(std::vector<glm::vec3>{
    glm::vec3(0, 0, 559.2f), glm::vec3(0, 0, 0),
        glm::vec3(0, 548.8f, 0), glm::vec3(0, 548.8f, 559.2f)}, glm::vec3(0, 1.0f, 0))),
    scene_left_wall(Rectangle(std::vector<glm::vec3>{
    glm::vec3(552.8f, 0, 0), glm::vec3(549.6f, 0, 559.2f),
        glm::vec3(556.0f, 548.8f, 559.2f), glm::vec3(556.0f, 548.8f, 0)}, glm::vec3(1.0f, 0, 0))),
    short_block(Block(std::vector<Rectangle>{
    Rectangle(std::vector<glm::vec3>{
        glm::vec3(130.0f, 165.0f, 65.0f), glm::vec3(82.0f, 165.0f, 225.0f),
            glm::vec3(240.0f, 165.0f, 272.0f), glm::vec3(290.0f, 165.0f, 114.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(290.0f, 0, 114.0f), glm::vec3(290.0f, 165.0f, 114.0f),
            glm::vec3(240.0f, 165.0f, 272.0f), glm::vec3(240.0f, 0, 272.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(130.0f, 0, 65.0f), glm::vec3(130.0f, 165.0f, 65.0f),
            glm::vec3(290.0f, 165.0f, 114.0f), glm::vec3(290.0f, 0, 114.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(82.0f, 0, 225.0f), glm::vec3(82.0f, 165.0f, 225.0f),
            glm::vec3(130.0f, 165.0f, 65.0f), glm::vec3(130.0f, 0, 65.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(240.0f, 0, 272.0f), glm::vec3(240.0f, 165.0f, 272.0f),
            glm::vec3(82.0f, 165.0f, 225.0f), glm::vec3(82.0f, 0, 225.0f)}, glm::vec3(1.0f, 1.0f, 1.0f))
})),
tall_block(Block(std::vector<Rectangle>{
    Rectangle(std::vector<glm::vec3>{
        glm::vec3(423.0f, 330.0f, 247.0f), glm::vec3(265.0f, 330.0f, 296.0f),
            glm::vec3(314.0f, 330.0f, 456.0f), glm::vec3(472.0f, 330.0f, 406.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(423.0f, 0, 247.0f), glm::vec3(423.0f, 330.0f, 247.0f),
            glm::vec3(472.0f, 330.0f, 406.0f), glm::vec3(472.0f, 0, 406.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(472.0f, 0, 406.0f), glm::vec3(472.0f, 330.0f, 406.0f),
            glm::vec3(314.0f, 330.0f, 456.0f), glm::vec3(314.0f, 0, 456.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(314.0f, 0, 456.0f), glm::vec3(314.0f, 330.0f, 456.0f),
            glm::vec3(265.0f, 330.0f, 296.0f), glm::vec3(265.0f, 0, 296.0f)}, glm::vec3(1.0f, 1.0f, 1.0f)),
        Rectangle(std::vector<glm::vec3>{
        glm::vec3(265.0f, 0, 296.0f), glm::vec3(265.0f, 330.0f, 296.0f),
            glm::vec3(423.0f, 330.0f, 247.0f), glm::vec3(423.0f, 0, 247.0f)}, glm::vec3(1.0f, 1.0f, 1.0f))
//})) {
//}
*/
// Update the constructor to initialize material
Model::Model() : 
    background_color(std::vector<double>{0, 0, 0, 1}),
    color(1.0f, 1.0f, 1.0f),
    material(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Model::Model(const std::string& obj_path, const glm::vec3& color) :
    background_color(std::vector<double>{0, 0, 0, 1}),
    color(color),
    material(color)
{
    if (!loadFromOBJ(obj_path)) {
        std::cerr << "Failed to load model from: " << obj_path << std::endl;
    }
    
    // If we have a material path, try to load it
    if (!material_path.empty()) {
        loadMaterial(material_path);
    }
}

Model::Model(const std::string& obj_path, const std::string& material_path)
{
    if (!loadFromOBJ(obj_path)) {
        std::cerr << "Failed to load model from: " << obj_path << std::endl;
    }
    
    // If we have a material path, try to load it
    if (!material_path.empty()) {
        loadMaterial(material_path);
    }
}

bool Model::loadFromOBJ(const std::string& path) {
    bool success = ObjLoader::loadObj(
        path,
        vertices,
        normals,
        texture_coords,
        indices,
        material_path
    );
    
    if (success) {
        // Extract filename for model name
        size_t lastSlash = path.find_last_of("/\\");
        size_t lastDot = path.find_last_of(".");
        if (lastSlash == std::string::npos) lastSlash = 0;
        else lastSlash++;
        
        if (lastDot == std::string::npos || lastDot <= lastSlash) {
            name = path.substr(lastSlash);
        } else {
            name = path.substr(lastSlash, lastDot - lastSlash);
        }
        
        // If material path is defined, load it
        if (!material_path.empty()) {
            // Get the directory of the obj file
            std::string dir = "";
            if (lastSlash != std::string::npos) {
                dir = path.substr(0, lastSlash);
            }
            
            // Combine directory with material path
            loadMaterial(dir + material_path);
        }
    }
    
    return success;
}

bool Model::loadMaterial(const std::string& path) {
    return ObjLoader::loadMtl(path, material);
}

bool Model::hasTextureCoords() const {
    return !texture_coords.empty();
}

bool Model::hasTexture() const {
    return material.hasTexture();
}
