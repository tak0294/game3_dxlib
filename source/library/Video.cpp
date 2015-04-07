#include <DxLib.h>
#include "library/Video.hpp"
#include <iostream>

/**
 * Declare real symbols.
 */
VECTOR Video::m_bgPosition[BG_LAYER_NUM];
VECTOR Video::m_bgSize[BG_LAYER_NUM];
VECTOR Video::m_bgScreenSizes[BG_LAYER_NUM];
int Video::m_width;
int Video::m_height;
int Video::m_bgScreens[BG_LAYER_NUM];
int Video::m_shaderHandle;
int Video::m_bgScrollSpeed[BG_LAYER_NUM];
VERTEX2DSHADER Video::m_bgVertex[BG_LAYER_NUM][4];
int Video::m_bgScrollDirection[BG_LAYER_NUM];

/**
 * initialize.
 */
void Video::initialize(int w, int h) {
	m_width = w;
	m_height = h;
	
	for(int layer=0;layer<BG_LAYER_NUM;layer++) {
		m_bgScreens[layer] = -1;
		m_bgScrollSpeed[layer] = 1;
	}
	m_bgScrollSpeed[1] = 2;
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
//	setupBgScreens();
	setupPixelShaders();

}

void Video::scrollBG() {
	
	for(int layer=0;layer<BG_LAYER_NUM;layer++) {
		for(int ii=0;ii<m_bgScrollSpeed[layer];ii++) {

			if(m_bgScrollDirection[layer] & Video::DIRECTION_LEFT) {
				m_bgPosition[layer].x -= 1;
			}
			if(m_bgScrollDirection[layer] & Video::DIRECTION_RIGHT) {
				m_bgPosition[layer].x += 1;
			}
			if(m_bgScrollDirection[layer] & Video::DIRECTION_UP) {
				m_bgPosition[layer].y -= 1;
			}
			if(m_bgScrollDirection[layer] & Video::DIRECTION_DOWN) {
				m_bgPosition[layer].y += 1;
			}

	
		    m_bgVertex[layer][0].pos.x = m_bgPosition[layer].x;
		    m_bgVertex[layer][1].pos.x = m_bgPosition[layer].x + m_bgScreenSizes[layer].x;
		    m_bgVertex[layer][2].pos.x = m_bgPosition[layer].x;
		    m_bgVertex[layer][3].pos.x = m_bgPosition[layer].x + m_bgScreenSizes[layer].x;
		    
		    m_bgVertex[layer][0].pos.y = m_bgPosition[layer].y;
		    m_bgVertex[layer][1].pos.y = m_bgPosition[layer].y;
		    m_bgVertex[layer][2].pos.y = m_bgPosition[layer].y + m_bgScreenSizes[layer].y;
		    m_bgVertex[layer][3].pos.y = m_bgPosition[layer].y + m_bgScreenSizes[layer].y;
		    
		    
		    if(m_bgPosition[layer].x < m_bgSize[layer].x * -2 || 
			   m_bgPosition[layer].x > 0){
		    	m_bgPosition[layer].x = -m_bgSize[layer].x;
			}
			
			if(m_bgPosition[layer].y < m_bgSize[layer].y * -2 || 
			   m_bgPosition[layer].y > 0){
		    	m_bgPosition[layer].y = -m_bgSize[layer].y;
			}
		}
	}
	
}

void Video::drawBG() {
	
	scrollBG();
	
    //描画対象をバックスクリーンに戻してシェーダを使って描画
    SetDrawScreen(DX_SCREEN_BACK);
	    
    for(int ii=0;ii<BG_LAYER_NUM;ii++) {
    	if(m_bgScreens[ii] == -1)	continue;
    	
	    //シェーダで使うテクスチャは先ほど作った描画可能画像
	    SetUseTextureToShader(0, m_bgScreens[ii]);
	    //ピクセルシェーダのセット
	    SetUsePixelShader(m_shaderHandle);
	    DrawPrimitive2DToShader(m_bgVertex[ii], 4, DX_PRIMTYPE_TRIANGLESTRIP);    	
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

void Video::makeBgVertex(BgLayer layer, int w, int h) {
	 //頂点の設定
    for (int i = 0; i < 4; i++)
    {
        m_bgVertex[layer][i].pos = VGet((i%2)*w, (i/2)*h, 0);
        m_bgVertex[layer][i].rhw = 1.0f;
        m_bgVertex[layer][i].dif = GetColorU8(255, 255, 255, 255);
        m_bgVertex[layer][i].spc = GetColorU8(0, 0, 0, 0);
        m_bgVertex[layer][i].u = m_bgVertex[layer][i].su = (float)(i%2);
        m_bgVertex[layer][i].v = m_bgVertex[layer][i].sv = (float)(i/2);
    }

}


void Video::tiledBgFromFile(BgLayer layer, std::string image_filename) {
	int g_handle = LoadGraph(image_filename.c_str());
	int sp_w, sp_h;
	GetGraphSize(g_handle, &sp_w, &sp_h);
	m_bgSize[layer].x = sp_w;
	m_bgSize[layer].y = sp_h;
	
	int scr_w = m_width + sp_w*2;
	int scr_h = m_height + sp_h*2;
	m_bgScreenSizes[layer].x = scr_w;
	m_bgScreenSizes[layer].y = scr_h;

	m_bgScreens[layer] = MakeScreen(scr_w, scr_h, TRUE);	
	SetDrawScreen(m_bgScreens[layer]);
	makeBgVertex(layer, scr_w, scr_h);
	for(int ii=0;ii<scr_h;ii+=sp_h) {
		for(int jj=0;jj<scr_w;jj+=sp_w) {
			DrawGraph(jj,ii,g_handle, TRUE);	
		}
	}
	
	// 背景の初期位置を設定する. 
	m_bgPosition[layer].x = -sp_w;
	m_bgPosition[layer].y = -sp_h;
	
}


void Video::setBgScrollDirection(BgLayer layer, int direct) {
	m_bgScrollDirection[layer] = direct;
}

