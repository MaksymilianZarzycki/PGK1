#include "primitives.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "primitiveRenderer.h"

Point2D::Point2D()
{
    this->x = 0;
    this->y = 0;
}

Point2D::Point2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Point2D::draw(ALLEGRO_COLOR color)
{
    PrimitiveRenderer pRender;
    pRender.alDrawPoint(x, y, color);
}



LineSegment::LineSegment(Point2D a, Point2D b)
{
    this->a = a;
    this->b = b;
}

void LineSegment::draw(ALLEGRO_COLOR color)
{
    PrimitiveRenderer pRender;
    pRender.drawLine(a.x, a.y, b.x, b.y, color);
}