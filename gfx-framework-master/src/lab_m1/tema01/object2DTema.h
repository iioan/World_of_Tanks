#pragma once

#include <string>
#include <vector>


#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2DTema
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 center, float length, float z, glm::vec3 color, bool fill = false);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 radius, float length, float z, glm::vec3 color, bool fill = false);
}
