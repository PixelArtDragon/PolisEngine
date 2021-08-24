#include "ShaderLoader.h"

#include <fstream>
#include <sstream>
#include "Debug.h"
#include <vector>

std::shared_ptr<Shader> ShaderLoader::load(const std::string& filename, ShaderType shader_type) const {
    auto shader = std::make_shared<Shader>();
    shader->name = filename;
    std::ifstream infile(filename);
    if (!infile.good()) {
        Debug::Log(LogSeverity::Error, "Shader file " + filename + " does not exist.");
        shader->shader_id = 0;
        return shader;
    }
    std::stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();
    std::string file_string = buffer.str();
    char const* shader_code = file_string.c_str();
    GLuint shader_id = glCreateShader((shader_type ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER));
    glShaderSource(shader_id, 1, &shader_code, NULL);
    glCompileShader(shader_id);
    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length) {
            std::vector<char> shader_log(log_length);
            glGetShaderInfoLog(shader_id, log_length, NULL, shader_log.data());
            Debug::Log(LogSeverity::Error, "Error compiling shader " + filename + ", reason: " + shader_log.data());
            shader->shader_id = 0;
            glDeleteShader(shader_id);
            return shader;
        }
    }
    shader->shader_id = shader_id;
    return shader;
}
