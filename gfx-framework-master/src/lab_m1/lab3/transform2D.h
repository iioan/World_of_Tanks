#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        // TODO(student): Implement the translation matrix
        return glm::mat3(
                1, 0, 0,                        // coloana 1 in memorie 
                0, 1, 0,                        // coloana 2 in memorie 
                translateX, translateY, 1);     // coloana 3 in memorie 
    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        // TODO(student): Implement the scaling matrix
        return glm::mat3(
                scaleX, 0, 0,                   // coloana 1 in memorie
                0, scaleY, 0,                   // coloana 2 in memorie
                0, 0, 1);                       // coloana 3 in memorie
    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        // TODO(student): Implement the rotation matrix
        return glm::mat3(
                cos(radians), sin(radians), 0,  // coloana 1 in memorie
				-sin(radians), cos(radians), 0, // coloana 2 in memorie
				0, 0, 1);                       // coloana 3 in memorie        );
    }
}   // namespace transform2D
