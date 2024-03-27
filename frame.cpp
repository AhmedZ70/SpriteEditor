#include "frame.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name frame cpp file for assignment8
 * This cpp file contains the method definitions for a frame to be used in a sprite editor app.
*/

// Constructor definition
Frame::Frame(int width, int height) : image(width, height, QImage::Format_ARGB32) {
    image.fill(Qt::white);
}

// getImage definition
QImage& Frame::getImage() { return image; }

// setPixel definition
void Frame::setPixel(int x, int y, const QColor &color) {
    if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
        image.setPixelColor(x, y, color);
    }
}
