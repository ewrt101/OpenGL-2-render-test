#include "TextureLoader.h"
#include "loadTGA.h"
#include "loadBMP.h"

//TGA
TextrueLoader_TGA::TextrueLoader_TGA(const char* _fname){
    fname = _fname;
}

void TextrueLoader_TGA::loadTexture()				
{
    cout << " Trying to load file"<< endl;
	glGenTextures(1, &txId); 				// Create a Texture object
	glBindTexture(GL_TEXTURE_2D, txId);		//Use this texture
    loadTGA(fname);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	cout << " Texture loaded"<< endl;
}

//BMP
TextrueLoader_BMP::TextrueLoader_BMP(const char* _fname){
    fname = _fname;
}

void TextrueLoader_BMP::loadTexture()				
{
    cout << " Trying to load file"<< endl;
	glGenTextures(1, &txId); 				// Create a Texture object
	glBindTexture(GL_TEXTURE_2D, txId);		//Use this texture
    loadBMP(fname);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	cout << " Texture loaded"<< endl;
}
