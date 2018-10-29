#include "pch.h"
#include "ENGINE.h"

void Engine::draw() {
	m_window.clear();


	m_map->draw();

	m_window.display();
}