#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include <GL/glew.h>
#include <string>
#include <iostream>

#include <Mesh.h>
#include <stb_image.h>

using antisocial::Mesh;

#define CUBE_MAP_FRONT   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
#define CUBE_MAP_BACK    GL_TEXTURE_CUBE_MAP_POSITIVE_Z
#define CUBE_MAP_TOP     GL_TEXTURE_CUBE_MAP_POSITIVE_Y
#define CUBE_MAP_BOTTOM  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
#define CUBE_MAP_RIGHT   GL_TEXTURE_CUBE_MAP_POSITIVE_X
#define CUBE_MAP_LEFT    GL_TEXTURE_CUBE_MAP_NEGATIVE_X

namespace antisocial
{

    class Skybox
    {
    public:
        Skybox(std::string front, std::string back, std::string top, std::string bottom, std::string right, std::string left, Mesh* mesh);
        ~Skybox();

        void draw();

    private:
        bool loadSideTexture(GLenum side, std::string file);

    private:
        GLuint _cubeMapHandle;
        Mesh* _cubeMesh;

        typedef struct
        {
            unsigned char imageTypeCode;
            short int imageWidth;
            short int imageHeight;
            unsigned char bitCount;
            unsigned char *imageData;
        } TGAFILE;

        bool LoadTGAFile(const char *filename, TGAFILE *tgaFile)
        {
            FILE *filePtr;
            unsigned char ucharBad;
            short int sintBad;
            long imageSize;
            int colorMode;
            unsigned char colorSwap;

            // Open the TGA file.
            filePtr = fopen(filename, "rb");
            if (filePtr == NULL)
            {
                return false;
            }

            // Read the two first bytes we don't need.
            fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
            fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

            // Which type of image gets stored in imageTypeCode.
            fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

            // For our purposes, the type code should be 2 (uncompressed RGB image)
            // or 3 (uncompressed black-and-white images).
            if (tgaFile->imageTypeCode != 2 && tgaFile->imageTypeCode != 3)
            {
                fclose(filePtr);
                return false;
            }

            // Read 13 bytes of data we don't need.
            fread(&sintBad, sizeof(short int), 1, filePtr);
            fread(&sintBad, sizeof(short int), 1, filePtr);
            fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
            fread(&sintBad, sizeof(short int), 1, filePtr);
            fread(&sintBad, sizeof(short int), 1, filePtr);

            // Read the image's width and height.
            fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
            fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

            // Read the bit depth.
            fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

            // Read one byte of data we don't need.
            fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

            // Color mode -> 3 = BGR, 4 = BGRA.
            colorMode = tgaFile->bitCount / 8;
            imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

            // Allocate memory for the image data.
            tgaFile->imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

            // Read the image data.
            fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

            // Change from BGR to RGB so OpenGL can read the image data.
            for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
            {
                colorSwap = tgaFile->imageData[imageIdx];
                tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
                tgaFile->imageData[imageIdx + 2] = colorSwap;
            }

            fclose(filePtr);
            return true;
        }
    };

}

#endif // __SKYBOX_H__
