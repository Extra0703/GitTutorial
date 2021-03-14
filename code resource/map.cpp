#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 重新思考
	// 
	// 用二維陣列存地圖沒問題，他就只是從1像素單位，變成1格單位
	// 二維陣列地圖，表示的只是初始地圖，裡面的人物、箱子，會移動，所以這兩樣東西不能用map來確認位置，他們必須寫一個自己的method
	// 
	/////////////////////////////////////////////////////////////////////////////

	Map::Map() {
		int gameMap_init[10][15] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									 {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									 {0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
									 {0, 0, 0, 1, 3, 0, 0, 0, 0, 3, 0, 2, 1, 0, 0},
									 {0, 0, 0, 1, 0, 0, 4, 0, 3, 3, 0, 2, 1, 0, 0},
									 {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0},
									 {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
									 {0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0},
									 {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
									 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 15; j++) {
				gameMap[i][j] = gameMap_init[i][j];
			}
		}
	}

	void Map::LoadBitmap() {
		wall.LoadBitmap(IDB_WALL);
		goal.LoadBitmap(IDB_GOAL, RGB(255, 255, 255));
	}

	void Map::OnShow() {
		int count = 0;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 10; j++) {
				switch (gameMap[j][i]){
					case 0:
						break;
					case 1:
						wall.SetTopLeft(i * 64, j * 64);
						wall.ShowBitmap();
						break;
					case 2:
						goal.SetTopLeft(i * 64, j * 64);
						goal.ShowBitmap();
						break;
					default:
						break;
				}
			}
		}
	}

	int Map::getMap(int x, int y) {
		return gameMap[y][x];
	}
}