#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// These two functions are written in JS, exported and used in C
void renderCanvas(int dataLength, int singleCircleSize);
int generateRandom(int max);

// Number of circles
#define NUM_CIRCLES 100

// Circle Data Structure
struct Circle
{
    int x; // x-axis coordinate
    int y; // y-axis coordinate
    int r; // radius
    int cr; // RGB - Red color
    int cg; // RGB - Green color
    int cb; // RGB - Blue color
};

// Circle struct for animation
struct CircleAnimationData
{
    int x; // x-axis coordinate
    int y; // y-axis coordinate
    int r; // radius
    int xv; // x-axis velocity
    int yv; // y-axis velocity
    int xd; // x-axis direction
    int yd; // y-axis direction
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

int getRand(max)
{
    return generateRandom(max);
}
/* Init circle data and start render - JS */
int main()
{
    // create circles
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        // get radius
        int radius = getRand(50);

        // Coordinates
        int x = getRand(1000) + radius;
        int y = getRand(1000) + radius;

        // Fill animation
        animationData[i].x = x;
        animationData[i].y = y;
        animationData[i].r = radius;
        animationData[i].xv = getRand(10);
        animationData[i].yv = getRand(10);
        animationData[i].xd = 1;
        animationData[i].yd = 1;

        // Fill circle struct
        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radius;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
    }
    renderCanvas(NUM_CIRCLES * 6, 6);
}

struct Circle *getCircles(int canvasWidth, int canvasHeight)
{
    // Update the circle animation before sending
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        // check collision RIGHT
        if ((animationData[i].x + animationData[i].r) >= canvasWidth)
        {
            animationData[i].xd = 0;
        }
        // check collision LEFT
        if ((animationData[i].x - animationData[i].r) <= 0)
        {
            animationData[i].xd = 1;
        }
        // check collision TOP
        if ((animationData[i].y - animationData[i].r) <= 0)
        {
            animationData[i].yd = 1;
        }
        // check collision BOTTOM
        if ((animationData[i].y + animationData[i].r) >= canvasHeight)
        {
            animationData[i].yd = 0;
        }

        // Move circle direction
        if (animationData[i].xd == 1)
        {
            animationData[i].x += animationData[i].xv;
        }
        else
        {
            animationData[i].x -= animationData[i].xv;
        }
        if (animationData[i].yd == 1)
        {
            animationData[i].y += animationData[i].yv;
        }
        else
        {
            animationData[i].y -= animationData[i].yv;
        }

        // Update matching circle data with animation data
        circles[i].x = animationData[i].x;
        circles[i].y = animationData[i].y;
    }
    return circles;
}