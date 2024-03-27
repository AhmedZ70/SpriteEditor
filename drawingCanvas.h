#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "frame.h"
#include "sprite.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name drawingCanvas h file for assignment8
 * This h file contains the outlined methods for use within the DrawingCanvas.
 * DrawingCanvas is in-charge of the pixel drawing for our Sprite Editor
*/

class DrawingCanvas : public QWidget {
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    int getFrameCount() const;
    QImage getFrameThumbnail(int index);
    void setCurrentFrameIndex(int index);
    void setCurrentColor(const QColor &color);
    void addNewFrame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Sprite sprite;
    QColor currentColor;
    int currentFrameIndex;

    void drawToImage(const QPoint &point);

signals:
    void drawingChanged(); // Signal to update UI elements related to frame changes
};

#endif // DRAWINGCANVAS_H
