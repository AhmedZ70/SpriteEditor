#include "spriteModel.h"

SpriteModel::SpriteModel(QObject *parent) : QObject(parent), sprite(),  currentFrameIndex(0) {
    sprite.addFrame(Frame(32, 32));

}

void SpriteModel::addFrame() {
    sprite.addFrame(Frame(32, 32));
    setCurrentFrameIndex(getFrameCount() - 1);
    emit spriteChanged();
}

void SpriteModel::deleteFrame(){
    sprite.removeFrame(currentFrameIndex);
    currentFrameIndex = sprite.frameCount()-1;
    emit spriteChanged();
}

void SpriteModel::duplicateFrame() {
    sprite.duplicateFrame();
    emit spriteChanged();
}

void SpriteModel::setCurrentFrameIndex(size_t index) {
    if (index >= 0 && index < sprite.frameCount()) {
        currentFrameIndex = index;
    }
    emit spriteChanged();
}

int SpriteModel::getCurrentFrameIndex() const {
    return currentFrameIndex;
}


QImage SpriteModel::getCurrentFrameImage(size_t index) {
    if (index >= 0 && index < sprite.frameCount()) {
        return sprite.getFrame(index).getImage();
    }
    return QImage();
}

void SpriteModel::updatePixel(const QPoint& canvasPoint, const QColor& color, int width, int height) {
    QPoint scaledPosition(canvasPoint.x() * getCurrentFrameImage(currentFrameIndex).width() / width, canvasPoint.y() * getCurrentFrameImage(currentFrameIndex).height() / height);
    if (currentFrameIndex < (int)sprite.frameCount()) {
        Frame& currentFrame = sprite.getFrame(currentFrameIndex);
        currentFrame.setPixel(scaledPosition.x(), scaledPosition.y(), color);
        emit spriteChanged();
    }
}

int SpriteModel::getFrameCount() const {
    return sprite.frameCount();
}

QImage SpriteModel::getFrameThumbnail(size_t index) {
    if (index < sprite.frameCount()) {
        return sprite.getFrame(index).getImage().scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation);
    }
    return QImage();
}
