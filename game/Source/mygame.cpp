
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
	for (int i = 0; i < 6; i++) {				// �]�w�y���_�l�y��
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

	for (int i = 0; i < 1; i++) {				// �]�w�y���_�l�y��
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
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
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
	bool temp;
	
		
	//
	// �������l
	//
	eraser.OnMove();
	sword.Setisstop(eraser.Getstop());
	sword.OnMove();

	//
	// �P�_���l�O�_�I��y
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
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}

	

	int x_pos = 1;
	int y_pos = 1;
					// ���w�ѤU��������
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
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
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
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	sword.SetXY(eraser.GetX1(), eraser.GetY1());
	
	//
	// ���ʼu�����y
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

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	int i;
	for (i = 0; i < NUMBALLS; i++) {
		ball[i].LoadBitmap();
		trap[i].LoadBitmap();
		boss[i].LoadBitmap();
	}
									// ���J��i�Ӳy���ϧ�
		
	eraser.LoadBitmap();
	sword.LoadBitmap();
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
	map.LoadBitmap();										// ���J�ϧ�
	orc.LoadBitmap();
	hits_left.LoadBitmap();	
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mp3");	// ���J�s��2���n��ntut.mid
	CAudio::Instance()->Load(AUDIO_SWORD_HIT, "sounds\\sword_hit.wav");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char ROLL = 0x42; //�u
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetClick(true);
	sword.SetClick(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetClick(false);
	sword.SetClick(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetClick(true);
	sword.SetClick(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetClick(false);
	sword.SetClick(false);
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
	//c_practice.OnShow();
	map.OnShow();	// �K�W�u�����y

	
	

	for (int i = 0; i < 2; i++) {
		trap[i].OnShow();				// �K�W��i���y
	}

	for (int i = 0; i < 1; i++) {
			boss[i].OnShow();
		
						// �K�W��i���y
	}

	for (int i = 0; i < NUMBALLS; i++) {
		ball[i].OnShow();				// �K�W��i���y
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
	eraser.OnShow();					// �K�W���l
	//practice.ShowBitmap();
	//
	//  �K�W���W�Υk�U��������
	//
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();
}
}