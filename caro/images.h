#pragma once
#include "resource.h"

#define IDB_BOARD IDB_BITMAP1
#define IDB_BOXX IDB_BITMAP4
#define IDB_BOXXS IDB_BITMAP5
#define IDB_BOXO IDB_BITMAP2
#define IDB_BOXOS IDB_BITMAP3
#define IDB_BOXS IDB_BITMAP6

namespace Img
{
	enum Id
	{
		Board,
		BoxX,
		BoxXs,
		BoxO,
		BoxOs,
		BoxS
	};
}

class sf::Image;

bool IsInitImage();
void InitImage();
const sf::Image* GetImage(Img::Id id);
