// @Author: Adam Fuzesi 
// @Date: 12/19/2023

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// initialization of the used variables and constants

int A, B, C;

float cubeWidth =  10; 
int widthGeneral = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';

float incrementSpeed = 0.6;

// handles the calculation of the X axis projections

float calculateX(int i, int j, int k) {
    return j * sin(A)* sin(B) * cos(C) - k * cos(A)  * sin(B) * cos(C) + 
           j * cos(A) * sin(C) + k *  sin(A) *   sin(C) + i * cos(B) * cos(C);
}
// handles the calculation of the Y axis projections 
float calculateY (int i ,int j, int k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - 
           j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - 
           i * cos(B) * sin(C);
}

float calculateZ (int i, int j, int k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

int main() {
    printf("\x1b[2J");
    while(1) {
        memset(buffer, backgroundASCIICode, widthGeneral * height);

    }
    return 0;
}

int createRotation() {
    return 0;
}

