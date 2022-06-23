namespace game_framework {

	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int	Getstop();
		int n;
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetRoll(bool flag);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetClick(bool flag);
		
	protected:
		CAnimation runr;
		CAnimation runl;
		CAnimation stopr;
		CAnimation stopl;
		CAnimation swordr;
		CAnimation swordl;
		CAnimation rolll;
		CAnimation rollr;
		int x, y;					// ���l���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isRolling;
		bool isClick;
		int isrun,isstop;		//�O�_�b�]��
		int top, down, lift, right;
	};
}