// PARTNERS: Tareq Anwaryar and Rachel Greer

// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

//I changed something
// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;



// Example call: fractalCreation(vertices.at(0), vertices.at(1), vertices.at(2));

void fractalCreation(float numberOfNodes, vector<Vector2f> startingPoints, vector<Vector2f>& createdPoints)
{
	/*
		Choose a random point inside of the triangle
			A point halfway between 2 random points

		for() loop:
			Take whatever the last point is (halfway point)
			Draw a dot halfway between this point and 1 of the random initial points


	*/

	float scaling = numberOfNodes / (numberOfNodes + 3);

	Vector2f randomPoint(0, 0);

	Vector2f centerPoint(0, 0);
	float xTotal = 0.0;
	float yTotal = 0.0;

	for (int i = 0; i < numberOfNodes; i++)
	{
		
		xTotal += startingPoints.at(i).x;
		yTotal += startingPoints.at(i).y;

	}
	centerPoint.x = xTotal / numberOfNodes;
	centerPoint.y = yTotal / numberOfNodes;

	randomPoint = startingPoints.at(startingPoints.size()-1);
	startingPoints.erase(startingPoints.begin() + startingPoints.size() - 1);

	/*
	if (startingPoints.at(0).x > startingPoints.at(1).x)
	{
		randomPoint.x = startingPoints.at(0).x + (startingPoints.at(0).x - startingPoints.at(1).x) * scaling;
	}
	else
	{
		randomPoint.x = startingPoints.at(0).x + (startingPoints.at(0).x - startingPoints.at(1).x) * scaling;
	}
	if (startingPoints.at(0).y > startingPoints.at(1).y)
	{
		randomPoint.y = startingPoints.at(0).y + (startingPoints.at(0).y - startingPoints.at(1).y) * scaling;
	}
	else
	{
		randomPoint.y = startingPoints.at(0).y + (startingPoints.at(0).y - startingPoints.at(1).y) * scaling;
	}
	//Vector2f randomPoint( (startingPoints.at(0).x + startingPoints.at(1).x) * scaling, (startingPoints.at(0).y + startingPoints.at(1).y) * scaling);
	*/
	createdPoints.push_back(randomPoint);
	int selection = 0;


	if (numberOfNodes == 5)
	{
		startingPoints.push_back(centerPoint);
	}

	for (size_t i = 0; i < 10000; i++)
	{

		selection = rand() % startingPoints.size();
		if (numberOfNodes == 4)
		{
			randomPoint = Vector2f((randomPoint.x + startingPoints.at(selection).x) / 2, (randomPoint.y + startingPoints.at(selection).y) / 2);
		}
		else if (numberOfNodes == 5)
		{
			randomPoint = Vector2f(randomPoint.x + (startingPoints.at(selection).x - randomPoint.x) * .6666, randomPoint.y + (startingPoints.at(selection).y - randomPoint.y) * .6666);
		}
		else
		{
			randomPoint = Vector2f((randomPoint.x + startingPoints.at(selection).x) / 2, (randomPoint.y + startingPoints.at(selection).y) / 2);
			//randomPoint = Vector2f(randomPoint.x + (startingPoints.at(selection).x - randomPoint.x) * scaling, randomPoint.y + (startingPoints.at(selection).y - randomPoint.y) * scaling);
		}

		//randomPoint = Vector2f((randomPoint.x + startingPoints.at(selection).x) * scaling, (randomPoint.y + startingPoints.at(selection).y) * scaling);

		createdPoints.push_back(randomPoint);
	}

	if (numberOfNodes == 5)
	{
		startingPoints.erase(startingPoints.begin() + startingPoints.size() - 1);
	}
	

}



