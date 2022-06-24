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
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void OnMove();											// 移動
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
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		int isrun;
		int x, y;					
		int x1, y1;
		int dx, dy;					
		int inx, iny;
		int index;					
		int delay_counter;			
		int delay;					
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}