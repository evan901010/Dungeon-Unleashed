#pragma once
#include "CSword.h"
namespace game_framework {
	class Trap
	{
	public:
		Trap();
		bool HitEraser(CEraser *eraser);						
		bool HitCSword(CSword *sword);
		bool HitOthers(Trap *ball);
		bool IsAlive();
		CAnimation run;
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetDelay(int d);									
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
		CMovingBitmap bmp;			
		CMovingBitmap bmp_center;	
		int x, y;					
		int x1, y1;
		int dx, dy;					
		int inx, iny;
		int index;					
		int delay_counter;			// �վ����t�ת��p�ƾ�
		int delay;					// ���઺�t��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}
