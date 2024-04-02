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
    /// @brief Returns the width set by the user
    int getWidth() const;
    /// @brief Returns the height set by the user
    int getHeight() const;

private:
    /// @brief Text editor for width
    QLineEdit *widthText;

    /// @brief Text editor for height
    QLineEdit *heightText;


public slots:
    /// @brief Sets the text for width
    /// @param The text to use to set the width
    void updateSecondInput(const QString &text);

    /// @brief Sets the text for height
    /// @param The text to use to set the height
    void updateFirstInput(const QString &text);


protected:

     /// @brief Checks that the width and height are not null or zero
    void accept() override;

 };

#endif // DIMENSIONSDIALOG_H

