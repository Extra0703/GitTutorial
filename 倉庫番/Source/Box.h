namespace game_framework {
	class Box{
	public:
		Box();
		bool HitBox(Box *box);											// �O�_�I��box
		void OnMove();
		void OnShow();
		void LoadBitmap();				// ���J�ϧ�
		void SetX1Y1(int x, int y);		// �]�w���W�� xy �y��
		void SetX2Y2(int x, int y);		// �]�w�k�U�� xy �y��
		int  GetX1();					// box���W�� x �y��
		int  GetY1();					// box���W�� y �y��
		int  GetX2();					// box�k�U�� x �y��
		int  GetY2();					// box�k�U�� y �y��
	protected:
		CMovingBitmap chest;		// ���J�c�l�Ϲ�
		int x1, y1;					// ���W�y��
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}