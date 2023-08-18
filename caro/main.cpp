#include <SFML/Graphics.hpp>

#include "resource.h"
#include "images.h"
#include "texture.h"

#include <Windows.h>
#include <iostream>


using namespace std;
using namespace sf;


int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(800,600),"Caro");

	InitImage();
	InitTexture();
	
	int row, col;
	cin >> row >> col;


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

		window.clear(Color::White);



		window.display();
	}


	return EXIT_SUCCESS;
}