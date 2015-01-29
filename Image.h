//Must call initwindow for create instance of this class.
#pragma once
#include "graphics.h"
#include <string>
#include <fstream>

typedef char Byte;
typedef char* ByteStream;

class Image
{
public:
	//Constructors
	Image(const char* filePath, int pixelWidth, int pixelHeight);
	Image(const Image& source); //copy constructor
	Image(Image&& source); // move constructor
	~Image(); //destructor

	//Assignment Operators
	Image& operator=(const Image& source);
	Image& operator=(Image&& source); //Move Assignment

	//Display Image: (x, y) is top left coordinate
	void displayImage(int x, int y) const;

	int getImageWidth() const;
	int getImageHeight() const;
	void changeImage(const char* filePath, int pixelWidth, int pixelHeight);
private:
	ByteStream image_;
	int imageSize_;
	int imageWidth_;
	int imageHeight_;
};