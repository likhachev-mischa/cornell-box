#pragma once
#include <vector>
#include "model_geometry.h"

class Model {
public:
    std::vector<double> background_color;
    Rectangle scene_left_wall;
    Rectangle scene_right_wall;
    Rectangle scene_back_wall;
    Rectangle scene_floor;
    Rectangle scene_ceiling;
    Block short_block;
    Block tall_block;

    Model();
};

