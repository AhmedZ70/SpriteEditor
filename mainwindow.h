#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "drawingcanvas.h"
#include "spriteModel.h"

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
    // void on_Pencil_Clicked_Signal();
    // void on_Eraser_Clicked_Signal();
    // void on_Color_Clicked_Signal();
    // void on_NewFrame_ClickedSignal();
    // void on_FPS_Clicked_Signal();
    // void on_SetSize_Clicked_Signal();
    // void on_Open_Clicked_Signal();
    // void on_Save_Signal();
    // void on_PlayBack_Signal();
    // void on_addFrameButton_Signal();
    // void on_duplicateFrameButtonClicked_Signal();

    void colorSelected(QColor selectedColor);
    void spriteUpdated();
    void dimensionsSet(int width, int height);


private slots:
    // void StartProgram();
    // void on_pencilButton_clicked();
    // void on_eraserButton_clicked();
    // void on_FPS_clicked();
    // void on_SetSize_clicked();
    // void on_actionLoad_clicked();
    // void on_actionSave_clicked();
    // void on_playSpriteButton_clicked();
    // void on_duplicateFrameButton_clicked();


    void onAddFrameButtonClicked();
    void onDeleteFrameButtonClicked();
    void onEraserButtonClicked();
    void onPencilButtonClicked();
    void onDuplicateFrameButtonClicked();
    void onColorPickerClicked();
    void updateFrameList();
    void OnFrameListWidgetItemClicked(QListWidgetItem *item);
    void provideCurrentImage();

private:
    Ui::MainWindow *ui;
    DrawingCanvas *canvas;
    SpriteModel *spriteEditor;
    QColor lastUsedColor;

protected:
    void showEvent(QShowEvent *event) override;

};
#endif // MAINWINDOW_H
