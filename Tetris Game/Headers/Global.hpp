#pragma once

	constexpr unsigned char CELL_SIZE = 30;
	constexpr unsigned char COLUMNS = 10;
	constexpr unsigned char ROWS = 20;
	constexpr unsigned char MOVE_SPEED = 4;
	extern int orientation; //0 is the origin

	// Store the x & y coordinates and what type of shape it is
	struct Position 
	{int x, y;};
	
	struct info
	{int shape, mark;};
