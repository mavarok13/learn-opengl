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

// * Compile 1st fragment shader
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

// * Compile 2nd fragment shader
	std::string fragment2_shader_source_code = shader_loader::ReadShaderSourceFromFile(fragment2_shader_path);
	const char* fragment2_shader_source_code_c_str = fragment2_shader_source_code.c_str();

	unsigned fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader2, 1, &fragment2_shader_source_code_c_str, NULL);

	std::cout << "[SHADER COMPILE INFO]: Starting compile fragment shader..." << std::endl;
	glCompileShader(fragment_shader2);
	glGetShaderiv(fragment_shader2, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment_shader2, 512, NULL, info_log);
		std::cerr << "[SHADER COMPILE ERR]: " << info_log << std::endl;
	} else {
		std::cout << "[SHADER COMPILE INFO]: Shader compile successfuly" << std::endl;
	}

// * Link shaders
// * First program
	unsigned shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cerr << "[SHADER LINK ERR]: " << info_log << std::endl;
	} else {
		std::cout << "[SHADER LINK INFO]: Shader link successfuly" << std::endl;
	}

// * Second program
	unsigned shader_program2 = glCreateProgram();
	glAttachShader(shader_program2, vertex_shader);
	glAttachShader(shader_program2, fragment_shader2);
	glLinkProgram(shader_program2);

	glGetProgramiv(shader_program2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program2, 512, NULL, info_log);
		std::cerr << "[SHADER LINK ERR]: " << info_log << std::endl;
	} else {
		std::cout << "[SHADER LINK INFO]: Shader link successfuly" << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(fragment_shader2);

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

// * Get uniform variables

	unsigned color1 = glGetUniformLocation(shader_program, "color");
	unsigned color2 = glGetUniformLocation(shader_program2, "color");

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

		glUseProgram(shader_program);
		float red_color = std::sin(.00000001f*(sc.now() - now).count())+.5f;
		glUniform4f(color1, red_color, .0f, .0f, 1.f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shader_program2);
		float blue_color = std::cos(.00000001f*(sc.now() - now).count()+3.14f/2)+.5f;
		glUniform4f(color1, .0f, .0f, blue_color, 1.f);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.display();
	}

	window.close();

	return 0;
}