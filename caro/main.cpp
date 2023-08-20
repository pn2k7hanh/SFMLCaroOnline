#include <SFML/Graphics.hpp>

#include "resource.h"
#include "images.h"
#include "texture.h"

#include <Windows.h>
#include <iostream>
#include <map>


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

	RenderWindow window(VideoMode(
		mtop+mbottom+ul.w+dr.w+bx.w*n,
		mleft+mright+ul.h+dr.h+bx.h*m),"Caro",Style::Titlebar | Style::Close);
	window.setTitle("Caro Online");
	window.setSize(Vector2u(mtop+mbottom+ul.w+dr.w+bx.w*n,mleft+mright+ul.h+dr.h+bx.h*m));

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
			tbos(*GetTexture(Tex::BoxOs)),
			tbs(*GetTexture(Tex::BoxS));

	window.setKeyRepeatEnabled(false);
	
	Clock clock;



	// Mouse Event
	int preX = 0, preY = 0;
	bool preSelected = false;
	bool mouseMoved = false;
	bool mousePressed = false;
	bool mouseReleased = false;

	// Key Event
	map<Keyboard::Key, pair<float, float>> keys; // first is delay; second is time
	int keyboardFirstDelay = 150;
	int keyboardSecondDelay = 75;

	// Select Box Move
	int x = (m - 1) / 2;
	int y = (n - 1) / 2;
	int dx = 0, dy = 0;
	bool selected = false;

	// Field
	int** field;
	field = new int* [m];
	for (int i = 0; i < m; i++)
	{
		field[i] = new int[n];
	}

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds();
		if (!keys.empty())
		{
			for (map<Keyboard::Key, pair<float, float>>::iterator i = keys.begin(); i != keys.end(); i++)
			{
				i->second.second += time;
			}
		}
		clock.restart();

		// Event
		Event event;
		while (window.pollEvent(event))
		{
			
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::MouseMoved:
				mouseMoved = true;
				break;
			case Event::MouseButtonPressed:
				mousePressed = true;
				break;
			case Event::MouseButtonReleased:
				mouseReleased = true;
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Space ||
					event.key.code == Keyboard::Enter)
				{
					preX = x;
					preY = y;
					preSelected = true;
				}
				else
				{
					keys.insert({ event.key.code,{0,0} });
					preSelected = false;
				}
				break;
			case Event::KeyReleased:
				if (event.key.code == Keyboard::Space ||
					event.key.code == Keyboard::Enter)
				{
					if (preSelected)
					{
						selected = true;
					}
				}
				else keys.erase(event.key.code);
				break;
			}
		}

		// Keyboard
		if (!keys.empty())
		{
			for (map<Keyboard::Key, pair<float, float>>::iterator i = keys.begin(); i != keys.end(); i++)
			{
				if (i->second.second >= i->second.first)
				{
					i->second.second = 0;

					if (i->second.first == 0)
					{
						i->second.first = keyboardFirstDelay;
					}
					else if (i->second.first >= keyboardFirstDelay)
					{
						i->second.first = keyboardSecondDelay;
					}

					switch (i->first)
					{
					case Keyboard::W:
					case Keyboard::Up:
						dy = -1;
						break;
					case Keyboard::S:
					case Keyboard::Down:
						dy = 1;
						break;
					case Keyboard::A:
					case Keyboard::Left:
						dx = -1;
						break;
					case Keyboard::D:
					case Keyboard::Right:
						dx = 1;
						break;
					}
				}
			}
		}

		// Select Box Move
		if (dx != 0 || dy != 0)
		{
			if (0 <= x + dx && x + dx < m)
			{
				x += dx;
			}
			if (0 <= y + dy && y + dy < m)
			{
				y += dy;
			}
			dx = dy = 0;
		}

		// Mouse
		if (mouseMoved)
		{
			Vector2i mouse = Mouse::getPosition(window);
			
			x = (mouse.x - mleft - ul.w) / bx.w;
			y = (mouse.y - mtop - ul.h) / bx.h;

			if (!(0 <= x && x < m && 0 <= y && y < n))
			{
				x = (m - 1) / 2;
				y = (n - 1) / 2;
			}

			mouseMoved = false;
		}

		if (mousePressed)
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i mouse = Mouse::getPosition(window);
				preX = (mouse.x - mleft - ul.w) / bx.w;
				preY = (mouse.y - mtop - ul.h) / bx.h;
				if (0 <= preX && preX < m && 0 <= preY && preY < n)
				{
					preSelected = true;
				}
			}
			mousePressed = false;
		}

		if (mouseReleased)
		{
			if (preSelected)
			{
				if (0 <= preX && preX < m && 0 <= preY && preY < n)
				{
					Vector2i mouse = Mouse::getPosition(window);
					int tmpX = (mouse.x - mleft - ul.w) / bx.w;
					int tmpY = (mouse.y - mtop - ul.h) / bx.h;
					if (preX == tmpX && preY == tmpY)
					{
						selected = true;
					}
				}
				preSelected = false;
			}
			mouseReleased = false;
		}

		// Selected
		if (selected)
		{
			cout << "Selected" << endl;
			selected = false;
		}





		////// Draw //////
		
		window.clear(Color::Black);

		// Border
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
		// Box
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (x == i && y == j)
				{
					tbs.setPosition((float)i * bx.w, (float)j * bx.h);
					tbs.move((float)mleft + ul.w, (float)mtop + ul.h);
					window.draw(tbs);
				}
				else
				{
					tb.setPosition((float)i * bx.w, (float)j * bx.h);
					tb.move((float)mleft + ul.w, (float)mtop + ul.h);
					window.draw(tb);
				}
			}
		}


		window.display();
	}

	for (int i = 0; i < m; i++)
	{
		delete[] field[i];
	}
	delete[] field;

	return EXIT_SUCCESS;
}