#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QObject>
#include "sprite.h" // Assuming Sprite class is defined elsewhere

class SpriteModel : public QObject {
    Q_OBJECT

public:
    explicit SpriteModel(QObject *parent = nullptr);

    // Methods to interact with the sprite
    void addFrame();
    void duplicateFrame();
    void deleteFrame();
    QImage getCurrentFrameImage(size_t index);
    int getFrameCount() const;
    QImage getFrameThumbnail(size_t index);
    int getCurrentFrameIndex() const;
    void setCurrentFrameIndex(size_t index);
    void drawPixel(const QPoint& position, const QColor& color);

signals:
    // Signals to notify changes in the sprite
    void spriteChanged();
    void frameAdded();
    void frameDuplicated();

public slots:
         void updatePixel(const QPoint& position, const QColor& color, int width, int height);
         void setInitialFrame(int width, int height);

private:
    Sprite sprite; // The Sprite object that holds the frame data
    int currentFrameIndex;
    int spriteWidth;
    int spriteHeight;


};

#endif // SPRITEMODEL_H
