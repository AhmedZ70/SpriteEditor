# Sprite Editor 
Sprite-Editor created by GitHub Classroom

## Table of contents

- Project Description
- Software Requirements
- Extra feature
- Troubleshooting
- Implementation Highlights
- External Code Resources
- Authors Information 

## Project Description
Our Sprite Editor is a sophisticated Qt C++ application that allows users to create, edit, and animate sprites. This tool is particularly tailored for artists and game developers looking to design pixel art and sprite sheets. Key features include drawing, erasing, frame editing, sprite animation with adjustable frame rates, and a robust color picker.


## Software Requirements:
Operating System: Any OS capable of running Qt, including Windows, macOS, and Linux.
Qt Framework: Version Qt 6.6.0 or above.

## Extra Features

The Sprite Editor includes several advanced features to enhance user productivity and creativity:

### Undo
Allows users to revert their last action(s). This feature is crucial when making edits to sprites, as it provides the flexibility to experiment without the fear of making irreversible changes.

### Redo
Complements the undo feature by allowing users to reapply actions that were previously undone. This ensures that users can navigate forward and backward in their action history with ease.

### Duplicate
This feature enables users to create an exact copy of the selected frame(s) quickly. It is especially useful for creating repeated patterns or when a similar design is needed as a starting point for further edits.this effect is chosen randomly by the server, the snake's speed temporarily increases, making it move 4 more units per frame

## Troubleshooting

Encountering issues? Here's a quick guide to solving common problems:

### Installation Issues
- Make sure Qt is installed and the PATH is correctly set.
- Confirm all dependencies in the `.pro` file are correct.

### Runtime Errors
- If the application crashes, check for correct resource linking and file paths.
- For features not working, ensure you have the right Qt version and a C++11 compatible compiler.

### Performance Problems
- For slow performance with large sprites, optimize sprite size or check your system's resources.

### File Saving and Loading
- Can't save or load? Check your file permissions in the application directory.

## External code resources
-Qt Widgets C++ Classes: [https://doc.qt.io/qt-6/qtwidgets-module.html]

## Implementation Highlights

One of the core architectural decisions in the development of the Sprite Editor is the adherence to the Model-View-Controller (MVC) design pattern. This structure is pivotal in separating the concerns of user interface (View), data (Model), and the control flow (Controller), promoting clean and maintainable code. Here’s how it benefits our application:

### Model
The Model component manages the sprite data and business logic. It is responsible for manipulating the sprite frames, colors, and animations, ensuring high cohesion and low coupling. This way, data management is centralized, facilitating easier testing and modification.

### View
The View layer is our user interface, which displays the sprite canvas and tool selections without incorporating any of the business logic. It reacts to user inputs and displays the results of their interactions, but all processing is delegated to the Controller to handle.

### Controller
The Controller acts as an intermediary between the Model and View, taking user inputs from the View, processing them with help from the Model, and updating the View accordingly. This separation allows for different user interfaces to be used with the same underlying model logic.

This MVC architecture is particularly beneficial for collaborative environments, as it allows for parallel development on separate components, and also makes it easier to scale and adapt the application as it grows in complexity and functionality.

## FAQ

Here are some common questions regarding the Sprite Editor's capabilities and limitations:

### What is the maximum number of frames I can add?
The maximum number of frames you can add to a sprite is 30. This ensures optimal performance and manageability within the editor.

### What is the range for frames per second (fps) in animations?
You can set the fps for your animations anywhere from 1 to 30. This allows for smooth playback and a good range of animation speeds.

### How many pixels can each frame have?
Each frame can have anywhere from 1 to 256 pixels in both width and height, giving you the freedom to create detailed sprites while keeping the file sizes manageable.

## Authors Information
Joseph Corbeil

Johnny Song

Ezekiel Jaramillo

Ahmed Zahran

Raj Reddy

Joel Ronca


Last updated: April 1, 2024

