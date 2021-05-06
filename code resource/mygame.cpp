/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	// �ثe���d
	int newStage = 1;
	// �O�_�i�J���d���
	bool initStage = false;
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
	chooseMenu = 0;
	chooseStage = 0;
	inChooseStage = false;
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	homepage.LoadBitmap(IDB_HOMEPAGE, RGB(255, 255, 255));
	background.LoadBitmap(IDB_WALL, RGB(255, 255, 255));
	menu.LoadBitmap(IDB_MENU, RGB(255, 255, 255));
	menuInv.LoadBitmap(IDB_MENUINV, RGB(255, 255, 255));
	play.LoadBitmap(IDB_PLAY, RGB(255, 255, 255));
	playInv.LoadBitmap(IDB_PLAYINV, RGB(255, 255, 255));
	helpText1.LoadBitmap(IDB_HELPTEXT1, RGB(255, 255, 255));

	stage1.LoadBitmap(IDB_STAGE1, RGB(255, 255, 255));
	stage1Inv.LoadBitmap(IDB_STAGE1INV, RGB(255, 255, 255));
	stage2.LoadBitmap(IDB_STAGE2, RGB(255, 255, 255));
	stage2Inv.LoadBitmap(IDB_STAGE2INV, RGB(255, 255, 255));
	stage3.LoadBitmap(IDB_STAGE3, RGB(255, 255, 255));
	stage3Inv.LoadBitmap(IDB_STAGE3INV, RGB(255, 255, 255));
	stage4.LoadBitmap(IDB_STAGE4, RGB(255, 255, 255));
	stage4Inv.LoadBitmap(IDB_STAGE4INV, RGB(255, 255, 255));
	stage5.LoadBitmap(IDB_STAGE5, RGB(255, 255, 255));
	stage5Inv.LoadBitmap(IDB_STAGE5INV, RGB(255, 255, 255));
	stage6.LoadBitmap(IDB_STAGE6, RGB(255, 255, 255));
	stage6Inv.LoadBitmap(IDB_STAGE6INV, RGB(255, 255, 255));
	stage7.LoadBitmap(IDB_STAGE7, RGB(255, 255, 255));
	stage7Inv.LoadBitmap(IDB_STAGE7INV, RGB(255, 255, 255));
	stage8.LoadBitmap(IDB_STAGE8, RGB(255, 255, 255));
	stage8Inv.LoadBitmap(IDB_STAGE8INV, RGB(255, 255, 255));
	stage9.LoadBitmap(IDB_STAGE9, RGB(255, 255, 255));
	stage9Inv.LoadBitmap(IDB_STAGE9INV, RGB(255, 255, 255));
	stage10.LoadBitmap(IDB_STAGE10, RGB(255, 255, 255));
	stage10Inv.LoadBitmap(IDB_STAGE10INV, RGB(255, 255, 255));
	stage11.LoadBitmap(IDB_STAGE11, RGB(255, 255, 255));
	stage11Inv.LoadBitmap(IDB_STAGE11INV, RGB(255, 255, 255));
	stage12.LoadBitmap(IDB_STAGE12, RGB(255, 255, 255));
	stage12Inv.LoadBitmap(IDB_STAGE12INV, RGB(255, 255, 255));
}

