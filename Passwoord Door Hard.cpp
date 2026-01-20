#include "tiny2d.h"
#include<string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

std::string GenerarOperacion(int target);
void _ROOM(float dt);
void _PAPER(float dt);
void _END(float dt);

typedef enum {
    ROOM,
    PAPER,
    END
} Scene;

std::string GenerarOperacion(int target) {
    int A, B;
    int op = rand() % 4; // 0 suma, 1 resta, 2 multiplicación, 3 división

    switch (op) {

        // SUMA: A + B = target (operandos pequeños)
        case 0:
            A = RandIntRange(0, target);
            B = target - A;
            return to_string(A) + " + " + to_string(B);

        // RESTA BONITA: A - B = target (operandos 1–9)
        case 1:
            A = RandIntRange(target, 9); // A siempre entre target y 9
            B = A - target;              // B siempre entre 0 y 9
            return to_string(A) + " - " + to_string(B);

        // MULTIPLICACIÓN EXACTA: A * B = target
        case 2: {
            if (target == 0) {
                A = 0;
                B = RandIntRange(1, 9);
                return "0 * " + to_string(B);
            }

            vector<int> divs;
            for (int i = 1; i <= target; i++)
                if (target % i == 0)
                    divs.push_back(i);

            A = divs[rand() % divs.size()];
            B = target / A;
            return to_string(A) + " * " + to_string(B);
        }

        // DIVISIÓN EXACTA: A / B = target
        case 3:
            B = RandIntRange(1, 9);   // divisor pequeño
            A = target * B;           // múltiplo exacto
            return to_string(A) + " / " + to_string(B);
    }

    return "ERROR";
}


int numberOne;
int numberTwo;
int numberThree;
int numberFour;
int numberFive;
int numberSix;
int numberSeven;
int numberEight;
int numberNine;
string passwordStr;
int password;
string op1, op2, op3, op4, op5, op6, op7, op8, op9;
bool codeAccepted = false;
string inputCode = "";
Scene currentScene = ROOM;

bool tiny2D_Init() {
    srand(time(NULL));
    numberOne = RandIntRange(1, 9);
    numberTwo = RandIntRange(1, 9);
    numberThree = RandIntRange(1, 9);
    numberFour = RandIntRange(1, 9);
    numberFive = RandIntRange(1, 9);
    numberSix = RandIntRange(1, 9);
    numberSeven = RandIntRange(1, 9);
    numberEight = RandIntRange(1, 9);
    numberNine = RandIntRange(1, 9);
    op1 = GenerarOperacion(numberOne);
    op2 = GenerarOperacion(numberTwo);
    op3 = GenerarOperacion(numberThree);
    op4 = GenerarOperacion(numberFour);
    op5 = GenerarOperacion(numberFive);
    op6 = GenerarOperacion(numberSix);
    op7 = GenerarOperacion(numberSeven);
    op8 = GenerarOperacion(numberEight);
    op9 = GenerarOperacion(numberNine);
    passwordStr = to_string(numberOne) + to_string(numberTwo) + to_string(numberThree) + to_string(numberFour) + to_string(numberFive) + to_string(numberSix) + to_string(numberSeven) + to_string(numberEight) + to_string(numberNine);
    password = stoi(passwordStr);
    return true;
}

void _ROOM(float dt) {
    ClearBackground(color.WHITE);
    DrawText2D("You are in a room.\nPress P for look a PAPER.", 10, 10, color.BLACK);
    DrawText2D("Enter the 9-digit code to open the door:", 10, 100, color.BLACK);
    DrawText2D(("Input: " + inputCode).c_str(), 10, 130, color.BLACK);
    
    for (int k = '1'; k <= '9'; k++) {
        if (IsKeyPressed(k)) {
            inputCode += (char)k;
        }
    }

    if (IsKeyPressed(VK_BACK)) {
        if (!inputCode.empty()) {
            inputCode.pop_back();
        }
    }
    if (IsKeyPressed(VK_RETURN)) {
        if (inputCode.size() == 9) {
            if (inputCode == to_string(password)) {
                codeAccepted = true;
                inputCode = "Code Accepted!";
                currentScene = END;
            } else {
                inputCode = "";
            }
        }
    }
    if (inputCode.size() > 9) {
        inputCode = inputCode.substr(0, 9);
    }
}

void _PAPER(float dt) {
    ClearBackground(color.GRAY);
    DrawText2D("You are looking a paper.\nPress R for ROOM.", 10, 10, color.WHITE);
    DrawText2D((std::string("The operations are: \n" + op1 + "\n" + op2 + "\n" + op3 + "\n" + op4 + "\n" + op5 + "\n" + op6 + "\n" + op7 + "\n" + op8 + "\n" + op9)).c_str(), 50, 50, color.WHITE);
}

void _END(float dt) {
    ClearBackground(color.BLACK);
    DrawText2D("The door is open!\nYou escaped!\n\nPress R to restart.", 320, 268, color.WHITE);
}

bool tiny2D_Update(float dt) {
    static bool firstFrame = true;
    
    if (firstFrame) {
        SetFullscreen(true);
        firstFrame = false;
    }

    if (IsKeyPressed(VK_ESCAPE)) {
        return false;
    }

    if (!codeAccepted) {
        if (IsKeyPressed('R')) {
            currentScene = ROOM;
        } else if (IsKeyPressed('P')) {
            currentScene = PAPER;
        }
    } else {
        if (IsKeyPressed('R')) {
            numberOne = RandIntRange(1, 9);
            numberTwo = RandIntRange(1, 9);
            numberThree = RandIntRange(1, 9);
            numberFour = RandIntRange(1, 9);
            numberFive = RandIntRange(1, 9);
            numberSix = RandIntRange(1, 9);
            numberSeven = RandIntRange(1, 9);
            numberEight = RandIntRange(1, 9);
            numberNine = RandIntRange(1, 9);
            op1 = GenerarOperacion(numberOne);
            op2 = GenerarOperacion(numberTwo);
            op3 = GenerarOperacion(numberThree);
            op4 = GenerarOperacion(numberFour);
            op5 = GenerarOperacion(numberFive);
            op6 = GenerarOperacion(numberSix);
            op7 = GenerarOperacion(numberSeven);
            op8 = GenerarOperacion(numberEight);
            op9 = GenerarOperacion(numberNine);
            passwordStr = to_string(numberOne) + to_string(numberTwo) + to_string(numberThree) + to_string(numberFour) + to_string(numberFive) + to_string(numberSix) + to_string(numberSeven) + to_string(numberEight) + to_string(numberNine);
            password = stoi(passwordStr);
            codeAccepted = false;
            inputCode = "";
            currentScene = ROOM;
        }
    }

    switch(currentScene) {
        case ROOM:
            _ROOM(dt);
            break;
        case PAPER:
            _PAPER(dt);
            break;
        case END:
            _END(dt);
            break;
    }

    return true;
}

int main() {
    return tiny2D_Run(800, 600, "Password Door");
}