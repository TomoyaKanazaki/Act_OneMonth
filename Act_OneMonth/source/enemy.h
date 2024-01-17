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
		LANTERN = 0, //�ʏ�̓G
		MAX,
		NONE
	};

	//�����o�֐�
	CEnemy(int nPriority = 5);
	~CEnemy();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//�ÓI�����o�֐�
	static CEnemy* Create(D3DXVECTOR3 pos, CEnemy::TYPE type);

protected:

	//�����o�֐�
	void RotateToMove(); // �ړ�����������
	void RotateToPlayer(); // �v���C���[������

private:

	//�����o�ϐ�
	CEnemy::TYPE m_type;
	D3DXVECTOR3 m_posCenter; // �����ڂ̒��S

};

#endif
