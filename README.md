# Vulkan Labyrinth

This project is an implementation of a labyrinth using Vulkan. It was created as a way to explore the Vulkan graphics API and to showcase the power of real-time rendering in creating immersive environments.

## Features

- Generated random labyrinth
- First-person view
- Real-time lighting and shadowing
- Realistic materials using PBR (Physically Based Rendering) shaders
- User-controlled camera movement
- FPS (Frames Per Second) counter

## Requirements

To run the application, you will need the following:

- A Vulkan-capable GPU (graphics card)
- Vulkan SDK (Software Development Kit)
- GLFW (a multi-platform library for OpenGL, OpenGL ES, and Vulkan)
- GLM (a C++ mathematics library for graphics software)

## Build and Run

1. Clone this repository to your local machine.
2. Navigate to the project directory and create a new directory called `build`.
3. From the `build` directory, run the following command to generate the project files: 

    ```
    cmake ..
    ```

4. Build the project by running the following command:

    ```
    cmake --build .
    ```

5. Once the build is complete, you can run the application by executing the `VulkanLabyrinth` executable file in the `bin` directory.

## Controls

The controls for the application are as follows:

- W, A, S, D: Move the camera forward, left, backward, and right
- Mouse: Control the camera's direction
- Esc: Quit the application

## Credits

This project was developed by [Your Name] as a part of a computer graphics course at [Your Institution]. The code is released under the MIT License. 

## Screenshots

![Screenshot 1](screenshots/screenshot1.png)

![Screenshot 2](screenshots/screenshot2.png)

## Acknowledgements

Special thanks to the following resources for their help and inspiration:

- [Vulkan Tutorial](https://vulkan-tutorial.com/)
- [LearnOpenGL](https://learnopengl.com/)
