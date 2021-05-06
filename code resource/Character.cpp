#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include <cmath>
#include "gamelib.h"
#include "Box.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 可改變座標的只有: OnMove();
	/////////////////////////////////////////////////////////////////////////////
	Character::Character() {
		x1 = y1 = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		checkHitBox[0] = checkHitBox[1] = checkHitBox[2] = checkHitBox[3] = false;
	}

	void Character::HitBox(Box *chest) {
		int chestX1 = chest->GetX1();
		int chestX2 = chest->GetX2();
		int chestY1 = chest->GetY1();
		int chestY2 = chest->GetY2();
		bool touchChest = HitRectangle(chestX1, chestY1, chestX2, chestY2);

		// 往下移 並且有碰撞
		bool touchTop = isMovingDown && touchChest;
		bool touchBottom = isMovingUp && touchChest;
		bool touchLeft = isMovingRight && touchChest;
		bool touchRight = isMovingLeft && touchChest;

		checkHitBox[0] = touchTop;
		checkHitBox[1] = touchBottom;
		checkHitBox[2] = touchLeft;
		checkHitBox[3] = touchRight;
	}
	
	bool Character::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x2 = x1 + chara.Width();	// chara的右下角x座標
		int y2 = y1 + chara.Height();	// chara的右下角y座標

		return (tx2 > x1 && tx1 < x2 && ty2 > y1 && ty1 < y2);
	}

	void Character::OnMove(){
		const int STEP_SIZE = 8;
		if (isMovingLeft) {
			left.OnMove();
			x1 -= STEP_SIZE;
		}
		if (isMovingRight) {
			right.OnMove();
			x1 += STEP_SIZE;
		}
		if (isMovingUp) {
			up.OnMove();
			y1 -= STEP_SIZE;
		}
		if (isMovingDown) {
			down.OnMove();
			y1 += STEP_SIZE;
		}
	}

	void Character::OnShow() {
		if (isMovingUp) {
			up.SetTopLeft(x1, y1);
			up.OnShow();
		}
		else if (isMovingDown) {
			down.SetTopLeft(x1, y1);
			down.OnShow();
		}
		else if (isMovingLeft) {
			left.SetTopLeft(x1, y1);
			left.OnShow();
		}
		else if (isMovingRight) {
			right.SetTopLeft(x1, y1);
			right.OnShow();
		}
		else {
			down.SetTopLeft(x1, y1);
			down.OnShow();
		}

		/*chara.SetTopLeft(x1, y1);
		chara.ShowBitmap();*/
	}

	void Character::LoadBitmap()
	{
		up.AddBitmap(IDB_UP1, RGB(255, 255, 255));
		up.AddBitmap(IDB_UP2, RGB(255, 255, 255));
		up.AddBitmap(IDB_UP3, RGB(255, 255, 255));
		down.AddBitmap(IDB_DOWN1, RGB(255, 255, 255));
		down.AddBitmap(IDB_DOWN2, RGB(255, 255, 255));
		down.AddBitmap(IDB_DOWN3, RGB(255, 255, 255));
		left.AddBitmap(IDB_LEFT1, RGB(255, 255, 255));
		left.AddBitmap(IDB_LEFT2, RGB(255, 255, 255));
		right.AddBitmap(IDB_RIGHT1, RGB(255, 255, 255));
		right.AddBitmap(IDB_RIGHT2, RGB(255, 255, 255));

		chara.LoadBitmap(IDB_UP1, RGB(255, 255, 255));
	}

	void Character::SetMovingDown(bool flag) {
		isMovingDown = flag;
	}

	void Character::SetMovingLeft(bool flag) {
		isMovingLeft = flag;
	}

	void Character::SetMovingRight(bool flag) {
		isMovingRight = flag;
	}

	void Character::SetMovingUp(bool flag) {
		isMovingUp = flag;
	}

	void Character::SetX1Y1(int x, int y) {
		x1 = x;
		y1 = y;
	}

	void Character::SetX2Y2(int x, int y) {
		x1 = x - chara.Width();
		y1 = y - chara.Height();
	}

	int Character::GetX1()
	{
		return x1;
	}

	int Character::GetY1()
	{
		return y1;
	}

	int Character::GetX2()
	{
		return x1 + chara.Width();
	}

	int Character::GetY2()
	{
		return y1 + chara.Height();
	}
}