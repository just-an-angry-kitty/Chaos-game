// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	// 1 font to communicate with the user
	Font coolFont;
	if (!coolFont.loadFromFile("impact.ttf"))
	{
		// error...
		cout << "something went wrong loading the font :(" << endl;
	}
	
	// 1 text object to display text to the user
	Text coolText;
	coolText.setFont(coolFont);
	coolText.setString("Hi! Please click 3 times to create the triangle vertices.");
	coolText.setCharacterSize(24);
	coolText.setFillColor(Color::Cyan);
	coolText.setStyle(Text::Underlined);
	coolText.setPosition(700,30);

	


	vector<Vector2f> vertices;
	vector<Vector2f> points;

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
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
					if(vertices.size() < 3)
					{
					vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						if(vertices.size() == 3)
						{
							coolText.setFillColor(Color::Yellow);
							coolText.setString("Cool! Now click again to start the chaos game algorithm");
						}
					}
					else if (points.size() == 0)  // when triangle vertices are set, we will start adding points inside the triangle
					{
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		// now we need a random number generator
		srand(static_cast<unsigned int>(time(0)));

		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			for (int i = 0; i < 20; i++) {          // generate 20 new points each time
				int randomI = rand() % 3;
				Vector2f lastPoint = points.back();
				Vector2f newVertex = vertices[randomI];
				// Triangle: r = 1/2 or 0.5
				Vector2f nextPoint((lastPoint.x + newVertex.x) * 0.5, (lastPoint.y + newVertex.y) * 0.5);
				points.push_back(nextPoint);
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		// display the text
		window.draw(coolText);


		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		///TODO:  Draw points
		Color theMostBeautifulColor(86, 196, 255);
		CircleShape dot(1);
		dot.setFillColor(theMostBeautifulColor);
		for (int i = 0; i < points.size(); i++)
		{
			dot.setPosition(points[i].x, points[i].y);
			window.draw(dot);
		}

		window.display();
	}
}
