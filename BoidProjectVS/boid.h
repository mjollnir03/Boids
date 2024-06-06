#pragma once // Include guard to prevent multiple inclusion of this header file

#include <cmath> // Include math functions
#include "functions.h" // Include user-defined functions


// Constants defining boid properties
const float BOID_SIZE = 2.5f; // Size of the boid
const Color BOID_COLOR = LIGHTGRAY; // Color of the boid
const float MAX_VELOCITY = 4.0f; // Maximum velocity of the boid

const static Vector2 DIRECTION_CHOICES[8] = {
    {0.3f, 0.0f}, {-0.3f, 0.0f}, {0.0f, -0.3f}, {0.0f, 0.3f},
    {-0.3f, -0.3f}, {0.3f, -0.3f}, {-0.3f, 0.3f}, {0.3f, 0.3f}
};

// Class definition for a boid
class Boid {
private:
    int xpos; // Current x-position of the boid
    int ypos; // Current y-position of the boid
    float xvel; // Current x-velocity of the boid
    float yvel; // Current y-velocity of the boid

    Vector2 GetDirection(); // Returns x and y values to be applied to xvel and yvel
    void ApplyVelocity(); // Updates position based on velocity, ensuring it stays within bounds
    bool CheckBoundaryCollision(); // Checks and handles boundary collisions

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

// Method to apply the current velocity to update the position
void Boid::ApplyVelocity() {
    // Ensure velocities stay within bounds
    this->xvel = Clamp(this->xvel, -MAX_VELOCITY, MAX_VELOCITY);
    this->yvel = Clamp(this->yvel, -MAX_VELOCITY, MAX_VELOCITY);

    // Update position based on velocity
    this->xpos += static_cast<int>(this->xvel);
    this->ypos += static_cast<int>(this->yvel);
}

// Method to determine the direction of movement based on random chance
Vector2 Boid::GetDirection() {
    /*
    LEGEND:
    DIRECTION_CHOICES[0] = go right
    DIRECTION_CHOICES[1] = go left
    DIRECTION_CHOICES[2] = go up
    DIRECTION_CHOICES[3] = go down
    DIRECTION_CHOICES[4] = go up-left
    DIRECTION_CHOICES[5] = go up-right
    DIRECTION_CHOICES[6] = go down-left
    DIRECTION_CHOICES[7] = go down-right
    */
    Vector2 direction = { 0.0f, 0.0f };

    // Create a random device and random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a distribution for a 50% chance
    std::uniform_int_distribution<> dis(0, 1);
    int randomChance = dis(gen);

    if (randomChance == 1) {
        // Define the distribution range for indices (0 to 7)
        std::uniform_int_distribution<> directionDis(0, 7);
        // Choose a random index from 0 to 7
        int randomIndex = directionDis(gen);
        // Set the direction to the chosen value from DIRECTION_CHOICES
        direction = DIRECTION_CHOICES[randomIndex];
    }

    return direction;
}

// Method to check and handle collisions with the boundaries of the screen
bool Boid::CheckBoundaryCollision() {
    // Constants defining turning behavior near boundaries
    const float boundaryTurnFactor = 0.2f; // Turning speed near boundaries
    bool boundaryHit = false;

    // Gradually adjust velocity when near boundaries
    if (this->xpos < 50) {
        this->xvel += boundaryTurnFactor; // Turn right
        this->yvel += 0.1f;
        boundaryHit = true;
    }
    else if (this->xpos > GetScreenWidth() - 50) {
        this->xvel -= boundaryTurnFactor; // Turn left
        this->yvel += 0.1f;
        boundaryHit = true;
    }
    if (this->ypos < 50) {
        this->yvel += boundaryTurnFactor; // Turn down
        boundaryHit = true;
    }
    else if (this->ypos > GetScreenHeight() - 50) {
        this->yvel -= boundaryTurnFactor; // Turn up
        boundaryHit = true;
    }

    if (boundaryHit) {
        this->ApplyVelocity();
    }

    return boundaryHit;
}

// Method to update the boid's position and velocity
void Boid::Update() {
    // Check boundary collision
    if (this->CheckBoundaryCollision()) {
        return;
    }

    // Below is what caused the generic directions for the boids
    // instead I will implement a grid that will cause the boids
    // to go in certain directions
    Vector2 newVelocities = this->GetDirection();

    this->xvel += newVelocities.y;
    this->yvel += newVelocities.x;

    // Accelerate velocity by 15% if within the range of -1 and 1
    if (this->xvel > -1.0f && this->xvel < 1.0f) {
        this->xvel *= 1.15f;
    }
    if (this->yvel > -1.0f && this->yvel < 1.0f) {
        this->yvel *= 1.15f;
    }

    this->ApplyVelocity();
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
