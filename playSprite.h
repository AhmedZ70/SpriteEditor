// #ifndef PLAYSPRITE_H
// #define PLAYSPRITE_H

// #include "frame.h"
// #include <QWidget>
// #include <QDialog>
// #include <QLabel>
// #include <QTimer>
// #include <QObject>
// #include <QVBoxLayout>

// /**
//  * @author Joseph Corbeil, Raj Reddy, Johnny Song, Joel Ronca, Ezekiel Jaramillo, and Ahmed Zahran
//  * @date March. 26, 2024
//  * @name playSprite.h file for Assignment8
//  * This header file defines the variables/methods for the PlaySprite class which will be used in the MainWindow class
// */

// class PlaySprite : public QObject {
//     Q_OBJECT

// private:

//     // a vector holding the different frames to display
//     std::vector<Frame> frames;

//     // int showing what the frames per second (fps) is
//     int fps;

// public slots:
//     void setFramesAndFPS(std::vector<Frame> frameslist, int framesPersecond);
//     void Play();

// public:


//     /// @brief default constructor with no paramaters
//     PlaySprite();

//     // PlaySprite(const PlaySprite &other);

//     // /// @brief constructor to take in paramaters
//     // /// @param framesPerSecond will be set to fps
//     // PlaySprite(std::vector<Frame> frame, int framesPerSecond);

//     /// @brief Destructor.
//     // ~PlaySprite();

//     /// @brief setter method for the frames per second (fps)
//     /// @param the new fps to be set to
//     ///
//     void setFPS(int fps);


//     /// @brief method to show a pop-up window of the sprite animation cycle
//     QDialog* PopUpWindow();
// };

// #endif // PLAYSPRITE_H
