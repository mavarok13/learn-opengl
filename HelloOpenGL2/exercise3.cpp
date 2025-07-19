// ==================================================================
// * Exercise 3: connect color value of vertex to triangle position
// ==================================================================

#include <iostream>
#include <optional>
#include <chrono>
#include <cmath>

#include <SFML/Window.hpp>
#include <glad/glad.h>

#include "src/shader_loader.hpp"

// * FIX THIS
const char* vertex_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL2/src/vertex4.glsl";
const char* fragment_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL2/src/fragment4.glsl";

int main() {
	unsigned window_width = 720u;
	unsigned window_height = 480u;

	sf::Window window(sf::VideoMode(sf::Vector2u{ window_width, window_height }), L"����", sf::Style::Titlebar | sf::Style::Close);
	window.setActive(true);

	if (!gladLoadGL()) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, window.getSize().x, window.getSize().y);

	shader_loader::ShaderProgram shader_program(vertex_shader_path, fragment_shader_path);

// * ======================

	float vertices[] = {
		// corners
		-.5f, -.5f, .0f,
		.5f, -.5f, .0f,
		.0f, .5f, .0f
	};

	glViewport(0, 0, window.getSize().x, window.getSize().y);

// * Configure vertex arrays and buffers
	unsigned VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

// * =================================

	std::chrono::steady_clock sc;
	const auto now = sc.now();

	bool is_running = true;
	while (is_running) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				is_running = false;
			} else if (event->is<sf::Event::Resized>()) {
				auto* const resized = event->getIf<sf::Event::Resized>();
				glViewport(0, 0, resized->size.x, resized->size.y);
			}
		}

		glClearColor(.0f, .0f, .0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		float offset = std::sin(.000000001f*(sc.now()-now).count());
		shader_program.SetUniform1f("offset", offset);
		shader_program.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.display();
	}

	window.close();

	return 0;
}