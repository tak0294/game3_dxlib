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
    //ピクセルシェーダ読み込み
    int shaderhandle = LoadPixelShader("SamplePS.pso");
    //新たに描画可能画像を作成してシェーダにこれを渡す
    int thirdscreen = MakeScreen(640, 480);
    //頂点の設定
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
        //描画可能画像に対して書き込み
        SetDrawScreen(thirdscreen);
        ClearDrawScreen();
        DrawGraph(0, 0, test, TRUE);

        //描画対象をバックスクリーンに戻してシェーダを使って描画
        SetDrawScreen(DX_SCREEN_BACK);
        //シェーダで使うテクスチャは先ほど作った描画可能画像
        SetUseTextureToShader(0, thirdscreen);
        Video::initialize(640, 480);
        //ピクセルシェーダのセット
        SetUsePixelShader(shaderhandle);
        DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
        ScreenFlip();
        ClearDrawScreen();
    }

    DxLib_End();
    return 0;
}
