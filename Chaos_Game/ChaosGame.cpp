// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>

//I changed something
// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

// Gonna come back to this to see why the smaller window clicks aren't matching https://github.com/rhermle/ChaosGameStarterCode (It's the mouse click events done for us)

int main()
{
	View view(FloatRect(0.f, 0.f, 1920.f, 1080.f));
	// Create a video mode object
	//VideoMode vm(1920, 1080);
	VideoMode vm(800, 600);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos!", Style::Default);

	// Create vector
	vector<Vector2f> vertices;

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("background_stars.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Variables to control time itself
	Clock clock;

	// Track whether the game is running
	bool paused = true;

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
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					Vector2i pixelPos = { event.mouseButton.x, event.mouseButton.y };
					Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
					vertices.push_back(worldPos);
					//vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the points
		RectangleShape shape{ Vector2f{4,4} };
		shape.setFillColor(Color::Cyan);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			shape.setPosition(Vector2f{ vertices.at(i) });
			window.draw(shape);
		}

		// Show everything we just drew
		window.display();


	}

	return 0;
}
