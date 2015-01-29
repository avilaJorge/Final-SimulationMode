#include "Grid.h"
#include "Constants.h"
#include <iostream>

Grid::Grid(int x, int y, double proportionRed, double proportionGreen, double bias)
{
	srand(GetTickCount());
	x_ = x;
	y_ = y;
	bias_ = bias;
	proportionRed_ = proportionRed;
	proportionGreen_ = proportionGreen;
	temporaryHousing_ = nullptr;
	biasStr_ = std::to_string(100 * bias_) + percentSymbol_;
	proportionRedStr_ = std::to_string(100 * proportionRed_) + percentSymbol_;
	proportionGreenStr_ = std::to_string(100 * proportionGreen_) + percentSymbol_;
	segregationStr_ = "0.00000" + percentSymbol_;
	initializeResidentGrid();
}

Grid::~Grid()
{
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			delete residents_[i][j];
		}
	}
}
// copy constructor
Grid::Grid(const Grid& source)
{
	x_ = source.x_;
	y_ = source.y_;
	bias_ = source.bias_;
	sadCount_ = source.sadCount_;
	redResidents_ = source.redResidents_;
	greenResidents_ = source.greenResidents_;
	proportionRed_ = source.proportionRed_;
	proportionGreen_ = source.proportionGreen_;
	temporaryHousing_ = source.temporaryHousing_;
	segregation_ = source.segregation_;
	biasStr_ = source.biasStr_;
	proportionRedStr_ = source.proportionRedStr_;
	proportionGreenStr_ = source.proportionGreenStr_;
	segregationStr_ = source.segregationStr_;

	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			residents_[i][j] = source.residents_[i][j];
		}
	}
}

//Assignment Operator
Grid& Grid::operator=(const Grid& source)
{
	if (&source != this)
	{
		x_ = source.x_;
		y_ = source.y_;
		bias_ = source.bias_;
		sadCount_ = source.sadCount_;
		redResidents_ = source.redResidents_;
		greenResidents_ = source.greenResidents_;
		proportionRed_ = source.proportionRed_;
		proportionGreen_ = source.proportionGreen_;
		temporaryHousing_ = source.temporaryHousing_;
		segregation_ = source.segregation_;
		biasStr_ = source.biasStr_;
		proportionRedStr_ = source.proportionRedStr_;
		proportionGreenStr_ = source.proportionGreenStr_;
		segregationStr_ = source.segregationStr_;

		for (int i = 0; i < GRID_HEIGHT; i++)
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				residents_[i][j] = source.residents_[i][j];
			}
		}
	}

	return *this;
}

void Grid::draw() const
{
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			if (residents_[i][j] != nullptr)
				residents_[i][j]->draw();
		}
	}

	if (tempHousingOccupied())
	{
		temporaryHousing_->draw();
	}

	setcolor(WHITE);
	rectangle(GRID_X_POSITION, GRID_Y_POSITION, GRID_X_POSITION + GRID_PIXEL_WIDTH, GRID_Y_POSITION + GRID_PIXEL_HEIGHT);
	rectangle(INFO_BOX_X, INFO_BOX_Y, INFO_BOX_X + INFO_BOX_WIDTH, INFO_BOX_Y + INFO_BOX_HEIGHT);
	outtextxy(INFO_BOX_TEXT_X, INFO_BOX_Y + (1 * SPACER), "Segregation:");
	outtextxy(INFO_BOX_TEXT_X + SPACER, INFO_BOX_Y + (3 * SPACER), const_cast<char*>(segregationStr_.c_str()));
	outtextxy(INFO_BOX_TEXT_X, INFO_BOX_Y + (5 * SPACER), "Bias Level:");
	outtextxy(INFO_BOX_TEXT_X + SPACER, INFO_BOX_Y + (7 * SPACER), const_cast<char*>(biasStr_.c_str()));
	outtextxy(INFO_BOX_TEXT_X, INFO_BOX_Y + (9 * SPACER), "Red Proportion:");
	outtextxy(INFO_BOX_TEXT_X + SPACER, INFO_BOX_Y + (11 * SPACER), const_cast<char*>(proportionRedStr_.c_str()));
	outtextxy(INFO_BOX_TEXT_X, INFO_BOX_Y + (13 * SPACER), "Green Proportion:");
	outtextxy(INFO_BOX_TEXT_X + SPACER, INFO_BOX_Y + (15 * SPACER), const_cast<char*>(proportionGreenStr_.c_str()));
	setcolor(RED);
	if (sadCount_ > 0)
		outtextxy(INFO_BOX_TEXT_X, INFO_BOX_Y + (18 * SPACER), "People are still unhappy! :(");
	else
		outtextxy(INFO_BOX_TEXT_X, INFO_BOX_Y + (18 * SPACER), "Everyone is satisfied...");
}

