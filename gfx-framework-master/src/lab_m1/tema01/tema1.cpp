#include "lab_m1/tema01/tema1.h"

#include <vector>
#include <iostream>
#include <random>
#include <ctime>

#include "lab_m1/tema01/transform2D.h"
#include "lab_m1/tema01/object2DTema.h"

using namespace std;
using namespace m1;

#define X_MAX 1280 // rezolutia ecranului
#define Y_MAX 720 // rezolutia ecranului

tema1::tema1()
{
}


tema1::~tema1()
{
}


vector<Square> tema1::generateIntervalShopSquare(int length) {
    vector<Square> intervals;
    for (int i = 0, x = 50; i < 4; i++, x = x + 200) {
        int y = Y_MAX - 150;
        Square interval = Square(x, y, length, 0);
        intervals.push_back(interval);
    }
    return intervals;
}

vector<Square> tema1::generateIntervalGameSquare(int length) {
    vector<Square> intervals;
    for (int i = 0, y = 320; i < 3; i++, y -= 150) {
        for (int j = 0, x = 90; j < 3; j++, x += 150) {
            Square interval = Square(x, y, length, i + 1);
            intervals.push_back(interval);
        }
    }
    return intervals;
}

void tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    waitingTimeStars = 0; // timpul de asteptare pentru a adauga stele
    waitingTimeEnemy = 0; // timpul de asteptare pentru a adauga inamici
    timeAddStars = 1;

    timeAddEnemy = rand() % 3 + 4; // startul jocului se adauga un inamic la 4 - 6 secunde
    angularStep = 0;

    dragDiamond = -1;
    dragX = 0;
    dragY = 0;
    dragColor = "";

    firstLine = 380;
    secondLine = 230;
    thirdLine = 80;

    Mesh* outlinedSquare = object2DTema::CreateSquare("outlinedSquare", corner, squareSide, black, false);
    AddMeshToList(outlinedSquare);

    Mesh* orangeDiamond = object2DTema::CreateDiamond("orangeDiamond", corner, length, 2, orange, true);
    AddMeshToList(orangeDiamond);

    Mesh* blueDiamond = object2DTema::CreateDiamond("blueDiamond", corner, length, 2, blue, true);
    AddMeshToList(blueDiamond);

    Mesh* purpleDiamond = object2DTema::CreateDiamond("purpleDiamond", corner, length, 2, purple, true);
    AddMeshToList(purpleDiamond);

    Mesh* yellowDiamond = object2DTema::CreateDiamond("yellowDiamond", corner, length, 2, yellow, true);
    AddMeshToList(yellowDiamond);

    Mesh* priceStar = object2DTema::CreateStar("priceStar", corner, priceStarSide, 0, grey, true);
    AddMeshToList(priceStar);

    Mesh* redSquare = object2DTema::CreateSquare("redSquare", corner, LivesSide, red, true);
    AddMeshToList(redSquare);

    Mesh* gameSquare = object2DTema::CreateSquare("gameSquare", corner, squareSide, green, true);
    AddMeshToList(gameSquare);

    Mesh* pinkStar = object2DTema::CreateStar("pinkStar", corner, length, 5, pink, true);
    AddMeshToList(pinkStar);

    Mesh* orangeEnemy = object2DTema::CreateHexagon("orangeEnemy", corner, length, orange, true);
    AddMeshToList(orangeEnemy);

    Mesh* blueEnemy = object2DTema::CreateHexagon("blueEnemy", corner, length, blue, true);
    AddMeshToList(blueEnemy);

    Mesh* purpleEnemy = object2DTema::CreateHexagon("purpleEnemy", corner, length, purple, true);
    AddMeshToList(purpleEnemy);

    Mesh* yellowEnemy = object2DTema::CreateHexagon("yellowEnemy", corner, length, yellow, true);
    AddMeshToList(yellowEnemy);

    Mesh* orangeStar = object2DTema::CreateStar("orangeStar", corner, length, 10, orange, true);
    AddMeshToList(orangeStar);

    Mesh* blueStar = object2DTema::CreateStar("blueStar", corner, length, 10, blue, true);
    AddMeshToList(blueStar);

    Mesh* purpleStar = object2DTema::CreateStar("purpleStar", corner, length, 10, purple, true);
    AddMeshToList(purpleStar);

    Mesh* yellowStar = object2DTema::CreateStar("yellowStar", corner, length, 10, yellow, true);
    AddMeshToList(yellowStar);

    shopSquareInterval = generateIntervalShopSquare(squareSide);
    gameSquareInterval = generateIntervalGameSquare(squareSide);

}


