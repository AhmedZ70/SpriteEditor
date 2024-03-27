#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <iostream>
#include "DrawingCanvas.h"
#include <QColorDialog>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas = new DrawingCanvas(this);
    canvas->setGeometry(ui->drawPanel->geometry());
    delete ui->drawPanel;
    ui->drawPanel = canvas;
    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::onAddFrameButtonClicked);
    connect(this, &MainWindow::spriteUpdated, this, &MainWindow::updateFrameList);
    connect(ui->framesList, &QListWidget::itemClicked, this, &MainWindow::OnFrameListWidgetItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrameList() {
    ui->framesList->clear(); // Clear the existing items
    for (int i = 0; i < canvas->getFrameCount(); ++i) {
        QImage thumbnail = canvas->getFrameThumbnail(i);

        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(QPixmap::fromImage(thumbnail)));
        item->setData(Qt::UserRole, QVariant::fromValue(i)); // Store the frame index
        ui->framesList->addItem(item);
    }
}

void MainWindow::OnFrameListWidgetItemClicked(QListWidgetItem *item) {
    int frameIndex = item->data(Qt::UserRole).toInt();
    canvas->setCurrentFrameIndex(frameIndex);
}

void MainWindow::onAddFrameButtonClicked() {
    canvas->addNewFrame();
    emit spriteUpdated();
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
// void MainWindow::on_colorPicker_clicked(){

//     QColor selectedColor = QColorDialog::getColor(Qt::white, this, "Select color");
//     emit colorSelected(selectedColor);
//     std::cout <<"Color selected and signal sent" << std::endl;
// }
