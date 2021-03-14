#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include <cmath>
#include "gamelib.h"
#include "map.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 
	/////////////////////////////////////////////////////////////////////////////
	Character::Character() {
		x = y = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		leftIs = rightIs = upIs = downIs = 0;
	}

	void Character::LoadBitmap() {
		man.LoadBitmap(IDB_UP1, RGB(255, 255, 255));
	}

	void Character::OnMove(){
		const int STEP_SIZE = 64;
		if (isMovingLeft && getLeftIs() != 1 && getLeftIs() != 3) {
			x -= STEP_SIZE;
		}
		if (isMovingRight && getRightIs() != 1 && getRightIs() != 3) {
			x += STEP_SIZE;
		}
		if (isMovingUp && getUpIs() != 1 && getUpIs() != 3) {
			y -= STEP_SIZE;
		}
		if (isMovingDown && getDownIs() != 1 && getDownIs() != 3) {
			y += STEP_SIZE;
		}
	}

	void Character::OnShow() {
		man.SetTopLeft(x, y);
		man.ShowBitmap();
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

	void Character::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}

	int Character::getX() {
		return x;
	}

	int Character::getY() {
		return y;
	}

	void Character::setLeftIs(int type) {
		leftIs = type;
	}

	void Character::setRightIs(int type) {
		rightIs = type;
	}

	void Character::setUpIs(int type) {
		upIs = type;
	}

	void Character::setDownIs(int type) {
		downIs = type;
	}

	int Character::getLeftIs() {
		return leftIs;
	}

	int Character::getRightIs() {
		return rightIs;
	}

	int Character::getUpIs() {
		return upIs;
	}

	int Character::getDownIs() {
		return downIs;
	}
}