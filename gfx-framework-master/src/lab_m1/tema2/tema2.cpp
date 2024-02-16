#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "lab_m1/tema2/tema2.h"

using namespace std;
using namespace m1;

tema2::tema2()
{
}

tema2::~tema2()
{
}

void tema2::Init()
{
    gamePlay = 150.f;
    firstMove = true;
    FREEZE = false;
    playingTime = time(0);
    addMissile = time(0);

    score = 0;
    factor = 160;

    lastMouseX = 0;
    lastMouseY = 0;
    float x = 3.f;
    float y = 0.f;
    float z = 3.f;
    player = Player(x, y, z);
        
    // Colors collection for buildings
    buildingColors.push_back(glm::vec3(55 / 255.f, 63 / 255.f, 82 / 255.f));
    buildingColors.push_back(glm::vec3(123 / 255.f, 17 / 255.f, 31 / 255.f));
    buildingColors.push_back(glm::vec3(105 / 255.f, 41 / 255.f, 47 / 255.f));
    buildingColors.push_back(glm::vec3(0 / 255.f, 80 / 255.f, 137 / 255.f));
    buildingColors.push_back(glm::vec3(0 / 255.f, 75 / 255.f, 118 / 255.f));
    buildingColors.push_back(glm::vec3(52 / 255.f, 116 / 255.f, 130 / 255.f));
    buildingColors.push_back(glm::vec3(243 / 255.f, 113 / 255.f, 74 / 255.f));
    buildingColors.push_back(glm::vec3(0 / 255.f, 170 / 255.f, 201 / 255.f));
    buildingColors.push_back(glm::vec3(232 / 255.f, 196 / 255.f, 173 / 255.f));
    buildingColors.push_back(glm::vec3(126 / 255.f, 203 / 255.f, 220 / 255.f));
    GenerateBuildings();

    camera = new implemented::CameraTema2();
    cameraPosition = glm::vec3(x, y + 1.3f, z + 3.5f);
    camera->Set(cameraPosition, glm::vec3(x, y, z), glm::vec3(0, 1, 0));

    lightPosition = glm::vec3(0, 8, 0);

    noVillains = rand() % 3 + 5;
    villainsKilled = 0;
    GenerateVillains();

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("senile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "senile.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tema2"), "turela.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("quad");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "quad.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Shader* shader = new Shader("tun");
        shader->AddShader("src/lab_m1/tema2/shaders/tun/TunVertexShader.glsl", GL_VERTEX_SHADER);
        shader->AddShader("src/lab_m1/tema2/shaders/tun/TunFragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("corp");
        shader->AddShader("src/lab_m1/tema2/shaders/corp/CorpVertexShader.glsl", GL_VERTEX_SHADER);
        shader->AddShader("src/lab_m1/tema2/shaders/corp/CorpFragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("senile");
        shader->AddShader("src/lab_m1/tema2/shaders/senile/SenileVertexShader.glsl", GL_VERTEX_SHADER);
        shader->AddShader("src/lab_m1/tema2/shaders/senile/SenileFragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("turela");
        shader->AddShader("src/lab_m1/tema2/shaders/turela/TurelaVertexShader.glsl", GL_VERTEX_SHADER);
        shader->AddShader("src/lab_m1/tema2/shaders/turela/TurelaFragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("VertexColor");
        shader->AddShader("src/lab_m1/tema2/shaders/VertexColor/VertexColorVertexShader.glsl", GL_VERTEX_SHADER);
        shader->AddShader("src/lab_m1/tema2/shaders/VertexColor/VertexColorFragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Camera projection matrix + material properties + polygon mode
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    materialShininess = 30;
    materialKd = 0.5;
    materialKs = 0.5;
    polygonMode = GL_FILL;

    // Create the text renderer object
    glm::ivec2 resolution = window->GetResolution();
    textRendererSmall = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
    textRendererSmall->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 20);

    textRendererBig = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
    textRendererBig->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 50);
}


void tema2::GenerateBuildings()
{
    srand(time(NULL));
    // random number between 21 and 26
    int nrBuildings = rand() % 6 + 21;
    int i = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(-35.f, 35.f);
    while (i < nrBuildings)
    {
        float x = dis(gen);
        float y = 0;
        float z = dis(gen);
        uniform_real_distribution<float> dis2(3.f, 7.f);
        float sX = dis2(gen);
        float sY = dis2(gen) + 2.f;
        float sZ = dis2(gen);
        // halfSide = 0.5f from the initial cube
        float halfSide = 0.5f;
        float newHalfSideX = sX;
        float newHalfSideZ = sZ;
        // Check if the building collides with the tank
        float minX = x - newHalfSideX;
        float maxX = x + newHalfSideX;
        float minZ = z - newHalfSideZ;
        float maxZ = z + newHalfSideZ;
        if (player.tankCenter[0] + 2 >= minX && player.tankCenter[0] + 2 <= maxX && player.tankCenter[2] + 2 >= minZ &&
            player.tankCenter[2] + 2 <= maxZ)
        {
            continue;
        }
        // Generate a random color for the building + Add it to the vector
        int colorIndex = rand() % 5;
        glm::vec3 buildingColor = buildingColors[colorIndex];
        Building building = Building(x, y, z, sX, sY, sZ, buildingColor);
        buildings.push_back(building);
        i++;
    }
}


void tema2::GenerateVillains()
{
    srand(time(NULL));
    int i = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(-30.f, 30.f);
    while (i < noVillains)
    {
        float x = dis(gen);
        float y = 0;
        float z = dis(gen);
        uniform_real_distribution<float> dis2(3.f, 7.f);
        // Checks if the tank is inside a building
        bool ok = false;
        for (int j = 0; j < buildings.size(); j++)
        {
            if (buildings[j].isInside(x, y, z) || buildings[j].isInside(x + 2, y, z + 2) ||
                buildings[j].isInside(x + 2, y, z - 2) || buildings[j].isInside(x - 2, y, z + 2) ||
                buildings[j].isInside(x - 2, y, z - 2))
            {
                ok = true;
                break;
            }
        }
        // Checks if the tank is too close to the player or to another tank
        if (glm::distance(glm::vec3(x, y, z), player.tankCenter) < 5)
        {
            ok = true;
        }
        for (int k = i; k < villains.size(); k++)
        {
            if (glm::distance(glm::vec3(x, y, z), villains[k].tankCenter) < 1.5f)
            {
                ok = true;
                break;
            }
        }

        if (ok)
        {
            continue;
        }
        // Generate a random angle for the tank
        uniform_real_distribution<float> dis3(-180.f, 180.f);
        float tankAngle = dis3(gen);
        Villain villain = Villain(x, y, z, tankAngle);
        villains.push_back(villain);
        i++;
    }
}

/*
 * Pentru player, verifica daca se ciocneste cu o cladire; 
 * Procedeul este asemanator ca la ciocnirea dintre doua tancuri
 * De asemenea, verificam daca playerul nu iese din mapa
 */
void tema2::TankBuildingCollision(float factor)
{
    for (int i = 0; i < buildings.size(); i++)
    {
        float distanceBetweenCenters = glm::distance(player.tankCenter, buildings[i].center);
        float sumofRadius = player.radius + buildings[i].diagonal / 2;

        if (distanceBetweenCenters < sumofRadius)
        {
            float distanceToMove = (sumofRadius - distanceBetweenCenters);
            glm::vec3 direction = glm::normalize(player.tankCenter - buildings[i].center);
            glm::vec3 displacement = direction * distanceToMove;
            player.tankCenter = player.tankCenter + displacement;
        }
    }

    if (player.tankCenter[0] < -37.5f || player.tankCenter[0] > 37.5f || player.tankCenter[2] < -37.5f ||
        player.tankCenter[2] > 37.5f)
    {
        player.tankCenter = player.tankCenter - glm::vec3(factor * sin((-1) * (player.tankAngle)), 0,
            (-1) * factor * cos(player.tankAngle));
    }
}



void tema2::RenderPlayer()
{
    glm::mat4 bodyModelMatrix = glm::mat4(1);
    bodyModelMatrix = glm::translate(bodyModelMatrix, player.tankCenter);
    bodyModelMatrix = glm::rotate(bodyModelMatrix, player.tankAngle, glm::vec3(0, 1, 0));
    glm::mat4 turretModelMatrix = glm::mat4(1);
    turretModelMatrix = glm::translate(turretModelMatrix, player.tankCenter);
    turretModelMatrix = glm::rotate(turretModelMatrix, player.tankAngle + player.turretAngle, glm::vec3(0, 1, 0));

    RenderMesh(meshes["tun"], shaders["tun"], turretModelMatrix, glm::vec3(0), 0, player.lives, 5);
    RenderMesh(meshes["corp"], shaders["corp"], bodyModelMatrix, glm::vec3(0), 0, player.lives, 5);
    RenderMesh(meshes["senile"], shaders["senile"], bodyModelMatrix, glm::vec3(0), 0, player.lives, 5);
    RenderMesh(meshes["turela"], shaders["turela"], turretModelMatrix, glm::vec3(0), 0, player.lives, 5);
}

/*
 * Renderizeaza proiectilele lansate de player
 * Verifica daca proiectilul a lovit o cladire sau a iesit din mapa
 * Randam cladirile
 */
void tema2::RenderStuff()
{
    for (int i = 0; i < playerMissiles.size(); i++)
    {
        playerMissiles[i].Update();
        for (int j = 0; j < buildings.size(); j++)
        {
            if (buildings[j].isInside(playerMissiles[i].center[0], playerMissiles[i].center[1],
                playerMissiles[i].center[2]))
            {
                playerMissiles[i].expired = true;
            }
        }
        // check if the center is outside the map
        if (playerMissiles[i].center[0] < -37.5f || playerMissiles[i].center[0] > 37.5f ||
            playerMissiles[i].center[2] < -37.5f || playerMissiles[i].center[2] > 37.5f)
        {
            playerMissiles[i].expired = true;
        }
        if (playerMissiles[i].expired)
        {
            playerMissiles.erase(playerMissiles.begin() + i);
            i--;
            continue;
        }
        RenderMesh(meshes["sphere"], shaders["VertexColor"], playerMissiles[i].modelMatrix,
            glm::vec3(14 / 255.f, 22 / 255.f, 115 / 255.f));
    }

    for (int i = 0; i < buildings.size(); i++)
    {
        RenderMesh(meshes["box"], shaders["VertexColor"], buildings[i].modelMatrix, buildings[i].color);
    }
}


/*
 * Renderizeaza tancurile inamice
 * Daca nu s-a terminat jocul si tancul nu a fost distrus, il updateaza
 * Verifica daca tancul a lovit o cladire sau a iesit din mapa
 * Verifica daca tancul a lovit un alt tanc
 * Genereaza atacul catre player
 */
void tema2::RenderVillains(float deltaTime)
{
    for (int i = 0; i < villains.size(); i++)
    {
        if (!FREEZE)
        {
            if (villains[i].killed == false)
            {
                villains[i].UpdateVillain(deltaTime);
            }

            for (int j = 0; j < buildings.size(); j++)
            {
                float distanceBetweenCenters = glm::distance(villains[i].tankCenter, buildings[j].center);
                float sumofRadius = villains[i].radius + buildings[j].diagonal / 2;

                if (distanceBetweenCenters < sumofRadius)
                {
                    float distanceToMove = (sumofRadius - distanceBetweenCenters);
                    glm::vec3 direction = glm::normalize(villains[i].tankCenter - buildings[j].center);
                    glm::vec3 displacement = direction * distanceToMove;
                    villains[i].tankCenter = villains[i].tankCenter + displacement;
                }
            }

            float distanceToPlayer = glm::distance(villains[i].tankCenter, player.tankCenter);
            float radiusSum = villains[i].radius + player.radius;
            if (distanceToPlayer < radiusSum)
            {
                float distanceToMove = (radiusSum - distanceToPlayer);
                glm::vec3 direction = glm::normalize(villains[i].tankCenter - player.tankCenter);
                glm::vec3 displacement = direction * abs(distanceToMove);
                villains[i].tankCenter = villains[i].tankCenter + displacement * 0.5f;
                player.tankCenter = player.tankCenter - displacement * 0.5f;
            }

            for (int j = 0; j < villains.size(); j++)
            {
                if (j != i)
                {
                    float distanceBetweenCenters = glm::distance(villains[i].tankCenter, villains[j].tankCenter);
                    float radiusSum = villains[i].radius + villains[j].radius;

                    if (distanceBetweenCenters < radiusSum)
                    {
                        float distanceToMove = (radiusSum - distanceBetweenCenters);
                        glm::vec3 direction = glm::normalize(villains[i].tankCenter - villains[j].tankCenter);
                        glm::vec3 displacement = direction * abs(distanceToMove);
                        villains[i].tankCenter = villains[i].tankCenter + displacement * 0.5f;
                        villains[j].tankCenter = villains[j].tankCenter - displacement * 0.5f;
                    }
                }
            }
            if (villains[i].killed == false)
            {
                villains[i].GenerateAttackPlayer(player.tankCenter, 1.f);
            }
        }

        glm::mat4 bodyModelMatrix = glm::mat4(1);
        bodyModelMatrix = glm::translate(bodyModelMatrix, villains[i].tankCenter);
        bodyModelMatrix = glm::rotate(bodyModelMatrix, villains[i].tankAngle, glm::vec3(0, 1, 0));
        glm::mat4 turretModelMatrix = glm::mat4(1);
        turretModelMatrix = glm::translate(turretModelMatrix, villains[i].tankCenter);
        turretModelMatrix = glm::rotate(turretModelMatrix, villains[i].turretAngle, glm::vec3(0, 1, 0));

        RenderMesh(meshes["tun"], shaders["tun"], turretModelMatrix, glm::vec3(0), 1, villains[i].lives, 4);
        RenderMesh(meshes["corp"], shaders["corp"], bodyModelMatrix, glm::vec3(0), 1, villains[i].lives, 4);
        RenderMesh(meshes["senile"], shaders["senile"], bodyModelMatrix, glm::vec3(0), 1, villains[i].lives, 4);
        RenderMesh(meshes["turela"], shaders["turela"], turretModelMatrix, glm::vec3(0), 1, villains[i].lives, 4);
    }
}


void tema2::KillVillains()
{
    for (int i = 0; i < villains.size(); i++)
    {
        if (villains[i].killed == false)
        {
            for (int j = 0; j < playerMissiles.size(); j++)
            {
                if (villains[i].IsInside(playerMissiles[j].center))
                {
                    villains[i].lives--;
                    playerMissiles[j].expired = true;
                }
            }
            if (villains[i].lives == 0)
            {
                villains[i].killed = true;
                villainsKilled++;
                score += factor;
            }
        }
    }
}

/*
 * Renderizeaza proiectilele lansate de tancurile inamice
 */
void tema2::RenderVillainsMissiles(float deltaTime)
{
    for (int i = 0; i < villains.size(); i++)
    {
        if (villains[i].attack == true && villains[i].killed == false)
        {
            if (villains[i].GetMissile() == true)
            {
                glm::vec3 tunCoordinates = villains[i].tunCoordinates();
                Missile missile = Missile(tunCoordinates.x, tunCoordinates.y, tunCoordinates.z,
                    villains[i].turretAngle / 2, villains[i].turretAngle / 2);
                villainMissiles.push_back(missile);
            }
        }
    }

    for (int i = 0; i < villainMissiles.size(); i++)
    {
        villainMissiles[i].Update();
        for (int j = 0; j < buildings.size(); j++)
        {
            if (buildings[j].isInside(villainMissiles[i].center[0], villainMissiles[i].center[1],
                villainMissiles[i].center[2]))
            {
                villainMissiles[i].expired = true;
            }
        }
        // check if the center is outside the map
        if (villainMissiles[i].center[0] < -37.5f || villainMissiles[i].center[0] > 37.5f ||
            villainMissiles[i].center[2] < -37.5f || villainMissiles[i].center[2] > 37.5f)
        {
            villainMissiles[i].expired = true;
        }
        if (villainMissiles[i].expired)
        {
            villainMissiles.erase(villainMissiles.begin() + i);
            i--;
            continue;
        }
    }

    for (int i = 0; i < villainMissiles.size(); i++)
    {
        RenderMesh(meshes["sphere"], shaders["VertexColor"], villainMissiles[i].modelMatrix,
            glm::vec3(132 / 255.f, 38 / 255.f, 45 / 255.f));
    }
}

/*
 * Verifica daca playerul a fost lovit de un proiectil
 */
void tema2::KillPlayer()
{
    for (int i = 0; i < villainMissiles.size(); i++)
    {
        if (player.IsInside(villainMissiles[i].center))
        {
            player.lives -= 1;
            villainMissiles[i].expired = true;
        }
        if (villainMissiles[i].expired)
        {
            villainMissiles.erase(villainMissiles.begin() + i);
            i--;
        }
    }
}

void tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(134 / 255.f, 176 / 255.f, 255 / 255.f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void tema2::Update(float deltaTimeSeconds)
{
    camera->UpdateWithObject(player.tankCenter);
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }

    glm::mat4 planeModelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(1.5f));
    RenderMesh(meshes["plane"], shaders["VertexColor"], planeModelMatrix,
        glm::vec3(32 / 255.f, 94 / 255.f, 97 / 255.f));
    RenderPlayer();
    RenderStuff();
    RenderVillains(deltaTimeSeconds);

    time_t currentTime = time(0);
    int timeLeft = gamePlay - (currentTime - playingTime);
    if (timeLeft >= 0 && player.lives != 0 && villainsKilled < noVillains)
    {   // daca nu s-a terminat jocul, tankurile se misca + se fac atacurile
        KillVillains();
        RenderVillainsMissiles(deltaTimeSeconds);
        KillPlayer();

        if (timeLeft == 75 && factor == 160)
        {
            // daca au ramas 75 de secunde, factorul de multiplicare se injumatateste
            factor /= 2;
        }

        int minutesLeft = timeLeft / 60;
        int secondsLeft = timeLeft % 60;

        string minutes2String = to_string(minutesLeft);
        string secs2String = to_string(secondsLeft);
        string res = minutes2String + " : " + secs2String;
        textRendererSmall->RenderText(res, 600.f, 5.f, 1.0f, glm::vec3(1.0f));

        textRendererSmall->RenderText("Good luck!", 5.0f, 5.0f, 1.0f, glm::vec3(1.0f));
        textRendererSmall->RenderText("Tanks to destroy: ", 1040.0f, 5.0f, 1.0f, glm::vec3(1.0f));
        int number = noVillains - villainsKilled;
        string number2Print = to_string(number);
        textRendererSmall->RenderText(number2Print, 1250.f, 5.0f, 1.0f, glm::vec3(1.0f));
    }
    else
    {
        FREEZE = true;
        if (villainsKilled == noVillains || (timeLeft <= 0 && player.lives > 0))
        {
            textRendererBig->RenderText("FELICITARI! Scor: ", 320.0f, 500.0f, 1.0f, glm::vec3(1.0f));
            string score2String = to_string(score);
            textRendererBig->RenderText(score2String, 850.0f, 500.0f, 1.0f, glm::vec3(1.0f));
        }
        else
        {
            textRendererBig->RenderText("Ai pierdut! :(", 430.f, 500.0f, 1.0f, glm::vec3(1.0f));
        }
    }
}

void tema2::FrameEnd()
{
}

void tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color,
    const int& type, const int& HP, const int& maxHP)
{
    if (!mesh || !shader || !shader->program)
        return;
    // cout << HP;
    //  Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

    // TODO(student): Set eye position (camera position) uniform
    glm::vec3 eyePosition = camera->position;
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    GLint objectColorLoc = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(objectColorLoc, 1, glm::value_ptr(color));

    GLint tankType = glGetUniformLocation(shader->program, "tankType");
    glUniform1i(tankType, type);

    GLint HPloc = glGetUniformLocation(shader->program, "HP");
    glUniform1i(HPloc, HP);

    GLint maxHPloc = glGetUniformLocation(shader->program, "maxHP");
    glUniform1i(maxHPloc, maxHP);

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glm::mat4 projection = projectionMatrix;
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the object
    mesh->Render();
}

void tema2::OnInputUpdate(float deltaTime, int mods)
{
    float forwardSpeed = 2.5f * deltaTime;
    float rotateSpeed = 2 * deltaTime;
    if (window->KeyHold(GLFW_KEY_W) && !FREEZE)
    {
        // change the center coordinates of the tank
        player.tankCenter = player.tankCenter +
            forwardSpeed * glm::vec3(sin((-1) * (player.tankAngle)), 0, (-1) * cos(player.tankAngle));

        TankBuildingCollision(0.1f);
    }
    if (window->KeyHold(GLFW_KEY_S) && !FREEZE)
    {
        player.tankCenter = player.tankCenter -
            forwardSpeed * glm::vec3(sin((-1) * (player.tankAngle)), 0, (-1) * cos(player.tankAngle));
        TankBuildingCollision(-0.1f);
    }
    if (window->KeyHold(GLFW_KEY_A))
    {
        camera->RotateThirdPerson_OY(forwardSpeed);
        player.tankAngle += forwardSpeed;
    }
    if (window->KeyHold(GLFW_KEY_D))
    {
        camera->RotateThirdPerson_OY(-forwardSpeed);
        player.tankAngle -= forwardSpeed;
    }

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_Q))
        {
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E))
        {
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }
    }
}

