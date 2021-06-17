namespace game_framework {
	class Character {
	public:
		Character();
		void HitBox(Box *chest);
		void OnMove();
		void OnShow();
		void LoadBitmap();				// 載入圖形
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetX1Y1(int x, int y);		// 設定左上角 xy 座標
		void SetX2Y2(int x, int y);		// 設定右下角 xy 座標
		int  GetX1();					// character左上角 x 座標
		int  GetY1();					// character左上角 y 座標
		int  GetX2();					// character右下角 x 座標
		int  GetY2();					// character右下角 y 座標

		bool checkHitBox[4];			// 哪裡撞箱子的陣列
	protected:
		CAnimation up, down, left, right;		// 人物移動的animation
		CMovingBitmap chara;		// 載入人物圖像
		int x1, y1;					// 左上座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}