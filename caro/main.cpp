#include <SFML/Graphics.hpp>

#include "resource.h"
#include <Windows.h>

#include <iostream>


using namespace std;
using namespace sf;


int main(int argc, char** argv)
{
	RenderWindow window(VideoMode(800,600),"Caro");

	HMODULE bModule = GetModuleHandle(nullptr);
	HRSRC bResource = FindResource(bModule, MAKEINTRESOURCE(IDB_BITMAP1), RT_BITMAP);

	HGLOBAL bLoadedResource = LoadResource(nullptr, bResource);

	LPVOID bResourceData = LockResource(bLoadedResource);

	BITMAPINFOHEADER* bBitmapInfoHeader = reinterpret_cast<BITMAPINFOHEADER*>(bResourceData);

	int width = bBitmapInfoHeader->biWidth;
	int height = bBitmapInfoHeader->biHeight;
	int bpp = bBitmapInfoHeader->biBitCount;

	int size = width * height * (bpp / 8);

	BYTE* bPixelData = reinterpret_cast<BYTE*>(bResourceData) + sizeof(BITMAPINFOHEADER);

	Texture board;
	board.loadFromMemory(bPixelData,size);

	Sprite sprite(board);

	cout << width << endl;
	cout << height << endl;
	cout << bpp / 8 << endl;
	cout << size << endl;






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