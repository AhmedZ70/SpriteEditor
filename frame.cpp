#include "frame.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name frame cpp file for assignment8
 * This cpp file contains the method definitions for a frame to be used in a sprite editor app.
 *
 * File and software practice principles reviewed by Joel Ronca.
*/

Frame::Frame(int width, int height) : image(width, height, QImage::Format_ARGB32) {

    // Makes the image transparent
    image.fill(Qt::transparent);
}

QImage& Frame::getImage() {

    // Returns the image
    return image;
}

void Frame::setPixel(int x, int y, const QColor &color) {

    // Sets the pixel color if the image is within the correct bounds
    if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
        image.setPixelColor(x, y, color);
    }
}

QJsonObject Frame::toJson() const {
    QJsonObject json;

    // Converts QImage to QByteArray in PNG format
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    this->image.save(&buffer, "PNG");

    // Converts QByteArray to base64 string and store in JSON
    json["image"] = QString::fromUtf8(byteArray.toBase64());

    // Stores image dimensions
    json["width"] = this->image.width();
    json["height"] = this->image.height();

    return json;
}

Frame Frame::fromJson(const QJsonObject& json) {
    QByteArray byteArray = QByteArray::fromBase64(json["image"].toString().toUtf8());

    // Stores image from json into a QImage
    QImage image;
    image.loadFromData(byteArray, "PNG");

    // Stores frame by frame of the image
    Frame frame(image.width(), image.height());
    frame.image = image;

    return frame;
}

void Frame::takeSnapshot() {

    // Stores a copy of the image onto the stack
    undoStack.push(image.copy());
    redoStack.clear();
}

void Frame::undo() {
    if (!undoStack.isEmpty()) {

        // If the undo stack is not empty, push onto the stack
        redoStack.push(image);

        // Pop and store the returned image from the undo stack
        image = undoStack.pop();
    }
}

void Frame::redo() {
    if (!redoStack.isEmpty()) {

        // If the redo stack is not empty, push onto the undo stack
        undoStack.push(image);

        // Pop and store the image from the redo stack
        image = redoStack.pop();
    }
}
