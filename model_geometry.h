#pragma once

#include <vector>
#include <glm/glm.hpp>
 
class Rectangle {
public:
    glm::vec3 RGB_color;
    std::vector<glm::vec3> rectangle_corners;
    Rectangle(const std::vector<glm::vec3>& rectangle_corners, glm::vec3 RGB_color);
    const glm::vec3& operator[](const size_t& index) const;
};
 
class Block{
public:
    std::vector<Rectangle> block_sides;
    Block(const std::vector<Rectangle>& block_sides);
};
