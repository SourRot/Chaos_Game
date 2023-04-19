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


    /*
        We need to declare our data structure outside of the while loop

        I currently have it set to just increasing # of clicks as a proof that the event section works and registers mouse clicks
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

        // our event variable
        Event event;


        // This while loop checks for events and does different things based on which event happened

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
                        /*
                            We need to get the position of the mouse and store this in our data structure

                                This code snippet assigns the mouse position to a vector of 2 ints
                                    Vector2i localPosition = Mouse::getPosition(window);

                                Useful pages
                                    https://www.sfml-dev.org/documentation/2.5.1/structsf_1_1Event_1_1MouseButtonEvent.php#a49b937b311729174950787781aafcdc7
                                    https://www.sfml-dev.org/tutorials/2.5/graphics-transform.php
                        
                        */
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

        /*
            This is going to be the function for drawing our sprites on mouse clicks     
      
                while (something)
                {
                    window.draw(spriteClick);
                }
            Currently I have it set a wonky for() loop for proof of concept on event usage

            This is eventually going to be a rectangle instead of a sprite

        */
        for (int i = 0; i < number_of_clicks; i++)
        {
            window.draw(spriteClick);
        }

        // Show everything we just drew
        window.display();

    }

	return 0;
}