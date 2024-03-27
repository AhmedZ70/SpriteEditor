#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class Sprite : public QWidget {
    Q_OBJECT

public:
    explicit Sprite(QWidget *parent = nullptr)
        : QWidget(parent), image(32, 32, QImage::Format_ARGB32) {
        image.fill(Qt::white);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        // Scale the image to the current size of the widget
        // Omitting the scaling mode, which defaults to a method similar to nearest neighbor
        QImage scaledImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);
        painter.drawImage(0, 0, scaledImage);
    }

    void mousePressEvent(QMouseEvent *event) override {
        drawPixel(event->pos());
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if(event->buttons() & Qt::LeftButton) {
            drawPixel(event->pos());
        }
    }

private:
    QImage image;

    void drawPixel(const QPoint &position) {
        // Scale the position back to the 256x256 image coordinates
        QPoint scaledPosition(position.x() * 32 / width(), position.y() * 32 / height());
        if(image.rect().contains(scaledPosition)) {
            image.setPixelColor(scaledPosition, Qt::black); // Here We want to make this whatever the user selects
            update(); // Cause a repaint
        }
    }
};

#endif // SPRITE_H
