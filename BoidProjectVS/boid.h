#pragma once // Include guard to prevent multiple inclusion of this header file

#include <cmath> // Include math functions
#include "functions.h" // Include user-defined functions
#include <iostream>

// Constants defining boid properties
const float BOID_SIZE = 3.5f; // Size of the boid
const Color BOID_COLOR = RAYWHITE; // Color of the boid
const float MAX_VELOCITY = 5.0f; // Maximum velocity of the boid
const static Vector2 GRIDKEY[4][4] = {
    { {0.2f, 0.0f}, {-0.0f, 0.2f}, {0.0f, 0.2f}, {-0.2f, 0.0f} },
    { {0.2f, 0.2f}, {0.2f, 0.0f}, {0.2f, 0.2f}, {-0.2f, 0.2f} },
    { {0.2f, -0.2f}, {-0.2f, -0.2f}, {0.0f, 0.2f}, {0.0f, 0.0f} },
    { {0.2f, 0.0f}, {0.0f, -0.2f}, {-0.2f, 0.0f}, {-0.2f, 0.0f} }
};

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
    // Ensure velocities stay within bounds
    this->xvel = Clamp(this->xvel, -MAX_VELOCITY, MAX_VELOCITY);
    this->yvel = Clamp(this->yvel, -MAX_VELOCITY, MAX_VELOCITY);

    // Update position based on velocity
    this->xpos += static_cast<int>(this->xvel);
    this->ypos += static_cast<int>(this->yvel);

}

Vector2 Boid::GetDirection() {
    int XCoordinate = 0; //480
    int YCoordinate = 0; //270
    Vector2 direction = { 0.0f, 0.0f };

    for (int y = 0; y <= 4; y++) { 

        if (this->GetYPos() > y * 270 && this->GetYPos() < (y + 1) * 270) {
            YCoordinate = y;
            for (int x = 0; x <= 4; x++) {
                if (this->GetXPos() > x * 480 && this->GetXPos() < (x + 1) * 480) {
                    XCoordinate = x;
                    break;
                }
                
            }
        }
    }

    //std::cout << "Current X: " << XCoordinate << std::endl << "Current Y: " << YCoordinate << std::endl;
    direction = GRIDKEY[XCoordinate][YCoordinate];


    return direction;
}

bool Boid::CheckBoundaryCollosion() {
    // Constants defining turning behavior near boundaries and random steering
    const float boundaryTurnFactor = 1.9f; // Turning speed near boundaries
    bool boundryHit = false; 

    // Gradually adjust velocity when near boundaries
    if (this->xpos < 0) {
        this->xvel += boundaryTurnFactor; // Turn right
        boundryHit = true;
    }
    else if (this->xpos > GetScreenWidth()) {
        this->xvel -= boundaryTurnFactor; // Turn left
        boundryHit = true;
    }
    if (this->ypos < 0) {
        this->yvel += boundaryTurnFactor; // Turn down
        boundryHit = true;
    }
    else if (this->ypos > GetScreenHeight()) {
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

    //below is what caused the generic directions for the boids
    //instead I will implement a grid that will cause the boids
    //to go in certain directions
    Vector2 newVelocities = this->GetDirection();
    
    //set new xvel and yvel
    //this->SetXVel(newVelocities.x);
    //this->SetYVel(newVelocities.y);
    this->xvel += newVelocities.y;
    this->yvel += newVelocities.x;


    this->ApplyVelocity();
    



}


// Method to draw the boid
void Boid::DrawBoid() {
    // Draw the boid as a circle at its current position
    DrawCircle(this->xpos, this->ypos, BOID_SIZE, BOID_COLOR);
    //DrawGrid();
    
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