#pragma once // Include guard to prevent multiple inclusion of this header file

#include <cmath> // Include math functions
#include "functions.h" // Include user-defined functions

// Constants defining boid properties
const float BOID_SIZE = 2.5f; // Size of the boid
const float SCREEN_MARGIN = BOID_SIZE * 25.0f; // Margin from screen edges
const Color BOID_COLOR = RAYWHITE; // Color of the boid
const Color PERIMETER_COLOR = GREEN; // Color of the perimeter
const float MAX_VELOCITY = 5.0f; // Maximum velocity of the boid

// Class definition for a boid
class Boid {
private:
    int xpos; // Current x-position of the boid
    int ypos; // Current y-position of the boid
    float xvel; // Current x-velocity of the boid
    float yvel; // Current y-velocity of the boid

public:
    // Constructor with parameters for initial position and velocity
    Boid(int x, int y, float xvel, float yvel);

    // Method to draw the boid
    void DrawBoid();

    // Method to update the boid's position and velocity
    void Update();

    // Method to apply separation behavior to avoid collisions with nearby boids
    void ApplySeparation(Boid* boids[], int numBoids, float avoidFactor, int visualRange);

    // Method to apply alignment behavior to match velocities with nearby boids
    void ApplyAlignment(Boid* boids[], int numBoids, float alignFactor, int visualRange);

    // Method to apply cohesion behavior to move towards the center of nearby boids
    void ApplyCohesion(Boid* boids[], int numBoids, float cohesionFactor, int visualRange);

    // Destructor (if needed)
    ~Boid();

    // Setters to update the boid's position and velocity
    void SetXPos(int x);
    void SetYPos(int y);
    void SetXVel(float xvel);
    void SetYVel(float yvel);

    // Getters to retrieve the boid's position and velocity
    int GetXPos() const;
    int GetYPos() const;
    float GetXVel() const;
    float GetYVel() const;
};

// Constructor implementation
Boid::Boid(int x, int y, float xvel, float yvel) {
    this->xpos = x;
    this->ypos = y;
    this->xvel = xvel;
    this->yvel = yvel;
}

// Method to update the boid's position and velocity
void Boid::Update() {
    // Constants defining turning behavior near boundaries and random steering
    const float boundaryTurnFactor = 1.9f; // Turning speed near boundaries
    const float randomTurnFactor = 0.5f;   // Random steering strength
    bool randomTurn = true; // Flag to enable random steering

    // Gradually adjust velocity when near boundaries
    if (this->xpos < SCREEN_MARGIN) {
        this->xvel += boundaryTurnFactor; // Turn right
        randomTurn = false; // Disable random steering
    }
    else if (this->xpos > GetScreenWidth() - SCREEN_MARGIN) {
        this->xvel -= boundaryTurnFactor; // Turn left
        randomTurn = false; // Disable random steering
    }
    if (this->ypos < SCREEN_MARGIN) {
        this->yvel += boundaryTurnFactor; // Turn down
        randomTurn = false; // Disable random steering
    }
    else if (this->ypos > GetScreenHeight() - SCREEN_MARGIN) {
        this->yvel -= boundaryTurnFactor; // Turn up
        randomTurn = false; // Disable random steering
    }

    // Randomly adjust velocity to steer left or right
    if (GetRandomValue(0, 100) < 50 && randomTurn) { // 50% chance to steer left
        this->xpos += randomTurnFactor; // Move left
    }
    else if (GetRandomValue(0, 100) > 50 && randomTurn) { // 50% chance to steer right
        this->ypos -= randomTurnFactor; // Move right
    }

    // Ensure velocities stay within bounds
    this->xvel = Clamp(this->xvel, -MAX_VELOCITY, MAX_VELOCITY);
    this->yvel = Clamp(this->yvel, -MAX_VELOCITY, MAX_VELOCITY);

    // Update position based on velocity
    this->xpos += this->xvel;
    this->ypos += this->yvel;
}

// Method to draw the boid
void Boid::DrawBoid() {
    // Draw the boid as a circle at its current position
    DrawCircle(this->xpos, this->ypos, BOID_SIZE, BOID_COLOR);
}

