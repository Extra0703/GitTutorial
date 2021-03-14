namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 思路 
	//
	// 移動沒甚麼問題，但是碰撞該如何處理?
	// 寫 hitWall 和 hitBox ，box 則要寫 hitWall
	// 有沒有能只用 map 的二維陣列判斷會不會撞到牆啊?
	// 現在的 x, y 除以 64取整數，用 map 的 getMap()，得到目前位置
	// 每動一步前都計算下一步的位置，會不會是 wall 
	// 直接用座標寫好了，這樣比較直覺，也比較簡單
	// 設定好左上角和右下角的座標，再判斷有沒有撞到
	//
	// 想在 SetMovingLeft 裡面做 nextStepHitLeftWall 判斷
	// 判斷還是寫到 mygame.cpp 好了
	/////////////////////////////////////////////////////////////////////////////

	class Character {
	public:
		Character();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
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
		CMovingBitmap man;
		int x, y;					// 人物左上角 座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		int leftIs, rightIs, upIs, downIs;	// 人物上下左右分別是甚麼
	};
}