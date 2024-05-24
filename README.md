# Boids

### About
This project implements a simulation of Boids, an artificial life program, originally developed by Craig Reynolds in 1986, that simulates the flocking behavior of birds. The simulation models the collective behavior of simple agents (boids) that follow three primary rules: separation, alignment, and cohesion. Each boid adjusts its position and velocity based on its nearby neighbors, resulting in emergent flocking behavior. The simulation is developed in C++ using the Raylib library for rendering.

### Demo
The boid simulation initializes with a specified number of boids, each having random initial positions and velocities. The boids move within a defined screen area, avoiding the edges, and interact with each other according to the rules of separation, alignment, and cohesion. The visual representation shows the boids as small circles that move fluidly, mimicking the natural flocking of birds. There are some issues, but never the less I enjoyed this project and what I was able to achieve.

![Boids Simulation](https://github.com/mjollnir03/Boids/assets/98365394/49882548-0704-4442-8e99-c510bc7050c4)


### References/Sources Used
- Craig Reynolds' original paper on Boids: "Flocks, Herds, and Schools: A Distributed Behavioral Model" (1987)
- Raylib library for rendering: [Raylib](https://www.raylib.com/)
- V. Hunter Adams Boids-Algorithm Pseudocode [Boids-algorithm](https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html)

### Conclusion
The Boids project effectively demonstrates the principles of emergent behavior using simple rules for individual agents. By leveraging modern graphics libraries and potential GPU acceleration, the simulation achieves smooth and realistic flocking behavior. This project serves as a foundation for further exploration into artificial life simulations and parallel computing techniques. The use of Raylib for rendering makes the project accessible and easy to modify for additional features and improvements.
I have included the executable file in the repository so that you can run the demo without having to compile the project, just make sure that you download the `Executable` folder and inside will be the .exe and a .dll for the raylib library. Simple just click on the .exe file and it should run, and make sure that the .dll is in the same directory as the .exe file.
