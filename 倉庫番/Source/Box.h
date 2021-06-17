namespace game_framework {
	class Box{
	public:
		Box();
		bool HitBox(Box *box);											// 是否碰到box
		void OnMove();
		void OnShow();
		void LoadBitmap();				// 載入圖形
		void SetX1Y1(int x, int y);		// 設定左上角 xy 座標
		void SetX2Y2(int x, int y);		// 設定右下角 xy 座標
		int  GetX1();					// box左上角 x 座標
		int  GetY1();					// box左上角 y 座標
		int  GetX2();					// box右下角 x 座標
		int  GetY2();					// box右下角 y 座標
	protected:
		CMovingBitmap chest;		// 載入箱子圖像
		int x1, y1;					// 左上座標
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}