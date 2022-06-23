#include "CSword.h"
namespace game_framework {
	class CBall
	{
	public:
		CBall();
		bool HitEraser(CEraser *eraser);						
		bool HitCSword(CSword *sword);
		bool HitOthers(CBall *ball);
		bool IsAlive();		
		CAnimation runr;
		CAnimation runl;
		void LoadBitmap();		
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void OnMove();											// ����
		void OnShow();											
		void SetXY(int nx, int ny);								
		void SetIsAlive(bool alive);							
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
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		int isrun;
		int x, y;					
		int x1, y1;
		int dx, dy;					
		int inx, iny;
		int index;					
		int delay_counter;			
		int delay;					
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}