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

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name MainWindow h file for assignment8
 * This cpp file contains the event handler implementations for the buttons in the UI.
 *
 * File and software practice principles reviewed by Raj Reddy.
*/

// Constructor for the MainWindow class.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    // Sets up primary UI and initializes the sprite editor and drawing canvas.
    ui->setupUi(this);
    spriteEditor = new SpriteModel(this);
    canvas = new DrawingCanvas(this);
    initializeHelpTexts();


    // Connects the help menu functions to their respective functions
    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionDuplicate, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionLoad_2, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionPlay_Back, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionSave_2, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionShow_True_Size, &QAction::triggered, this, &MainWindow::showHelpDialog);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::showHelpDialog);

    // Sets the fps slider's minimum, maximum, and initial values.
    ui->fpsSlider->setMinimum(1);
    ui->fpsSlider->setMaximum(30);
    ui->fpsSlider->setValue(16);

    // Configures the canvas geometry and replaces the drawPanel with the canvas.
    canvas->setGeometry(ui->drawPanel->geometry());
    delete ui->drawPanel;
    ui->drawPanel = canvas;

    // Sets the icon size and width for the frames list.
    ui->framesList->setIconSize(QSize(64, 64));
    ui->framesList->setFixedWidth(128);

    // Updates the FPS label with the current value of the fps slider.
    updateFpsLabel(ui->fpsSlider->value());

    // Connects signals and slots for the canvas, sprite editor, and UI elements.
    connect(canvas, &DrawingCanvas::requestPixelChange, spriteEditor, &SpriteModel::updatePixel);
    connect(spriteEditor, &SpriteModel::spriteChanged, canvas, &DrawingCanvas::updateDrawing);
    connect(spriteEditor, &SpriteModel::spriteChanged, this, &MainWindow::updateFrameList);
    connect(canvas, &DrawingCanvas::requestCurrentImage, this, &MainWindow::provideCurrentImage);

    // Connects signals and slots from the buttons in the GUI to their respective functions
    connect(ui->addFrameButton, &QPushButton::clicked, this, &MainWindow::onAddFrameButtonClicked);
    connect(ui->deleteFrameButton, &QPushButton::clicked, this, &MainWindow::onDeleteFrameButtonClicked);
    connect(ui->eraserButton, &QPushButton::clicked, this, &MainWindow::onEraserButtonClicked);
    connect(ui->pencilButton, &QPushButton::clicked, this, &MainWindow::onPencilButtonClicked);
    connect(ui->duplicateFrameButton, &QPushButton::clicked, this, &MainWindow::onDuplicateFrameButtonClicked);
    connect(ui->colorPicker, &QPushButton::clicked, this, &MainWindow::onColorPickerClicked);

    // Connects the frames management and color selection implmentations to their respective functions
    connect(ui->framesList, &QListWidget::itemClicked, this, &MainWindow::OnFrameListWidgetItemClicked);
    connect(this, &MainWindow::colorSelected, canvas, &DrawingCanvas::colorChanged);
    connect(this, &MainWindow::dimensionsSet, spriteEditor, &SpriteModel::setInitialFrame);

    // Connects the save and load functions to their respective methods
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveClicked);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadClicked);
    connect(this, &MainWindow::Load, spriteEditor, &SpriteModel::load);
    connect(this, &MainWindow::Save, spriteEditor, &SpriteModel::save);
    connect(spriteEditor, &SpriteModel::loaded, this, &MainWindow::updateFrameList);


    // Connects the play back and true size buttons to their respective functions
    connect(ui->playSpriteButton, &QPushButton::clicked, spriteEditor, &SpriteModel::playAnimation);
    connect(ui->showTrueSizeButton, &QPushButton::clicked, spriteEditor, &SpriteModel::showTrueSize);

    // Connects drawing and erasing implementations to their respective functions
    connect(this, &MainWindow::Drawing, canvas,&DrawingCanvas::enterDrawingMode);
    connect(this, &MainWindow::Erasing, canvas,&DrawingCanvas::erasingMode);

    connect(canvas, &DrawingCanvas::drawingStarted, spriteEditor, &SpriteModel::onDrawingStarted);
    connect(ui->undoButton, &QPushButton::clicked, spriteEditor, &SpriteModel::undo);
    connect(ui->redoButton, &QPushButton::clicked, spriteEditor, &SpriteModel::redo);

    // Sets the icons for the pencil and eraser buttons.
    ui->pencilButton->setIcon(QIcon(":/icons/penIcon.png"));
    ui->eraserButton->setIcon(QIcon(":/icons/eraserIcon.png"));

    // Connects the FPS slider to update the FPS value in the sprite editor and FPS label.
    connect(ui->fpsSlider, &QSlider::valueChanged, [&](int value) {
        std::cout << "Slider value changed to:" << value;
        spriteEditor->setFPS(value);
    });
    connect(ui->fpsSlider, &QSlider::valueChanged, this, &MainWindow::updateFpsLabel);

    // Sets the initial drawing mode to pencil on application startup.
    QTimer::singleShot(0, this, [this]() {
        ui->pencilButton->click();
    });

    // Sets the style sheet for the FPS slider and label.
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
    // Destructor for the MainWindow class.
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
    helpTexts["actionShow_True_Size"] = "Plays-back and shows the actual size of the sprite.";
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

    // Updates the list of frames in the UI by looping through the frame count
    for (int i = 0; i < spriteEditor->getFrameCount(); ++i) {
        QImage thumbnail = spriteEditor->getFrameThumbnail(i);

        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(QPixmap::fromImage(thumbnail)));
        item->setData(Qt::UserRole, QVariant::fromValue(i));
        ui->framesList->addItem(item);
    }
}


