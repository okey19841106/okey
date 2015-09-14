#include "stdafx.h"
#include "Hexagon.h"


namespace okey
{
	Hexagon::Hexagon()
	{
		_x = 500;
		_y = 500;
		_length = 50;
		_unitx = _length * 1.7320508;
		_unity = _length * 1.5;
	}

	Hexagon::~Hexagon(){}

	void Hexagon::Draw(CDC* pDC)
	{
		//pDC->Rectangle(0,0, 500, 500);
		DrawMap(pDC);
// 		CPoint p[6];
// 		GetCellPoint(500, 500, p);
// 		pDC->Polygon(p, 6);
// 
// 		CString sz = CString("[0,0]");
// 		pDC->TextOutW(50,50,sz);
	}
	void Hexagon::GetCellPoint(int x, int y , CPoint* lpPoints)
	{
		if(lpPoints == NULL) return;
	
		lpPoints[0].x = x - _length;
		lpPoints[0].y = y;

		lpPoints[1].x = x - _length/2;
		lpPoints[1].y = y + (int)(_unitx*0.5); 

		lpPoints[2].x = x + _length/2;
		lpPoints[2].y = lpPoints[1].y;//y + _length/2;

		lpPoints[3].x = x + _length;
		lpPoints[3].y = y;

		lpPoints[4].x = x + _length/2;
		lpPoints[4].y = y - (int)(_unitx*0.5); 

		lpPoints[5].x = x  - _length/2;
		lpPoints[5].y = lpPoints[4].y;
	}

	void Hexagon::DrawMap(CDC* pDC)
	{
		
		int x = (int)(_x / _unity) + 1;
		int y = (int)(_y / _unitx) + 1;
		int x_s = 0;
		int y_s = (int)(_unitx * 0.5);
		for (int i = 0; i < x; ++i)
		{
			if (i % 2 == 0)
			{
				for (int j = 0; j < y ; ++j)
				{
					int p_x = i * (_unity); 
					int p_y = (int)(_unitx * 0.5) + (int)(_unitx*j);
					CPoint p[6];
					GetCellPoint(p_x, p_y, p);
					pDC->Polygon(p,6);
				}
			}
			else
			{
				for (int j = 0; j < y ; ++j)
				{
					int p_x = (int)(_unity) + i*3*_length;
					int p_y = (int)(_unitx*j);
					CPoint p[6];
					GetCellPoint(p_x, p_y, p);
					pDC->Polygon(p,6);
				}
			}
		}
	}
// 		while(y < _y)
// 		{
// 			x = 0;
// 			while(x < _x)
// 			{
// 				CPoint p[6];
// 				GetCellPoint(x,y,p);
// 				pDC->Polygon(p,6);
// 				x += 3*_length;
// 			}
// 			y += (int)(_unitx * 0.5);
// 		}
	
	
}