#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 可改變座標的有: SetXY();
	/////////////////////////////////////////////////////////////////////////////
	Box::Box(){
		x1 = y1 = 0;
	}

	bool Box::HitBox(Box *box)
	{
		bool hitBox = HitRectangle(box->GetX1(), box->GetY1(), box->GetX2(), box->GetY2());

		return hitBox;
	}

	bool Box::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x2 = x1 + chest.Width();	// 球的右下角x座標
		int y2 = y1 + chest.Height();	// 球的右下角y座標

		return (tx2 > x1 && tx1 < x2 && ty2 > y1 && ty1 < y2);
	}

	void Box::OnMove(){
		
	}

	void Box::OnShow() {
		chest.SetTopLeft(x1, y1);
		chest.ShowBitmap();
	}

	void Box::LoadBitmap()
	{
		chest.LoadBitmap(IDB_BOX, RGB(255, 255, 255));
	}

	void Box::SetX1Y1(int x, int y) {
		x1 = x;
		y1 = y;
	}

	void Box::SetX2Y2(int x, int y) {
		x1 = x - chest.Width();
		y1 = y - chest.Height();
	}

	int Box::GetX1()
	{
		return x1;
	}

	int Box::GetY1()
	{
		return y1;
	}

	int Box::GetX2()
	{
		return x1 + chest.Width();
	}

	int Box::GetY2()
	{
		return y1 + chest.Height();
	}
}