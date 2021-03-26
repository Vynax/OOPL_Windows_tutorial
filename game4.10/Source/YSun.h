
namespace game_framework {
	
	class YSun
	{
	public:
		YSun();
		void OnLButtonDown(UINT nFlags, CPoint point);
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetY(int y);
		int  GetX();
		int  GetY();
		int	 GetFloor();
	private:
		CMovingBitmap sun;
		int x, y;
		bool is_alive;
		CAnimation sunanimation;	// �Q�ΰʵe�@�ϧ�
		int floor;					// where sun stop
	};
}