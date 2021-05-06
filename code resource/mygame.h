/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "map.h"
#include "Box.h"
#include "Character.h"

/////////////////////////////////////////////////////////////////////////////
// 參考文件裡，eraser專心移動，ball來判斷有沒有撞到，到mygame再處理onmove
// 在box寫碰到人物，character專心移動，map判斷他們有沒有撞牆(和ball一樣寫法)
// 總之，不要寫上下左右分別是啥的method
// character專心移動，box寫hitBox(回傳bool)和hitCharacter(回傳有哪裡撞到)，map寫hitWall(回傳bool)
/////////////////////////////////////////////////////////////////////////////
// map負責OnShow()，但不設定box和character的座標，給撞牆判斷
/////////////////////////////////////////////////////////////////////////////

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////


	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1e
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap homepage;							// 倉庫番
		CMovingBitmap background;						// 背景箱子
		CMovingBitmap menu;								// 選單1
		CMovingBitmap menuInv;							// 選單2
		CMovingBitmap play;								// 遊玩1
		CMovingBitmap playInv;							// 遊玩2
		CMovingBitmap helpText1;

		CMovingBitmap stage1;							// 關卡1
		CMovingBitmap stage1Inv;
		CMovingBitmap stage2;							// 關卡2
		CMovingBitmap stage2Inv;
		CMovingBitmap stage3;							// 關卡3
		CMovingBitmap stage3Inv;
		CMovingBitmap stage4;							// 關卡4
		CMovingBitmap stage4Inv;
		CMovingBitmap stage5;							// 關卡5
		CMovingBitmap stage5Inv;
		CMovingBitmap stage6;							// 關卡6
		CMovingBitmap stage6Inv;
		CMovingBitmap stage7;							// 關卡7
		CMovingBitmap stage7Inv;
		CMovingBitmap stage8;							// 關卡8
		CMovingBitmap stage8Inv;
		CMovingBitmap stage9;							// 關卡9
		CMovingBitmap stage9Inv;
		CMovingBitmap stage10;							// 關卡10
		CMovingBitmap stage10Inv;
		CMovingBitmap stage11;							// 關卡11
		CMovingBitmap stage11Inv;
		CMovingBitmap stage12;							// 關卡12
		CMovingBitmap stage12Inv;

		int chooseMenu;									// 目前是選哪個 菜單選項
		int chooseStage;								// 目前是選哪個 關卡
		bool inChooseStage;								// 選擇關卡中
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		void SetObjectPosition(Map gameMap);			// 依據不同地圖，設定箱子和人物物件位置
		void CheckManHitWall(Map gameMap);				// 依據不同地圖，判斷人物有沒有撞牆
		void CheckManHitBox(Map gameMap);				// 依據不同地圖，判斷人物有沒有撞箱子
		bool CheckWin(Map gameMap);						// 判斷該地圖箱子有沒有都在終點上
		CMovingBitmap background;						// 白底背景
		Character man;									// 人物物件
		Box box[8];										// 箱子物件
		Map1 gamemap1;									// 地圖物件
		Map2 gamemap2;
		Map3 gamemap3;
		Map4 gamemap4;
		Map5 gamemap5;
		Map6 gamemap6;
		Map7 gamemap7;
		Map8 gamemap8;
		Map9 gamemap9;
		Map10 gamemap10;
		Map11 gamemap11;
		Map12 gamemap12;

		// 下面的先不要動
		int whichMap;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Down的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
		int chooseMenu;		// 選哪個

		CMovingBitmap chooseStage;						// 回去選關卡
		CMovingBitmap chooseStageInv;
		CMovingBitmap exit;								// 返回主選單
		CMovingBitmap exitInv;
		CMovingBitmap nextStage;						// 去下一關
		CMovingBitmap nextStageInv;

		CMovingBitmap sign;								// 恭喜過關
	};

}