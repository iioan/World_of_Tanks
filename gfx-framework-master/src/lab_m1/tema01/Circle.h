// Circle.h
/*
    Clasa este folosita pentru a retine informatii despre stelele din joc.
*/

#pragma once
#include <string>

class Circle {
    public:
        Circle::Circle(float x, float y, int radius, std::string type);
        int Circle::isInside(int x, int y) const;
        void Circle::Update(float deltaTime);
        bool Circle::stillInside();
        std::string removeStar();
        std::string type; // tipul stelei
        float angularStep;
        float x; // pozitia centrului pe axa x
        float y; // pozitia centrului pe axa y
        int radius; // raza cercului
        int killed; // 0 daca nu a fost lovit, 1 daca a fost lovit
};