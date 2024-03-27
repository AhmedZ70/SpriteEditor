#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "Frame.h"
#include "Sprite.h"

class DrawingCanvas : public QWidget {
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr)
        : QWidget(parent), sprite(), currentColor(Qt::blue), currentFrameIndex(0) {
        setAttribute(Qt::WA_StaticContents);
        sprite.addFrame(Frame(32, 32));
    }
    int getFrameCount() const {
        return sprite.frameCount();
    }
    QImage getFrameThumbnail(int index) {
        if (index >= 0 && index < sprite.frameCount()) {
            return sprite.getFrame(index).getImage().scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation); // Example size
        }
        return QImage();
    }
    void setCurrentFrameIndex(int index) {
        if (index >= 0 && index < sprite.frameCount()) {
            currentFrameIndex = index;
            update(); // Redraw with the new current frame
        }
    }
    // Public method to set the current drawing color
    void setCurrentColor(const QColor &color) {
        currentColor = color;
    }
    void addNewFrame() {
        sprite.addFrame(Frame(32, 32)); // Assuming all frames are the same size
        currentFrameIndex = sprite.frameCount() - 1; // Switch to the new frame
        update(); // Redraw the canvas
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        if (sprite.frameCount() > 0) {
            QImage scaledImage = sprite.getFrame(currentFrameIndex).getImage().scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);
            painter.drawImage(rect(), scaledImage);
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            drawToImage(event->position().toPoint());
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            drawToImage(event->position().toPoint());
        }
    }

private:
    Sprite sprite;
    QColor currentColor;
    int currentFrameIndex;

    void drawToImage(const QPoint &point) {
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

signals:
    void drawingChanged(); // Could signal to update UI elements related to frame changes
};

#endif // DRAWINGCANVAS_H
