namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѷ|�@���u�����y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CGamemap
	{
	public:
		CGamemap();
		void LoadBitmap();		// ���J�ϧ�
		CAnimation all[3];   //�����a��
		void setmap(int in);
		void OnMove();			// ����
		void OnShow();			// �N�ϧζK��e��
	private:
		int x, y;// �ϧήy��
		int level;//�ĴX��
		int n;//��n�i�I��
		int map[3][3];
		CAnimation animation;	// �Q�ΰʵe�@�ϧ�
	};
}