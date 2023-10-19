//==========================================
//
//  オブジェクトキャラクター(object_char.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_CHAR_H_
#define _OBJECT_CHAR_H_
#include "object.h"
#include "layer.h"

//==========================================
//  前方宣言
//==========================================
class CModel;
class CMotion;

//==========================================
//  クラス定義
//==========================================
class CObject_Char : public CObject
{
public:

	//メンバ関数
	CObject_Char(int nPriority = 4);
	~CObject_Char();

	//メンバ関数
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

protected:

	//メンバ変数
	CModel** m_ppModel; //モデル情報
	CLayer::LAYERDATA* m_pLayer; //階層構造情報
	CMotion* m_pMotion;

private:

	//メンバ変数
	D3DXMATRIX m_mtxWorld;

};

#endif
