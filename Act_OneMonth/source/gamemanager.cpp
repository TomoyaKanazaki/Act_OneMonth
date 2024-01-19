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
#include "bg.h"
#include "field.h"
#include "gametime.h"
#include "build.h"
#include "tutorial.h"
#include "tutorial_wall.h"
#include "fog.h"
#include "enemy.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CGameManager::m_fDashTime = 0.8f;
CPlayer* CGameManager::m_pPlayer = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CGameManager::State CGameManager::m_State = NONE;
CGameManager::State CGameManager::m_oldState = NONE;
CGameManager::Progress CGameManager::m_Progress = TUTORIAL_ENEMY;
CTutorial* CGameManager::m_pTutorial = nullptr;
CTutorialWall* CGameManager::m_pTutorialWall = nullptr;

//==========================================
//  定数定義
//==========================================
namespace
{
	const float END_FOG = 560.0f;
	const float START_FOG = 150.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{
	m_fTimer = 0.0f;
	m_Progress = TUTORIAL_ENEMY;
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
	// フォグの距離を設定
	Fog::SetStart(START_FOG);
	Fog::SetEnd(END_FOG);

	//状態の初期化
	m_State = STATE_START;

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-2500.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// 敵の生成
	CEnemy::Create(D3DXVECTOR3(-2000.0f, 20.0f, 0.0f), CEnemy::BOSS);

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

	//BGMの再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_GAME);

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

	//チュートリアルを終了
	m_pTutorial = nullptr;

	// カメラの終了
	m_pCamera = NULL;

	// フォグを終了
	Fog::Set(false);

	//BGMの停止
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CGameManager::Update(void)
{
	//前回の状態を保存する
	m_oldState = m_State;

#if _DEBUG
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		CEnemy::Create(D3DXVECTOR3(-2000.0f, 20.0f, 0.0f), CEnemy::LANTERN);
		CEnemy::Create(D3DXVECTOR3(-1900.0f, 20.0f, 0.0f), CEnemy::LANTERN);
		CEnemy::Create(D3DXVECTOR3(-1950.0f, 20.0f, 0.0f), CEnemy::LANTERN);
	}
#endif

	// 状態管理
	TaskState();

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

#ifndef _DEBUG
	//チュートリアルの進行
	TaskTutorial();
#endif

	//リザルトに遷移
	if (m_pPlayer->GetPos().x >= 2300.0f || m_pPlayer->GetDeath())
	{
		if (m_pPlayer->GetDeath())
		{
			CSceneManager::SetClear(false);
		}
		else if (m_pPlayer->GetPos().x >= 2300.0f)
		{
			CSceneManager::SetClear(true);
		}

		// 遷移
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	//画面遷移テスト
	if (CManager::GetInstance()->GetJoyPad()->GetPress(CJoyPad::BUTTON_A))
	{
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}

//==========================================
//  チュートリアル処理
//==========================================
void CGameManager::TaskTutorial()
{

}

//==========================================
//  状態管理の処理
//==========================================
void CGameManager::TaskState()
{
	// ゲームをスタート
	if (m_State == STATE_START && m_pPlayer->GetPos().x >= -2250.0f)
	{
		m_State = STATE_NORMAL;
	}
}