// Setter methods to update the boid's position and velocity
void Boid::SetXPos(int x) {
    this->xpos = x;
}

void Boid::SetYPos(int y) {
    this->ypos = y;
}

void Boid::SetXVel(float xvel) {
    this->xvel = xvel;
}

void Boid::SetYVel(float yvel) {
    this->yvel = yvel;
}

// Getter methods to retrieve the boid's position and velocity
int Boid::GetXPos() const {
    return this->xpos;
}

int Boid::GetYPos() const {
    return this->ypos;
}

float Boid::GetXVel() const {
    return this->xvel;
}

float Boid::GetYVel() const {
    return this->yvel;
}

// Method to apply separation behavior to avoid collisions with nearby boids
void Boid::ApplySeparation(Boid* boids[], int numBoids, float avoidFactor, int visualRange) {
    float moveX = 0;
    float moveY = 0;

    // Loop through all boids
    for (int i = 0; i < numBoids; i++) {
        if (boids[i] == this) continue; // Skip self

        // Calculate distance between this boid and the current boid
        float distance = sqrt(pow(this->xpos - boids[i]->GetXPos(), 2) + pow(this->ypos - boids[i]->GetYPos(), 2));

        // Check if the current boid is within the visual range
        if (distance < visualRange) {
            // Add avoidance vector to move away from the current boid
            moveX += this->xpos - boids[i]->GetXPos();
            moveY += this->ypos - boids[i]->GetYPos();
        }
    }

    // Update velocity based on avoidance vector
    this->xvel += moveX * avoidFactor;
    this->yvel += moveY * avoidFactor;
}

// Method to apply alignment behavior to match velocities with nearby boids
void Boid::ApplyAlignment(Boid* boids[], int numBoids, float alignFactor, int visualRange) {
    float avgXVel = 0;
    float avgYVel = 0;
    int numNeighbors = 0;

    // Loop through all boids
    for (int i = 0; i < numBoids; i++) {
        if (boids[i] == this) continue; // Skip self

        // Calculate distance between this boid and the current boid
        float distance = sqrt(pow(this->xpos - boids[i]->GetXPos(), 2) + pow(this->ypos - boids[i]->GetYPos(), 2));

        // Check if the current boid is within the visual range
        if (distance < visualRange) {
            // Add velocity of the current boid to calculate average velocity
            avgXVel += boids[i]->GetXVel();
            avgYVel += boids[i]->GetYVel();
            numNeighbors++;
        }
    }

    // If there are neighboring boids
    if (numNeighbors > 0) {
        // Calculate average velocity
        avgXVel /= numNeighbors;
        avgYVel /= numNeighbors;

        // Adjust velocity towards the average velocity
        this->xvel += (avgXVel - this->xvel) * alignFactor;
        this->yvel += (avgYVel - this->yvel) * alignFactor;
    }
}

// Method to apply cohesion behavior to move towards the center of nearby boids
void Boid::ApplyCohesion(Boid* boids[], int numBoids, float cohesionFactor, int visualRange) {
    float avgXPos = 0;
    float avgYPos = 0;
    int numNeighbors = 0;

    // Loop through all boids
    for (int i = 0; i < numBoids; i++) {
        if (boids[i] == this) continue; // Skip self

        // Calculate distance between this boid and the current boid
        float distance = sqrt(pow(this->xpos - boids[i]->GetXPos(), 2) + pow(this->ypos - boids[i]->GetYPos(), 2));

        // Check if the current boid is within the visual range
        if (distance < visualRange) {
            // Add position of the current boid to calculate average position
            avgXPos += boids[i]->GetXPos();
            avgYPos += boids[i]->GetYPos();
            numNeighbors++;
        }
    }

    // If there are neighboring boids
    if (numNeighbors > 0) {
        // Calculate average position
        avgXPos /= numNeighbors;
        avgYPos /= numNeighbors;

        // Calculate movement towards the average position
        float moveX = avgXPos - this->xpos;
        float moveY = avgYPos - this->ypos;

        // Adjust velocity towards the average position
        this->xvel += moveX * cohesionFactor;
        this->yvel += moveY * cohesionFactor;
    }
}

// Destructor (if needed)
Boid::~Boid() {
    // Destructor implementation (if needed)
}
