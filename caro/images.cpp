#include <SFML/Graphics/Image.hpp>

#include <Windows.h>

#include "images.h"

#include <iostream>
using std::cout;
using std::endl;

bool isInitImage = false;

sf::Image *Board, *BoxX, *BoxXs, *BoxO, *BoxOs, *BoxS;


void LoadImage(HDC &hdc,BYTE id,sf::Image *image)
{
	HBITMAP bitmap = LoadBitmap(GetModuleHandle(nullptr), MAKEINTRESOURCE(id));
	SelectObject(hdc, bitmap);
	BITMAP info;
	GetObject(bitmap, sizeof(BITMAP), &info);
	int width = info.bmWidth;
	int height = info.bmHeight;
	image->create(width, height);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			COLORREF color = GetPixel(hdc, i, j);
			BYTE red = GetRValue(color);
			BYTE green = GetGValue(color);
			BYTE blue = GetBValue(color);
			image->setPixel(i, j, sf::Color(red, green, blue));
		}
	}
	DeleteObject(bitmap);
}

void CreateImage()
{
	Board = new sf::Image;
	BoxX = new sf::Image;
	BoxXs = new sf::Image;
	BoxO = new sf::Image;
	BoxOs = new sf::Image;
	BoxS = new sf::Image;
}

bool IsInitImage()
{
	return isInitImage;
}

void InitImage()
{
	if (isInitImage) return;

	CreateImage();

	HDC hdc = CreateCompatibleDC(nullptr);

	LoadImage(hdc, IDB_BOARD, Board);
	LoadImage(hdc, IDB_BOXX, BoxX);
	LoadImage(hdc, IDB_BOXXS, BoxXs);
	LoadImage(hdc, IDB_BOXO, BoxO);
	LoadImage(hdc, IDB_BOXOS, BoxOs);
	LoadImage(hdc, IDB_BOXS, BoxS);

	DeleteDC(hdc);

	isInitImage = true;
}

const sf::Image* GetImage(Img::Id id)
{
	switch (id)
	{
	case Img::Board: return Board;
	case Img::BoxX: return BoxX;
	case Img::BoxXs: return BoxXs;
	case Img::BoxO: return BoxO;
	case Img::BoxOs: return BoxOs;
	case Img::BoxS: return BoxS;
	}
	return nullptr;
}