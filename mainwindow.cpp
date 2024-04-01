#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
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

    ui->fpsSlider->setMinimum(1);
    ui->fpsSlider->setMaximum(24);
    ui->fpsSlider->setValue(16);

    canvas->setGeometry(ui->drawPanel->geometry());
    delete ui->drawPanel;
    ui->drawPanel = canvas;
    ui->framesList->setIconSize(QSize(64, 64));
    ui->framesList->setFixedWidth(128);
    updateFpsLabel(ui->fpsSlider->value());


    connect(canvas, &DrawingCanvas::requestPixelChange, spriteEditor, &SpriteModel::updatePixel);
    connect(spriteEditor, &SpriteModel::spriteChanged, canvas, &DrawingCanvas::updateDrawing);
    connect(canvas, &DrawingCanvas::requestCurrentImage, this, &MainWindow::provideCurrentImage);

    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::onAddFrameButtonClicked);
    connect(ui->deleteFrameButton, &QPushButton::clicked, this, &MainWindow::onDeleteFrameButtonClicked);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::onEraserButtonClicked);
    connect(ui->pencilButton, &QPushButton::clicked, this, &MainWindow::onPencilButtonClicked);
    connect(ui->duplicateFrameButton, &QPushButton::clicked, this, &MainWindow::onDuplicateFrameButtonClicked);
    connect(ui->colorPicker, &QPushButton::clicked, this, &MainWindow::onColorPickerClicked);

    //connect(this, &MainWindow::spriteUpdated, spriteEditor, &SpriteModel::setPlaySpriteMembers);

    connect(this, &MainWindow::spriteUpdated, this, &MainWindow::updateFrameList);
    connect(ui->framesList, &QListWidget::itemClicked, this, &MainWindow::OnFrameListWidgetItemClicked);
    connect(this, &MainWindow::colorSelected, canvas, &DrawingCanvas::colorChanged);
    connect(this, &MainWindow::dimensionsSet, spriteEditor, &SpriteModel::setInitialFrame);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveClicked);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadClicked);
    connect(this, &MainWindow::Load, spriteEditor, &SpriteModel::load);
    connect(this, &MainWindow::Save, spriteEditor, &SpriteModel::save);


    connect(ui->playSpriteButton, &QPushButton::clicked, spriteEditor, &SpriteModel::playAnimation);

    connect(spriteEditor, &SpriteModel::loaded, this, &MainWindow::updateFrameList);
    connect(this, &MainWindow::Drawing, canvas,&DrawingCanvas::enterDrawingMode);
    connect(this, &MainWindow::Erasing, canvas,&DrawingCanvas::erasingMode);

    connect(canvas, &DrawingCanvas::drawingStarted, spriteEditor, &SpriteModel::onDrawingStarted);
    connect(ui->undoButton, &QPushButton::clicked, spriteEditor, &SpriteModel::undo);
    connect(ui->redoButton, &QPushButton::clicked, spriteEditor, &SpriteModel::redo);

    ui-> pencilButton->setIcon(QIcon(":/icons/penIcon.png"));
    ui-> eraserButton->setIcon(QIcon(":/icons/eraserIcon.png"));

    //Connect the FPS slider to
    connect(ui->fpsSlider, &QSlider::valueChanged, [&](int value) {
        std::cout << "Slider value changed to:" << value;
        spriteEditor->setFPS(value);
    });
    connect(ui->fpsSlider, &QSlider::valueChanged, this, &MainWindow::updateFpsLabel);


    QTimer::singleShot(0, this, [this]() {
        ui->pencilButton->click();
    });

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
    if (image.isNull()) {
        qDebug() << "Current frame image is null";
        return;
    }
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
    emit Erasing();
}

void MainWindow::onPencilButtonClicked(){
    ui->pencilButton->setEnabled(false);
    ui->eraserButton->setEnabled(true);
    if(lastUsedColor==""){
        lastUsedColor = QColor(Qt::red);
    }
    emit colorSelected(QColor(lastUsedColor));
    emit Drawing();
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

void MainWindow::on_playSpriteButton_clicked(){
    emit playSpriteClicked();
}

void MainWindow::updateFpsLabel(int value) {
    ui->fpsValueLabel->setText(QString::number(value) + " FPS");
}

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

