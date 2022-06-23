#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "orc.h"
#include "trap.h"
#include "Boss.h"
#include "Chest.h"
#include "Demon.h"
namespace game_framework {
	enum AUDIO_ID {				
		AUDIO_DING,				
		AUDIO_LAKE,				
		AUDIO_NTUT,			
		AUDIO_SWORD_HIT	,	
		AUDIO_BOSS_HIT,
		AUDIO_BOSS_BATTLE,
		AUDIO_CHEST,
		AUDIO_DIE,
		AUDIO_END
	};
	class CGameStateInit : public CGameState{
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								
		void OnBeginState();							
		void OnKeyUp(UINT, UINT, UINT); 			
		void OnLButtonDown(UINT nFlags, CPoint point); 
	protected:
		void OnShow();									
	private:
		CMovingBitmap logo;								
	};
	class CPractice {
	public:
		CPractice();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int x, y;
	};
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void newlevel();
		void OnBeginState();							
		void OnInit();  								
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int upkey, downkey, leftkey, rightkey, enemyconst, demonconst, totalenemy, totalboss, totaltrap, totalchest, totaldemon,onekey,twokey,threekey,fourkey;
		int level;
		CPractice c_practice;
		CMovingBitmap pratice;
		int picX, picY;
		CMovingBitmap practice;
		const int		NUMBALLS;	
		CMovingBitmap	background;	
		CMovingBitmap	help;		
		CBall			*ball;		
		CMovingBitmap	corner;		
		CEraser			eraser;		
		CSword			sword;
		Trap *trap;
		Chest *chest;
		CGamemap   map;		
		orc orc;
		Boss *boss;
		Demon *demon;
		CMovingBitmap boss_blood1;
		CMovingBitmap boss_blood2;
		CMovingBitmap boss_blood3;
		CMovingBitmap boss_blood4;
		CMovingBitmap boss_blood5;
		CMovingBitmap boss_blood6;
		CMovingBitmap boss_blood7;
		CMovingBitmap boss_blood8;
		CMovingBitmap boss_blood9;
		CMovingBitmap boss_blood10;
		CMovingBitmap boss_blood11;
		CMovingBitmap boss_blood12;
		CMovingBitmap background1;
		CMovingBitmap background2;
		CMovingBitmap background3;
		CMovingBitmap direction;
		CMovingBitmap name1;
		CMovingBitmap name2;
		CMovingBitmap name3;
		CMovingBitmap orc_1;
		CMovingBitmap orc_2;
		CMovingBitmap orc_3;
		CMovingBitmap demon_5;
		CMovingBitmap demon_4;
		CMovingBitmap demon_3;
		CMovingBitmap demon_2;
		CMovingBitmap demon_1;
		CInteger boss_blood;
	};
	class CGameStateOver : public CGameState{
	
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							
		void OnInit();
	protected:
		void OnMove();									
		void OnShow();									
	private:
		int counter;	
		CMovingBitmap end_1;
		CMovingBitmap end_2;
		CMovingBitmap end_3;
		CMovingBitmap end_4;
		CMovingBitmap end_5;

		CMovingBitmap die_1;
		CMovingBitmap die_2;
		CMovingBitmap die_3;
		CMovingBitmap die_4;
		CMovingBitmap die_5;

	};


}