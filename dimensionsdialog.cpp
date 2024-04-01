
#include "dimensionsDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

dimensionsDialog::dimensionsDialog(QWidget *parent)
    : QDialog(parent), widthText(new QLineEdit(this)), heightText(new QLineEdit(this)) {

    // Set validators to ensure only integers are entered
    widthText->setValidator(new QIntValidator(1, 10000, this));
    heightText->setValidator(new QIntValidator(1, 10000, this));
    widthText->setText("64");
    heightText->setText("64");

    // Set up the form layout with labels and line edits
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("&Width:"), widthText);
    formLayout->addRow(tr("&Height:"), heightText);

    // Create OK and Cancel buttons
    QPushButton *okButton = new QPushButton(tr("OK"));

    // Connect the buttons to QDialog's accept() and reject() slots
    connect(okButton, &QPushButton::clicked, this, &dimensionsDialog::accept);

    // Set up the horizontal layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);

    // Create the main layout combining the form and the buttons
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    // Set the dialog's main layout
    setLayout(mainLayout);

    // Set the window title
    setWindowTitle(tr("Set Dimensions"));

    connect(widthText, &QLineEdit::textChanged, this, &dimensionsDialog::updateSecondInput);
    connect(heightText, &QLineEdit::textChanged, this, &dimensionsDialog::updateFirstInput);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint);
}

int dimensionsDialog::getWidth() const {
    return widthText->text().toInt();
}

int dimensionsDialog::getHeight() const {
    return heightText->text().toInt();
}

void dimensionsDialog::updateSecondInput(const QString &text) {

    heightText->setText(text);
}

void dimensionsDialog::updateFirstInput(const QString &text) {
    widthText->setText(text);
}

void dimensionsDialog::accept() {
    int width = widthText->text().toInt();
    int height = heightText->text().toInt();
    // Check if either input field is empty
    if (widthText->text().isEmpty() || heightText->text().isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("Width and Height cannot be empty."));
        return;
    }

    if (height< 2 || height > 256|| width < 2 || width > 256) {
        QMessageBox::warning(this, tr("Input Error"), tr("Width and Height must be less than 256."));
        return;
    }


    QDialog::accept();
}
