#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "actor/PlayerActor.hpp"
#include "application/Math.hpp"
#include "application/Camera.hpp"
#include "world/World.hpp"


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
	sf::View m_view;
	Camera m_camera;

	std::shared_ptr<PlayerActor> m_playerActor;
	World m_world;

	std::vector<math::Polygon> b;
	sf::ConvexShape _b;
};

