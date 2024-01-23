//==========================================
//
//  �G�l�~�[�}�l�[�W��(enemymanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

//==========================================
//  �O���錾
//==========================================
class CEnemy;

//==========================================
//  �N���X��`
//==========================================
class CEnemyManager
{
public:

	// �����o�֐�
	CEnemyManager();
	~CEnemyManager();

	void Init();
	void Uninit();
	void Update();
	void Load(); // �f�[�^�̓ǂݍ��ݏ���

	// �ÓI�����o�֐�
	static CEnemyManager* Create(); // ��������

private:

	// �������\����
	struct Info
	{
		D3DXVECTOR3 pos;
		int type;
	};

	// �����o�ϐ� 
	Info* m_pInfo; // �ݒu���
	CEnemy* m_pBoss; // �{�X�̃|�C���^
	bool m_bPopFrag; // �{�X�̏o���t���O

};

#endif
