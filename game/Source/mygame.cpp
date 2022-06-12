#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{

		//
		logo.LoadBitmap(IDB_BACKGROUND);
					// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
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
	//
	// 貼上logo
	//
	logo.SetTopLeft(0,0);
	logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
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

}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

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
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 100;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 10;
	for (int i = 0; i < 6; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);

	}

	for (int i = 0; i < 5; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		demon[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		demon[i].SetDelay(x_pos);
		demon[i].SetIsAlive(true);

	}

	const int BOSS_HITS_LEFT = 12;
	const int BOSS_HITS_LEFT_X = 590;
	const int BOSS_HITS_LEFT_Y = 0;
	const int BOSS_X_OFFSET = 0;
	const int BOSS_Y_OFFSET = 0;
	boss_blood.SetInteger(BOSS_HITS_LEFT);

	for (int i = 0; i < 1; i++) {				// 設定球的起始座標
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

	eraser.Initialize();
	sword.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				
	help.SetTopLeft(0, SIZE_Y - help.Height());			
	hits_left.SetInteger(HITS_LEFT);					
	hits_left.SetTopLeft(500,500);		
	CAudio::Instance()->Play(AUDIO_NTUT, true);		
}
void CGameStateRun::newlevel()
{

	level++;
	if (level == 0) {
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		enemyconst = 3;
		demonconst = 5;
		ball = new CBall[enemyconst];
		for (int i = 0; i < enemyconst; i++)
			ball[i].LoadBitmap();								// 載入第i個球的圖形
		for (int i = 0; i < enemyconst; i++) {				// 設定球的起始座標
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
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		demonconst = 5;
		demon = new Demon[demonconst];
		for (int i = 0; i < demonconst; i++)
			demon[i].LoadBitmap();								// 載入第i個球的圖形
		for (int i = 0; i < demonconst; i++) {				// 設定球的起始座標
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
		CAudio::Instance()->Play(AUDIO_BOSS_BATTLE);
		const int BOSS_HITS_LEFT = 12;
		const int BOSS_HITS_LEFT_X = 590;
		const int BOSS_HITS_LEFT_Y = 0;
		const int BOSS_X_OFFSET = 300;
		const int BOSS_Y_OFFSET = 100;
		const int BOSS_PER_ROW = 7;
		const int BOSS_GAP = 7;
		boss_blood.SetInteger(BOSS_HITS_LEFT);

		for (int i = 0; i < 1; i++) {				// 設定球的起始座標
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
		boss_blood1.SetTopLeft(100, 550);
		boss_blood2.SetTopLeft(100, 550);
		boss_blood3.SetTopLeft(100, 550);
		boss_blood4.SetTopLeft(100, 550);
		boss_blood5.SetTopLeft(100, 550);
		boss_blood6.SetTopLeft(100, 550);
		boss_blood7.SetTopLeft(100, 550);
		boss_blood8.SetTopLeft(100, 550);
		boss_blood9.SetTopLeft(100, 550);
		boss_blood10.SetTopLeft(100, 550);
		boss_blood11.SetTopLeft(100, 550);
		boss_blood12.SetTopLeft(100, 550);
	}

	direction.SetTopLeft(600, 220);

	if (level == 0) {
		background1.SetTopLeft(0, 0);
		name1.SetTopLeft(600, 30);
		orc_3.SetTopLeft(650, 80);
		orc_2.SetTopLeft(650, 80);
		orc_1.SetTopLeft(650, 80);
	}

	if (level == 1) {
		background2.SetTopLeft(0, 0);
		name2.SetTopLeft(600, 30);
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
	//
	// 移動球
	//
	bool temp;
	
	eraser.OnMove();
	sword.Setisstop(eraser.Getstop());
	sword.OnMove();

	//
	// 判斷擦子是否碰到球
	//

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
				hits_left.Add(-1);
				//
				// 若剩餘碰撞次數為0，則跳到Game Over狀態
				//
				if (hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
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
				hits_left.Add(-1);
				//
				// 若剩餘碰撞次數為0，則跳到Game Over狀態
				//
				if (hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}
		}
	}

	int x_pos = 1;
	int y_pos = 1;
					// 指定剩下的撞擊數
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
				hits_left.Add(-1);
				boss[i].SetXY(100, 100);
			
			
				//
				// 若剩餘碰撞次數為0，則跳到Game Over狀態
				//
				if (hits_left.GetInteger() <= 0) {
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
			hits_left.Add(-1);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_left.GetInteger() <= 0) {
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
				hits_left.Add(+1);
				if (hits_left.GetInteger() > 3) {
					hits_left.SetInteger(3);
				}
				//
				// 若剩餘碰撞次數為0，則跳到Game Over狀態
				//
				if (hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}
		}
	}
	sword.SetXY(eraser.GetX1(), eraser.GetY1());
	
	//
	// 移動彈跳的球
	//
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
	boss_blood11.LoadBitmap("Bitmaps/boss_blood11.bmp", RGB(0, 0, 0));
	boss_blood12.LoadBitmap("Bitmaps/boss_blood12.bmp", RGB(0, 0, 0));

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
									// 載入第i個球的圖形
		
	eraser.LoadBitmap();
	sword.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形

	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	map.LoadBitmap();										// 載入圖形
	orc.LoadBitmap();
	hits_left.LoadBitmap();	
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mp3");	// 載入編號2的聲音ntut.mid
	CAudio::Instance()->Load(AUDIO_SWORD_HIT, "sounds\\sword_hit.wav");	// 載入編號2的聲音ntut.mid
	CAudio::Instance()->Load(AUDIO_BOSS_HIT, "sounds\\boss_hit.wav");
	CAudio::Instance()->Load(AUDIO_BOSS_BATTLE, "sounds\\boss_battle.wav");
	CAudio::Instance()->Load(AUDIO_CHEST, "sounds\\chest.wav");

	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
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
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char ROLL = 0x42; //滾
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
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
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
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	//c_practice.OnShow();
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
	}

	if (level == 2) {
		background3.ShowBitmap();
		name3.ShowBitmap();
	}
	map.OnShow();	// 貼上彈跳的球

	

	direction.ShowBitmap();
	if (level != 1) {
		for (int i = 0; i < 2; i++) {
			trap[i].OnShow();				// 貼上第i號球
		}
	}

	if (level == 2) {

		for (int i = 0; i < 1; i++) {
				boss[i].OnShow();
								// 貼上第i號球
		}
	}
	
	if (level == 0) {
		for (int i = 0; i < totalenemy; i++) {
			ball[i].OnShow();				// 貼上第i號球
		}
	}

	if (level == 1) {
		for (int i = 0; i < totaldemon; i++) {
			demon[i].OnShow();				// 貼上第i號球
		}
	}

	if (level == 1 || level == 2) {
		for (int i = 0; i < 1; i++) {
			chest[i].OnShow();				// 貼上第i號球
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
		else if (boss_blood.GetInteger() == 2) {
			boss_blood11.ShowBitmap();
		}
		else if (boss_blood.GetInteger() == 1) {
			boss_blood12.ShowBitmap();
		}
	}

		
	
	hits_left.ShowBitmap();
		
	sword.OnShow();
	eraser.OnShow();					// 貼上擦子
	//practice.ShowBitmap();
	//
	//  貼上左上及右下角落的圖
	//
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();
}
}