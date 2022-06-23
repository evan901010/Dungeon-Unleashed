#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}
	void CGameStateInit::OnInit()
	{
		logo.LoadBitmap(IDB_BACKGROUND);
	}
	CPractice::CPractice()
	{
		x = y = 0;
	}
	void CPractice::OnMove()
	{
		if (y <= SIZE_Y){
			x += 3;
			x += 3;
		}
		else {
			x = y = 0;
		}
	}
	void CPractice::LoadBitmap() {
		pic.LoadBitmap(IDB_BITMAP2);
	}
	void CPractice::OnShow()
	{
		pic.SetTopLeft(x, y);
		pic.ShowBitmap();
	}
void CGameStateInit::OnBeginState()
{
}
void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}
void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}
void CGameStateInit::OnShow()
{
	logo.SetTopLeft(0,0);
	logo.ShowBitmap();
			
}								
CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}
void CGameStateOver::OnMove()
{

	end_1.SetTopLeft(0, 0);
	end_2.SetTopLeft(0, 0);
	end_3.SetTopLeft(0, 0);
	end_4.SetTopLeft(0, 0);
	end_5.SetTopLeft(0, 0);

	die_1.SetTopLeft(0, 0);
	die_2.SetTopLeft(0, 0);
	die_3.SetTopLeft(0, 0);
	die_4.SetTopLeft(0, 0);
	die_5.SetTopLeft(0, 0);
	counter--;
	if (counter < 0) {
		GotoGameState(GAME_STATE_INIT);
	}
	CAudio::Instance()->Stop(AUDIO_NTUT);
	CAudio::Instance()->Stop(AUDIO_BOSS_BATTLE);
}
void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
	CAudio::Instance()->Stop(AUDIO_NTUT);
	CAudio::Instance()->Stop(AUDIO_BOSS_BATTLE);
	if (this->game->hits_left.GetInteger() <= 0) {
		CAudio::Instance()->Play(AUDIO_DIE);
	}
	else {
		CAudio::Instance()->Play(AUDIO_END);
	}
}
void CGameStateOver::OnInit()
{
	CAudio::Instance()->Load(AUDIO_DIE, "sounds\\die.mp3");
	CAudio::Instance()->Load(AUDIO_END, "sounds\\end.mp3");
	end_1.LoadBitmap("Bitmaps/end_1.bmp", RGB(0, 0, 0));
	end_2.LoadBitmap("Bitmaps/end_2.bmp", RGB(0, 0, 0));
	end_3.LoadBitmap("Bitmaps/end_3.bmp", RGB(0, 0, 0));
	end_4.LoadBitmap("Bitmaps/end_4.bmp", RGB(0, 0, 0));
	end_5.LoadBitmap("Bitmaps/end_5.bmp", RGB(0, 0, 0));

	die_1.LoadBitmap("Bitmaps/die_1.bmp", RGB(0, 0, 0));
	die_2.LoadBitmap("Bitmaps/die_2.bmp", RGB(0, 0, 0));
	die_3.LoadBitmap("Bitmaps/die_3.bmp", RGB(0, 0, 0));
	die_4.LoadBitmap("Bitmaps/die_4.bmp", RGB(0, 0, 0));
	die_5.LoadBitmap("Bitmaps/die_5.bmp", RGB(0, 0, 0));
}
void CGameStateOver::OnShow()
{
	if (this->game->hits_left.GetInteger() <= 0) {
		
		if (counter >= 120) {
			die_5.ShowBitmap();
		}
		else if (counter >= 90 && counter < 120) {
			die_4.ShowBitmap();
		}
		else if (counter >= 60 && counter < 90) {
			die_3.ShowBitmap();
		}
		else if (counter >= 30 && counter < 60) {
			die_2.ShowBitmap();
		}
		else if (counter < 30) {
			die_1.ShowBitmap();
		}
	}
	else {
		
		if (counter >= 120) {
			end_5.ShowBitmap();
		}
		else if (counter >= 90 && counter < 120) {
			end_4.ShowBitmap();
		}
		else if (counter >= 60 && counter < 90) {
			end_3.ShowBitmap();
		}
		else if (counter >= 30 && counter < 60) {
			end_2.ShowBitmap();
		}
		else if (counter < 30) {
			end_1.ShowBitmap();
		}
	}
				
}


CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(10)
{
	totalenemy = 3;
	totalboss = 1;
	totaltrap = 2;
	totalchest = 1;
	totaldemon = 5;
	picX = picY = 0;
	ball = new CBall [totalenemy];
	trap = new Trap[totaltrap];
	boss = new Boss[totalboss];
	chest = new Chest[totalchest];
	demon = new Demon[totaldemon];
	
}
CGameStateRun::~CGameStateRun()
{
	delete [] ball;
	delete[] trap;
	delete[] boss;
	delete[] chest;
	delete[] demon;
}
void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 70;
	const int BALL_XY_OFFSET = 150;
	const int BALL_PER_ROW = 3;
	const int HITS_LEFT = 3;
	const int HITS_LEFT_X = 0;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 10;
	for (int i = 0; i < 6; i++) {				
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);

	}
	for (int i = 0; i < 5; i++) {				
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		demon[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		demon[i].SetDelay(x_pos);
		demon[i].SetIsAlive(true);

	}
	const int BOSS_HITS_LEFT = 10;
	const int BOSS_HITS_LEFT_X = 590;
	const int BOSS_HITS_LEFT_Y = 0;
	const int BOSS_X_OFFSET = 0;
	const int BOSS_Y_OFFSET = 0;
	boss_blood.SetInteger(BOSS_HITS_LEFT);
	for (int i = 0; i < 1; i++) {				
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		boss[i].SetXY(x_pos * BALL_GAP + BOSS_X_OFFSET, y_pos * BALL_GAP + BOSS_Y_OFFSET);
		boss[i].SetDelay(x_pos);
		boss[i].SetIsAlive(true);

	}
	const int TRAP_GAP = 192;
	const int TRAP_X_OFFSET = 204;
	const int TRAP_Y_OFFSET = 214;
	const int TRAP_PER_ROW = 3;
	for (int i = 0; i < 2; i++) {
		int x_pos = i % TRAP_PER_ROW;
		int y_pos = i / TRAP_PER_ROW;
		trap[i].SetXY(x_pos * TRAP_GAP + TRAP_X_OFFSET, y_pos * TRAP_GAP + TRAP_Y_OFFSET);
		trap[i].SetDelay(x_pos);
		trap[i].SetIsAlive(true);
	}
	const int CHEST_GAP = 192;
	const int CHEST_X_OFFSET = 492;
	const int CHEST_Y_OFFSET = 110;
	const int CHEST_PER_ROW = 3;

	for (int i = 0; i < 1; i++) {
		int x_pos = i % CHEST_PER_ROW;
		int y_pos = i / CHEST_PER_ROW;
		chest[i].SetXY(x_pos * CHEST_GAP + CHEST_X_OFFSET, y_pos *CHEST_GAP + CHEST_Y_OFFSET);
		chest[i].SetDelay(x_pos);
		chest[i].SetIsAlive(true);
	}
	level = 0;
	map.setmap(0);
	eraser.Initialize();
	sword.Initialize();
	background.SetTopLeft(BACKGROUND_X, 0);
	help.SetTopLeft(0, SIZE_Y - help.Height());
	CAudio::Instance()->Play(AUDIO_NTUT, true);
	CAudio::Instance()->Stop(AUDIO_BOSS_BATTLE);
	eraser.Initialize();
	sword.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				
	help.SetTopLeft(100, SIZE_Y - help.Height());			
	this->game->hits_left.SetInteger(HITS_LEFT);
	this->game->hits_left.SetTopLeft(300,100);
	CAudio::Instance()->Play(AUDIO_NTUT, true);		
}
void CGameStateRun::newlevel()
{
	CAudio::Instance()->Play(AUDIO_BOSS_BATTLE);
	level++;
	if (level == 0) {
		CAudio::Instance()->Stop(AUDIO_BOSS_BATTLE);
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 100;
		const int BALL_PER_ROW = 7;
		enemyconst = 3;
		demonconst = 5;
		ball = new CBall[enemyconst];
		for (int i = 0; i < enemyconst; i++)
			ball[i].LoadBitmap();							
		for (int i = 0; i < enemyconst; i++) {				
			int x_pos = i % BALL_PER_ROW;
			int y_pos = i / BALL_PER_ROW;
			ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
			ball[i].SetDelay(x_pos);
			ball[i].SetIsAlive(true);
		}
	}
	eraser.Initialize();
	sword.Initialize();
	map.setmap(level);
	if (level == 1) {
		CAudio::Instance()->Stop(AUDIO_BOSS_BATTLE);
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 100;
		const int BALL_PER_ROW = 7;
		demonconst = 5;
		demon = new Demon[demonconst];
		for (int i = 0; i < demonconst; i++)
			demon[i].LoadBitmap();								
		for (int i = 0; i < demonconst; i++) {				
			int x_pos = i % BALL_PER_ROW;
			int y_pos = i / BALL_PER_ROW;
			demon[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
			demon[i].SetDelay(x_pos);
			demon[i].SetIsAlive(true);
		}
	}
	eraser.Initialize();
	sword.Initialize();
	map.setmap(level);
	if (level == 2) {
		CAudio::Instance()->Stop(AUDIO_NTUT);
		const int BOSS_HITS_LEFT = 12;
		const int BOSS_HITS_LEFT_X = 590;
		const int BOSS_HITS_LEFT_Y = 0;
		const int BOSS_X_OFFSET = 300;
		const int BOSS_Y_OFFSET = 100;
		const int BOSS_PER_ROW = 7;
		const int BOSS_GAP = 7;
		boss_blood.SetInteger(BOSS_HITS_LEFT);
		for (int i = 0; i < 1; i++) {				
			int x_pos = i % BOSS_PER_ROW;
			int y_pos = i / BOSS_PER_ROW;
			boss[i].SetXY(x_pos * BOSS_GAP + BOSS_X_OFFSET, y_pos * BOSS_GAP + BOSS_Y_OFFSET);
			boss[i].SetDelay(x_pos);
			boss[i].SetIsAlive(true);
		}
	}
}
void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (enemyconst == 0 && level == 0) {
		newlevel();
	}
	if (demonconst == 0 && level == 1) {
		newlevel();
	}
	if (boss_blood.GetInteger() <= 0) {
		GotoGameState(GAME_STATE_OVER);
	}
	if (level == 2) {
		background3.SetTopLeft(0, 0);
		name3.SetTopLeft(600, 30);
		boss_blood1.SetTopLeft(594, 70);
		boss_blood2.SetTopLeft(594, 70);
		boss_blood3.SetTopLeft(594, 70);
		boss_blood4.SetTopLeft(594, 70);
		boss_blood5.SetTopLeft(594, 70);
		boss_blood6.SetTopLeft(594, 70);
		boss_blood7.SetTopLeft(594, 70);
		boss_blood8.SetTopLeft(594, 70);
		boss_blood9.SetTopLeft(594, 70);
		boss_blood10.SetTopLeft(594, 70);

	}
	direction.SetTopLeft(600, 220);
	if (level == 0) {
		background1.SetTopLeft(0, 0);
		name1.SetTopLeft(600, 30);
		orc_3.SetTopLeft(600, 70);
		orc_2.SetTopLeft(600, 70);
		orc_1.SetTopLeft(600, 70);
	}
	if (level == 1) {
		background2.SetTopLeft(0, 0);
		name2.SetTopLeft(600, 30);
		demon_5.SetTopLeft(600, 70);
		demon_4.SetTopLeft(600, 70);
		demon_3.SetTopLeft(600, 70);
		demon_2.SetTopLeft(600, 70);
		demon_1.SetTopLeft(600, 70);
	}
	c_practice.OnMove();
	if (picX <= SIZE_Y) {
		picX += 1;
		picY += 1;
	}
	else {
		picX = picY = 0;
	}
	practice.SetTopLeft(picX, picY);
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	bool temp;
	eraser.OnMove();
	sword.Setisstop(eraser.Getstop());
	sword.OnMove();
	if (level == 0) {
		for (int i=0; i < totalenemy; i++){
			if (ball[i].IsAlive() && ball[i].HitCSword(&sword)) {
				enemyconst--;
				ball[i].SetIsAlive(false);
				CAudio::Instance()->Play(AUDIO_SWORD_HIT);
			}
			if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
				enemyconst--;
				ball[i].SetIsAlive(false);
				CAudio::Instance()->Play(AUDIO_DING);
				this->game->hits_left.Add(-1);
				if (this->game->hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	
					CAudio::Instance()->Stop(AUDIO_NTUT);
					GotoGameState(GAME_STATE_OVER);
				}
			}
		}
	}
	if (level == 1) {
		for (int i = 0; i < totaldemon; i++) {
			if (demon[i].IsAlive() && demon[i].HitCSword(&sword)) {
				demonconst--;
				demon[i].SetIsAlive(false);
				CAudio::Instance()->Play(AUDIO_SWORD_HIT);
			}
			if (demon[i].IsAlive() && demon[i].HitEraser(&eraser)) {
				demonconst--;
				demon[i].SetIsAlive(false);
				CAudio::Instance()->Play(AUDIO_DING);
				this->game->hits_left.Add(-1);
				if (this->game->hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	
					CAudio::Instance()->Stop(AUDIO_NTUT);	
					GotoGameState(GAME_STATE_OVER);
				}
			}
		}
	}
	int x_pos = 1;
	int y_pos = 1;
	if (level == 2) {
		for (int i = 0; i < 1; i++) {
			if (boss[i].IsAlive() && boss[i].HitCSword(&sword)) {
				boss[i].SetIsAlive(true);
				CAudio::Instance()->Play(AUDIO_BOSS_HIT);
				boss[i].SetXY(100, 100);
				boss_blood.Add(-1);
				if (boss_blood.GetInteger() <= 0) {
					boss[i].SetIsAlive(false);
				}
			}
			if (boss[i].IsAlive() && boss[i].HitEraser(&eraser)) {
				boss[i].SetIsAlive(true);
				CAudio::Instance()->Play(AUDIO_DING);
				this->game->hits_left.Add(-1);
				boss[i].SetXY(100, 100);
				if (this->game->hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		if (trap[i].IsAlive() && trap[i].HitEraser(&eraser)) {
			trap[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			this->game->hits_left.Add(-1);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (this->game->hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	if (level == 1 || level == 2) {
		for (int i = 0; i < 1; i++) {
			if (chest[i].IsAlive() && chest[i].HitEraser(&eraser)) {
				chest[i].SetIsAlive(false);
				CAudio::Instance()->Play(AUDIO_CHEST);
				this->game->hits_left.Add(+1);
				if (this->game->hits_left.GetInteger() > 3) {
					this->game->hits_left.SetInteger(3);
				}
				if (this->game->hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}
		}
	}
	sword.SetXY(eraser.GetX1(), eraser.GetY1());
	if (level == 0) {
		for (int i = 0; i < totalenemy; i++) {
			temp = 0;
			for (int j = 0; j < totalenemy; j++) {
				if (j != i) {
					if (ball[i].HitOthers(&ball[j])) {
						ball[i].istach();
						temp = 1;
						break;
					}
				}
			}
			if (temp == 0) {
				ball[i].getxy(eraser.GetX1(), eraser.GetY1());
			}
			ball[i].OnMove();

		}
	}
	if (level == 1) {
		for (int i = 0; i < totaldemon; i++) {
			temp = 0;
			for (int j = 0; j < totaldemon; j++) {
				if (j != i) {
					if (demon[i].HitOthers(&demon[j])) {
						demon[i].istach();
						temp = 1;
						break;
					}
				}
			}
			if (temp == 0) {
				demon[i].getxy(eraser.GetX1(), eraser.GetY1());
			}
			demon[i].OnMove();
		}
	}
	if (level == 2) {
		for (int i = 0; i < totalboss; i++) {
				temp = 0;
				for (int j = 0; j < totalboss; j++) {
					if (j != i) {
						if (boss[i].HitOthers(&boss[j])) {
							boss[i].istach();
							temp = 1;
							break;
						}
					}
				}
				if (temp == 0) {
					boss[i].getxy(eraser.GetX1(), eraser.GetY1());
				}
				boss[i].OnMove();
		}
	}
	map.OnMove();
	orc.OnMove();
	for (int i = 0; i < 2; i++) {
		trap[i].OnMove();
	}
	for (int i = 0; i < 1; i++) {
		chest[i].OnMove();
	}
}
void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	c_practice.LoadBitmap();
	level = 0;
	enemyconst = 3;
	demonconst = 5;
	totalenemy = enemyconst;
	map.setmap(level);
	practice.LoadBitmap("RES\\bitmap3.bmp");
	direction.LoadBitmap("Bitmaps/direction.bmp", RGB(0, 0, 0));
	name1.LoadBitmap("Bitmaps/name1.bmp", RGB(0, 0, 0));
	name2.LoadBitmap("Bitmaps/name2.bmp", RGB(0, 0, 0));
	name3.LoadBitmap("Bitmaps/name3.bmp", RGB(0, 0, 0));
	orc_1.LoadBitmap("Bitmaps/orc_1.bmp", RGB(0, 0, 0));
	orc_2.LoadBitmap("Bitmaps/orc_2.bmp", RGB(0, 0, 0));
	orc_3.LoadBitmap("Bitmaps/orc_3.bmp", RGB(0, 0, 0));
	demon_1.LoadBitmap("Bitmaps/demon_1.bmp", RGB(0, 0, 0));
	demon_2.LoadBitmap("Bitmaps/demon_2.bmp", RGB(0, 0, 0));
	demon_3.LoadBitmap("Bitmaps/demon_3.bmp", RGB(0, 0, 0));
	demon_4.LoadBitmap("Bitmaps/demon_4.bmp", RGB(0, 0, 0));
	demon_5.LoadBitmap("Bitmaps/demon_5.bmp", RGB(0, 0, 0));
	background1.LoadBitmap("Bitmaps/background1.bmp");
	background2.LoadBitmap("Bitmaps/background2.bmp");
	background3.LoadBitmap("Bitmaps/background3.bmp");
	boss_blood1.LoadBitmap("Bitmaps/boss_blood1.bmp", RGB(0, 0, 0));
	boss_blood2.LoadBitmap("Bitmaps/boss_blood2.bmp", RGB(0, 0, 0));
	boss_blood3.LoadBitmap("Bitmaps/boss_blood3.bmp", RGB(0, 0, 0));
	boss_blood4.LoadBitmap("Bitmaps/boss_blood4.bmp", RGB(0, 0, 0));
	boss_blood5.LoadBitmap("Bitmaps/boss_blood5.bmp", RGB(0, 0, 0));
	boss_blood6.LoadBitmap("Bitmaps/boss_blood6.bmp", RGB(0, 0, 0));
	boss_blood7.LoadBitmap("Bitmaps/boss_blood7.bmp", RGB(0, 0, 0));
	boss_blood8.LoadBitmap("Bitmaps/boss_blood8.bmp", RGB(0, 0, 0));
	boss_blood9.LoadBitmap("Bitmaps/boss_blood9.bmp", RGB(0, 0, 0));
	boss_blood10.LoadBitmap("Bitmaps/boss_blood10.bmp", RGB(0, 0, 0));

	int i;
	for (i = 0; i < totalenemy; i++) {
		ball[i].LoadBitmap();
	}
	for (i = 0; i < totaldemon; i++) {
		demon[i].LoadBitmap();
	}
	for (i = 0; i < totalboss; i++) {
		boss[i].LoadBitmap();
	}
	for (i = 0; i < totaltrap; i++) {
		trap[i].LoadBitmap();
	}
	for (i = 0; i < totalchest; i++) {
		chest[i].LoadBitmap();
	}
	eraser.LoadBitmap();
	sword.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));			
	corner.LoadBitmap(IDB_CORNER);							
	corner.ShowBitmap(background);							
	map.LoadBitmap();										
	orc.LoadBitmap();
	this->game->hits_left.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mp3");	
	CAudio::Instance()->Load(AUDIO_SWORD_HIT, "sounds\\sword_hit.wav");	
	CAudio::Instance()->Load(AUDIO_BOSS_HIT, "sounds\\boss_hit.wav");
	CAudio::Instance()->Load(AUDIO_BOSS_BATTLE, "sounds\\boss_battle.wav");
	CAudio::Instance()->Load(AUDIO_CHEST, "sounds\\chest.wav");
}
void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_ONE = 0x31;
	const char KEY_TWO = 0x32;
	const char KEY_THREE = 0x33;
	const char KEY_FOUR = 0x34;
	const char ROLL = 0x10;
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(true);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(true);
	if (nChar == ROLL) {
		eraser.SetRoll(true);
	}
	if (nChar == KEY_ONE) {
		level = -1;
		newlevel();
	}
	if (nChar == KEY_TWO) {
		level = 0;
		newlevel();
	}
	if (nChar == KEY_THREE) {
		level = 1;
		newlevel();
	}
	if (nChar == KEY_FOUR) {
		GotoGameState(GAME_STATE_OVER);
	}
}
void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char ROLL = 0x10; //滾
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
	if (nChar == ROLL) {
		eraser.SetRoll(false);
	}
}
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	eraser.SetClick(true);
	sword.SetClick(true);
}
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	eraser.SetClick(false);
	sword.SetClick(false);
}
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	eraser.SetClick(true);
	sword.SetClick(true);
}
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	eraser.SetClick(false);
	sword.SetClick(false);
}
void CGameStateRun::OnShow()
{
	if (level == 0) {
		background1.ShowBitmap();
		name1.ShowBitmap();
		if (enemyconst == 3) {
			orc_3.ShowBitmap();
		}
		else if (enemyconst == 2) {
			orc_2.ShowBitmap();
		}
		else if (enemyconst == 1) {
			orc_1.ShowBitmap();
		}	
	}
	if (level == 1) {
		background2.ShowBitmap();
		name2.ShowBitmap();
		if (demonconst == 5) {
			demon_5.ShowBitmap();
		}
		else if (demonconst == 4) {
			demon_4.ShowBitmap();
		}
		else if (demonconst == 3) {
			demon_3.ShowBitmap();
		}
		else if (demonconst == 2) {
			demon_2.ShowBitmap();
		}
		else if (demonconst == 1) {
			demon_1.ShowBitmap();
		}

	}
	if (level == 2) {
		background3.ShowBitmap();
		name3.ShowBitmap();
	}
	map.OnShow();	
	direction.ShowBitmap();
	if (level != 1) {
		for (int i = 0; i < 2; i++) {
			trap[i].OnShow();				
		}
	}
	if (level == 2) {
		for (int i = 0; i < 1; i++) {
				boss[i].OnShow();
		}
	}
	if (level == 0) {
		for (int i = 0; i < totalenemy; i++) {
			ball[i].OnShow();				
		}
	}
	if (level == 1) {
		for (int i = 0; i < totaldemon; i++) {
			demon[i].OnShow();				
		}
	}
	if (level == 1 || level == 2) {
		for (int i = 0; i < 1; i++) {
			chest[i].OnShow();			
		}
	}
	if (level == 2) {
		if(boss_blood.GetInteger() == 12){
			boss_blood1.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 11) {
			boss_blood2.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 10) {
			boss_blood3.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 9) {
			boss_blood4.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 8) {
			boss_blood5.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 7) {
			boss_blood6.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 6) {
			boss_blood7.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 5) {
			boss_blood8.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 4) {
			boss_blood9.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 3) {
			boss_blood10.ShowBitmap();
		}

	}
	this->game->hits_left.ShowBitmap();
		
	sword.OnShow();
	eraser.OnShow();					
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();



}
}