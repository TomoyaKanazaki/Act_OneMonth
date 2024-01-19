//==========================================
//
//  �I�u�W�F�N�g�L�����N�^�[(object_char.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_CHAR_H_
#define _OBJECT_CHAR_H_
#include "object.h"
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CMotion;

//==========================================
//  �N���X��`
//==========================================
class CObject_Char : public CObject
{
public:

	//�����o�֐�
	CObject_Char(int nPriority = 4);
	~CObject_Char();

	//�����o�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

protected:

	//�����o�ϐ�
	CModel** m_ppModel; //���f�����
	CLayer::LAYERDATA* m_pLayer; //�K�w�\�����
	CMotion* m_pMotion;

private:

	//�����o�ϐ�
	D3DXMATRIX m_mtxWorld;
	D3DXCOLOR m_col;

};

#endif
