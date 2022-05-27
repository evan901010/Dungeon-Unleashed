#pragma once
#include "CSword.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供會一直彈跳的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class orc
	{
	public:
		orc();
		void LoadBitmap();		// 載入圖形
		CAnimation runr;
		CAnimation runl;
		void OnMove();			// 移動
		void OnShow();			// 將圖形貼到畫面
	private:
		int x, y;// 圖形座標
		int level;//第幾關
		int n;//第n張背景
		int map[3][3];
		int isrun;
		CAnimation animation;	// 利用動畫作圖形
	};
}