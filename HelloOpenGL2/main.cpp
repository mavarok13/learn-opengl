#include <iostream>
#include <optional>
#include <chrono>
#include <cmath>

#include <SFML/Window.hpp>
#include <glad/glad.h>

#include "src/shader_loader.hpp"

// * FIX THIS
const char* vertex_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL2/src/vertex.glsl";
const char* fragment_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL2/src/fragment.glsl";
const char* fragment2_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL2/src/fragment2.glsl";

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

// * Create program
	shader_loader::ShaderProgram shader_program1(vertex_shader_path, fragment_shader_path);
	shader_loader::ShaderProgram shader_program2(vertex_shader_path, fragment2_shader_path);

// * ======================

	float vertices[] = {
		// 1st triable
		-.5f, -.51f, .0f, // left bottom 
		.5f, -.51f, .0f, // right bottom
		.5f, .49f, .0f, // right upper
		
		// 2nd triangle
		-.5f, -.49f, .0f, // left bottom 
		.5f, .51f, .0f, // right upper
		-.5f, .51f, .0f // left upper
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

	unsigned VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	unsigned VBO2;
	glGenBuffers(1, &VBO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) (sizeof(float)*9));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

// * Create clock
	std::chrono::steady_clock sc;
	auto now = sc.now();

// * =================================

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

		float red_color = std::sin(.00000001f*(sc.now() - now).count())+.5f;
		shader_program1.SetUniform4f("color", red_color, .0f, .0f, 1.f);
		shader_program1.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		float blue_color = std::cos(.00000001f*(sc.now() - now).count()+3.14f/2)+.5f;
		shader_program2.SetUniform4f("color", .0f, .0f, blue_color, .0f);
		shader_program2.Use();
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.display();
	}

	window.close();

	return 0;
}