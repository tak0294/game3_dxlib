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
			DIRECTION_NONE = 0,
			DIRECTION_VERTICAL = 1,
			DIRECTION_HORIZONTAL = 2,
			DIRECTION_RIGHT_DOWN = 3,
			DIRECTION_LEFT_DOWN = 4,
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
		static int m_width;
		static int m_height;
		static int m_bgScreens[BG_LAYER_NUM];
		static int m_shaderHandle;
		static VERTEX2DSHADER m_bgVertex[4];
		static void setupPixelShaders();
	
	public:
		static void setup();
		static void initialize(int w, int h);
		static void setupBgScreens();
		static void drawBG();
		static void drawSpriteToBg(int spriteHandle);
  		static void drawSpriteToBg(int spriteHandle, int x, int y);
		static void clearBG();  		
  		static void tiledBgFromFile(BgLayer layer, std::string image_filename);
      
};

#endif
