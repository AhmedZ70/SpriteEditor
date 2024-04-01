#ifndef DIMENSIONSDIALOG_H
#define DIMENSIONSDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QIntValidator>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name dimensions dialog .h file for assignment8
 * This .h file contains the outlined methods for choosing the width and height of the sprite
 * The user will choose the dimensions by a popup at the start of the program execution
*/
class dimensionsDialog: public QDialog {
    Q_OBJECT

public:
    /// @brief Opens the dimension popup to choose the width and height
    explicit dimensionsDialog(QWidget *parent = nullptr);
    /// @brief returns the width set by the user
    int getWidth() const;
    /// @brief returns the height set by the user
    int getHeight() const;

private:
    // Text editor for width
    QLineEdit *widthText;
    // Text editor for height
    QLineEdit *heightText;


public slots:
    /// @brief sets the text for width
    /// @param the text to use to set the width
    void updateSecondInput(const QString &text);
    /// @brief sets the text for height
    /// @param the text to use to set the height
    void updateFirstInput(const QString &text);


protected:

 /// @brief checks that the width and height are not null or zero
void accept() override;

 };
#endif // DIMENSIONSDIALOG_H

