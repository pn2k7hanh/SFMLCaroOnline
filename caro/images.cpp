#include <SFML/Graphics/Image.hpp>

#include <Windows.h>

#include "images.h"

bool isInitImage = false;

sf::Image Board, BoxX, BoxXs, BoxO, BoxOs;


void LoadImage(HDC &hdc,BYTE id,sf::Image &image)
{
	HBITMAP bitmap = LoadBitmap(GetModuleHandle(nullptr), MAKEINTRESOURCE(id));
	BITMAP info;
	GetObject(bitmap, sizeof(BITMAP), &info);
	int width = info.bmWidth;
	int height = info.bmHeight;
	image.create(width, height);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			COLORREF color = GetPixel(hdc, i, j);
			BYTE red = GetRValue(color);
			BYTE green = GetGValue(color);
			BYTE blue = GetBValue(color);
			image.setPixel(i, j, sf::Color(red, green, blue));
		}
	}
	DeleteObject(bitmap);
}

void InitImage()
{
	if (isInitImage) return;

	HDC hdc = CreateCompatibleDC(nullptr);

	LoadImage(hdc, IDB_BOARD, Board);
	LoadImage(hdc, IDB_BOXX, BoxX);
	LoadImage(hdc, IDB_BOXXS, BoxXs);
	LoadImage(hdc, IDB_BOXO, BoxO);
	LoadImage(hdc, IDB_BOXOS, BoxOs);

	DeleteDC(hdc);

	isInitImage = true;
}
