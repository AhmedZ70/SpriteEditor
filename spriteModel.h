#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

//#include "playSprite.h"
#include "sprite.h"
#include <QObject>

/**
 * @author Joseph Corbeil, Raj Reddy, Johnny Song, Joel Ronca, Ezekiel Jaramillo, and Ahmed Zahran
 * @date March. 26, 2024
 * @name spriteModel.h file for Sprite Editor
 * This header file defines the variables/methods for the SpriteModel class which is the model class for sprite
*/

class SpriteModel: public QObject {

    Q_OBJECT

public:

    explicit SpriteModel(QObject *parent = nullptr);

    // may need to add default constructor and destructor
    //SpriteModel();
    //~SpriteModel();

public slots:
    void colorChanged();
    void frameSizeSet(int width, int height);
    void frameDeleted(int frame);
    void frameAdded();
    void Duplicatd();
    void undo();
    void redo();




private:

    // object named sprite which is an instance of the Sprite class
    Sprite sprite;

    // object named animation which is an instance of the PlaySprite class
    //PlaySprite animation;


    /// @brief adds a frame for the sprite
    /// @param the frame to be added
    void addFrame(Frame newFrame);

    /// @brief sets a frame for the sprite
    /// @param frame is the frame to be set to
    void setFrame(Frame frame);

    /// @brief removes a frame for the sprite
    /// @param deletedFrame is the frame to be deleted
    void removeFrame(Frame deletedFrame);

    /// @brief setter method to set a sprite, will be void
    /// @param newSprite is the sprite to be set to
    void setSprite(Sprite newSprite);

    /// @brief getter method for the FPS
    /// @return will return the FPS
    int getFramesPerSecond();


};


#endif // SPRITEMODEL_H
