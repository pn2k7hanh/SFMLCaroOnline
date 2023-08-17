#include <SFML/Graphics.hpp>

#include "resource.h"
#include <Windows.h>

using namespace std;
using namespace sf;


int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(800,600),"Caro");

	HBITMAP bitmap = LoadBitmap(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDB_BITMAP1));
	
	Texture board;
	board.loadFromMemory(&bitmap, sizeof(bitmap));
	
	Sprite box(board);
	box.setTextureRect(IntRect(4,3,28,27));

	DeleteObject(bitmap);

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

		window.draw(box);

		window.display();
	}


	return EXIT_SUCCESS;
}