#include<iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

char forme[] = {'C', 'L', 'R', 'T'};

// liste de couleur/=================================
//================ 0 =1
Color colors[] = {Color::Red, Color::Blue, Color::Yellow, Color::Green};

// declaration de Piece data
//=================================

struct Piece
{
    int couleur;
    char forme;

    CircleShape creat_circle(int x, int y = 300)
    {
        CircleShape *circle = new CircleShape(35.f);
        circle->setPosition(x, y);
        circle->setFillColor(colors[couleur - 1]);
        return *circle;
    }

    CircleShape creat_triangle(int x, int y = 300)
    {
        CircleShape *triangle = new CircleShape(45.5, 3);
        triangle->setFillColor(colors[couleur - 1]);
        triangle->setPosition(x, y);
        return *triangle;
    }

    RectangleShape creat_square(int x, int y = 300)
    {
        RectangleShape *square = new RectangleShape(Vector2f(70.f, 70.f));

        square->setPosition(x, y);

        square->setFillColor(colors[couleur - 1]);
        return *square;
    }

    RectangleShape creat_diamond(int x, int y = 300)
    {
        RectangleShape *diamond = new RectangleShape(Vector2f(56, 56));
        diamond->setRotation(45);
        diamond->setPosition(x + 50, y);
        diamond->setFillColor(colors[couleur - 1]);
        return *diamond;
    }
};
