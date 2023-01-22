#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#ifdef LINUX
#include<unistd.h>
#else
#include <windows.h>
#endif

#define HEIGHT 15       //Height of the play area
#define WIDTH 80        //Width of the play area
#define TRUE 1          // TRUE and FALSE defines the game progress either running stopped
#define FALSE 0         

int snake_headX,snake_headY;    // X and Y co-ordinate of SNAKE
int foodX,foodY;                // X and Y co-ordinate of FOOD
int gameover;                   // Game State 
int score;                      // Stores the score
int tailX[10],tailY[10];        // X and Y co-ordinates of the tail        
int tail_piece=0;               // Number of tail pieces
int runIntro=TRUE;              // Tells either to run or not the Intro() function
int runRetry = FALSE;
int openpanel;
int nextlevel;

int keyPressed; /*  KEY    MOVEMENT    ALTERNATE(INT)
                     w       up             1
                     s      down            2
                     a      left            3
                     d      right           4       */

//Just Basic Introduction About The Game and obviously my name :)
void Intro()
{

    int introKeys;
    printf("\n----> WELCOME TO THE <- SNAKE GAME ->\n");
    printf("----> ~by Shivansh Upadhyay\n");
    printf("----> TELL ME IF YOU LIKE THE GAME AND THE CODE EXPLANATION\n");
    printf("----> INSTAGRAM - @codewithshivansh\n----> GOTO https://github.com/goldbrick00 FOR THE SOURCE CODE\n");
    printf("\n----> PRESS 1 TO CONTINUE\n");
    printf("\n----> PRESS 0 TO EXIT");
    printf("\n----> ");-
    scanf("%d",&introKeys);
    switch(introKeys)
    {
        case 1:{
            runIntro = FALSE;
            main();}
        case 0:{
            // printf("\n\nHope You Enjoyed The Game.");
            system("exit");}
    }
}

//  Dispaly is basically the area where we play our game with a specified height and width  //
/* Here We Displayed :
    1. The Border i.e the dead end
    2. The food
    3. the snake
*/ 
void Display()
{
    system("cls");
    // system("clear");
    int i,j,k;
    for(i=0;i<=HEIGHT;i++)  //height is 16 not 15 due to " <= " operator (i.e 0 to 15)
    {
        for(j=0;j<=WIDTH;j++)   //width is 81 not 80 due to " <= " operator (i.e 0 to 90)
        {   
            if(i==HEIGHT||i==0 ||j==0|| j==WIDTH)   //Making exception for 0th row,16th(last) row and 0th column,81st last column
            {
                if(openpanel==TRUE)
                {
                    if(j==WIDTH && i==14)
                        printf("->");
                    else
                        printf("#");
                }
                else
                    printf("#");    //printf "#" for the exception case
            }    
            else
            {
                if(i==snake_headY && j==snake_headX)
                    printf("0");    /* (snakeX,snakeY) are the co-ordinates of snake (initially)
                                      Printf Snake Head "0" where (snakeX,snakeY) matches the co-ordinate (j,i)*/
                else if(i==foodY && j==foodX)
                    printf("*");    
                else
                {
                    int check=0;    //check if there is tail so no need to print " " (space)
                    for(k=0;k<tail_piece;k++)
                    {
                        if(i==tailY[k] && j==tailX[k])  //Where there is tail no need to print space as it disturbs the border
                        {
                            printf("%d",k+1);
                            check=1;
                        }
                    }
                    if(check==0)
                        printf(" ");    //else print space
                }
            }
        }
        printf("\n");   //change line after every column printed succesfully
}

}

// Locator() function locates the Snake and Food in our play area  // 
/* 
   1.Initial Position of snake and the food 
   2.As it is the First function in main() after the Intro() function,
   It can also be called an Initializer Function as it initialises
        a. The gameover to FALSE
        b. score to zero
*/
void Locator() // Inititialiser
{
    // Initialistaion of Snake Poisiton
    snake_headX=WIDTH/2;
    snake_headY=HEIGHT/2;

    // Initialiation of Food Position
    foodX=rand()%(79 + 1 - 2)+2;
    foodY=rand()%(14 + 1 - 2)+2;

    //Intilial gameover state
    gameover=FALSE;
    
    //Intialisation of score
    score=0;

    openpanel = FALSE;

    nextlevel =1;
}

