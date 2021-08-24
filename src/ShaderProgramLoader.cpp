#include "ShaderProgramLoader.h"
#include "Debug.h"
#include <vector>

std::shared_ptr<ShaderProgram> ShaderProgramLoader::load(const std::string& name, const Shader& vertex_shader, const Shader& fragment_shader) const {
    auto shader_program = std::make_shared<ShaderProgram>();
    shader_program->name = name;
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader.shader_id);
    glAttachShader(program_id, fragment_shader.shader_id);
    glLinkProgram(program_id);

    GLint is_linked;
    glGetProgramiv(program_id, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE) {
        int log_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length) {
            std::vector<char> program_log(log_length);
            glGetProgramInfoLog(program_id, log_length, NULL, program_log.data());
            Debug::Log(LogSeverity::Error, "Error compiling program " + name + " with shaders " +vertex_shader.name + ", " + fragment_shader.name + ", reason: " + program_log.data());
            shader_program->program_id = 0;
            return shader_program;
        }
    }
    shader_program->program_id = program_id;

    return shader_program;
}
