#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!

}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;

    }




    {
        shape = 0;
        finalMesh = "box";
    }

    {
        positionPlay.x = 0;
        positionPlay.y = 0;
        positionPlay.z = 0;
    }

    polygonMode = GL_FILL;

    // Create the text renderer object
    glm::ivec2 resolution = window->GetResolution();
    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

    textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 18);


}


void Lab1::FrameStart()
{
    // variabile care trebuie actualizate in fiecare frame
}



void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer


    glClearColor(color.x, color.y, color.z, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);


    // render some text
    textRenderer->RenderText("Hello, world!", 5.0f, 5.0f, 1.0f, glm::vec3(1.0f));
  

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    if (window->KeyHold(GLFW_KEY_A)) {
        positionPlay.x -= 1 * deltaTime;
    }
    
    if (window->KeyHold(GLFW_KEY_D)) {
        positionPlay.x += 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_W)) {
        positionPlay.z -= 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        positionPlay.z += 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        positionPlay.y += 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        positionPlay.y -= 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_R)) {
        positionPlay.y -= 1 * deltaTime;
    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.
        color.x = 0.5f;
        color.y = 0.2f;
        color.z = 0.1;
    }

    if (key == GLFW_KEY_C) {
        if (shape == 2) {
            shape = -1;
            finalMesh = "box";
        }
        if (shape == 0) {
            finalMesh = "sphere";
        }
        if (shape == 1) {
            finalMesh = "teapot";
        }
        shape++;
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
