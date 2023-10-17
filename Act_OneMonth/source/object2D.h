//==========================================
//
//  �I�u�W�F�N�g2D�N���X(object2D.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"

//==========================================
//  �I�u�W�F�N�g2D�N���X��`
//==========================================
class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 3); //�R���X�g���N�^
	~CObject2D(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max);
	void SetCol(const D3DXCOLOR col);
	D3DXCOLOR GetCol(void) { return m_col; }
	void AddAlpah(float fDiff);

private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXCOLOR m_col;
	float m_fLength;
	float m_fAngle;
};

#endif