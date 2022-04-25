#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Headers/Global.hpp"
#include "Headers/GetTetromino.hpp"
#include "Headers/Rotation.hpp"

std::vector<Position> temp_tetromino(4); // I don't know what to comment on this one

bool trigger_next_tetromino = true; // Roll another tetromino
float speed = 0.8;  // Lower the value the faster
float soft_drop_speed = 0.1; // Softdrop speed
int move_side = 0, move_down = 0;
float movedown_timer=0, movedown_delay;  // I can do Fall_timer or Fall_delay but I'am already to lazy to change everything
bool gameplay = true;

int r, next_shape;      // the current shape / next shape
                        // I don't know why I name the current_shape "r" and again to lazy to change

int increase_speed_trigger=0;
int orientation = 0;    // what orientation the shape is

int line = 0;  // Do I need to explain this?
int level = 1; // Really?
int level_cap = 10; // every time the line goes this number increase the speed

// Color
std::vector<sf::Color> shape_color = {
    sf::Color(12, 12, 39),// Background
    sf::Color(12, 12, 39), // Outline
    sf::Color(51, 102, 255), // I
    sf::Color(0, 0, 204), // J
    sf::Color(204, 122, 0), // L
    sf::Color(255, 255, 0), // O
    sf::Color(153, 0, 153), // T
    sf::Color(0, 204, 0), // S
    sf::Color(255, 0, 0), // Z
    sf::Color(87,87,87), // Ghost mino
    sf::Color(114,114,114) // Game Over
};


// Mark the cell if it has minos on it
// Store a bunch of info
std::vector<std::vector<info>> matrix(ROWS, std::vector<info>(COLUMNS));

// Check the side collision
void Check_side_collision(std::vector<Position> tetromino){
    for(Position mino: tetromino){
    
        // Collision check for the side of the screen
        if((mino.x+move_side) < 0 || (mino.x+move_side) > COLUMNS-1){
            move_side = 0;
            break;
        }

        // Collision check for the side of the other tetromino
        // I just check the matrix if the position is already occupied 
        if(matrix[mino.y][mino.x + move_side].mark == 1){ 
            move_side = 0;
            break;
        }
    }
}

// Render the mino
void RenderDisplay(sf::RenderWindow& window, int& r, std::vector<Position>& tetromino, std::vector<Position>& ghost_tetromino){
    trigger_next_tetromino = false; // don't roll another tetromino while current is moving

    for(Position& mino: tetromino){
        int x = mino.x;
        int y = mino.y;

        if(y == 0 &&matrix[y][x].mark == 1 ){
            r = 8;
            mino.y -= 1;
        }
    }

    Check_side_collision(tetromino);
    
    // ghost mino
    for(int i = 0; i < ROWS; i++){
        for(Position& g_mino: ghost_tetromino){
            g_mino.y += 1;
        }
        for(Position& mino: ghost_tetromino){
            if(mino.y == 1){
                break;
            }
            // Very bottom of the screen
            if(mino.y==ROWS){
                for(Position& mino1: ghost_tetromino){
                    mino1.y -= 1;
                    sf::RectangleShape rect;
                    rect.setPosition(sf::Vector2f(mino1.x*CELL_SIZE,mino1.y*CELL_SIZE));
                    rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
                    rect.setOutlineColor(shape_color[1]);
                    rect.setOutlineThickness(-1);
                    rect.setFillColor(shape_color[9]);
                    window.draw(rect);
                }
                break;
            }
            // On top of another mino
            else if(matrix[mino.y][mino.x].mark == 1){
                for(Position& mino1: ghost_tetromino){
                    mino1.y -= 1;
                    sf::RectangleShape rect;
                    rect.setPosition(sf::Vector2f(mino1.x*CELL_SIZE,mino1.y*CELL_SIZE));
                    rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
                    rect.setOutlineColor(shape_color[1]);
                    rect.setOutlineThickness(-1);
                    rect.setFillColor(shape_color[9]);
                    window.draw(rect);
                }
                break;
            }
        }
    }
    temp_tetromino = ghost_tetromino; // Copy the position of ghost_mino to temp_mino for the use of hard_drop funstion

    // Loop to render all the mino
    for(Position& mino: tetromino){

        // A bunch of code for rendering all the mino
        mino.y += move_down;
        mino.x += move_side;
        sf::RectangleShape rect;
        rect.setPosition(sf::Vector2f(mino.x*CELL_SIZE,mino.y*CELL_SIZE));
        rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
        rect.setOutlineColor(shape_color[1]);
        rect.setOutlineThickness(-1);
        rect.setFillColor(shape_color[r+2]);
        window.draw(rect);
    }

    move_down = 0;
    move_side = 0;
}

