#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "sprite.h"

void Sprite::addFrame(const Frame &frame) {
    frames.push_back(frame);
}

void Sprite::removeFrame(size_t index) {
    if (index < frames.size()) {
        frames.erase(frames.begin() + index);
    }
}

Frame &Sprite::getFrame(size_t index) {
    return frames.at(index);
}

size_t Sprite::frameCount() const {
    return frames.size();
}
