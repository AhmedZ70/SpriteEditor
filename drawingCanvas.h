#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStack>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name drawingCanvas h file for assignment8
 * This h file contains the outline methods used to draw
*/
class DrawingCanvas : public QWidget {
    Q_OBJECT

private:

    /// @brief Current color chosen to draw with
    QColor currentColor;

    /// @brief Image representing a frame
    QImage currentImage;

public:

    /// @brief Constructor that sets by default the current color as red
    /// @param Sets the QWidget to a nullpt
    explicit DrawingCanvas(QWidget *parent = nullptr);

protected:

    /// @brief Draws a checkboard pattern with white and gret that represents empty
    /// @param Paints the provided event and overrides any other events
    void paintEvent(QPaintEvent *event) override;

    /// @brief Event taht sends a signal that the mouse has been moved
    /// @param MouseMoveEvent that should be shown and overrides any other events
    void mouseMoveEvent(QMouseEvent *event) override;

    /// @brief Event that sends a signal that the mouse has been pressed
    /// @param MouseMoveEvent that should be shown and overrides any other events
    void mousePressEvent(QMouseEvent *event) override;


signals:

    /// @brief Signal that indicates that a pixel has been chosen to be colored
    /// @param Point that the user clicked (pixel)
    /// @param Color taht the user chose to paint the pixel
    /// @param Width of the point
    /// @param Height of the point
    void requestPixelChange(const QPoint& point, const QColor& color, int canvasWidth, int canvasHeight);

    /// @brief Signal that requests an update of the new image
    void requestCurrentImage();

    /// @brief Signal to start the drawing
    void drawingStarted();

public slots:
    /// @brief Changes the current color to a new one selected by the user
    void colorChanged(QColor newColor);

    /// @brief Triggers the paint event which updates the drawing shown
    void updateDrawing();

    /// @brief Updates the current image
    /// @param Image to return at that frame
    void receiveCurrentImage(const QImage& image);

    /// @brief Changes the icon of the cursor to a pencil and enters drawing mode
    void enterDrawingMode();

    /// @brief Changes the icon of the cursor to an eraser and enters erasing mode
    void erasingMode();
};

#endif // DRAWINGCANVAS_H
