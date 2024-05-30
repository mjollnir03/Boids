#include <raylib.h> // Include Raylib library for graphics
#include <cstdlib> // Include standard library for various utilities
#include <ctime> // Include time library for random number generation based on time
#include "boid.h" // Include user-defined Boid class header file

#define NUM_BOIDS 250 // Define the number of boids in the simulation

int main() {
    // Define colors for background and boids
    Color backgroundColor = BLACK;
    Color boidColor = RAYWHITE;

    // Define screen dimensions
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Define parameters for boid behavior
    const int VISUAL_RANGE = 100; // Range within which boids interact with each other
    const float AVOID_FACTOR = 0.03f; // Factor controlling avoidance behavior
    const float ALIGN_FACTOR = 0.02f; // Factor controlling alignment behavior
    const float COHESION_FACTOR = 0.005f; // Factor controlling cohesion behavior

    // Seed the random number generator with current time
    srand(static_cast<unsigned>(time(0)));

    // Array to store pointers to boids
    Boid* boids[NUM_BOIDS];

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

            for (int j = 0; j < NUM_BOIDS; j++) { //this method will be faster, O(N^2) is better than previous method
                //calculate the distance that the boid[i] is from the boid[j]
                
                //accumalate necessary variables and etc.

                //check if boid is in "Visual Range"


            }

            // Old code to mark the special visual ranges per type of method call
            /*
            boids[i]->ApplySeparation(boids, NUM_BOIDS, AVOID_FACTOR, VISUAL_RANGE - 60);
            boids[i]->ApplyAlignment(boids, NUM_BOIDS, ALIGN_FACTOR, VISUAL_RANGE - 20);
            boids[i]->ApplyCohesion(boids, NUM_BOIDS, COHESION_FACTOR, VISUAL_RANGE + 20);
            */
            

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