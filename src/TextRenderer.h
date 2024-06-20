#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H


#include <glad/glad.h> // Use GLAD instead of GLEW
#include <GLFW/glfw3.h> // GLFW header
#include <glm/glm.hpp>  // GLM header
#include <ft2build.h>   // FreeType header
#include FT_FREETYPE_H  
#include <map>
#include <string>

struct Character {
    GLuint TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;  // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    std::map<GLchar, Character> Characters;
    GLuint VAO, VBO;
    int screenWidth, screenHeight;

    TextRenderer(int screenWidth, int screenHeight);

    void Load(std::string font, GLuint fontSize);
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

#endif