#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include "lab_m1/tema2/lab_cameraTema2.h"
#include "lab_m1/tema2/classes/Player.h"
#include "lab_m1/tema2/classes/Missile.h"
#include "lab_m1/tema2/classes/Building.h"
#include "lab_m1/tema2/classes/Villain.h"


namespace m1
{
    class tema2 : public gfxc::SimpleScene
    {
    public:
        tema2();
        ~tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1, 1, 1), const int& type = 0, const int& HP = -1, const int& maxHP = -1);
        void tema2::RenderPlayer();
        void tema2::RenderStuff();
        void tema2::GenerateBuildings(); 
        void tema2::TankBuildingCollision(float factor);
        void tema2::GenerateVillains();
        void tema2::RenderVillains(float deltaTime);
        void tema2::VillainBuildingCollision(Villain villain);
        void tema2::HandleCollisionsTanks();
        void tema2::KillVillains();
        void tema2::RenderVillainsMissiles(float deltaTime);
        void tema2::KillPlayer();


        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::CameraTema2* camera;
        glm::mat4 projectionMatrix;

        glm::vec3 cameraPosition; 
        glm::vec3 lightPosition;

        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        bool firstMove;
        int lastMouseX;
        int lastMouseY;
        Player player;
        std::vector <Missile> playerMissiles;
        std::vector <Missile> villainMissiles;

        time_t addMissile;
        time_t playingTime; 
        int score;
        int factor;
        bool FREEZE;

        std::vector <Building> buildings;
        std::vector <glm::vec3> buildingColors;

        int noVillains;
        std::vector <Villain> villains;
        int villainsKilled;
        float gamePlay;

        // The actual renderer object
        gfxc::TextRenderer* textRendererSmall;
        gfxc::TextRenderer* textRendererBig;

        // Draw primitives mode
        GLenum polygonMode;
    };
}   // namespace m1
