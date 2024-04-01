#include "spriteModel.h"
#include <QFile>
#include <QDebug>

SpriteModel::SpriteModel(QObject *parent) : QObject(parent), sprite(),  currentFrameIndex(0) {
    this->fps = 8;
}

void SpriteModel::addFrame() {
    sprite.addFrame(Frame(spriteWidth, spriteHeight));
    setCurrentFrameIndex(getFrameCount() - 1);
    emit spriteChanged();

}

void SpriteModel::deleteFrame() {
    if(sprite.frameCount() > 1)
    sprite.removeFrame(currentFrameIndex);
    currentFrameIndex = sprite.frameCount()-1;
    emit spriteChanged();
}

std::vector<Frame> SpriteModel::getAllFrames() {
    return sprite.returnFrames();
}

void SpriteModel::duplicateFrame() {
    Frame dubFrame = sprite.getCurrentFrame(currentFrameIndex);
    sprite.insertFrame(currentFrameIndex, dubFrame);
    emit spriteChanged();
}
void SpriteModel::setCurrentFrameIndex(size_t index) {
    if (index < sprite.frameCount()) {
        currentFrameIndex = index;
    }
    emit spriteChanged();
}

int SpriteModel::getCurrentFrameIndex() const {
    return currentFrameIndex;
}


QImage SpriteModel::getCurrentFrameImage(size_t index) {
    if (index < sprite.frameCount()) {
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
void SpriteModel::setInitialFrame(int width, int height)
{
    spriteWidth = width;
    spriteHeight = height;
    sprite.addFrame(Frame(spriteWidth, spriteHeight));
}

bool SpriteModel::save(const QString& fileName) const {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file for writing:" << fileName;
        return false;
    }

    QJsonObject jsonObj = sprite.toJson();
    QJsonDocument doc(jsonObj);
    file.write(doc.toJson());
    file.close();
    return true;
}

void SpriteModel::load(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << fileName;
        throw std::runtime_error("File cannot be opened.");
    }
    QByteArray rawData = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(rawData));
    QJsonObject jsonObj = doc.object();

    Sprite newSprite = Sprite::fromJson(jsonObj);
    sprite = newSprite;
    emit spriteChanged();
    emit loaded();
}

void SpriteModel::playAnimation() {
    if (!playbackPopup) {
        playbackPopup = new QDialog();
        playbackPopup->setWindowTitle("Preview");
        allFrames = getAllFrames();
        QVBoxLayout* layout = new QVBoxLayout(playbackPopup);

        QLabel* imageLabel = new QLabel(playbackPopup);
        layout->addWidget(imageLabel);

        playbackPopup->setLayout(layout);
        playbackPopup->setAttribute(Qt::WA_DeleteOnClose);

        playbackTimer = new QTimer(playbackPopup);
        connect(playbackTimer, &QTimer::timeout, this, [this, imageLabel]() {
            if (currentPlaybackFrameIndex < allFrames.size()) {
                QImage img = allFrames[currentPlaybackFrameIndex++].getImage();
                if (!img.isNull()) {
                    // Scale the image to a new size
                    QSize newSize(600, 600); // Example new size, adjust as needed
                    img = img.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation);
                    imageLabel->setPixmap(QPixmap::fromImage(img));
                } else {
                    qDebug() << "Image at index" << currentPlaybackFrameIndex << "is null.";
                }
                if (currentPlaybackFrameIndex >= allFrames.size()) {
                    currentPlaybackFrameIndex = 0; // Loop back to the first frame
                }
            }
        });
        // Ensure the dialog and timer are cleaned up properly
        connect(playbackPopup, &QDialog::destroyed, [this]() {
            playbackTimer->stop(); // Stop the timer to prevent further ticks
            playbackTimer = nullptr; // Reset the timer pointer
            playbackPopup = nullptr; // Reset the popup pointer
        });

        playbackTimer->start(1000 / fps); // Adjust fps as needed
    }

    if (playbackPopup && !playbackPopup->isVisible()) {
        playbackPopup->show();
    }
}

void SpriteModel::showTrueSize() {
    if (!playbackPopup) {
        playbackPopup = new QDialog();
        playbackPopup->setWindowTitle("True Size Preview");
        allFrames = getAllFrames();
        QVBoxLayout* layout = new QVBoxLayout(playbackPopup);

        QLabel* imageLabel = new QLabel(playbackPopup);
        layout->addWidget(imageLabel);

        playbackPopup->setLayout(layout);
        playbackPopup->setAttribute(Qt::WA_DeleteOnClose);

        playbackTimer = new QTimer(playbackPopup);
        connect(playbackTimer, &QTimer::timeout, this, [this, imageLabel]() {
            if (currentPlaybackFrameIndex < allFrames.size()) {
                QImage img = allFrames[currentPlaybackFrameIndex++].getImage();
                if (!img.isNull()) {
                    imageLabel->setPixmap(QPixmap::fromImage(img)); // Display image at true size
                } else {
                    qDebug() << "Image at index" << currentPlaybackFrameIndex << "is null.";
                }
                if (currentPlaybackFrameIndex >= allFrames.size()) {
                    currentPlaybackFrameIndex = 0; // Loop back to the first frame
                }
            }
        });
        // Ensure the dialog and timer are cleaned up properly
        connect(playbackPopup, &QDialog::destroyed, [this]() {
            playbackTimer->stop(); // Stop the timer to prevent further ticks
            playbackTimer = nullptr; // Reset the timer pointer
            playbackPopup = nullptr; // Reset the popup pointer
        });

        playbackTimer->start(1000 / fps); // Adjust fps as needed
    }

    if (playbackPopup && !playbackPopup->isVisible()) {
        playbackPopup->show();
    }
}



void SpriteModel::onDrawingStarted(){
        sprite.getFrame(currentFrameIndex).takeSnapshot();
}

void SpriteModel::setFPS(int newVal){
    this->fps = newVal;
}
void SpriteModel::undo() {
    sprite.getFrame(currentFrameIndex).undo();
    emit spriteChanged();
}

void SpriteModel::redo() {
    sprite.getFrame(currentFrameIndex).redo();
    emit spriteChanged();
}

