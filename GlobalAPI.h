//---------------------------------------------------------------------------

#ifndef GlobalAPIH
#define GlobalAPIH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "RectEx.h"

namespace GlobalAPI
{
	//painting API
	BOOL BitBltEx(HDC hDestDC,RectX rc,HDC hSrcDC, POINT ptStart, DWORD dwRop);

	int DrawTextEx(HDC hDC, const AnsiString& strTx, RectX rc, UINT uFormat);
	BOOL RectangleX(HDC hDC, RectX rc);
	BOOL EllipseX(HDC hDC, RectX rc);
	void DrawScrawl(HDC hDC, POINT ptStart, POINT ptEnd);
	int DrawArrowLine(HDC hDC, LPPOINT lpPointStart, LPPOINT lpPointEnd, double nArrowBorderLen, double xAngleInRadians, COLORREF cr);

};

#endif
