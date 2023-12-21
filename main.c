// @Author: Adam Fuzesi
// @Date: 12/19/2023
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// initialization of the used variables and constants

float A, B, C;

float cubeWidth = 10;
int widthGeneral = 160, heightGeneral = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';
int distanceFromCam = 60;
float K1 = 40;

float incrementSpeed = 0.6;
float x, y, z;
float ooz;
int xp, yp;
int idx;

// handles the calculation of the X axis projections

float calculateX(int i, int j, int k)
{
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
           j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}
// handles the calculation of the Y axis projections
float calculateY(int i, int j, int k)
{
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
           j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
           i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k)
{
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, char ch)
{
    // Calculates projections
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;
    ooz = 1 / z;

    // Corrects the aspect ratio, migth have to adjust once other sides are programmed
    float aspectRatio = (float)heightGeneral / (float)widthGeneral;

    // Centering the cube
    xp = (int)(widthGeneral / 2 + (K1 * ooz * x));
    // Vertical offset centers the projection by lowering it
    int verticalOffset = 10;
    // Example offset, adjust as needed
    yp = (int)(heightGeneral / 2 - (K1 * ooz * y * aspectRatio)) + verticalOffset;

    // Buffer index's calculation
    idx = xp + yp * widthGeneral;

    if (idx >= 0 && idx < widthGeneral * heightGeneral)
    {
        if (ooz > zBuffer[idx])
        {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}
int main()
// handles the logic for printing the projections.
{
    printf("\x1b[2J");
    while (1)
    {
        memset(buffer, backgroundASCIICode, widthGeneral * heightGeneral);
        memset(zBuffer, 0, widthGeneral * heightGeneral * 4);
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed)
        {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed)
            {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '.');
                calculateForSurface(cubeWidth, cubeY, cubeX, '#');
                calculateForSurface(-cubeWidth, cubeX, -cubeY, '&');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '~');
                calculateForSurface(cubeX, -cubeY, cubeWidth, '$');
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < widthGeneral * heightGeneral; k++)
        {
            putchar(k % widthGeneral ? buffer[k] : 10);
        }

        A += 0.005;
        B += 0.005;
        usleep(1000);
    }
    return 0;
}
