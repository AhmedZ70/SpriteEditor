#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class Sprite : public QWidget {
    Q_OBJECT

public:
    explicit Sprite(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QImage image;

    void drawPixel(const QPoint &position);
};

#endif // SPRITE_H
