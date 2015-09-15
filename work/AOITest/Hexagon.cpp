#include "stdafx.h"
#include "Hexagon.h"


namespace okey
{
	Hexagon::Hexagon()
	{
		_x = 800;
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
		CRect rc;
		rc.left = rc.top = 0;
		rc.right = _x;
		rc.bottom = _y;
		pDC->Rectangle(&rc);
		bool flag = false;
		//int x = (_x - (_length*0.5))/_unity + 2;
		int x = (int)(_x / _unity) + 1;
		int delt =_x - ((x - 1)* _unity) ;
		if (delt > 0 && ((float)delt > _length*0.5))
		{
			++x;
		}
		int y = (int)(_y / _unitx) + 1;
		int delt_y = _y - ((y - 1)* _unitx);
		if (delt_y > 0 && (float)delt_y > (_unitx * 0.5))
		{
			++y;
			flag = true;
		}


		int x_s = 0;
		int y_s = (int)(_unitx * 0.5);
		for (int i = 0; i < x; ++i)
		{
			if (i % 2 == 0)
			{
				for (int j = 0; j < y ; ++j)
				{
					int p_x = i * (_unity); 
					int p_y = (int)(_unitx*j);
					CPoint p[6];
					GetCellPoint(p_x, p_y, p);
					pDC->Polygon(p,6);
					CString str;
					str.Format(CString("[%d,%d]"),i,j);
					pDC->TextOutW(p_x,p_y,str);
					
				}
			}
			else
			{
				for (int j = 0; j < y ; ++j)
				{
					int p_x = /*(_unity * 0.5f) + */(int)(_unity*i);
					int p_y = (int)(_unitx * 0.5) + (int)(_unitx*j);
					CPoint p[6];
					GetCellPoint(p_x, p_y, p);
					pDC->Polygon(p,6);
					CString str;
					str.Format(CString("[%d,%d]"),i,j);
					pDC->TextOutW(p_x,p_y,str);
					if (flag && j == y -2)
					{
						++j;
					}
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
	void Hexagon::GetCellID(int x, int y, int& rx, int &ry)
	{
		rx = ry = -1;
		if (x < 0 || x > _x)
		{
			return;
		}
		if (y < 0 || y > _y)
		{
			return;
		}

		float w = _unity;
		float h = _unitx * 0.5f;
		float temp1 = (w*w - h*h )/2.0f;
		float temp2 = (w*w + h*h )/2.0f;
// #define CELL_BORDER        (40) //Áù±ßÐÎ±ß³¤
// #define GRID_WIDTH        (CELL_BORDER*1.5f)
// #define GRID_HEIGHT        (CELL_BORDER*0.8660254f)    // sqr(3)/2=0.8660254
// #define TEMP_1            ((GRID_WIDTH*GRID_WIDTH ¨C GRID_HEIGHT*GRID_HEIGHT)/2.f)
// #define TEMP_2            ((GRID_WIDTH*GRID_WIDTH + GRID_HEIGHT*GRID_HEIGHT)/2.f)

		ry = (int)(y/h);
		float ty = y -ry*h;

		rx = (int)(x/w);
		float tx = x -rx*w;

		if((rx+ry)&1)
		{
			if(tx*w-ty*h > temp1) rx++;
		}
		else
		{
			if(tx*w+ty*h > temp2) rx++;
		}
// 		if (ry & 1)
// 		{
// 			ry = ry  /2;
// 		}
// 		else
// 		{
// 			ry = (ry + 1) /2;
// 		}
		ry = (ry+(1-(rx&1)))/2;
	}
	
}