void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(37 / 255.0f, 16 / 255.0f, 97 / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


// functie care returneaza numele stelei de atac
std::string tema1::getAttackStar(int color) {
    if (color == 0) {
        return "orangeStar";
    }
    if (color == 1) {
        return "blueStar";
    }
    if (color == 2) {
        return "purpleStar";
    }
    if (color == 3) {
        return "yellowStar";
    }
}


// functie ce randeaza elementele de pe scena
void tema1::InitScene(float deltaTimeSeconds) {
    // randare dreptunghi rosu
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(0.7f, 5.5f);
    modelMatrix *= transform2D::Translate(10, 2);
    RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);

    // randare patratelele din shop
    for (int i = 0; i < shopSquareInterval.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(shopSquareInterval[i].x, shopSquareInterval[i].y);
        RenderMesh2D(meshes["outlinedSquare"], shaders["VertexColor"], modelMatrix);
    }

    // randare romburi din shop
    for (int i = 0; i < shopSquareInterval.size(); i++) {
        modelMatrix = glm::mat3(1);
        int x = shopSquareInterval[i].x + shopSquareInterval[i].side / 2;
        int y = shopSquareInterval[i].y + shopSquareInterval[i].side / 2;
        modelMatrix *= transform2D::Translate(x, y);
        switch (i) {
        case 0:
            RenderMesh2D(meshes["orangeDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        case 1:
            RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        case 2:
            RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        case 3:
            RenderMesh2D(meshes["purpleDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        }
    }

    // randare stelute pentru preturile romburilor
    for (int i = 0, x = 60; i < 4; i++, x += 200) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, Y_MAX - 175);
        switch (i) {
        case 0:
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            break;
        case 1:
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(45, 0);
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            break;
        case 2:
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(45, 0);
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            break;
        case 3:
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(45, 0);
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(45, 0);
            RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
            break;
        }
    }

    // randare patratele pentru vieti
    for (int i = 0, x = 830; i < LIVES; i++, x += 120) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, Y_MAX - LivesSide - 50);
        RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);
    }

    // randare stelute pentru resurse (de cheltuit)
    for (int i = 0, x = 850; i < stars2Spend; i++, x += priceStarSide / 1.3f) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, Y_MAX - LivesSide - 80);
        RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
    }

    // randare patratele de joc + stelute pentru atac!
    for (int i = 0; i < gameSquareInterval.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(gameSquareInterval[i].x, gameSquareInterval[i].y);
        RenderMesh2D(meshes["gameSquare"], shaders["VertexColor"], modelMatrix);
        if (gameSquareInterval[i].free != 0 && gameSquareInterval[i].underAttack != -1) {
            gameSquareInterval[i].updateTime();
            if (gameSquareInterval[i].waitingTimeAttack >= 3) {
                gameSquareInterval[i].waitingTimeAttack = 0;
                int color = gameSquareInterval[i].underAttack;
                string star = getAttackStar(color);
                int y = gameSquareInterval[i].y + gameSquareInterval[i].side / 2;
                int x = gameSquareInterval[i].x + gameSquareInterval[i].side;
                Circle starAttack = Circle(x, y, length / 2.5f, star);
                attackStars.push_back(starAttack);
            }
        }
        if (gameSquareInterval[i].free == 0) {
            gameSquareInterval[i].underAttack != -1;
        }

    }

    // randare stelute de resurse
    for (int i = 0; i < stars.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(stars[i].x, stars[i].y);
        RenderMesh2D(meshes[stars[i].type], shaders["VertexColor"], modelMatrix);
    }

    // randare inamici
    for (int i = 0; i < enemies.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemies[i].x, enemies[i].y);
        modelMatrix *= transform2D::Scale(enemies[i].scaleX, enemies[i].scaleY);
        switch (enemies[i].color) {
        case 0:
            RenderMesh2D(meshes["orangeEnemy"], shaders["VertexColor"], modelMatrix);
            break;
        case 1:
            RenderMesh2D(meshes["blueEnemy"], shaders["VertexColor"], modelMatrix);
            break;
        case 2:
            RenderMesh2D(meshes["purpleEnemy"], shaders["VertexColor"], modelMatrix);
            break;
        case 3:
            RenderMesh2D(meshes["yellowEnemy"], shaders["VertexColor"], modelMatrix);
        }
        // enemy se misca doar pe X
        enemies[i].updateX(deltaTimeSeconds);
        // functie de minimizare a inamicului 
        enemies[i].Minimize(deltaTimeSeconds);

        // daca inamicul a ajuns la un patrat de joc, care are un romb 
        // atunci elimina rombul
        int x = enemies[i].x - enemies[i].length * 1.1f;
        int y = enemies[i].y;
        int index = getGameSquareIndex(x, y);
        if (index != -1 && gameSquareInterval[index].free != 0) {
            gameSquareInterval[index].underAttack = -1;
            gameSquareInterval[index].free = 0;
            int diamondIndex = findDiamondIndex(gameSquareInterval[index]);
            if (diamondIndex != -1)
            {
                diamonds[diamondIndex].scaleX = 0.98f;
                diamonds[diamondIndex].scaleY = 0.98f;
                gameSquareInterval[index].free = 0;
                gameSquareInterval[index].underAttack = -1;
            }
        }
    }

    // randare romb care este folosit pentru drag and drop
    if (dragDiamond == 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(dragX - length / 4, dragY);
        RenderMesh2D(meshes[dragColor], shaders["VertexColor"], modelMatrix);
    }

    // randare romburi pe patratele de joc
    for (int i = 0; i < diamonds.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(diamonds[i].x, diamonds[i].y);
        modelMatrix *= transform2D::Scale(diamonds[i].scaleX, diamonds[i].scaleY);
        RenderMesh2D(meshes[diamonds[i].color], shaders["VertexColor"], modelMatrix);
        diamonds[i].Minimize(deltaTimeSeconds);
        if (diamonds[i].scaleX <= 0.01f) {
            int squareIndex = diamonds[i].square;
            gameSquareInterval[squareIndex].free = 0;
            gameSquareInterval[squareIndex].underAttack = -1;
            diamonds.erase(diamonds.begin() + i);
       
        }
    }

    // randare stelute de atac
    for (int i = 0; i < attackStars.size(); i++) {
        // daca n-au luat contact cu inamicul, randeaza-le
        if (attackStars[i].killed == 0) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(attackStars[i].x, attackStars[i].y);
            modelMatrix *= transform2D::Rotate(attackStars[i].angularStep);
            RenderMesh2D(meshes[attackStars[i].type], shaders["VertexColor"], modelMatrix);
        }
        attackStars[i].Update(deltaTimeSeconds);
        // daca au iesit din scena, sterge-le
        if (attackStars[i].stillInside() == false) {
            attackStars.erase(attackStars.begin() + i);
        }
    }

}


