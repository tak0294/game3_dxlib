#include "library/GameManager.hpp"

GameManager::GameManager(int screen_w, int screen_h) {
	Video::initialize(screen_w, screen_h);
	InputSystem::initialize();
	this->m_currentScene = NULL;
}

void GameManager::start() {

	while (!ProcessMessage())
    {
    	Video::clearSpriteLayer();

    	InputSystem::updateKeyState();
    	if(InputSystem::isESC) {
    		break;
    	}

        // Draw current scene.
        if(this->m_currentScene != NULL) {
	        this->m_currentScene->update();
	        this->m_currentScene->draw();
		}
	
		Video::drawBGLayer();
		Video::drawSpriteLayer();
		Video::finishDrawLayer();
		Video::clearSpriteLayer();
    }
}

void GameManager::quit() {
	//SDL_FreeSurface(image);
	//SDL_Quit();
}


void GameManager::setScene(Scene *scene) {
	this->m_currentScene = scene;
}
