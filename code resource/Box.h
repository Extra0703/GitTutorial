namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �`���A��W�U���k�Oԣ��method�R��
	// �Mball�@�ˡA�g�I��H����method�A�٭n�g�I��box��method
	// OnMove�令��I��H���A�P�_���Wxy�B�k�Uxy�A�O���ӾɭP��(���k�u���A�A�W�U)
	// ���ʪ��j�p�]�w����n�Pcharacter��K��A�p�G�|����
	// �令�P����K��A��character�Pbox��K��
	/////////////////////////////////////////////////////////////////////////////

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