// functie care genereaza stelute de resurse
void tema1::GenerateRecources(float deltaTimeSeconds) {

    time_t currentTime = std::time(nullptr);
    double deltaTime = difftime(currentTime, lastUpdateTimeStars);
    lastUpdateTimeStars = currentTime;
    waitingTimeStars += deltaTime;

    // adaug stelute de resurse la un interval de timp
    if (waitingTimeStars >= timeAddStars) {
        resourcesStars += 3;
        waitingTimeStars = 0;
        // intre 12 si 15 secunde adaug stele de resurse
        timeAddStars = rand() % 4 + 12;
        printf("Time for next stars: %d\n", timeAddStars);
        for (int i = 0; i < 3; i++) {
            int radius = length / 2.5f;
            // coordonate random intre RAZA si X_MAX
            int x = rand() % (X_MAX - radius) + radius;
            int y = rand() % (Y_MAX - radius) + radius;
            string type = "pinkStar";
            // adaug stelutele in vectorul de stelute
            Circle star = Circle(x, y, radius, type);
            stars.push_back(star);
        }
    }
}


// functie care genereaza inamici
void tema1::GenerateEnemies(float deltaTimeSeconds) {
    time_t currentTime = std::time(nullptr);
    double deltaTime = difftime(currentTime, lastUpdateTimeEnemy);
    lastUpdateTimeEnemy = currentTime;
    waitingTimeEnemy += deltaTime;
    // adaug inamici la un interval de timp
    if (waitingTimeEnemy >= timeAddEnemy) {
        waitingTimeEnemy = 0;
        // timp random intre 3 si 11 secunde
        timeAddEnemy = rand() % 8 + 3;
        // culoare (foarte) random
        int colorRand = rand() % 100000;
        colorRand = colorRand % 4;
        // linie random
        int lineRand = rand() % 3 + 1;
        // lungime random
        float lengthHex = length / 2.5f;
        // coordonata X la capatul ecranului
        float x = X_MAX + length / 2;
        float y;
        // coordonata Y in functie de linia random
        switch (lineRand) {
        case 1:
            y = firstLine;
            break;
        case 2:
            y = secondLine;
            break;
        case 3:
            y = thirdLine;
        }
        Enemy enemy = Enemy(x, y, lengthHex, colorRand, lineRand);
        // adaug inamicul in vectorul de inamici
        enemies.push_back(enemy);

        printf("Time to add the next enemy: %d seconds\n", timeAddEnemy);
    }
}


