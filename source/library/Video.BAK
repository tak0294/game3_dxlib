#include <DxLib.h>
#include "library/Video.hpp"
#include <iostream>

/**
 * Declare real symbols.
 */
int Video::m_width;
int Video::m_height;
int Video::m_bgScreens[BG_LAYER_NUM];
int Video::m_shaderHandle;
VERTEX2DSHADER Video::m_bgVertex[4];


/**
 * initialize.
 */
void Video::initialize(int w, int h) {
	m_width = w;
	m_height = h;
	 //頂点の設定
    for (int i = 0; i < 4; i++)
    {
        m_bgVertex[i].pos = VGet((i%2)*(float)m_width, (i/2)*(float)m_height, 0);
        m_bgVertex[i].rhw = 1.0f;
        m_bgVertex[i].dif = GetColorU8(255, 255, 255, 255);
        m_bgVertex[i].spc = GetColorU8(0, 0, 0, 0);
        m_bgVertex[i].u = m_bgVertex[i].su = (float)(i%2);
        m_bgVertex[i].v = m_bgVertex[i].sv = (float)(i/2);
    }
}

void Video::setupPixelShaders() {
	m_shaderHandle = LoadPixelShader("SamplePS.pso");
}

/**
 * set up Videos
 */
void Video::setup() {
    ChangeWindowMode(TRUE);
    SetGraphMode(m_width, m_height, 32);
    DxLib_Init();
    SetDrawScreen(DX_SCREEN_BACK);
	setupBgScreens();
	setupPixelShaders();

}


void Video::setupBgScreens() {
	for(int ii=0;ii<BG_LAYER_NUM;ii++) {
		m_bgScreens[ii] = MakeScreen(m_width, m_height, TRUE);
	}
}

void Video::drawBG() {
    //描画対象をバックスクリーンに戻してシェーダを使って描画
    SetDrawScreen(DX_SCREEN_BACK);
    
    for(int ii=0;ii<4;ii++) {
    	m_bgVertex[ii].pos.x -= 1;
    	if(m_bgVertex[ii].pos.x < 64) {
    		m_bgVertex[ii].pos.x = 64;
		}
	}
    
    for(int ii=0;ii<BG_LAYER_NUM;ii++) {
	    //シェーダで使うテクスチャは先ほど作った描画可能画像
	    SetUseTextureToShader(0, m_bgScreens[ii]);
	    //ピクセルシェーダのセット
	    SetUsePixelShader(m_shaderHandle);
	    DrawPrimitive2DToShader(m_bgVertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);    	
	}
    ScreenFlip();
    ClearDrawScreen();
}


void Video::drawSpriteToBg(int spriteHandle) {
	drawSpriteToBg(spriteHandle, 0, 0);
}

void Video::drawSpriteToBg(int spriteHandle, int x, int y) {
	SetDrawScreen(m_bgScreens[0]);
    ClearDrawScreen();
    DrawGraph(x, y, spriteHandle, TRUE);

}

void Video::clearBG() {
	for(int layer=0;layer<BG_LAYER_NUM;layer++) {
		SetDrawScreen(m_bgScreens[layer]);
		ClearDrawScreen();
	}
}

void Video::tiledBgFromFile(BgLayer layer, std::string image_filename) {
	int g_handle = LoadGraph(image_filename.c_str());
	int sp_w, sp_h;
	GetGraphSize(g_handle, &sp_w, &sp_h);
	SetDrawScreen(m_bgScreens[layer]);
	for(int ii=0;ii<m_height;ii+=sp_h) {
		for(int jj=0;jj<m_width;jj+=sp_w) {
			DrawGraph(jj,ii,g_handle, TRUE);	
		}
	}
}




