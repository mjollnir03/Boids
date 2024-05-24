#include <raylib.h>
#include "boid.h"


int main() {

    Color backgroundColor = BLACK; 
    Color boidColor = RAYWHITE;

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    int centerX = screenWidth / 2; 
    int centerY = screenHeight / 2;  
    
    Boid* boidptr = new Boid(centerX, centerY, { 0.0f, 0.0f }); 

    InitWindow(screenWidth, screenHeight, "Boids - By Ellmaer Ranjber");
    SetTargetFPS(60);
    HideCursor();

    while (WindowShouldClose() == false) {

        BeginDrawing();

        ClearBackground(backgroundColor);
        
        boidptr->DrawBoid();
         

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
