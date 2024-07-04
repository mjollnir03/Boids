# Boids

## About
- This project implements a simulation of Boids, an artificial life program originally developed by Craig Reynolds in 1986, that simulates the flocking behavior of birds. The simulation models the collective behavior of simple agents (boids) that follow three primary rules: separation, alignment, and cohesion. Each boid adjusts its position and velocity based on its nearby neighbors, resulting in emergent flocking behavior. The simulation is developed in C++ using the Raylib library for rendering.

## Demos
- The boid simulation initializes with a specified number of boids, each having random initial positions and velocities. The boids move within a defined screen area, avoiding the edges, and interact with each other according to the rules of separation, alignment, and cohesion. The visual representation shows the boids as small circles that move fluidly, mimicking the natural flocking of birds. There are some issues, but nevertheless, I enjoyed this project and what I was able to achieve.

- Below are video snippets showcasing the different rules when applied to the agents. For the video snippets, the agent size has been changed from 2.5 -> 4.5 and the protected range has been changed from 10 -> 20. These changes have been reverted and only had been done so the boids could be more visually apparent.

- The following snippet is of the Boids with no rules applied whatsoever:
  
  <img src="https://github.com/mjollnir03/Boids/assets/98365394/d263f626-32f2-411d-b1af-ebac33cd67bf" width="90%"/>
  
- This is when only Separation is applied:
  
  <img src="https://github.com/mjollnir03/Boids/assets/98365394/389821e1-551b-4eef-ace1-76aafcb1dba7" width="90%"/>
  
- This is when both Separation and Alignment are applied:
  
  <img src="https://github.com/mjollnir03/Boids/assets/98365394/a33d2387-ec42-4118-af1a-3525a3546525" width="90%"/>
  
- Lastly, this is with Separation, Alignment, and Cohesion all applied:
  
  <img src="https://github.com/mjollnir03/Boids/assets/98365394/8ad8994c-35fe-4232-ab80-e1aab08757cd" width="90%"/>
  
- Previous Version:
  
  - The video below was my first version of this Boid project. As you can see, it is a lot more rigid and unrealistic than the current version.
    
    <img src="https://github.com/mjollnir03/Boids/assets/98365394/7c01a83d-f3b2-44f7-b76f-0cce44ea0444" width="90%"/> 

## References
- Craig Reynolds' original paper on Boids: "Flocks, Herds, and Schools: A Distributed Behavioral Model" (1987)
- Raylib library for rendering: [Raylib](https://www.raylib.com/)
- V. Hunter Adams Boids-Algorithm Pseudocode: [Boids-algorithm](https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html)

## Conclusion
- This Boids project has been an exciting journey into the world of artificial life and emergent behavior. Implementing the flocking behavior of birds through simple rules has provided valuable insights into how complex patterns can arise from basic interactions. While there are still improvements to be made, such as optimizing performance and addressing edge cases, the current version effectively demonstrates the core principles of separation, alignment, and cohesion.

- Future enhancements could include adding obstacles for the boids to navigate around, experimenting with different rule parameters to observe varied flocking behaviors, and perhaps integrating more advanced rendering techniques for a visually richer experience.

- Overall, this project has been both educational and enjoyable. I look forward to continuing to refine and expand on this work, and I encourage others to explore the fascinating world of Boids.

### Executable Directory (Windows Only)
- For those interested in running the simulation on a Windows system, the executable can be found in the following directory:
  
**ExecutableFilesDirectory/**

└── `BoidProjectVS.exe`

└── `raylib.dll`

└── `BoidProjectVS.pdb`


Ensure you navigate through the above directory path to locate and run the `BoidProjectVS.exe` file.
