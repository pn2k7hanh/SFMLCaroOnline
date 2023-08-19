#pragma once

#include "images.h"


const struct
{
	Img::Id id;
	int x, y, w, h;
}	u{ Img::Board,4,0,24,3 },
	d{ Img::Board,4,27,24,1 },
	l{ Img::Board,0,3,4,24 },
	r{ Img::Board,28,3,2,24 },
	ul{ Img::Board,0,0,4,3 },
	ur{ Img::Board,28,0,2,3 },
	dl{ Img::Board,0,27,4,1 },
	dr{ Img::Board,28,27,2,1 },
	bx{ Img::Board,4,3,24,24 },
	x{ Img::BoxX,0,0,24,24 },
	xs{ Img::BoxXs,0,0,24,24 },
	o{ Img::BoxO,0,0,24,24 },
	os{ Img::BoxOs,0,0,24,24 };

namespace Tex
{
	enum Id
	{
		Up,
		Down,
		Left,
		Right,
		UpLeft,
		UpRight,
		DownLeft,
		DownRight,
		Box,
		BoxX,
		BoxXs,
		BoxO,
		BoxOs
	};
}

namespace sf
{
	class Texture;
}

bool IsInitTexture();
void InitTexture();
sf::Texture* GetTexture(Tex::Id id);


