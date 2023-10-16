//==========================================
//
//  マップ管理クラス(map.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MAP_H_
#define _MAP_H_
#include "object.h"

//==========================================
//  クラス定義
//==========================================
class CMap
{
public:

	//メンバ関数
	CMap();
	~CMap();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static void Save(void);

private:

	//マップチップ情報
	struct Tips
	{
		D3DXVECTOR3 pos; //座標
		D3DXVECTOR3 rot; //角度
		CObject::TYPE type; //オブジェクトの種類
	};

	//静的メンバ変数
	static Tips m_Tips[2048];

};

#endif
