namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �`���A��W�U���kmethod�R��
	// map�P�_�Ǧ^���x�Φ��S������
	/////////////////////////////////////////////////////////////////////////////

	// �o��class�D�n�O���L���~�ӥ�
	class Map
	{
	public:
		Map();
		void hitWall(int x1, int y1, int x2, int y2);		// �ǤJcharacter��box�����W�M�k�U�y�СA�ݦ��S������
		void OnShow();
		void LoadBitmap();									// ���J�ϧ�
		int GetPosition(int x, int y);
		int GetChestNumber();								// �Ӧa�Ϧ��X�ӽc�l

		bool checkHitWall[4];								// ���̼��𪺰}�C
	protected:
		CMovingBitmap wall, goal;					// �� �M ���I����
		int chestNumber = 1;						// �w�]�c�l�ƶq
		int gameMap[10][15];						// �a��
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