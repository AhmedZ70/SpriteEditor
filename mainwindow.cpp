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
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    spriteEditor = new SpriteModel(this);
    canvas = new DrawingCanvas(this);

    initializeHelpTexts();


    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionDuplicate, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionLoad_2, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionPlay_Back, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionSave_2, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionShow_True_Size, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::showHelpDialog);


    ui->fpsSlider->setMinimum(1);
    ui->fpsSlider->setMaximum(30);
    ui->fpsSlider->setValue(16);

    canvas->setGeometry(ui->drawPanel->geometry());
    delete ui->drawPanel;
    ui->drawPanel = canvas;
    ui->framesList->setIconSize(QSize(64, 64));
    ui->framesList->setFixedWidth(128);
    updateFpsLabel(ui->fpsSlider->value());


    connect(canvas, &DrawingCanvas::requestPixelChange, spriteEditor, &SpriteModel::updatePixel);
    connect(spriteEditor, &SpriteModel::spriteChanged, canvas, &DrawingCanvas::updateDrawing);
    connect(spriteEditor, &SpriteModel::spriteChanged, this, &MainWindow::updateFrameList);
    connect(canvas, &DrawingCanvas::requestCurrentImage, this, &MainWindow::provideCurrentImage);

    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::onAddFrameButtonClicked);
    connect(ui->deleteFrameButton, &QPushButton::clicked, this, &MainWindow::onDeleteFrameButtonClicked);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::onEraserButtonClicked);
    connect(ui->pencilButton, &QPushButton::clicked, this, &MainWindow::onPencilButtonClicked);
    connect(ui->duplicateFrameButton, &QPushButton::clicked, this, &MainWindow::onDuplicateFrameButtonClicked);
    connect(ui->colorPicker, &QPushButton::clicked, this, &MainWindow::onColorPickerClicked);

    connect(ui->framesList, &QListWidget::itemClicked, this, &MainWindow::OnFrameListWidgetItemClicked);
    connect(this, &MainWindow::colorSelected, canvas, &DrawingCanvas::colorChanged);
    connect(this, &MainWindow::dimensionsSet, spriteEditor, &SpriteModel::setInitialFrame);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveClicked);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadClicked);
    connect(this, &MainWindow::Load, spriteEditor, &SpriteModel::load);
    connect(this, &MainWindow::Save, spriteEditor, &SpriteModel::save);

    connect(ui->playSpriteButton, &QPushButton::clicked, spriteEditor, &SpriteModel::playAnimation);
    connect(ui->showTrueSizeButton, &QPushButton::clicked, spriteEditor, &SpriteModel::showTrueSize);

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
    QString sliderAndLabelStyleSheet = R"(
    QSlider {
        min-height: 150px;
    }

    QSlider::groove:vertical {
        background: #E0E0E0;
        border: none;
        width: 20px;
        border-radius: 10px;
    }

    QSlider::handle:vertical {
        background: #FFFFFF;
        border: 1px solid #CCCCCC;
        height: 25px;
        width: 20px;
        margin: -2px 0;
        border-radius: 10px;
        position: absolute;
    }

    QSlider::add-page:vertical {
        background: #CCCCCC;
        border-radius: 10px;
    }

    QSlider::sub-page:vertical {
        background: #D6D6D6;
        border-radius: 10px;
    }

    QLabel {
        background: #E0E0E0;
        color: #333333;
        border: none;
        border-radius: 4px;
        font-size: 16px;
        qproperty-alignment: 'AlignCenter';
        min-width: 60px;
    }
)";
    ui->fpsSlider->setStyleSheet(sliderAndLabelStyleSheet);
    ui->fpsValueLabel->setStyleSheet(sliderAndLabelStyleSheet);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeHelpTexts() {
    helpTexts["actionAdd"] = "Adds a new frame to your sprite.";
    helpTexts["actionDelete"] = "Removes the selected frame from your sprite.";
    helpTexts["actionDuplicate"] = "Creates a copy of the selected frame.";
    helpTexts["actionLoad_2"] = "Opens a previously saved srpite.";
    helpTexts["actionPlay_Back"] = "Plays back the current set of frames.";
    helpTexts["actionRedo"] = "Redraws the last segment that was undone.";
    helpTexts["actionSave_2"] = "Saves the current state of your sprite.";
    helpTexts["actionShow_True_Size"] = "Playes-back and shows the actual size of the sprite.";
    helpTexts["actionUndo"] = "Reverses the last segmant drawn in the selected frame.";
}

void MainWindow::showHelpDialog() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        QString actionName = action->objectName();
        QString helpText = helpTexts.value(actionName);
        QMessageBox::information(this, tr("Help for ") + action->text(), helpText);
    }
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


void MainWindow::updateFpsLabel(int value) {
    ui->fpsValueLabel->setText(QString::number(value) + " FPS");
}

void MainWindow::onShowTrueSizeClicked(){
    emit trueSizeClicked();
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

