#ifndef FRAME_H
#define FRAME_H

#include <QColor>
#include <QColormap>
#include <QImage>
#include <QBuffer>
#include <QByteArray>
#include <QJsonObject>
#include <QStack>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name frame h file for assignment8
 * This h file contains the outlined methods for use within a frame.
*/

class Frame{
private:
    // Member variable that holds an image displayed on the frame
    QImage image;

    QStack<QImage> undoStack;
    QStack<QImage> redoStack;

public:

    /// @brief Frame constructor
    /// @param int width of a frame
    /// @param int height of a frame
    Frame(int width, int height);

    /// @brief Returns the frames QImage
    /// @return QImage
    QImage &getImage();

    /// @brief Sets the color of a pixel in a Frame(QImage) with a QColor
    /// @param int x pixel coordinate
    /// @param int y pixel coordinate
    /// @param QColor color of the pixel to be sets
    void setPixel(int x, int y, const QColor &color);

    /// @brief Serializes the frame to a JSON object.
    /// @return QJsonObject the serialized json object
    QJsonObject toJson() const;

    /// @brief Deserializes the frame from a JSON object.
    /// @param QJsonObject to deserialize
    /// @return Frame object after deserialization.
    static Frame fromJson(const QJsonObject& json);

    void takeSnapshot();

    void undo();

    void redo();
};

#endif // FRAME_H
