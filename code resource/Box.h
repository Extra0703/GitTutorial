namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 思路 
	//
	// box 應該要寫在 map 內?
	// 知道是箱子還不夠，還需要知道是"幾號箱子"
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
		int x, y;					// 箱子左上角座標
		bool onGoal;				// 在終點上?
		int boxNumber;				// 幾號箱子
		int leftIs, rightIs, upIs, downIs;	// 箱子上下左右分別是甚麼
	};
}