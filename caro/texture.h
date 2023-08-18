#pragma once

#include "images.h"

#include <SFML/Graphics/Texture.hpp>

//namespace sf
//{
//	class Texture;
//}

const struct
{
	unsigned char id;
	int x, y, w, h;
}	u{ IDB_BOARD,4,0,24,3 },
	d{ IDB_BOARD,4,27,24,1 },
	l{ IDB_BOARD,0,3,4,24 },
	r{ IDB_BOARD,28,3,2,24 },
	ul{ IDB_BOARD,0,0,4,3 },
	ur{ IDB_BOARD,28,0,2,3 },
	dl{ IDB_BOARD,0,27,4,1 },
	dr{ IDB_BOARD,28,27,2,1 },
	bx{ IDB_BOARD,4,3,24,24 },
	x{ IDB_BOXX,0,0,24,24 },
	xs{ IDB_BOXXS,0,0,24,24 },
	o{ IDB_BOXO,0,0,24,24 },
	os{ IDB_BOXOS,0,0,24,24 };

extern bool isInitTexture;

namespace Tex {
	extern sf::Texture up, down, left, right, upleft, upright, downleft, downright, box, boxx, boxxs, boxo, boxos;
}


void InitTexture();