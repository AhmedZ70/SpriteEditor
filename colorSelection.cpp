#include "colorSelection.h"

ColorSelection::ColorSelection(QObject *parent)
    : QObject(parent), colorDialog(new QColorDialog())
{

    colorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
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
