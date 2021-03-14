#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// ���s���
	// 
	// �ΤG���}�C�s�a�ϨS���D�A�L�N�u�O�q1�������A�ܦ�1����
	// �G���}�C�a�ϡA���ܪ��u�O��l�a�ϡA�̭����H���B�c�l�A�|���ʡA�ҥH�o��˪F�褣���map�ӽT�{��m�A�L�̥����g�@�Ӧۤv��method
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