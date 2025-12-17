#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void clear_screen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear"); // Linux/macOS
#endif
}

void stats(int player1, int player2, int draw)
{
    printf("------------------------\n");
    printf("    Player 1 Stats:     \n");
    printf("------------------------\n");
    printf("Wins: %d\nLoss: %d\n", player1, player2);
    printf("------------------------\n");
    printf("    Player 2 Stats:     \n");
    printf("------------------------\n");
    printf("Wins: %d\nLoss: %d\n", player2, player1);
    printf("------------------------\n");
    printf("Total Draws: %d\n", draw);
    printf("Total Games played: %d\n",player1 + player2+ draw);
}

void display_board(char board[3][3])
{
    // Display baord
    printf("\n");
    printf("        |       |       \n");
    printf("    %c   |   %c   |   %c  \n", board[0][0],board[0][1], board[0][2]);
    printf("--------|-------|-------\n");
    printf("        |       |       \n");
    printf("    %c   |   %c   |   %c  \n", board[1][0],board[1][1], board[1][2]);
    printf("--------|-------|-------\n");
    printf("    %c   |   %c   |   %c  \n", board[2][0],board[2][1], board[2][2]);
    printf("        |       |       \n");
}


int condition(char board[3][3], int move_counter)
{
    int state = 0; // 0 is undefined, 1 is player 1 win, 2 is player 2 win and 3 is draw
    // row check
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == 'X' || board[i][0] == 'O') &&
            board[i][0] == board[i][1] && board[i][1] == board[i][2]) // Checks the element 0,0 is X or Y and then next elements are X/Y or other words equal to first element
        {
            state = board[i][0] == 'X' ? 1 : 2;
            return state;
        }
    }

    // Column Check
    for (int j = 0; j < 3; j++)
    {
        if ((board[0][j] == 'X' || board[0][j] == 'O') &&
            board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            state = board[0][j] == 'X' ? 1 : 2;
            return state;
        }
    }

    // diagonal check
    if ((board[0][0] == 'X' || board[0][0] == 'O') &&
        board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            state = board[0][0] == 'X' ? 1 : 2;
            return state;
        }
        

    if ((board[0][2] == 'X' || board[0][2] == 'O') &&
        board[0][2] == board[1][1] && board[1][1] == board[2][0])
        {
            state = board[0][2] == 'X' ? 1 : 2;
            return state;
        }
        

    if (move_counter == 9)
    {
        state = 3;
        return state;
    }

    return state; // undetermined
}




int game()
{
    // Initialize board
    char board[3][3] = {
        {'1', '2' ,'3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
    };
    int move_counter = 0;
    int state = 0;

    display_board(board);

    // Input From user

    int move;
    while (state == 0)
    {
        int player = move_counter % 2 == 0 ? 1 : 2; // tenary operation to determine player
        printf("Player %d enter move: ", player);
        scanf("%d", &move);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // flush buffer

        if(move > 0 && move < 10) // checks if move is valid
        {
            // Row and column conversion
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;
            if (board[row][col] != 'X' && board[row][col] != 'O')
            {
                board[row][col] = (player == 1) ? 'X' : 'O';
                move_counter++;
                clear_screen();
                display_board(board);
                state = condition(board, move_counter);

                switch (state)
                {
                case 1:
                    printf("Player 1 Wins!!\n");
                    printf("\n");
                    break;

                case 2:
                    printf("Player 2 Wins!!\n");
                    printf("\n");
                    break;
                
                case 3:
                    printf("Draw ;(\n");
                    printf("\n");
                    break;
                }

                if (state == 1 || state == 2 || state == 3)
                {
                    break;
                }
            }
            else
            {
                printf("Cell Already Taken\n");
            }
        }
        else
        {
            printf("Invalid Input\n");
            continue;
        }

    }
    return state;
}


int main()
{
    int win_1 = 0, win_2 = 0, draw = 0;
    char input[10];
    int state = 0;
    int stop = 0;
    while (!stop)
    {
        printf("Type \"quit\" to exit, \"stats\" to view stats, or press Enter to play again.\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0)
        {
            printf("Exiting Game\n");
            stop = 1;
        }
        else if (strcmp(input, "stats") == 0)
        {
            stats(win_1, win_2, draw);
        }

        else if (strlen(input) == 0)
        {
            clear_screen();
            printf("Tic Tac Toe\n");
            state = game();

        // Update stats
        if (state == 1) win_1++;
        else if (state == 2) win_2++;
        else if (state == 3) draw++;
        }
    }

    return 0;
}
