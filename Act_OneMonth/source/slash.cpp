//==========================================
//
//  斬撃エフェクト(slash.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "slash.h"
#include "manager.h"
#include "renderer.h"
#include "gametime.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 SLASH_SIZE = D3DXVECTOR3(2000.0f, 50.0f, 0.0f); // ポリゴンサイズ
	const float CLEAR_TIME = 4.0f; // 1 / n 秒
}

//==========================================
//  コンストラクタ
//==========================================
CSlash::CSlash(int nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CSlash::~CSlash()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CSlash::Init(void)
{
	// サイズを設定
	m_size = SLASH_SIZE;

	// ポリゴンの左端の座標を算出
	m_posLeft.x = m_pos.x + (cosf(m_rot.z) * m_size.x);
	m_posLeft.y = m_pos.y + (sinf(m_rot.z) * m_size.x);

	// ポリゴンの右端の座標を算出
	m_posRight.x = m_pos.x - (cosf(m_rot.z) * m_size.x);
	m_posRight.y = m_pos.y - (sinf(m_rot.z) * m_size.x);

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ARROW));

	// 初期化
	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CSlash::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CSlash::Update(void)
{
	// 完全に透過していた場合終了する
	if (m_col.a <= 0.0f)
	{
		Uninit();
		return;
	}

	// 不透明度を下げる
	m_col.a -= CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat() * 2.0f;

	// 攻撃判定
	Hit();

	// デバッグ表示
	DebugProc::Print("左端 : %f, %f\n", m_posLeft.x, m_posLeft.y);
	DebugProc::Print("右端 : %f, %f\n", m_posRight.x, m_posRight.y);

	// 更新する
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CSlash::Draw(void)
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
CSlash* CSlash::Create(const D3DXVECTOR3 pos, const float rot, const D3DXCOLOR col)
{
	// インスタンス生成
	CSlash* pSlash = new CSlash;

	// NULLチェック
	if (pSlash == nullptr) { return nullptr; }

	// 値の設定
	pSlash->m_pos = pos;
	pSlash->m_rot.z = rot;
	pSlash->m_col = col;

	// 初期化処理
	pSlash->Init();

	// 値を返す
	return pSlash;
}

//==========================================
//  敵との当たり判定
//==========================================
void CSlash::Hit()
{
	//当たり判定の生成
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭のアドレスを取得
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //敵の場合
			{
				if (pObj->GetObjState() == CObject::NORMAL) // 通常状態の場合
				{
					// 目標点を取得する
					D3DXVECTOR3 pos = pObj->GetPos();

					// 始点から終点までのベクトルを求める
					D3DXVECTOR3 vecLine = m_posRight - m_posLeft;

					// 始点から目標点までのベクトルを求める
					D3DXVECTOR3 vecToPos = pos - m_posLeft;

					// 各ベクトルの大きさを求める
					float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
					float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

					// 媒介変数tを求める
					float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

					// 線分の判定
					if (0.0f <= t && t <= 1.0f)
					{
						// 目標点から直線に垂線を下した時の交点を求める
						D3DXVECTOR3 posCross = m_posLeft + (t * vecLine);

						// 交点から目標点までのベクトルを求める
						D3DXVECTOR3 vecToCross = pos - posCross;

						// 判定距離の比較
						if (SLASH_SIZE.y * SLASH_SIZE.y >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
						{
							// 当たっていた時の演出系処理
							CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
							pObj->SetState(CObject::ATTACKED);
						}
					}
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}
