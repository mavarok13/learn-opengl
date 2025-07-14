#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

// * TO DO:
// |-	fix shaders source code reading(ReadShaderSourceFromFile return all code in one line and '#' in the begin cause compile failing)

namespace shader_loader {

namespace fs = std::filesystem;

constexpr unsigned INPUT_BUFFER_SIZE = 256u;

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

} // namespace shader_loader