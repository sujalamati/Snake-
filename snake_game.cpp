#include <conio.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <windows.h>

using namespace std;

bool gameOver=false;

int score = 0;

char dir {};

int width = 50;
int height = 19;

short boundaryThickness = 1;

short initLenTail=4;

int fruitX = (rand()%(width-2*boundaryThickness))+boundaryThickness;
int fruitY = (rand()%(height-2*boundaryThickness))+boundaryThickness;

int snakeHeadX = width/2;
int snakeHeadY = height/2;

vector<int> tailX;
vector <int> tailY;

bool fruitFound=false;

void draw();
void setup();
void logic();
void input();
void validFruit();

int main() 
{    
    srand(time(0));

    for (int j=0; j<initLenTail ;j++){
        tailX.push_back(snakeHeadX-j-1);
        tailY.push_back(snakeHeadY);
    }

    while(!kbhit()){
        draw();
        system("CLS");
    }

    while(!gameOver){
        draw();
        input();
        logic();
        setup();

        Sleep(0.0100);   
        system("CLS");
    }
    cout << "GAME OVER !!!" << endl << "Score : " << score;
    return 0;
}

void draw()
{
    for (int i = 0; i<height; i++)
    {
        for (int j=0; j<width ; j++)
        {
            if(i==0 || i==height-1)
            {
                cout << "#";
            }
            else
            {
                bool tailFound=false;
                for (int k=0; k!=tailX.size(); k++)
                {
                    if (tailX[k] == j && tailY[k]==i){
                        tailFound=true;
                        break;
                    }
                }


                if(j==0 || j==width-1)
                {
                    cout << "#";
                    continue;
                }
                if (i==fruitY && j==fruitX)
                {
                    cout << "X";
                    continue;
                }
                if (i==snakeHeadY && j==snakeHeadX){
                    cout << "$";
                    continue;
                }
                if (tailFound){
                    cout<<"O";
                }
                else{
                    cout << " ";
                }
            }
        }
        cout<<endl;
    }
}

void setup()
{
    for (int k=tailX.size(); k != 0; k--){
        tailX[k-1]=tailX[k-2];
        tailY[k-1]=tailY[k-2];
    }

    tailX[0]=snakeHeadX;    
    tailY[0]=snakeHeadY;

    switch(dir){
        case 'w':
        snakeHeadY--;
        break;

        case 'a':
        snakeHeadX--;
        break;

        case 's':
        snakeHeadY++;
        break;

        case 'd':
        snakeHeadX++;
        break;

        default:
        break;
    }
    
    if (fruitFound){
        validFruit();
    }

    if (snakeHeadX==boundaryThickness-1 || snakeHeadX==width-boundaryThickness)
    {
        gameOver=true;
        return;
    }
    if (snakeHeadY==boundaryThickness-1 || snakeHeadY==height-boundaryThickness)
    {   
        gameOver=true;
        return;
    }

    for (int k=0; k!=tailX.size(); k++){
        if (snakeHeadX==tailX[k] && snakeHeadY==tailY[k])
        {
            gameOver=true;
            break;
        }
    }
}

void logic(){
    fruitFound=false;
    if (snakeHeadX==fruitX && snakeHeadY==fruitY){
        fruitX = (rand()%(width-2*boundaryThickness))+boundaryThickness;
        fruitY = (rand()%(height-2*boundaryThickness))+boundaryThickness;
        
        fruitFound=true;

        score+=1;
        tailX.push_back(1);
        tailY.push_back(1);
    }
}

void input()
{
    char keypress;
    if (kbhit())
    {
        keypress=getchar();  
        if (keypress=='w' && dir!='s')
        {
            dir=keypress;
        }
        else if (keypress=='a' && dir!='d')
        {
            dir=keypress;
        }
        else if (keypress=='s' && dir !='w')
        {
            dir=keypress;
        }
        else if (keypress == 'd' && dir != 'a')
        {
            dir=keypress;
        }
    }   
}

void validFruit(void){
    for (int k=0; k!=tailX.size();k++){
        if (fruitX==tailX[k] && fruitY==tailY[k]){
            fruitX = (rand()%(width-2*boundaryThickness))+boundaryThickness;
            fruitY = (rand()%(height-2*boundaryThickness))+boundaryThickness;
            validFruit();
            break;
        }
    } 
}