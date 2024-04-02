#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "sprite.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name sprite cpp file for assignment8
 * This cpp file contains the method implementation for use within a sprite.
 * A sprite is essentially a collection of frames that can be animated.
 *
 * File and software principles reviewed by Johnny Song
*/

Sprite::Sprite(int width, int height): width(width), height(height) {
    // Set the initial current frame index to 0.
    currentFrame = 0;
}

void Sprite::addFrame() {
    Frame frame = Frame(width, height);

    // Add the frame to the frames vector.
    frames.push_back(frame);

    // Increment the current frame index.
    currentFrame++;
}

void Sprite::addFrame(const Frame &frame) {

    // Add the given frame to the frames vector.
    frames.push_back(frame);
    currentFrame++;
}

std::vector<Frame> Sprite::returnFrames() {

    // Return the frames vector.
    return frames;
}

void Sprite::insertFrame(size_t index, const Frame& frame) {
    if (index <= frames.size()) {

        // Insert the frame at the specified index.
        frames.insert(frames.begin() + index, frame);
    } else {
        // If the index is invalid, add the frame to the end of the vector.
        frames.push_back(frame);
    }
}

void Sprite::removeFrame(size_t index) {
    // Check if the index is valid.
    if (index < frames.size()) {

        // Remove the frame at the specified index.
        frames.erase(frames.begin() + index);
    }
}

Frame &Sprite::getFrame(size_t index) {
    // Returns the frame at the specified index.
    return frames.at(index);
}

size_t Sprite::frameCount() const {

    // Return the size of the frames vector.
    return frames.size();
}

void Sprite::duplicateFrame() {

    // Check if the current frame index is valid.
    if(currentFrame >= 0 && currentFrame < (int)frames.size()) {

        // Get the current frame.
        Frame duplicatedFrame = frames.at(currentFrame);

        // Add the duplicated frame to the end of the vector.
        frames.push_back(duplicatedFrame);
    }
}

Frame & Sprite::getCurrentFrame(int index) {

    // Return the frame at the specified index.
    return frames.at(index);
}

void Sprite::removeFrame() {

    // Remove the frame at the current frame index.
    frames.erase(frames.begin() + currentFrame);
}

QJsonObject Sprite::toJson() const {
    QJsonObject json;
    QJsonArray frameArray;

    // Iterate through the frames.
    for (const auto& frame : frames) {

        // Convert each frame to JSON and add it to the array.
        frameArray.append(frame.toJson());
    }

    // Add the sprite's properties to the JSON object.
    json["width"] = width;
    json["height"] = height;
    json["currentFrame"] = currentFrame;
    json["frames"] = frameArray;

    return json;
}

Sprite Sprite::fromJson(const QJsonObject& json) {
    Sprite sprite;

    // Set the sprite's properties from the JSON object.
    sprite.width = json["width"].toInt();
    sprite.height = json["height"].toInt();
    sprite.currentFrame = json["currentFrame"].toInt();

    // Get the frames array from the JSON object.
    QJsonArray frameArray = json["frames"].toArray();

    // Iterate through the frames in the array.
    for (const auto& frameValue : frameArray) {

        // Create a Frame object from the JSON object.
        Frame frame = Frame::fromJson(frameValue.toObject());

        // Add the frame to the sprite.
        sprite.frames.push_back(frame);
    }

    return sprite;
}
