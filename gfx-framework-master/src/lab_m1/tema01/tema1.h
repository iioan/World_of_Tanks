#pragma once

#include "components/simple_scene.h"
#include "Circle.h"
#include "Square.h"
#include "Enemy.h"
#include "Diamond.h"
#include <vector>
#include <ctime>
#include <string>

namespace m1
{
    class tema1 : public gfxc::SimpleScene
    {
     public:
        tema1();
        ~tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void tema1::InitScene(float deltaTimeSeconds);
        void tema1::GenerateRecources(float deltaTimeSeconds);
        void tema1::LoseLife();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void tema1::GenerateAttack(float deltaTime);
        void tema1::RemoveEnemies();

        std::vector<Square> generateIntervalShopSquare(int length);
        std::vector<Square> generateIntervalGameSquare(int length);
        int tema1::GetResources(int x, int y);
        void tema1::GenerateEnemies(float deltaTimeSeconds);
        int tema1::getShopSquareIndex(int x, int y);
        int tema1::getGameSquareIndex(int x, int y);
        int tema1::colorPrice(std::string dragColor);
        int tema1::colorFree(std::string dragColor);
        int tema1::findDiamondIndex(Square gameSquare);
        int tema1::getMatch(Diamond diamond);
        std::string tema1::getAttackStar(int color);

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        int LIVES = 3;
        int stars2Spend = 5;

        // culorile pe care le folosesc
        glm::vec3 green = glm::vec3(59 / 255.0f, 227 / 255.0f, 107 / 255.0f);
        glm::vec3 orange = glm::vec3(252 / 255.0f, 94 / 255.0f, 3 / 255.0f);
        glm::vec3 red = glm::vec3(198 / 255.0f, 0 / 255.0f, 17 / 255.0f);
        glm::vec3 blue = glm::vec3(3 / 255.0f, 98 / 255.0f, 252 / 255.0f);
        glm::vec3 yellow = glm::vec3(255 / 255.0f, 230 / 255.0f, 3 / 255.0f);
        glm::vec3 purple = glm::vec3(83 / 255.0f, 43 / 255.0f, 90 / 255.0f);
        glm::vec3 grey = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 pink = glm::vec3(255 / 255.0f, 0 / 255.0f, 234 / 255.0f);
        glm::vec3 black = glm::vec3(0, 0, 0);

        glm::vec3 corner = glm::vec3(0, 0, 0);
        float squareSide = 120;
        float LivesSide = 80;
        float length = 100;
        float priceStarSide = 60;

        int resourcesStars = 0;
        float waitingTimeStars = 0;
        int timeAddStars;
            
        int firstLine;
        int secondLine;
        int thirdLine;

        int timeAddEnemy;
        float waitingTimeEnemy = 0;
        std::vector<Enemy> enemies;
        std::vector<Enemy> enemies1stLine;
        std::vector<Enemy> enemies2ndLine;
        std::vector<Enemy> enemies3rdLine;
        // la inamic se misca doar X-ul!!
        // se pierde punctul cand X-ul final devine mai mic decat lungimea

        std::vector<Square> gameSquareInterval; // vector pentru patratelele din joc
        std::vector<Square> shopSquareInterval; // vector pentru patratelele din shop
        std::vector<Circle> stars;
        std::vector<Circle> attackStars;

        int dragDiamond;
        float dragX;
        float dragY;
        std::string dragColor;

        std::vector<Diamond> diamonds;

        time_t lastUpdateTimeStars;
        time_t lastUpdateTimeEnemy;
    };
}   
