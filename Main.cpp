#include "Constants.h"
#include "graphics.h"
#include "Image.h"
#include "Grid.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	int page = 0;
	int mouseX, mouseY;
	double bias;
	double redResidents;
	double greenResidents;
	bool done = false;
	char keyInput = NULL;


	cout << "Enter the level of bias (0.0 - 1.00): " << endl;
	do{
		cin >> bias;
		if (bias < 0 || bias > 1)
			cout << "Enter the level of bias (0.0 - 1.00): " << endl;
	} while (bias < 0 || bias > 1);

	do{
		cout << "You will now enter the proportion of residents.  This will represent how many" << endl;
		cout << "households are composed of each type of resident.  The sum of the proportions" << endl;
		cout << "does not need to be 100%. There can be empty households." << endl;

		cout << "Enter the proportion of red residents (0.0 - 1.00): " << endl;
		cin >> redResidents;
		cout << "Enter the proportion of green residents (0.0 - 1.00): " << endl;
		cin >> greenResidents;
		if (redResidents + greenResidents < 0 || redResidents + greenResidents > 1)
			cout << "The sum of the proportions must be less than or equal to 1: " << endl;
	} while (redResidents + greenResidents < 0 || redResidents + greenResidents > 1);



	initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Segregation Project");
	Grid grid(GRID_X_POSITION, GRID_Y_POSITION, redResidents, greenResidents, bias);
	grid.checkResidentSimilarity();


	while (!done)
	{
		grid.checkResidentSimilarity();
		grid.draw();
		
		if (mousex() > GRID_X_POSITION && mousex() < (GRID_X_POSITION + GRID_PIXEL_WIDTH) &&
			mousey() > GRID_Y_POSITION && mousey() < (GRID_Y_POSITION + GRID_PIXEL_HEIGHT))
		{

			if (ismouseclick(WM_LBUTTONDOWN))
			{
				getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
				grid.printGridCoordinates(mouseX, mouseY);
				grid.removeResident(mouseX, mouseY);
			}

			if (ismouseclick(WM_LBUTTONUP))
			{
				getmouseclick(WM_LBUTTONUP, mouseX, mouseY);
				grid.printGridCoordinates(mouseX, mouseY);
				grid.placeResident(mouseX, mouseY);
			}

			if (grid.tempHousingOccupied())
			{
				grid.moveResident(mousex(), mousey());
			}
		}

		while (kbhit())
		{
			keyInput = getch();
		}

		switch (keyInput)
		{
		case ESC:
			done = true;
			break;
		}

		setvisualpage(page);
		page = !page;
		setactivepage(page);
		delay(FRAME_DELAY);
		cleardevice();
		keyInput = NULL;
	}

	return 0;
}