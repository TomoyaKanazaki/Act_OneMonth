//==========================================
//
//  �a��ꂽ�|���S��(cut_polygon.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "cut_polygon.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCutPolygon::CCutPolygon(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCutPolygon::~CCutPolygon()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCutPolygon::Init(void)
{
	//������
	HRESULT hr = CObject3D::Init();

	//�e�N�X�`�����W�̐ݒ�
	if (m_move.y > 0.0f)
	{
		SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	}
	if (m_move.y < 0.0f)
	{
		SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}

	return hr;
}

//==========================================
//  �I������
//==========================================
void CCutPolygon::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CCutPolygon::Update(void)
{
	//�ړ�
	m_pos += m_move;

	//�����ɂ��ړ��̒�~
	//m_move.x += (0.0f - m_move.x) * 0.1f;

	//�����x��������
	D3DXCOLOR col = GetCol();
	col.a += (0.0f - col.a) * 0.1f;
	SetCol(col);

	//�����x0�ŏ���
	if (col.a <= 0.0f)
	{
		Uninit();
		return;
	}

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CCutPolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
CCutPolygon* CCutPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, LPDIRECT3DTEXTURE9 tex)
{
	//�C���X�^���X����
	CCutPolygon* pCut = new CCutPolygon;

	//�l��ݒ�
	pCut->m_pos = pos;
	pCut->m_size = size;
	pCut->m_move = move;

	//����������
	pCut->Init();

	//�e�N�X�`�����蓖��
	pCut->BindTexture(tex);

	return pCut;
}
