#include <iostream> // Include standard input/output stream library
#include <raylib.h> // Include Raylib library for graphics
#include <raymath.h> // Include Raylib math library
#include <cstdlib> // Include standard library for various utilities
#include <random> // Include the random library
#include "boid.h" // Include user-defined Boid class header file

#define NUM_BOIDS 500 // Define the number of boids in the simulation

// Function prototypes
void InitializeBoids(Boid* boids[], int screenWidth, int screenHeight);
void UpdateBoids(Boid* boids[], int screenWidth, int screenHeight);
void PlayRaylibLogoAnimation(int screenWidth, int screenHeight); // Taken from the raylib examples 

int main() {
    // Define colors for background and boids
    Color backgroundColor = BLACK;

    // Define screen dimensions
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Seed the random number generator with current time
    srand(static_cast<unsigned>(time(0)));

    // Array to store pointers to boids
    Boid* boids[NUM_BOIDS];

    // Initialize boids with random positions and velocities
    InitializeBoids(boids, screenWidth, screenHeight);

    // Initialize the window with specified dimensions and title
    InitWindow(screenWidth, screenHeight, "Boids - By Ellmaer Ranjber");
    SetTargetFPS(60); // Set target frames per second for rendering
    // HideCursor(); // Hide cursor during simulation (optional)

    // Play the Raylib screen intro
    //PlayRaylibLogoAnimation(screenWidth, screenHeight);

    // Main simulation loop
    while (WindowShouldClose() == false) {
        BeginDrawing(); // Begin rendering frame
        ClearBackground(backgroundColor); // Clear the screen with the background color

        // Update and draw boids
        UpdateBoids(boids, screenWidth, screenHeight);

        EndDrawing(); // End rendering frame
    }

    // Clean up memory by deleting dynamically allocated boids
    for (int i = 0; i < NUM_BOIDS; i++) {
        delete boids[i];
    }

    CloseWindow(); // Close the window
    return 0; // Return success status
}

// Function to initialize boids with random positions and velocities
void InitializeBoids(Boid* boids[], int screenWidth, int screenHeight) {
    for (int i = 0; i < NUM_BOIDS; i++) {
        // Generate random initial positions
        int centerX = rand() % screenWidth;
        int centerY = rand() % screenHeight;

        // Generate random initial velocities within a range of -5 to 5
        float velocityX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10.0f) - 5.0f;
        float velocityY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10.0f) - 5.0f;

        // Create a new boid with random initial position and velocity, and store its pointer
        boids[i] = new Boid(centerX, centerY, velocityX, velocityY);
    }
}

// Function to update boids' positions, velocities, and draw them
void UpdateBoids(Boid* boids[], int screenWidth, int screenHeight) {
    // Define parameters for boid behavior
    const int VISUAL_RANGE = 50; // Range within which boids interact with each other
    const int PROTECTED_RANGE = 10; // Range within which boids avoid each other
    const float AVOID_FACTOR = 0.05f; // Factor controlling avoidance behavior
    const float ALIGN_FACTOR = 0.05f; // Factor controlling alignment behavior
    const float COHESION_FACTOR = 0.0005f; // Factor controlling cohesion behavior

    // Variables for separation, alignment, and cohesion calculations
    int moveX = 0, moveY = 0;
    float avgXVel = 0, avgYVel = 0;
    float avgXPos = 0, avgYPos = 0;
    int numNeighbors = 0;

    // Variables to calculate the distance between two boids
    Vector2 pos1, pos2;
    float distance;

    for (int i = 0; i < NUM_BOIDS; i++) {
        // Reset movement and averaging variables for the current boid
        moveX = 0; moveY = 0;
        avgXVel = 0; avgYVel = 0;
        avgXPos = 0; avgYPos = 0;
        numNeighbors = 0;

        for (int j = 0; j < NUM_BOIDS; j++) {
            // Calculate the distance between boid[i] and boid[j]
            pos1 = { static_cast<float>(boids[i]->GetXPos()), static_cast<float>(boids[i]->GetYPos()) };
            pos2 = { static_cast<float>(boids[j]->GetXPos()), static_cast<float>(boids[j]->GetYPos()) };
            distance = Vector2Distance(pos1, pos2);

            // Check if boid[j] is in the protected range of boid[i]
            if (distance < PROTECTED_RANGE) {
                moveX += boids[i]->GetXPos() - boids[j]->GetXPos();
                moveY += boids[i]->GetYPos() - boids[j]->GetYPos();
            }

            // Check if boid[j] is in the visual range of boid[i]
            if (distance < VISUAL_RANGE) {
                avgXVel += boids[j]->GetXVel();
                avgYVel += boids[j]->GetYVel();
                avgXPos += boids[j]->GetXPos();
                avgYPos += boids[j]->GetYPos();
                numNeighbors++;
            }
        }

        // Calculate average velocities and positions for alignment and cohesion
        if (numNeighbors > 0) {
            avgXVel /= numNeighbors;
            avgYVel /= numNeighbors;
            avgXPos /= numNeighbors;
            avgYPos /= numNeighbors;
        }

        // Apply boid behaviors
        boids[i]->ApplySeparation(AVOID_FACTOR, moveX, moveY);
        boids[i]->ApplyAlignment(ALIGN_FACTOR, avgXVel, avgYVel);
        boids[i]->ApplyCohesion(COHESION_FACTOR, avgXPos, avgYPos);

        // Update position and velocity of the current boid
        boids[i]->Update();

        // Draw the current boid on the screen
        boids[i]->DrawBoid();
    }
}

void PlayRaylibLogoAnimation(int screenWidth, int screenHeight)
{
    // Local Variables
    int logoPositionX = screenWidth / 2 - 128;
    int logoPositionY = screenHeight / 2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0; // Tracking animation states (State Machine)
    float alpha = 1.0f; // Useful for fading
    float fadeOutAlpha = 0.0f; // Fade out alpha value

    
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (state == 0) // State 0: Small box blinking
        {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0; // Reset counter... will be used later...
            }
        }
        else if (state == 1) // State 1: Top and left bars growing
        {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2) // State 2: Bottom and right bars growing
        {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;

            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3) // State 3: Letters appearing (one by one)
        {
            framesCounter++;

            if (framesCounter / 12) // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }

            if (lettersCount >= 10) // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        else if (state == 4) // State 4: Fade to black
        {
            fadeOutAlpha += 0.01f;

            if (fadeOutAlpha >= 1.0f)
            {
                fadeOutAlpha = 1.0f;
            }
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (state == 0)
        {
            if ((framesCounter / 15) % 2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
        }
        else if (state == 1)
        {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
        }
        else if (state == 2)
        {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

            DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
            DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
        }
        else if (state == 3)
        {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
            DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

            DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
            DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

            DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));

            DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, alpha));
        }
        else if (state == 4)
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fadeOutAlpha));
        }

        EndDrawing();

        if (state == 4 && fadeOutAlpha >= 1.0f) // Exit the loop when the screen is completely black
        {
            break;
        }
    }

    CloseWindow(); // Close window and OpenGL context
}