void tema2::OnKeyPress(int key, int mods)
{
}

void tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        int X = mouseX;
        if (firstMove)
        {
            lastMouseX = X;
            firstMove = false;
        }
        else
        {
            if (X > lastMouseX)
            {
                // RIGHT
                player.turretModelMatrix = glm::rotate(player.turretModelMatrix, -0.05f, glm::vec3(0, 1, 0));
                player.turretAngle -= 0.03f;
                lastMouseX = X;
            }
            else if (X < lastMouseX)
            {
                // LEFT
                player.turretModelMatrix = glm::rotate(player.turretModelMatrix, 0.05f, glm::vec3(0, 1, 0));
                player.turretAngle += 0.03f;
                lastMouseX = X;
            }
        }
    }
}

void tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !FREEZE)
    {
        time_t currentTime = time(0);
        if (currentTime - addMissile >= 1)
        {
            addMissile = currentTime;
        }
        else
        {
            return;
        }
        glm::vec3 tunCoordinates = player.tunCoordinates();
        Missile missile =
            Missile(tunCoordinates.x, tunCoordinates.y, tunCoordinates.z, player.turretAngle, player.tankAngle);
        playerMissiles.push_back(missile);
    }
}

void tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void tema2::OnWindowResize(int width, int height)
{
}
