#pragma once

#include <cmath>
#include <algorithm>
#include "functions.h"

const float BOID_SIZE = 10.0f;
const float PERIMETER_RADIUS = BOID_SIZE * 10.0f;
const Color BOID_COLOR = RAYWHITE;
const Color PERIMETER_COLOR = GREEN;
const float MAX_VELOCITY = 6.0f;
const float MIN_VELOCITY = 2.0f;

class Boid {
private:
    int xpos; // current xpos of the boid
    int ypos; // current ypos of the boid
    float xvel; // current xvel of the boid
    float yvel; // current yvel of the boid

public:
    Boid(int x, int y, float xvel, float yvel);
    void DrawBoid();
    void Update();
    bool IsWithinPerimeter(const Boid& other) const;
    ~Boid();
};

Boid::Boid(int x, int y, float xvel, float yvel) {
    this->xpos = x;
    this->ypos = y;
    this->xvel = xvel;
    this->yvel = yvel;
}

void Boid::Update() {
    const float turnFactor = 1.0f; // Adjust this value to control the turning speed

    // Gradually adjust velocity when near boundaries
    if (this->xpos < PERIMETER_RADIUS) {
        this->xvel += turnFactor;
    }
    else if (this->xpos > GetScreenWidth() - PERIMETER_RADIUS) {
        this->xvel -= turnFactor;
    }
    if (this->ypos < PERIMETER_RADIUS) {
        this->yvel += turnFactor;
    }
    else if (this->ypos > GetScreenHeight() - PERIMETER_RADIUS) {
        this->yvel -= turnFactor;
    }

    // Ensure velocities stay within bounds
    this->xvel = Clamp(this->xvel, -MAX_VELOCITY, MAX_VELOCITY); 
    this->yvel = Clamp(this->yvel, -MAX_VELOCITY, MAX_VELOCITY);

    // Update position based on velocity
    this->xpos += this->xvel;
    this->ypos += this->yvel;
}


bool Boid::IsWithinPerimeter(const Boid& other) const {
    // Calculate the distance between the centers of the two boids
    float dx = this->xpos - other.xpos;
    float dy = this->ypos - other.ypos;
    float distance = sqrt(dx * dx + dy * dy);

    // Check if the distance is less than or equal to the sum of the perimeter radii
    return distance <= (PERIMETER_RADIUS);
}

void Boid::DrawBoid() {
    // Draw the boid
    DrawCircle(this->xpos, this->ypos, BOID_SIZE, BOID_COLOR);
    // Draw the perimeter
    DrawCircleLines(this->xpos, this->ypos, PERIMETER_RADIUS, PERIMETER_COLOR); 
}

Boid::~Boid() {
    // Destructor implementation (if needed)
}
