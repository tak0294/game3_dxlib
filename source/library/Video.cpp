#include <DxLib.h>
#include "library/Video.hpp"
#include <iostream>

/**
 * Declare real symbols.
 */
VECTOR Video::m_bgPosition[BG_LAYER_NUM];
VECTOR Video::m_bgSize[BG_LAYER_NUM];
VECTOR Video::m_bgLayersizes[BG_LAYER_NUM];
int Video::m_width;
int Video::m_height;
int Video::m_spriteLayers[SPRITE_LAYER_NUM + BG_LAYER_NUM];
int Video::m_shaderHandle;
int Video::m_bgScrollSpeed[BG_LAYER_NUM];
VERTEX2DSHADER Video::m_bgVertex[BG_LAYER_NUM][4];
VERTEX2DSHADER Video::m_spriteVertex[SPRITE_LAYER_NUM + BG_LAYER_NUM][4];
int Video::m_bgScrollDirection[BG_LAYER_NUM];

/**
 * initialize.
 */
void Video::setupLayers() {

	/**
	 * Initialize BG Layers.
	 */
	for(int layer=Video::BG_1;layer<Video::BG_1 + BG_LAYER_NUM;layer++) {
		Video::makeScreen(layer, m_width, m_height);
		makeSpriteVertex(layer, m_width, m_height);
		m_bgScrollSpeed[layer] = 0;
	}
	
	/**
	 * Initialize Sprite Layers.
	 */
	for(int layer=Video::SP_1;layer<Video::SP_1 + SPRITE_LAYER_NUM;layer++) {
		Video::makeScreen(layer, m_width, m_height);
		makeSpriteVertex(layer, m_width, m_height);
	}
}

void Video::setupPixelShaders() {
	m_shaderHandle = LoadPixelShader("SamplePS.pso");
}

/**
 * set up Videos
 */
void Video::initialize(int w, int h) {

	m_width = w;
	m_height = h;

    ChangeWindowMode(TRUE);
    SetGraphMode(m_width, m_height, 32);
    DxLib_Init();
    ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    SetDrawScreen(DX_SCREEN_BACK);
//	setupBgScreens();
	setupPixelShaders();
	setupLayers();

}

/**
 * レイヤーを明示的に作成,削除.
 */
void Video::makeScreen(int layer, int w, int h) {
	deleteScreen(layer);
	m_spriteLayers[layer] = MakeScreen(w, h, TRUE);
	makeSpriteVertex(layer, w, h);
}

void Video::deleteScreen(int layer) {
	if(m_spriteLayers[layer] != -1) {
		DeleteGraph(m_spriteLayers[layer]);
		m_spriteLayers[layer] = -1;
	}
}


void Video::setBgScrollSpeed(SpriteLayer layer, int speed) {
	m_bgScrollSpeed[layer] = speed;
} 

