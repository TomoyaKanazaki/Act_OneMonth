//==========================================
//
//  ターゲットクラス(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "renderer.h"
#include "gamemanager.h"
#include "player.h"
#include "texture.h"
#include "input.h"
#include "gametime.h"
#include "debugproc.h"
#include "camera.h"
#include "course.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float MOVE_SPEED = 350.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CTarget::CTarget(int nPriority) : CObject3D(nPriority),
m_pPosMove(nullptr),
m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_nNumCount(0),
m_nNextIdx(0)
{

}

//==========================================
//  デストラクタ
//==========================================
CTarget::~CTarget()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTarget::Init(void)
{
	// サイズを設定
	m_size = POLYGON_SIZE;

	// 初期位置をプレイヤー座標に設定する
	m_pos = CGameManager::GetPlayer()->GetCenter();

	// 移動可能回数 + 1 の座標データを生成する
	if (m_pPosMove == nullptr)
	{
		m_pPosMove = new D3DXVECTOR3[m_nNumCount];

		// 値を初期化する
		for (int i = 0; i < m_nNumCount; ++i)
		{
			m_pPosMove[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// 始点をプレイヤー座標に設定する
		m_pPosMove[0] = m_pos;

		// 保存先インデックスを１つ進める
		++m_nNextIdx;
	}

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::KATANA));

	// 初期化
	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CTarget::Uninit(void)
{
	// 座標データの削除
	if (m_pPosMove != nullptr)
	{
		delete m_pPosMove;
		m_pPosMove = nullptr;
	}

	// 終了
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTarget::Update(void)
{
	// 前回からの経過時間を取得
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 移動
	Move();

	// 移動先設定
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN) ||
		CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_RB)||
		CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_LB))
	{
		SetMove();
		CGameManager::GetPlayer()->SetMovePos(m_pos);
	}

	// 更新
	CObject3D::Update();

	// デバッグ表示
	DebugProc::Print("ターゲット座標 : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	DebugProc::Print("保存先インデックス [ %d ]\n", m_nNextIdx);
	DebugProc::Print("保存できる座標 [ %d ]\n", m_nNumCount);
	for (int i = 0; i < m_nNumCount; ++i)
	{
		DebugProc::Print("保存された座標 [ %d ] : ( %f, %f, %f )\n", i, m_pPosMove[i].x, m_pPosMove[i].y, m_pPosMove[i].z);
	}
	DebugProc::Print("\n");
}

//==========================================
//  描画処理
//==========================================
void CTarget::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画
	CObject3D::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CTarget* CTarget::Create(const int nNum)
{
	// インスタンス生成
	CTarget* pTarget = new CTarget;

	// NULLチェック
	if (pTarget == nullptr) { return nullptr; }

	// 値を設定
	pTarget->m_nNumCount = nNum + 1;

	// 初期化処理
	pTarget->Init();

	// 値を返す
	return pTarget;
}

//==========================================
//  移動の処理
//==========================================
void CTarget::Move(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//パッド移動量を取得
	move = CManager::GetInstance()->GetJoyPad()->GetStickL(0.1f);

	//キーボード移動量の取得
	if (move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		move = CManager::GetInstance()->GetKeyboard()->GetWASD();
	}

	//移動量の適用
	m_move.x = move.x * MOVE_SPEED;
	m_move.y = move.z * MOVE_SPEED;

	//移動量を適用
	m_pos += m_move * m_fDeltaTime;

	// 移動制限
	Limit();
}

//==========================================
//  移動先の設定
//==========================================
void CTarget::SetMove()
{
	// 設定可能数と次のインデックスを比較
	if (m_nNumCount <= m_nNextIdx)
	{
		return;
	}

	// 現在の座標を次の移動先に保存する
	m_pPosMove[m_nNextIdx] = m_pos;

	// 移動の軌跡を生成
	CCourse::Create(m_pPosMove[m_nNextIdx - 1], m_pPosMove[m_nNextIdx]);

	// 保存先インデックスを１つ進める
	++m_nNextIdx;
}

//==========================================
//  移動制限
//==========================================
void CTarget::Limit()
{
	// y軸の0未満を補正
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}

	// スクリーン外の判定
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		m_pos = m_oldPos;
	}
}
