#pragma once
#include "resource.h"

namespace sf
{
	class Image;
}


#define IDB_BOARD IDB_BITMAP1
#define IDB_BOXX IDB_BITMAP4
#define IDB_BOXXS IDB_BITMAP5
#define IDB_BOXO IDB_BITMAP2
#define IDB_BOXOS IDB_BITMAP3

extern bool isInitImage;

extern sf::Image Board, BoxX, BoxXs, BoxO, BoxOs;

void InitImage();