void Video::scrollBG() {
	
	for(int layer=BG_1;layer<BG_1+BG_LAYER_NUM;layer++) {
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

	
		    m_spriteVertex[layer][0].pos.x = m_bgPosition[layer].x;
		    m_spriteVertex[layer][1].pos.x = m_bgPosition[layer].x + m_bgLayersizes[layer].x;
		    m_spriteVertex[layer][2].pos.x = m_bgPosition[layer].x;
		    m_spriteVertex[layer][3].pos.x = m_bgPosition[layer].x + m_bgLayersizes[layer].x;
		    
		    m_spriteVertex[layer][0].pos.y = m_bgPosition[layer].y;
		    m_spriteVertex[layer][1].pos.y = m_bgPosition[layer].y;
		    m_spriteVertex[layer][2].pos.y = m_bgPosition[layer].y + m_bgLayersizes[layer].y;
		    m_spriteVertex[layer][3].pos.y = m_bgPosition[layer].y + m_bgLayersizes[layer].y;
		    
		    
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

void Video::drawBGLayer() {
	
	scrollBG();
	
    //描画対象をバックスクリーンに戻してシェーダを使って描画
    SetDrawScreen(DX_SCREEN_BACK);
	    
    for(int ii=BG_1;ii<BG_1+BG_LAYER_NUM;ii++) {
    	if(m_spriteLayers[ii] == -1)	continue;
    	
	    //シェーダで使うテクスチャは先ほど作った描画可能画像
	    SetUseTextureToShader(0, m_spriteLayers[ii]);
	    //ピクセルシェーダのセット
	    SetUsePixelShader(m_shaderHandle);
	    DrawPrimitive2DToShader(m_spriteVertex[ii], 4, DX_PRIMTYPE_TRIANGLESTRIP);    	
	}
}

void Video::drawSpriteLayer() {
	
	//描画対象をバックスクリーンに戻してシェーダを使って描画
	SetDrawScreen(DX_SCREEN_BACK);
	
	for(int ii=SP_1;ii<SP_1+SPRITE_LAYER_NUM;ii++) {
    	if(m_spriteLayers[ii] == -1)	continue;
    	
	    //シェーダで使うテクスチャは先ほど作った描画可能画像
	    SetUseTextureToShader(0, m_spriteLayers[ii]);
	    //ピクセルシェーダのセット
	    SetUsePixelShader(m_shaderHandle);
	    DrawPrimitive2DToShader(m_spriteVertex[ii], 4, DX_PRIMTYPE_TRIANGLESTRIP);    	
	}
}

void Video::finishDrawLayer() {
	SetDrawScreen(DX_SCREEN_BACK);
    ScreenFlip();
    ClearDrawScreen();
}


void Video::clearSpriteLayer() {
	for(int layer=SP_1;layer<SP_1+SPRITE_LAYER_NUM;layer++) {
		SetDrawScreen(m_spriteLayers[layer]);
		ClearDrawScreen();
	}
}

void Video::clearBGLayer() {
	for(int layer=BG_1;layer<BG_1+BG_LAYER_NUM;layer++) {
		SetDrawScreen(m_spriteLayers[layer]);
		ClearDrawScreen();
	}
}

void Video::makeBgVertex(int layer, int w, int h) {
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

void Video::makeSpriteVertex(int layer, int w, int h) {
	 //頂点の設定
    for (int i = 0; i < 4; i++)
    {
        m_spriteVertex[layer][i].pos = VGet((i%2)*w, (i/2)*h, 0);
        m_spriteVertex[layer][i].rhw = 1.0f;
        m_spriteVertex[layer][i].dif = GetColorU8(255, 255, 255, 255);
        m_spriteVertex[layer][i].spc = GetColorU8(0, 0, 0, 0);
        m_spriteVertex[layer][i].u = m_spriteVertex[layer][i].su = (float)(i%2);
        m_spriteVertex[layer][i].v = m_spriteVertex[layer][i].sv = (float)(i/2);
    }
}

void Video::bgFromFile(SpriteLayer layer, std::string image_filename, int x, int y) {
	int r,g,b;
	GetTransColor(&r, &g, &b);
	SetTransColor(255, 255, 255);

	int g_handle = LoadGraph(image_filename.c_str());
	int sp_w, sp_h;
	GetGraphSize(g_handle, &sp_w, &sp_h);
	
	m_bgSize[layer].x = sp_w;
	m_bgSize[layer].y = sp_h;
	Video::makeScreen(layer, sp_w, sp_h);
	SetDrawScreen(m_spriteLayers[layer]);
	makeSpriteVertex(layer, sp_w, sp_h);
	DrawGraph(x, y, g_handle,  TRUE);
	SetTransColor(r,g,b);
}

void Video::bgFromFile(SpriteLayer layer, std::string image_filename, int x, int y, int w, int h) {
	int r,g,b;
	GetTransColor(&r, &g, &b);
	SetTransColor(255, 255, 255);

	int g_handle = LoadGraph(image_filename.c_str());
	int sp_w, sp_h;
	GetGraphSize(g_handle, &sp_w, &sp_h);
	
	m_bgSize[layer].x = sp_w;
	m_bgSize[layer].y = sp_h;
	Video::makeScreen(layer, w, h);
	SetDrawScreen(m_spriteLayers[layer]);
	makeSpriteVertex(layer, w, h);
	DrawExtendGraph(x, y, x+w, y+h, g_handle, TRUE);
	SetTransColor(r,g,b);
}

void Video::bgFromGraph(SpriteLayer layer, int g_handle, int x, int y, int w, int h) {
	int sp_w, sp_h;
	GetGraphSize(g_handle, &sp_w, &sp_h);
	
	m_bgSize[layer].x = sp_w;
	m_bgSize[layer].y = sp_h;
	Video::makeScreen(layer, w, h);
	SetDrawScreen(m_spriteLayers[layer]);
	makeSpriteVertex(layer, w, h);
	DrawExtendGraph(x, y, x+w, y+h, g_handle, TRUE);
}


void Video::tiledBgFromFile(SpriteLayer layer, std::string image_filename) {
	int g_handle = LoadGraph(image_filename.c_str());
	int sp_w, sp_h;
	GetGraphSize(g_handle, &sp_w, &sp_h);
	m_bgSize[layer].x = sp_w;
	m_bgSize[layer].y = sp_h;
	
	int scr_w = m_width + sp_w*2;
	int scr_h = m_height + sp_h*2;
	m_bgLayersizes[layer].x = scr_w;
	m_bgLayersizes[layer].y = scr_h;

	Video::makeScreen(layer, scr_w, scr_h);

	SetDrawScreen(m_spriteLayers[layer]);
	makeSpriteVertex(layer, scr_w, scr_h);
	for(int ii=0;ii<scr_h;ii+=sp_h) {
		for(int jj=0;jj<scr_w;jj+=sp_w) {
			DrawGraph(jj,ii,g_handle, TRUE);	
		}
	}
	
	// 背景の初期位置を設定する. 
	m_bgPosition[layer].x = -sp_w;
	m_bgPosition[layer].y = -sp_h;
	
}


void Video::setBgScrollDirection(SpriteLayer layer, int direct) {
	m_bgScrollDirection[layer] = direct;
}


void Video::drawSprite(SpriteLayer layer, int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TurnFlag) {
	SetDrawScreen(m_spriteLayers[layer]);
	DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, TRUE, TurnFlag);
} 

void Video::drawBox(SpriteLayer layer, int x1, int y1, int x2, int y2, int Color, int FillFlag) {
	SetDrawScreen(m_spriteLayers[layer]);
	DrawBox(x1, y1, x2, y2, Color, FillFlag);
}

void Video::drawCircle(SpriteLayer layer, int x, int y, int r, int Color, int FillFlag) {
	SetDrawScreen(m_spriteLayers[layer]);
	DrawCircle(x, y, r, Color, FillFlag);
}

void Video::drawString(SpriteLayer layer, int x, int y, std::string string, int color) {
	drawString(layer, x, y, string, color, 14);
}

void Video::drawString(SpriteLayer layer, int x, int y, std::string string, int color, int size) {
	int old_size = GetFontSize();
	SetFontSize(size);
	SetDrawScreen(m_spriteLayers[layer]);
	DrawString(x, y, string.c_str(), color);
	SetFontSize(old_size);
}
