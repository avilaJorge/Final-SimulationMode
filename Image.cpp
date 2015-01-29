#include "Image.h"

Image::Image(const char* filePath, int pixelWidth, int pixelHeight)
{
	imageWidth_ = pixelWidth;
	imageHeight_ = pixelHeight;

	changeImage(filePath, imageWidth_, imageHeight_);
}

Image::~Image()
{
	delete[] image_;
}

//Copy constructor
Image::Image(const Image& source)
{
	imageSize_ = source.imageSize_;
	imageWidth_ = source.imageWidth_;
	imageHeight_ = source.imageHeight_;

	//deep copy 
	image_ = new Byte[imageSize_];
	//copy in image data
	for (int i = 0; i < imageSize_; i++)
	{
		image_[i] = source.image_[i];
	}
}

//Move  Constructor
Image::Image(Image&& source)
{
	imageSize_ = source.imageSize_;
	imageWidth_ = source.imageWidth_;
	imageHeight_ = source.imageHeight_;

	image_ = source.image_; //shallow copy in move constructor instead of deep copy
	source.image_ = nullptr;//then unlink the original pointer
}

//Assignment Operator
Image& Image::operator=(const Image& source)
{
	//In case the same object is on both sides of the assigment operator
	if (&source != this)
	{
		//destructor
		//delete what is currently stored in image_
		delete image_;

		//copy constructor
		imageSize_ = source.imageSize_;
		imageWidth_ = source.imageWidth_;
		imageHeight_ = source.imageHeight_;

		image_ = new Byte[imageSize_];

		for (int i = 0; i < imageSize_; i++)
		{
			image_[i] = source.image_[i];
		}
	}

	return *this;
}

//Move Assignment Operator
Image& Image::operator=(Image&& source)
{
	//to avoid moving into yourself
	if (&source != this)
	{
		//destructor
		delete image_;

		//move constructor
		imageSize_ = source.imageSize_;
		imageWidth_ = source.imageWidth_;
		imageHeight_ = source.imageHeight_;

		image_ = source.image_; //shallow copy
		source.image_ = nullptr;
	}
	return *this;
}

void Image::changeImage(const char* filePath, int pixelWidth, int pixelHeight)
{
	imageWidth_ = pixelWidth;
	imageHeight_ = pixelHeight;

	readimagefile(filePath, 0, 0, pixelWidth, pixelHeight);
	imageSize_ = imagesize(0, 0, pixelWidth, pixelHeight) / sizeof(Byte);
	image_ = new Byte[imageSize_];
	getimage(0, 0, pixelWidth, pixelHeight, image_);
	cleardevice();
}

void Image::displayImage(int x, int y) const
{
	putimage(x, y, image_, COPY_PUT);
}

int Image::getImageWidth() const
{
	return imageWidth_;
}

int Image::getImageHeight() const
{
	return imageHeight_;
}