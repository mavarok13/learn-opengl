#include <iostream>
#include <optional>

#include <SFML/Window.hpp>
#include <glad/glad.h>

#include "src/shader_loader.hpp"

// * FIX THIS
const char* vertex_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL/src/vertex.glsl";
const char* fragment_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL/src/fragment.glsl";

int main() {
	unsigned window_width = 720u;
	unsigned window_height = 480u;

	sf::Window window(sf::VideoMode(sf::Vector2u{ window_width, window_height }), L"Тест", sf::Style::Titlebar | sf::Style::Close);
	window.setActive(true);

	if (!gladLoadGL()) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

// * Compile vertex shader
	int success; char info_log[512];

	std::string vertex_shader_source_code = shader_loader::ReadShaderSourceFromFile(vertex_shader_path);
	const char* vertex_shader_source_code_c_str = vertex_shader_source_code.c_str();

	unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source_code_c_str, NULL);
	std::cout << "[SHADER COMPILE INFO]: Start compile vertex shader..." << std::endl;
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cerr << "[SHADER COMPILE ERR]: " << info_log << std::endl;
	} else {
		std::cout << "[SHADER COMPILE INFO]: Shader compile successfuly" << std::endl;
	}

// * Compile fragment shader
	std::string fragment_shader_source_code = shader_loader::ReadShaderSourceFromFile(fragment_shader_path);
	const char* fragment_shader_source_code_c_str = fragment_shader_source_code.c_str();

	unsigned fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source_code_c_str, NULL);
	std::cout << "[SHADER COMPILE INFO]: Start compile fragment shader..." << std::endl;
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cerr << "[SHADER COMPILE ERR]: " << info_log << std::endl;
	} else {
		std::cout << "[SHADER COMPILE INFO]: Shader compile successfuly" << std::endl;
	}

// * Link shaders
	unsigned shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cerr << "[SHADER LINK ERR]: " << info_log << std::endl;
	} else {
		std::cout << "[SHADER LINK INFO]: Shader link successfuly" << std::endl;
	}

// * ======================

	float vertices[] = {
		-.5f, -.5f, .0f,
		.5f, -.5f, .0f,
		.0f, .5f, .0f
	};

	glViewport(0, 0, window.getSize().x, window.getSize().y);

	unsigned VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

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

		glClearColor(.02f, .75f, .23f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.display();
	}

	window.close();

	return 0;
}