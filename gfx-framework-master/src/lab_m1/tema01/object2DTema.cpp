#include "object2DTema.h"

#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"


// Functia creaza un patrat (e functia din lab-ul 3)
Mesh* object2DTema::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


// Creeaza un romb
Mesh* object2DTema::CreateDiamond(
    const std::string& name,
    glm::vec3 center,
    float length,
    float z, // z coordinate of the star
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center, color), // centru
        VertexFormat(center + glm::vec3(-length / 4, 0, z), color), 
        VertexFormat(center + glm::vec3(length / 4, 0, z), color),
        VertexFormat(center + glm::vec3(0, length / 2, z), color),
        VertexFormat(center + glm::vec3(0, -length / 2, z), color),

        VertexFormat(center + glm::vec3(0, length / 8, z), color), // 5
        VertexFormat(center + glm::vec3(0, -length / 8, z), color), // 6
        VertexFormat(center + glm::vec3(length - length / 2, length / 8, z), color), // 7
        VertexFormat(center + glm::vec3(length - length / 2, -length / 8, z), color), // 8

    };
    Mesh* diamond = new Mesh(name);
    
        if (!fill) {
            diamond->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            std::vector<unsigned int> indices = { 1, 2, 3,  1, 2, 4,  5, 6, 7, 6 ,7, 8};
    
            diamond->InitFromData(vertices, indices);
        }
        return diamond;

}


/*
    Creaza un hexagon
    Ma folosesc de formula x = x0 + r * cos(angle) si y = y0 + r * sin(angle) 
    pentru a calcula coordonatele varfurilor hexagonului.
*/
Mesh* object2DTema::CreateHexagon(
    const std::string& name,
    glm::vec3 center, // Center point of the hexagon
    float radius, // Distance from the center to any of the hexagon's vertices
    glm::vec3 color,
    bool fill) {
    
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(center, color));
    // Creeaza varfurile hexagonului
    for (int i = 0; i <= 6; i++) {
		float angle = 2 * M_PI * i / 6 + M_PI / 4;
		float x = center.x + radius * cos(angle) / 2.5f;
		float y = center.y + radius * sin(angle) / 2.5f;
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0.2f), color));
	}

    glm::vec3 innerHexCenter = center;
    glm::vec3 innerHexColor = glm::vec3(0.5f, 0.5f, 0.5f);
    vertices.push_back(VertexFormat(innerHexCenter, innerHexColor));
    // Creeaza varfurile hexagonului interior
    for (int i = 0; i <= 6; i++) {
        float angle = 2 * M_PI * i / 6 + M_PI / 4;
        float x = center.x + radius * cos(angle) / 4;
        float y = center.y + radius * sin(angle) / 4;
        vertices.push_back(VertexFormat(glm::vec3(x, y, 1), innerHexColor));
    }

    Mesh* hexagon = new Mesh(name);

    if (!fill) {
		hexagon->SetDrawMode(GL_LINE_LOOP);
	}
    else {
        std::vector<unsigned int> indices = { 0, 1, 2,  0, 2, 3,  0, 3, 4,  0, 4, 5,  0, 5, 6,  0, 6, 7, 
                                              8, 9, 10,  8, 10, 11,  8, 11, 12,  8, 12, 13,  8, 13, 14,  8, 14, 15};

		hexagon->InitFromData(vertices, indices);
	}
	return hexagon;
}


/*
	Creeaza o stea
    Ma folosesc de formula x = x0 + r * cos(angle) si y = y0 + r * sin(angle) 
    pentru a calcula coordonatele varfurilor stelei.
    Unghiul dintre 2 puncte consecutive dintr-o stea este de 2 * PI / 5; 
    De asemenea, trebuie sa rotim steaua cu M_PI / 10 pentru a o pozitiona corect
 */
Mesh* object2DTema::CreateStar (
	const std::string& name,
	glm::vec3 center, // Center point of the star
	float radius, // Distance from the center to any of the star's vertices
    float z, // z coordinate of the star
	glm::vec3 color,
	bool fill) {

    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(center, color));

    for (int i = 0; i < 5; i++) {
        float angle = 2 * M_PI / 5 * i + M_PI / 10;
        float x = center.x + radius * cos(angle) / 2.5f;
        float y = center.y + radius * sin(angle) / 2.5f;
        vertices.push_back(VertexFormat(glm::vec3(x, y, z), color));
    }
    float innerRadius = radius * 38.2f / 100.0f;

    for (int i = 0; i <= 5; i++) {
		float angle = 2 * M_PI / 5 * i + M_PI / 5 + M_PI / 10;; 
		float x = center.x + innerRadius * cos(angle) / 2.5f;
		float y = center.y + innerRadius * sin(angle) / 2.5f;
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), color));
	}

    Mesh* star = new Mesh(name);

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        std::vector<unsigned int> indices = {3, 6, 5,  7, 1, 4,  8, 2, 10};
		star->InitFromData(vertices, indices);
    }
    return star;  
}   



