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
	const int mtop = 20;
	const int mleft = 20;
	const int mright = 20;
	const int mbottom = 20;
	
	int m, n;
	cin >> m >> n;

	int** matrix;
	matrix = new int* [m];
	for_each(matrix, matrix + m, [=](int* array) {array = new int[n]; });

	RenderWindow window(VideoMode(mtop+mbottom+ul.w+dr.w+bx.w*n,mleft+mright+ul.h+dr.h+bx.h*m),"Caro");

	InitImage();
	InitTexture();


	// Sprite ////////////////////////////

	Sprite	tup(*GetTexture(Tex::Up)),
			tdown(*GetTexture(Tex::Down)),
			tleft(*GetTexture(Tex::Left)),
			tright(*GetTexture(Tex::Right)),
			tul(*GetTexture(Tex::UpLeft)),
			tdl(*GetTexture(Tex::DownLeft)),
			tur(*GetTexture(Tex::UpRight)),
			tdr(*GetTexture(Tex::DownRight)),
			tb(*GetTexture(Tex::Box)),
			tbx(*GetTexture(Tex::BoxX)),
			tbxs(*GetTexture(Tex::BoxXs)),
			tbo(*GetTexture(Tex::BoxO)),
			tbos(*GetTexture(Tex::BoxOs));

	// Preload Board

	

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

		window.clear(Color::Black);









		window.display();
	}


	return EXIT_SUCCESS;
}