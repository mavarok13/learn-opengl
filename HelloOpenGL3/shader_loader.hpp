#pragma once

#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

#include <glad/glad.h>

// * TO DO:
// |-	fix shaders source code reading(ReadShaderSourceFromFile return all code in one line and '#' in the begin cause compile failing)

namespace shader_loader {

namespace fs = std::filesystem;

constexpr unsigned INPUT_BUFFER_SIZE = 512u;

std::string ReadShaderSourceFromFile(const std::string & shader_file_location) {
	fs::path shader_path{shader_file_location};

	if (!fs::exists(shader_path)) {
		throw std::exception("Couldn't found shader file");
	}

	std::ifstream ifs{shader_path};
	if (!ifs.is_open()) {
		throw std::exception("Couldn't open shader file");
	}

	std::stringstream ss;
	char source_file_buffer[INPUT_BUFFER_SIZE];
	while (ifs.getline(source_file_buffer, INPUT_BUFFER_SIZE)) {
		ss << source_file_buffer << '\n';
	}

	return ss.str();
}

//	* CLASS FOR COMPILE SHADERS, CREATE PROGRAM, USE IT AND USE OTHER USEFUL FEATURES (E. G. SET UNIFORM VARIABLES)
class ShaderProgram {
public:
	ShaderProgram(const std::string & vertex_shader_path, const std::string & fragment_shader_path) {
//	*	* Get shaders source code
		std::string vertex_shader_source = ReadShaderSourceFromFile(vertex_shader_path);
		std::string fragment_shader_source = ReadShaderSourceFromFile(fragment_shader_path);
		const char* vertex_shader_source_c_str = vertex_shader_source.c_str();
		const char* fragment_shader_source_c_str = fragment_shader_source.c_str();

//	*	* Create shaders
		unsigned vertex_shader, fragment_shader;
		
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

//	*	* Define debug variables
		int success;
		char log_info[INPUT_BUFFER_SIZE];
//	*	* Compile vertex shader
		glShaderSource(vertex_shader, 1, &vertex_shader_source_c_str, NULL);

		std::cout << "[VERTEX SHADER COMPILATION INFO]: Starting compilation..." << std::endl;
		glCompileShader(vertex_shader);

		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex_shader, INPUT_BUFFER_SIZE, NULL, log_info);
			std::cerr << "[VERTEX SHADER COMPILATION ERR]" << log_info << std::endl;
		} else {
			std::cout << "[VERTEX SHADER COMPILATION INFO]: Done" << std::endl;
		}

//	*	* Compile fragment shader
		glShaderSource(fragment_shader, 1, &fragment_shader_source_c_str, NULL);
		
		std::cout << "[FRAGMENT SHADER COMPILATION INFO]: Starting compilation..." << std::endl;
		glCompileShader(fragment_shader);

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment_shader, INPUT_BUFFER_SIZE, NULL, log_info);
			std::cerr << "[FRAGMENT SHADER COMPILATION ERR]" << log_info << std::endl;
		} else {
			std::cout << "[FRAGMENT SHADER COMPILATION INFO]: Done" << std::endl;
		}

//	*	* Create program
		id_ = glCreateProgram();

//	*	* Attach and link shaders to program
		std::cout << "[SHADER PROGRAM LINKING INFO]: Starting linking program..." << std::endl;
		glAttachShader(id_, vertex_shader);
		glAttachShader(id_, fragment_shader);
		glLinkProgram(id_);

		glGetProgramiv(id_, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id_, INPUT_BUFFER_SIZE, NULL, log_info);
			std::cerr << "[SHADER PROGRAM LINKING ERR]: " << log_info << std::endl;
		} else {
			std::cout << "[SHADER PROGRAM LINKING INFO]: Done" << std::endl;
		}

		std::cout << "[SHADER PROGRAM CREATION INFO]: Shader program successfuly was created!" << std::endl;

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	void Use() const {
		glUseProgram(id_);
	}

//	* Set uniform variables
	void SetUniform1f(const std::string & name, float val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform1f(location, val);
	}

	void SetUniform2f(const std::string & name, float x_val, float y_val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform2f(location, x_val, y_val);
	}

	void SetUniform3f(const std::string & name, float x_val, float y_val, float z_val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform3f(location, x_val, y_val, z_val);
	}

	void SetUniform4f(const std::string & name, float x_val, float y_val, float z_val, float w_val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform4f(location, x_val, y_val, z_val, w_val);
	}

	void SetUniform1i(const std::string & name, int val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform1i(location, val);
	}

	void SetUniform2i(const std::string & name, int x_val, int y_val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform2i(location, x_val, y_val);
	}

	void SetUniform3i(const std::string & name, int x_val, int y_val, int z_val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform3i(location, x_val, y_val, z_val);
	}

	void SetUniform4i(const std::string & name, int x_val, int y_val, int z_val, int w_val) const {
		unsigned location = glGetUniformLocation(id_, name.c_str());
		Use();
		glUniform4i(location, x_val, y_val, z_val, w_val);
	}
//	* =============================================================================== * //
private:
	unsigned id_;
};

} // namespace shader_loader