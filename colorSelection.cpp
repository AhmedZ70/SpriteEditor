#include "colorSelection.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name colorSelection .cpp file for assignment8
 * This .cpp file contians the methods implementations needed for the user to select a color in the sprite editor
 * The user will choose the color by clicking the 'Color Selection' button in the Sprite Editor
 *
 * File and software practice principles reviewed by Raj Reddy.
*/

ColorSelection::ColorSelection(QObject *parent)
    : QObject(parent), colorDialog(new QColorDialog())
{
    // Sets the alpha channel in the color dialog
    colorDialog->setOption(QColorDialog::ShowAlphaChannel, true);

    // Sets the current color as a default with the alpha always staying at 255
    currentColor.setRgb(255,255,255,255);
}

QColor ColorSelection::selectColor(const QColor &initialColor)
{
    // Set the initial color of the dialog
    colorDialog->setCurrentColor(initialColor);

    // Set new Color
    if (colorDialog->exec() == QColorDialog::Accepted){
        QColor newColor = colorDialog->currentColor();
        currentColor = newColor;
        return newColor;

    }
    else
        return initialColor;
}
