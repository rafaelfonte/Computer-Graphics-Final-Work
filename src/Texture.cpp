#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{
  //dtor
}

void Texture::initTexture(char *path) {
  //ctor
	//printf ("\nLoading texture..\n");
  // Load a texture object (256x256 true color)
  bits = LoadDIBitmap(path, &info);
  if (bits == (GLubyte *)0) {
		//printf ("Error loading texture!\n\n");
	} else {
    // Figure out the type of texture
    if (info->bmiHeader.biHeight == 1) {
      type = GL_TEXTURE_1D;
    } else {
      type = GL_TEXTURE_2D;
    }

    // Create and bind a texture object
    glGenTextures(1, &texture);
    glBindTexture(type, texture);

    // Create an RGBA image
    rgba = (GLubyte *)malloc(info->bmiHeader.biWidth * info->bmiHeader.biHeight * 4);

    int i;
    i = info->bmiHeader.biWidth * info->bmiHeader.biHeight;
    for(rgbaptr = rgba, ptr = bits;  i > 0; i--, rgbaptr += 4, ptr += 3)
    {
      rgbaptr[0] = ptr[2];     // windows BMP = BGR
      rgbaptr[1] = ptr[1];
      rgbaptr[2] = ptr[0];
      rgbaptr[3] = (ptr[0] + ptr[1] + ptr[2]) / 3;
    }

    // Set texture parameters
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(type, 0, 4, info->bmiHeader.biWidth, info->bmiHeader.biHeight,
                    0, GL_RGBA, GL_UNSIGNED_BYTE, rgba );
    //printf("Textures ok.\n\n", texture);
	}
}
