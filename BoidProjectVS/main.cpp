#include <raylib.h>
#include "boid.h"


int main() {

    Color backgroundColor = BLACK; 
    Color boidColor = RAYWHITE;

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    int centerX = screenWidth / 2; 
    int centerY = screenHeight / 2;  
    
    Boid* boidptr = new Boid(centerX, centerY, 6.0f, 2.0f); 
    Boid* boidptr2 = new Boid(centerX, centerY, -6.0f, -2.0f);

    InitWindow(screenWidth, screenHeight, "Boids - By Ellmaer Ranjber");
    SetTargetFPS(60);
    //HideCursor();

    while (WindowShouldClose() == false) {

        BeginDrawing();
        
        boidptr->Update();
        boidptr2->Update();

        ClearBackground(backgroundColor);
        
        boidptr->DrawBoid();
        boidptr2->DrawBoid();

        // Check for perimeter collision
        if (boidptr->IsWithinPerimeter(*boidptr2)) {
            DrawText("Collision Detected!", screenWidth / 2 - MeasureText("Collision Detected!", 20) / 2, screenHeight / 2, 20, RED);
        }
         

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
