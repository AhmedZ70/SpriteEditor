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

private:

    /// The Sprite object containing all frames
    Sprite sprite;

    /// The current color selected for drawing
    QColor currentColor;

    /// The index of the current frame being edited
    int currentFrameIndex;

    /// @brief Draws a pixel at the specified point on the current frame.
    /// @param point The point where the pixel should be drawn.
    void drawToImage(const QPoint &point);

public:

    /// @brief Constructs a DrawingCanvas widget.
    /// @param parent The parent widget. Default is nullptr for top-level widget.
    explicit DrawingCanvas(QWidget *parent = nullptr);

    /// @brief Returns the total number of frames in the sprite.
    /// @return The frame count as an integer.
    int getFrameCount() const;

    /// @brief Retrieves a thumbnail image for a specified frame index.
    /// @param index The index of the frame.
    /// @return A QImage representing the thumbnail of the frame.
    QImage getFrameThumbnail(int index);

    /// @brief Sets the current frame index to the specified value.
    /// @param index The index of the frame to make current.
    void setCurrentFrameIndex(int index);

    /// @brief Sets the current drawing color.
    /// @param color The QColor to set as the current drawing color.
    void setCurrentColor(const QColor &color);

    /// @brief Adds a new frame to the sprite.
    void addNewFrame();

protected:

    /// @brief Overridden paint event handler to draw the canvas content.
    /// @param event The paint event.
    void paintEvent(QPaintEvent *event) override;

    /// @brief Overridden mouse move event handler for drawing on the canvas.
    /// @param event The mouse event.
    void mouseMoveEvent(QMouseEvent *event) override;

    /// @brief Overridden mouse press event handler to start drawing on the canvas.
    /// @param event The mouse event.
    void mousePressEvent(QMouseEvent *event) override;

signals:

    /// @brief Signal emitted when the drawing on the canvas has changed.
    void drawingChanged();
};

#endif // DRAWINGCANVAS_H
