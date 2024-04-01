#ifndef COLORSELECTION_H

#define COLORSELECTION_H

#include <QObject>
#include<QColorDialog>
#include<QColor>

// /**
//  * @author Joseph Corbeil, Raj Reddy, Johnny Song, Joel Ronca, Ezekiel Jaramillo, and Ahmed Zahran
//  * @date March. 26, 2024
//  * @name colorSelection h file for Assignment8
//  * This header file defines the variables/methods choosing a color.
//  * The user will choose the colors from a window which shows a color palette.
// */
class ColorSelection : public QObject
{
    Q_OBJECT

public:
    /// @brief Pops a window containing a color palette
    explicit ColorSelection(QObject *parent = nullptr);
    /// @brief Allows the user to select a color from the color palette and sets the color to the currentColor variable
    /// @param initialColor the initial color which is always white
    /// @return the color that was selected
    QColor selectColor(const QColor &initialColor = Qt::white);
    /// @brief Returns the currentColor variable
    QColor getCurrentColor();

private:
    /// @brief Dialog that pops up to show color palette
    QColorDialog *colorDialog;
    // Current color that is being used by drawing
    QColor currentColor;
    /// @brief Changes the current color to a new current color
    void setCurrentColor();
};



#endif // COLORSELECTION_H