/*
    This function is responsible for the Movememnt of The Snake in the entire game.
    It uses the kbhit() function from the conio.h library.
*/
void Input()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'w':
            {
                keyPressed=1;
                break;
            }
            case 's':
            {
                keyPressed=2;
                break;
            }
            case 'a':
            {
                keyPressed=3;
                break;
            }
            case 'd':
            {
                keyPressed=4;
                break;
            }


        }
    }
}

/*
    This funtion is responsible for every logic used in this game.
    Like - Snake Movement,
           Increment in score when snake eats food,
           new location of food when eaten,
           Tail to be added when snake eats food,
           first tail follows the snake head and other follows each previous tail,
           Gameover = TRUE when snake collide with the border,
*/
void Controller()
{
    int i;
    int prevx,prevy,prev2x,prev2y;
    prevx=tailX[0];
    prevy=tailY[0];
    tailX[0]=snake_headX;
    tailY[0]=snake_headY;
    for(i=1;i<=tail_piece;i++)
    {
        prev2x=tailX[i];
        prev2y=tailY[i];

        tailX[i]=prevx;
        tailY[i]=prevy;

        prevx=prev2x;
        prevy=prev2y;
    }

    switch(keyPressed)
    {
        case 1:
        {
            snake_headY--;
            break;
        }
        case 2:
        {
            snake_headY++;
            break;
        }
        case 3:
        {
            snake_headX--;
            break;
        }
        case 4:
        {
            snake_headX++;
            break;
        }
    }
    if(snake_headX==0||snake_headX==WIDTH||snake_headY==0||snake_headY==HEIGHT)
    {
        if(snake_headX==WIDTH && snake_headY==14){
            nextlevel++;++
        }
        else{
        gameover = TRUE;
        score=0;
        tail_piece=0;}
    }
    else if(snake_headX==foodX && snake_headY==foodY)
    {
        score++;
        foodX=rand()%(79 + 1 - 2)+2;
        foodY=rand()%(14 + 1 - 2)+2;
        tail_piece++;
        

    }

    else if(score==5){
        // gameover=TRUE;
        openpanel=TRUE;
}
else if(snake_headX==WIDTH && snake_headY==14)
{
    nextlevel++;
}

}

/*
    The ScoreBoard() function just display the score on the screen
*/
void Retry()

{
    int retryKeys;
    printf("\nHOPE YOU ENJOYED THE GAME\n");
    printf("\n----> PRESS 1 TO PLAY AGAIN\n");
    printf("----> PRESS 2 TO VIEW THE SCORE\n");
    printf("----> PRESS 0 TO EXIT\n");
    printf("----> ");
    scanf("%d",&retryKeys);
    switch(retryKeys)
    {
        case 1:{
            runRetry = FALSE;
            main();}
        // case 2:
        // {

        // }
        case 0:{
            printf("\n\nHope You Enjoyed The Game.");
            system("exit");}
    }
}

void ScoreBoard()
{
    printf("\nScore = %d\n",score);
}

//  Driver Code Here //
void main()
{

    if(runIntro ==TRUE) /* Intiialy set to TRUE(check at the top) to run the Intro First.*/
        Intro();          /* After running the intro it becomes FALSE and the else part runs  */
    
    else if(runRetry == TRUE)
    {
        Retry();
    }
    else
    {
    Locator();  //Its is the Initialiser function as discussed above so we never wanted to initialise score or position of snake and food everytime
    while(gameover!=TRUE)   
    {
        Display();     // 
        Input();       // 
        Controller();  // 
        ScoreBoard();  // 
    }
    runRetry = TRUE;
    main();
    }
}

// SNAKE GAME WITH C PROGRAMMING  