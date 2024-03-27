#include "sprite.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>



Sprite:: Sprite(QWidget *parent)
    : QWidget(parent), image(32, 32, QImage::Format_ARGB32) {
    image.fill(Qt::white);
}



void Sprite:: paintEvent(QPaintEvent *event){
        QPainter painter(this);
        // Scale the image to the current size of the widget
        // Omitting the scaling mode, which defaults to a method similar to nearest neighbor
        QImage scaledImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);
        painter.drawImage(0, 0, scaledImage);
    }

void Sprite:: mousePressEvent(QMouseEvent *event){
        drawPixel(event->pos());
    }

void Sprite:: mouseMoveEvent(QMouseEvent *event) {
        if(event->buttons() & Qt::LeftButton) {
            drawPixel(event->pos());
        }
    }


void Sprite:: drawPixel(const QPoint &position) {
        // Scale the position back to the 256x256 image coordinates
        QPoint scaledPosition(position.x() * 32 / width(), position.y() * 32 / height());
        if(image.rect().contains(scaledPosition)) {
            image.setPixelColor(scaledPosition, Qt::black); // Here We want to make this whatever the user selects
            update(); // Cause a repaint
        }
    }

