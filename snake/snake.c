#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>
#include <ctype.h>
#include <unistd.h>

typedef struct  snake_info
{
    int width;
    int height;
    int snake_x;
    int snake_y;
    int food_x;
    int food_y;
    int score;
} info;

// Function prototype


void clear_screen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear"); // Linux/macOS
#endif
}
void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void canvas(int height, int width, int snake_x, int snake_y, int food_x, int food_y)
{
    for (int y = 0; y <= height; y++)
    {
        for(int x = 0; x <= width; x++)
        {
            if(y == 0 || x == 0 || y == height || x == width)
            {
                printf("#");
                continue;
            }
            else if (y == snake_y && x == snake_x)
            {
                printf("@");
            }
            else if (y == food_y && x == food_x)
            {
                printf("+");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void food_position(int width, int height, int *x, int *y)
{
    *x = (rand() % (width - 2)) + 1;
    *y = (rand() % (height - 2)) + 1;
}

void game(int height, int width)
{
    info snake;
    clear_screen();
    printf("        ================================\n");
    printf("        ||                              ||\n");
    printf("        ||          S N A K E           ||\n");
    printf("        ||                              ||\n");
    printf("        ================================\n");

    // randomly Spawn the snake in the box
    snake.snake_x = (rand() % (width - 2)) + 1;
    snake.snake_y = (rand() % (height - 2)) + 1;

    // food position
    food_position(width, height, &snake.food_x, &snake.food_y);
    

    // snakeey eats the food
    snake.score = 0;
    
    // draw the canvas
    int collision = 0;
    char movement;
    while (!collision)
    {
        clear_screen();
        canvas(height, width, snake.snake_x, snake.snake_y, snake.food_x, snake.food_y);
        
        printf("Score: %d\n", snake.score);
        printf("Movement: ");
        scanf("%c", &movement);
        clear_buffer();
        movement = tolower(movement);

        switch (movement)
        {
        case 'a':
            snake.snake_x--;
            break;
        case 'd':
            snake.snake_x++;
            break;
        case 'w':
            snake.snake_y--;
            break;
        case 's':
            snake.snake_y++;
            break;
        
        default:
            printf("Invalid Movement\n");
            sleep(1);
            break;
        }

        if (snake.food_x == snake.snake_x && snake.food_y == snake.snake_y)
        {
            snake.score += 100;
            while (snake.food_x == snake.snake_x && snake.food_y == snake.snake_y) 
            {
                food_position(width, height, &snake.food_x, &snake.food_y);
            }
        }

        if (snake.snake_x == 0 || snake.snake_x == width ||
        snake.snake_y == 0 || snake.snake_y == height)
        {
            clear_screen();
            printf("Game Over!\n");
            printf("Score: %d\n", snake.score);
            collision = 1;
        }
        usleep(100000);
    }    
}

void stats()
{
    printf("stats\n");
}

int main()
{
    info snake;
    char ini_choice[10];
    int stop = 0;
    srand(time(NULL));
    while(!stop)
    {
        printf("Enter \"quit\" to exit, \"stats\" to view stats, or press Enter to play\n");
        fgets(ini_choice, sizeof(ini_choice), stdin);
        ini_choice[strcspn(ini_choice, "\n")] = 0;

        if (strcmp(ini_choice, "quit") == 0)
        {
            printf("Exiting ;( \n");
            stop = 1;
        }
        else if (strcmp(ini_choice, "stats") == 0)
        {
            stats();
        }
        else if ( strlen(ini_choice) == 0 )
        {
            while (1)
            {
                printf("Enter Canvas Height: ");
                if (scanf("%d", &snake.height) == 1)
                {
                    printf("Enter Canvas Width: ");
                    if(scanf("%d", &snake.width) == 1)
                        {
                            if (snake.width < 5 || snake.height < 5)
                            {
                                printf("Canvas too small. Minimum is 5x5.\n");
                                clear_buffer();
                                continue;
                            }
                            game(snake.height, snake.width);
                            break;
                        }
                    else
                    {
                        printf("Invalid Input\n");
                    }
                }
                else
                {
                    printf("Invalid Input\n");
                }
                clear_buffer();
            }
        }
        else
        {
            printf("Invalid Input \n");
            clear_buffer();
        }
    }

    return 0;
}
