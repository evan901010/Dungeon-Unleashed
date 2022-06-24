#pragma once

namespace game_framework {


	class CSword
	{
	public:
		CSword();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int n;
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetClick(bool flag);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void Setisstop(int nisstop);		// �]�w���l���W���y��
		void wait();
	protected:
		CAnimation attackl;
		CAnimation attackr;
		CAnimation attackstopl;
		CAnimation attackstopr;
		int x, y;					// ���l���W���y��
		int attack1 ,attack2;
		int isClick;
		int isstop;		
		int time;
	};
}