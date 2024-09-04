#include "/opt/homebrew/include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 1000
#define MAX_CYCLES 25
//int MAX_CYCLES = 1;

// Mandelbrot set equation: z = z^2 + c
typedef struct {
    float re,im;
} CMPLX;

CMPLX sqr(CMPLX x){
    CMPLX temp = (CMPLX){x.re * x.re - x.im * x.im , 2 * x.re * x.im};
    return temp;
}

int get_cycles(CMPLX c){
    int cycles = 0;
    CMPLX z = {0,0};
    for (int i = 0; i < MAX_CYCLES ; i++){
        CMPLX temp = sqr(z);
        z.re = temp.re + c.re;
        z.im = temp.im + c.im;

        if ( fabsf(z.re * z.re + z.im * z.im) > 16 ){
            break;
        }
        cycles++;
    }
    return cycles;
}

Color get_color(CMPLX c){
    int temp = get_cycles(c);
    return (Color){10 * temp % 255, 2 * temp % 255, 4 * temp % 255,255 - (temp/MAX_CYCLES) * 255};
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Mandelbrot");

    CMPLX z = {0,0};
    CMPLX c;

    int pixels[WIDTH][HEIGHT];
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            c.re = (float)i*4/WIDTH - 2;
            c.im = (float)j*4/HEIGHT - 2;
            pixels[i][j] = get_cycles(c);
        }
    }
    double dt = 0;
    int r = 70;
    int g = 20;
    int b = 10;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        dt = GetFrameTime();
        for (int i = 0; i < WIDTH; i++){
            for(int j = 0; j < HEIGHT; j++){
                DrawPixel(i,j,(Color){(10 * pixels[i][j] )% 255,2 *  pixels[i][j] % 255,4 * pixels[i][j] % 255,255 - (pixels[i][j])/MAX_CYCLES * 255});
            }
        }
        DrawFPS(10, 10);
        EndDrawing();
        ClearBackground(BLACK);
    }

    CloseWindow();

    return 0;
}
