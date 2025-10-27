#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#pragma once

class Point2D
{
    public:
        Point2D();
        Point2D(float x, float y);
        float x;
        float y;
        

        void draw(ALLEGRO_COLOR color);
};

class LineSegment
{
    public:
        LineSegment();
        LineSegment(Point2D a, Point2D b);
        Point2D a;
        Point2D b;

        void draw(ALLEGRO_COLOR color);
};
