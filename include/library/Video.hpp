#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <DxLib.h>
const int BG_LAYER_NUM = 2;
const int SPRITE_LAYER_NUM = 2;

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
		enum BgLayer {
			BG_1 = 0, 
			BG_2 = 1,
			BG_3 = 2,
		};
		enum SpriteLayer {
			SP_1 = 0, 
			SP_2 = 1,
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
	      
	private:
		static void setupLayers();
		static int m_bgScrollSpeed[BG_LAYER_NUM];
		static VECTOR m_bgPosition[BG_LAYER_NUM];
		static VECTOR m_bgSize[BG_LAYER_NUM];
		static int m_width;
		static int m_height;
		static int m_bgLayers[BG_LAYER_NUM];
		static int m_spriteLayers[SPRITE_LAYER_NUM];
		static VECTOR m_bgLayersizes[BG_LAYER_NUM];
		static int m_shaderHandle;
		static VERTEX2DSHADER m_bgVertex[BG_LAYER_NUM][4];
		static VERTEX2DSHADER m_spriteVertex[SPRITE_LAYER_NUM][4];
		static void setupPixelShaders();
		static int m_bgScrollDirection[BG_LAYER_NUM];
		static void makeBgVertex(int layer, int w, int h);
  		static void makeSpriteVertex(int layer, int w, int h);
  		
	
	public:
		static void initialize(int w, int h);
		static void scrollBG();
		static void drawBGLayer();
		static void drawSpriteLayer();
		static void finishDrawLayer();
		static void clearBG();
		static void clearSpriteLayer();
  		static void tiledBgFromFile(BgLayer layer, std::string image_filename);
  		static void setBgScrollDirection(BgLayer layer, int direct);
  		static void drawSprite(SpriteLayer layer, int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TurnFlag);
      
};

#endif
