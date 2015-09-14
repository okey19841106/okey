#ifndef __HEXAGON_H___
#define __HEXAGON_H___

class CDC;
class CPoint;


namespace okey
{

	

	class Hexagon
	{
	public:
		Hexagon();
		~Hexagon();

		void Draw(CDC* pDC);
		void DrawMap(CDC* pDC);
		void GetCellPoint(int x, int y , CPoint* point);
	protected:
		int _length;
		float _unitx;
		float _unity;
		int _x;
		int _y;
	};
}

#endif