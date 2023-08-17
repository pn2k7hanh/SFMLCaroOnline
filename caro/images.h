#pragma once
#include "resource.h"

typedef LPCWSTR;

namespace Img
{
	struct
	{
		LPCWSTR f;
		int x, y, w, h;
	}	u	{ IDB_BITMAP1,4,0,24,3 },
		d	{ IDB_BITMAP1,4,27,24,1 },
		l	{ IDB_BITMAP1,0,3,4,24 },
		r	{ IDB_BITMAP1,28,3,2,24 },
		ul	{ IDB_BITMAP1,0,0,4,3 },
		ur	{ IDB_BITMAP1,28,0,2,3 },
		dl	{ IDB_BITMAP1,0,27,4,1 },
		dr	{ IDB_BITMAP1,28,27,2,1 },
		x	{ IDB_BITMAP4,0,0,24,24 },
		xs	{ IDB_BITMAP5,0,0,24,24 },
		o	{ IDB_BITMAP2,0,0,24,24 },
		os	{ IDB_BITMAP3,0,0,24,24 };
}