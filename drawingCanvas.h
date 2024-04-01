#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStack>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name sprite h file for assignment8
 * This h file contains the outline methods for choosing the width and height of the sprite
 * The user will choose the dimensions by a popup at the start of the program execution
*/
class DrawingCanvas : public QWidget {
    Q_OBJECT

private:
    // Current color chosen to draw with
    QColor currentColor;

    //void drawToImage(const QPoint &point);
    // Image representing a frame
    QImage currentImage;

  //  bool drawingStarted = false;



public:
    //Constructor that sets by default the current color as red
    explicit DrawingCanvas(QWidget *parent = nullptr);

protected:
    /// @brief Draws a checkboard pattern with white and gret that represents empty
    void paintEvent(QPaintEvent *event) override;
    /// @brief event taht sends a signal that the mouse has been moved
    void mouseMoveEvent(QMouseEvent *event) override;
    /// @brief event that sends a signal that the mouse has been pressed
    void mousePressEvent(QMouseEvent *event) override;


signals:

    //void drawingChanged();
    /// @brief signal that indicates that a pixel has been chosen to be colored
    /// @param point that the user clicked (pixel)
    /// @param color taht the user chose to paint the pixel
    /// @param width of the point
    /// @param height of the point
    void requestPixelChange(const QPoint& point, const QColor& color, int canvasWidth, int canvasHeight);
    /// @brief signal that requests an update of the new image
    void requestCurrentImage();
    void drawingStarted();

public slots:
    /// @brief changes the current color to a new one selected by the user
    void colorChanged(QColor newColor);
    /// @brief Triggers the paint event which updates the drawing shown
    void updateDrawing();
    /// @brief updates the current image
    void receiveCurrentImage(const QImage& image);
    /// @brief changes the icon of the cursor to a pencil and enters drawing mode
    void enterDrawingMode();
    /// @brief changes the icon of the cursor to an eraser and enters erasing mode
    void erasingMode();





};

#endif // DRAWINGCANVAS_H
