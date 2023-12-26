#define RAYGUI_IMPLEMENTATION
#include <vector>
#include <iostream>
#include <raylib.h>
#include "raygui.h" 

using namespace std;
//Setting all the constants 
const int screenWidth = 700;
const int screenHeight = 800;

const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;

const int tileWidth = 65;
const int tileHeight = 65;
const int gap = 10;
const int tileLeftPadding = 160;
const int tileTopPadding = 150;
//Setting gameState
// gameState = 0 = Initial state
// gameState = 1 = winning state
// gameState = 2 = losing state
int gameState = 0;

int row = 0;


string word[5];
int matches[5][5] = {0};  

string getRandomWord()
{
    // Array of common 5-letter words
    const string commonWords[] = {
        "APPLE", "TABLE", "HOUSE", "HAPPY", "MUSIC", "OCEAN", "CLOUD", "PIANO", "CHAIR", "KNIFE"
    };

    const int numWords = sizeof(commonWords) / sizeof(commonWords[0]);
    srand((int)(time(nullptr)));
    int randomIndex = rand() % numWords;
    string randWord = commonWords[randomIndex];
    cout << randWord;
    return randWord;
}


string targetWord = getRandomWord();

//Generate Tiles and update text ( from word array ) for every tick ( 60fps )
void genTiles() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            string character = string(1, word[j][i]);
            
            DrawText(character.c_str(), tileLeftPadding + 25 + i * (tileWidth + gap), tileTopPadding + 20 + j * (tileHeight + gap), 25, WHITE);

            if(matches[j][i] == MATCH){
                DrawRectangleLines(tileLeftPadding + i * (tileWidth + gap), tileTopPadding + j * (tileHeight + gap), tileWidth, tileHeight, GREEN);
            }
                
            else if(matches[j][i] == PARTIAL_MATCH)
                DrawRectangleLines(tileLeftPadding + i * (tileWidth + gap), tileTopPadding + j * (tileHeight + gap), tileWidth, tileHeight, YELLOW);
            else
                DrawRectangleLines(tileLeftPadding + i * (tileWidth + gap), tileTopPadding + j * (tileHeight + gap), tileWidth, tileHeight, WHITE);
        }
    }
}

//To check correctness of the word
void checkWord(string &targerWord, string &word, int row){
    int totalMatches = 0;
    for (int i = 0; i < 5; i++) { 
        if(word[i] == targerWord[i]){
            matches[row][i] = MATCH;
            totalMatches++;
            //To check if user have won
            if(totalMatches > 4){
                gameState = 1;
            }

        }else{
            bool partialMatch = false;
            for(int k = 0; k < 5; k++){
                if(k == i)
                    continue;

                if(word[i] == targerWord[k]){   
                    matches[row][i] = PARTIAL_MATCH;
                    partialMatch = true;
                    break;
                }
            }
            if((targerWord[i] != word[i]) && !partialMatch){
                matches[row][i] = NOT_MATCH;
            }
        }
    } 
}
//Reset the Game to Default stats
void resetGame() {
    for (int i = 0; i < 5; i++) {
        word[i].clear();
        for (int j = 0; j < 5; j++) {
            matches[j][i] = 0;
        }
    }

    row = 0;
    gameState = 0;
}

void overlay() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GRAY);
    // Checking the game status to display the revelant overlay ( i.e win/lose screen )
    if (gameState == 1) {
        DrawText("YOU WIN!", 220, 400, 55, GREEN);
    } else if (gameState == 2) {
        DrawText("YOU LOST", 200, 400, 55, RED);
        string message = "The word was " + targetWord;
        DrawText(message.c_str(), 210, 470, 25, BLACK);
    }
    //Handling onClick for PlayAgain Btn. If Clicked call resetGame func with setting a new
    // random word to start
    if (GuiButton((Rectangle){235, 500, 200, 50}, "PLAY AGAIN")) {
        resetGame();
        targetWord = getRandomWord();
    }
}

int main() {

    InitWindow(screenWidth, screenHeight, "Wordle Game");
    SetTargetFPS(60);
    //QWERTY Layout keyboard array
    char alphabets[] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    while (WindowShouldClose() == false) {
        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        if(gameState == 1){
            overlay();
        }else if(row == 5){
            gameState = 2;
            overlay();
        }else{

        
            DrawText("WORDLE!", 220, 30, 55, WHITE);

            genTiles();

            // Displaying the Keyboard and handling the onClick for the keys
            for (int i = 0; i < 26; i++) {
                float buttonX = 50 + i * 60;
                float buttonY = 600;

                if (i > 9) {
                    buttonX = 80 + (i - 10) * 60;
                    buttonY = buttonY + 60;
                    if (i > 18) {
                        buttonX = 140 + (i - 19) * 60;
                        buttonY = buttonY + 60;
                    }
                }

                // Draw button
                if (GuiButton((Rectangle){ buttonX, buttonY, 60, 60 }, string(1, alphabets[i]).c_str())) {
                    word[row].push_back(alphabets[i]);
                    if ((word[row].length() % 5) == 0) {
                        checkWord(targetWord, word[row], row);
                        row++;
                    }
                }
            }

            // Delete Button to remove last character from the current row of word array
            if (GuiButton((Rectangle){ 560, 720, 60, 60 }, "Del") && !word[row].empty()) {
                word[row].pop_back();
                for (int i = 0; i < 5; i++) {
                    cout << word[i] << endl;
                }
            }
        }
        EndDrawing();
        
    }

    CloseWindow();
    return 0;
}

