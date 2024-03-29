#include "drawingCanvas.h"
using namespace std;
DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent), currentColor(Qt::red){
    setAttribute(Qt::WA_StaticContents);
}

void DrawingCanvas::paintEvent(QPaintEvent *) {
    emit requestCurrentImage();
    QPainter painter(this);

    // Draw checkerboard pattern
    int tileSize = 10;
    QColor color1(220, 220, 220); // Light gray
    QColor color2(255, 255, 255); // White
    QRect background = this->rect();

    for (int y = 0; y < background.height(); y += tileSize) {
        for (int x = 0; x < background.width(); x += tileSize) {
            QRect tileRect(x, y, tileSize, tileSize);
            QColor tileColor = ((x / tileSize) % 2 == (y / tileSize) % 2) ? color1 : color2;
            painter.fillRect(tileRect, tileColor);
        }
    }

    if (!currentImage.isNull()) {
        painter.drawImage(rect(), currentImage);
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        const QPoint canvasPoint = event->position().toPoint();
        emit requestPixelChange(canvasPoint, currentColor, width(), height());
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        const QPoint canvasPoint = event->position().toPoint();
        emit requestPixelChange(canvasPoint, currentColor, width(), height());
    }
}
void DrawingCanvas::receiveCurrentImage(const QImage& image) {
    currentImage = image;
}

//trigers paintevent which will draw
void DrawingCanvas::updateDrawing(){
    update();
}

void DrawingCanvas::colorChanged(QColor newColor) {
    currentColor = newColor;
}



