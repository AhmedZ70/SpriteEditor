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

    /// @brief Instance variable of a sprite
    Sprite sprite;

    /// @brief Current frame of the sprite instance
    int currentFrameIndex;

    /// @brief current frames ower second
    int fps;

    /// @brief Width of the frames of the sprite instance
    int spriteWidth;

    /// @brief Height of the frames of the sprite instance
    int spriteHeight;

    /// @brief Vector of all of the frames
    std::vector<Frame> allFrames;

    /// @brief Tracks the current frame index for playback
    int currentPlaybackFrameIndex = 0;

    /// @brief Manages the playback timing
    QTimer* playbackTimer = nullptr;

    /// @brief Manages the playback popups
    QDialog* playbackPopup = nullptr;

public:

    /// @brief Constructor for sprite model
    /// @param Sets the QObject provided to a nullptr
    explicit SpriteModel(QObject *parent = nullptr);

    /// @brief Plays the sprite animation
    void playAnimation();

    /// @brief Plays an animation of the spirte at its true pixel size
    void showTrueSize();

    /// @brief Destructor for Sprite Model class
    ~SpriteModel();

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
    /// @param New current fps
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

    /// @brief Retrieves the frame at the specified index
    /// @param Index at which the frame should be return at
    /// @return The current frame
    Frame& getCurrentFrame(int index);

    /// @brief Retrieves all the frames
    /// @return Presents all the frames in a vector class
    std::vector<Frame> getAllFrames();

signals:

    /// @brief Signal that notifies that the sprite pixels have been changed.
    void spriteChanged();

    /// @brief Signal that notifies that a frame has been added to the sprite instance.
    void frameAdded();

    /// @brief Signal that notifies that a frame has been duplicated in the sprite instance.
    void frameDuplicated();

    /// @brief Signal that notifies that a sprite file has been loaded
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

    /// @brief Signifies that a drawing has started
    void onDrawingStarted();

    /// @brief Stack to hold all the undo calls
    void undo();

    /// @brief Stack to hold all the redo calls
    void redo();
};

#endif // SPRITEMODEL_H
