#include <optional>

#include <SFML/Window.hpp>

int main() {
	sf::Window window(sf::VideoMode({768, 420}), L"Тест", sf::Style::Titlebar | sf::Style::Close);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
	}

	return 0;
}