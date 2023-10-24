//==========================================
//
//  ��̓N���X(icon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ICON_H_
#define _ICON_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CIcon : CObject3D
{
public:

	//�����o�֐�
	CIcon(int nPriority = 7);
	~CIcon();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	float GetLIfe(void) { return m_fLife; }

	//�ÓI�����o�֐�
	static CIcon* Create(D3DXVECTOR3 size);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_Default;
	float m_fLife;

	//�ÓI�����o�ϐ�
	static const float m_fMaxLife;

};

#endif
