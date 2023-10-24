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
class CIcon;

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
		STATE_CONCENTRATE, //集中状態
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
	static CEnemy* GetBoss(void) { return m_pBoss; }
	static void KillBoss(void) { m_pBoss = nullptr; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static State GetState(void) { return m_State; }
	static State GetOldState(void) { return m_oldState; }
	static CIcon *GetIcon(void) { return m_pIcon; }

private:

	//メンバ変数
	float m_fTimer;

	//静的メンバ変数
	static const float m_fDashTime;
	static CPlayer* m_pPlayer;
	static CEnemy* m_pBoss;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static State m_State; //ゲームの状態
	static State m_oldState; //前フレームでのゲームの状態
	static CIcon *m_pIcon;

};

#endif
