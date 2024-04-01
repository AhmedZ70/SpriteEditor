#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QTimer>

#include <QVBoxLayout>

#include "sprite.h"
#include "playSprite.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name sprite h file for assignment8
 * This h file contains the outlined methods for use within a sprite.
 * A sprite is essentially a collection of frames that can be animated.
*/

class SpriteModel : public QObject {
    Q_OBJECT

private:
    // Instance variable of a sprite
    Sprite sprite;

    // Current frame of the sprite instance
    int currentFrameIndex;

    // current frames ower second
    int fps;

    // Width of the frames of the sprite instance
    int spriteWidth;

    // Height of the frames of the sprite instance
    int spriteHeight;

    std::vector<Frame> allFrames; // Consider storing frames as a member if they don't change often
    int currentPlaybackFrameIndex = 0; // Tracks the current frame index for playback
    QTimer* playbackTimer = nullptr; // Manages the playback timing
    QDialog* playbackPopup = nullptr;

public:
    /// @brief Constructor for sprite model
    explicit SpriteModel(QObject *parent = nullptr);

    void playAnimation();

    // ~SpriteModel();

    /// @brief Adds a frame to the the sprite (wrapper).
    void addFrame();

    /// @brief Duplicates a frame to the sprite (wrapper).
    void duplicateFrame();

    /// @brief Deletes a frame from the sprite (wrapper).
    void deleteFrame();

    /// @brief Gets a certain frame (QImage) at an index.
    /// @param size_t index of the wanted frame (QImage)
    /// @return QImage frame from the index
    QImage getCurrentFrameImage(size_t index);

    /// @brief Gets the number of frames of a sprite.
    /// @return int number of frames for a sprite
    int getFrameCount() const;

    /// @brief Sets the fps of the Sprite model
    /// @param new current fps
    void setFPS(int newVal);

    /// @brief Gets the frame thumbnail from a sprite at an index.
    /// @param size_t index of the wanted frame thumbnail
    /// @return QImage the frame thumbnail
    QImage getFrameThumbnail(size_t index);

    /// @brief Gets the index of the current frame of a sprite.
    /// @return int the index
    int getCurrentFrameIndex() const;

    /// @brief Sets the current frame of a sprite at a given index.
    /// @param size_t index to be set
    void setCurrentFrameIndex(size_t index);

    /// @brief Draws a pixel on a frame of a sprite at a position with a given color.
    /// @param QPoint position where the pixel will be drawn
    /// @param QColor color of the pixel to be drawn
    void drawPixel(const QPoint& position, const QColor& color);

    Frame & getCurrentFrame(int index);

    std::vector<Frame> getAllFrames();

signals:
    /// @brief Signal that notifies that the sprite pixels have been changed.
    void spriteChanged();

    /// @brief Signal that notifies that a frame has been added to the sprite instance.
    void frameAdded();

    /// @brief Signal that notifies that a frame has been duplicated in the sprite instance.
    void frameDuplicated();

    void loaded();

public slots:
         void updatePixel(const QPoint& position, const QColor& color, int width, int height);

         void setInitialFrame(int width, int height);

         /// @brief Saves the sprite to a file with a .ssp extension.
         /// @param const QString& fileName The name of the file to save the sprite to
         /// @return bool True if the save was successful, false otherwise
         bool save(const QString& fileName) const;

         /// @brief Loads a sprite from a .ssp file.
         /// @param const QString& fileName The name of the file to load the sprite from
         /// @return std::optional<Sprite> A sprite instance if loading was successful, std::nullopt otherwise
         void load(const QString& fileName);

         void onDrawingStarted();

         void undo();

         void redo();


};

#endif // SPRITEMODEL_H
