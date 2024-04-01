
#include "dimensionsDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

dimensionsDialog::dimensionsDialog(QWidget *parent)
    : QDialog(parent), widthEdit(new QLineEdit(this)), heightEdit(new QLineEdit(this)) {

    // Set validators to ensure only integers are entered
    widthEdit->setValidator(new QIntValidator(1, 10000, this));
    heightEdit->setValidator(new QIntValidator(1, 10000, this));
    widthEdit->setText("64");
    heightEdit->setText("64");

    // Set up the form layout with labels and line edits
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("&Width:"), widthEdit);
    formLayout->addRow(tr("&Height:"), heightEdit);

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

    connect(widthEdit, &QLineEdit::textChanged, this, &dimensionsDialog::updateSecondInput);
    connect(heightEdit, &QLineEdit::textChanged, this, &dimensionsDialog::updateFirstInput);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint);
}

int dimensionsDialog::getWidth() const {
    return widthEdit->text().toInt();
}

int dimensionsDialog::getHeight() const {
    return heightEdit->text().toInt();
}

void dimensionsDialog::updateSecondInput(const QString &text) {

    heightEdit->setText(text);
}

void dimensionsDialog::updateFirstInput(const QString &text) {
    widthEdit->setText(text);
}

void dimensionsDialog::accept() {

    // Check if either input field is empty
    if (widthEdit->text().isEmpty() || heightEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("Width and Height cannot be empty."));
        return;
    }

    QDialog::accept();
}
