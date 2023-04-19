#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


int main()
{
    /*
       ~Window Stuff~
    */
	VideoMode vm(1920, 1080);

    RenderWindow window(vm, "Chaos!", Style::Default);



    /*
        ~Font and Text~
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

    // set the position

    text.setPosition(10.f, 50.f);




    /*
        ~Sprites & Textures~
    */


    // Backround Sprite

    Sprite spriteBackground;
    Texture textureBackground;

    if (!textureBackground.loadFromFile("backround_stars.png"))
    {
        // error...
    }

    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

 


    // Sprite for clicks

    Sprite spriteClick;
    Texture textureClick;

    if (!textureClick.loadFromFile("kirby.png"))
    {
        // error...
    }


    spriteClick.setTexture(textureClick);


    /*
        ~Events~
    */
    int number_of_clicks = 0;


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
            switch (event.type)
            {

                case Event::Closed:
                    window.close();
                    break;

                case Event::MouseButtonPressed:
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        number_of_clicks++;
                    }
                    break;

                default:
                    break;
            }

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

        // Draw Text
        window.draw(text);

        // Draw spriteClick
        for (int i = 0; i < number_of_clicks; i++)
        {
            window.draw(spriteClick);
        }

        // Show everything we just drew
        window.display();

    }

	return 0;
}