#pragma once

namespace game_framework {


	class CSword
	{
	public:
		CSword();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		int n;
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetClick(bool flag);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void Setisstop(int nisstop);		// 設定擦子左上角座標

	protected:
		CAnimation attackl;
		CAnimation attackr;
		int x, y;					// 擦子左上角座標
		int attack1 ,attack2;
		bool isClick;
		int isstop;		
	};
}