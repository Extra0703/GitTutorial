/*
 * mygame.h: ���ɮ��x�C��������class��interface
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
// �ѦҤ��̡Aeraser�M�߲��ʡAball�ӧP�_���S������A��mygame�A�B�zonmove
// �bbox�g�I��H���Acharacter�M�߲��ʡAmap�P�_�L�̦��S������(�Mball�@�˼g�k)
// �`���A���n�g�W�U���k���O�Oԣ��method
// character�M�߲��ʡAbox�ghitBox(�^��bool)�MhitCharacter(�^�Ǧ����̼���)�Amap�ghitWall(�^��bool)
/////////////////////////////////////////////////////////////////////////////
// map�t�dOnShow()�A�����]�wbox�Mcharacter���y�СA������P�_
/////////////////////////////////////////////////////////////////////////////

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////


	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1e
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap homepage;							// �ܮw�f
		CMovingBitmap background;						// �I���c�l
		CMovingBitmap menu;								// ���1
		CMovingBitmap menuInv;							// ���2
		CMovingBitmap play;								// �C��1
		CMovingBitmap playInv;							// �C��2
		CMovingBitmap helpText1;

		CMovingBitmap stage1;							// ���d1
		CMovingBitmap stage1Inv;
		CMovingBitmap stage2;							// ���d2
		CMovingBitmap stage2Inv;
		CMovingBitmap stage3;							// ���d3
		CMovingBitmap stage3Inv;
		CMovingBitmap stage4;							// ���d4
		CMovingBitmap stage4Inv;
		CMovingBitmap stage5;							// ���d5
		CMovingBitmap stage5Inv;
		CMovingBitmap stage6;							// ���d6
		CMovingBitmap stage6Inv;
		CMovingBitmap stage7;							// ���d7
		CMovingBitmap stage7Inv;
		CMovingBitmap stage8;							// ���d8
		CMovingBitmap stage8Inv;
		CMovingBitmap stage9;							// ���d9
		CMovingBitmap stage9Inv;
		CMovingBitmap stage10;							// ���d10
		CMovingBitmap stage10Inv;
		CMovingBitmap stage11;							// ���d11
		CMovingBitmap stage11Inv;
		CMovingBitmap stage12;							// ���d12
		CMovingBitmap stage12Inv;

		int chooseMenu;									// �ثe�O����� ���ﶵ
		int chooseStage;								// �ثe�O����� ���d
		bool inChooseStage;								// ������d��
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		void SetObjectPosition(Map gameMap);			// �̾ڤ��P�a�ϡA�]�w�c�l�M�H�������m
		void CheckManHitWall(Map gameMap);				// �̾ڤ��P�a�ϡA�P�_�H�����S������
		void CheckManHitBox(Map gameMap);				// �̾ڤ��P�a�ϡA�P�_�H�����S�����c�l
		bool CheckWin(Map gameMap);						// �P�_�Ӧa�Ͻc�l���S�����b���I�W
		CMovingBitmap background;						// �թ��I��
		Character man;									// �H������
		Box box[8];										// �c�l����
		Map1 gamemap1;									// �a�Ϫ���
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

		// �U���������n��
		int whichMap;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LDown���ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		int chooseMenu;		// �����

		CMovingBitmap chooseStage;						// �^�h�����d
		CMovingBitmap chooseStageInv;
		CMovingBitmap exit;								// ��^�D���
		CMovingBitmap exitInv;
		CMovingBitmap nextStage;						// �h�U�@��
		CMovingBitmap nextStageInv;

		CMovingBitmap sign;								// ���߹L��
	};

}