// functie care returneaza indexul inamicului care se afla pe aceeasi linie cu un romb
// ++ amandoi au aceeasi culoare
int tema1::getMatch(Diamond diamond) {
    int line = diamond.line;
    string color = diamond.removeDiamond();
    int match = 0;
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].line == line && enemies[i].getType() == color && diamond.x <= enemies[i].x) {
            return enemies[i].color;
        }
    }
    return -1;
}


// functie care genereaza atacul
void tema1::GenerateAttack(float deltaTime) {
    for (int i = 0; i < diamonds.size(); i++) {
        // pentru romb se verifica daca exista un inamic pe aceeasi linie
        int match = getMatch(diamonds[i]);
        if (match != -1) {
            // atunci ataca inamicul
            int squareIndex = diamonds[i].square;
            gameSquareInterval[squareIndex].underAttack = match;
        }
        else {
            // altfel nu ataca; se reseteaza patratul
            int squareIndex = diamonds[i].square;
            gameSquareInterval[squareIndex].underAttack = -1;
        }
    }

    for (int i = 0; i < attackStars.size(); i++) {
        string type = attackStars[i].removeStar();
        for (int j = 0; j < enemies.size(); j++) {
            // se verifica daca inamicul a fost lovit
            // se calculeaza suma razelor
            int radiusSum = attackStars[i].radius + enemies[j].length;
            glm::vec2 center1 = glm::vec2(attackStars[i].x, attackStars[i].y);
            glm::vec2 center2 = glm::vec2(enemies[j].x, enemies[j].y);
            // se calculeaza distanta dintre cele doua centre
            float distance = glm::distance(center1, center2);
            // daca distanta este mai mica decat suma razelor si sunt de ac. culoare
            if (distance <= radiusSum && type == enemies[j].getType()
                && attackStars[i].killed == 0 && enemies[j].scaleX == 1) {
                // steaua dispare
                attackStars[i].killed = 1;
                // inamicul pierde o viata
                if (enemies[j].lives > 0) {
                    enemies[j].lives--;
                }
                // daca inamicul a ramas fara vieti, dispare
                if (enemies[j].lives == 0 && enemies[j].scaleX == 1) {
                    enemies[j].scaleX = 0.98f;
                    enemies[j].scaleY = 0.98f;
                    enemies[j].killed = 1;
                }
            }
        }
    }
}


