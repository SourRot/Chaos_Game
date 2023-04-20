// PARTNERS: Tareq Anwaryar and Rachel Greer

// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>

//I changed something
// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

// Example call: fractalCreation(vertices.at(0), vertices.at(1), vertices.at(2));

void fractalCreation(Vector2f point1, Vector2f point2, Vector2f point3, vector<Vector2f>& createdPoints)
{
	/*
		Rectangle creation:
			RectangleShape shape{ Vector2f{4,4} };
				shape.setFillColor(Color::Cyan);
				for (size_t i = 0; i < vertices.size(); i++)
				{
					FloatRect pointRect = shape.getLocalBounds();	// FINALLY FIXED THE POINT POSITION HOLY FLIP << THE MAN IS INSANE
					shape.setOrigin(pointRect.left +
						pointRect.width / 2.0f,
						pointRect.top +
						pointRect.height / 2.0f);
					shape.setPosition(Vector2f{ vertices.at(i) });
					window.draw(shape);
		}
	*/

	/*
		Choose a random point inside of the triangle
			A point halfway between 2 random points

		for() loop:
			Take whatever the last point is (halfway point)
			Draw a dot halfway between this point and 1 of the random initial points


	*/
	Vector2f randomPoint( (point1.x + point2.x) / 2, ( point1.y + point2.y ) / 2 );
	createdPoints.push_back(randomPoint);
	int selection = 0;

	
	
	for (size_t i = 0; i < 500; i++)
	{
			
			selection = rand() % 3 + 1;

			if (selection == 1) 
			{
				randomPoint = Vector2f((randomPoint.x + point1.x) / 2, (randomPoint.y + point1.y) / 2);
			}
			else if (selection == 2) 
			{
				randomPoint = Vector2f((randomPoint.x + point2.x) / 2, (randomPoint.y + point2.y) / 2);
			}
			else if (selection == 3) 
			{
				randomPoint = Vector2f((randomPoint.x + point3.x) / 2, (randomPoint.y + point3.y) / 2);
			}
			
			createdPoints.push_back(randomPoint);
	}

}

int main()
{
	float width = VideoMode::getDesktopMode().width;
	float height = VideoMode::getDesktopMode().height;
	View view(FloatRect(0.f, 0.f, width, height));
	// Create a video mode object
	VideoMode vm(width, height);
	//VideoMode vm(800, 600);

	// Create and open a window for the game
	RenderWindow window(vm, "Chaos!", Style::Default);

	// Create vectors
	vector<Vector2f> vertices;	// Initial 3 points (user clicks)
	vector<Vector2f> newPoints;	// Halfway points that are generated

	// Loading font
	Font font;
	font.loadFromFile("Kanit-Thin.ttf");
	Text messageText;

	// Set font and font size
	messageText.setFont(font);
	messageText.setCharacterSize(44);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("background_stars.png");

	// Create a sprite
	Sprite spriteBackground;

	// Setting the texture of the sprite and scaling it to our window
	Vector2u TextureSize;  // Added to store texture size.
	Vector2u WindowSize;   // Added to store window size.

	if (!textureBackground.loadFromFile("background_stars.png"))
	{
		return -1;
	}
	else
	{
		TextureSize = textureBackground.getSize(); // Get size of texture.
		WindowSize = window.getSize();             // Get size of window.

		float ScaleX = (float)WindowSize.x / TextureSize.x;
		float ScaleY = (float)WindowSize.y / TextureSize.y;     // Calculate scale.

		spriteBackground.setTexture(textureBackground);
		spriteBackground.setScale(ScaleX, ScaleY);      // Set scale.  
	}
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

					if (vertices.size() < 4)
					{
						std::cout << "the left button was pressed" << std::endl;
						std::cout << "mouse x: " << event.mouseButton.x << std::endl;
						std::cout << "mouse y: " << event.mouseButton.y << std::endl;

						Vector2i pixelPos = { event.mouseButton.x, event.mouseButton.y };
						Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
						vertices.push_back(worldPos);
						//vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}

					else
					{
						paused = false;
						break;
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Update the text
		stringstream ss;
		if (vertices.size() < 3)
		{
			ss << "Click anywhere to make vertices";
			messageText.setString(ss.str());
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left +
				textRect.width / 2.0f,
				textRect.top +
				textRect.height / 2.0f);
			messageText.setPosition(width / 2.0f, 100);
		}
		else
		{
			ss << "Alright that's 3! Time to start building your star! Give us another click";
			messageText.setString(ss.str());
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left +
				textRect.width / 2.0f,
				textRect.top +
				textRect.height / 2.0f);
			messageText.setPosition(width / 2.0f, 100);
		}

		// Clear everything from the last frame
		window.clear();

		window.setView(view);

		// Draw background
		window.draw(spriteBackground);

		// Draw the points
		RectangleShape shape{ Vector2f{4,4} };
		shape.setFillColor(Color::Cyan);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			FloatRect pointRect = shape.getLocalBounds();	// FINALLY FIXED THE POINT POSITION HOLY FLIP << THE MAN IS INSANE
			shape.setOrigin(pointRect.left +
				pointRect.width / 2.0f,
				pointRect.top +
				pointRect.height / 2.0f);
			shape.setPosition(Vector2f{ vertices.at(i) });
			window.draw(shape);
		}


		// Creating the vector of new points
		while (paused == false)
		{
			fractalCreation(vertices.at(0), vertices.at(1), vertices.at(2), newPoints);
			paused = true;
		}

		for (size_t i = 0; i < newPoints.size(); i++)
		{
			FloatRect pointRect = shape.getLocalBounds();	
			shape.setOrigin(pointRect.left +
				pointRect.width / 2.0f,
				pointRect.top +
				pointRect.height / 2.0f);
			shape.setPosition(Vector2f{ newPoints.at(i)});

			window.draw(shape);
			window.display();
			sleep(milliseconds(20));

		}
		

		// Draw our text
		window.draw(messageText);

		// Show everything we just drew
		window.display();


	}

	return 0;
}
