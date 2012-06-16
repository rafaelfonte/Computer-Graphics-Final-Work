#ifndef TEXTURE_H
#define TEXTURE_H

#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include "bitmap.h"

class Texture
{
  public:

    BITMAPINFO *info;        /* Bitmap information */

    GLubyte *bits;           /* Bitmap RGB pixels */

    GLubyte *ptr;            /* Pointer into bit buffer */

    GLubyte *rgba;           /* RGBA pixel buffer */

    GLubyte *rgbaptr;        /* Pointer into RGBA buffer */

    GLubyte temp;            /* Swapping variable */

    GLenum type;             /* Texture type */

    GLuint texture;          /* Texture object */

    Texture();

    virtual ~Texture();

    void initTexture(char *path);

  protected:
  private:
};

#endif // TEXTURE_H