// daca inamicul a iesit din scena, pierzi o viata
void tema1::LoseLife() {
    for (int i = 0; i < enemies.size(); i++) {
        if (!enemies[i].stillInside()) {
            enemies.erase(enemies.begin() + i);
            LIVES--;
            printf("Ai pierdut o viata\n");
        }
    }
}


// elimina inamicii din vector, care au fost omorati
void tema1::RemoveEnemies() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].scaleX <= 0.01f) {
            enemies.erase(enemies.begin() + i);
        }
    }

    for (int i = 0; i < attackStars.size(); i++) {
        if (attackStars[i].killed == 1) {
			attackStars.erase(attackStars.begin() + i);
		}
    }
}


void tema1::Update(float deltaTimeSeconds)
{
    InitScene(deltaTimeSeconds);
    GenerateRecources(deltaTimeSeconds);
    GenerateEnemies(deltaTimeSeconds);
    GenerateAttack(deltaTimeSeconds);
    LoseLife();
    RemoveEnemies();
    if (LIVES == 0) {
        cout << "GAME OVER" << endl;
        exit(0);
    }
}


void tema1::FrameEnd()
{
}


void tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void tema1::OnKeyPress(int key, int mods)
{
}


void tema1::OnKeyRelease(int key, int mods)
{
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Daca drag-uim un romb, actualizam constant pozitia lui
    if (dragDiamond == 1) {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int X = mouseX;
        int Y = viewport[3] - mouseY;

        if (X > 0 && X < X_MAX && Y > 0 && Y < Y_MAX) {
            dragX = X;
            dragY = Y;
        }
    }
}


// functie care returneaza 1 daca am dat click pe o stea de resursa
int tema1::GetResources(int x, int y) {
    for (int i = 0; i < stars.size(); i++) {
        if (stars[i].isInside(x, y)) {
            stars.erase(stars.begin() + i);
            return 1;
        }
    }
    return 0;
}


// functie care returneaza indexul patratului din shop pe care am dat click
int tema1::getShopSquareIndex(int x, int y) {
    for (int i = 0; i < shopSquareInterval.size(); i++) {
        if (shopSquareInterval[i].isInside(x, y)) {
            return i;
        }
    }
    return -1;
}


// functie care returneaza indexul patratului de joc pe care am dat click
int tema1::getGameSquareIndex(int x, int y) {
    for (int i = 0; i < gameSquareInterval.size(); i++) {
        if (gameSquareInterval[i].isInside(x, y)) {
            return i;
        }
    }
    return -1;
}


// functie care returneaza indexul rombului de pe patratul de joc
int tema1::findDiamondIndex(Square gameSquare) {
    for (int i = 0; i < diamonds.size(); i++) {
        if (gameSquare.isInside(diamonds[i].x, diamonds[i].y)) {
            return i;
        }
    }
    return -1;
}

