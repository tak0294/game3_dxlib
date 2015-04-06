#include <DxLib.h>
#include "Video.hpp"
#include <iostream>

/**
 * Declare real symbols.
 */
int Video::m_width;
int Video::m_height;


/**
 * initialize.
 */
void Video::initialize(int w, int h) {
	 m_width = w;
	 m_height = h;
	 DrawString( 0 , 0 , "TEST TEXT" ,  GetColor( 255 , 255 , 255 ) ) ;
}
