
#include "drawingCanvas.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name drawingCanvas h file for assignment8
 * This cpp file contains the outlined methods for use within the DrawingCanvas.
 * DrawingCanvas is in-charge of the pixel drawing for our Sprite Editor
*/

// Constructor
DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent), sprite(), currentColor(Qt::red), currentFrameIndex(0) {
    setAttribute(Qt::WA_StaticContents);
    sprite.addFrame(Frame(32, 32)); // Initial frame
}

// Returns the number of frames in the sprite
int DrawingCanvas::getFrameCount() const {
    return sprite.frameCount();
}

// Returns a thumbnail for a specific frame
QImage DrawingCanvas::getFrameThumbnail(int index) {
    if (index >= 0 && index < sprite.frameCount()) {
        return sprite.getFrame(index).getImage().scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation);
    }
    return QImage();
}

// Sets the current frame index
void DrawingCanvas::setCurrentFrameIndex(int index) {
    if (index >= 0 && index < sprite.frameCount()) {
        currentFrameIndex = index;
        update(); // Redraw with the new current frame
    }
}

// Sets the current drawing color
void DrawingCanvas::setCurrentColor(const QColor &color) {
    currentColor = color;
}

// Adds a new frame to the sprite
void DrawingCanvas::addNewFrame() {
    sprite.addFrame(Frame(32, 32)); // Assuming all frames are the same size
    currentFrameIndex = sprite.frameCount() - 1; // Switch to the new frame
    update(); // Redraw the canvas
}

void DrawingCanvas::deleteFrame(){
    sprite.removeFrame(currentFrameIndex);
    currentFrameIndex = sprite.frameCount()-1;
    update();
}

// Paint event handler
void DrawingCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if (sprite.frameCount() > 0) {
        QImage scaledImage = sprite.getFrame(currentFrameIndex).getImage().scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);
        painter.drawImage(rect(), scaledImage);
    }
}

// Mouse move event handler
void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        drawToImage(event->position().toPoint());
    }
}

// Mouse press event handler
void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawToImage(event->position().toPoint());
    }
}

// Method to draw to the image
void DrawingCanvas::drawToImage(const QPoint &point) {
    if (currentFrameIndex < sprite.frameCount()) {
        Frame& currentFrame = sprite.getFrame(currentFrameIndex);
        QPoint scaledPosition(point.x() * currentFrame.getImage().width() / width(), point.y() * currentFrame.getImage().height() / height());

        if(currentFrame.getImage().rect().contains(scaledPosition)) {
            currentFrame.setPixel(scaledPosition.x(), scaledPosition.y(), currentColor);
            update();
        }

        emit drawingChanged();
    }
}

void DrawingCanvas:: colorChanged(QColor newColor)
{
    currentColor = newColor;
}
