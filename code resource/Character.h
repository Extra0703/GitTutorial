namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// ��� 
	//
	// ���ʨS�ƻ���D�A���O�I���Ӧp��B�z?
	// �g hitWall �M hitBox �Abox �h�n�g hitWall
	// ���S����u�� map ���G���}�C�P�_�|���|�������?
	// �{�b�� x, y ���H 64����ơA�� map �� getMap()�A�o��ثe��m
	// �C�ʤ@�B�e���p��U�@�B����m�A�|���|�O wall 
	// �����ήy�мg�n�F�A�o�ˤ����ı�A�]���²��
	// �]�w�n���W���M�k�U�����y�СA�A�P�_���S������
	//
	// �Q�b SetMovingLeft �̭��� nextStepHitLeftWall �P�_
	// �P�_�٬O�g�� mygame.cpp �n�F
	/////////////////////////////////////////////////////////////////////////////

	class Character {
	public:
		Character();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
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
		int x, y;					// �H�����W�� �y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		int leftIs, rightIs, upIs, downIs;	// �H���W�U���k���O�O�ƻ�
	};
}