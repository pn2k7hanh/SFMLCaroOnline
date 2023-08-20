#include <SFML/Graphics/Texture.hpp>
#include "images.h"

#include "texture.h"

#include <iostream>
using std::cout;
using std::endl;

bool isInitTexture = false;

sf::Texture *TexUp, 
			*TexDown, 
			*TexLeft, 
			*TexRight, 
			*TexUpLeft, 
			*TexUpRight, 
			*TexDownLeft, 
			*TexDownRight, 
			*TexBox, 
			*TexBoxX, 
			*TexBoxXs, 
			*TexBoxO, 
			*TexBoxOs,
			*TexBoxS;

bool IsInitTexture()
{
	return isInitTexture;
}

void CreateTexture()
{
	TexUp = new sf::Texture;
	TexDown = new sf::Texture;
	TexLeft = new sf::Texture;
	TexRight = new sf::Texture;
	TexUpLeft = new sf::Texture;
	TexUpRight = new sf::Texture;
	TexDownLeft = new sf::Texture;
	TexDownRight = new sf::Texture;
	TexBox = new sf::Texture;
	TexBoxX = new sf::Texture;
	TexBoxXs = new sf::Texture;
	TexBoxO = new sf::Texture;
	TexBoxOs = new sf::Texture;
	TexBoxS = new sf::Texture;
}

void InitTexture()
{
	if (IsInitTexture()) return;
	if (IsInitImage()) InitImage();

	CreateTexture();

	TexUp->loadFromImage(*GetImage(u.id), sf::IntRect(u.x, u.y, u.w, u.h));
	TexDown->loadFromImage(*GetImage(d.id), sf::IntRect(d.x, d.y, d.w, d.h));
	TexLeft->loadFromImage(*GetImage(l.id), sf::IntRect(l.x, l.y, l.w, l.h));
	TexRight->loadFromImage(*GetImage(r.id), sf::IntRect(r.x, r.y, r.w, r.h));
	TexUpLeft->loadFromImage(*GetImage(ul.id), sf::IntRect(ul.x, ul.y, ul.w, ul.h));
	TexUpRight->loadFromImage(*GetImage(ur.id), sf::IntRect(ur.x, ur.y, ur.w, ur.h));
	TexDownLeft->loadFromImage(*GetImage(dl.id), sf::IntRect(dl.x, dl.y, dl.w, dl.h));
	TexDownRight->loadFromImage(*GetImage(dr.id), sf::IntRect(dr.x, dr.y, dr.w, dr.h));
	TexBox->loadFromImage(*GetImage(bx.id), sf::IntRect(bx.x, bx.y, bx.w, bx.h));
	TexBoxX->loadFromImage(*GetImage(x.id), sf::IntRect(x.x, x.y, x.w, x.h));
	TexBoxXs->loadFromImage(*GetImage(xs.id), sf::IntRect(xs.x, xs.y, xs.w, xs.h));
	TexBoxO->loadFromImage(*GetImage(o.id), sf::IntRect(o.x, o.y, o.w, o.h));
	TexBoxOs->loadFromImage(*GetImage(os.id), sf::IntRect(os.x, os.y, os.w, os.h));
	TexBoxS->loadFromImage(*GetImage(bs.id), sf::IntRect(bs.x, bs.y, bs.w, bs.h));

	isInitTexture = true;
}

sf::Texture* GetTexture(Tex::Id id)
{
	switch (id)
	{
	case Tex::Up: return TexUp;
	case Tex::Down: return TexDown;
	case Tex::Left: return TexLeft;
	case Tex::Right: return TexRight;
	case Tex::UpLeft: return TexUpLeft;
	case Tex::UpRight: return TexUpRight;
	case Tex::DownLeft: return TexDownLeft;
	case Tex::DownRight: return TexDownRight;
	case Tex::Box: return TexBox;
	case Tex::BoxX: return TexBoxX;
	case Tex::BoxXs: return TexBoxXs;
	case Tex::BoxO: return TexBoxO;
	case Tex::BoxOs: return TexBoxOs;
	case Tex::BoxS: return TexBoxS;
	}
	return nullptr;
}