void Grid::removeResident(int x, int y)
{
	int gridX = (x - x_) / GRID_PIECE_SIDE;
	int gridY = (y - y_) / GRID_PIECE_SIDE;

	if (residents_[gridY][gridX] != nullptr)
	{
		if (residents_[gridY][gridX]->getMood() == SAD)
		{
			temporaryHousing_ = residents_[gridY][gridX];
			residents_[gridY][gridX] = nullptr;
		}
	}
}

void Grid::placeResident(int x, int y)
{
	int gridX = (x - x_) / GRID_PIECE_SIDE;
	int gridY = (y - y_) / GRID_PIECE_SIDE;

	if (tempHousingOccupied())
	{

		if (residents_[gridY][gridX] == nullptr)
		{
			temporaryHousing_->setGridCoordinates(gridX, gridY);
			residents_[gridY][gridX] = temporaryHousing_;
			temporaryHousing_ = nullptr;
		}
		else
		{
			gridX = temporaryHousing_->getGridX();
			gridY = temporaryHousing_->getGridY();
			temporaryHousing_->move(gridX, gridY);
			residents_[gridY][gridX] = temporaryHousing_;
			temporaryHousing_ = nullptr;
		}
	}
}

void Grid::moveResident(int x, int y)
{
	int gridX = (x - x_) / GRID_PIECE_SIDE;
	int gridY = (y - y_) / GRID_PIECE_SIDE;

	if (tempHousingOccupied())
	{
		temporaryHousing_->move(gridX, gridY);
	}
}

bool Grid::tempHousingOccupied() const
{
	if (temporaryHousing_ == nullptr)
		return false;
	else return true;
}

void Grid::printGridCoordinates(int x, int y)
{
	int gridX = (x - x_) / GRID_PIECE_SIDE;
	int gridY = (y - y_) / GRID_PIECE_SIDE;

	std::cout << "(" << gridX << ", " << gridY << ")" << std::endl;
}

void Grid::initializeResidentGrid()
{
	redResidents_ = (GRID_HEIGHT * GRID_WIDTH) * proportionRed_;
	greenResidents_ = (GRID_HEIGHT * GRID_WIDTH) * proportionGreen_;
	int vacant = (GRID_HEIGHT * GRID_WIDTH) - (redResidents_ + greenResidents_);
	int x = 0;
	int y = 0;

	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			residents_[i][j] = nullptr;
		}
	}

	for (int i = 0; i < redResidents_; i++)
	{
		x = rand() % GRID_WIDTH;
		y = rand() % GRID_HEIGHT;
		
		while (residents_[y][x] != nullptr)
		{
			x = rand() % GRID_WIDTH;
			y = rand() % GRID_HEIGHT;
		}
		residents_[y][x] = createResident(RED_PERSON, x, y);
	}

	for (int i = 0; i < greenResidents_; i++)
	{
		x = rand() % GRID_WIDTH;
		y = rand() % GRID_HEIGHT;

		while (residents_[y][x] != nullptr)
		{
			x = rand() % GRID_WIDTH;
			y = rand() % GRID_HEIGHT;
		}
		residents_[y][x] = createResident(GREEN_PERSON, x, y);
	}
}

