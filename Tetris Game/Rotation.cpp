#include "Headers/Global.hpp"
#include "Headers/GetTetromino.hpp"
#include "Headers/Rotation.hpp"
#include <iostream>

// Note: shape "O" is not included in the rotation since it is the same when you rotate it... OBVIOUSLY!!!!!!
// rotation = 0 is the origin

/*  Never gonna give you up
    Never gonna let you down
    Never gonna run around and desert you
    Never gonna make you cry
    Never gonna say goodbye
    Never gonna tell a lie and hurt you
*/

std::vector<Position> rotate(int i_shape, int i_x, int i_y){
    if(i_shape == 0){ // This prevent the I shape from moving up ang going out of bounds
        if(i_y == 0){i_y = 2;}
        if(i_y == 1){i_y = 2;}
    }
    
    if(i_shape == 0){
        if(i_x < 2){i_x = 2;}
        if(i_x > COLUMNS -2){i_x = COLUMNS-2;}
    }
    if(i_shape != 0){
        if(i_x < 1){i_x = 1;}
        if(i_x > COLUMNS -2){i_x = COLUMNS-2;}
    }
    std::vector<Position> output_tetromino(4);

    switch(i_shape){
        case 0:
            switch(orientation){ // I
                case 0: 
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1,0};
                    output_tetromino[2] = {-1, 0};
                    output_tetromino[3] = {-2, 0};
                    break;
                case 1:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0,1};
                    output_tetromino[2] = {0, -1};
                    output_tetromino[3] = {0, -2};
                    break;
                case 2: 
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1,0};
                    output_tetromino[2] = {-1, 0};
                    output_tetromino[3] = {-2, 0};
                    break;
                case 3:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0,1};
                    output_tetromino[2] = {0, -1};
                    output_tetromino[3] = {0, -2};
                    break;
            }
            break;
        case 1:
            switch(orientation){ // J
                case 0:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1, 0};
                    output_tetromino[2] = {-1, -1};
                    output_tetromino[3] = {-1, 0};
                    break;
                case 1:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0,1};
                    output_tetromino[2] = {1,-1};
                    output_tetromino[3] = {0,-1};
                    break;
                case 2:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {-1,0};
                    output_tetromino[2] = {1,1};
                    output_tetromino[3] = {1,0};
                    break;
                case 3:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0,-1};
                    output_tetromino[2] = {-1,1};
                    output_tetromino[3] = {0,1};
                    break;
            }
            break;
        case 2:
            switch(orientation){ // L
                case 0:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1, 0};
                    output_tetromino[2] = {1, -1};
                    output_tetromino[3] = {-1, 0};
                    break;
                case 1:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0,1};
                    output_tetromino[2] = {1,1};
                    output_tetromino[3] = {0,-1};
                    break;
                case 2:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {-1,0};
                    output_tetromino[2] = {-1,1};
                    output_tetromino[3] = {1,0};
                    break;
                case 3:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0,-1};
                    output_tetromino[2] = {-1,-1};
                    output_tetromino[3] = {0,1};
                    break;
            }
            break;
        
        // So I remove the rotation for the O shape because it is stupid
        case 4: 
            switch(orientation){ // S
                case 0:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1, -1};
                    output_tetromino[2] = {0, -1};
                    output_tetromino[3] = {-1, 0};
                    break;
                case 1:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1,1};
                    output_tetromino[2] = {1, 0};
                    output_tetromino[3] = {0, -1};
                    break;
                case 2:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {-1, 1};
                    output_tetromino[2] = {0, 1};
                    output_tetromino[3] = {1, 0};
                    break;
                case 3:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {-1, -1};
                    output_tetromino[2] = {-1, 0};
                    output_tetromino[3] = {0, 1};
                    break;
            }
            break;
        case 5:
            switch(orientation){ // T
                case 0:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1, 0};
                    output_tetromino[2] = {0, -1};
                    output_tetromino[3] = {-1, 0};
                    break;
                case 1:
                    output_tetromino[0] = {0,0};
                    output_tetromino[1] = {0,1};
                    output_tetromino[2] = {1,0};
                    output_tetromino[3] = {0,-1};
                    break;
                case 2:
                    output_tetromino[0] = {0,0};
                    output_tetromino[1] = {-1,0};
                    output_tetromino[2] = {0,1};
                    output_tetromino[3] = {1,0};
                    break;
                case 3:
                    output_tetromino[0] = {0,0};
                    output_tetromino[1] = {0,-1};
                    output_tetromino[2] = {-1,0};
                    output_tetromino[3] = {0,1};
                    break;
            }
            break;
        case 6:
            switch(orientation){ // Z
                case 0:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {1, 0};
                    output_tetromino[2] = {0, -1};
                    output_tetromino[3] = {-1, -1};
                    break;
                case 1:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0,1};
                    output_tetromino[2] = {1, 0};
                    output_tetromino[3] = {1, -1};
                    break;
                case 2:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {-1, 0};
                    output_tetromino[2] = {0, 1};
                    output_tetromino[3] = {1, 1};
                    break;
                case 3:
                    output_tetromino[0] = {0, 0};
                    output_tetromino[1] = {0, -1};
                    output_tetromino[2] = {-1, 0};
                    output_tetromino[3] = {-1, 1};
                    break;
            }
            break;
        deafult:
            break;
    }
    for(int i=0; i<4; i++){
        output_tetromino[i].x += i_x;
        output_tetromino[i].y += i_y;
    }
    return output_tetromino;
}
