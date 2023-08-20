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
	const int mleft = 30;
	const int mright = 40;
	const int mbottom = 50;
	
	int m, n;
	//cin >> m >> n;
	m = 20;
	n = 20;

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
		
		Vector2i pos = Mouse::getPosition(window);
		cout << pos.x << " " << pos.y << endl;

		// Preload Board
		tul.setPosition(0, 0); tul.move(mleft, mtop);
		tur.setPosition((float)ul.w + n * bx.w, 0); tur.move(mleft, mtop);
		tdl.setPosition(0, (float)ul.h + m * bx.h); tdl.move(mleft, mtop);
		tdr.setPosition((float)ul.w + n * bx.w, (float)ul.h + m * bx.h); tdr.move(mleft, mtop);
		window.draw(tul);
		window.draw(tur);
		window.draw(tdl);
		window.draw(tdr);
		for (int i = 0; i < m; i++)
		{
			tleft.setPosition(0, (float)ul.h + i * l.h);
			tleft.move(mleft, mtop);
			tright.setPosition((float)ul.w + n * bx.w, (float)ul.h + i * l.h);
			tright.move(mleft, mtop);
			window.draw(tleft);
			window.draw(tright);
		}
		for (int i = 0; i < n; i++)
		{
			tup.setPosition((float)ul.w + i * u.w, 0);
			tup.move(mleft, mtop);
			tdown.setPosition((float)ul.w + i * u.w, (float)ul.h + m * bx.h);
			tdown.move(mleft, mtop);
			window.draw(tup);
			window.draw(tdown);
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				tb.setPosition((float)i * bx.w, (float)j * bx.h);
				tb.move((float)mleft + ul.w, (float)mtop + ul.h);
				window.draw(tb);
			}
		}



		//tbx.setPosition(50., 50.);
		//window.draw(tbx);
		


		window.display();
	}


	return EXIT_SUCCESS;
}