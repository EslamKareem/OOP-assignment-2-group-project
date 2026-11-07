#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <iomanip>

// Screen / Output device for the Vole (Brookshear) machine.
// Holds the last byte written to memory-mapped address 0x00 and prints it as hex.
class Screen {
private:
    int lastValue;  // last value written (kept in range 0..255)

public:
    Screen();                          // default constructor (used by Machine member)
    ~Screen() = default;

    // Called by Memory when a store targets address 0x00.
    void write(int value);

    // Print the screen contents as hex, e.g. "0x0F".
    void display() const;

    // Return the last value written to the screen.
    int getLastValue() const;
};

#endif // SCREEN_H
