#include "drawingCanvas.h"
using namespace std;
DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent), currentColor(Qt::red){
    setAttribute(Qt::WA_StaticContents);
}

void DrawingCanvas::paintEvent(QPaintEvent *) {
    emit requestCurrentImage();
    QPainter painter(this);
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



