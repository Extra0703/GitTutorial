namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 總之，把上下左右method刪掉
	// map判斷傳回的矩形有沒有撞牆
	/////////////////////////////////////////////////////////////////////////////

	// 這個class主要是給他們繼承用
	class Map
	{
	public:
		Map();
		void hitWall(int x1, int y1, int x2, int y2);		// 傳入character或box的左上和右下座標，看有沒有撞牆
		void OnShow();
		void LoadBitmap();									// 載入圖形
		int GetPosition(int x, int y);
		int GetChestNumber();								// 該地圖有幾個箱子

		bool checkHitWall[4];								// 哪裡撞牆的陣列
	protected:
		CMovingBitmap wall, goal;					// 牆 和 終點的圖
		int chestNumber = 1;						// 預設箱子數量
		int gameMap[10][15];						// 地圖
	};

	class Map1 : public Map {
	public:
		Map1();
	};

	class Map2 : public Map {
	public:
		Map2();
	};

	class Map3 : public Map {
	public:
		Map3();
	};

	class Map4 : public Map {
	public:
		Map4();
	};

	class Map5 : public Map {
	public:
		Map5();
	};

	class Map6 : public Map {
	public:
		Map6();
	};

	class Map7 : public Map {
	public:
		Map7();
	};

	class Map8 : public Map {
	public:
		Map8();
	};

	class Map9 : public Map {
	public:
		Map9();
	};

	class Map10 : public Map {
	public:
		Map10();
	};

	class Map11 : public Map {
	public:
		Map11();
	};

	class Map12 : public Map {
	public:
		Map12();
	};
}