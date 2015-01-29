#pragma once
#include "Image.h"

enum state {
	HAPPY,
	INDIFFERENT,
	SAD
};
enum type {
	RED_PERSON = 0,
	GREEN_PERSON
};

class Person
{
public:
	//constructors
	Person(int x, int y, int gridX, int gridY, double bias, type residentType, Image& happy, Image& indifferent, Image& sad);
	Person(const Person& source);//copy constructor
	
	//Assignment operator
	Person& operator=(const Person& source);

	//draw function
	void draw() const;
	void setMood(int greenNeighbors, int redNeighbors);
	void setGridCoordinates(int x, int y);
	void move(int x, int y);
	double calculateSimilarity(int greenNeighbors, int redNeighbors);
	double getSimilarity() const;
	int getGridX() const;
	int getGridY() const;
	type getType() const;
	state getMood() const;
private:
	int x_;
	int y_;
	int gridX_;
	int gridY_;
	double similarity_;
	double bias_;
	type residentType_;
	state mood_;
	Image* happy_;
	Image* indifferent_;
	Image* sad_;
};