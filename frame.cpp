#include "frame.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name frame cpp file for assignment8
 * This cpp file contains the method definitions for a frame to be used in a sprite editor app.
*/

// Constructor definition
Frame::Frame(int width, int height) : image(width, height, QImage::Format_ARGB32) {
    image.fill(Qt::transparent);
}

// getImage definition
QImage& Frame::getImage() { return image; }

// setPixel definition
void Frame::setPixel(int x, int y, const QColor &color) {
    if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
        image.setPixelColor(x, y, color);
    }
}

QJsonObject Frame::toJson() const {
    QJsonObject json;

    // Convert QImage to QByteArray in PNG format
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    this->image.save(&buffer, "PNG");

    // Convert QByteArray to base64 string and store in JSON
    json["image"] = QString::fromUtf8(byteArray.toBase64());

    // Store image dimensions
    json["width"] = this->image.width();
    json["height"] = this->image.height();

    return json;
}

Frame Frame::fromJson(const QJsonObject& json) {
    QByteArray byteArray = QByteArray::fromBase64(json["image"].toString().toUtf8());

    QImage image;
    image.loadFromData(byteArray, "PNG");

    Frame frame(image.width(), image.height());
    frame.image = image;

    return frame;
}
