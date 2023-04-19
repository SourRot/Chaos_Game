#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


int main()
{
    /*
        Window stats
    */
	VideoMode vm(1920, 1080);

    RenderWindow window(vm, "Chaos!", Style::Default);

    Texture textureBackground;

    if (!textureBackground.loadFromFile("backround_stars.png"))
    {
        // error...
    }

    Sprite spriteBackground;

    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    /*
        Font and Text!
    */
    Font font;

    if (!font.loadFromFile("Kanit-Thin.ttf"))
    {

        // error...
    }

    Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Hello world");

    // set the character size
    text.setCharacterSize(16); // in pixels, not points!

    // set the color
    text.setFillColor(Color::Yellow);

    // set the text style
    text.setStyle(Text::Bold | Text::Underlined);

    text.setPosition(10.f, 50.f);






    // run the program as long as the window is open
    while (window.isOpen())
    {
        /*
         ****************************************
         Handle the players input
         ****************************************
         */

        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /*
        ****************************************
        Update the scene
        ****************************************
        */


        /*
        ****************************************
        Draw the scene
        ****************************************
        */

        // Clear everything from the last frame
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);

        //Draw Text
        window.draw(text);

        // Show everything we just drew
        window.display();

    }

	return 0;
}