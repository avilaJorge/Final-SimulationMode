#include "Constants.h"
#include "Fraction.h"
#include "Person.h"
#include <cmath>
#include <iostream>


Person::Person(int x, int y, int gridX, int gridY, double bias, type residentType, Image& happy, Image& indifferent, Image& sad)
{
	x_ = x;
	y_ = y;
	gridX_ = gridX;
	gridY_ = gridY;
	bias_ = bias;
	residentType_ = residentType;
	mood_ = INDIFFERENT;
	happy_ = &happy;
	indifferent_ = &indifferent;
	sad_ = &sad;
}

//copy constructor
Person::Person(const Person& source)
{
	x_ = source.x_;
	y_ = source.y_;
	gridX_ = source.gridX_;
	gridY_ = source.gridY_;
	bias_ = source.bias_;
	residentType_ = source.residentType_;
	mood_ = source.mood_;
	happy_ = source.happy_;
	indifferent_ = source.indifferent_;
	sad_ = source.sad_;
}

//assigment operator
Person& Person::operator=(const Person& source)
{
	if (&source != this)
	{
		x_ = source.x_;
		y_ = source.y_;
		gridX_ = source.gridX_;
		gridY_ = source.gridY_;
		bias_ = source.bias_;
		residentType_ = source.residentType_;
		mood_ = source.mood_;
		happy_ = source.happy_;
		indifferent_ = source.indifferent_;
		sad_ = source.sad_;
	}
	
	return *this;
}

void Person::draw() const
{
	if (mood_ == HAPPY)
		happy_->displayImage(x_, y_);
	else if (mood_ == INDIFFERENT)
		indifferent_->displayImage(x_, y_);
	else if (mood_ == SAD)
		sad_->displayImage(x_, y_);

}

double Person::calculateSimilarity(int greenNeighbors, int redNeighbors)
{
	int localResidents = greenNeighbors + redNeighbors;
	Math::Fraction similarityFraction = Math::Fraction(greenNeighbors, localResidents) - Math::Fraction(redNeighbors, localResidents);
	similarity_ = 100 * std::abs(static_cast<double>(similarityFraction));
	return similarity_;
}

void Person::setMood(int greenNeighbors, int redNeighbors)
{
	double localResidents = greenNeighbors + redNeighbors;
	double similarResidents;
	double oppositeResidents;
	double percentageSimilar;

	if (residentType_ == GREEN_PERSON)
	{
		similarResidents = greenNeighbors;
		oppositeResidents = redNeighbors;
	}
	else
	{
		similarResidents = redNeighbors;
		oppositeResidents = greenNeighbors;
	}

	//Prevent Division by 0
	if (localResidents > 0)
		percentageSimilar = similarResidents / localResidents;
	else percentageSimilar = 0.0;

	if ( percentageSimilar > bias_ && oppositeResidents > 0)
		mood_ = HAPPY;
	else if (percentageSimilar >= bias_)
		mood_ = INDIFFERENT;
	else if (percentageSimilar < bias_)
		mood_ = SAD;
}

double Person::getSimilarity() const
{
	return similarity_;
}

int Person::getGridX() const
{
	return gridX_;
}

int Person::getGridY() const
{
	return gridY_;
}

type Person::getType() const
{
	return residentType_;
}

state Person::getMood() const
{
	return mood_;
}

void Person::setGridCoordinates(int x, int y)
{
	gridX_ = x;
	gridY_ = y;
	x_ = GRID_X_POSITION + (GRID_PIECE_SIDE * gridX_);
	y_ = GRID_Y_POSITION + (GRID_PIECE_SIDE * gridY_);
}

void Person::move(int x, int y)
{
	x_ = GRID_X_POSITION + (GRID_PIECE_SIDE * x);
	y_ = GRID_Y_POSITION + (GRID_PIECE_SIDE * y);

}
