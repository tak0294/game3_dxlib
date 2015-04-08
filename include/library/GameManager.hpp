#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <DxLib.h>
#include "library/Video.hpp"
#include "library/InputSystem.hpp"
#include "library/Scene.hpp"

/***************************************************************************************
 * GameManager Class.
 ***************************************************************************************/
class GameManager {
	Scene *m_currentScene;
public:
	GameManager(int, int);
	void setScene(Scene *scene);
	void start();
	void quit();
};


#endif
