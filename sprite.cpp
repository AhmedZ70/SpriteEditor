#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "sprite.h"

Sprite:: Sprite(int width, int height): width(width), height(height){}

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

QJsonObject Sprite::toJson() const {
    QJsonObject json;
    QJsonArray frameArray;

    for (const auto& frame : frames) {
        frameArray.append(frame.toJson());
    }

    json["width"] = width;
    json["height"] = height;
    json["currentFrame"] = currentFrame;
    json["frames"] = frameArray;

    return json;
}

Sprite Sprite::fromJson(const QJsonObject& json) {
    Sprite sprite;

    sprite.width = json["width"].toInt();
    sprite.height = json["height"].toInt();
    sprite.currentFrame = json["currentFrame"].toInt();

    QJsonArray frameArray = json["frames"].toArray();
    for (const auto& frameValue : frameArray) {
        Frame frame = Frame::fromJson(frameValue.toObject());
        sprite.frames.push_back(frame);
    }

    return sprite;
}
