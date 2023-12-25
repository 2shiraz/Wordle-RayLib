#define RAYGUI_IMPLEMENTATION
#include <vector>
#include <iostream>
#include <raylib.h>
#include "raygui.h" 

using namespace std;

const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;

const int tileWidth = 65;
const int tileHeight = 65;
const int gap = 10;

int row = 0;

string word[5];
int matches[5][5] = {0};

string getRandomWord()
{
    return "EVOKE";
}

void genTiles() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            string character = string(1, word[j][i]);
            
            DrawText(character.c_str(), 68 + i * (tileWidth + gap), 120 + j * (tileHeight + gap), 25, WHITE);

            if(matches[j][i] == MATCH){
                DrawRectangleLines(50 + i * (tileWidth + gap), 100 + j * (tileHeight + gap), tileWidth, tileHeight, GREEN);
            }
                
            else if(matches[j][i] == PARTIAL_MATCH)
                DrawRectangleLines(50 + i * (tileWidth + gap), 100 + j * (tileHeight + gap), tileWidth, tileHeight, YELLOW);
            else
                DrawRectangleLines(50 + i * (tileWidth + gap), 100 + j * (tileHeight + gap), tileWidth, tileHeight, GRAY);
        }
    }
}
void won(){

}
//Simple Algorithm to check Matchness of the word
void checkWord(string &targerWord, string &word, int row){
    int totalMatches = 0;
    for (int i = 0; i < 5; i++) { 
        if(word[i] == targerWord[i]){
            matches[row][i] = MATCH;
            totalMatches++;
            if(totalMatches > 4){
                cout << "You WON!!";
                //break;
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

int main() {
    string targetWord = getRandomWord();

    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Wordle Game");
    SetTargetFPS(60);

    // Define an array of alphabets
    char alphabets[] = "QWERTYUIOP/nASDFGHJKLZXCVBNM";

    while (WindowShouldClose() == false) {


        //Draw
        BeginDrawing();
        ClearBackground(BLACK);

        genTiles();

        for (int i = 0; i < 26; i++) {
            float buttonX = 50 + i * 40;
            float buttonY = 500;

            if(alphabets[i] == '/n'){
                cout << "N found";
            }
            // Draw button
            if (GuiButton((Rectangle){ buttonX, buttonY, 40, 40 }, string(1, alphabets[i]).c_str())) {
                word[row].push_back(alphabets[i]);
                if((word[row].length() % 5) == 0){
                    checkWord(targetWord, word[row], row);
                    row++;  
                }
                //cout << "Button " << alphabets[i] << " clicked!" << endl;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
