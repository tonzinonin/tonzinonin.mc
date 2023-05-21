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
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetRendererID() const { return m_RendererID; }
};
