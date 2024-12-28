#include <SFML/Graphics.hpp>
#include "game.h"
#include <fstream>
using namespace std;
int main()
{
    ifstream file("files/config.cfg");
    ifstream file2("files/leaderboard.txt");
    string temp1;
    string temp2;
    string temp3;
    int columns;
    int rows;
    int width;
    int height;
    int tiles;
    int mines;
    getline(file,temp1);
    getline(file,temp2);
    getline(file,temp3);
    columns=stoi(temp1);
    rows=stoi(temp2);
    width = stoi(temp1)*32;
    height = stoi(temp2)*32+100;
    mines=stoi(temp3);
    tiles=stoi(temp1)*stoi(temp2);
    welcomeWindow welcome(width,height);
    if(welcome.open==true){
        gameWindow game(columns,rows,width,height,tiles,mines);
//        if(game.leaderBool==true){
//            cout << "hi" << endl;
//            leaderboardWindow leader(width,height);
//        }
    }
    return 0;
}