// Check the Collision when falling
bool Check_Collision(std::vector<Position>& tetromino){
    for(Position mino: tetromino){
        
        // Collision check for the bottom of the screen
        if(mino.y==ROWS){
            for(Position mino1: tetromino){
            int x = mino1.y-1;
            int y = mino1.x;
            matrix[x][y].mark=1;    // mark the position in the matrix
            matrix[x][y].shape = r; // pass the shape of the tetromino to the matrix also
            }
            orientation = 0;
            trigger_next_tetromino = true;
            return true;    // return True means it collide
        }

        // Collision check for the other tetromino
        // I just check the matrix if the position is already occupied 
        else if(matrix[mino.y][mino.x].mark == 1){
            for(Position mino1: tetromino){
                int x = mino1.y-1;
                int y = mino1.x;
                matrix[x][y].mark=1;    // mark the position in the matrix
                matrix[x][y].shape = r; // pass the shape of the tetromino to the matrix also
            }
            orientation = 0;
            trigger_next_tetromino = true;
            return true;    // return True means it collide
        }
    }
    return false;   // return false means it didn't collide to anything
}

// Render the matrix
void RenderMatrix(sf::RenderWindow& window){
    if(!gameplay){
        for(int i=0; i<ROWS;i++){
            for(int j=0; j<COLUMNS;j++){
                matrix[i][j].mark = 0;
            }
        }
        gameplay = true;
        line = 0;
        level = 1;
        speed  = 0.8;
    }
    for(int i=0; i<ROWS;i++){
        for(int j=0; j<COLUMNS;j++){
            if(matrix[i][j].mark == 1){
                sf::RectangleShape rect;
                rect.setPosition(sf::Vector2f(j*CELL_SIZE,i*CELL_SIZE));
                rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
                rect.setOutlineColor(shape_color[1]);
                rect.setOutlineThickness(-1);
                rect.setFillColor(shape_color[matrix[i][j].shape+2]);
                window.draw(rect);
            }
        }
    }
}

void GameoverCheck(){
    if(matrix[1][5].mark == 1){
        gameplay = false;
    }

}

void GameOverRender(sf::RenderWindow& window){
    for(int i=0; i<ROWS;i++){
        for(int j=0; j<COLUMNS;j++){
            if(matrix[i][j].mark == 1){
                sf::RectangleShape rect;
                rect.setPosition(sf::Vector2f(j*CELL_SIZE,i*CELL_SIZE));
                rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
                rect.setOutlineColor(shape_color[1]);
                rect.setOutlineThickness(-1);
                rect.setFillColor(shape_color[9]);
                window.draw(rect);
            }
        }
    }
}
// Function for Line clearing Duh!!!
// I'm not explaining whats inside :)
// Apparently there is a dragon in there
void Line_Clearing(sf::Sound& clearlinessound){
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLUMNS; j++){
            if(matrix[i][j].mark != 1){
                break;
            }
            if(j == COLUMNS-1){
                for(int k=0; k<COLUMNS; k++){
                    matrix[i][k].mark = 0;
                }
                // I don't know how this works anymore
                for(int i2=i-1; i2>=0;i2--){
                    for(int j2=0; j2<COLUMNS;j2++){
                        if(matrix[i2][j2].mark==1){
                            matrix[i2][j2].mark=0;
                            matrix[i2+1][j2].mark=1;
                            matrix[i2+1][j2].shape = matrix[i2][j2].shape;
                        }
                    }
                }
                line += 1;
                clearlinessound.play();

                // End up explaining this one smh
                // Increase the speed of the game every 10 lines 
                if(line > level_cap){ 
                    level_cap+=10;  // Increase the level_cap by 10
                    level += 1;
                    if(speed != 0.1 ){  // decrease the speed by 0.1 but stop when already hit 0.1 or the speed will go super sonic
                        speed -= 0.1;   // hehehehe
                    }
                }
            }
        }
    }
}

