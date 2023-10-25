//==========================================
//
//  �q�b�g�}�[�J�[(marker.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MARKER_H_
#define _MARKER_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CMarker : public CObject3D
{
public:

	//�����o�֐�
	CMarker(int nPriority = 6); //�R���X�g���N�^
	~CMarker(); //�f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CMarker* Create(const D3DXVECTOR3 pos);

private:

	//�ÓI�����o�ϐ�
	static const D3DXVECTOR3 mc_size;

};

#endif
