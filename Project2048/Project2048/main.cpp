#include <stdio.h>
#include <easyx.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#define GRID_WIDTH 100	// width of grid
#define INTERVAL	15	// the distance between adjacent grids
#define GRID_NUM	5	// the number of grids in each row and column


enum Color
{
	zero = RGB(205, 193, 180),
	twoTo1 = RGB(238, 228, 218),
	twoTo2 = RGB(237, 224, 200),
	twoTo3 = RGB(242, 177, 121),
	twoTo4 = RGB(245, 149, 99),
	twoTo5 = RGB(246, 124, 95),
	twoTo6 = RGB(246, 94, 59),
	twoTo7 = RGB(242, 177, 121),
	twoTo8 = RGB(237, 204, 97),
	twoTo9 = RGB(255, 0, 128),
	twoTo10 = RGB(145, 0, 72),
	twoTo11 = RGB(242, 17, 158),
	back = RGB(187, 173, 160),
};

Color colors[13] = { zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11, back };


int map[GRID_NUM][GRID_NUM];

// Randomly generate 2 or 4
int rand2Or4()
{
	return 2;
}


// Put generated numbers into map
void createNumber()
{
	while (true)
	{
		int r = rand() % GRID_NUM;
		int c = rand() % GRID_NUM;

		if (map[r][c] == 0)
		{
			map[r][c] = rand2Or4();
			break;
		}

	}

}

void init()
{
	createNumber();
	createNumber();

}


void draw()
{
	// set the grids
	for (int r = 0; r < GRID_NUM; r++)
	{
		for (int c = 0; c < GRID_NUM; c++)
		{
			// coordinates of each grid
			int x = c * GRID_WIDTH + (c + 1) * INTERVAL;
			int y = r * GRID_WIDTH + (r + 1) * INTERVAL;

			// set grid's background color
			int index = map[r][c];
			setfillcolor(colors[index]);

			// Convert data into the graphics
			solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);
			if (map[r][c] != 0)
			{
				// assign numbers to grid
				settextcolor(RGB(119, 110, 101));	// font color
				settextstyle(50, 0, "华文新魏");	// font style
				char str[5] = { 0 };
				sprintf(str, "%d", map[r][c]);
				int horspace = (GRID_WIDTH - textwidth(str)) / 2;	// add horizontal space
				int vecspace = (GRID_WIDTH - textheight(str)) / 2;	// add vertical space

				outtextxy(x + horspace, y + vecspace, str);	// make number in the mid of grid
			}
			
		}
	}
	
}

void moveUp()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		int temp = 0;
		for (int beg = 1; beg < GRID_NUM; beg++)
		{
			if (map[beg][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[beg][i];
					map[beg][i] = 0;
				}
				else if (map[temp][i] == map[beg][i])
				{
					map[temp][i] *= 2;
					map[beg][i] = 0;
					++temp;
				}
				else
				{
					map[temp + 1][i] = map[beg][i];
					if (temp + 1 != beg)
						map[beg][i] = 0;
					++temp;
				}
			}
		}
	}
}

void moveDown()
{
	for (int i = 0; i < GRID_NUM; i++)	// as column
	{
		int temp = GRID_NUM - 1;
		for (int beg = GRID_NUM - 2; beg >= 0; beg--) // as row
		{
			if (map[beg][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[beg][i];
					map[beg][i] = 0;
				}
				else if (map[temp][i] == map[beg][i])
				{
					map[temp][i] *= 2;
					map[beg][i] = 0;
					--temp;
				}
				else
				{
					map[temp - 1][i] = map[beg][i];
					if (temp - 1 != beg)
						map[beg][i] = 0;
					--temp;
				}
			}
		}
	}
}

void moveRight()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		int temp = GRID_NUM - 1;
		for (int beg = GRID_NUM - 2; beg >= 0; beg--)
		{
			if (map[i][beg] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][beg];
					map[i][beg] = 0;
				}
				else if (map[i][temp] == map[i][beg])
				{
					map[i][temp] *= 2;
					map[i][beg] = 0;
					--temp;
				}
				else
				{
					map[i][temp - 1] = map[i][beg];
					if (temp - 1 != beg)
						map[i][beg] = 0;
					--temp;
				}
			}
		}
	}
}

void moveLeft()
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		int temp = 0;
		for (int beg = 1; beg < GRID_NUM; beg++)
		{
			if (map[i][beg] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][beg];
					map[i][beg] = 0;
				}
				else if (map[i][temp] == map[i][beg])
				{
					map[i][temp] *= 2;
					map[i][beg] = 0;
					++temp;
				}
				else
				{
					map[i][temp+1] = map[i][beg];
					if (temp + 1 != beg)
						map[i][beg] = 0;
					++temp;
				}
			}
		}
	}
}

void keyEvent()
{
	int key = _getch();
	switch (key)
	{
	case 72:
		moveUp();
		createNumber();
		break;
	case 80:
		moveDown();
		createNumber();
		break;
	case 75:
		moveLeft();
		createNumber();
		break;
	case 77:
		moveRight();
		createNumber();
		break;

	}
}


int main()
{
	// Create graph window
	int windows_length = GRID_NUM * GRID_WIDTH + (GRID_NUM + 1) * INTERVAL;

	initgraph(windows_length, windows_length, EW_SHOWCONSOLE);

	// Set window's background color
	setbkcolor(RGB(187, 173, 160));
	cleardevice();

	// Set background mode to be transparent
	setbkmode(TRANSPARENT);
	
	// Initiallize the graph
	srand(time(NULL));
	init();


	while (true)
	{
		draw();
		keyEvent();
	}

//	getchar();


	return 0;
}
