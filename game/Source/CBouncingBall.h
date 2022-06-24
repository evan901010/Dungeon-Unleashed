namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供會一直彈跳的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CGamemap
	{
	public:
		CGamemap();
		void LoadBitmap();		// 載入圖形
		CAnimation all[3];   //全部地圖
		void setmap(int in);
		void OnMove();			// 移動
		void OnShow();			// 將圖形貼到畫面
	private:
		int x, y;// 圖形座標
		int level;//第幾關
		int n;//第n張背景
		int map[3][3];
		CAnimation animation;	// 利用動畫作圖形
	};
}