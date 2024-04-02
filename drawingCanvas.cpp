#include "drawingCanvas.h"
using namespace std;

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name sprite cpp file for assignment8
 * This cpp file contains the method implementations for choosing the width and height of the sprite
 * The user will choose the dimensions by a popup at the start of the program execution
 *
 * File and software practice principles reviewed by Joe Corbeil.
*/

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent), currentColor(Qt::red){

    // Starting color is set to red
    setAttribute(Qt::WA_StaticContents);
    enterDrawingMode();
}

void DrawingCanvas::paintEvent(QPaintEvent *) {
    emit requestCurrentImage();
    QPainter painter(this);

    // Defines the event to be painted by size and color
    int tileSize = 10;
    QColor color1(220, 220, 220);
    QColor color2(255, 255, 255);

    // Sets background to a rectangle
    QRect background = this->rect();

    // Nested for-loop to draw colors to correct location
    for (int y = 0; y < background.height(); y += tileSize) {
        for (int x = 0; x < background.width(); x += tileSize) {
            QRect tileRect(x, y, tileSize, tileSize);
            QColor tileColor = ((x / tileSize) % 2 == (y / tileSize) % 2) ? color1 : color2;
            painter.fillRect(tileRect, tileColor);
        }
    }

    // Draws image if the current image is not null
    if (!currentImage.isNull()) {
        painter.drawImage(rect(), currentImage);
    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {

        // Sets the current point to a new point
        const QPoint canvasPoint = event->position().toPoint();

        // Calls correct signal
        emit requestPixelChange(canvasPoint, currentColor, width(), height());
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit drawingStarted();

        // Sets currnet point to a new point
        const QPoint canvasPoint = event->position().toPoint();

        // Calls correct signal
        emit requestPixelChange(canvasPoint, currentColor, width(), height());

    }
}

void DrawingCanvas::receiveCurrentImage(const QImage& image) {
    currentImage = image;
}

void DrawingCanvas::updateDrawing(){
    // trigers paintevent which will draw
    update();
}

void DrawingCanvas::colorChanged(QColor newColor) {
    currentColor = newColor;
}

void DrawingCanvas::enterDrawingMode() {

    // Sets cursor to the pen mouse png
    QPixmap cursorPixmap(":/icons/penMouse.png");
    QPixmap scaledCursorPixmap = cursorPixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Creates cursor
    QCursor drawingCursor(scaledCursorPixmap, 0, scaledCursorPixmap.height() );

    // Sets drawing cursor
    setCursor(drawingCursor);
}

void DrawingCanvas::erasingMode() {

     // Sets cursor to the eraser png
    QPixmap cursorPixmap(":/icons/eraser.png");
    QPixmap scaledCursorPixmap = cursorPixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Creates cursor
    QCursor erasingCursor(scaledCursorPixmap, 0, scaledCursorPixmap.height() );

    // Sets erasing cursor
    setCursor(erasingCursor);
}



