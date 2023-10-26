//==========================================
//
//  ゲームマネージャクラス(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "manager.h"
#include "sound.h"
#include "player.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"
#include "model.h"
#include "renderer.h"
#include "debugproc.h"
#include "bg.h"
#include "enemy.h"
#include "field.h"
#include "gametime.h"
#include "icon.h"
#include "build.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CGameManager::m_fDashTime = 0.8f;
CPlayer* CGameManager::m_pPlayer = NULL;
CEnemy* CGameManager::m_pBoss = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CGameManager::State CGameManager::m_State = NONE;
CGameManager::State CGameManager::m_oldState = NONE;
CIcon* CGameManager::m_pIcon = nullptr;

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{
	m_fTimer = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CGameManager::Init(void)
{
	//状態の初期化
	m_State = STATE_NORMAL;

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	//ボスの生成
	m_pBoss = CEnemy::Create(D3DXVECTOR3(1000.0f, 30.0f, 0.0f), CEnemy::BOSS_MAIN);

	//雑魚敵の生成
	CEnemy::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(300.0f, 150.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-150.0f, 150.0f, 0.0f), CEnemy::HOMING);

	//建物の生成
	CBuild::Create();

	//背景の生成
	CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 20000.0f), D3DXVECTOR3(60000.0f, 0.0f, 20000.0f), 1);

	//床の生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 6.0f), CFeild::SOIL);
	
	//水の生成
	CFeild::Create(D3DXVECTOR3(0.0f, -3000.0f, 0.0f), D3DXVECTOR3(60000.0f, 0.0f, 60000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CFeild::WATER);

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
		m_pCamera->Init();
	}

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGameManager::Uninit(void)
{
	//ライトの終了、破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	m_pCamera = NULL;

	//BGMの停止
	CManager::GetManager()->GetManager()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CGameManager::Update(void)
{
	//前回の状態を保存する
	m_oldState = m_State;

#if _DEBUG
	//画面遷移テスト
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetManager()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}

#endif

	//状態の切り替え
	if (CManager::GetManager()->GetJoyPad()->GetLTRT(CJoyPad::BUTTON_LT, 100) || CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		if (m_State == STATE_NORMAL)
		{
			m_State = STATE_CONCENTRATE;

			//紋章を召喚
			if (m_pIcon == nullptr)
			{
				D3DXVECTOR3 size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
				m_pIcon = CIcon::Create(size);
			}
		}
	}

	//状態を更新
	if (m_pIcon != nullptr)
	{
		if (m_pIcon->GetLIfe() <= 0.0f && m_State == STATE_CONCENTRATE)
		{
			m_State = STATE_DASH;
			m_pIcon = nullptr;
		}
	}

	//状態を更新
	if (m_State == STATE_DASH)
	{
		if (m_fTimer >= m_fDashTime)
		{
			m_fTimer = 0.0f;
			m_State = STATE_NORMAL;
		}
		m_fTimer += CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();
	}

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//ゲームクリア
	if (m_pBoss == nullptr)
	{
		CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}
