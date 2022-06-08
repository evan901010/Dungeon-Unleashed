#pragma once

#include "CSword.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Boss
	{
	public:
		Boss();
		bool HitEraser(CEraser *eraser);						// �O�_�I�����l
		bool HitCSword(CSword *sword);
		bool HitOthers(Boss *ball);
		bool IsAlive();
		bool IsAttack();
		CAnimation run;
		CAnimation attack;
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetDelay(int d);									// �]�w���઺�t��
		void getxy(int x2, int y2);
		void forward();
		void back();
		void istach();
		int GetX1();
		int GetX2();
		int GetY1();
		int GetY2();
		bool ittouch;
	protected:
		CMovingBitmap bmp;			// �y����
		CMovingBitmap bmp_center;	// ��ߪ���			
		int x, y;					// ��ߪ��y��
		int x1, y1;
		int dx, dy;					// �y�Z����ߪ��첾�q
		int inx, iny;
		int index;					// �y���u���סv�A0-17���0-360��
		int delay_counter;			// �վ����t�ת��p�ƾ�
		int delay;					// ���઺�t��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}