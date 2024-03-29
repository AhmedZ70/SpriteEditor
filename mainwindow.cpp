#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <iostream>
#include <QColorDialog>
#include <QColor>
#include "spriteModel.h"
#include <QInputDialog>
#include "dimensionsdialog.h"
#include <QTimer>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    spriteEditor = new SpriteModel(this);
    canvas = new DrawingCanvas(this);

    canvas->setGeometry(ui->drawPanel->geometry());
    delete ui->drawPanel;
    ui->drawPanel = canvas;

    connect(canvas, &DrawingCanvas::requestPixelChange, spriteEditor, &SpriteModel::updatePixel);
    connect(spriteEditor, &SpriteModel::spriteChanged, canvas, &DrawingCanvas::updateDrawing);
    connect(canvas, &DrawingCanvas::requestCurrentImage, this, &MainWindow::provideCurrentImage);

    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::onAddFrameButtonClicked);
    connect(ui->deleteFrameButton, &QPushButton::clicked, this, &MainWindow::onDeleteFrameButtonClicked);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::onEraserButtonClicked);
    connect(ui->pencilButton, &QPushButton::clicked, this, &MainWindow::onPencilButtonClicked);
    connect(ui->duplicateFrameButton, &QPushButton::clicked, this, &MainWindow::onDuplicateFrameButtonClicked);
    connect(ui->colorPicker, &QPushButton::clicked, this, &MainWindow::onColorPickerClicked);

    connect(this, &MainWindow::spriteUpdated, this, &MainWindow::updateFrameList);
    connect(ui->framesList, &QListWidget::itemClicked, this, &MainWindow::OnFrameListWidgetItemClicked);
    connect(this, &MainWindow::colorSelected, canvas, &DrawingCanvas::colorChanged);
    connect(this, &MainWindow::dimensionsSet, spriteEditor, &SpriteModel::setInitialFrame);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveClicked);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadClicked);
    connect(this, &MainWindow::Load, spriteEditor, &SpriteModel::load);
    connect(this, &MainWindow::Save, spriteEditor, &SpriteModel::save);

    connect(spriteEditor, &SpriteModel::loaded, this, &MainWindow::updateFrameList);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrameList() {
    ui->framesList->clear();
    for (int i = 0; i < spriteEditor->getFrameCount(); ++i) {
        QImage thumbnail = spriteEditor->getFrameThumbnail(i);

        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(QPixmap::fromImage(thumbnail)));
        item->setData(Qt::UserRole, QVariant::fromValue(i));
        ui->framesList->addItem(item);
    }
}

void MainWindow::provideCurrentImage() {
    QImage image = spriteEditor->getCurrentFrameImage(spriteEditor->getCurrentFrameIndex());
    canvas->receiveCurrentImage(image.scaled(canvas->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
}

void MainWindow::OnFrameListWidgetItemClicked(QListWidgetItem *item) {
    int frameIndex = item->data(Qt::UserRole).toInt();
    spriteEditor->setCurrentFrameIndex(frameIndex);
    emit spriteUpdated();
}

void MainWindow::onAddFrameButtonClicked() {
    spriteEditor->addFrame();
    emit spriteUpdated();
}

void MainWindow::onDeleteFrameButtonClicked()
{
    spriteEditor->deleteFrame();
    emit spriteUpdated();
}

void MainWindow::onEraserButtonClicked(){
    ui->eraserButton->setEnabled(false);
    ui->pencilButton->setEnabled(true);
    emit colorSelected(QColor(Qt::transparent));
}

void MainWindow::onPencilButtonClicked(){
    ui->pencilButton->setEnabled(false);
    ui->eraserButton->setEnabled(true);
    if(lastUsedColor==""){
        lastUsedColor = QColor(Qt::red);
    }
    emit colorSelected(QColor(lastUsedColor));
}

void MainWindow::onDuplicateFrameButtonClicked(){
    spriteEditor->duplicateFrame();
    emit spriteUpdated();
}

void MainWindow::onColorPickerClicked(){

    QColor selectedColor = QColorDialog::getColor(Qt::white, this, "Select color");
    lastUsedColor = selectedColor;
    emit colorSelected(selectedColor);
}
// void MainWindow::StartProgram(){
//     ui->addFrameButton->setEnabled(true);
//     ui->duplicateFrameButton->setEnabled(true);
//     ui->deleteFrameButton->setEnabled(false);
//     ui->undoButton->setEnabled(false);

// }
// Assuming `frameListWidget` is your QListWidget and `sprite` is your Sprite instance


// void MainWindow::on_pencilButton_clicked(){
//     emit on_Pencil_Clicked_Signal();
//     std::cout << "Pencil Clicked signal sent" << std::endl;
// }

// void MainWindow::on_eraserButton_clicked(){
//     emit on_Eraser_Clicked_Signal();
//     std::cout << "OnEraser Clicked signal sent" << std::endl;
// }

// void MainWindow::on_FPS_clicked(){
//     emit on_FPS_Clicked_Signal();
//     std::cout << "OnFPS Clicked signal sent" << std::endl;

// }

// void MainWindow::on_SetSize_clicked(){
//     emit on_SetSize_Clicked_Signal();
//     std::cout << "OnSetSize signal sent" << std::endl;

// }

// void MainWindow::on_actionLoad_clicked(){
//     emit on_Open_Clicked_Signal();
//     std::cout << "OnOpen Clicked signal sent" << std::endl;

// }

// void MainWindow::on_actionSave_clicked(){
//     emit on_Save_Signal();
//     std::cout << "OnSave Clicked signal sent" << std::endl;
// }

// void MainWindow::on_playSpriteButton_clicked(){
//     emit on_PlayBack_Signal();
//     std::cout << "OnPlayBack Clicked signal sent" << std::endl;
// }
// void MainWindow::on_duplicateFrameButton_clicked(){
//     emit on_duplicateFrameButtonClicked_Signal();
//     std::cout << "Duplicate Frame Button Clicked signal sent" << std::endl;
// }


void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
        // Use QTimer::singleShot to defer showing the dialog
        QTimer::singleShot(0, this, [this]() {
            dimensionsDialog dialog(this);
            if (dialog.exec() == QDialog::Accepted) {
                int width = dialog.getWidth();
                int height = dialog.getHeight();
                emit dimensionsSet(width, height);
            }
        });


}

void MainWindow:: onSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Load Sprite"), "", tr("SSP Files (*.ssp)"));
    if (!fileName.isEmpty()) {
        emit Save(fileName);
    }
}
void MainWindow:: onLoadClicked()
{
        QString fileName = QFileDialog::getOpenFileName(this, tr("Load Sprite"), "", tr("SSP Files (*.ssp)"));
        if (!fileName.isEmpty()) {
            emit Load(fileName);
        }
  }

