#ifndef SPRITE_H
#define SPRITE_H

#include "Frame.h"
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name sprite h file for assignment8
 * This h file contains the outlined methods for use within a sprite.
 * A sprite is essentially a collection of frames that can be animated.
*/

class Sprite {
private:
    // list cntaining the frames of the sprite
    std::vector<Frame> frames;

    // int of the pixel width of a sprite frame
    int width;

    // int of the pixel height of a sprite frame
    int height;

    // int of the current frame that is displayed
    int currentFrame;

public:
    /// @brief Sprite default constructor.
    Sprite() = default;

    /// @brief Sprite constructor with specified width and height pixels.
    /// @param int width of the frames for a sprite
    /// @param int height of the frames for a sprite
    Sprite(int width, int height);

    /// @brief Adds a frame to the list of frames of the sprite.
    void addFrame();

    /// @brief Removes the current frame from the list.
    /// @param size_t index of the current frame
    void removeFrame(size_t index);

    /// @brief Gets the frame from the index, if it doesn't exist it doesn't do anything.
    /// @param size_t index of the frame to get
    /// @return Frame at the index
    Frame &getFrame(size_t index);

    /// @brief Returns the count of frames.
    /// @return size_t the frame count
    size_t frameCount() const;

    /// @brief Duplicates the current frame as a new next frame.
    void duplicateFrame();

    /// @brief Adds an empty frame to the next frame.
    /// @param Frame to add
    void addFrame(const Frame &frame);

    /// @brief Removes the current frame from the list and goes to the previous frame, if none creates new empty frame.
    void removeFrame();

    /// @brief Serializes the sprite to a Json object.
    /// @return QJsonObject the serialized Json object
    QJsonObject toJson() const;

    /// @brief Deserializes the sprite from a Json object.
    /// @param QJsonObject to deserialize
    /// @return Sprite object after being deserialized
    static Sprite fromJson(const QJsonObject& json);
};

//SPRITE_H
#endif
