#ifndef COLORSELECTION_H

#define COLORSELECTION_H

#include <QObject>
#include<QColorDialog>
#include<QColor>

class ColorSelection : public QObject
{
    Q_OBJECT

public:

    explicit ColorSelection(QObject *parent = nullptr);

    QColor selectColor(const QColor &initialColor = Qt::white);

    QColor getCurrentColor();

private:
    QColorDialog *colorDialog;
    QColor currentColor;
    void setCurrentColor();
};



#endif // COLORSELECTION_H
