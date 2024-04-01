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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

    //Signal that indicates whenever sprite was clicked
    void playSpriteClicked();
    void trueSizeClicked();
    // void on_addFrameButton_Signal();
    // void on_duplicateFrameButtonClicked_Signal();

    // signal that sends the color selected from the color palette
    void colorSelected(QColor selectedColor);
    // signal for updating the view of the sprite
    void spriteUpdated();
    // signal that emits the width and height
    void dimensionsSet(int width, int height);
    // signal that triggers the save method
    void Save(QString fileName);
    // signal that triggers the load method
    void Load(QString fileName);
    // signal sent to enter drawing mode
    void Drawing();
    // signal sent to enter erasing mode
    void Erasing();
    // signal that emits the new value of the FPS
    void valueChanged(int);
    // signal that refreshes the play sprite with new fps
    void updatePlaySprite();

private slots:

    void onShowTrueSizeClicked();
    // emits signal for adding frame
    void onAddFrameButtonClicked();
    // emits signal for deleting a frame
    void onDeleteFrameButtonClicked();
    // emits signal for entering eraser mode
    void onEraserButtonClicked();
    // emits signal for entering pencil mode
    void onPencilButtonClicked();
    // emits signal for duplicating frame
    void onDuplicateFrameButtonClicked();
    // emits signal for opening color palette
    void onColorPickerClicked();
    // emits signal for updating the list of frames
    void updateFrameList();
    // emits signal when the list selection of frames is clicked
    void OnFrameListWidgetItemClicked(QListWidgetItem *item);
    // receives image and displays it
    void provideCurrentImage();
    // emits save signal and provides file name
    void onSaveClicked();
    // emits load signal and provides file name
    void onLoadClicked();

    void updateFpsLabel(int value);

private:
    // UI responsible of the view
    Ui::MainWindow *ui;
    // canva responsible for allowing the user to draw
    DrawingCanvas *canvas;
    // Model that handles the logic of the Sprite Editor
    SpriteModel *spriteEditor;
    // last color chosen
    QColor lastUsedColor;
    // PlaySprite *playSpriteInstance;

protected:
    //Opening dialog for choosing the width and height of the document
    void showEvent(QShowEvent *event) override;

};
#endif // MAINWINDOW_H
