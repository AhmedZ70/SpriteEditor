#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QString>
#include "drawingcanvas.h"
#include "spriteModel.h"

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name sprite h file for assignment8
 * This h file contains the event handlers for the buttons in the UI
*/
QT_BEGIN_NAMESPACE
namespace Ui {

    class MainWindow;
} 
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /// @brief Main constuctor for the Main Window class
    MainWindow(QWidget *parent = nullptr);

    /// @brief Destructor for the Main Window class
    ~MainWindow();

signals:

    /// @brief Signal that indicates whenever sprite was clicked
    void playSpriteClicked();

    /// @brief Signal to show the sprite play back at the true size pixel to pixel
    void trueSizeClicked();

    /// @brief Signal that sends the color selected from the color palette
    void colorSelected(QColor selectedColor);

    /// @brief Signal for updating the view of the sprite
    void spriteUpdated();

    /// @brief Signal that emits the width and height
    void dimensionsSet(int width, int height);

    /// @brief Signal that triggers the save method
    /// @param Filename to which the sprite is saved to
    void Save(QString fileName);

    /// @brief Signal that triggers the load method
    /// @param Filename to load to sprite
    void Load(QString fileName);

    /// @brief Signal sent to enter drawing mode
    void Drawing();

    /// @brief Signal sent to enter erasing mode
    void Erasing();

    /// @brief Signal that emits the new value of the FPS
    /// @param takes in an int
    void valueChanged(int);

    /// @brief Signal that refreshes the play sprite with new fps
    void updatePlaySprite();

private slots:

    /// @brief Emits a signal to show the play back at the true size of the pixels
    void onShowTrueSizeClicked();

    /// @brief Emits signal for adding frame
    void onAddFrameButtonClicked();

    /// @brief Emits signal for deleting a frame
    void onDeleteFrameButtonClicked();

    /// @brief Emits signal for entering eraser mode
    void onEraserButtonClicked();

    /// @brief Emits signal for entering pencil mode
    void onPencilButtonClicked();

    /// @brief Emits signal for duplicating frame
    void onDuplicateFrameButtonClicked();

    /// @brief Emits signal for opening color palette
    void onColorPickerClicked();

    /// @brief Emits signal for updating the list of frames
    void updateFrameList();

    /// @brief Emits signal when the list selection of frames is clicked
    /// @param Takes an a pointer to show what frames to select from
    void OnFrameListWidgetItemClicked(QListWidgetItem *item);

    /// @brief Receives image and displays it
    void provideCurrentImage();

    /// @brief Emits save signal and provides file name
    void onSaveClicked();

    /// @brief Emits load signal and provides file name
    void onLoadClicked();

    /// @brief Emits the label updater for the FPS
    /// @param int value to update the FPS to
    void updateFpsLabel(int value);

private:

    /// @brief UI responsible of the view
    Ui::MainWindow *ui;

    /// @brief Canvas responsible for allowing the user to draw
    /// @return An instance of a Drawing Canvas object
    DrawingCanvas *canvas;

    /// @brief Model that handles the logic of the Sprite Editor
    /// @return An instance of the a Sprite Model object
    SpriteModel *spriteEditor;

    /// @brief Last color chosen
    /// @return An instance of Qts QColor object
    QColor lastUsedColor;

protected:

    /// @brief Opening dialog for choosing the width and height of the document
    /// @param Event to show and will override any other events
    void showEvent(QShowEvent *event) override;

};
#endif // MAINWINDOW_H
