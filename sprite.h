#ifndef SPRITE_H
#define SPRITE_H

#include "Frame.h"
#include <vector>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name sprite h file for assignment7
 * This h file contains the outlined methods for use within a sprite.
 * A sprite is essentially a collection of frames that can be animated.
*/

class Sprite {
private:
    //list cntaining the frames of the sprite
    std::vector<Frame> frames;
    int width;
    int height;
    int currentFrame;

public:
    //Default constructor
    Sprite() = default;
    //Adds a frame to the list of frames of the sprite
    void addFrame();
    //Removes the current frame from the list
    void removeFrame(size_t index);
    //Gets the frame from the index, if it doesn't exist doesnt do anything
    Frame &getFrame(size_t index);
    //Returns the count of frames
    size_t frameCount() const;

    void duplicateFrame();
    void addFrame(const Frame &frame);
    void removeFrame();

    Sprite(int width, int height);
};

//SPRITE_H
#endif