void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // daca am dat click pe butonul stanga
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int X = mouseX;
        int Y = viewport[3] - mouseY;

        unsigned char pixel[3];
        glReadPixels(X, Y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

        int index = getShopSquareIndex(X, Y);

        // extrag culoarea pixelului pe care am dat click
        glm::vec3 pickedColor = glm::vec3(pixel[0] / 255.0f, pixel[1] / 255.0f, pixel[2] / 255.0f);
        // daca e roz, atunci am dat click pe o stea de resursa
        if (pickedColor == pink) {
            if (GetResources(X, Y)) {
                stars2Spend++;
            }
        }
        // altfel, daca am dat click pe un patrat din shop si am destule stele de cheltuit, 
        // voi incepe procesul de drag and drop
        else if (index != -1) {
            // aici iau dupa caz
            dragX = X;
            dragY = Y;
            if (index == 0 && stars2Spend >= 1) {
                dragDiamond = 1;
                dragColor = "orangeDiamond";
            }
            if (index == 1 && stars2Spend >= 2) {
                dragDiamond = 1;
                dragColor = "blueDiamond";
            }
            if (index == 2 && stars2Spend >= 2) {
                dragDiamond = 1;
                dragColor = "yellowDiamond";
            }
            if (index == 3 && stars2Spend >= 3) {
                dragDiamond = 1;
                dragColor = "purpleDiamond";
            }
        }
    }
    // daca am dat click pe butonul dreapta
    else if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int X = mouseX;
        int Y = viewport[3] - mouseY;

        int index = getGameSquareIndex(X, Y);
        // daca am dat click pe un patrat de joc, care are un romb, atunci il elimin
        if (index != -1 && gameSquareInterval[index].free != 0) {
            gameSquareInterval[index].underAttack = -1;
            int diamondIndex = findDiamondIndex(gameSquareInterval[index]);
            if (diamondIndex != -1)
            {
                diamonds[diamondIndex].scaleX = 0.98f;
                diamonds[diamondIndex].scaleY = 0.98f;
                gameSquareInterval[index].free = 0;
                gameSquareInterval[index].underAttack = -1;
            }
        }
    }
}


// functie care returneaza pretul rombului
int tema1::colorPrice(string dragColor) {
    if (dragColor == "orangeDiamond") {
        return 1;
    }
    if (dragColor == "blueDiamond") {
        return 2;
    }
    if (dragColor == "yellowDiamond") {
        return 2;
    }
    if (dragColor == "purpleDiamond") {
        return 3;
    }
}


// functie care returneaza indexul culorii rombului
// care va fi folosit pentru a seta patratul de joc
int tema1::colorFree(string dragColor) {
    if (dragColor == "orangeDiamond") {
        return 1;
    }
    if (dragColor == "blueDiamond") {
        return 2;
    }
    if (dragColor == "yellowDiamond") {
        return 3;
    }
    if (dragColor == "purpleDiamond") {
        return 4;
    }
}

void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Dupa ce dam release la butonul stanga, vom cumpara rombul
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int X = mouseX;
        int Y = viewport[3] - mouseY;

        if (dragDiamond == 1) {
            // drag and drop-ul se termina
            dragDiamond = -1;
            // iau indexul patratului de joc pe care am dat release
            int index = getGameSquareIndex(X, Y);
            // daca am dat release pe un patrat de joc, care nu are romb, atunci il cumpar
            if (index != -1 && gameSquareInterval[index].free == 0) {
                int price = colorPrice(dragColor);
                int free = colorFree(dragColor);
                if (stars2Spend >= price) {
                    gameSquareInterval[index].free = free;
                    stars2Spend -= price;
                }
                // il adaug in vectorul de romburi
                int diamondX = gameSquareInterval[index].x + gameSquareInterval[index].side / 2;
                int diamondY = gameSquareInterval[index].y + gameSquareInterval[index].side / 2;
                int line = gameSquareInterval[index].line;
                Diamond diamond = Diamond(diamondX, diamondY, dragColor, line, index);
                diamonds.push_back(diamond);
            }
        }
    }
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema1::OnWindowResize(int width, int height)
{
}
