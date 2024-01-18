//==========================================
//
//  �a���G�t�F�N�g(slash.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SLASH_H_
#define _SLASH_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CSlash : public CObject3D
{
public:

	//�����o�֐�
	CSlash(int nPriority = 6);
	~CSlash();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CSlash* Create(const D3DXVECTOR3 pos, const float rot, const D3DXCOLOR col);

private:

	// �����o�֐�
	void Hit();

	// �����o�ϐ�
	D3DXVECTOR3 m_posLeft; // �|���S���̍��[
	D3DXVECTOR3 m_posRight; // �|���S���̉E�[

};

#endif
