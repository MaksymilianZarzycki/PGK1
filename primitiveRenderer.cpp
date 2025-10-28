#include "primitiveRenderer.h"

#include <iostream>
#include <utility>
#include <cmath>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

void PrimitiveRenderer::alDrawPoint(int x, int y, ALLEGRO_COLOR color)
{
    al_draw_pixel(x, y, color);
}

void PrimitiveRenderer::alDrawLine(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, int thickness)
{
    al_draw_line(x1, y1, x2, y2, color, 1);
}

void PrimitiveRenderer::alDrawRectangle(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color)
{
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
}

void PrimitiveRenderer::alDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, ALLEGRO_COLOR color)
{
    al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, color);
}

void PrimitiveRenderer::alDrawCircle(int cx, int cy, int r, ALLEGRO_COLOR color)
{
    al_draw_filled_circle(cx, cy, r, color);
}

void PrimitiveRenderer::drawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color)
{
    float m = (y2 - y1) / (x2 - x1);

    if (abs(m) <= 1)
    {
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }


        float y = y1;
        for (int x = x1 + 1; x <= x2; x++)
        {
            al_draw_pixel(x, y, color);
            //y = m*(x-x1) + y1;
            y += m;
        }
    }
    else
    {
        if (y1 > y2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }


        float m = (x2 - x1) / (y2 - y1);
        float x = x1;
        for (int y = y1 + 1; y <= y2; y++)
        {
            al_draw_pixel(x, y, color);
            //x = m*(y-y1) + x1;
            x += m;
        }
    }
}

void PrimitiveRenderer::drawBrokenLine(std::vector<Point2D>& points, ALLEGRO_COLOR color)
{
    /*if(points.size()<2)
    {
        std::cout<<"drawBrokenLine: Not enough points"<<std::endl;
        return;
    }*/

    LineSegment segment(points[0], points[1]);
    for (int i = 0; i < points.size() - 1; i++)
    {
        segment.a = points[i];
        segment.b = points[i + 1];
        segment.draw(color);
    }
}

void PrimitiveRenderer::drawCircle(float x, float y, float r, ALLEGRO_COLOR color)
{
 
    float step = 1.0 / r;
    for (float i = 0; i < 3.14/4; i+=step)
    {
        int xn = r * cos(i) +0.5;
        int yn = r * sin(i) +0.5;

        al_draw_pixel(x+xn, y+yn, color);
        al_draw_pixel(x+xn, y-yn, color);
        al_draw_pixel(x-xn, y-yn, color);
        al_draw_pixel(x-xn, y+yn, color);

        al_draw_pixel(x + yn, y + xn, color);
        al_draw_pixel(x + yn, y - xn, color);
        al_draw_pixel(x - yn, y - xn, color);
        al_draw_pixel(x - yn, y + xn, color);
    }
}

void PrimitiveRenderer::drawEllipse(float x, float y, float rx, float ry, ALLEGRO_COLOR color)
{

    float step = 1.0 / (ry+rx)/2;
    for (float i = 0; i < 3.14/2; i += step)
    {
        int xn = rx * cos(i) + 0.5;
        int yn = ry * sin(i) + 0.5;

        al_draw_pixel(x + xn, y + yn, color);
        al_draw_pixel(x + xn, y - yn, color);
        al_draw_pixel(x - xn, y - yn, color);
        al_draw_pixel(x - xn, y + yn, color);
    }
}

void PrimitiveRenderer::drawPolygon(std::vector<Point2D>& points, ALLEGRO_COLOR color)
{
    /*if(points.size()<2)
    {
        std::cout<<"drawBrokenLine: Not enough points"<<std::endl;
        return;
    }*/

    LineSegment segment(points[0], points[1]);
    for (int i = 0; i < points.size() - 1; i++)
    {
        segment.a = points[i];
        segment.b = points[i + 1];
        segment.draw(color);
    }
    segment.a = points[0];
    segment.b = points[points.size() - 1];
    segment.draw(color);
}