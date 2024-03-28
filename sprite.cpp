#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "sprite.h"

void Sprite::addFrame()
{
    Frame frame = Frame(width, height);
    frames.push_back(frame);
    currentFrame++;
}

void Sprite::addFrame(const Frame &frame)
{
    frames.push_back(frame);
    currentFrame++;
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

void Sprite::duplicateFrame()
{
    Frame duplicatedFrame = frames.at(currentFrame);
    frames.push_back(duplicatedFrame);
}

void Sprite:: removeFrame()
{
    frames.erase(frames.begin() + currentFrame);
}

Sprite:: Sprite(int width, int height): width(width), height(height){}