int main()
{


	// Create a video mode object
		// Values for desktop scaling
			float width = VideoMode::getDesktopMode().width;
			float height = VideoMode::getDesktopMode().height;
			View view(FloatRect(0.f, 0.f, width, height));
		VideoMode vm(width, height);
		

	// Create and open a window for the game
		RenderWindow window(vm, "Chaos!", Style::Default);

	// Create vectors
		vector<Vector2f> vertices;	// Initial 3 points (user clicks)
		vector<Vector2f> newPoints;	// Halfway points that are generated

	// Loading font
		Font font;
		font.loadFromFile("./Kanit-Thin.ttf");
		Text messageText;

	// Set font and font size
		messageText.setFont(font);
		messageText.setCharacterSize(44);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Backround sprite creation
	Sprite spriteBackground;

	// Setting the texture of the sprite and scaling it to our window
	Vector2u TextureSize;  // Added to store texture size.
	Vector2u WindowSize;   // Added to store window size.

	if (!textureBackground.loadFromFile("./background_stars.png"))
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

	// Buttons

		// Variables for various button parts
			Text triangleButton;
			Sprite spriteTriangleButton;

			Text rectangleButton;
			Sprite spriteRectangleButton;
			
			Text pentagonButton;
			Sprite spritePentagonButton;

			Text goCrazyButton;
			Sprite spriteGoCrazyButton;


			Vector2f buttonScaling = {2, 2 };

		// Button fonts
			triangleButton.setFont(font);
			triangleButton.setCharacterSize(44);
			triangleButton.setColor(Color::Black);

			rectangleButton.setFont(font);
			rectangleButton.setCharacterSize(44);
			rectangleButton.setColor(Color::Black);

			pentagonButton.setFont(font);
			pentagonButton.setCharacterSize(44);
			pentagonButton.setColor(Color::Black);

			goCrazyButton.setFont(font);
			goCrazyButton.setCharacterSize(44);
			goCrazyButton.setColor(Color::Black);

		// Button texts
			triangleButton.setString("Triangle");
			rectangleButton.setString("Rectangle");
			pentagonButton.setString("Pentagon");
			goCrazyButton.setString("Go Crazy");

	// Button texture assignment

		// Create a texture for button
			Texture textureButton;

		// Load a graphic into the texture
			textureButton.loadFromFile("./button_backround.png");

		// Button texture time

			// Triangle
				spriteTriangleButton.setTexture(textureButton);

			// Rectangle
				spriteRectangleButton.setTexture(textureButton);

			// Hexagon
				spritePentagonButton.setTexture(textureButton);

			// Reset
				spriteGoCrazyButton.setTexture(textureButton);

		// Button Positions

			// Triangle
				
				// Text
					FloatRect triangleButtonRect = triangleButton.getLocalBounds();
					triangleButton.setOrigin(triangleButtonRect.left +
						triangleButtonRect.width / 2.0f,
						triangleButtonRect.top +
						triangleButtonRect.height / 2.0f);
					triangleButton.setPosition(width / 12.0f, 200);

				// Sprite
					FloatRect trianglesSpriteRect = spriteTriangleButton.getLocalBounds();
					spriteTriangleButton.setOrigin(trianglesSpriteRect.left +
						trianglesSpriteRect.width / 2.0f,
						trianglesSpriteRect.top +
						trianglesSpriteRect.height / 2.0f);
					spriteTriangleButton.setPosition(width / 12.0f, 200);


			// Rectangle
			
				// Text
					FloatRect rectangleButtonRect = rectangleButton.getLocalBounds();
					rectangleButton.setOrigin(rectangleButtonRect.left +
						rectangleButtonRect.width / 2.0f,
						rectangleButtonRect.top +
						rectangleButtonRect.height / 2.0f);
					rectangleButton.setPosition(width / 12.0f, 400);

				// Sprite
					FloatRect rectangleSpriteRect = spriteRectangleButton.getLocalBounds();
					spriteRectangleButton.setOrigin(rectangleSpriteRect.left +
						rectangleSpriteRect.width / 2.0f,
						rectangleSpriteRect.top +
						rectangleSpriteRect.height / 2.0f);
					spriteRectangleButton.setPosition(width / 12.0f, 400);

			// Rhombus
			
				// Text
					FloatRect pentagonButtonRect = pentagonButton.getLocalBounds();
					pentagonButton.setOrigin(pentagonButtonRect.left +
						pentagonButtonRect.width / 2.0f,
						pentagonButtonRect.top +
						pentagonButtonRect.height / 2.0f);
					pentagonButton.setPosition(width / 12.0f, 600);

				// Sprite 
					FloatRect rhombusSpriteRect = spritePentagonButton.getLocalBounds();
					spritePentagonButton.setOrigin(rhombusSpriteRect.left +
						rhombusSpriteRect.width / 2.0f,
						rhombusSpriteRect.top +
						rhombusSpriteRect.height / 2.0f);
					spritePentagonButton.setPosition(width / 12.0f, 600);

			// Reset
			
				// Text
					FloatRect goCrazyButtonRect = goCrazyButton.getLocalBounds();
					goCrazyButton.setOrigin(goCrazyButtonRect.left +
						goCrazyButtonRect.width / 2.0f,
						goCrazyButtonRect.top +
						goCrazyButtonRect.height / 2.0f);
					goCrazyButton.setPosition(width / 12.0f, 800);

				// Sprite
					FloatRect goCrazySpriteRect = spriteGoCrazyButton.getLocalBounds();
					spriteGoCrazyButton.setOrigin(goCrazySpriteRect.left +
						goCrazySpriteRect.width / 2.0f,
						goCrazySpriteRect.top +
						goCrazySpriteRect.height / 2.0f);
					spriteGoCrazyButton.setPosition(width / 12.0f, 800);
					

			// Button sprite resizing
					spriteTriangleButton.scale(buttonScaling);

					spriteRectangleButton.scale(buttonScaling);
					spritePentagonButton.scale(buttonScaling);
					spriteGoCrazyButton.scale(buttonScaling);
					


	// The orb
	Texture textureKirby;
	textureKirby.loadFromFile("./kirby_fixed_size.png");

	Sprite kirby;
	kirby.setTexture(textureKirby);

	Vector2f kirbyScaling = { .2, .2 };

	kirby.scale(kirbyScaling);

	// Track whether the game is running
		bool created = false;
		int nodes = 0;
		int nodes_max = 0;
		bool reset = false;
		bool selection_made = false;
		bool secretFound = false;

	//	secret jumbo kirby
		Texture jumboKirby;
		jumboKirby.loadFromFile("./kirby.png");
		Vector2f jumboKirbyScaling = { 3, 3 };


		Sprite secretJumboKirby;
		secretJumboKirby.setTexture(textureKirby);

		FloatRect jumboKirbyRect = secretJumboKirby.getLocalBounds();
		secretJumboKirby.setOrigin(jumboKirbyRect.left +
			jumboKirbyRect.width / 2.0f,
			jumboKirbyRect.top +
			jumboKirbyRect.height / 2.0f);
		secretJumboKirby.setPosition(width / 3.0f, 2000);



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
					auto mouse_pos = Mouse::getPosition(window);
					auto translated_pos = window.mapPixelToCoords(mouse_pos);

					if (secretJumboKirby.getGlobalBounds().contains(translated_pos))
					{
						secretFound = true;
					}

					if (spriteTriangleButton.getGlobalBounds().contains(translated_pos))
					{
						nodes_max = 4;
						selection_made = true;
					}
					else if (spriteRectangleButton.getGlobalBounds().contains(translated_pos))
					{
						nodes_max = 5;
						selection_made = true;
					}
					else if (spritePentagonButton.getGlobalBounds().contains(translated_pos))
					{
						nodes_max = 6;
						selection_made = true;
					}
					else if (spriteGoCrazyButton.getGlobalBounds().contains(translated_pos))
					{
						nodes_max = 10;
						selection_made = true;
					}
					
					else if (selection_made = true && nodes_max > 1)
					{
						std::cout << "the left button was pressed" << std::endl;
						std::cout << "mouse x: " << event.mouseButton.x << std::endl;
						std::cout << "mouse y: " << event.mouseButton.y << std::endl;

						if (nodes < nodes_max)
						{
							Vector2i pixelPos = { event.mouseButton.x, event.mouseButton.y };
							Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
							vertices.push_back(worldPos);
							nodes++;
						}
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
		if (created == false && selection_made == false)
		{
			ss << "Choose your shape!";
			messageText.setString(ss.str());
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left +
				textRect.width / 2.0f,
				textRect.top +
				textRect.height / 2.0f);
			messageText.setPosition(width / 2.0f, 100);
		}
		else if (selection_made = true)
		{
			if (nodes_max == 4)
			{
				ss << "Sierkirby Triangle";
				messageText.setString(ss.str());
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(width / 2.0f, 100);
			}
			else if (nodes_max == 5)
			{
				ss << "Kirbtangle!";
				messageText.setString(ss.str());
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(width / 2.0f, 100);
			}
			else if (nodes_max == 6)
			{
				ss << "Kirbagon";
				messageText.setString(ss.str());
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(width / 2.0f, 100);
			}
		}
		else if (created == true)
		{
			ss << "Beautiful...";
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

		// Initialize the vector for point-making

			if ((nodes == nodes_max && selection_made == true) && created == false)
			{
				fractalCreation((float)nodes, vertices, newPoints);
				created = true;

			}

		// Secret Jumbo Kirby
			if (secretFound == true)
			{
				kirby.scale(jumboKirbyScaling);
				secretFound = false;
			}
		
		// Draw the points
		//RectangleShape shape{ Vector2f{4,4} };
		//shape.setFillColor(Color::Cyan);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			//FloatRect pointRect = shape.getLocalBounds();	// FINALLY FIXED THE POINT POSITION HOLY FLIP << THE MAN IS INSANE
			FloatRect pointRect = kirby.getLocalBounds();
			//shape.setOrigin(pointRect.left +
			kirby.setOrigin(pointRect.left +
				pointRect.width / 2.0f,
				pointRect.top +
				pointRect.height / 2.0f);
			//shape.setPosition(Vector2f{ vertices.at(i) });
			kirby.setPosition(Vector2f{ vertices.at(i) });
			//window.draw(shape);
			window.draw(kirby);
		}

		// Basic message text
			window.draw(messageText);

			
		// Buttons
			window.draw(spriteTriangleButton);
			window.draw(triangleButton);
				
			window.draw(spriteRectangleButton);
			window.draw(rectangleButton);

			window.draw(spritePentagonButton);
			window.draw(pentagonButton);

			window.draw(spriteGoCrazyButton);
			window.draw(goCrazyButton);


			window.draw(secretJumboKirby);
		// Drawing the fractal

			for (size_t i = 0; i < newPoints.size(); i++)
			{

				//window.clear(); // ***** this does something very cool/funny

			//FloatRect pointRect = shape.getLocalBounds();
			FloatRect pointRect = kirby.getLocalBounds();
			//shape.setOrigin(pointRect.left +
			kirby.setOrigin(pointRect.left +
				pointRect.width / 2.0f,
				pointRect.top +
				pointRect.height / 2.0f);

			//shape.setPosition(Vector2f{ newPoints.at(i) });
			kirby.setPosition(Vector2f{ newPoints.at(i) });
			//window.draw(shape);
			window.draw(kirby);
		}

		// Show everything we just drew
		window.display();


	}

	return 0;
}
