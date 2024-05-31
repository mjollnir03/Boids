#pragma once // Include guard to prevent multiple inclusion of this header file

#include <cmath> // Include math functions
#include "functions.h" // Include user-defined functions

// Constants defining boid properties
const float BOID_SIZE = 3.5f; // Size of the boid
const Color BOID_COLOR = RAYWHITE; // Color of the boid
const float MAX_VELOCITY = 5.0f; // Maximum velocity of the boid

// Class definition for a boid
class Boid {
private:
    int xpos; // Current x-position of the boid
    int ypos; // Current y-position of the boid
    float xvel; // Current x-velocity of the boid
    float yvel; // Current y-velocity of the boid
    Vector2 GetDirection(); // Returns x and y values to be applied to xvel and yvel
    void ApplyVelocity();
    bool CheckBoundaryCollosion();

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

void Boid::ApplyVelocity() {
    //add some acceleration to the velocities 
    this->xvel += this->xvel * 0.01f;
    this->yvel += this->yvel * 0.01f;

    // Ensure velocities stay within bounds
    this->xvel = Clamp(this->xvel, -MAX_VELOCITY, MAX_VELOCITY);
    this->yvel = Clamp(this->yvel, -MAX_VELOCITY, MAX_VELOCITY);

    // Update position based on velocity
    this->xpos += this->xvel;
    this->ypos += this->yvel;

}

Vector2 Boid::GetDirection() {

    return { 3.0, 3.0 };
}

bool Boid::CheckBoundaryCollosion() {
    // Constants defining turning behavior near boundaries and random steering
    const float boundaryTurnFactor = 0.3f; // Turning speed near boundaries
    bool boundryHit = false; 

    // Gradually adjust velocity when near boundaries
    if (this->xpos < 20) {
        this->xvel += boundaryTurnFactor; // Turn right
        boundryHit = true;
    }
    else if (this->xpos > GetScreenWidth() - 20) {
        this->xvel -= boundaryTurnFactor; // Turn left
        boundryHit = true;
    }
    if (this->ypos < 20) {
        this->yvel += boundaryTurnFactor; // Turn down
        boundryHit = true;
    }
    else if (this->ypos > GetScreenHeight() - 20) {
        this->yvel -= boundaryTurnFactor; // Turn up
        boundryHit = true;
    }

    if (boundryHit) {
        this->ApplyVelocity();
    }

    return boundryHit;
}


// WORK IN PROGRESS
void Boid::Update() { //follow grid idea

    //variables


    //check boundry collosion
    if (this->CheckBoundaryCollosion()) { return; } //base case

    this->ApplyVelocity();
    



}


// Method to draw the boid
void Boid::DrawBoid() {
    // Draw the boid as a circle at its current position
    DrawCircle(this->xpos, this->ypos, BOID_SIZE, BOID_COLOR);
    DrawGrid();
    
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