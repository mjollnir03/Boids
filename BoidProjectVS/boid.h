#pragma once // Include guard to prevent multiple inclusion of this header file

#include <cmath> // Include math functions
#include "functions.h" // Include user-defined functions

// Constants defining boid properties
const float BOID_SIZE = 2.5f; // Size of the boid
const float SCREEN_MARGIN = BOID_SIZE * 10.0f; // Margin from screen edges
const Color BOID_COLOR = RAYWHITE; // Color of the boid
const float MAX_VELOCITY = 6.0f; // Maximum velocity of the boid

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
    void ApplySeparation(float avoidFactor, int moveX, int moveY);

    // Method to apply alignment behavior to match velocities with nearby boids
    void ApplyAlignment(float alignFactor, float avgXVel, float avgYVel);

    // Method to apply cohesion behavior to move towards the center of nearby boids
    void ApplyCohesion(float cohesionFactor, float avgXPos, float avgYPos);

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
        this->xvel += randomTurnFactor; // Move left
    }
    else if (GetRandomValue(0, 100) > 50 && randomTurn) { // 50% chance to steer right
        this->yvel += randomTurnFactor; // Move right
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
void Boid::ApplySeparation(float avoidFactor, int moveX, int moveY) {
    this->xvel += moveX * avoidFactor;
    this->yvel += moveY * avoidFactor;
}

// Method to apply alignment behavior to match velocities with nearby boids
void Boid::ApplyAlignment(float alignFactor, float avgXVel, float avgYVel) {
    this->xvel += (avgXVel - this->xvel) * alignFactor;
    this->yvel += (avgYVel - this->yvel) * alignFactor;
}

// Method to apply cohesion behavior to move towards the center of nearby boids
void Boid::ApplyCohesion(float cohesionFactor, float avgXPos, float avgYPos) {
    this->xvel += (avgXPos - this->xpos) * cohesionFactor;
    this->yvel += (avgYPos - this->ypos) * cohesionFactor;
}

// Destructor (if needed)
Boid::~Boid() {
    // Destructor implementation (if needed)
}