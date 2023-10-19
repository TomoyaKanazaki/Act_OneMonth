//==========================================
//
//  �G�N���X(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object_char.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy : public CObject_Char
{
public:

	//�񋓌^��`
	enum TYPE
	{
		NORMAL = 0, //�ʏ�̓G
		MAX,
		NONE
	};

	//�����o�֐�
	CEnemy(int nPriority = 3);
	~CEnemy();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//�ÓI�����o�֐�
	static CEnemy* Create(D3DXVECTOR3 pos, CEnemy::TYPE type);
	static int GetNum(void) { return m_nNum; }

protected:

	//���f�����
	CModel** m_ppModel; //���f�����
	CLayer::LAYERDATA* m_pLayer; //�K�w�\�����
	CMotion* m_pMotion;

private:

	//�����o�ϐ�
	CEnemy::TYPE m_type;

	//�ÓI�����o�ϐ�
	static int m_nNum;

};

#endif
