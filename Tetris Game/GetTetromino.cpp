#include <vector>
#include <iostream>
#include "Headers/Global.hpp"
#include "Headers/GetTetromino.hpp"

	/* The word "muscle" comes from a Latin term meaning "little mouse."
		Bend your arm at the elbow and flex. What do you see when you look at your bicep? 
		The ancient Romans apparently saw the resemblance of a tiny rodent, which is why 
		it's called a "muscle," a word derived from the Latin term musculus—meaning "little mouse," 
		according to Merriam-Webster.
	*/


std::vector<Position> get_tetromino(int i_shape, int i_x, int i_y){

    std::vector<Position> output_tetromino(4);

    switch (i_shape)
	{
		case 0: // I
		{
			output_tetromino[0] = {0, -1};
			output_tetromino[1] = {1,-1};
			output_tetromino[2] = {-1, -1};
			output_tetromino[3] = {-2, -1};

			break;
		}
		case 1: // J
		{
			output_tetromino[0] = {0, 0};
			output_tetromino[1] = {1, 0};
			output_tetromino[2] = {-1, -1};
			output_tetromino[3] = {-1, 0};

			break;
		}
		case 2: // L
		{
			output_tetromino[0] = {0, 0};
			output_tetromino[1] = {1, 0};
			output_tetromino[2] = {1, -1};
			output_tetromino[3] = {-1, 0};

			break;
		}
		case 3: // O
		{
			output_tetromino[0] = {0, 0};
			output_tetromino[1] = {0, -1};
			output_tetromino[2] = {-1, -1};
			output_tetromino[3] = {-1, 0};

			break;
		}
		case 4: // S
		{
			output_tetromino[0] = {0, 0};
			output_tetromino[1] = {1, -1};
			output_tetromino[2] = {0, -1};
			output_tetromino[3] = {-1, 0};

			break;
		}
		case 5: // T
		{
			output_tetromino[0] = {0, 0};
			output_tetromino[1] = {1, 0};
			output_tetromino[2] = {0, -1};
			output_tetromino[3] = {-1, 0};

			break;
		}
		case 6: // Z
		{
			output_tetromino[0] = {0, 0};
			output_tetromino[1] = {1, 0};
			output_tetromino[2] = {0, -1};
			output_tetromino[3] = {-1, -1};
		}
	}

    for(int i=0; i<4; i++){
        
        output_tetromino[i].x += i_x;
        output_tetromino[i].y += i_y;
    }
    return output_tetromino;
}