void Grid::checkResidentSimilarity()
{
	sadCount_ = 0;
	segregation_ = 0;

	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			if (residents_[i][j] != nullptr)
			{

				int greenNeighbors = 0;
				int redNeighbors = 0;
				int gridX = 0;
				int gridY = 0;
				int residentX = residents_[i][j]->getGridX();
				int residentY = residents_[i][j]->getGridY();

				//check left side first
				gridX = residentX - 1;
				gridY = residentY;
				if (gridX >= 0)
				{
					//check upper left
					if (gridY - 1 >= 0)
					{
						if (residents_[gridY - 1][gridX] != nullptr)
						{
							if(residents_[gridY - 1][gridX]->getType() == GREEN_PERSON)
								greenNeighbors++;
							else redNeighbors++;
						}
					}

					//check left
					if (residents_[gridY][gridX] != nullptr)
					{
						if (residents_[gridY][gridX]->getType() == GREEN_PERSON)
							greenNeighbors++;
						else redNeighbors++;
					}

					//check bottom left
					if (gridY + 1 < GRID_HEIGHT)
					{
						if (residents_[gridY + 1][gridX] != nullptr)
						{
							if (residents_[gridY + 1][gridX]->getType() == GREEN_PERSON)
								greenNeighbors++;
							else redNeighbors++;
						}
					}
				}

				//check right side
				gridX = residentX + 1;
				if (gridX < GRID_WIDTH)
				{
					//check upper right
					if (gridY - 1 >= 0)
					{
						if (residents_[gridY - 1][gridX] != nullptr)
						{
							if(residents_[gridY - 1][gridX]->getType() == GREEN_PERSON)
								greenNeighbors++;
							else redNeighbors++;
						}
					}

					//check Right
					if (residents_[gridY][gridX] != nullptr)
					{
						if(residents_[gridY][gridX]->getType() == GREEN_PERSON)
							greenNeighbors++;
						else redNeighbors++;
					}

					//check bottom Right
					if (gridY + 1 < GRID_HEIGHT)
					{
						if (residents_[gridY + 1][gridX] != nullptr)
						{
							if (residents_[gridY + 1][gridX]->getType() == GREEN_PERSON)
								greenNeighbors++;
							else redNeighbors++;
						}
					}
				}

				//check above
				gridX = residentX;
				gridY = residentY - 1;
				if (gridY >= 0)
				{
					if (residents_[gridY][gridX] != nullptr)
					{
						if (residents_[gridY][gridX]->getType() == GREEN_PERSON)
							greenNeighbors++;
						else redNeighbors++;
					}
				}

				//check below
				gridY = residentY + 1;
				if (gridY < GRID_HEIGHT)
				{
					if (residents_[gridY][gridX] != nullptr)
					{
						if (residents_[gridY][gridX]->getType() == GREEN_PERSON)
							greenNeighbors++;
						else redNeighbors++;
					}
				}


				residentX = residents_[i][j]->getGridX();
				residentY = residents_[i][j]->getGridY();
				
				//set mood of resident based on types of surrounding residents.
				residents_[residentY][residentX]->setMood(greenNeighbors, redNeighbors);
				if (residents_[residentY][residentX]->getMood() == SAD)
					sadCount_++;

				//check yourself
				if (residents_[residentY][residentX]->getType() == GREEN_PERSON)
					greenNeighbors++;
				else redNeighbors++;

				//calculating similarity includes the type of this resident.
				segregation_ += residents_[residentY][residentX]->calculateSimilarity(greenNeighbors, redNeighbors);
			}
		}
	}
	segregation_ /= (redResidents_ + greenResidents_);
	segregationStr_ = std::to_string(segregation_) + percentSymbol_;
}

Person* Grid::createResident(int selection, int gridX, int gridY)
{
	switch (selection)
	{
	case 0:
		return new Person(x_ + (gridX * GRID_PIECE_SIDE), y_ + (gridY * GRID_PIECE_SIDE), gridX,
			gridY, bias_, RED_PERSON, redHappy_, redIndifferent_, redSad_);
		break;
	case 1:
		return new Person(x_ + (gridX * GRID_PIECE_SIDE), y_ + (gridY * GRID_PIECE_SIDE), gridX,
			gridY, bias_, GREEN_PERSON, greenHappy_, greenIndifferent_, greenSad_);
		break;
	default:
		return nullptr;
		break;
	}
}

void Grid::setBias(double bias)
{
	bias_ = bias;
}

void Grid::printResidents() const
{
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			if (residents_[i][j] == nullptr)
			{
				std::cout << "[ X ]";
			}
			else if (residents_[i][j]->getType() == GREEN_PERSON)
			{
				std::cout << "[ G ]";
			}
			else if (residents_[i][j]->getType() == RED_PERSON)
			{
				std::cout << "[ R ]";
			}
		}
		std::cout << std::endl;
	}
}