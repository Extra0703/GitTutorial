namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// ��� 
	//
	// 960*640
	// ��� 64*64�A�a�Ϸ|�ܦ� 15*10�A�G���}�C�N�O[10][15]
	// wall �O 1, goal �O 2, box �O 3, man �O 4�A�I���z��
	// ���m�����Ʀn�A�o�̪��G���}�C���\��N�u�O "�]�w��l��m"
	// ���@�U�A�c�l�M�H���ݩ󪫥�A�����Ӽg�b�a�ϸ�
	//
	// �I���쩳���η|����n�O???
	// ��̫�֩w�O�ήy�е����m�P�_���S���I��
	// �I���P�_�A�O�H�ۤH���@�P�i�檺
	// �� ���Ӧ��ɶ��A��A�ثe���o��
	//
	// �{�b����Ӱ��D"����K�䨫�A�����|������bug"�A"�i�H�K�䨫�A���|������bug"
	// �ثe�վ㬰��̡A����A��ɶ���o���D�ѨM
	//
	// �c�l�I��A�H���c�l�A�c�l���|�׵۲���
	/////////////////////////////////////////////////////////////////////////////

	class Map
	{
	public:
		Map();
		void LoadBitmap();
		void OnShow();
		int getMap(int x, int y);
		
	protected:
		CMovingBitmap wall, goal;
		int gameMap[10][15];
	};
}