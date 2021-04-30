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
#include <stdlib.h> /* �üƬ������ */
#include <time.h>   /* �ɶ�������� */
#include <string>	// to_string
#include <sstream>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "YMap.h"

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
	flag_menutogame = 0;
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	
	Sleep(300);
	//
	// �}�l���J���
	//
	mainmenu.LoadBitmap("Bitmaps/MainMenu.bmp");
	adventure0.LoadBitmap("Bitmaps/Adventure0.bmp", RGB(255,255,255));
	adventure1.LoadBitmap("Bitmaps/Adventure1.bmp", RGB(255,255,255));
	CAudio::Instance()->Load(AUDIO_MAIN, "sounds\\mainmenu.mp3");
	CAudio::Instance()->Play(AUDIO_MAIN, true);
	CAudio::Instance()->Load(AUDIO_MENUTOGAME, "sounds\\menutogame.mp3");
	CAudio::Instance()->Load(AUDIO_SUNPICK, "sounds\\sun_pick.mp3");
	CAudio::Instance()->Load(AUDIO_PLANTS, "sounds\\plants_sound.mp3");

	Sleep(500);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
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
	//const char KEY_SPACE = ' ';
	//if (nChar == KEY_SPACE)
	//	GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

//void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point) {
//	adventure1.SetTopLeft(470, 100);
//	adventure1.ShowBitmap();
//}

//void CGameStateInit::OnMouseHover(UINT nFlags, CPoint point) {
//	adventure1.SetTopLeft(470, 100);
//	adventure1.ShowBitmap();
//}
void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	

	if (point.x > 470 && point.y > 100 && point.x < 790 && point.y < 260) {
		//adventure1.ShowBitmap();
		flag_menutogame = 1;

		CAudio::Instance()->Play(AUDIO_MENUTOGAME, false);
		//Sleep(6000);

		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	}
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wmainmenu
	//
	mainmenu.SetTopLeft(0,0);
	mainmenu.ShowBitmap();

	adventure0.SetTopLeft(470, 100);
	adventure1.SetTopLeft(470, 100);
	
	if (flag_menutogame == 0) {
		adventure0.ShowBitmap();
	} else {
		adventure1.ShowBitmap();
	}
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(170,"�L�n������");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	// pDC->SetBkColor(RGB(0,0,0));
	pDC->SetBkMode(TRANSPARENT);
	
	pDC->SetTextColor(RGB(0,0,0));
	pDC->TextOut(500, 270, "~ 19XX-XX-XX ~");
	pDC->SetTextColor(RGB(204, 255, 204));
	pDC->TextOut(480,320,"�I�� \"�_�I�Ҧ�\" �}�l !");
	// pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(5,530,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,565,"Press Alt-F4 or ESC to Quit.");
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


	Sleep(100);
	ShowInitProgress(85);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%


	Sleep(100);
	//
	// �}�l���J���
	//
	// Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
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
	picX = picY = 0;
	flag = 0;
	
	// suntry
	sun_amount = 1000;			// �@�}�l50��sun
	sun_interval_time = 5;		// 5 second
	generateSunFlowerFlag = false;
	generatePeaShooterFlag = false;
	sun_flower_card_delay_flag = 0;
	peashooter_card_delay_flag = 0;
	//normalzombie_vector.clear();
	//normalzombie_vector.push_back(YNormalZombie(200, 1));
	//normalzombie_vector.push_back(YNormalZombie(560, 2));
	//normalzombie_vector.push_back(YNormalZombie(250, 1));
	//normalzombie_vector.push_back(YNormalZombie(500, 3));
	//normalzombie_vector.push_back(YNormalZombie(1300, 2));
	//normalzombie_vector.push_back(YNormalZombie(1600, 3));
	//normalzombie_vector.push_back(YNormalZombie(2000, 4));
	//normalzombie_vector.push_back(YNormalZombie(2100, 1));
	//normalzombie_vector.push_back(YNormalZombie(2150, 2));
	//normalzombie_vector.push_back(YNormalZombie(2150, 0));
	//normalzombie_vector.push_back(YNormalZombie(2200, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(200, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(560, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(500, 3));

}


CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	//
	// �}�l���J���
	//
	// practice.LoadBitmap(IDB_SNOWGIEDRAW);
	chooser.LoadBitmap("Bitmaps/ChooserBackground.bmp");
	//gamemap.LoadBitmap();							// ���J�a�Ϫ��ϧ�  //practiceGreenBlue
	//c_practice.LoadBitmap();
	background.LoadBitmap("Bitmaps/Background.bmp");			// ���J�I�����ϧ�
	//shovel.LoadBitmap("Bitmaps/Shovel.bmp");
	shovel_card.LoadBitmap();

/*	int i;
	for (i = 0; i < NUMBALLS; i++)
		ball[i].LoadBitmap();*/								// ���J��i�Ӳy���ϧ�

	eraser.LoadBitmap();

	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	bball.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();
	sun.LoadBitmap();
	sun_flower_card.LoadBitmap();
	pea_shooter_card.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_START, "sounds\\startgame.mp3");	// ���J�s��0���n��ding.wav
	//normalzombie.LoadBitmapA();
	//for (YNormalZombie & normalzombie : normalzombie_vector) {
	//	normalzombie.LoadBitmap();
	//}
	for (auto normalzombie_sp : normalzombie_vector) {
		normalzombie_sp->LoadBitmap();
	}
	car0.LoadBitmap();
	car1.LoadBitmap();
	car2.LoadBitmap();
	car3.LoadBitmap();
	car4.LoadBitmap();

	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 0;
	const int ANIMATION_SPEED = 15;
	//for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
	//	int x_pos = i % BALL_PER_ROW;
	//	int y_pos = i / BALL_PER_ROW;
	//	ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
	//	ball[i].SetDelay(x_pos);
	//	ball[i].SetIsAlive(true);
	//}
	eraser.Initialize();
	//background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Stop(AUDIO_MAIN);
	CAudio::Instance()->Play(AUDIO_START, true);		

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(true);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(true);
	//gamemap.OnKeyDown(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{	
	if (generateSunFlowerFlag && !map.checkmyMap(point.x, point.y) && point.x > 100 && point.x < 840 && point.y>78 && point.y < 571) {
		CAudio::Instance()->Play(AUDIO_PLANTS, false);
		int tx = map.getXmyMapLocation(point.x, point.y);
		int ty = map.getYmyMapLocation(point.x, point.y);
		map.setmyMap(point.x, point.y);

		//YSunFlower sunflower(tx, ty);
		//sunflower.LoadBitmap();
		auto sp = make_shared<YSunFlower>(tx, ty);
		sp->LoadBitmap();
		sunflower_vector.push_back(sp);
		generateSunFlowerFlag = false;
	}
	else if (generatePeaShooterFlag && !map.checkmyMap(point.x, point.y) && point.x >100 && point.x<840 && point.y>78 && point.y < 571) {
		CAudio::Instance()->Play(AUDIO_PLANTS, false);
		int tx = map.getXmyMapLocation(point.x, point.y);
		int ty = map.getYmyMapLocation(point.x, point.y);
		map.setmyMap(point.x, point.y);
		
		//YPeaShooter peashooter(tx, ty);
		//peashooter.LoadBitmap();
		auto sp = make_shared<YPeaShooter>(tx, ty);
		sp->LoadBitmap();
		peashooter_vector.push_back(sp);
		generatePeaShooterFlag = false;
	}

	// suntry
	if (point.x > sun.GetX() - 5 && point.y - 5 > sun.GetY() && point.x < sun.GetX() + 80 && point.y < sun.GetY() + 80 && sun.IsAlive()) {
		CAudio::Instance()->Play(AUDIO_SUNPICK, false);
		sun.SetIsAlive(false);
		sun_amount += 25;
		sun.SetY(-500);
	}
	// sunflowercardtry

	if (point.x > sun_flower_card.GetX() && point.y > sun_flower_card.GetY() && point.x < sun_flower_card.GetX() + 65 && point.y < sun_flower_card.GetY() + 90 && sun_flower_card.IsAlive()) {
		sun_flower_card.SetIsAlive(false);
		sun_amount -= sun_flower_card.GetSunCost();
		generateSunFlowerFlag = true;
		sun_flower_card_delay_flag = 150;

	}
	else if (point.x > pea_shooter_card.GetX() && point.y > pea_shooter_card.GetY() && point.x < pea_shooter_card.GetX() + 65 && point.y < pea_shooter_card.GetY() + 90 && pea_shooter_card.IsAlive()) {
		pea_shooter_card.SetIsAlive(false);
		sun_amount -= pea_shooter_card.GetSunCost();
		generatePeaShooterFlag = true;
		peashooter_card_delay_flag = 150;
	}
	if (sun_flower_card.GetSunCost() > sun_amount) {
		sun_flower_card.SetIsAlive(false);
	}
	else if (pea_shooter_card.GetSunCost() > sun_amount) {
		pea_shooter_card.SetIsAlive(false);
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//c_practice.OnMove();

	chooser.SetTopLeft(0, 0);
	//shovel.SetTopLeft(520, 0);

	//
	// ���ʭI���Ϫ��y��
	//
	if (picX > -400 && flag == 0) {
		picX -= 4;
	}// (-400,0)
	else if (flag == 0) {
		Sleep(1000);
		flag = 1;
	}
	else if (picX < -150) {
		//flag = 1;
		picX += 4;
	}// (-150,0)
	else {
		flag = 2;
		picX = -150;
	}
	background.SetTopLeft(picX, picY);



	// Suntry
	if (flag==2) {
		sun.OnMove();

		if (sun_flower_card_delay_flag > 0) {
			sun_flower_card_delay_flag--;
		}


		if (peashooter_card_delay_flag > 0) {
			peashooter_card_delay_flag--;
		}

		for (auto sf : sunflower_vector) {
			sf->OnMove();
		}
		for (auto ps : peashooter_vector) {
			ps->OnMove();
			
		}
		
		for (size_t i = 0; i < normalzombie_vector.size(); i++) {

			for (size_t j = 0; j < sunflower_vector.size(); j++) {
				if (sunflower_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 90, normalzombie_vector.at(i)->GetY() + 30)) {
					sunflower_vector.at(j)->LostBlood(normalzombie_vector.at(i)->GetAttackPower());
					if (sunflower_vector.at(j)->GetBlood() < 1) {
						sunflower_vector.at(j)->SetIsAlive(false);
						map.unsetmyMap(sunflower_vector.at(j)->GetX(), sunflower_vector.at(j)->GetY());
						sunflower_vector.erase(sunflower_vector.begin() + j);
					}
				}
			}

			if (map.checkmyMap(normalzombie_vector.at(i)->GetX() + 90, normalzombie_vector.at(i)->GetY() + 35) && normalzombie_vector.at(i)->IsAlive()) {
				normalzombie_vector.at(i)->OnMove(std::string("attack"));
			}

			else if (normalzombie_vector.at(i)->IsAlive()) {
				normalzombie_vector.at(i)->OnMove(std::string("walk"));
			}
			else if (!normalzombie_vector.at(i)->IsAlive()) {
				normalzombie_vector.at(i)->OnMove(std::string("die"));
			}

			// zombie walk to car -> car move
			if ((normalzombie_vector.at(i)->GetY() == 48 && normalzombie_vector.at(i)->GetX() < car0.GetX() - 30) || !car0_flag) {
				car0_flag = false;
				car0.OnMove();
			}
			if ((normalzombie_vector.at(i)->GetY() == 152 && normalzombie_vector.at(i)->GetX() < car1.GetX() - 30) || !car1_flag) {
				car1_flag = false;
				car1.OnMove();
			}
			if ((normalzombie_vector.at(i)->GetY() == 240 && normalzombie_vector.at(i)->GetX() < car2.GetX() - 30) || !car2_flag) {
				car2_flag = false;
				car2.OnMove();
			}
			if ((normalzombie_vector.at(i)->GetY() == 338 && normalzombie_vector.at(i)->GetX() < car3.GetX() - 30) || !car3_flag) {
				car3_flag = false;
				car3.OnMove();
			}
			if ((normalzombie_vector.at(i)->GetY() == 434 && normalzombie_vector.at(i)->GetX() < car4.GetX() - 30) || !car4_flag) {
				car4_flag = false;
				car4.OnMove();
			}
			// car hits zombies
			if ((normalzombie_vector.at(i)->GetY() == 48 && normalzombie_vector.at(i)->GetX() < car0.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if ((normalzombie_vector.at(i)->GetY() == 152 && normalzombie_vector.at(i)->GetX() < car1.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if ((normalzombie_vector.at(i)->GetY() == 240 && normalzombie_vector.at(i)->GetX() < car2.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if ((normalzombie_vector.at(i)->GetY() == 338 && normalzombie_vector.at(i)->GetX() < car3.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if ((normalzombie_vector.at(i)->GetY() == 434 && normalzombie_vector.at(i)->GetX() < car4.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			for (auto p : peashooter_vector) {
				int temp_y = map.getYmyMapLocation(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY() + 30);
				if (p->checkBulletCollideWithZombie(normalzombie_vector.at(i)->GetX(), temp_y)) {
					normalzombie_vector.at(i)->LostBlood(1);
				}
			}
			if (normalzombie_vector.at(i)->GetX() > 900 && !normalzombie_vector.at(i)->IsAlive()) {
				normalzombie_vector.erase(normalzombie_vector.begin() + i);
			}

		}
	}

	// sunflowercardtry
	if (sun_amount >= sun_flower_card.GetSunCost() && sun_flower_card_delay_flag == 0) {
		sun_flower_card.SetIsAlive(true);
	}
	if (sun_amount >= pea_shooter_card.GetSunCost() && peashooter_card_delay_flag == 0) {
		pea_shooter_card.SetIsAlive(true);
	}
	
	// go to game state over
	if (normalzombie_vector.empty()) {
		CAudio::Instance()->Stop(AUDIO_START);
		GotoGameState(GAME_STATE_OVER);
	}

	// �ק�cursor�˦�
	//if (generateSunFlowerFlag) {
	//	SetCursor(AfxGetApp()->LoadCursor(".\\bitmaps\\SunFlower\\SunFlower_0.bmp"));
	//}

	// gamemap.OnMove();
	//
	// ���ʲy
	//
	//for (int i = 0; i < NUMBALLS; i++)
	//	ball[i].OnMove();
	//
	// �������l
	//
	//eraser.OnMove();
	//
	// �P�_���l�O�_�I��y
	//
	//for (int i = 0; i < NUMBALLS; i++)
	//	if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
	//		ball[i].SetIsAlive(false);
	//		hits_left.Add(-1);
	//		//
	//		// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
	//		//
	//		if (hits_left.GetInteger() <= 0) {
	//			CAudio::Instance()->Stop(AUDIO_START);
	//			GotoGameState(GAME_STATE_OVER);
	//		}
	//	}
	//
	// ���ʼu�����y
	//
	//bball.OnMove();
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();				// �K�W�I����
	
	//gamemap.OnShow();					// �K�W�a�ϡA�`�N���� //practiceGreenBlue
	//help.ShowBitmap();					// �K�W������
	//hits_left.ShowBitmap();
	
	/* teacher's ball
	for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();				// �K�W��i���y
	bball.OnShow();						// �K�W�u�����y
	eraser.OnShow();					// �K�W���l
	*/

	//
	//  �K�W���W�Υk�U��������
	//
	//corner.SetTopLeft(0,0);
	//corner.ShowBitmap();
	//corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	//corner.ShowBitmap();
	
	if (flag == 2 ) {

		for (size_t i = 0; i < sunflower_vector.size(); i++) {
			sunflower_vector.at(i)->OnShow();
		}
		for (size_t i = 0; i < peashooter_vector.size(); i++) {
			peashooter_vector.at(i)->OnShow();
		}
		for (auto normalzombie : normalzombie_vector) {
			if (normalzombie->GetX() < 950) {
				if (map.checkmyMap(normalzombie->GetX() + 90, normalzombie->GetY() + 35) && normalzombie->IsAlive()) {
					normalzombie->OnShow(std::string("attack"));
				}
				else if (normalzombie->IsAlive()) {
					normalzombie->OnShow(std::string("walk"));
				}
				else if (!normalzombie->IsAlive()) {
					normalzombie->OnShow(std::string("die"));
				}
			}
		}

		sun.OnShow();
		chooser.ShowBitmap();
		shovel_card.OnShow();
		sun_flower_card.OnShow();
		pea_shooter_card.OnShow();
		car0.OnShow();
		car1.OnShow();
		car2.OnShow();
		car3.OnShow();
		car4.OnShow();

	}

	

	// sun amount
	if (flag == 2) {
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(90, "�L�n������");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkMode(TRANSPARENT);

		pDC->SetTextColor(RGB(0, 0, 0));

		if (sun_amount == 50)
			pDC->TextOut(30, 62, "50");
		else if (sun_amount == 0) 
			pDC->TextOut(34, 62, "0");
		else if (sun_amount == 25) 
			pDC->TextOut(30, 62, "25");
		else if (sun_amount == 75) 
			pDC->TextOut(30, 62, "75");
		else if (sun_amount == 100)
			pDC->TextOut(26, 62, "100");
		else if (sun_amount == 125)
			pDC->TextOut(26, 62, "125");
		else if (sun_amount == 150)
			pDC->TextOut(26, 62, "150");
		else if (sun_amount == 175)
			pDC->TextOut(26, 62, "175");
		else if (sun_amount == 200)
			pDC->TextOut(26, 62, "200");
		else if (sun_amount == 225)
			pDC->TextOut(26, 62, "225");
		else if (sun_amount == 250)
			pDC->TextOut(26, 62, "250");
		else if (sun_amount == 275)
			pDC->TextOut(26, 62, "275");
		else if (sun_amount == 300)
			pDC->TextOut(26, 62, "300");
		else if (sun_amount == 325)
			pDC->TextOut(26, 62, "325");
		else if (sun_amount == 350)
			pDC->TextOut(26, 62, "350");
		else if (sun_amount == 375)
			pDC->TextOut(26, 62, "375");
		else if (sun_amount == 400)
			pDC->TextOut(26, 62, "400");
		else if (sun_amount == 425)
			pDC->TextOut(26, 62, "425");
		else if (sun_amount == 450)
			pDC->TextOut(26, 62, "450");
		else if (sun_amount == 475)
			pDC->TextOut(26, 62, "475");
		else if (sun_amount == 500)
			pDC->TextOut(26, 62, "500");
		else {
			pDC->TextOut(26, 62, "###");
		}
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
	
	//c_practice.OnShow();  //practice snowgie
}



//CPractice::CPractice() {
//	x = y = 0;
//}
//
//void CPractice::OnMove() {
//	if (y <= SIZE_Y) {
//		x += 3;
//		y += 3;
//	}
//	else {
//		x = y = 0;
//	}
//}
//
//void CPractice::LoadBitmap() {
//	pic.LoadBitmap(IDB_SNOWGIE);
//}
//
//void CPractice::OnShow() {
//	pic.SetTopLeft(x, y);
//	pic.ShowBitmap();
//}

//CGameMap::CGameMap()
//	:X(20), Y(40), MW(120), MH(100)			// �����a�ϥ��W���y�ФΨC�i�p�ϼe��
//{
//	int map_init[4][5] = { {0, 0, 1, 0, 0},		// �����a�ϰ}�C���
//						  {0, 1, 2, 1, 0},
//						  {1, 2, 1, 2, 1},
//						  {2, 1, 2, 1, 2} };
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 5; j++) {
//			map[i][j] = map_init[i][j];		// �̧Ƕ�Jmap��
//		}
//	}
//	random_num = 0;
//	bballs = NULL;
//}
//
//void CGameMap::LoadBitmap() {
//	blue.LoadBitmap(IDB_BLUE);
//	green.LoadBitmap(IDB_GREEN);
//}
//
//void CGameMap::OnShow() {
//	for (int i = 0; i < 5; i++) {			// ���k��ܤ��i��
//		for (int j = 0; j < 4; j++) {		// ���U��ܥ|�i��
//			switch (map[j][i]) {
//				case 0:
//					break;
//				case 1:
//					blue.SetTopLeft(X + (MW*i), Y + (MH*j));	// �]�w�C�i�Ϫ��y��
//					blue.ShowBitmap();							// ��ܳ]�w�����y��
//					break;
//				case 2:
//					green.SetTopLeft(X + (MW*i), Y + (MH*j));	// �]�w�C�i�Ϫ��y��
//					green.ShowBitmap();							// ��ܳ]�w�����y��
//					break;
//				default:
//					ASSERT(0);									// map�}�C���ӥX�{0, 1, 2 ���~����
//			}
//	
//		}
//	}
//	for (int i = 0; i < random_num; i++)
//	{	
//		bballs[i].OnShow();
//	}
//}

void CBouncingBall::SetXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void CBouncingBall::SetFloor(int floor) {
	this->floor = floor;
}

void CBouncingBall::SetVelocity(int velocity) {
	this->velocity = velocity;
	this->initial_velocity = velocity;
}

//void CGameMap::InitializeBouncingBall(int ini_index, int row, int col) {
//	const int VELOCITY = 10;							// �y���_�l�W�ɰ���	
//	const int BALL_PIC_HEIGHT = 15;						// �y�Ϥ�������
//	int floor = Y + (row + 1)*MH - BALL_PIC_HEIGHT;		// �]�w�y�����U�I��Map���U��
//
//	bballs[ini_index].LoadBitmap();						// ���J�u���y���ʵe
//	bballs[ini_index].SetFloor(floor);					// �]�w�u���y���_�l������
//	bballs[ini_index].SetVelocity(VELOCITY+col);		// �]�w�u���y����l�t�סA�V�k�䪺�u�V��
//	bballs[ini_index].SetXY(X+col*MW + MW/2, floor);	// �]�w�u���y���_�l��mX�y�Ь���Map�@�b����m
//}
//
//void CGameMap::RandomBouncingBall() {
//	const int MAX_RAND_NUM = 10;
//	random_num = (rand() % MAX_RAND_NUM) + 1;			// �H��1~MAX_RAND_NUM
//
//	delete[] bballs;													// ���R�����e�Ұt�m���Ŷ�
//	bballs = new CBouncingBall[random_num];				// �ʺA�t�mCBouncingBall �}�C
//	int ini_index = 0;								
//	for (int row = 0; row < 4; row++) {
//		for (int col = 0; col < 5; col++) {
//			if (map[row][col] != 0 && ini_index < random_num) {		// �u��y�b���⪺�a�ϥB��l�ƪ��}�C���ޥ��p���H�����Ӽ�
//				InitializeBouncingBall(ini_index, row, col);
//				ini_index++;										
//			}
//		}
//	}
//}
//
//void CGameMap::OnKeyDown(UINT nChar) {
//	const int KEY_SPACE = 0x20;
//	if (nChar == KEY_SPACE)
//		RandomBouncingBall();	// ��ť�����U���H���u���y
//}
//
//void CGameMap::OnMove() {
//	for (int i = 0; i < random_num; i++) {
//		bballs[i].OnMove();
//	}
//}
//
//CGameMap::~CGameMap() {
//	delete[] bballs;
//}

}