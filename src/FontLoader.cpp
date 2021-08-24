#include "FontLoader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Debug.h"

std::shared_ptr<Font> FontLoader::load(const std::string& font_file) const {
    std::shared_ptr<Font> font = std::make_shared<Font>();

    FT_Library library;

    FT_Init_FreeType(&library);

    FT_Face face;

    auto error = FT_New_Face(library, font_file.c_str(), 0, &face);

    if (error == FT_Err_Unknown_File_Format) {
        Debug::Log(LogSeverity::Error, "Could not read font file: " + font_file);
    } else if (error) {
        Debug::Log(LogSeverity::Error, "Error loading font file: " + font_file);
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    unsigned int width = 0;
    unsigned int height = 0;
    for (int i = 0; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            Debug::Log(LogSeverity::Warning, "Could not load glyph " + i);
            continue;
        }
        width += face->glyph->bitmap.width;
        height = std::max(height, face->glyph->bitmap.rows);
    }

    font->atlas_size = glm::ivec2(width, height);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &font->glyph_atlas);
    glBindTexture(GL_TEXTURE_2D, font->glyph_atlas);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, width, height);
    int x = 0;
    for (int i = 0; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            Debug::Log(LogSeverity::Warning, "Could not load glyph " + i);
            continue;
        }
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_LUMINANCE, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        x += face->glyph->bitmap.width;
        Character character;
        character.advance = glm::ivec2(face->glyph->advance.x, face->glyph->advance.y);
        character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character.position = glm::vec2((float)x, 0);

        font->characters.insert(std::pair<char, Character>(i, character));
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    return font;
}
