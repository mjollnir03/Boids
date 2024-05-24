#pragma once

const float BOID_SIZE = 10.0f;
const Color BOID_COLOR = RAYWHITE;

class Boid {
private:
	int xpos;
	int ypos;
	Vector2 velocity; 

public: 
	Boid(int x, int y, Vector2 velocity);
	void DrawBoid();
	~Boid();

};

Boid::Boid(int x, int y, Vector2 velocity) {
	this->xpos = x;
	this->ypos = y;
	this->velocity = velocity;
}

void Boid::DrawBoid() {
	DrawCircle(this->xpos, this->ypos, BOID_SIZE, BOID_COLOR );
}

Boid::~Boid() {

}