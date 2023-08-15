#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(800,600),"Caro");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
	}

	return EXIT_SUCCESS;
}