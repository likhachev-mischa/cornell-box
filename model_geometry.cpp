#include "model_geometry.h"

Rectangle::Rectangle(const std::vector<glm::vec3>& rectangle_corners, glm::vec3 RGB_color) :
    RGB_color(RGB_color), rectangle_corners(rectangle_corners){}
 
const glm::vec3& Rectangle::operator[](const size_t& index) const{
    return rectangle_corners[index];
}
 
Block::Block(const std::vector<Rectangle>& block_sides):block_sides(block_sides){}