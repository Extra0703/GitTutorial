namespace game_framework {
	class Character {
	public:
		Character();
		void HitBox(Box *chest);
		void OnMove();
		void OnShow();
		void LoadBitmap();				// ���J�ϧ�
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetX1Y1(int x, int y);		// �]�w���W�� xy �y��
		void SetX2Y2(int x, int y);		// �]�w�k�U�� xy �y��
		int  GetX1();					// character���W�� x �y��
		int  GetY1();					// character���W�� y �y��
		int  GetX2();					// character�k�U�� x �y��
		int  GetY2();					// character�k�U�� y �y��

		bool checkHitBox[4];			// ���̼��c�l���}�C
	protected:
		CAnimation up, down, left, right;		// �H�����ʪ�animation
		CMovingBitmap chara;		// ���J�H���Ϲ�
		int x1, y1;					// ���W�y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}