void MainWindow::provideCurrentImage() {

    // Provides the current image to the drawing canvas.
    QImage image = spriteEditor->getCurrentFrameImage(spriteEditor->getCurrentFrameIndex());

    if (image.isNull()) {

        // Error message if image is null
        qDebug() << "Current frame image is null";
        return;
    }

    // Scales image to approriate aspect ratio and utilizes Qt's FastTransformation function
    canvas->receiveCurrentImage(image.scaled(canvas->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
}

void MainWindow::OnFrameListWidgetItemClicked(QListWidgetItem *item) {

    // Handles the selection of a frame from the frames list.
    int frameIndex = item->data(Qt::UserRole).toInt();
    spriteEditor->setCurrentFrameIndex(frameIndex);
    emit spriteUpdated();
}

void MainWindow::onAddFrameButtonClicked() {

    // Handles the click event of the Add Frame button.
    spriteEditor->addFrame();
    emit spriteUpdated();
}

void MainWindow::onDeleteFrameButtonClicked()
{

    // Handles the click event of the Delete Frame button.
    spriteEditor->deleteFrame();
    emit spriteUpdated();
}

void MainWindow::onEraserButtonClicked(){

    // Handles the click event of the Eraser button.
    ui->eraserButton->setEnabled(false);
    ui->pencilButton->setEnabled(true);

    // connects to appropriate signal/slot
    emit colorSelected(QColor(Qt::transparent));
    emit Erasing();
}

void MainWindow::onPencilButtonClicked(){

    // Handles the click event of the Pencil button.
    ui->pencilButton->setEnabled(false);
    ui->eraserButton->setEnabled(true);

    // If the previously used color is blank or there is not previous color, set the lastUsedColor to red
    if(lastUsedColor==""){
        lastUsedColor = QColor(Qt::red);
    }

    emit colorSelected(QColor(lastUsedColor));
    emit Drawing();
}

void MainWindow::onDuplicateFrameButtonClicked(){

    // Handles the click event of the Duplicate Frame button.
    spriteEditor->duplicateFrame();
    emit spriteUpdated();
}


void MainWindow::onColorPickerClicked(){

    // Handles the click event of the Color Picker button.
    QColor selectedColor = QColorDialog::getColor(Qt::white, this, "Select color");
    if(selectedColor.isValid()){
    lastUsedColor = selectedColor;
    emit colorSelected(selectedColor);
    }
}

void MainWindow::updateFpsLabel(int value) {

    // Updates the FPS label with the current FPS value.
    ui->fpsValueLabel->setText(QString::number(value) + " FPS");
}

void MainWindow::onShowTrueSizeClicked(){

    // Handles the click event of the Show True Size button.
    emit trueSizeClicked();
}

void MainWindow::showEvent(QShowEvent *event) {

    // Handles the show event of the main window.
    QMainWindow::showEvent(event);

    // Uses QTimer::singleShot to defer showing the dimensions dialog.
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
    // Handles the click event of the Save action and saves it to a .ssp file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Load Sprite"), "", tr("SSP Files (*.ssp)"));

    // If the file is not empty, then call the Save signal with the file as its parameter
    if (!fileName.isEmpty()) {
        emit Save(fileName);
    }
}


void MainWindow:: onLoadClicked()
{
    // Handles the click event of the Load action.
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Sprite"), "", tr("SSP Files (*.ssp)"));

    // If the file is not empty, then call the Load signal with the file as its parameter
    if (!fileName.isEmpty()) {
        emit Load(fileName);
    }
}
