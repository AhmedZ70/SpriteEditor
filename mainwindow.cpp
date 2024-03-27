#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QColorDialog>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartProgram(){
    ui->addFrameButton->setEnabled(true);
    ui->duplicateFrameButton->setEnabled(true);
    ui->deleteFrameButton->setEnabled(false);
    ui->undoButton->setEnabled(false);

}

void MainWindow::on_addFrameButton_clicked(){
    emit on_addFrameButton_Signal();
    std::cout << "On add Frame Button signal sent" << std::endl;

}

void MainWindow::on_pencilButton_clicked(){
    emit on_Pencil_Clicked_Signal();
    std::cout << "Pencil Clicked signal sent" << std::endl;
}

void MainWindow::on_eraserButton_clicked(){
    emit on_Eraser_Clicked_Signal();
    std::cout << "OnEraser Clicked signal sent" << std::endl;
}

void MainWindow::on_FPS_clicked(){
    emit on_FPS_Clicked_Signal();
    std::cout << "OnFPS Clicked signal sent" << std::endl;

}

void MainWindow::on_SetSize_clicked(){
    emit on_SetSize_Clicked_Signal();
    std::cout << "OnSetSize signal sent" << std::endl;

}

void MainWindow::on_actionLoad_clicked(){
    emit on_Open_Clicked_Signal();
    std::cout << "OnOpen Clicked signal sent" << std::endl;

}

void MainWindow::on_actionSave_clicked(){
    emit on_Save_Signal();
    std::cout << "OnSave Clicked signal sent" << std::endl;
}

void MainWindow::on_playSpriteButton_clicked(){
    emit on_PlayBack_Signal();
    std::cout << "OnPlayBack Clicked signal sent" << std::endl;
}
void MainWindow::on_duplicateFrameButton_clicked(){
    emit on_duplicateFrameButtonClicked_Signal();
    std::cout << "Duplicate Frame Button Clicked signal sent" << std::endl;
}
void MainWindow::on_colorPicker_clicked(){

    QColor selectedColor = QColorDialog::getColor(Qt::white, this, "Select color");
    emit colorSelected(selectedColor);
    std::cout <<"Color selected and signal sent" << std::endl;
}
