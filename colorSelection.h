#ifndef COLORSELECTION_H

#define COLORSELECTION_H

#include <QObject>
#include<QColorDialog>
#include<QColor>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name colorSelection .h file for assignment8
 * This .h file contians the methods need for user to select a color in the sprite editor
 * The user will choose the color by clicking the 'Color Selection' button in the Sprite Editor
*/
class ColorSelection : public QObject
{
    Q_OBJECT

public:
    /// @brief Pops a window containing a color palette
    explicit ColorSelection(QObject *parent = nullptr);

    /// @brief Allows the user to select a color from the color palette and sets the color to the currentColor variable
    /// @param initialColor the initial color which is always white
    /// @return The color that was selected
    QColor selectColor(const QColor &initialColor = Qt::white);

    /// @brief Returns the currentColor variable
    QColor getCurrentColor();

private:
    /// @brief Dialog that pops up to show color palette
    QColorDialog *colorDialog;

    /// @brief Current color that is being used by drawing
    QColor currentColor;
};
#endif // COLORSELECTION_H
