#pragma once
#include "CSword.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѷ|�@���u�����y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class orc
	{
	public:
		orc();
		void LoadBitmap();		// ���J�ϧ�
		CAnimation runr;
		CAnimation runl;
		void OnMove();			// ����
		void OnShow();			// �N�ϧζK��e��
	private:
		int x, y;// �ϧήy��
		int level;//�ĴX��
		int n;//��n�i�I��
		int map[3][3];
		int isrun;
		CAnimation animation;	// �Q�ΰʵe�@�ϧ�
	};
}