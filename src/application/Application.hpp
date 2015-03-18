#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "Math.hpp"


class Application
{
public:
	Application(int argc, char** argv);
	~Application();
	
private:
	void run();
	void initialize();
	void handleEvents();
	void update(sf::Time & deltaTime);
	void render();

	bool m_running, m_active;
	bool m_space, m_mouse;

	sf::RenderWindow m_window;

	math::Polygon a, b, c;
	sf::ConvexShape _a, _b, _c;
};

