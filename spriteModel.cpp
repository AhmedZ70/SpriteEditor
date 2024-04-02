#include "spriteModel.h"
#include <QFile>
#include <QDebug>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name spriteModel h file for assignment8
 * This h file contains the outlined methods for use within the spriteModel class.
 * Sprite Model will control the frames, animations, connect the drawing canvas, and dimension dialog.
 *
 * File and software practice principles reviewed by Ezekiel Jaramillo.
*/

SpriteModel::SpriteModel(QObject *parent) : QObject(parent), sprite(), currentFrameIndex(0) {

    // Set the default frames per second to 16.
    this->fps = 16;
}

SpriteModel::~SpriteModel() {

    // Delete the playback timer and popup dialog
    delete playbackTimer;
    delete playbackPopup;
}

void SpriteModel::addFrame() {

    // Add a new frame to the sprite.
    sprite.addFrame(Frame(spriteWidth, spriteHeight));

    // Set the current frame index to the last frame.
    setCurrentFrameIndex(getFrameCount() - 1);
    emit spriteChanged();
}

// Deletes the current frame from the sprite and emits a signal to update the view.
void SpriteModel::deleteFrame() {

    if (sprite.frameCount() > 1) {
        sprite.removeFrame(currentFrameIndex);

        // Update the current frame index.
        currentFrameIndex = sprite.frameCount() - 1;
        emit spriteChanged();
    }
}

std::vector<Frame> SpriteModel::getAllFrames() {

    // Return all frames from the sprite.
    return sprite.returnFrames();
}

void SpriteModel::duplicateFrame() {
    Frame dubFrame = sprite.getCurrentFrame(currentFrameIndex);

    // Insert the duplicated frame.
    sprite.insertFrame(currentFrameIndex, dubFrame);
    emit spriteChanged();
}

void SpriteModel::setCurrentFrameIndex(size_t index) {

    if (index < sprite.frameCount()) {

        // Set the current frame index.
        currentFrameIndex = index;
        emit spriteChanged();
    }
}

int SpriteModel::getCurrentFrameIndex() const {
    return currentFrameIndex;
}

QImage SpriteModel::getCurrentFrameImage(size_t index) {

    // Ensure the index is within the range of frames.
    if (index < sprite.frameCount()) {
        return sprite.getFrame(index).getImage();
    }

    // Return an empty image if the index is out of range.
    return QImage();
}

void SpriteModel::updatePixel(const QPoint& canvasPoint, const QColor& color, int width, int height) {

    // Scale the canvas point to the frame's dimensions.
    QPoint scaledPosition(canvasPoint.x() * getCurrentFrameImage(currentFrameIndex).width() / width,
                          canvasPoint.y() * getCurrentFrameImage(currentFrameIndex).height() / height);

    // Ensure the current frame index is within the range of frames.
    if (currentFrameIndex < (int)sprite.frameCount()) {
        Frame& currentFrame = sprite.getFrame(currentFrameIndex);

        // Update the pixel in the current frame.
        currentFrame.setPixel(scaledPosition.x(), scaledPosition.y(), color);
        emit spriteChanged();
    }
}

int SpriteModel::getFrameCount() const {
    return sprite.frameCount();
}

QImage SpriteModel::getFrameThumbnail(size_t index) {

    // Ensure the index is within the range of frames.
    if (index < sprite.frameCount()) {

        // Return a scaled thumbnail image of the frame.
        return sprite.getFrame(index).getImage().scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation);
    }

    return QImage();
}

void SpriteModel::setInitialFrame(int width, int height) {
    spriteWidth = width;
    spriteHeight = height;

    // Add an initial frame to the sprite.
    sprite.addFrame(Frame(spriteWidth, spriteHeight));
}

bool SpriteModel::save(const QString& fileName) const {
    QFile file(fileName);

    // Open the file for writing.
    if (!file.open(QIODevice::WriteOnly)) {

        // Log an error message if the file cannot be opened.
        qDebug() << "Could not open file for writing:" << fileName;

        // Return false to indicate failure.
        return false;
    }

    // Convert the sprite to a JSON object.
    QJsonObject jsonObj = sprite.toJson();

    // Create a JSON document from the JSON object.
    QJsonDocument doc(jsonObj);

    // Write the JSON document to the file.
    file.write(doc.toJson());
    file.close();

    // Return true to indicate success.
    return true;
}

void SpriteModel::load(const QString& fileName) {
    QFile file(fileName);

    // Open the file for reading.
    if (!file.open(QIODevice::ReadOnly)) {

        // Log an error message if the file cannot be opened.
        qDebug() << "Could not open file for reading:" << fileName;

        // Throw an exception to indicate failure.
        throw std::runtime_error("File cannot be opened.");
    }

    // Read all data from the file.
    QByteArray rawData = file.readAll();

    // Create a JSON document from the raw data.
    QJsonDocument doc(QJsonDocument::fromJson(rawData));

    // Get the JSON object from the JSON document.
    QJsonObject jsonObj = doc.object();

    // Create a new sprite from the JSON object.
    Sprite newSprite = Sprite::fromJson(jsonObj);

    // Set the sprite to the new sprite.
    sprite = newSprite;

    emit spriteChanged();
    emit loaded();
}

