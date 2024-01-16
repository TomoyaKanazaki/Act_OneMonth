//==========================================
//
//  �a���G�t�F�N�g�N���X(slice.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SLICE_H_
#define _SLICE_H_
#include "object3D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CSlice : public CObject3D_Anim
{
public:

	//�����o�֐�
	CSlice(int nPriority = 6); //�R���X�g���N�^
	~CSlice(); //�f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CSlice* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, bool bRandRot = false);

private:

	//�����o�ϐ�

};

#endif
