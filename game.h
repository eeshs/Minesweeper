//
// Created by eeshs on 4/14/2024.
//

#ifndef PROJECT3_GAME_H
#define PROJECT3_GAME_H

#endif //PROJECT3_GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <fstream>
using namespace std;
class welcomeWindow{
private:
    sf::Window* windowPtr;
    sf::VideoMode videoMode;
    sf::Event ev;
public:
    int width;
    int height;
    bool open = false;
    welcomeWindow(int width,int height){
        this->width=width;
        this->height=height;
        sf::RenderWindow window(sf::VideoMode(width, height), "Welcome Window", sf::Style::Close);
        sf::Font font;
        if(!font.loadFromFile("files/font.ttf")){
            cout<<"error"<<endl;
        }
        sf::Text text;
        sf::Text text1;
        text.setFont(font);
        text.setString("WELCOME TO MINESWEEPER!");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(24);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.width/2.0f,textRect.height/2.0f);
        text.setPosition(width/2,height/2-150);
        text1.setFont(font);
        text1.setString("Enter your name:");
        text1.setFillColor(sf::Color::White);
        text1.setCharacterSize(20);
        sf::FloatRect textRect2 = text1.getLocalBounds();
        text1.setOrigin(textRect2.left+textRect2.width/2.0f,textRect2.top+textRect2.height/2.0f);
        text1.setPosition(width/2,height/2-75);
        text.setStyle(sf::Text::Bold);
        text.setStyle(sf::Text::Underlined);
        text1.setStyle(sf::Text::Bold);
        sf::Text inputText;
        inputText.setFont(font);
        inputText.setCharacterSize(18);
        inputText.setFillColor(sf::Color::Yellow);
        inputText.setPosition(width/2, height/2-45);
        sf::RectangleShape cursor;
        cursor.setSize(sf::Vector2f(2, inputText.getCharacterSize()));
        cursor.setFillColor(sf::Color::Yellow);
        cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width, inputText.getPosition().y);
        string userInput="";
        while (window.isOpen())
        {
            while (window.pollEvent(ev))
            {
                if (ev.type == sf::Event::Closed)
                    window.close();
                else if (ev.type == sf::Event::TextEntered) {
                    if((ev.text.unicode>64&&ev.text.unicode<91)||(ev.text.unicode>96)&&(ev.text.unicode<123)){
                        if(userInput.length()==0){
                            char temp = toupper(ev.text.unicode);
                            userInput+=temp;
                            inputText.setString(userInput);
                        }
                        else if(userInput.length()<10){
                            char temp = tolower(ev.text.unicode);
                            userInput += temp;
                            inputText.setString(userInput);
                        }
                        cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width, inputText.getPosition().y);
                    }
                    else if(ev.text.unicode==8){
                        if(userInput.length()>1){
                            userInput= userInput.substr(0,userInput.length()-1);
                            inputText.setString(userInput);
                            cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width, inputText.getPosition().y);
                        }
                        else{
                            userInput="";
                            inputText.setString(userInput);
                            cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width, inputText.getPosition().y);
                        }
                    }
                    inputText.setOrigin(inputText.getLocalBounds().width/2,
                                        inputText.getLocalBounds().height/2);
                    cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width/2+4,
                                       inputText.getPosition().y);
                }
                else if(ev.type==sf::Event::KeyPressed){
                    if(ev.key.scancode==sf::Keyboard::Scan::Enter){
                        if(userInput.length()>0){
                            open = true;
                            window.close();
                        }
                    }
                }

            }

            window.clear(sf::Color::Blue);

            window.draw(text);
            window.draw(text1);
            window.draw(cursor);
            window.draw(inputText);
            window.display();
        }
    }
};
class leaderboardWindow{
public:
    int width;
    int height;
    sf::Window* windowPtr;
    leaderboardWindow(int width,int height){
        this->width=width;
        this->height=height;
        sf::RenderWindow window(sf::VideoMode(width, height), "Leaderboard", sf::Style::Close);
        this->windowPtr=&window;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear(sf::Color::Blue);
            sf::Font font;
            sf::Text text1;
            if(!font.loadFromFile("files/font.ttf")){
                cout<<"error"<<endl;
            }
            text1.setFont(font);
            text1.setString("LEADERBOARD");
            text1.setCharacterSize(20);
            sf::FloatRect textRect = text1.getLocalBounds();
            text1.setOrigin(textRect.width/2.0f,textRect.height/2.0f);
            text1.setPosition(width/2,height/2-120);
            ifstream file("files/leaderboard.txt");
            vector<string> data;
            for(int i=0;i<5;i++){
                string temp;
                string temp2;
                string temp3;
                getline(file,temp);
                if(!font.loadFromFile("files/font.ttf")){
                    cout<<"error"<<endl;
                }
                temp2=temp.substr(0,temp.find(','));
                cout<<temp.find(',')<<endl;
                temp3=temp.substr(temp.find(',')+2,temp.length()-1);
                data.push_back(temp2);
                data.push_back(temp3);
            }
            sf::Text leaderText;
            if(!font.loadFromFile("files/font.ttf")){
                cout<<"error"<<endl;
            }
            leaderText.setFont(font);
            leaderText.setString("1. \t"+data[0]+"\t"+data[1]+"\n"+"2. \t"+data[2]+"\t"+data[3]+"\n"+"3. \t"+data[4]+"\t"+data[5]+"\n"+"4. \t"+data[6]+"\t"+data[7]+"\n"+"5. \t"+data[8]+"\t"+data[9]+"\n");
            leaderText.setCharacterSize(18);
            sf::FloatRect textRect2 = leaderText.getLocalBounds();
            leaderText.setOrigin(textRect2.width/2.0f,textRect2.height/2.0f);
            leaderText.setPosition(width/2,height/2-+20);
            text1.setStyle(sf::Text::Bold);
            text1.setStyle(sf::Text::Underlined);
            leaderText.setStyle(sf::Text::Bold);
            window.draw(text1);
            window.draw(leaderText);
            window.display();
        }


    }
};
class gameWindow{
private:
    sf::Event ev;
public:
    int width;
    int height;
    int rows;
    int columns;
    int tiles;
    int mineCount;
    bool leaderBool;
    struct Tile{
        int val;
        vector<Tile*> neighbors;
        int proxMines=0;
        sf::Texture texture;
        sf::Sprite sprite;
        bool revealed=false;
        Tile(int val){
            if(!texture.loadFromFile("files/images/tile_hidden.png")){
                cout<<"error"<<endl;
            }
            this->val=val;
        }
        void setVal(int val){
            this->val=val;
        }
    };
    vector <vector<Tile>> tileVec;
    map<int, sf::Sprite> parseDigits(sf::Sprite digits){
        map<int, sf::Sprite> digitsMap;
        for(int i=0;i<11;i++){
            sf::IntRect rect(i*21,0,21,32);
            digits.setTextureRect(rect);
            sf::Sprite sprite = digits;
            digitsMap.emplace(i,sprite);
        }
        return digitsMap;
    }
    void resetGame(){
        tileVec.clear();
        vector<Tile> temp;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                Tile tile(0);
                sf::Texture hiddenTile;
                if (!hiddenTile.loadFromFile("files/images/tile_hidden.png")) {
                    cout << "failed" << endl;
                }
                tile.sprite.setTexture(hiddenTile);
                temp.push_back(tile);
            }
            tileVec.push_back(temp);
            temp.clear();
        }
        int currMines = 0;
        while (currMines < mineCount) {
            int row = rand() % rows;
            int col = rand() % columns;
            if (tileVec[row][col].val != -1) {
                tileVec[row][col].val = -1;
                currMines++;
            }
        }

        for (int i = 1; i < rows - 1; i++) {
            for (int j = 1; j < columns - 1; j++) {
                if (tileVec[i][j].val != -1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (i == 0 && j == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == 0 && j == columns - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == rows - 1 && j == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == rows - 1 && j == columns - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (j == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == rows - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (j == columns - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else {
                    continue;
                }
            }
        }
        sf::Texture hiddenTile;
        if (!hiddenTile.loadFromFile("files/images/tile_hidden.png")) {
            cout << "failed" << endl;
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                tileVec[i][j].sprite.setPosition(j * hiddenTile.getSize().x, i * hiddenTile.getSize().y);
            }
        }

    }
    void tileReveal(Tile tile){

        sf::Texture tileRevealed;
        if (!tileRevealed.loadFromFile("files/images/tile_revealed.png")) {
            cout << "failed" << endl;
        }
        tile.sprite.setTexture(tileRevealed);
        for(int k=0;k<tile.neighbors.size();k++){
            if (tile.neighbors[k]->proxMines == 1) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_1.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            }
            else if (tile.neighbors[k]->proxMines == 0) {
                tile.neighbors[k]->texture.loadFromFile("files/images/tile_revealed.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                sf::Texture temp;
                temp.loadFromFile("files/images/tile_hidden.png");
                tile.neighbors[k]->revealed=true;
                if(tile.neighbors[k]->revealed==false){
                    tileReveal(*tile.neighbors[k]);
                }
            }
            else if (tile.neighbors[k]->proxMines == 2) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_2.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            } else if (tile.neighbors[k]->proxMines == 3) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_3.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            } else if (tile.neighbors[k]->proxMines == 4) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_4.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            } else if (tile.neighbors[k]->proxMines == 5) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_5.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            } else if (tile.neighbors[k]->proxMines == 6) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_6.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            } else if (tile.neighbors[k]->proxMines == 7) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_7.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            }
            else if (tile.neighbors[k]->proxMines == 8) {
                tile.neighbors[k]->texture.loadFromFile("files/images/number_8.png");
                tile.neighbors[k]->sprite.setTexture(tile.neighbors[k]->texture);
                tile.neighbors[k]->revealed=true;
            }
        }
    }
    gameWindow(int columns, int rows, int width, int height, int tiles, int mineCount) {
        this->width = width;
        this->height = height;
        this->tiles = tiles;
        this->mineCount = mineCount;
        this->rows=rows;
        this->columns=columns;
        bool won = false;
        bool leaderPause=false;
        vector<Tile> temp;
        sf::Texture hiddenTile;
        bool lost = false;
        if (!hiddenTile.loadFromFile("files/images/tile_hidden.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number1;
        if (!number1.loadFromFile("files/images/number_1.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number2;
        if (!number2.loadFromFile("files/images/number_2.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number3;
        if (!number3.loadFromFile("files/images/number_3.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number4;
        if (!number4.loadFromFile("files/images/number_4.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number5;
        if (!number5.loadFromFile("files/images/number_5.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number6;
        if (!number6.loadFromFile("files/images/number_6.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number7;
        if (!number7.loadFromFile("files/images/number_7.png")) {
            cout << "failed" << endl;
        }
        sf::Texture number8;
        if (!number8.loadFromFile("files/images/number_8.png")) {
            cout << "failed" << endl;
        }
        sf::Texture mine;
        if (!mine.loadFromFile("files/images/mine.png")) {
            cout << "failed" << endl;
        }
        sf::Texture tileRevealed;
        if (!tileRevealed.loadFromFile("files/images/tile_revealed.png")) {
            cout << "failed" << endl;
        }
        sf::Texture happyFace;
        if (!happyFace.loadFromFile("files/images/face_happy.png")) {
            cout << "failed" << endl;
        }
        sf::Texture sadFace;
        if (!sadFace.loadFromFile("files/images/face_lose.png")) {
            cout << "failed" << endl;
        }
        sf::Texture face_win;
        if (!face_win.loadFromFile("files/images/face_win.png")) {
            cout << "failed" << endl;
        }
        sf::Sprite face;
        face.setTexture(happyFace);
        face.setPosition((columns / 2.0) * 32 - 32, 32 * (rows + 0.5));
        sf::Texture debug;
        if (!debug.loadFromFile("files/images/debug.png")) {
            cout << "failed" << endl;
        }
        sf::Sprite bug;
        bug.setTexture(debug);
        bug.setPosition((columns * 32) - 304, 32 * (rows + 0.5));
        sf::Texture pause;
        if (!pause.loadFromFile("files/images/pause.png")) {
            cout << "failed" << endl;
        }
        sf::Texture play;
        if (!play.loadFromFile("files/images/play.png")) {
            cout << "failed" << endl;
        }
        sf::Sprite pauseOrPlay;
        pauseOrPlay.setTexture(pause);
        pauseOrPlay.setPosition((columns * 32) - 240, 32 * (rows + 0.5));
        sf::Texture leaderboardImage;
        if (!leaderboardImage.loadFromFile("files/images/leaderboard.png")) {
            cout << "failed" << endl;
        }
        sf::Sprite leader;
        leader.setTexture(leaderboardImage);
        leader.setPosition((columns * 32) - 176, 32 * (rows + 0.5));
        sf::Texture flag;
        if (!flag.loadFromFile("files/images/flag.png")) {
            cout << "failed" << endl;
        }
        sf::Texture digitsText;
        if (!digitsText.loadFromFile("files/images/digits.png")) {
            cout << "failed" << endl;
        }
        sf::Sprite digits;
        digits.setTexture(digitsText);
        map<int, sf::Sprite> digitMap = parseDigits(digits);
        sf::Sprite digit1;
        sf::Sprite digit2;
        sf::Sprite digit3;
        sf::Sprite negative;
        sf::Sprite clock0;
        sf::Sprite clock1;
        sf::Sprite clock2;
        sf::Sprite clock3;
        negative = digitMap.at(10);
        negative.setPosition(12, 32 * (rows + 0.5) + 16);
        int digitArr[3];
        int nonFlaggedMines = mineCount;
        int tempMine = nonFlaggedMines;
        for (int i = 2; i > -1; i--) {
            digitArr[i] = tempMine % 10;
            tempMine /= 10;
        }
        digit1 = digitMap.at(digitArr[0]);
        digit2 = digitMap.at(digitArr[1]);
        digit3 = digitMap.at(digitArr[2]);
        digit1.setPosition(33, 32 * (rows + 0.5) + 16);
        digit2.setPosition(54, 32 * (rows + 0.5) + 16);
        digit3.setPosition(75, 32 * (rows + 0.5) + 16);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                Tile tile(0);
                sf::Texture hiddenTile;
                if (!hiddenTile.loadFromFile("files/images/tile_hidden.png")) {
                    cout << "failed" << endl;
                }
                tile.sprite.setTexture(hiddenTile);
                temp.push_back(tile);
            }
            tileVec.push_back(temp);
            temp.clear();
        }
        int currMines = 0;
        while (currMines < mineCount) {
            int row = rand() % rows;
            int col = rand() % columns;
            if (tileVec[row][col].val != -1) {
                tileVec[row][col].val = -1;
                currMines++;
            }
        }
        for (int i = 1; i < rows - 1; i++) {
            for (int j = 1; j < columns - 1; j++) {
                if (tileVec[i][j].val != -1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (i == 0 && j == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == 0 && j == columns - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == rows - 1 && j == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == rows - 1 && j == columns - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (j == 0) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (i == rows - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j + 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j + 1]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else if (j == columns - 1) {
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i - 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j - 1]);
                    tileVec[i][j].neighbors.push_back(&tileVec[i + 1][j]);
                    //done
                    for (int m = 0; m < tileVec[i][j].neighbors.size(); m++) {
                        if (tileVec[i][j].neighbors[m]->val == -1) {
                            tileVec[i][j].proxMines++;
                        }
                    }
                } else {
                    continue;
                }
            }
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                tileVec[i][j].sprite.setPosition(j * hiddenTile.getSize().x, i * hiddenTile.getSize().y);
            }
        }
        sf::RenderWindow window(sf::VideoMode(width, height), "Game Window", sf::Style::Close);
        auto start_time = chrono::high_resolution_clock::now();
        auto pauseTime = chrono::high_resolution_clock::now();
        auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-pauseTime).count();
        bool paused=false;
        while (window.isOpen()) {
            while (window.pollEvent(ev)) {
                if (ev.type == sf::Event::Closed)
                    window.close();
                else if (ev.type == sf::Event::MouseButtonPressed) {
                    if (ev.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
                        sf::FloatRect faceBounds = face.getGlobalBounds();
                        sf::FloatRect bugBounds = bug.getGlobalBounds();
                        sf::FloatRect pauseBounds = pauseOrPlay.getGlobalBounds();
                        sf::FloatRect leaderBounds = leader.getGlobalBounds();
                        for (int i = 0; i < rows; ++i) {
                            for (int j = 0; j < columns; ++j) {
                                sf::FloatRect tileBounds = tileVec[i][j].sprite.getGlobalBounds();
                                if (tileBounds.contains(worldPos)&&tileVec[i][j].sprite.getTexture()!=&flag&&lost==false&&won==false) {
                                    if (tileVec[i][j].val == -1) {
                                        tileVec[i][j].sprite.setTexture(mine);
                                        face.setTexture(sadFace);
                                        lost=true;
                                    }
                                    else if (tileVec[i][j].proxMines == 0) {
                                        tileVec[i][j].sprite.setTexture(tileRevealed);
                                        tileReveal(tileVec[i][j]);
                                    }else if (tileVec[i][j].proxMines == 1) {
                                        tileVec[i][j].sprite.setTexture(number1);
                                        tileVec[i][j].revealed=true;
                                    } else if (tileVec[i][j].proxMines == 2) {
                                        tileVec[i][j].sprite.setTexture(number2);
                                        tileVec[i][j].revealed=true;
                                    } else if (tileVec[i][j].proxMines == 3) {
                                        tileVec[i][j].sprite.setTexture(number3);
                                        tileVec[i][j].revealed=true;
                                    } else if (tileVec[i][j].proxMines == 4) {
                                        tileVec[i][j].sprite.setTexture(number4);
                                        tileVec[i][j].revealed=true;
                                    } else if (tileVec[i][j].proxMines == 5) {
                                        tileVec[i][j].sprite.setTexture(number5);
                                        tileVec[i][j].revealed=true;
                                    }
                                    else if (tileVec[i][j].proxMines == 6) {
                                        tileVec[i][j].sprite.setTexture(number6);
                                        tileVec[i][j].revealed=true;
                                    }
                                    else if (tileVec[i][j].proxMines == 7) {
                                        tileVec[i][j].sprite.setTexture(number7);
                                        tileVec[i][j].revealed=true;
                                    }
                                    else if (tileVec[i][j].proxMines == 8) {
                                        tileVec[i][j].sprite.setTexture(number8);
                                        tileVec[i][j].revealed=true;
                                    }
                                    /*
                                    bool yes=true;
                                    for(int i=0;i<rows;i++){
                                        for(int j=0;j<columns;j++){
                                            if(tileVec[i][j].sprite.getTexture()==&hiddenTile&&(tileVec[i][j].val!=-1)){
                                                yes=false;
                                                break;
                                            }
                                        }
                                    }
                                    if(yes==true){
                                        won=true;
                                        face.setTexture(face_win);
                                    }
                                     */
                                }
                            }
                        }
                        if (leaderBounds.contains(worldPos)) {
                            leaderPause=true;
                            leaderBool=true;
                            for(int i=0;i<rows;i++){
                                for(int j=0;j<columns;j++){
                                    tileVec[i][j].sprite.setTexture(tileRevealed);
                                }
                            }
                        }
                        else if(faceBounds.contains(worldPos)){
                            resetGame();
                            for(int i=0;i<rows;i++){
                                for(int j=0;j<columns;j++){
                                    tileVec[i][j].sprite.setTexture(hiddenTile);
                                }
                            }
                            nonFlaggedMines=mineCount;
                            int tempMine2=nonFlaggedMines;
                            for (int i = 2; i > -1; i--) {
                                digitArr[i] = tempMine2 % 10;
                                tempMine2 /= 10;
                            }
                            digit1 = digitMap.at(digitArr[0]);
                            digit2 = digitMap.at(digitArr[1]);
                            digit3 = digitMap.at(digitArr[2]);
                            digit1.setPosition(33, 32 * (rows + 0.5) + 16);
                            digit2.setPosition(54, 32 * (rows + 0.5) + 16);
                            digit3.setPosition(75, 32 * (rows + 0.5) + 16);
                            if(face.getTexture()==&sadFace){
                                lost=false;
                                face.setTexture(happyFace);
                            }
                            start_time = chrono::high_resolution_clock::now();
                            pauseTime = chrono::high_resolution_clock::now();
                            elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-pauseTime).count();
                        }
                        else if (bugBounds.contains(worldPos)) {
                            for (int i = 0; i < rows; ++i) {
                                for (int j = 0; j < columns; ++j) {
                                    if (tileVec[i][j].val == -1) {
                                        tileVec[i][j].sprite.setTexture(mine);
                                    }
                                }
                            }
                        }
                        else if(pauseBounds.contains(worldPos)&&lost==false&&won==false){
                            paused=!paused;
                            if(paused){
                                pauseOrPlay.setTexture(play);
                                pauseTime=chrono::high_resolution_clock::now();

                            }
                            else{
                                for(int i=0;i<rows;i++){
                                    for(int j=0;j<columns;j++){
                                        if (tileVec[i][j].revealed==false) {
                                            tileVec[i][j].sprite.setTexture(hiddenTile);
                                        }
                                        else{
                                            if(tileVec[i][j].proxMines==0){
                                                tileVec[i][j].sprite.setTexture(tileRevealed);
                                                tileReveal(tileVec[i][j]);
                                            }
                                            else if (tileVec[i][j].proxMines == 1) {
                                                tileVec[i][j].sprite.setTexture(number1);
                                            } else if (tileVec[i][j].proxMines == 2) {
                                                tileVec[i][j].sprite.setTexture(number2);
                                            } else if (tileVec[i][j].proxMines == 3) {
                                                tileVec[i][j].sprite.setTexture(number3);
                                            } else if (tileVec[i][j].proxMines == 4) {
                                                tileVec[i][j].sprite.setTexture(number4);
                                            } else if (tileVec[i][j].proxMines == 5) {
                                                tileVec[i][j].sprite.setTexture(number5);
                                            }
                                            else if (tileVec[i][j].proxMines == 6) {
                                                tileVec[i][j].sprite.setTexture(number6);
                                            }
                                            else if (tileVec[i][j].proxMines == 7) {
                                                tileVec[i][j].sprite.setTexture(number7);
                                            }
                                            else if (tileVec[i][j].proxMines == 8) {
                                                tileVec[i][j].sprite.setTexture(number8);
                                            }
                                        }
                                    }
                                }
                                pauseOrPlay.setTexture(pause);
                                auto unPausedTime = chrono::steady_clock::now();
                                elapsed_paused_time += chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-pauseTime).count();
                            }
                        }
                    }
                    else if (ev.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
                        for (int i = 0; i < rows; ++i) {
                            for (int j = 0; j < columns; ++j) {
                                sf::FloatRect tileBounds = tileVec[i][j].sprite.getGlobalBounds();
                                if (tileBounds.contains(worldPos)) {
                                    if (tileVec[i][j].sprite.getTexture() != &flag) {
                                        tileVec[i][j].sprite.setTexture(flag);
                                        nonFlaggedMines--;
                                    }
                                    else {
                                        tileVec[i][j].sprite.setTexture(hiddenTile);
                                        nonFlaggedMines++;
                                    }
                                    int tempMine = nonFlaggedMines;
                                    if (nonFlaggedMines < 0) {
                                        tempMine = abs(nonFlaggedMines);
                                        negative.setPosition(12, 32 * (rows + 0.5) + 16);
                                    }
                                    for (int i = 2; i > -1; i--) {
                                        digitArr[i] = tempMine % 10;
                                        tempMine /= 10;
                                    }
                                    digit1 = digitMap.at(digitArr[0]);
                                    digit2 = digitMap.at(digitArr[1]);
                                    digit3 = digitMap.at(digitArr[2]);
                                    digit1.setPosition(33, 32 * (rows + 0.5) + 16);
                                    digit2.setPosition(54, 32 * (rows + 0.5) + 16);
                                    digit3.setPosition(75, 32 * (rows + 0.5) + 16);
                                }
                            }
                        }
                    }
                }
            }

        window.clear(sf::Color(190, 190, 190));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                window.draw(tileVec[i][j].sprite);
            }
        }
        bool temp2=true;
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                if(tileVec[i][j].val!=-1&&tileVec[i][j].revealed==false){
                    temp2=false;
                    break;
                }
            }
        }
        if(temp2==true){
            won=true;
            face.setTexture(face_win);
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    if(tileVec[i][j].val==-1){
                        tileVec[i][j].sprite.setTexture(flag);
                    }
                }
            }
        }

        if(paused==true){
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    tileVec[i][j].sprite.setTexture(tileRevealed);
                }
            }
        }
        else{
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    if(tileVec[i][j].sprite.getTexture()!=&flag&&tileVec[i][j].sprite.getTexture()!=&mine){
                        if (tileVec[i][j].revealed==false) {
                            tileVec[i][j].sprite.setTexture(hiddenTile);
                        }
                        else{
                            if(tileVec[i][j].proxMines==0){
                                tileVec[i][j].sprite.setTexture(tileRevealed);
                                tileReveal(tileVec[i][j]);
                            }
                            else if (tileVec[i][j].proxMines == 1) {
                                tileVec[i][j].sprite.setTexture(number1);
                            } else if (tileVec[i][j].proxMines == 2) {
                                tileVec[i][j].sprite.setTexture(number2);
                            } else if (tileVec[i][j].proxMines == 3) {
                                tileVec[i][j].sprite.setTexture(number3);
                            } else if (tileVec[i][j].proxMines == 4) {
                                tileVec[i][j].sprite.setTexture(number4);
                            } else if (tileVec[i][j].proxMines == 5) {
                                tileVec[i][j].sprite.setTexture(number5);
                            }
                            else if (tileVec[i][j].proxMines == 6) {
                                tileVec[i][j].sprite.setTexture(number6);
                            }
                            else if (tileVec[i][j].proxMines == 7) {
                                tileVec[i][j].sprite.setTexture(number7);
                            }
                            else if (tileVec[i][j].proxMines == 8) {
                                tileVec[i][j].sprite.setTexture(number8);
                            }
                    }
                    }
                }
            }
        }

        auto game_duration=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-start_time);
        int total_time=game_duration.count();
        int minutes;
        int seconds;
        bool leaderPause=false;
        if(!paused&&lost==false&&leaderPause==false&&won==false&&leaderBool==false&&leaderPause==false){
            total_time=total_time-elapsed_paused_time;
            minutes=total_time/60;
            seconds=total_time%60;
        }
        int min0=minutes/10%10;
        int min1=minutes%10;
        int sec0=seconds/10%10;
        int sec1=seconds%10;
        clock0=digitMap.at(min0);
        clock1=digitMap.at(min1);
        clock2=digitMap.at(sec0);
        clock3=digitMap.at(sec1);
        clock0.setPosition((columns*32)-97,32*(rows+0.5)+16);
        clock1.setPosition((columns*32)-76,32*(rows+0.5)+16);
        clock2.setPosition((columns*32)-54,32*(rows+0.5)+16);
        clock3.setPosition((columns*32)-33,32*(rows+0.5)+16);
        window.draw(face);
        window.draw(pauseOrPlay);
        window.draw(leader);
        window.draw(bug);
        window.draw(digit1);
        window.draw(digit2);
        window.draw(digit3);
        window.draw(clock0);
        window.draw(clock1);
        window.draw(clock2);
        window.draw(clock3);
        if(nonFlaggedMines<0){
            window.draw(negative);
        }
        window.display();
            if(leaderBool==true){
                leaderboardWindow leader(width-30,height-30);
                while(leader.windowPtr->isOpen()){
                    leaderPause=true;
                    for(int i=0;i<rows;i++){
                        for(int j=0;j<columns;j++){
                            tileVec[i][j].sprite.setTexture(tileRevealed);
                        }
                    }
                }
                leaderPause=false;
                for(int i=0;i<rows;i++){
                    for(int j=0;j<columns;j++){
                        if (tileVec[i][j].revealed==false) {
                            tileVec[i][j].sprite.setTexture(hiddenTile);
                        }
                        else{
                            if(tileVec[i][j].proxMines==0){
                                tileVec[i][j].sprite.setTexture(tileRevealed);
                                tileReveal(tileVec[i][j]);
                            }
                            else if (tileVec[i][j].proxMines == 1) {
                                tileVec[i][j].sprite.setTexture(number1);
                            } else if (tileVec[i][j].proxMines == 2) {
                                tileVec[i][j].sprite.setTexture(number2);
                            } else if (tileVec[i][j].proxMines == 3) {
                                tileVec[i][j].sprite.setTexture(number3);
                            } else if (tileVec[i][j].proxMines == 4) {
                                tileVec[i][j].sprite.setTexture(number4);
                            } else if (tileVec[i][j].proxMines == 5) {
                                tileVec[i][j].sprite.setTexture(number5);
                            }
                            else if (tileVec[i][j].proxMines == 6) {
                                tileVec[i][j].sprite.setTexture(number6);
                            }
                            else if (tileVec[i][j].proxMines == 7) {
                                tileVec[i][j].sprite.setTexture(number7);
                            }
                            else if (tileVec[i][j].proxMines == 8) {
                                tileVec[i][j].sprite.setTexture(number8);
                            }
                        }
                    }
                }
                leaderBool = false;
            }

        }
        }
};



