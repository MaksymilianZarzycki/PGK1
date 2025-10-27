#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "primitives.h"

class PrimitiveRenderer
{
public:
    void alDrawPoint(int x, int y, ALLEGRO_COLOR color);
    void alDrawLine(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, int thickness);
    void alDrawRectangle(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color);
    void alDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, ALLEGRO_COLOR color);
    void alDrawCircle(int cx, int cy, int r, ALLEGRO_COLOR color);
    void drawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color);
    void drawBrokenLine(std::vector<Point2D>& points, ALLEGRO_COLOR color);
};
