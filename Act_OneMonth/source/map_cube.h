//==========================================
//
//  基本のブロッククラス(map_cube.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MAP_CUBE_H_
#define _MAP_CUBE_H_
#include "object.h"
#include "layer.h"

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  クラス定義
//==========================================
class CMap_Cube : public CObject
{
public:

	//メンバ関数
	CMap_Cube();
	~CMap_Cube();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CMap_Cube* Create(D3DXVECTOR3 pos);

private:

	//メンバ変数

	//モデル情報
	CModel** m_ppModel; //モデル情報
	CLayer::LAYERDATA* m_pLayer; //階層構造情報

};

#endif
