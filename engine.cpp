#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "primitiveRenderer.h"
#include "primitives.h"

class Engine
{

public:
    Engine(bool fullscreen = false, int width = 640, int heiht = 380, int fps = 60);
    ~Engine();
    void run();
private:
    bool stop;
    bool fullscreen;
    int width;
    int height;
    int fps;

    int mouseX, mouseY;
    bool mousePressed;

    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* fpsTimer;
    ALLEGRO_EVENT_QUEUE* event_queue;

    ALLEGRO_EVENT event;

    void init();
    void input();
    void update();
    void render();

    PrimitiveRenderer pRender;
};

Engine::Engine(bool fullscreen, int width, int height, int fps)
    :fullscreen(fullscreen), width(width), height(height), fps(fps), display(nullptr), fpsTimer(nullptr), event_queue(nullptr)
{
    init();
}

Engine::~Engine()
{
    if (fpsTimer)
        al_destroy_timer(fpsTimer);
    if (event_queue)
        al_destroy_event_queue(event_queue);
    if (display)
        al_destroy_display(display);
}

void Engine::init()
{
    if (!al_init())
    {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        exit(-1);
    }

    if (!al_install_keyboard() || !al_install_mouse())
    {
        std::cerr << "Failed to initialize Mouse/Keyboard!" << std::endl;
        exit(-1);
    }

    if (!al_init_primitives_addon())
    {
        std::cerr << "Failed to initialize Primitives!" << std::endl;
        exit(-1);
    }

    fpsTimer = al_create_timer(1.0 / fps);
    if (!fpsTimer) {
        std::cerr << "Failed to create timer!" << std::endl;
        exit(-1);
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        std::cerr << "Failed to create event_queue!" << std::endl;
        exit(-1);
    }

    al_set_new_display_flags(fullscreen ? ALLEGRO_FULLSCREEN : 0);
    display = al_create_display(width, height);
    if (!display) {
        std::cerr << "Failed to create display!" << std::endl;
        exit(-1);
    }

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(fpsTimer));
    al_start_timer(fpsTimer);
}

void Engine::input()
{
    switch (event.type)
    {
    case ALLEGRO_EVENT_MOUSE_AXES:
        mouseX = event.mouse.x;
        mouseY = event.mouse.y;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        if (event.keyboard.keycode = ALLEGRO_KEY_ESCAPE)
            stop = true;
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        stop = true;
        break;
    }
}

 // <------------------- REMEMBER TO DELETE LATER
void Engine::update()
{
    pRender.alDrawRectangle(20, 20, 100, 100, al_map_rgb(255, 255, 255));
    pRender.alDrawTriangle(120, 20, 200, 20, 150, 100, al_map_rgb(0, 120, 120));
    pRender.alDrawCircle(150, 150, 100, al_map_rgb(50, 255, 50));

    Point2D pointA(width / 2, height / 2);
    Point2D pointB(mouseX, mouseY);
    LineSegment segment(pointA, pointB);
    segment.draw(al_map_rgb(255, 255, 255));


    std::vector<Point2D> points;
    Point2D* newPoint = new Point2D(10, 10);
    points.push_back(*newPoint);
    newPoint = new Point2D(110, 10);
    points.push_back(*newPoint);
    newPoint = new Point2D(10, 110);
    points.push_back(*newPoint);
    newPoint = new Point2D(110, 110);
    points.push_back(*newPoint);



    pRender.drawPolygon(points, al_map_rgb(255, 0, 0));

    pRender.drawCircle(150, 150, 100, al_map_rgb(255, 0, 0));

    pRender.drawEllipse(mouseX, mouseY, 50, 100, al_map_rgb(255, 0, 0));
}

/*void Engine::render()
{
     al_clear_to_color(al_map_rgb(0, 0, 0));

    pRender.alDrawRectangle(20,20,100,100,al_map_rgb(255, 255, 255));
    pRender.alDrawTriangle(120,20,200,20, 150, 100, al_map_rgb(0, 120, 120));
    pRender.alDrawCircle(50,50, 10, al_map_rgb(50, 255, 50));


    //pRender.drawLine(width/2, height/2, mouseX, mouseY, al_map_rgb(255,255,255));

    al_flip_display();
}*/

void Engine::run()
{

    while (!stop) {
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            update();
            al_flip_display();
            //render();
        }
        else {
            input();
        }
    }
}

int main(void)
{
    Engine engine(false, 800, 800, 30);
    engine.run();

    return 0;
}