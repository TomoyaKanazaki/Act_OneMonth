//==========================================
//
//  ゲームマネージャクラス(gamemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "scene.h"

//==========================================
//  前方宣言
//==========================================
class CPlayer;
class CEnemy;
class CCamera;
class CLight;
class CUi;

//==========================================
//  ゲームマネージャクラス定義
//==========================================
class CGameManager : public CScene
{
public:

	//ゲーム状態
	enum State
	{
		STATE_NORMAL = 0, //通常状態
		STATE_CONCENTRTTE, //集中状態
		STATE_DASH, //ダッシュ状態
		MAX,
		NONE
	};

	CGameManager(); //コンストラクタ
	~CGameManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	

	//静的メンバ関数
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CEnemy* GetEnemy(void) { return m_pBoss; }
	static void KillBoss(void) { m_pBoss = nullptr; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CUi* GetUi(void) { return m_pUi; }
	static State GetState(void) { return m_State; }

private:

	//メンバ変数

	//静的メンバ変数
	static CPlayer* m_pPlayer;
	static CEnemy* m_pBoss;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CUi *m_pUi;
	static State m_State; //ゲームの状態

};

#endif