void SpriteModel::playAnimation() {

    // Check if the playback popup dialog does not exist.
    if (!playbackPopup) {

        // Create a new QDialog for the playback popup.
        playbackPopup = new QDialog();
        playbackPopup->setWindowTitle("Preview");
        allFrames = getAllFrames();

        // Create a vertical layout for the popup.
        QVBoxLayout* layout = new QVBoxLayout(playbackPopup);

        // Create a QLabel for displaying the animation frame.
        QLabel* imageLabel = new QLabel(playbackPopup);

        // Add the image label to the layout.
        layout->addWidget(imageLabel);

        playbackPopup->setLayout(layout);

        // Set the popup to be deleted on close.
        playbackPopup->setAttribute(Qt::WA_DeleteOnClose);

        // Create a new QTimer for the animation playback.
        playbackTimer = new QTimer(playbackPopup);
        connect(playbackTimer, &QTimer::timeout, this, [this, imageLabel]() {

            // Check if there are more frames to display.
            if (currentPlaybackFrameIndex < allFrames.size()) {

                // Get the next frame image.
                QImage img = allFrames[currentPlaybackFrameIndex++].getImage();
                if (!img.isNull()) {

                    // Scale the image to a new size
                    QSize newSize(600, 600);
                    img = img.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation);

                    // Set the image in the label.
                    imageLabel->setPixmap(QPixmap::fromImage(img));
                } else {

                    // Display error if index bounds are exceeded
                    qDebug() << "Image at index" << currentPlaybackFrameIndex << "is null.";
                }

                // Loop back to the first frame.
                if (currentPlaybackFrameIndex >= allFrames.size()) {
                    currentPlaybackFrameIndex = 0;
                }
            }
        });

        // Ensure the dialog and timer are cleaned up properly
        connect(playbackPopup, &QDialog::destroyed, [this]() {

            // Stop the timer to prevent further ticks.
            playbackTimer->stop();

            // Reset the timer pointer.
            playbackTimer = nullptr;

            // Reset the popup pointer.
            playbackPopup = nullptr;
        });

        // Start the timer with the interval based on the frames per second.
        playbackTimer->start(1000 / fps);
    }

    // Show the popup if it is not already visible.
    if (playbackPopup && !playbackPopup->isVisible()) {
        playbackPopup->show();
    }
}

void SpriteModel::showTrueSize() {

    // Check if the playback popup dialog does not exist.
    if (!playbackPopup) {
        playbackPopup = new QDialog();

        // Set the window title of the popup.
        playbackPopup->setWindowTitle("True Size Preview");
        allFrames = getAllFrames();

        // Create a vertical layout for the popup.
        QVBoxLayout* layout = new QVBoxLayout(playbackPopup);

        QLabel* imageLabel = new QLabel(playbackPopup);

        // Center the image in the label.
        imageLabel->setAlignment(Qt::AlignCenter);

        // Add the image label to the layout.
        layout->addWidget(imageLabel);

        playbackPopup->setLayout(layout);

        // Set the popup to be deleted on close.
        playbackPopup->setAttribute(Qt::WA_DeleteOnClose);

        // Adjust the size of the popup.
        playbackPopup->resize(300, 300);

        // Create a new QTimer for the animation playback.
        playbackTimer = new QTimer(playbackPopup);
        connect(playbackTimer, &QTimer::timeout, this, [this, imageLabel]() {

            // Check if there are more frames to display.
            if (currentPlaybackFrameIndex < allFrames.size()) {

                // Get the next frame image.
                QImage img = allFrames[currentPlaybackFrameIndex++].getImage();

                if (!img.isNull()) {

                    // Set the image in the label at true size.
                    imageLabel->setPixmap(QPixmap::fromImage(img));
                } else {
                    qDebug() << "Image at index" << currentPlaybackFrameIndex << "is null.";
                }
                if (currentPlaybackFrameIndex >= allFrames.size()) {

                    // Loop back to the first frame.
                    currentPlaybackFrameIndex = 0;
                }
            }
        });

        // Ensure the dialog and timer are cleaned up properly
        connect(playbackPopup, &QDialog::destroyed, [this]() {

            // Stop the timer to prevent further ticks.
            playbackTimer->stop();

            // Reset the timer and popup pointer
            playbackTimer = nullptr;
            playbackPopup = nullptr;
        });

        // Start the timer with the interval based on the frames per second.
        playbackTimer->start(1000 / fps);
    }

    if (playbackPopup && !playbackPopup->isVisible()) {

        // Show the popup if it is not already visible.
        playbackPopup->show();
    }
}

void SpriteModel::onDrawingStarted() {

    // Take a snapshot of the current frame.
    sprite.getFrame(currentFrameIndex).takeSnapshot();
}

void SpriteModel::setFPS(int newVal) {
    this->fps = newVal;

    // Check if the playback popup is visible.
    if (fps > 0 && playbackPopup && playbackPopup->isVisible()) {
        int interval = 1000 / fps;

        // Set the new timer interval.
        playbackTimer->setInterval(interval);
    }
}

void SpriteModel::undo() {

    // Undo the last change to the current frame.
    sprite.getFrame(currentFrameIndex).undo();
    emit spriteChanged();
}

void SpriteModel::redo() {

    // Redo the last undone change to the current frame.
    sprite.getFrame(currentFrameIndex).redo();
    emit spriteChanged();
}
