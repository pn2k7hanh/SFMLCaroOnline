#include <SFML/Graphics.hpp>

#include "resource.h"
#include <Windows.h>

#include <iostream>


using namespace std;
using namespace sf;


int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(800,600),"Caro");

	HBITMAP bitmap = LoadBitmap(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDB_BITMAP1));
	if (bitmap == nullptr)
	{
		cout << "No" << endl;
		return -1;
	}

	BITMAP info;
	GetObject(bitmap,sizeof(BITMAP),&info);

	HDC hdc = CreateCompatibleDC(nullptr);
	SelectObject(hdc,bitmap);

	Image image;
	image.create(info.bmWidth, info.bmHeight, reinterpret_cast<const sf::Uint8*>(info.bmBits));

	Texture texture;
	texture.loadFromImage(image);

	Sprite sprite(texture);








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

		window.draw(sprite);

		window.display();
	}


	return EXIT_SUCCESS;
}