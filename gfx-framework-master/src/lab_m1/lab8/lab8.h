#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    class Lab8 : public gfxc::SimpleScene
    {
     public:
        Lab8();
        ~Lab8();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::vec3 lightPosition;
        glm::vec3 lightDirection;
        glm::vec3 secondLightPosition;
        glm::vec3 secondLightDirection;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        // TODO(student): If you need any other class variables, define them here.
        GLint ligthType;
        GLfloat angleOX, angleOY;
        GLfloat cutoffAngle;
        glm::vec3 point_light_pos[9];
        glm::vec3 point_light_color[9];
        glm::vec3 point_light_dir[9];

    };

}   // namespace m1
