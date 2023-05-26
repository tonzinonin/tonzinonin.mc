#include "Texture.h"

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glActiveTexture(GL_TEXTURE0 + slot);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}