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

#ifndef MYGAME_H
#define MYGAME_H

#include <memory>
#include <vector>
#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "YSun.h"
#include "YCard.h"
#include "YPlants.h"
#include "YMap.h"
#include "YZombies.h"
#include "YCar.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_START,				// 0
		AUDIO_MAIN,
		AUDIO_MENUTOGAME,
		AUDIO_SUNPICK,
		AUDIO_PLANTS,
		AUDIO_CAR
	};

	
	//class CPractice {
	//public:
	//	CPractice();
	//	void LoadBitmap();
	//	void OnMove();
	//	void OnShow();
	//private:
	//	CMovingBitmap pic;
	//	int			  x, y;
	//};
	

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
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		//void OnMouseMove(UINT nFlags, CPoint point);
		//void OnMouseHover(UINT nFlags, CPoint point);
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap	mainmenu;								// mainmenu picture
		CMovingBitmap	loadtext;						// Loading... picture
		CMovingBitmap	adventure0;
		CMovingBitmap	adventure1;
		int				flag_menutogame;
	};


	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѧa�Ϫ��c��
	// �����N�i�H��g�ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	// class CBouncingBall;

	
	//class CGameMap {
	//public:
	//	CGameMap();
	//	void LoadBitmap();			// ���J�a��
	//	void OnShow();				// ��ܦa��
	//	void OnMove();									// ����u���y���ʵe
	//	void OnKeyDown(UINT);							// �B�z������U��CGaneMap������
	//	void RandomBouncingBall();						// �H���u���y���Ӽƥ[�J��Map��
	//	void InitializeBouncingBall(int, int, int);		// ��l�Ƽu���y
	//	~CGameMap();									// �Ѻc�l
	//protected:
	//	CMovingBitmap blue, green;	// �إ��Ŧ�M���a��
	//	//int map[4][5];				// �إߤ@�Ӧa�ϯx�}��index
	//	const int X, Y;				// �j�a�Ϫ����W��x, y�y��
	//	const int MW, MH;			// �C�i�a�Ϫ��e����
	//	CBouncingBall* bballs;		// CBouncingBall����
	//	int random_num;				// �H���Ӽ�
	//};
	

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		friend class YZombies;

		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		// question
		//void setmyMap(int x, int y);
		//bool checkmyMap(int x, int y); // return true if plant are there
		//int  getXmyMapLocation(int x, int y);
		//int  getYmyMapLocation(int x, int y);
		//int	 mymap[9][5];
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		//CGameMap		gamemap;	// �a�� 
		//CPractice		c_practice;	// ���ʪ���
		
		const int		NUMBALLS;	// �y���`��
		CMovingBitmap	background;	// �I����
		
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		CEraser			eraser;		// ��l
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y
		CMovingBitmap	chooser; // practice;
		YShovelCard		shovel_card;
		int				level;
		int				picX, picY;
		int				flag;
		YSun			sun;
		int				sun_amount;			// show on the board
		bool			generateSunFlowerFlag;
		bool			generatePeaShooterFlag;
		bool			generateWallNutFlag;
		bool			shovelFlag;
		YSunFlowerCard  sun_flower_card;
		YPeaShooterCard  pea_shooter_card;
		YWallNutCard  wallnut_card;

		int sun_flower_card_delay_flag;
		int peashooter_card_delay_flag;
		int wallnut_card_delay_flag;

		std::vector<shared_ptr<YSunFlower>>	sunflower_vector;
		std::vector<shared_ptr<YPeaShooter>>	peashooter_vector;
		std::vector<shared_ptr<YWallNut>>	wallnut_vector;

		std::vector<shared_ptr<YNormalZombie>>	normalzombie_vector;

		YMap			map;
		bool			animation_flag;

		YCar car0;
		YCar car1;
		YCar car2;
		YCar car3;
		YCar car4;
		bool car0_flag;
		bool car1_flag;
		bool car2_flag;
		bool car3_flag;
		bool car4_flag;
		bool car0_sound_flag;
		bool car1_sound_flag;
		bool car2_sound_flag;
		bool car3_sound_flag;
		bool car4_sound_flag;
		bool zombie_home_flag;
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
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		CMovingBitmap	loose;

	};


}


#endif