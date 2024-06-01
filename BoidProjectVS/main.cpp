#include <iostream>
#include <raylib.h> // Include Raylib library for graphics
#include <raymath.h>
#include <cstdlib> // Include standard library for various utilities
#include <ctime> // Include time library for random number generation based on time
#include "boid.h" // Include user-defined Boid class header file


#define NUM_BOIDS 350 // Define the number of boids in the simulation

int main() {
    // Define colors for background and boids
    Color backgroundColor = BLACK;
    Color boidColor = RAYWHITE;
    


    // Define screen dimensions
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Define parameters for boid behavior
    const int VISUAL_RANGE = 100; // Range within which boids interact with each other
    const int PROTECTED_RANGE = 20;
    const float AVOID_FACTOR = 0.05f; // Factor controlling avoidance behavior
    const float ALIGN_FACTOR = 0.02f; // Factor controlling alignment behavior
    const float COHESION_FACTOR = 0.002f; // Factor controlling cohesion behavior

    // Seed the random number generator with current time
    srand(static_cast<unsigned>(time(0)));

    // Array to store pointers to boids
    Boid* boids[NUM_BOIDS];

    //Variabels to use in the main for loops 
    int moveX = 0; //used in Seperation()
    int moveY = 0; //used in Seperation()
    float avgXVel = 0; //used in Alignment()
    float avgYVel = 0; //used in Alignment()
    float avgXPos = 0; //used in Cohesion()
    float avgYPos = 0; //used in Cohesion()
    int numNeighbors = 0; //used in Alignment() and Cohesion()

    //used in main loopt calculate the distance between two boids
    Vector2 pos1;
    Vector2 pos2;
    float distance; 

    // Initialize boids with random positions and velocities
    for (int i = 0; i < NUM_BOIDS; i++) {
        // Generate random initial positions
        int centerX = rand() % screenWidth;
        int centerY = rand() % screenHeight;

        // Generate random initial velocities within a range
        float velocityX = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (6.0f - 2.0f)));
        float velocityY = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (6.0f - 2.0f)));

        // Create a new boid with random initial position and velocity, and store its pointer
        boids[i] = new Boid(centerX, centerY, velocityX, velocityY);
    }

    // Initialize the window with specified dimensions and title
    InitWindow(screenWidth, screenHeight, "Boids - By Ellmaer Ranjber");
    SetTargetFPS(60); // Set target frames per second for rendering
    //HideCursor(); // Hide cursor during simulation (optional)

    // Main simulation loop
    while (WindowShouldClose() == false) {
        BeginDrawing(); // Begin rendering frame

        ClearBackground(backgroundColor); // Clear the screen with the background color

        // Loop through all boids in the simulation
        for (int i = 0; i < NUM_BOIDS; i++) {
            moveX = 0; //used in Seperation()
            moveY = 0; //used in Seperation()
            avgXVel = 0; //used in Alignment()
            avgYVel = 0; //used in Alignment()
            avgXPos = 0; //used in Cohesion()
            avgYPos = 0; //used in Cohesion()
            int numAlignmentNeighbors = 0; //used in Alignment()
            int numCohesionNeighbors = 0; //used in Cohesion()

            for (int j = 0; j < NUM_BOIDS; j++) {

                // Calculate the distance that the boid[i] is from the boid[j]
                pos1 = { static_cast<float>(boids[i]->GetXPos()), static_cast<float>(boids[i]->GetYPos()) };
                pos2 = { static_cast<float>(boids[j]->GetXPos()), static_cast<float>(boids[j]->GetYPos()) };
                distance = Vector2Distance(pos1, pos2);

                // Check if boid is in "Protected Range"
                if (distance < PROTECTED_RANGE) {
                    moveX += boids[i]->GetXPos() - boids[j]->GetXPos();
                    moveY += boids[i]->GetYPos() - boids[j]->GetYPos();
                }

                // Calculate for alignment
                if (distance < (VISUAL_RANGE - 50)) {
                    avgXVel += boids[j]->GetXVel();
                    avgYVel += boids[j]->GetYVel();
                    numAlignmentNeighbors++;
                }

                // Calculate for cohesion
                if (distance < (VISUAL_RANGE - 50)) {
                    avgXPos += boids[j]->GetXPos();
                    avgYPos += boids[j]->GetYPos();
                    numCohesionNeighbors++;
                }
            }
            

            if (numAlignmentNeighbors > 0) {
                avgXVel /= numAlignmentNeighbors;
                avgYVel /= numAlignmentNeighbors;
            }

            if (numCohesionNeighbors > 0) {
                avgXPos /= numCohesionNeighbors;
                avgYPos /= numCohesionNeighbors;
            }

            boids[i]->ApplySeparation(AVOID_FACTOR, moveX, moveY);
            //boids[i]->ApplyAlignment(ALIGN_FACTOR, avgXVel, avgYVel);
            //boids[i]->ApplyCohesion(COHESION_FACTOR, avgXPos, avgYPos);

            // Update position and velocity of the current boid
            boids[i]->Update();

            // Draw the current boid on the screen
            boids[i]->DrawBoid();
        }

        EndDrawing(); // End rendering frame
    }


    // Clean up memory by deleting dynamically allocated boids
    for (int i = 0; i < NUM_BOIDS; i++) {
        delete boids[i];
    }

    CloseWindow(); // Close the window
    return 0; // Return success status
}