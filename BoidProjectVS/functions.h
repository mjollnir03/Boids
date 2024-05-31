#pragma once // Include guard to prevent multiple inclusion of this header file

// Template function to clamp a value between a minimum and maximum value
template<typename T>
T Clamp(T value, T min, T max) {
    // Check if the value is less than the minimum
    if (value < min) {
        return min; // Return the minimum value
    }
    // Check if the value is greater than the maximum
    else if (value > max) {
        return max; // Return the maximum value
    }
    else {
        return value; // Return the original value if within the range
    }
}


void DrawGrid() { // temporary function just to help visualize the point of the grid system I am creating
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            int centerX = x * 480;
            int centerY = y * 270;
            DrawCircle(centerX, centerY, 15, GREEN);
        }
    }

}