// Display the Info section
void show_Info(sf::RenderWindow& window, int next_shape, sf::Font font){
    std::vector<Position> next_tetromino(4);
    next_tetromino = get_tetromino(next_shape, 15, 3);

    // render the Text "Next"
    sf::Text next;
    next.setFont(font);
    next.setCharacterSize(20);
    next.setStyle(sf::Text::Bold);
    next.setFillColor(sf::Color(174,205,236));
    next.setPosition(425, 15);
    next.setString("Next");
    window.draw(next);

    sf::Text levels;
    levels.setFont(font);
    levels.setCharacterSize(20);
    levels.setStyle(sf::Text::Bold);
    levels.setFillColor(sf::Color(174,205,236));
    levels.setPosition(425, 150);
    levels.setString("Level\n"+std::to_string(level));
    window.draw(levels);

    sf::Text scores;
    scores.setFont(font);
    scores.setCharacterSize(20);
    scores.setStyle(sf::Text::Bold);
    scores.setFillColor(sf::Color(174,205,236));
    scores.setPosition(425, 265);
    scores.setString("Lines\n"+std::to_string(line));
    window.draw(scores);

    // Render the next Shape
    for(Position& mino: next_tetromino){
        sf::RectangleShape rect;
        rect.setPosition(sf::Vector2f(mino.x*CELL_SIZE,mino.y*CELL_SIZE-5));
        rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
        rect.setOutlineColor(shape_color[1]);
        rect.setOutlineThickness(-1);
        rect.setFillColor(shape_color[next_shape+2]);
        window.draw(rect);
    }
}

int main()
{   
    srand(time(0));
    std::vector<Position> tetromino(4);
    std::vector<Position> ghost_tetromino(4);


    sf::RenderWindow window(sf::VideoMode((COLUMNS*CELL_SIZE)*2, ROWS*CELL_SIZE), "Tetris",sf::Style::Titlebar | sf::Style::Close);
    
    sf::Image icon;
    icon.loadFromFile("image/Tetris-icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    // Hard drop sound
    sf::SoundBuffer harddropsfx;
    harddropsfx.loadFromFile("sound/harddrop.wav");
    sf::Sound harddropsound;
    harddropsound.setBuffer(harddropsfx);
    
    // clear lines sound
    sf::SoundBuffer clearlinessfx;
    clearlinessfx.loadFromFile("sound/clearlines.wav");
    sf::Sound clearlinessound;
    clearlinessound.setBuffer(clearlinessfx);

    sf::RectangleShape Info;
    Info.setFillColor(sf::Color(21, 21, 68));
    Info.setSize(sf::Vector2f(COLUMNS*CELL_SIZE, ROWS*CELL_SIZE));
    Info.setPosition(sf::Vector2f(COLUMNS*CELL_SIZE,0));
    

    sf::Clock render_clock;
    sf::Clock key_clock;

    r = rand() % 7;
    while (window.isOpen())
    {
        // timer for the Fall
        movedown_delay = speed;     
        float time = render_clock.getElapsedTime().asSeconds();
        render_clock.restart();
        movedown_timer+=time;

        ghost_tetromino = tetromino;

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){

                case sf::Event::Closed:     // Closed the game
                    window.close();
                    break;
                
                case sf::Event::KeyReleased:    // Key Released
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:      // Rotate
                        if(r == 3){break;}
                        if(orientation == 3){
                            orientation = 0;
                        }
                        else{orientation += 1;}
                        tetromino = rotate(r,tetromino[0].x, tetromino[0].y);
                        break;

                    case sf::Keyboard::Space:   // Hard Drop
                        tetromino = temp_tetromino;
                        harddropsound.play();
                        break;

                    default:
                        break;
                    }
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Left:    // Move Left
                        move_side = -1;
                        break;

                    case sf::Keyboard::Right:   // Move Right
                        move_side = 1;
                        break;
                    
                    case sf::Keyboard::Down:   // Soft Drop
                        movedown_delay = soft_drop_speed;
                        break;
                    }
                    break;
            }
        }
        

        Line_Clearing(clearlinessound);    // python sucks!!!

        //get another shape
        if(trigger_next_tetromino){
            GameoverCheck();
            r = next_shape;
            next_shape = rand() % 7;
            tetromino = get_tetromino(r, 5, 1);
            ghost_tetromino = tetromino;
        }

        // move down depend to the curretn speed
        if(movedown_timer>movedown_delay){
            movedown_timer=0;   // reset the timer for the downward movement
            move_down++;    // increment the y coordinates of the minos by 1
        }

        // render the entire game
        window.clear(sf::Color(12, 12, 39));
        window.draw(Info);
        RenderMatrix(window);   // render the matrix
        RenderDisplay(window, r, tetromino, ghost_tetromino);
        Check_Collision(tetromino);
        show_Info(window, next_shape, font);
        window.display();   // display it
    }
    

    return 0;
}