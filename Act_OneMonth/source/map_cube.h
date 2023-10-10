//==========================================
//
//  ��{�̃u���b�N�N���X(map_cube.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MAP_CUBE_H_
#define _MAP_CUBE_H_
#include "object.h"
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;

//==========================================
//  �N���X��`
//==========================================
class CMap_Cube : public CObject
{
public:

	//�����o�֐�
	CMap_Cube();
	~CMap_Cube();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CMap_Cube* Create(D3DXVECTOR3 pos);

private:

	//�����o�ϐ�

	//���f�����
	CModel** m_ppModel; //���f�����
	CLayer::LAYERDATA* m_pLayer; //�K�w�\�����

};

#endif
