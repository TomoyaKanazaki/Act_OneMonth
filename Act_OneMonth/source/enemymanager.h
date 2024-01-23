//==========================================
//
//  エネミーマネージャ(enemymanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

//==========================================
//  前方宣言
//==========================================
class CEnemy;

//==========================================
//  クラス定義
//==========================================
class CEnemyManager
{
public:

	// メンバ関数
	CEnemyManager();
	~CEnemyManager();

	void Init();
	void Uninit();
	void Update();
	void Load(); // データの読み込み処理

	// 静的メンバ関数
	static CEnemyManager* Create(); // 生成処理

private:

	// 生成情報構造体
	struct Info
	{
		D3DXVECTOR3 pos;
		int type;
	};

	// メンバ変数 
	Info* m_pInfo; // 設置情報
	CEnemy* m_pBoss; // ボスのポインタ
	bool m_bPopFrag; // ボスの出現フラグ

};

#endif
