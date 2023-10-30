//==========================================
//
//  �e�N�X�`���Ǘ��N���X(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//==========================================
//  �}�N����`
//==========================================
#define MAX_TEXTURE (256) //�g�p����e�N�X�`���̍ő吔

//==========================================
//  �e�N�X�`���Ǘ��N���X
//==========================================
class CTexture
{
public:
	//�e�N�X�`���̎�ނ̗񋓌^��`
	enum TEXTURE
	{
		BG = 0, //�w�i
		NUMBER, //����
		TITLE, //�^�C�g��
		CLEAR, //�Q�[���N���A
		OVER, //�Q�[���I�[�o�[
		FIELD, //��
		ARROW, //���
		SLASH, //�a���G�t�F�N�g
		SLICE, //�ެ�ݼެ��
		KATANA, //��
		MARKER, //�}�[�J�[
		WATER, //��
		SKY, //��
		ENEMY_00, //�G
		ENEMY_01, //�G
		TUTORIAL_00, //�`���[�g���A��00
		TUTORIAL_01, //�`���[�g���A��01
		TUTORIAL_02, //�`���[�g���A��02
		TEXTURE_MAX
	};

	CTexture(); //�R���X�g���N�^
	~CTexture(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Load(void); //�e�N�X�`���̃��[�h
	void UnLoad(void); //�e�N�X�`���̔j��
	int Regist(const char *pFilName); //�e�N�X�`���̓o�^
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_apTexture[nIdx]; } //�e�N�X�`���̎擾
	int GetNum(void) { return m_nNumAll; }

	//�ÓI�����o�֐�
	static bool GetLoadState(void) { return m_bLoad; }; //�e�N�X�`���̓ǂݍ��ݏ�Ԃ��擾

private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE]; //�e�N�X�`�����
	char m_sFilePass[MAX_TEXTURE][256]; //���ɓǂݍ��܂�Ă���e�N�X�`���̃p�X
	int m_nNumAll; //�e�N�X�`���̑���

	//�ÓI�����o�ϐ�
	static bool m_bLoad;

};

#endif
