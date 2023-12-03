#include <iostream>
#include <unistd.h> // for sleep function

using namespace std;

int main() {
    const int width = 50; // Width of the animation frame
    int pos = 0; // Starting position of the character
    bool direction = true; // True for right, false for left

    while (true) {
        system("clear"); // Clear the terminal screen

        for (int i = 0; i < pos; ++i) {
            cout << " "; // Print spaces before the character
        }

        cout << "*"; // Print the character
        cout <<flush;

        if (pos == width) {
            direction = false; // Change direction to left
        } else if (pos == 0) {
            direction = true; // Change direction to right
        }

        pos += direction ? 1 : -1; // Move the character

        usleep(50000); // Sleep for 50 milliseconds
    }

    return 0;
}
