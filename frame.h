#ifndef FRAME_H
#define FRAME_H

#include <QColor>
#include <QColormap>
#include <QImage>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name frame h file for assignment7
 * This h file contains the outlined methods for use within a frame.
*/

class Frame{
private:

    QImage image;
public:

    Frame(int width, int height) : image(width, height, QImage::Format_ARGB32) {
        image.fill(Qt::white);
    }

    QImage &getImage() { return image; }
    const QImage &getImage() const { return image; }

    void setPixel(int x, int y, const QColor &color) {
        if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
            image.setPixelColor(x, y, color);
        }
    }

};

#endif // FRAME_H
