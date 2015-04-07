#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <DxLib.h>
const int BG_LAYER_NUM = 2;

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
		static int m_bgScrollSpeed[BG_LAYER_NUM];
		static VECTOR m_bgPosition[BG_LAYER_NUM];
		static VECTOR m_bgSize[BG_LAYER_NUM];
		static int m_width;
		static int m_height;
		static int m_bgScreens[BG_LAYER_NUM];
		static VECTOR m_bgScreenSizes[BG_LAYER_NUM];
		static int m_shaderHandle;
		static VERTEX2DSHADER m_bgVertex[BG_LAYER_NUM][4];
		static void setupPixelShaders();
		static int m_bgScrollDirection[BG_LAYER_NUM];
	
	public:
		static void setup();
		static void initialize(int w, int h);
		static void scrollBG();
		static void drawBG();
		static void drawSpriteToBg(int spriteHandle);
  		static void drawSpriteToBg(int spriteHandle, int x, int y);
		static void clearBG();  		
  		static void tiledBgFromFile(BgLayer layer, std::string image_filename);
  		static void makeBgVertex(BgLayer layer, int w, int h);
  		static void setBgScrollDirection(BgLayer layer, int direct);
      
};

#endif
