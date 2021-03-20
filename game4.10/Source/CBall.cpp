#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CBall::CBall()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
	}

	bool CBall::HitEraser(CEraser *eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool CBall::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// �y�����W��x�y��
		int y1 = y + dy;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CBall::IsAlive()
	{
		return is_alive;
	}

	void CBall::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));			// ���J�y���ϧ�
		bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// ���J�y��ߪ��ϧ�
	}

	void CBall::OnMove()
	{
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// �p��y�V����ߪ��첾�qdx, dy
			//
			const int STEPS = 18;
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}
	}

	void CBall::SetDelay(int d)
	{
		delay = d;
	}

	void CBall::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CBall::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CBall::OnShow()
	{
		if (is_alive) {
			bmp.SetTopLeft(x + dx, y + dy);
			bmp.ShowBitmap();
			bmp_center.SetTopLeft(x, y);
			bmp_center.ShowBitmap();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// YSun: Sun class
	/////////////////////////////////////////////////////////////////////////////

	YSun::YSun() {
		srand((int)time(NULL));
		x = (rand() % 550) + 200;		// 200~750
		y = -100;
		floor = (rand() % 250) + 250;	//250~500
		is_alive = true;
	}
	void YSun::OnLButtonDown(UINT nFlags, CPoint point) {
		if (point.x > x - 5 && point.y - 5 > y && point.x < x + 80 && point.y < y + 80) {
			is_alive = false;
		}
	}
	bool YSun::IsAlive() {
		return is_alive;
	}
	void YSun::LoadBitmap() {
		char *filename[8] = { ".\\bitmaps\\sun0.bmp",".\\bitmaps\\sun1.bmp",".\\bitmaps\\sun2.bmp",".\\bitmaps\\sun3.bmp"
		, ".\\bitmaps\\sun4.bmp",".\\bitmaps\\sun5.bmp",".\\bitmaps\\sun6.bmp",".\\bitmaps\\sun7.bmp"
		};
		for (int i = 0; i < 8; i++)	// ���J�ʵe(��8�i�ϧκc��)
			sunanimation.AddBitmap(filename[i], RGB(255, 255, 255));
	}
	void YSun::OnMove() {
		if (!is_alive)
			return;
		if(GetY() < GetFloor())
			y = y + 1;
		
		sunanimation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
	}
	void YSun::OnShow() {
		sunanimation.SetTopLeft(x, y);
		sunanimation.OnShow();
	}

	void YSun::SetIsAlive(bool alive) {
		is_alive = alive;
	}

	int YSun::GetX() {
		return x;
	}

	int YSun::GetY() {
		return y;
	}

	int	YSun::GetFloor() {
		return floor;
	}
	//CMovingBitmap sun;			// �y����
	//int x, y;					// ��ߪ��y��

	//bool is_alive;


}