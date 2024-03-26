#ifndef FRAME_H
#define FRAME_H

#include "pixel.h"
#include <QColor>
#include <QColormap>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name frame h file for assignment7
 * This h file contains the outlined methods for use within a frame.
*/

class Frame{
private:
    // private pixel map object for a frame
    QColormap pixelMap;


public:
    /// @brief Frame constructor that initializes an array of pixels.
    Frame();

    /// @brief Copy constructor that will create a copy of a Frame.
    /// @param otherFrame the frame to be copied
    Frame(const Frame& otherFrame);

    /// @brief Destructor.
    ~Frame();

    /// @brief Gets the QColor of a specified pixel to save/manipulate
    /// @param x and y locations of the pixel
    /// @return QColor
    QColor getColor(int x, int y);

    /// @brief Sets the pixel with a QColor at a specific x and y
    /// @param x and y locations of the pixel
    void setPixel(int x, int y, QColor color);
};

#endif // FRAME_H
