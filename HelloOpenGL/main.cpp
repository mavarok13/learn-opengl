#include <iostream>
#include <optional>

#include <SFML/Window.hpp>
#include <glad/glad.h>

int main() {
	unsigned window_width = 720u;
	unsigned window_height = 480u;

	sf::Window window(sf::VideoMode(sf::Vector2u{ window_width, window_height }), L"Тест", sf::Style::Titlebar | sf::Style::Close);
	
	if (!gladLoadGL()) {
		std::wcerr << L"Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, window.getSize().x, window.getSize().y);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} else if (event->is<sf::Event::Resized>()) {
				auto* const resized = event->getIf<sf::Event::Resized>();
				glViewport(0, 0, resized->size.x, resized->size.y);
			}
		}


	}

	return 0;
}