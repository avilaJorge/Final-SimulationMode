#pragma once
#include "Person.h"
#include "Constants.h"
#include "Image.h"
#include <string>

class Grid
{
public:
	Grid(int x, int y, double proportionRed, double proportionGreen, double bias); //top left corner of drawn grid
	~Grid();
	Grid(const Grid& source); // copy constructor
	Grid(Grid&& source); //move constructor
	Grid& operator=(const Grid& source); //Assignment Operator
	Grid& operator=(Grid&& source); //Move Assignment
	void draw() const;
	void initializeResidentGrid();
	void checkResidentSimilarity();
	void setBias(double bias);
	void printResidents() const;
	void removeResident(int x, int y);
	void placeResident(int x, int y);
	void printGridCoordinates(int x, int y);
	void moveResident(int x, int y);
	bool tempHousingOccupied() const;
private:
	int x_;
	int y_;
	int sadCount_;
	int redResidents_;
	int greenResidents_;
	double proportionRed_;
	double proportionGreen_;
	double bias_;
	double segregation_;
	Person* temporaryHousing_;
	std::string proportionRedStr_;
	std::string proportionGreenStr_;
	std::string biasStr_;
	std::string segregationStr_;
	std::string percentSymbol_ = "%";
	Image greenHappy_ = Image("green_happy.bmp", GRID_PIECE_SIDE, GRID_PIECE_SIDE);
	Image greenIndifferent_ = Image("green_indifferent.bmp", GRID_PIECE_SIDE, GRID_PIECE_SIDE);
	Image greenSad_ = Image("green_sad.bmp", GRID_PIECE_SIDE, GRID_PIECE_SIDE);
	Image redHappy_ = Image("red_happy.bmp", GRID_PIECE_SIDE, GRID_PIECE_SIDE);
	Image redIndifferent_ = Image("red_indifferent.bmp", GRID_PIECE_SIDE, GRID_PIECE_SIDE);
	Image redSad_ = Image("red_sad.bmp", GRID_PIECE_SIDE, GRID_PIECE_SIDE);
	Person* createResident(int selection, int gridX, int gridY); //0 returns RED_PERSON, 1 returns GREEN_PERSON, 2 returns nullptr
	Person* residents_[GRID_HEIGHT][GRID_WIDTH];
};