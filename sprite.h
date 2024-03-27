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
    std::vector<Frame> frames;

public:
    Sprite() = default;

    void addFrame(const Frame &frame) {
        frames.push_back(frame);
    }

    void removeFrame(size_t index) {
        if (index < frames.size()) {
            frames.erase(frames.begin() + index);
        }
    }

    Frame &getFrame(size_t index) {
        return frames.at(index);
    }

    const Frame &getFrame(size_t index) const {
        return frames.at(index);
    }

    size_t frameCount() const {
        return frames.size();
    }

};

#endif // SPRITE_H
