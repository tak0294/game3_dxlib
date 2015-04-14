#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <DxLib.h>
const int BG_LAYER_NUM = 3;
const int SPRITE_LAYER_NUM = 3;

/****************************************************
 * Video class.
 ****************************************************/
class Video{
	public:
		enum ScrollDirection {
			DIRECTION_NONE  = 0,
			DIRECTION_RIGHT = 1,
			DIRECTION_LEFT  = 2,
			DIRECTION_UP    = 4,
			DIRECTION_DOWN  = 8,
		};
		
		enum SpriteLayer {
			BG_1 = 0,
			BG_2 = 1,
			BG_3 = 2,
			SP_1 = 3, 
			SP_2 = 4,
			UI_1 = 5,
		};
		enum PixelShader {
			PS_NONE = 0,
			PS_RASTER = 1,
			PS_PIXELIZE = 2,
		};
		enum BgTiledType {
			BG_TILED_BOTH = 0,
			BG_TILED_VERTICAL = 1,
			BG_TILED_HORIZONTAL = 2,
		};
		enum FontType {
			FONT_NORMAL = 0
		};

	// TODO:m_bgPosition, m_bgSizeÇm_layerPosition, m_layerSizeÇ÷ïœçXÇ∑ÇÈ.	      
	private:
		static void setupLayers();
		static int m_bgScrollSpeed[BG_LAYER_NUM];
		static VECTOR m_bgPosition[BG_LAYER_NUM];
		static VECTOR m_bgSize[BG_LAYER_NUM];
		static int m_width;
		static int m_height;
		static int m_spriteLayers[SPRITE_LAYER_NUM + BG_LAYER_NUM];
		static VECTOR m_bgLayersizes[BG_LAYER_NUM];
		static int m_shaderHandle;
		static VERTEX2DSHADER m_bgVertex[BG_LAYER_NUM][4];
		static VERTEX2DSHADER m_spriteVertex[SPRITE_LAYER_NUM + BG_LAYER_NUM][4];
		static void setupPixelShaders();
		static int m_bgScrollDirection[BG_LAYER_NUM];
		static void makeBgVertex(int layer, int w, int h);
  		static void makeSpriteVertex(int layer, int w, int h);
  		
	
	public:
		static void initialize(int w, int h);
		static void scrollBG();
		static void makeScreen(int layer, int w, int h);
		static void deleteScreen(int layer);
		static void drawBGLayer();
		static void drawSpriteLayer();
		static void finishDrawLayer();
		static void clearBGLayer();
		static void clearSpriteLayer();
		static void bgFromFile(SpriteLayer layer, std::string image_filename, int x, int y);
		static void bgFromFile(SpriteLayer layer, std::string image_filename, int x, int y, int w, int h);
		static void bgFromGraph(SpriteLayer layer, int g_handle, int x, int y, int w, int h);
		
  		static void tiledBgFromFile(SpriteLayer layer, std::string image_filename);
  		static void setBgScrollDirection(SpriteLayer layer, int direct);
  		static void setBgScrollSpeed(SpriteLayer layer, int speed);
  		static void drawSprite(SpriteLayer layer, int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TurnFlag);
  		static void drawBox(SpriteLayer layer, int x1, int y1, int x2, int y2, int Color, int FillFlag);
  		static void drawCircle(SpriteLayer layer, int x, int y, int r, int Color, int FillFlag);
  		static void drawString(SpriteLayer layer, int x, int y, std::string string, int color);
  		static void drawString(SpriteLayer layer, int x, int y, std::string string, int color, int size);
      
};

#endif
