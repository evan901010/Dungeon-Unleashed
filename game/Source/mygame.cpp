
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
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		logo.LoadBitmap(IDB_BACKGROUND);
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
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
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
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
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
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
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
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
	picX = picY = 0;
	ball = new CBall [NUMBALLS];
	trap = new Trap[NUMBALLS];
	boss = new Boss[NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
	delete[] trap;
	delete[] boss;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 70;
	const int BALL_XY_OFFSET = 70;
	const int BALL_PER_ROW = 3;
	const int HITS_LEFT = 3;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 10;
	for (int i = 0; i < 6; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);

	}
	const int BOSS_HITS_LEFT = 12;
	const int BOSS_HITS_LEFT_X = 590;
	const int BOSS_HITS_LEFT_Y = 0;
	const int BOSS_X_OFFSET = 300;
	const int BOSS_Y_OFFSET = 100;
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


	eraser.Initialize();
	sword.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{	
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

	c_practice.OnMove();
	if (picX <= SIZE_Y) {
		picX += 1;
		picY += 1;
	}
	else {
		picX = picY = 0;
	}
	practice.SetTopLeft(picX, picY);
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	//

	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// 移動球
	//
	bool temp;
	
		
	//
	// 移動擦子
	//
	eraser.OnMove();
	sword.Setisstop(eraser.Getstop());
	sword.OnMove();

	//
	// 判斷擦子是否碰到球
	//
	for (int i=0; i < NUMBALLS; i++){
		if (ball[i].IsAlive() && ball[i].HitCSword(&sword)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_SWORD_HIT);

		}
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
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

	

	int x_pos = 1;
	int y_pos = 1;
					// 指定剩下的撞擊數
	for (int i = 0; i < 1; i++) {

		if (boss[i].IsAlive() && boss[i].HitCSword(&sword)) {
			boss[i].SetIsAlive(true);
			CAudio::Instance()->Play(AUDIO_SWORD_HIT);
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
	sword.SetXY(eraser.GetX1(), eraser.GetY1());
	
	//
	// 移動彈跳的球
	//
	for (int i = 0; i < NUMBALLS; i++) {
		temp = 0;
		for (int j = 0; j < NUMBALLS; j++) {
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

	for (int i = 0; i < NUMBALLS; i++) {
		temp = 0;
		for (int j = 0; j < NUMBALLS; j++) {
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
	map.OnMove();
	orc.OnMove();
	for (int i = 0; i < 2; i++) {
		trap[i].OnMove();
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	c_practice.LoadBitmap();
	practice.LoadBitmap("RES\\bitmap3.bmp");
	boss_blood1.LoadBitmap("Bitmaps/boss_blood1.bmp", RGB(0,0,0));
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
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	int i;
	for (i = 0; i < NUMBALLS; i++) {
		ball[i].LoadBitmap();
		trap[i].LoadBitmap();
		boss[i].LoadBitmap();
	}
									// 載入第i個球的圖形
		
	eraser.LoadBitmap();
	sword.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
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
	const char ROLL = 0x42;
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
	map.OnShow();	// 貼上彈跳的球

	
	

	for (int i = 0; i < 2; i++) {
		trap[i].OnShow();				// 貼上第i號球
	}

	for (int i = 0; i < 1; i++) {
			boss[i].OnShow();
		
						// 貼上第i號球
	}

	for (int i = 0; i < NUMBALLS; i++) {
		ball[i].OnShow();				// 貼上第i號球
	}

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