#define RAYGUI_IMPLEMENTATION
#include <vector>
#include <iostream>
#include <raylib.h>
#include "raygui.h" // Include the RayGUI header

using namespace std;

const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;

const int tileWidth = 50;
const int tileHeight = 50;
const int gap = 10;

string word;
int matches[5][5] = {0};

string getRandomWord()
{
    return "ABCDE";
}



void genTiles() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if(matches[j][i] == MATCH)
                DrawRectangleLines(50 + i * (tileWidth + gap), 100 + j * (tileHeight + gap), tileWidth, tileHeight, GREEN);
            else if(matches[j][i] == PARTIAL_MATCH)
                DrawRectangleLines(50 + i * (tileWidth + gap), 100 + j * (tileHeight + gap), tileWidth, tileHeight, YELLOW);
            else
                DrawRectangleLines(50 + i * (tileWidth + gap), 100 + j * (tileHeight + gap), tileWidth, tileHeight, RED);
        }
    }
}
//Simple Algorithm to check Matchness of the word
int checkWord(string &targerWord, string &word){
    for (int i = 0; i < 5; i++) { 
        if(targerWord[i] == word[i]){
            matches[0][i] = MATCH;
            cout << "Match" << endl;
        }else{
            bool partialMatch = false;
            for(int k = 0; k < 5; k++){
                if(k == i)
                    continue;

                if(word[i] == targerWord[k]){   
                    cout << "Partially Matched" << endl;
                    matches[0][i] = PARTIAL_MATCH;
                    partialMatch = true;
                    break;
                }
                
            }
            
            if((targerWord[i] != word[i]) && !partialMatch){
                matches[0][i] = NOT_MATCH;
                cout << "NO Match" << endl;
            }
            
        }
        
    } 
    return 0;
}
void generate(){
    DrawText("A", 10, 10, 20, LIGHTGRAY);
}
int main() {
    string targetWord = getRandomWord();

    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Wordle Game");
    SetTargetFPS(60);

    // Define an array of alphabets
    char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (WindowShouldClose() == false) {

        //Draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto i = word.begin(); i != word.end(); i++)
            DrawText(&word[i], 60 + (i - word.begin()) * 50, 120, 20, WHITE);
        
       
        genTiles();

        // Draw buttons for each alphabet
        for (int i = 0; i < 26; i++) {
            // Calculate button position
            float buttonX = 50 + i * 40;
            float buttonY = 500;

            // Draw button
            if (GuiButton((Rectangle){ buttonX, buttonY, 50, 60 },  to_string(alphabets[i]).c_str())) {
                //generate();
                word.push_back(alphabets[i]);
                if(word.length() > 4){
                    int a = checkWord(targetWord, word);  
                }
                
                cout << "Button " << alphabets[i] << " clicked!" << endl;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
