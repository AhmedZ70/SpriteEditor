#ifndef DIMENSIONSDIALOG_H
#define DIMENSIONSDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QIntValidator>


class dimensionsDialog: public QDialog {
    Q_OBJECT

public:
    explicit dimensionsDialog(QWidget *parent = nullptr);
    int getWidth() const;
    int getHeight() const;

private:
    QLineEdit *widthEdit;
    QLineEdit *heightEdit;


public slots:
    void updateSecondInput(const QString &text);
    void updateFirstInput(const QString &text);


protected:
void accept() override;

 };
#endif // DIMENSIONSDIALOG_H

