#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>


class DrawingCanvas : public QWidget {
    Q_OBJECT

private:
    QColor currentColor;
    void drawToImage(const QPoint &point);
    QImage currentImage;

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void drawingChanged();
    void requestPixelChange(const QPoint& point, const QColor& color, int canvasWidth, int canvasHeight);
    void requestCurrentImage();

public slots:
    void colorChanged(QColor newColor);
    void updateDrawing();
    void receiveCurrentImage(const QImage& image);
    void enterDrawingMode();
    void erasingMode();
};

#endif // DRAWINGCANVAS_H
