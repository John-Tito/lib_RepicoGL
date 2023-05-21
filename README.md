# PicoTK

This library provides a lightweight OpenGL-based framework based on PicoGL.

---

## Compatibility

This library has been tested on esp32-wrover-b.

---

## Installation

1. Download the library from the official repository.
2. Add the header files and source files to your project directory.

---

## Usage

1. Implement your own initialization function and update function for updates.
2. Initialize the user interface by calling "ui_init()" function with your own initialization function and update function as arguments.
3. Call "ui_loop()" function to enter event loop and handle user interface events.
4. Call "ui_end()" function to release resources used for UI.

---

## Sample Code

see example folder

---

## API Reference

***ui_init(void (*init_fn)(void), int (*update_fn)(void))***

Initialize the user interface with your own initialization function and update function. Returns 0 on success, -1 otherwise.

Parameters:

- `init_fn`: a function pointer to your own initialization function.
- `update_fn`: a function pointer to your own update function for GUI logic updates.

***ui_loop()***

Main function to enter event loop and handle user interface events.

***ui_end()***

Release resources used for UI.

***tkSwapBuffers()***

Swap buffers to update the screen.

---

## Reference/Quote

1. [kaaass's blog](https://blog.kaaass.net/archives/1340).
2. [PicoGL](https://www.pico.net/kb/picogl). Pico.