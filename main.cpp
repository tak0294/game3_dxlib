#include <DxLib.h>
#include "Video.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpCmdLine, int nShowCmd)
{
 	
 	
    ChangeWindowMode(TRUE);
    SetGraphMode(640, 480, 32);
    if (DxLib_Init() == -1) { return -1; }  
    SetDrawScreen(DX_SCREEN_BACK);  

    int test = LoadGraph("Sprite-Logo.png");
    //�s�N�Z���V�F�[�_�ǂݍ���
    int shaderhandle = LoadPixelShader("SamplePS.pso");
    //�V���ɕ`��\�摜���쐬���ăV�F�[�_�ɂ����n��
    int thirdscreen = MakeScreen(640, 480);
    //���_�̐ݒ�
    VERTEX2DSHADER vertex[4];
    for (int i = 0; i < 4; i++)
    {
        vertex[i].pos = VGet((i%2)*640.0f, (i/2)*480.0f, 0);
        vertex[i].rhw = 1.0f;
        vertex[i].dif = GetColorU8(255, 255, 255, 255);
        vertex[i].spc = GetColorU8(0, 0, 0, 0);
        vertex[i].u = vertex[i].su = (float)(i%2);
        vertex[i].v = vertex[i].sv = (float)(i/2);
    }

    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
        //�`��\�摜�ɑ΂��ď�������
        SetDrawScreen(thirdscreen);
        ClearDrawScreen();
        DrawGraph(0, 0, test, TRUE);

        //�`��Ώۂ��o�b�N�X�N���[���ɖ߂��ăV�F�[�_���g���ĕ`��
        SetDrawScreen(DX_SCREEN_BACK);
        //�V�F�[�_�Ŏg���e�N�X�`���͐�قǍ�����`��\�摜
        SetUseTextureToShader(0, thirdscreen);
        Video::initialize(640, 480);
        //�s�N�Z���V�F�[�_�̃Z�b�g
        SetUsePixelShader(shaderhandle);
        DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
        ScreenFlip();
        ClearDrawScreen();
    }

    DxLib_End();
    return 0;
}