void CGameStateInit::OnBeginState()
{
	inChooseStage = initStage;
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';

	if (nChar == KEY_LEFT && chooseMenu > 1) {
		chooseMenu = chooseMenu - 1;
	}

	if (nChar == KEY_RIGHT && chooseMenu < 2) {
		chooseMenu = chooseMenu + 1;
	}

	if (nChar == KEY_LEFT && chooseStage > 1) {
		chooseStage = chooseStage - 1;
	}

	if (nChar == KEY_RIGHT && chooseStage < 12) {
		chooseStage = chooseStage + 1;
	}

	// ������d
	if (nChar == KEY_SPACE && inChooseStage) {
		// �n�h�� gameStateRun �� whichMap
		newStage = chooseStage;
		GotoGameState(GAME_STATE_RUN);
	}

	// �O�o������J�klol
	if (nChar == KEY_SPACE) {
		switch (chooseMenu)
		{
			case 1:
				inChooseStage = true;
				break;
			case 2:	// �o�̦� Bug
				GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
				break;
			default:
				break;
		}
	}


	if (nChar == KEY_ESC) {								// Demo �����C������k
		if (inChooseStage) {
			chooseMenu = 0;
			chooseStage = 0;
			inChooseStage = false;
		}
		else {
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
		}
	}
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			background.SetTopLeft(i * 64, j * 64);
			background.ShowBitmap();
		}
	}

	if (!inChooseStage) {
		homepage.SetTopLeft((SIZE_X - homepage.Width()) / 2, SIZE_Y / 8);
		menu.SetTopLeft(50, 480);
		menuInv.SetTopLeft(50, 480);
		play.SetTopLeft(350, 480);
		playInv.SetTopLeft(350, 480);
		menu.ShowBitmap();
		play.ShowBitmap();
		homepage.ShowBitmap();

		if (chooseMenu == 1) {
			menuInv.ShowBitmap();
			play.ShowBitmap();
		}
		else if (chooseMenu == 2) {
			menu.ShowBitmap();
			playInv.ShowBitmap();
		}
		else {
			menu.ShowBitmap();
			play.ShowBitmap();
		}
	}
	else {
		helpText1.SetTopLeft(48, 48);
		helpText1.ShowBitmap();
		switch (chooseStage)
		{
			case 0:
				stage1.SetTopLeft((SIZE_X - stage1.Width()) / 2, SIZE_Y / 4);
				stage1.ShowBitmap();
				stage2.SetTopLeft(448 + (SIZE_X - stage2.Width()) / 2, SIZE_Y / 4);
				stage2.ShowBitmap();
				break;
			case 1:
				stage1Inv.SetTopLeft((SIZE_X - stage1Inv.Width()) / 2, SIZE_Y / 4);
				stage1Inv.ShowBitmap();
				stage2.SetTopLeft(448 + (SIZE_X - stage2.Width()) / 2, SIZE_Y / 4);
				stage2.ShowBitmap();
				break;
			case 2:
				stage1.SetTopLeft(-448 + (SIZE_X - stage1.Width()) / 2, SIZE_Y / 4);
				stage1.ShowBitmap();
				stage2Inv.SetTopLeft((SIZE_X - stage2Inv.Width()) / 2, SIZE_Y / 4);
				stage2Inv.ShowBitmap();
				stage3.SetTopLeft(448 + (SIZE_X - stage3.Width()) / 2, SIZE_Y / 4);
				stage3.ShowBitmap();
				break;
			case 3:
				stage2.SetTopLeft(-448 + (SIZE_X - stage2.Width()) / 2, SIZE_Y / 4);
				stage2.ShowBitmap();
				stage3Inv.SetTopLeft((SIZE_X - stage3Inv.Width()) / 2, SIZE_Y / 4);
				stage3Inv.ShowBitmap();
				stage4.SetTopLeft(448 + (SIZE_X - stage4.Width()) / 2, SIZE_Y / 4);
				stage4.ShowBitmap();
				break;
			case 4:
				stage3.SetTopLeft(-448 + (SIZE_X - stage3.Width()) / 2, SIZE_Y / 4);
				stage3.ShowBitmap();
				stage4Inv.SetTopLeft((SIZE_X - stage4Inv.Width()) / 2, SIZE_Y / 4);
				stage4Inv.ShowBitmap();
				stage5.SetTopLeft(448 + (SIZE_X - stage5.Width()) / 2, SIZE_Y / 4);
				stage5.ShowBitmap();
				break;
			case 5:
				stage4.SetTopLeft(-448 + (SIZE_X - stage4.Width()) / 2, SIZE_Y / 4);
				stage4.ShowBitmap();
				stage5Inv.SetTopLeft((SIZE_X - stage5Inv.Width()) / 2, SIZE_Y / 4);
				stage5Inv.ShowBitmap();
				stage6.SetTopLeft(448 + (SIZE_X - stage6.Width()) / 2, SIZE_Y / 4);
				stage6.ShowBitmap();
				break;
			case 6:
				stage5.SetTopLeft(-448 + (SIZE_X - stage5.Width()) / 2, SIZE_Y / 4);
				stage5.ShowBitmap();
				stage6Inv.SetTopLeft((SIZE_X - stage6Inv.Width()) / 2, SIZE_Y / 4);
				stage6Inv.ShowBitmap();
				stage7.SetTopLeft(448 + (SIZE_X - stage7.Width()) / 2, SIZE_Y / 4);
				stage7.ShowBitmap();
				break;
			case 7:
				stage6.SetTopLeft(-448 + (SIZE_X - stage6.Width()) / 2, SIZE_Y / 4);
				stage6.ShowBitmap();
				stage7Inv.SetTopLeft((SIZE_X - stage7Inv.Width()) / 2, SIZE_Y / 4);
				stage7Inv.ShowBitmap();
				stage8.SetTopLeft(448 + (SIZE_X - stage8.Width()) / 2, SIZE_Y / 4);
				stage8.ShowBitmap();
				break;
			case 8:
				stage7.SetTopLeft(-448 + (SIZE_X - stage7.Width()) / 2, SIZE_Y / 4);
				stage7.ShowBitmap();
				stage8Inv.SetTopLeft((SIZE_X - stage8Inv.Width()) / 2, SIZE_Y / 4);
				stage8Inv.ShowBitmap();
				stage9.SetTopLeft(448 + (SIZE_X - stage9.Width()) / 2, SIZE_Y / 4);
				stage9.ShowBitmap();
				break;
			case 9:
				stage8.SetTopLeft(-448 + (SIZE_X - stage8.Width()) / 2, SIZE_Y / 4);
				stage8.ShowBitmap();
				stage9Inv.SetTopLeft((SIZE_X - stage9Inv.Width()) / 2, SIZE_Y / 4);
				stage9Inv.ShowBitmap();
				stage10.SetTopLeft(448 + (SIZE_X - stage10.Width()) / 2, SIZE_Y / 4);
				stage10.ShowBitmap();
				break;
			case 10:
				stage9.SetTopLeft(-448 + (SIZE_X - stage9.Width()) / 2, SIZE_Y / 4);
				stage9.ShowBitmap();
				stage10Inv.SetTopLeft((SIZE_X - stage10Inv.Width()) / 2, SIZE_Y / 4);
				stage10Inv.ShowBitmap();
				stage11.SetTopLeft(448 + (SIZE_X - stage11.Width()) / 2, SIZE_Y / 4);
				stage11.ShowBitmap();
				break;
			case 11:
				stage10.SetTopLeft(-448 + (SIZE_X - stage10.Width()) / 2, SIZE_Y / 4);
				stage10.ShowBitmap();
				stage11Inv.SetTopLeft((SIZE_X - stage11Inv.Width()) / 2, SIZE_Y / 4);
				stage11Inv.ShowBitmap();
				stage12.SetTopLeft(448 + (SIZE_X - stage12.Width()) / 2, SIZE_Y / 4);
				stage12.ShowBitmap();
				break;
			case 12:
				stage11.SetTopLeft(-448 + (SIZE_X - stage11.Width()) / 2, SIZE_Y / 4);
				stage11.ShowBitmap();
				stage12Inv.SetTopLeft((SIZE_X - stage12Inv.Width()) / 2, SIZE_Y / 4);
				stage12Inv.ShowBitmap();
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
	chooseMenu = 0;
}

void CGameStateOver::OnMove()
{
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	chooseStage.LoadBitmap(IDB_CHOOSESTAGE, RGB(255, 255, 255));
	chooseStageInv.LoadBitmap(IDB_CHOOSESTAGEINV, RGB(255, 255, 255));
	exit.LoadBitmap(IDB_EXIT, RGB(255, 255, 255));
	exitInv.LoadBitmap(IDB_EXITINV, RGB(255, 255, 255));
	nextStage.LoadBitmap(IDB_NEXTSTAGE, RGB(255, 255, 255));
	nextStageInv.LoadBitmap(IDB_NEXTSTAGEINV, RGB(255, 255, 255));

	sign.LoadBitmap(IDB_SIGN, RGB(255, 255, 255));

	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';

	if (nChar == KEY_UP && chooseMenu > 1) {
		chooseMenu = chooseMenu - 1;
	}

	if (nChar == KEY_DOWN && chooseMenu < 3) {
		chooseMenu = chooseMenu + 1;
	}

	if (nChar == KEY_SPACE) {
		switch (chooseMenu)
		{
		case 1: // �U�@��
			GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
			break;
		case 2: // ������d
			initStage = true;
			GotoGameState(GAME_STATE_INIT);						// ������GAME_STATE_INIT
			break;
		case 3: // 
			initStage = false;
			newStage = 1;
			GotoGameState(GAME_STATE_INIT);						// ������GAME_STATE_INIT
			break;
		default:
			break;
		}
	}
}

void CGameStateOver::OnShow()
{
	nextStage.SetTopLeft(600, 100);
	nextStageInv.SetTopLeft(600, 100);
	chooseStage.SetTopLeft(600, 300);
	chooseStageInv.SetTopLeft(600, 300);
	exit.SetTopLeft(600, 500);
	exitInv.SetTopLeft(600, 500);
	sign.SetTopLeft(75, 75);

	switch (chooseMenu)
	{
	case 1:
		if (newStage != 13) {	// 12 + 1
			nextStageInv.ShowBitmap();
		}
		chooseStage.ShowBitmap();
		exit.ShowBitmap();
		break;
	case 2:
		if (newStage != 13) {
			nextStage.ShowBitmap();
		}
		chooseStageInv.ShowBitmap();
		exit.ShowBitmap();
		break;
	case 3:
		if (newStage != 13) {
			nextStage.ShowBitmap();
		}
		chooseStage.ShowBitmap();
		exitInv.ShowBitmap();
		break;
	default:
		if (newStage != 13) {
			nextStage.ShowBitmap();
		}
		chooseStage.ShowBitmap();
		exit.ShowBitmap();
		break;
	}

	sign.ShowBitmap();
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
	whichMap = 1;
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	whichMap = newStage;

	switch (whichMap)
	{
	case 1:
		SetObjectPosition(gamemap1);
		break;
	case 2:
		SetObjectPosition(gamemap2);
		break;
	case 3:
		SetObjectPosition(gamemap3);
		break;
	case 4:
		SetObjectPosition(gamemap4);
		break;
	case 5:
		SetObjectPosition(gamemap5);
		break;
	case 6:
		SetObjectPosition(gamemap6);
		break;
	case 7:
		SetObjectPosition(gamemap7);
		break;
	case 8:
		SetObjectPosition(gamemap8);
		break;
	case 9:
		SetObjectPosition(gamemap9);
		break;
	case 10:
		SetObjectPosition(gamemap10);
		break;
	case 11:
		SetObjectPosition(gamemap11);
		break;
	case 12:
		SetObjectPosition(gamemap12);
		break;
	default:
		break;
	}
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// ���ʭI���Ϫ��y��
	//

	man.OnMove();
	
	switch (whichMap) {
	case 1:
		CheckManHitBox(gamemap1);
		CheckManHitWall(gamemap1);
		if (CheckWin(gamemap1)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 2:
		CheckManHitBox(gamemap2);
		CheckManHitWall(gamemap2);
		if (CheckWin(gamemap2)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 3:
		CheckManHitBox(gamemap3);
		CheckManHitWall(gamemap3);
		if (CheckWin(gamemap3)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 4:
		CheckManHitBox(gamemap4);
		CheckManHitWall(gamemap4);
		if (CheckWin(gamemap4)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 5:
		CheckManHitBox(gamemap5);
		CheckManHitWall(gamemap5);
		if (CheckWin(gamemap5)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 6:
		CheckManHitBox(gamemap6);
		CheckManHitWall(gamemap6);
		if (CheckWin(gamemap6)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 7:
		CheckManHitBox(gamemap7);
		CheckManHitWall(gamemap7);
		if (CheckWin(gamemap7)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 8:
		CheckManHitBox(gamemap8);
		CheckManHitWall(gamemap8);
		if (CheckWin(gamemap8)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 9:
		CheckManHitBox(gamemap9);
		CheckManHitWall(gamemap9);
		if (CheckWin(gamemap9)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 10:
		CheckManHitBox(gamemap10);
		CheckManHitWall(gamemap10);
		if (CheckWin(gamemap10)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 11:
		CheckManHitBox(gamemap11);
		CheckManHitWall(gamemap11);
		if (CheckWin(gamemap11)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	case 12:
		CheckManHitBox(gamemap12);
		CheckManHitWall(gamemap12);
		if (CheckWin(gamemap12)) {
			newStage = ++whichMap;
			GotoGameState(GAME_STATE_OVER);
		}
		break;
	default:
		break;
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	background.LoadBitmap(IDB_BACKGROUND2);
	man.LoadBitmap();
	for (int i = 0; i < 8; i++) {
		box[i].LoadBitmap();
	}
	gamemap1.LoadBitmap();
	gamemap2.LoadBitmap();
	gamemap3.LoadBitmap();
	gamemap4.LoadBitmap();
	gamemap5.LoadBitmap();
	gamemap6.LoadBitmap();
	gamemap7.LoadBitmap();
	gamemap8.LoadBitmap();
	gamemap9.LoadBitmap();
	gamemap10.LoadBitmap();
	gamemap11.LoadBitmap();
	gamemap12.LoadBitmap();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_RESET = 0x52; // R ��

	if (nChar == KEY_RESET) {
		OnBeginState();
	}

	if (nChar == KEY_LEFT) {
		man.SetMovingLeft(true);
		man.SetMovingRight(false);
		man.SetMovingUp(false);
		man.SetMovingDown(false);
	}
	if (nChar == KEY_RIGHT) {
		man.SetMovingLeft(false);
		man.SetMovingRight(true);
		man.SetMovingUp(false);
		man.SetMovingDown(false);
	}
	if (nChar == KEY_UP) {
		man.SetMovingLeft(false);
		man.SetMovingRight(false);
		man.SetMovingUp(true);
		man.SetMovingDown(false);
	}
	if (nChar == KEY_DOWN) {
		man.SetMovingLeft(false);
		man.SetMovingRight(false);
		man.SetMovingUp(false);
		man.SetMovingDown(true);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y

	if (nChar == KEY_LEFT) {
		man.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {
		man.SetMovingRight(false);
	}
	if (nChar == KEY_UP) {
		man.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN) {
		man.SetMovingDown(false);
	}
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//

	background.SetTopLeft(0, 0);
	background.ShowBitmap();

	switch (whichMap){
	case 1:
		gamemap1.OnShow();
		for (int i = 0; i < gamemap1.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 2:
		gamemap2.OnShow();
		for (int i = 0; i < gamemap2.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 3:
		gamemap3.OnShow();
		for (int i = 0; i < gamemap3.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 4:
		gamemap4.OnShow();
		for (int i = 0; i < gamemap4.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 5:
		gamemap5.OnShow();
		for (int i = 0; i < gamemap5.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 6:
		gamemap6.OnShow();
		for (int i = 0; i < gamemap6.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 7:
		gamemap7.OnShow();
		for (int i = 0; i < gamemap7.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 8:
		gamemap8.OnShow();
		for (int i = 0; i < gamemap8.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 9:
		gamemap9.OnShow();
		for (int i = 0; i < gamemap9.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 10:
		gamemap10.OnShow();
		for (int i = 0; i < gamemap10.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 11:
		gamemap11.OnShow();
		for (int i = 0; i < gamemap11.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	case 12:
		gamemap12.OnShow();
		for (int i = 0; i < gamemap12.GetChestNumber(); i++) {
			box[i].OnShow();
		}
		man.OnShow();
		break;
	default:
		break;
	}
}

// �o�̥u�O�]�w��m�A���i�Hshow
void CGameStateRun::SetObjectPosition(Map gameMap) {
	int count = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			switch (gameMap.GetPosition(i * 64, j * 64)) {
			case 3:
				box[count].SetX1Y1(i * 64, j * 64);
				count++;
				break;
			case 4:
				man.SetX1Y1(i * 64, j * 64);
				break;
			default:
				break;
			}
		}
	}
}

void CGameStateRun::CheckManHitWall(Map gameMap) {
	// ���W�A�k�W�A���U�A�k�U
	gameMap.hitWall(man.GetX1() + 5, man.GetY1() + 5, man.GetX2() - 5, man.GetY2() - 5);
	bool* hitDirection = gameMap.checkHitWall;

	if (hitDirection[0] && hitDirection[2]) { // ���W�B���U �� OK
		man.SetX1Y1((man.GetX1() / 64 + 1) * 64, man.GetY1());
	}
	if (hitDirection[1] && hitDirection[3]) { // �k�W�B�k�U �� OK
		man.SetX2Y2(man.GetX2() / 64 * 64, man.GetY2());
	}
	if (hitDirection[0] && hitDirection[1]) { // ���W�B�k�W �� OK
		man.SetX1Y1(man.GetX1(), (man.GetY1() / 64 + 1) * 64);
	}
	if (hitDirection[2] && hitDirection[3]) { // ���U�B�k�U �� OK
		man.SetX2Y2(man.GetX2(), man.GetY2() / 64 * 64);
	}
}

void CGameStateRun::CheckManHitBox(Map gameMap) {
	// (�¹諸��V�� ���I��) �B (�c�l�I�� �� �I�c�l) => �H���U�B�]�w��m
	for (int i = 0; i < gameMap.GetChestNumber(); i++) {
		// �W�B�U�B���B�k
		man.HitBox(&box[i]);
		bool* manHitBoxDirection = man.checkHitBox;
		// ���W�A�k�W�A���U�A�k�U
		gameMap.hitWall(box[i].GetX1() + 5, box[i].GetY1() + 5, box[i].GetX2() - 5, box[i].GetY2() - 5);
		bool* boxHitWallDirection = gameMap.checkHitWall;

		if (manHitBoxDirection[0]) {		// �q�W��  OK
			for (int j = 0; j < gameMap.GetChestNumber(); j++) {
				if (i == j) {
					continue;
				}
				if (boxHitWallDirection[2] || boxHitWallDirection[3] || box[i].HitBox(&box[j])) {	// �ӽc�l�I�� �� �I�c�l
					man.SetMovingDown(false);
					box[i].SetX2Y2(box[i].GetX2(), box[i].GetY2() / 64 * 64);
					man.SetX2Y2(man.GetX2(), box[i].GetY1());
				}
				else {													// �c�l���I�� �� ���I�c�l
					box[i].SetX1Y1(box[i].GetX1(), man.GetY2());
				}
			}

		}
		if (manHitBoxDirection[1]) {		// �q�U�� �̭����@�y +15 ���ӬO�~���~�� ��ɶ��F��
			for (int j = 0; j < gameMap.GetChestNumber(); j++) {
				if (i == j) {
					continue;
				}
				if (boxHitWallDirection[0] || boxHitWallDirection[1] || box[i].HitBox(&box[j])) {	// �ӽc�l�I��
					man.SetMovingUp(false);
					box[i].SetX2Y2(box[i].GetX2(), ((box[i].GetY2() + 15) / 64) * 64);
					man.SetX1Y1(man.GetX1(), box[i].GetY2());
				}
				else {													// �c�l���I��
					box[i].SetX2Y2(box[i].GetX2(), man.GetY1());
				}
			}
		}
		if (manHitBoxDirection[2]) {		// �q����  OK
			for (int j = 0; j < gameMap.GetChestNumber(); j++) {
				if (i == j) {
					continue;
				}
				if (boxHitWallDirection[1] || boxHitWallDirection[3] || box[i].HitBox(&box[j])) {	// �ӽc�l�I��
					man.SetMovingRight(false);
					box[i].SetX2Y2(box[i].GetX2() / 64 * 64, box[i].GetY2());
					man.SetX2Y2(box[i].GetX1(), man.GetY2());
				}
				else {													// �c�l���I��
					box[i].SetX1Y1(man.GetX2(), box[i].GetY1());
				}
			}
		}
		if (manHitBoxDirection[3]) {		// �q�k�� 
			for (int j = 0; j < gameMap.GetChestNumber(); j++) {
				if (i == j) {
					continue;
				}
				if (boxHitWallDirection[0] || boxHitWallDirection[2] || box[i].HitBox(&box[j])) {	// �ӽc�l�I��
					man.SetMovingLeft(false);
					box[i].SetX1Y1((box[i].GetX1() + 15) / 64 * 64, box[i].GetY1());
					man.SetX1Y1(box[i].GetX2(), man.GetY1());
				}
				else {													// �c�l���I��
					box[i].SetX2Y2(man.GetX1(), box[i].GetY2());
				}
			}
		}
	}
}

bool CGameStateRun::CheckWin(Map gameMap) {
	for (int i = 0; i < gameMap.GetChestNumber(); i++) {
		if (2 != gameMap.GetPosition(box[i].GetX1() + 32, box[i].GetY1() + 32)) {
			return false;
		}
	}
	// �o�ˤ~���|�d��
	man.SetMovingUp(false);
	man.SetMovingDown(false);
	man.SetMovingLeft(false);
	man.SetMovingRight(false);
	return true;
}
}