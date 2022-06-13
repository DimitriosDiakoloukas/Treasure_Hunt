//////////////////////////////////////////////////////
//  Project: Treasure Hunt                          //
//  Aristotle University,Thessaloniki               //
//  Electrical and Computer Engineering             //
//  Team: Diakoloukas Dimitris - Antakis Marios     //
//  First Semester - 2021-2022                      //
//////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <MMsystem.h>

#define WHITE 15
#define BLUE 9
#define GREEN 10
#define RED 12
#define YELLOW 14
#define GRAY 8
#define PURPLE 13
#define DARKGREEN 2
#define DARKYELLOW 6
#define CYAN 11
#define DARKPURPLE 5

/*
Color Codes for Text Printing
        black=0,
		dark_blue=1,
		dark_green=2,
		dark_aqua,dark_cyan=3,
		dark_red=4,
		dark_purple=5,dark_pink=5,dark_magenta=5,
		dark_yellow=6,
		dark_white=7,
		gray=8,
		blue=9,
		green=10,
		aqua=11,cyan=11,
		red=12,
		purple=13,pink=13,magenta=13,
		yellow=14,
		white=15
*/

struct Player
{
    int cur_i;  // position on x axis on map
    int pre_i;  // previous position on x axis on map
    int cur_j;  // position on y axis on map
    int pre_j;  // previous position on x axis on map
    int SeaCount;  // Times of falling in the sea
    int cnt; // Loss of energy
};

struct Island
{
    int iHeight; // Height of first(1) Island
    int iWidth; // Width of first(1) Island
    int i_2Height; // Height of second(2) Island
    int i_2Width; // Width of second(2) Island
    int nMount; // Number of Mountains on map
    int nTree;  // Number of Trees on map
    int nGremos; // Number of Cliffs on map
    int nOksia; // Number of Beech Trees on map
    char map[8][10]; // Map of first(1) Island
    char map2[14][14]; // Map of second(2) Island
};


// Game Instructions
void instructions_pliroforiki(void)
{
    printf("You find yourself somewhere in an island with treasures, forests, mountains,\n");
    printf("caves, cliffs, a beech tree and of course sea all around.\n");
    printf("Your goal is to find the treasure as fast as possible\n");
    printf("without falling in the sea with the sharks.\n");
    printf("You have a map which you can see (X), or move north (B),\n");
    printf("east (A), south (N), west (D), doing one move at a time.\n");
    printf("However your compass  isn't too accurate. There is only\n");
    printf("80%% chance to move towards the desired direction, while\n");
    printf("there is 20%% chance to move diagonally right or left towards\n");
    printf("the desired direction. Every time you make a move you will\n");
    printf("get information about the place you are on the map.\n");
    printf("If you fall in the sea , you will come back at the place you\n");
    printf("were before your unlucky move, except if you disturb the sharks.\n");
    printf("The possibility of being eaten by the sharks the first time \n");
    printf("you fall in the sea is 20%%. The second time you fall\n");
    printf("the possibility of being eaten is 70%%. The third time\n");
    printf("you fall in the sea will be your last!\n");
    printf("Since you have the map of the island, you will be able to\n");
    printf("specify your position approximately.The reason you can't \n");
    printf("be sure about your exact position is that you might have\n");
    printf("moved diagonally right or left in a move. With some practise,\n");
    printf("you will be able to find the treasure in less than 15 moves.\n");
    printf("The game becomes even more interesting at the second level in which \n");
    printf("you have to find the treasure with a limited amount of energy.\n");
    printf("Each move reduces your energy by one.\n");
    printf("You can increase your energy by one if you find food or water.\n");
    printf("Lastly there is a possibility of falling in quicksand from which\n");
    printf("you won't be able to come out alive.\n\n\n");
}

// Information about the making of the game
void plirofories_pliroforiki(void)
{
    printf("Code in ISO C17\nCompilation in a GNU GCC Compiler\nTeam Members: Antakis Marios - Diakoloukas Dimitris\n\n\n");
}

