namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// ��� 
	//
	// box ���ӭn�g�b map ��?
	// ���D�O�c�l�٤����A�ٻݭn���D�O"�X���c�l"
	/////////////////////////////////////////////////////////////////////////////

	class Box
	{
	public:
		Box();
		void LoadBitmap();
		void OnMove(Map* map);
		void OnShow();
		bool isOnGoal();
		void setIsOnGoal(Map* map);
		void setBoxNumber(int num);
		int getBoxNumber();
		void SetXY(int nx, int ny);
		int getX();
		int getY();
		void setLeftIs(int type);
		void setRightIs(int type);
		void setUpIs(int type);
		void setDownIs(int type);
		int getLeftIs();
		int getRightIs();
		int getUpIs();
		int getDownIs();

	protected:
		CMovingBitmap box;
		int x, y;					// �c�l���W���y��
		bool onGoal;				// �b���I�W?
		int boxNumber;				// �X���c�l
		int leftIs, rightIs, upIs, downIs;	// �c�l�W�U���k���O�O�ƻ�
	};
}