namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 思路 
	//
	// 960*640
	// 牆壁 64*64，地圖會變成 15*10，二維陣列就是[10][15]
	// wall 是 1, goal 是 2, box 是 3, man 是 4，背景透明
	// 把位置都先排好，這裡的二維陣列的功能就只是 "設定初始位置"
	// 等一下，箱子和人物屬於物件，不應該寫在地圖裡
	//
	// 碰撞到底怎麼用會比較好呢???
	// 到最後肯定是用座標絕對位置判斷有沒有碰牆
	// 碰撞判斷，是隨著人物一同進行的
	// 嘛 未來有時間再改，目前先這樣
	//
	// 現在有兩個問題"不能貼邊走，但不會有穿牆bug"，"可以貼邊走，但會有穿牆bug"
	// 目前調整為後者，之後再找時間把這問題解決
	//
	// 箱子碰牆，人推箱子，箱子不會斜著移動
	/////////////////////////////////////////////////////////////////////////////
	// 我想想哦
	//
	// 目前有三個基本的東西還沒弄出來: 新地圖、換關卡、重製鍵
	// 把地圖都寫出來(用switch可行嗎?)，箱子隨著地圖的不同改變數量，先寫關卡結束的東西吧
	// 是不是換關卡，重製鍵，都是放在 CGameStateRun 裡啊?
	/////////////////////////////////////////////////////////////////////////////
	// 新地圖 (已完成???)
	//
	// 第一個想法是用三維陣列，先試試看
	// 地圖的樣式是OK，但需要把物件重新繪製，把init, run, over，好好想過一遍
	// 我想其他的換關，介面，也是需要把這搞懂
	// 按照老師的建議後，選擇使用了繼承，發現把 mygame.h 的私有成員
	// 直接改成 Map1 gamemap; 一堆有用到 (Map* map) 類似這樣的method 還是可以工作
	// 但是人物繪製似乎有些問題，再看看
	/////////////////////////////////////////////////////////////////////////////
	// 重製鍵 (已完成)
	//
	// 按下R，重製本關，把地圖所有的物件回歸到原本的樣子
	/////////////////////////////////////////////////////////////////////////////
	// 換關卡 (已完成???)
	//
	// 我沒頭緒啦lol
	// 老師說一樣是在 gameStateRun 裡面，就只是把 OnShow() 做些修改而已
	//
	// 實作前的假設:
	// 直接在OnShow()改地圖，但是 人物、箱子，的OnShow()需不需要做些修改
	// 應該說，人物和箱子的位置會不會 改變，還是要重新執行
	//
	// 是可以動作了，可是實在有夠醜，之後再修改lol
	/////////////////////////////////////////////////////////////////////////////
	// 把 map 當作物件，不同的 map 就是不同的物件
	// 寫一個 basicMap class，讓後面的 map1, map2, mapN...繼承他!
	// 感覺會比較簡單，而且串起來後，OnShow() 會變比較精簡
	/////////////////////////////////////////////////////////////////////////////

	class Map
	{
	public:
		Map();
		void LoadBitmap();
		void OnShow();
		int getMap(int x, int y);
		int getBoxNum();
		
	protected:
		CMovingBitmap wall, goal;
		int gameMap[10][15];
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
}