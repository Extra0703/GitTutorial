namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 總之，把上下左右是啥的method刪掉
	// 和ball一樣，寫碰到人物的method，還要寫碰到box的method
	// OnMove改成當碰到人物，判斷左上xy、右下xy，是哪個導致的(左右優先，再上下)
	// 移動的大小設定成剛好與character邊貼邊，如果會撞牆
	// 改成與牆邊貼邊，而character與box邊貼邊
	/////////////////////////////////////////////////////////////////////////////

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