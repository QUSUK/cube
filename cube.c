#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //для функции system()

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

struct cube {
    float A, B, C;

    float cube_width;
    int width;
    int height;
    float zBuffer[160 * 44];
    char buffer[160 * 44];
    int back_ASCII_Code;
    int dis_from_cam;
    float horiz_offset;
    float K1;

    float increment_speed;

    float x, y, z;
    float ooz;
    int xp, yp;
    int idx;
};


float calculateX(int i, int j, int k, struct cube* object);

float calculateY(int i, int j, int k, struct cube* object);

float calculateZ(int i, int j, int k, struct cube* object);

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch, struct cube* object);

void Initializ(struct cube* object);



int main() {

    struct cube my_ascii_cube;

    Initializ(&my_ascii_cube);

    system("cls");
    while (1) {
        memset(my_ascii_cube.buffer, my_ascii_cube.back_ASCII_Code, my_ascii_cube.width * my_ascii_cube.height);
        memset(my_ascii_cube.zBuffer, 0, my_ascii_cube.width * my_ascii_cube.height * 4);
        my_ascii_cube.cube_width = 20;
        my_ascii_cube.horiz_offset = -2 * my_ascii_cube.cube_width;

        for (float cubeX = -my_ascii_cube.cube_width; cubeX < my_ascii_cube.cube_width; cubeX += my_ascii_cube.increment_speed) {
            for (float cubeY = -my_ascii_cube.cube_width; cubeY < my_ascii_cube.cube_width;
                cubeY += my_ascii_cube.increment_speed) {
                calculateForSurface(cubeX, cubeY, -my_ascii_cube.cube_width, '@', &my_ascii_cube);
                calculateForSurface(my_ascii_cube.cube_width, cubeY, cubeX, '$', &my_ascii_cube);
                calculateForSurface(-my_ascii_cube.cube_width, cubeY, -cubeX, '~', &my_ascii_cube);
                calculateForSurface(-cubeX, cubeY, my_ascii_cube.cube_width, '#', &my_ascii_cube);
                calculateForSurface(cubeX, -my_ascii_cube.cube_width, -cubeY, ';', &my_ascii_cube);
                calculateForSurface(cubeX, my_ascii_cube.cube_width, cubeY, '+', &my_ascii_cube);
            }
        }
        my_ascii_cube.cube_width = 10;
        my_ascii_cube.horiz_offset = 1 * my_ascii_cube.cube_width;


         /*second cube*/
        for (float cubeX = -my_ascii_cube.cube_width; cubeX < my_ascii_cube.cube_width; cubeX += my_ascii_cube.increment_speed) {
            for (float cubeY = -my_ascii_cube.cube_width; cubeY < my_ascii_cube.cube_width;
                cubeY += my_ascii_cube.increment_speed) {
                calculateForSurface(cubeX, cubeY, -my_ascii_cube.cube_width, '@', &my_ascii_cube);
                calculateForSurface(my_ascii_cube.cube_width, cubeY, cubeX, '$', &my_ascii_cube);
                calculateForSurface(-my_ascii_cube.cube_width, cubeY, -cubeX, '~', &my_ascii_cube);
                calculateForSurface(-cubeX, cubeY, my_ascii_cube.cube_width, '#', &my_ascii_cube);
                calculateForSurface(cubeX, -my_ascii_cube.cube_width, -cubeY, ';', &my_ascii_cube);
                calculateForSurface(cubeX, my_ascii_cube.cube_width, cubeY, '+', &my_ascii_cube);
            }
        }
        my_ascii_cube.cube_width = 5;
        my_ascii_cube.horiz_offset = 8 * my_ascii_cube.cube_width;
        // third cube
        for (float cubeX = -my_ascii_cube.cube_width; cubeX < my_ascii_cube.cube_width; cubeX += my_ascii_cube.increment_speed) {
            for (float cubeY = -my_ascii_cube.cube_width; cubeY < my_ascii_cube.cube_width;
                cubeY += my_ascii_cube.increment_speed) {
                calculateForSurface(cubeX, cubeY, -my_ascii_cube.cube_width, '@', &my_ascii_cube);
                calculateForSurface(my_ascii_cube.cube_width, cubeY, cubeX, '$', &my_ascii_cube);
                calculateForSurface(-my_ascii_cube.cube_width, cubeY, -cubeX, '~', & my_ascii_cube);
                calculateForSurface(-cubeX, cubeY, my_ascii_cube.cube_width, '#', &my_ascii_cube);
                calculateForSurface(cubeX, -my_ascii_cube.cube_width, -cubeY, ';', &my_ascii_cube);
                calculateForSurface(cubeX, my_ascii_cube.cube_width, cubeY, '+', &my_ascii_cube);
            }
        }
       
        
        system("cls");
        for (int k = 0; k < my_ascii_cube.width * my_ascii_cube.height; k++) {
            putchar(k % my_ascii_cube.width ? my_ascii_cube.buffer[k] : '\n');
        }

        my_ascii_cube.A += 0.05;
        my_ascii_cube.B += 0.05;
        my_ascii_cube.C += 0.01;
        Sleep(50);
    }

    return (0);
}


void Initializ(struct cube* object) {
    object->cube_width = 20;
    object->width = 160;
    object->height = 44;
    object->back_ASCII_Code = '.';
    object->dis_from_cam = 100;
    object->K1 = 40;
    object->increment_speed = 0.6;
}

float calculateX(int i, int j, int k, struct cube* object) {
    return j * sin(object->A) * sin(object->B) * cos(object->C) - k * cos(object->A) * sin(object->B) * cos(object->C) +
        j * cos(object->A) * sin(object->C) + k * sin(object->A) * sin(object->C) + i * cos(object->B) * cos(object->C);
}

float calculateY(int i, int j, int k, struct cube* object) {
    return j * cos(object->A) * cos(object->C) + k * sin(object->A) * cos(object->C) -
        j * sin(object->A) * sin(object->B) * sin(object->C) + k * cos(object->A) * sin(object->B) * sin(object->C) -
        i * cos(object->B) * sin(object->C);
}

float calculateZ(int i, int j, int k, struct cube* object) {
    return k * cos(object->A) * cos(object->B) - j * sin(object->A) * cos(object->B) + i * sin(object->B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch, struct cube* object) {
    object->x = calculateX(cubeX, cubeY, cubeZ, object);
    object->y = calculateY(cubeX, cubeY, cubeZ, object);
    object->z = calculateZ(cubeX, cubeY, cubeZ, object) + object->dis_from_cam;

    object->ooz = 1 / object->z;

    object->xp = (int)(object->width / 2 + object->horiz_offset + object->K1 * object->ooz * object->x * 2);
    object->yp = (int)(object->height / 2 + object->K1 * object->ooz * object->y);
    object->idx = object->xp + object->yp * object->width;
    if (object->idx >= 0 && object->idx < object->width * object->height) {
        if (object->ooz > object->zBuffer[object->idx]) {
            object->zBuffer[object->idx] = object->ooz;
            object->buffer[object->idx] = ch;
        }
    }
}