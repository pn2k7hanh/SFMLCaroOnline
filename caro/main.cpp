#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "resource.h"
#include "images.h"
#include "texture.h"

#include <Windows.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;
using namespace sf;

bool joined = false;
const char* joinip;
short joinport;
bool online = true;

unsigned short defaultPort = 33327;


int main(int argc, char** argv)
{

	for (int i = 1; i < argc; i++)
	{
		const char* str = argv[i];
		if (strcmp(str, "--help") == 0)
		{
			cout << "Help" << endl;
			return EXIT_SUCCESS;
		}
		else if (strcmp(str, "--join") == 0)
		{
			if (i + 2 < argc)
			{
				joinip = argv[i + 1];
				joinport = atoi(argv[i + 2]);
				i += 2;
			}
			else if (i + 1 < argc)
			{
				joinip = argv[i + 1];
				joinport = defaultPort;
				i++;
			}
			else
			{
				cerr << "Error: no input ip" << endl;
				return EXIT_FAILURE;
			}
			online = true;
			joined = true;
			//break;
		}
		else if (strcmp(str, "--online") == 0)
		{
			if (i + 1 < argc)
			{
				defaultPort = atoi(argv[i + 1]);
				online = true;
				i++;
			}
			else
			{
				clog << "Log: Using port 33327" << endl;
				online = true;
			}
			//break;
		}
		else
		{
			cerr << "Error: Unknowed option \"" << argv[i] << "\"" << endl;
			return EXIT_FAILURE;
		}
	}

	
	
	
	const int mtop = 20;
	const int mleft = 30;
	const int mright = 40;
	const int mbottom = 50;

	int m = 20, n = 20;
	


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

	
	//window.setVisible(false);

	Clock clock;

	// Mouse Event
	int preX = 0, preY = 0;
	int oldX = (m - 1) / 2;
	int oldY = (n - 1) / 2;
	bool preSelected = false;
	bool mouseMoved = false;
	bool mousePressed = false;
	bool mouseReleased = false;

	// Key Event
	map<Keyboard::Key, pair<int, int>> keys; // first is delay; second is time
	int keyboardFirstDelay = 125;
	int keyboardSecondDelay = 75;

	// Select Box Move
	int x = (m - 1) / 2;
	int y = (n - 1) / 2;
	int dx = 0, dy = 0;
	bool selected = false;

	// Field
	enum class Caro
	{
		X,
		O,
		None
	} **field, turn = Caro::X;

	field = new Caro* [m];
	for (int i = 0; i < m; i++)
	{
		field[i] = new Caro[n];
		for (int j = 0; j < n; j++)
		{
			field[i][j] = Caro::None;
		}
	}

	// Networking

	bool connected = false;
	bool received = false;
	bool sent = false;

	IpAddress pip;
	unsigned short pport;

	int nx = 0, ny = 0;

	UdpSocket* socket = new UdpSocket;

	if (online)
	{
		socket->bind(defaultPort);
		socket->setBlocking(true);
		if (joined)
		{
			char cdata[] = "connect algori\n";
			socket->send(cdata, sizeof(cdata), IpAddress(joinip), joinport);
			char* data = new char[1024];
			size_t size;
			clog << "Log: Connecting to " << joinip << ":" << joinport << ", please wait..." << endl;

			do
			{
				Socket::Status status = socket->receive(data, sizeof(*data) * 1023, size, pip, pport);
				if (Socket::Status::Done != status)
				{
					delete[]data;
					cerr << "Error: Couldn't receive data from socket!" << endl;
					clog << "Log: Exit caro!" << endl;
					return EXIT_FAILURE;
				}
			} while (pip != joinip || pport != joinport);

			data[size] = '\0';

			if (strstr(data, "connect algori") != nullptr)
			{
				socket->send(cdata, sizeof(cdata), IpAddress(joinip), joinport);
				connected = true;
				delete[]data;
				clog << "Log: Connect to " << joinip << ":" << joinport << " successfully! Have fun ^_^!" << endl;
			}
			else
			{
				delete[]data;
				cerr << "Error: Couldn't connect to " << joinip << ":" << joinport << endl;
				clog << "Log: Exit caro!" << endl;
				return EXIT_FAILURE;
			}
		}
		else
		{
			char cdata[] = "connect algori\n";
			char* data = new char[1024];
			size_t size;
			clog << "Waiting for connection, please wait..." << endl;

			do
			{
				Socket::Status status = socket->receive(data, sizeof(*data) * 1023, size, pip, pport);
				data[size] = '\0';
				if (Socket::Status::Done != status)
				{
					delete[]data;
					cerr << "Error: Couldn't receive data from socket!" << endl;
					clog << "Log: Exit caro!" << endl;
					return EXIT_FAILURE;
				}

			} while (strstr(data, "connect algori") == nullptr);

			clog << "Log: Connecting to " << pip << ":" << pport << "!" << endl;
			socket->send(cdata, sizeof(cdata), IpAddress(pip), pport);

			delete[]data;


		}
		socket->setBlocking(false);
	}
	
	socket->setBlocking(false);


	// Window
	RenderWindow window(VideoMode(
		mtop + mbottom + ul.w + dr.w + bx.w * n,
		mleft + mright + ul.h + dr.h + bx.h * m), "Caro", Style::Titlebar | Style::Close);
	window.setTitle("Caro Online");
	window.setSize(Vector2u(mtop + mbottom + ul.w + dr.w + bx.w * n, mleft + mright + ul.h + dr.h + bx.h * m));

	window.setKeyRepeatEnabled(false);

	bool closed = false;


	while (!closed)
	{
		int time = clock.getElapsedTime().asMilliseconds();

		if (!keys.empty())
		{
			for (map<Keyboard::Key, pair<int, int>>::iterator i = keys.begin(); i != keys.end(); i++)
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
				closed = true;
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
				}
				break;
			case Event::KeyReleased:
				if (event.key.code == Keyboard::Space ||
					event.key.code == Keyboard::Enter)
				{
					if (preSelected)
					{
						if (x == preX && y == preY)
						{
							selected = true;
						}
						preSelected = false;
					}
				}
				else keys.erase(event.key.code);
				break;
			}
		}

		// Keyboard
		if (!keys.empty())
		{
			for (map<Keyboard::Key, pair<int, int>>::iterator i = keys.begin(); i != keys.end(); i++)
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
			
			oldX = x;
			oldY = y;

			x = (mouse.x - mleft - ul.w) / bx.w;
			y = (mouse.y - mtop - ul.h) / bx.h;


			if (!(0 <= x && x < m && 0 <= y && y < n))
			{
				x = oldX;
				y = oldY;
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
					if (field[preX][preY] == Caro::None) preSelected = true;
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

		////// Receive Data
		if (online)
		{
			char* data = new char[1024];
			size_t size;
			IpAddress ip;
			unsigned short port;
			Socket::Status status = socket->receive(data, sizeof(*data) * 1023, size, ip, port);
			data[size] = '\0';
			if (Socket::Status::Done == status)
			{
				if (ip != pip || port != pport)
				{
					cerr << "Warning: " << ip << ":" << port << " try to break the game!" << endl;
				}
				else if (strstr(data, "connect algori") == nullptr)
				{
					if (strstr(data, "caro") != nullptr)
					{
						char* token = strtok(data, " ");
						if (strcmp(token, "caro") == 0)
						{
							token = strtok(nullptr, " ");
							preX = atoi(token);
							token = strtok(nullptr, " ");
							preY = atoi(token);
							received = true;
							selected = true;
						}
					}
					else if (strstr(data, "disconnect") != nullptr)
					{
						clog << "Log: " << pip << ":" << pport << " has been disconnected!" << endl;
						clog << "Log: You won!" << endl;
						closed = true;
					}
				}
			}
		}


		////// Selected //////
		if (selected)
		{
			// In online mode, check = true if it's your turn
			bool check = false;

			if (online)
				if (joined)
					if (turn == Caro::O) check = true; else;
				else
					if (turn == Caro::X) check = true; else;
			else check = true;


			if (check ^ received)
			{
				if (field[preX][preY] == Caro::None)
				{
					field[preX][preY] = turn;
					turn = (turn == Caro::X) ? Caro::O : Caro::X;
					if (check)
					{
						nx = preX;
						ny = preY;
						sent = true;
					}
				}
			}


			selected = false;
			received = false;
		}

		////// Send data
		if (online)
		{
			if (sent)
			{
				string data = "caro " + to_string(nx) + " " + to_string(ny) + "\n";
				Socket::Status status;
				do
				{
					status = socket->send(data.c_str(), sizeof(char) * (data.size() + 1), pip, pport);
				} while (status != Socket::Status::Done);
				sent = false;
			}
			if (closed)
			{
				char data[] = "disconnect\n";
				socket->send(data, sizeof(data), pip, pport);
			}
		}


		if (closed)
		{
			window.close();
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
					Sprite& _draw = (field[i][j] == Caro::X) ? tbxs : ((field[i][j] == Caro::O) ? tbos : tbs);
					_draw.setPosition((float)i * bx.w, (float)j * bx.h);
					_draw.move((float)mleft + ul.w, (float)mtop + ul.h);
					window.draw(_draw);
				}
				else
				{
					Sprite& _draw = (field[i][j] == Caro::X) ? tbx : ((field[i][j] == Caro::O) ? tbo : tb);
					_draw.setPosition((float)i * bx.w, (float)j * bx.h);
					_draw.move((float)mleft + ul.w, (float)mtop + ul.h);
					window.draw(_draw);
				}
				if (preSelected)
				{
					if (i == preX && j == preY)
					{
						Sprite& _draw = (turn == Caro::X) ? tbxs : tbos;
						_draw.setPosition((float)i * bx.w, (float)j * bx.h);
						_draw.move((float)mleft + ul.w, (float)mtop + ul.h);
						window.draw(_draw);
					}
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

	//*/

	return EXIT_SUCCESS;
}