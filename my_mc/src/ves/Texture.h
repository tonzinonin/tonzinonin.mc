#pragma once

#include <iostream>
#include "GL/glew.h"
#include "../thr/stb_image/stb_image.h"
#include <vector>

class Texture
{   
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    void T_INIT(const std::string& path , GLint renderer_mode)
    {
        m_FilePath = path;
        m_RendererID = 0;
        m_LocalBuffer = 0;
        m_Width = 0;
        m_Height = 0;
        m_BPP = 0;

        //stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

        if (m_LocalBuffer)
        {
            glGenTextures(1, &m_RendererID);
            glBindTexture(GL_TEXTURE_2D, m_RendererID);
            std::cout << "Texture:" << m_RendererID << std::endl;

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            //std::cout << m_BPP << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, renderer_mode , m_Width, m_Height, 0, renderer_mode, GL_UNSIGNED_BYTE, m_LocalBuffer);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        else std::cout << "texture not found" << std::endl;

        stbi_image_free(m_LocalBuffer);
    }
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetRendererID() const { return m_RendererID; }
};