// Returning at the previous position after falling in the sea
void sea_return(struct Player *to)
{
    //printf("1.Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d)\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j); //For debugging
    to->cur_i = to->pre_i;
    to->cur_j = to->pre_j;
    //printf("2.Cur(i,j)=(%d,%d)  Prev(i,j)=(%d,%d)\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j); //For debugging
}

// Moving West
void move_west(struct Player *to)
{
    int rnd;
    srand(time(NULL));
    rnd = rand() % 10;
    if(rnd<8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_j--;
        //printf("WEST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else if(rnd == 8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_j--;
        to->cur_i--;
        //printf("NORTHWEST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_j--;
        to->cur_i++;
        //printf("SOUTHWEST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
}

// Moving east 
void move_east(struct Player *to)
{
    int rnd;
    srand(time(NULL));
    rnd = rand() % 10;
    if(rnd<8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_j++;
        //printf("EAST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else if(rnd == 8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_j++;
        to->cur_i--;
        //printf("NORTHEAST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_j++;
        to->cur_i++;
        //printf("SOUTHEAST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
}

// Moving south
void move_south(struct Player *to)
{
    int rnd;
    srand(time(NULL));
    rnd = rand() % 10;
    if(rnd<8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_i++;
        //printf("SOUTH: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else if(rnd == 8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_i++;
        to->cur_j--;
        //printf("SOUTHWEST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d) --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_i++;
        to->cur_j++;
        //printf("SOUTHEAST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d)  --RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
}

// Moving north
void move_north(struct Player *to)
{
    int rnd;
    srand(time(NULL));
    rnd = rand() % 10;
    if(rnd<8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_i--;
        //printf("NORTH: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d)  -- RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else if(rnd == 8)
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_i--;
        to->cur_j--;
        //printf("NORTHWEST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d)  -- RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
    else
    {
        to->pre_i = to->cur_i;
        to->pre_j = to->cur_j;
        to->cur_i--;
        to->cur_j++;
        //printf("NORTHEAST: Cur(i,j)=(%d,%d)   Prev(i,j)=(%d,%d)  -- RND=%d\n",to->cur_i,to->cur_j,to->pre_i,to->pre_j,rnd); //For debugging
    }
}

// First time  in the sea
void player_in_sea_onetime(struct Player *to)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int rnd;
    srand(time(NULL));
    rnd = rand() % 10;
    if(rnd>1)
    {
        //printf("RND=%d\n",rnd); //For debugging
        sea_return(to);
        PlaySound(TEXT(".\\audio\\Water-splash-1311.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, BLUE);
        printf("You are in the sea! \n");
        SetConsoleTextAttribute(hConsole, WHITE);
        printf("The next time you fall there is 70%% possibility of being eaten by the sharks\n");
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else
    {
        //printf("RND=%d\n",rnd); //For debugging
        //printf("1st Time @Sea:  RND=%d\n",rnd); //For debugging
        PlaySound(TEXT(".\\audio\\Water-splash-1311.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, BLUE);
        printf("You are in the sea! \n");
        SetConsoleTextAttribute(hConsole, WHITE);
        Sleep(2000);
        printf("You are the delightful meal of the sharks! \n");
        PlaySound(TEXT(".\\audio\\sadGameOver.wav"),NULL,SND_ASYNC);
        system("pause");
        exit(0);
    }
}


// Second time in the sea
void player_in_sea_twotimes(struct Player *to)
{
    int rnd;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    srand(time(NULL));
    rnd = rand() % 10;
    if(rnd>6)
    {
        //printf("2nd Time @Sea:  RND=%d\n",rnd); //For debugging
        sea_return(to);
        PlaySound(TEXT(".\\audio\\Sea-water-splash-1198.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, BLUE);
        printf("You are in the sea !\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        printf("The next time you fall there is 100%% possibility of being eaten by the sharks\n");
        //system("pause");
        Sleep(2000);
    }
    else
    {
        //printf("2nd Time @Sea:  RND=%d\n",rnd); //For debugging
        PlaySound(TEXT(".\\audio\\Sea-water-splash-1198.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, BLUE);
        printf("You are in the sea !\n\n");
        SetConsoleTextAttribute(hConsole, RED);
        printf("You are the delightful meal of the sharks! \n");
        Sleep(2000);
        PlaySound(TEXT(".\\audio\\sadGameOver.wav"),NULL,SND_ASYNC);
        system("pause");
        exit(0);
    }
}


// Player's movement at level 1
void player_tracking(struct Island *isl, struct Player *to)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j;
    i = to->cur_i;
    j = to->cur_j;

    if((isl->map[i][j]) == 'M')
    {
        PlaySound(TEXT(".\\audio\\mountain.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, PURPLE);
        printf("You are on a mountain [M]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map[i][j]) == 'F')
    {
        PlaySound(TEXT(".\\audio\\forest.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, DARKGREEN);
        printf("You are in a forest [F]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map[i][j]) == 'C')
    {
        PlaySound(TEXT(".\\audio\\fallingScream.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, RED);
        printf("You are on a cliff [C]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map[i][j]) == 'B')
    {
        PlaySound(TEXT(".\\audio\\oakTree.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, GREEN);
        printf("You are at a beech tree [B]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map[i][j]) == 'T')
    {
        SetConsoleTextAttribute(hConsole, YELLOW);
        printf("Fantastic!!! You found the treasure [T]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        PlaySound(TEXT(".\\audio\\TreasureFound.wav"),NULL,SND_ASYNC);
        system("pause");
        exit(0);
    }
    else if((isl->map[i][j]) == '~')
    {
        to->SeaCount++;
        //printf("AT_SEA:%d times - Cur(%d,%d) - Pre(%d,%d)\n",to->SeaCount,i,j,to->pre_i,to->pre_j); //For debugging

        if (to->SeaCount == 1)
        {
            player_in_sea_onetime(to);
        }
        else if(to->SeaCount == 2)
        {
            player_in_sea_twotimes(to);

        }
        else if(to->SeaCount == 3)
        {
            PlaySound(TEXT(".\\audio\\JumpIntoWater1.wav"),NULL,SND_ASYNC);
            SetConsoleTextAttribute(hConsole, BLUE);
            printf("You are in the sea!\n");
            SetConsoleTextAttribute(hConsole, WHITE);
            Sleep(2000);
            printf("You are the delightful meal of the sharks! \n");
            PlaySound(TEXT(".\\audio\\sadGameOver.wav"),NULL,SND_ASYNC);
            system("pause");
            exit(0);
        }
        else
        {
            //printf("SeaCount:%d was not expected\n", to->SeaCount); //For debugging
            exit(-1);
        }
    }
    else
        printf("You are in open space [#]\n\n");

}

// Player's movement at level 2
void player_tracking_two(struct Island *isl, struct Player *to)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j;
    i = to->cur_i;
    j = to->cur_j;

    if((isl->map2[i][j]) == 'M')
    {
        PlaySound(TEXT(".\\audio\\mountain.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, PURPLE);
        printf("You are on a mountain [M]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map2[i][j]) == 'F')
    {
        PlaySound(TEXT(".\\audio\\forest.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, DARKGREEN);
        printf("You are in a forest [F]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map2[i][j]) == 'R')
    {
        PlaySound(TEXT("human-male.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, DARKPURPLE);
        printf("You are in a restaurant. Bon appetit[R]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map2[i][j]) == 'Q')
    {
        PlaySound(TEXT("battlemanscream.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, DARKYELLOW);
        printf("You are in quicksand [Q]. You will eventually die!!\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map2[i][j]) == 'W')
    {
        PlaySound(TEXT("drink water.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, CYAN);
        printf("You found a refreshing bottle of water [W]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map2[i][j]) == 'C')
    {
        PlaySound(TEXT(".\\audio\\fallingScream.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, RED);
        printf("You are on a cliff [C]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map2[i][j]) == 'B')
    {
        PlaySound(TEXT(".\\audio\\oakTree.wav"),NULL,SND_ASYNC);
        SetConsoleTextAttribute(hConsole, GREEN);
        printf("You are at a beech tree [B]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        //system("pause"); // It can be used instead of sleep();
        Sleep(2000);
    }
    else if((isl->map2[i][j]) == 'T')
    {
        SetConsoleTextAttribute(hConsole, YELLOW);
        printf("Fantastic!!! You found the treasure[T]\n\n");
        SetConsoleTextAttribute(hConsole, WHITE);
        PlaySound(TEXT(".\\audio\\TreasureFound.wav"),NULL,SND_ASYNC);
        system("pause");
        exit(0);
    }
    else if((isl->map2[i][j]) == '~')
    {
        to->SeaCount++;
        //printf("AT_SEA:%d times - Cur(%d,%d) - Pre(%d,%d)\n",to->SeaCount,i,j,to->pre_i,to->pre_j); //For debugging

        if (to->SeaCount == 1)
        {
            player_in_sea_onetime(to);
        }
        else if(to->SeaCount == 2)
        {
            player_in_sea_twotimes(to);
        }
        else if(to->SeaCount == 3)
        {
            PlaySound(TEXT(".\\audio\\JumpIntoWater1.wav"),NULL,SND_ASYNC);
            SetConsoleTextAttribute(hConsole, BLUE);
            printf("You are in the sea!\n\n");
            SetConsoleTextAttribute(hConsole, WHITE);
            Sleep(2000);
            printf("You are the delightful meal of the sharks! \n");
            PlaySound(TEXT(".\\audio\\sadGameOver.wav"),NULL,SND_ASYNC);
            system("pause");
            exit(0);
        }
        else
        {
            //printf("SeaCount:%d was not expected\n", to->SeaCount); //For debugging
            exit(-1);
        }
    }
    else
        printf("You are in open space [#]\n\n");

}


// Printing map 1 (Colored map)
void map_printer(struct Island *isl)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    int i, j;

    printf("Lets see map 1\n");

    for(i=0; i<isl->iHeight; i++)
    {
        putchar('\n');
        for(j=0; j<isl->iWidth; j++)
        {

            if((isl->map[i][j])== '#')
            {
                SetConsoleTextAttribute(hConsole, GRAY);
                printf("%c ", isl->map[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map[i][j])== 'T')
            {
                SetConsoleTextAttribute(hConsole, YELLOW);
                printf("%c ", isl->map[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map[i][j])== '~')
            {
                SetConsoleTextAttribute(hConsole, BLUE);
                printf("%c ", isl->map[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map[i][j])== 'B')
            {
                SetConsoleTextAttribute(hConsole, GREEN);
                printf("%c ", isl->map[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map[i][j])== 'F')
            {
                SetConsoleTextAttribute(hConsole, DARKGREEN);
                printf("%c ", isl->map[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map[i][j])== 'M')
            {
                SetConsoleTextAttribute(hConsole, PURPLE);
                printf("%c ", isl->map[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map[i][j])== 'C')
            {
                SetConsoleTextAttribute(hConsole, RED);
                printf("%c ", isl->map[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
        }
    }
    putchar('\n\n');
}

// Printing map 2 (Colored map)
void map_printer_two(struct Island *isl)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    int i, j;

    printf("Lets see map 2\n");

    for(i=0; i<isl->i_2Height; i++)
    {
        putchar('\n');
        for(j=0; j<isl->i_2Width; j++)
        {

            if((isl->map2[i][j])== '#')
            {
                SetConsoleTextAttribute(hConsole, GRAY);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'R')
            {
                SetConsoleTextAttribute(hConsole, DARKPURPLE);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'Q')
            {
                SetConsoleTextAttribute(hConsole, DARKYELLOW);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'W')
            {
                SetConsoleTextAttribute(hConsole, CYAN);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'T')
            {
                SetConsoleTextAttribute(hConsole, YELLOW);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== '~')
            {
                SetConsoleTextAttribute(hConsole, BLUE);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'B')
            {
                SetConsoleTextAttribute(hConsole, GREEN);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'F')
            {
                SetConsoleTextAttribute(hConsole, DARKGREEN);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'M')
            {
                SetConsoleTextAttribute(hConsole, PURPLE);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            if((isl->map2[i][j])== 'C')
            {
                SetConsoleTextAttribute(hConsole, RED);
                printf("%c ", isl->map2[i][j]);
                SetConsoleTextAttribute(hConsole, WHITE);
            }
        }
    }
    putchar('\n\n');
}


// Printing map 1(Black and white)    
/*void map_printer(struct Island *isl)
{
    int i, j;

    printf("Lets see the map\n");

    for(i=0; i<isl->iHeight; i++)
    {
        putchar('\n');
        for(j=0; j<isl->iWidth; j++)
        {
            printf("%c ",isl->map[i][j]);
        }
    }
    putchar('\n\n');
} */



// Initializing player's position at level 1
void initialize_player(struct Player *to, struct Island *isl)
{
    int rx, ry;

    srand(time(NULL));
    do
    {
        rx = rand()%(isl->iHeight-2)+1;
        ry = rand()%(isl->iWidth-2)+1;
    }
    while(isl->map[rx][ry] == 'T');

    //printf("RANDOMLY PLACED in %d %d\n", rx,ry); //For debugging
    to->cur_i = rx;
    to->cur_j = ry;
    to->pre_i = rx;
    to->pre_j = ry;
    to->SeaCount = 0;
    //printf("Current Random Position: %c \n",isl->map[rx][ry]); //For debugging
    //printf("Treasure is placed on map[3][4]: %c\n",isl->map[3][4]); //For debugging

}

// Initializing player's position at level 2
void initialize_player_two(struct Player *to, struct Island *isl)
{
    int rx, ry;

    srand(time(NULL));
    do
    {
        rx = rand()%(isl->i_2Height-2)+1;
        ry = rand()%(isl->i_2Width-2)+1;
    }
    while(isl->map[rx][ry] == 'T');

    //printf("RANDOMLY PLACED in %d %d\n", rx,ry); //For debugging
    to->cur_i = rx;
    to->cur_j = ry;
    to->pre_i = rx;
    to->pre_j = ry;
    to->SeaCount = 0;
    to->cnt = 10;
    //printf("Current Random Position: %c \n",isl->map[rx][ry]); //For debugging
    //printf("Treasure is placed on map[3][4]: %c\n",isl->map[3][4]); //For debugging
}

// Makingof the map randomly
// Has not been completed :(
/*void initialize_island(struct Island *isl)
{
    int i,j;
    int xtreasure, ytreasure;
    int iX=isl->iHeight;
    int iY=isl->iWidth;

    for(i=1;i<iX-1;i++){
        isl->map[i][0]='~';
        isl->map[i][iY-1]='~';
        for(j=1; j<iY-1;j++){
            isl->map[i][j]='#';
        }
    }

    for(j=0; j<iY;j++){
            isl->map[0][j]='~';
            isl->map[iX-1][j]='~';
    }

    // Put the treasure in the middle of the island
    xtreasure = (int) (iX-1)/2;
    ytreasure = (int) (iY-1)/2;
    isl->map[xtreasure][ytreasure]='Θ';
}
*/




// Basic game's menu for level 1
void gameplay(struct Player *to, struct Island *isl)
{
    char move;

    //printf("MAIN Player Starting point at %d - %d\n", to->cur_i, to->cur_j); //For debugging
    //printf("MAIN Player is place on %c\n", isl->map[to->cur_i][to->cur_j]); //For debugging


    printf("Choose one of the following:\n");
    printf("\t X or x: For map 1\n");
    printf("\t B or b: To move north\n");
    printf("\t A or a: To move east\n");
    printf("\t N or n: To move south\n");
    printf("\t D or d: To move west\n");
    printf("\t E: To exit\n\n");

    do
    {
        printf("Movement or action [X B A N D]\n");
        scanf("%c",&move);
        fflush(stdin);
        putchar('\n');
        switch(move)
        {
        case 'X':
        case 'x':
            map_printer(isl);
            printf("\n");
            break;
        case 'B':
        case 'b':
            move_north(to);
            player_tracking(isl, to);
            break;
        case 'A':
        case 'a':
            move_east(to);
            player_tracking(isl, to);
            break;
        case 'N':
        case 'n':
            move_south(to);
            player_tracking(isl, to);
            break;
        case 'D':
        case 'd':
            move_west(to);
            player_tracking(isl, to);
            break;
        case 'E':
            PlaySound(TEXT("buzzer (1).wav"),NULL,SND_ASYNC);
            printf("Have a nice day!\n");
            Sleep(1000);
            exit(0);
        default:
            puts("Wrong choice!\n");
            break;
        }
    }
    while(move!='E');
}

// Basic game's menu for level 2
void gameplay_two(struct Player *to, struct Island *isl)
{
    char move;

    //printf("MAIN Player Starting point at %d - %d\n", to->cur_i, to->cur_j); //For debugging
    //printf("MAIN Player is place on %c\n", isl->map[to->cur_i][to->cur_j]); //For debugging


    printf("Choose one of the following:\n");
    printf("\t X or x: For map 2\n");
    printf("\t B or b: To move north\n");
    printf("\t A or a: To move east\n");
    printf("\t N or n: To move south\n");
    printf("\t D or d: To move west\n");
    printf("\t E: To exit\n\n");

    do
    {
        printf("Movement or action [X B A N D]\n");
        scanf("%c",&move);
        fflush(stdin);
        putchar('\n');
        switch(move)
        {
        case 'X':
        case 'x':
            map_printer_two(isl);
            printf("\n");
            break;
        case 'B':
        case 'b':
            move_north(to);
            player_tracking_two(isl, to);
            energy(isl, to);
            kinoumeni(isl, to);
            break;
        case 'A':
        case 'a':
            move_east(to);
            player_tracking_two(isl, to);
            energy(isl, to);
            kinoumeni(isl, to);
            break;
        case 'N':
        case 'n':
            move_south(to);
            player_tracking_two(isl, to);
            energy(isl, to);
            kinoumeni(isl, to);
            break;
        case 'D':
        case 'd':
            move_west(to);
            player_tracking_two(isl, to);
            energy(isl, to);
            kinoumeni(isl, to);
            break;
        case 'E':
            PlaySound(TEXT("buzzer (1).wav"),NULL,SND_ASYNC);
            printf("Have a nice day!\n");
            Sleep(1000);
            exit(0);
        default:
            puts("Wrong choice!\n");
            break;
        }
    }
    while(move!='E');
}

//Energy
void energy(struct Island *isl, struct Player *to)
{
    int i, j;
    i = to->cur_i;
    j = to->cur_j;

    if(((isl->map2[i][j]) == 'R') || ((isl->map2[i][j]) == 'W'))
    {
        if(to->cnt<10)
        {
            to->cnt++;
            printf("Your energy is %d%%\n\n",10*(to->cnt));
        }
    }
    else if(((isl->map2[i][j]) == '#') || ((isl->map2[i][j]) == 'M') || ((isl->map2[i][j])== 'B') || ((isl->map2[i][j])== 'F') || ((isl->map2[i][j])== 'C') || ((isl->map2[i][j])== '~'))
    {
        to->cnt--;
        printf("Your energy is %d%%\n\n",10*(to->cnt));
        if(to->cnt == 0)
        {
            printf("You are out of energy\n\n");
            exit(0);
        }
    }
}
//Quicksand
void kinoumeni(struct Island *isl, struct Player *to)
{
  int i, j;
   i = to->cur_i;
   j = to->cur_j;
   int k;

  if((isl->map2[i][j]) == 'Q')
   for(k=to->cnt - 1; k>=0; k--){
    printf("Your energy is %d%%\n",10*k);
    PlaySound(TEXT("battlemanscream.wav"),NULL,SND_ASYNC);
    Sleep(1500);
     if(k == 0)
        {
            putchar('\n');
            printf("You are out of energy\n\n");
            exit(0);
        }
    }
}

// Main function
int main(void)
{
    SetConsoleOutputCP(1253);
    int num;
    int move;
    struct Player to;
    struct Island isl;
    isl.iHeight = 8;
    isl.iWidth = 10;
    isl.i_2Height = 14;
    isl.i_2Width = 14;
    isl.nGremos = 2;
    isl.nTree = 4;
    isl.nMount = 5;
    isl.nOksia = 1;

    char M[8][10] = {'~','~','~','~','~','~','~','~','~','~',
                     '~','#','#','#','F','#','#','#','#','~',
                     '~','#','C','F','#','#','M','#','#','~',
                     '~','M','#','#','T','#','#','#','M','~',
                     '~','#','#','#','F','#','#','M','#','~',
                     '~','M','#','#','#','B','#','F','#','~',
                     '~','#','#','#','C','#','#','#','#','~',
                     '~','~','~','~','~','~','~','~','~','~'
                    };

    char N[14][14] = {'~','~','~','~','~','~','~','~','~','~','~','~','~','~',
                      '~','#','W','F','W','Q','R','#','#','R','Q','F','R','~',
                      '~','R','Q','W','#','W','#','B','#','C','#','#','#','~',
                      '~','#','#','C','#','#','#','#','R','#','#','F','W','~',
                      '~','#','F','#','F','W','M','#','#','Q','#','#','#','~',
                      '~','M','#','#','#','#','#','T','#','M','R','#','#','~',
                      '~','#','#','#','M','#','#','#','C','#','#','R','#','~',
                      '~','W','C','#','#','#','C','#','#','W','#','#','W','~',
                      '~','#','Q','#','#','F','#','R','#','Q','R','#','#','~',
                      '~','#','#','R','#','#','#','#','#','#','#','F','#','~',
                      '~','R','#','#','#','#','M','#','W','C','#','#','#','~',
                      '~','#','B','#','#','F','#','#','#','#','F','#','R','~',
                      '~','#','#','#','C','#','#','R','#','W','#','F','#','~',
                      '~','~','~','~','~','~','~','~','~','~','~','~','~','~'
                     };
    printf("Welcome to Mario's and Dimitri's game!!!!!!!\n\n");
    PlaySound(TEXT("woooooo.wav"),NULL,SND_ASYNC);

    while(num != 5)
    {
        printf("Chosse one of the following:\n");
        printf("(1) For instructions\n(2) To play the game at level 1\n(3) To play the game at level 2\n(4) For information\n(5) To quit the game\n\n");
        scanf("%d", &num);
        fflush(stdin);
        switch(num)
        {
        case 1:
            instructions_pliroforiki();
            break;
        case 2:
            strcpy(isl.map, M);
            //initialize_island(&isl);
            initialize_player(&to, &isl);
            gameplay(&to, &isl);
            break;
        case 3:
            strcpy(isl.map2,  N);
            //initialize_island(&isl);
            initialize_player_two(&to, &isl);
            gameplay_two(&to, &isl);
            break;
        case 4:
            plirofories_pliroforiki();
            break;
        case 5:
            PlaySound(TEXT("buzzer (1).wav"),NULL,SND_ASYNC);
            printf("The end!\n");
            Sleep(1000);
            exit(0);
            break;
        default:
            printf("Wrong choice!\n");
            break;
        }
    }
    return 0;
}


