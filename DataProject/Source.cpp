#include <SFML/Graphics.hpp>
using namespace sf;
#include"menu.h"
int main()
{
    /*RenderWindow window(VideoMode(1000, 800), "MazeRunner");
    RectangleShape shape(Vector2f(40,40));
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    Menu m;
    m.display_menu();


    return 0;
}


