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
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
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
	logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
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
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28)
{
	ball = new CBall [NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI

	//numOfBoxInMap[0] = gamemap1.getBoxNum();
	//numOfBoxInMap[1] = gamemap2.getBoxNum();

	int count = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			int flag;
			switch (whichMap){
			case 1:
				flag = gamemap1.getMap(i, j);
				break;
			case 2:
				flag = gamemap2.getMap(i, j);
				break;
			case 3:
				flag = gamemap3.getMap(i, j);
				break;
			default:
				break;
			}
			if (flag == 3) {
				box[count].SetXY(i * 64, j * 64);
				box[count].setBoxNumber(count);
				count++;
			}
			if (flag == 4) {
				man.SetXY(i * 64, j * 64);
			}
		}
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
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// ���ʲy
	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();
	//
	// �������l
	//
	eraser.OnMove();
	//
	// �P�_���l�O�_�I��y
	//
	for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//
	// ���ʼu�����y
	//
	bball.OnMove();

	switch (whichMap) {
	case 1:
		setManLeftIs(&gamemap1);
		setManRightIs(&gamemap1);
		setManUpIs(&gamemap1);
		setManDownIs(&gamemap1);
		for (int i = 0; i < gamemap1.getBoxNum(); i++) {
			setBoxLeftIs(&gamemap1, i);
			setBoxRightIs(&gamemap1, i);
			setBoxUpIs(&gamemap1, i);
			setBoxDownIs(&gamemap1, i);
		}
		break;
	case 2:
		setManLeftIs(&gamemap2);
		setManRightIs(&gamemap2);
		setManUpIs(&gamemap2);
		setManDownIs(&gamemap2);
		for (int i = 0; i < gamemap2.getBoxNum(); i++) {
			setBoxLeftIs(&gamemap2, i);
			setBoxRightIs(&gamemap2, i);
			setBoxUpIs(&gamemap2, i);
			setBoxDownIs(&gamemap2, i);
		}
		break;
	case 3:
		setManLeftIs(&gamemap3);
		setManRightIs(&gamemap3);
		setManUpIs(&gamemap3);
		setManDownIs(&gamemap3);
		for (int i = 0; i < gamemap3.getBoxNum(); i++) {
			setBoxLeftIs(&gamemap3, i);
			setBoxRightIs(&gamemap3, i);
			setBoxUpIs(&gamemap3, i);
			setBoxDownIs(&gamemap3, i);
		}
		break;
	default:
		break;
	}

	/*setManLeftIs(&gamemap1);
	setManRightIs(&gamemap1);
	setManUpIs(&gamemap1);
	setManDownIs(&gamemap1);
	for (int i = 0; i < 4; i++) {
		setBoxLeftIs(&gamemap1, i);
		setBoxRightIs(&gamemap1, i);
		setBoxUpIs(&gamemap1, i);
		setBoxDownIs(&gamemap1, i);
	}*/
	man.OnMove();

	if (checkWin()/* && whichMap != 3*/) { // �i�H�T�w���S��Ĺ�F�A���\��OK
		//Sleep(1000);
		whichMap++;
		OnBeginState();
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	int i;
	for (i = 0; i < NUMBALLS; i++)	
		ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	eraser.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	bball.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//

	gamemap1.LoadBitmap();
	gamemap2.LoadBitmap();
	gamemap3.LoadBitmap();
	for (int i = 0; i < 8; i++) {
		box[i].LoadBitmap();
	}
	man.LoadBitmap();
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
		eraser.SetMovingLeft(true);
		if (3 == man.getLeftIs()) {
			whichBox = boxNumberCheck(man.getX() - 64, man.getY());
			if (3 != box[whichBox].getLeftIs() && 1 != box[whichBox].getLeftIs()) {
				box[whichBox].SetXY(box[whichBox].getX() - 64, box[whichBox].getY());
			}
		}
		man.SetMovingLeft(true);
	}
	if (nChar == KEY_RIGHT) {
		eraser.SetMovingRight(true);
		if (3 == man.getRightIs()) {
			whichBox = boxNumberCheck(man.getX() + 64, man.getY());
			if (3 != box[whichBox].getRightIs() && 1 != box[whichBox].getRightIs()) {
				box[whichBox].SetXY(box[whichBox].getX() + 64, box[whichBox].getY());
			}
		}
		man.SetMovingRight(true);
	}
	if (nChar == KEY_UP) {
		eraser.SetMovingUp(true);
		if (3 == man.getUpIs()) {
			whichBox = boxNumberCheck(man.getX(), man.getY() - 64);
			if (3 != box[whichBox].getUpIs() && 1 != box[whichBox].getUpIs()) {
				box[whichBox].SetXY(box[whichBox].getX(), box[whichBox].getY() - 64);
			}
		}
		man.SetMovingUp(true);
	}
	if (nChar == KEY_DOWN) {
		eraser.SetMovingDown(true);
		if (3 == man.getDownIs()) {
			whichBox = boxNumberCheck(man.getX(), man.getY() + 64);
			if (3 != box[whichBox].getDownIs() && 1 != box[whichBox].getDownIs()) {
				box[whichBox].SetXY(box[whichBox].getX(), box[whichBox].getY() + 64);
			}
		}
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
		eraser.SetMovingLeft(false);
		man.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {
		eraser.SetMovingRight(false);
		man.SetMovingRight(false);
	}
	if (nChar == KEY_UP) {
		eraser.SetMovingUp(false);
		man.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN) {
		eraser.SetMovingDown(false);
		man.SetMovingDown(false);
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	background.ShowBitmap();			// �K�W�I����
	help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();
	for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();				// �K�W��i���y
	bball.OnShow();						// �K�W�u�����y
	eraser.OnShow();					// �K�W���l
	//
	//  �K�W���W�Υk�U��������
	//
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();

	switch (whichMap){
	case 1:
		gamemap1.OnShow();
		for (int i = 0; i < gamemap1.getBoxNum(); i++) {
			box[i].OnShow();
		}
		break;
	case 2:
		gamemap2.OnShow();
		for (int i = 0; i < gamemap2.getBoxNum(); i++) {
			box[i].OnShow();
		}
		break;
	case 3:
		gamemap3.OnShow();
		for (int i = 0; i < gamemap3.getBoxNum(); i++) {
			box[i].OnShow();
		}
		break;
	default:
		break;
	}


	/*gamemap1.OnShow();
	for (int i = 0; i < 5; i++) {
		box[i].OnShow();
	}*/
	man.OnShow();
}

void CGameStateRun::setManLeftIs(Map* map) {
	if (1 == map->getMap(man.getX() / 64 - 1, man.getY() / 64)) {
		man.setLeftIs(1);
	}else if (boxCheck(man.getX() - 64, man.getY())) {
		man.setLeftIs(3);
	}else {
		man.setLeftIs(0);
	}
}

void CGameStateRun::setManRightIs(Map* map) {
	if (1 == map->getMap(man.getX() / 64 + 1, man.getY() / 64)) {
		man.setRightIs(1);
	}else if (boxCheck(man.getX() + 64, man.getY())) {
		man.setRightIs(3);
	}else {
		man.setRightIs(0);
	}
}

void CGameStateRun::setManUpIs(Map* map) {
	if (1 == map->getMap(man.getX() / 64, man.getY() / 64 - 1)) {
		man.setUpIs(1);
	}else if (boxCheck(man.getX(), man.getY() - 64)) {
		man.setUpIs(3);
	}else {
		man.setUpIs(0);
	}
}

void CGameStateRun::setManDownIs(Map* map) {
	if (1 == map->getMap(man.getX() / 64, man.getY() / 64 + 1)) {
		man.setDownIs(1);
	}else if (boxCheck(man.getX(), man.getY() + 64)) {
		man.setDownIs(3);
	}else {
		man.setDownIs(0);
	}
}

void CGameStateRun::setBoxLeftIs(Map* map, int num) {
	if (1 == map->getMap(box[num].getX() / 64 - 1, box[num].getY() / 64)) {
		box[num].setLeftIs(1);
	}
	else if (boxCheck(box[num].getX() - 64, box[num].getY())) {
		box[num].setLeftIs(3);
	}
	else {
		box[num].setLeftIs(0);
	}
}

void CGameStateRun::setBoxRightIs(Map* map, int num) {
	if (1 == map->getMap(box[num].getX() / 64 + 1, box[num].getY() / 64)) {
		box[num].setRightIs(1);
	}
	else if (boxCheck(box[num].getX() + 64, box[num].getY())) {
		box[num].setRightIs(3);
	}
	else {
		box[num].setRightIs(0);
	}
}

void CGameStateRun::setBoxUpIs(Map* map, int num) {
	if (1 == map->getMap(box[num].getX() / 64, box[num].getY() / 64 - 1)) {
		box[num].setUpIs(1);
	}
	else if (boxCheck(box[num].getX(), box[num].getY() - 64)) {
		box[num].setUpIs(3);
	}
	else {
		box[num].setUpIs(0);
	}
}

void CGameStateRun::setBoxDownIs(Map* map, int num) {
	if (1 == map->getMap(box[num].getX() / 64, box[num].getY() / 64 + 1)) {
		box[num].setDownIs(1);
	}
	else if (boxCheck(box[num].getX(), box[num].getY() + 64)) {
		box[num].setDownIs(3);
	}
	else {
		box[num].setDownIs(0);
	}
}

bool CGameStateRun::boxCheck(int boxX, int boxY) {
	for (int i = 0; i < 8; i++) {
		if (box[i].getX() == boxX && box[i].getY() == boxY) {
			return true;
		}
	}
	return false;
}

int CGameStateRun::boxNumberCheck(int boxX, int boxY) {
	for (int i = 0; i < 8; i++) {
		if (box[i].getX() == boxX && box[i].getY() == boxY) {
			return i;
		}
	}
	return 0;
}

bool CGameStateRun::checkWin() {
	switch (whichMap){
	case 1:
		for (int i = 0; i < gamemap1.getBoxNum(); i++) {
			box[i].setIsOnGoal(&gamemap1);
			if (false == box[i].isOnGoal()) {
				return false;
			}
		}
		break;
	case 2:
		for (int i = 0; i < gamemap2.getBoxNum(); i++) {
			box[i].setIsOnGoal(&gamemap2);
			if (false == box[i].isOnGoal()) {
				return false;
			}
		}
		break;
	case 3:
		for (int i = 0; i < gamemap3.getBoxNum(); i++) {
			box[i].setIsOnGoal(&gamemap3);
			if (false == box[i].isOnGoal()) {
				return false;
			}
		}
		break;
	default:
		break;
	}
	/*for (int i = 0; i < 5; i++) {
		box[i].setIsOnGoal(&gamemap1);
		if (false == box[i].isOnGoal()) {
			return false;
		}
	}*/
	return true;
}
}