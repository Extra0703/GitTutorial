#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "map.h"
#include "Box.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 
	/////////////////////////////////////////////////////////////////////////////
	Box::Box(){
		x = y = 0;
		onGoal = false;
		boxNumber = 0;
		//isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Box::LoadBitmap() {
		box.LoadBitmap(IDB_BOX, RGB(255, 255, 255));
	}

	void Box::OnMove(Map* map){
		
	}

	void Box::OnShow() {
		box.SetTopLeft(x, y);
		box.ShowBitmap();
	}

	bool Box::isOnGoal(){
		return onGoal;
	}

	void Box::setIsOnGoal(Map* map) {
		if (2 == map->getMap(x / 64, y / 64)) {
			onGoal = true;
		}else {
			onGoal = false;
		}
	}

	void Box::setBoxNumber(int num) {
		boxNumber = num;
	}
	int Box::getBoxNumber() {
		return boxNumber;
	}

	void Box::SetXY(int nx, int ny){
		x = nx; y = ny;
	}

	int Box::getX() {
		return x;
	}

	int Box::getY() {
		return y;
	}

	void Box::setLeftIs(int type) {
		leftIs = type;
	}

	void Box::setRightIs(int type) {
		rightIs = type;
	}

	void Box::setUpIs(int type) {
		upIs = type;
	}

	void Box::setDownIs(int type) {
		downIs = type;
	}

	int Box::getLeftIs() {
		return leftIs;
	}

	int Box::getRightIs() {
		return rightIs;
	}

	int Box::getUpIs() {
		return upIs;
	}

	int Box::getDownIs() {
		return downIs;
	}
}