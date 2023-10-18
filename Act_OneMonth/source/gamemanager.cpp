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
#include "map_cube.h"
#include "ui.h"
#include "enemy.h"
#include "field.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CPlayer *CGameManager::m_pPlayer = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CUi* CGameManager::m_pUi = NULL;
CGameManager::State CGameManager::m_State = NONE;

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{
	
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
	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	CEnemy::Create(D3DXVECTOR3(150.0f, 0.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), CEnemy::NORMAL);

	//床の生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1500.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f));

	////床の生成
	//CMap_Cube::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	//UIの生成
#ifdef _DEBUG
	if (m_pUi == NULL)
	{
		m_pUi = new CUi;
		m_pUi->Init();
	}
#endif

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

	//UIの終了
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		delete m_pUi;
	}

	//BGMの停止
	CManager::GetManager()->GetManager()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CGameManager::Update(void)
{
#if _DEBUG
	//画面遷移テスト
	if (CManager::GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetManager()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}

	//画面遷移テスト
	//if (CEnemy::GetNum() == 0)
	//{
	//	CManager::GetManager()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	//	return;
	//}

#endif

	//状態の切り替え
	if (CManager::GetManager()->GetJoyPad()->GetLTRT(CJoyPad::BUTTON_LT, 100))
	{
		m_State = STATE_CONCENTRTTE;
	}
	else
	{
		m_State = STATE_NORMAL;
	}

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//UIの更新
	if (m_pUi != NULL)
	{
		m_pUi->Update();
	}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{
	//UIの更新
	if (m_pUi != NULL)
	{
		m_pUi->Draw();
	}
}
