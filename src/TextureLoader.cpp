#include "TextureLoader.h"

#include <filesystem>

#include "Debug.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::shared_ptr<Texture> TextureLoader::load(const std::string& filename) const {
    if (!std::filesystem::exists(filename)) {
        Debug::Log(LogSeverity::Error, "Texture file " + filename + " does not exist.");
        return std::make_shared<Texture>(0, filename);
    }

    GLuint new_id;
    glGenTextures(1, &new_id);
    glBindTexture(GL_TEXTURE_2D, new_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);
    return std::make_shared<Texture>(new_id, filename);
}