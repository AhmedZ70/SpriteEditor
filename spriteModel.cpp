#include "spriteModel.h"

SpriteModel::SpriteModel(QObject *parent)
    : QObject(parent) {


}


void SpriteModel::colorChanged() {

}

void SpriteModel::frameSizeSet(int width, int height) {
    sprite = Sprite(width, height);
}

void SpriteModel::frameDeleted(int frame) {
    sprite.removeFrame(frame);

}

void SpriteModel::frameAdded() {
    sprite.addFrame();

}

void SpriteModel::Duplicatd() {
    sprite.duplicateFrame();
}

void SpriteModel::undo() {

}

void SpriteModel::redo() {

}

void SpriteModel::addFrame(Frame newFrame) {
    sprite.addFrame();
}

void SpriteModel::setFrame(Frame frame) {

}

void SpriteModel::removeFrame(Frame deletedFrame) {
    sprite.removeFrame();
}

void SpriteModel::setSprite(Sprite newSprite) {

    sprite.addFrame();
}

int SpriteModel::getFramesPerSecond() {

    return 0; // Placeholder return value
}
