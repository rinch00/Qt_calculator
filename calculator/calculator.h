#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>


class button;

QT_BEGIN_NAMESPACE
namespace Ui {
class calculator;
}
QT_END_NAMESPACE

class calculator : public QWidget
{
    Q_OBJECT

public:
    calculator();

private slots:
    void digitClicked();
    void percentClicked();
    void doubleOperationClicked();
    void equalClicked();
    void backspaceClicked();
    void clearAll();
    void pusto();
private:
    Ui::calculator *ui;

    button* createButton(const QString &text, const char* member);
    button* digitButtons[10];

    QLineEdit* display;

    QString m_division_sign = QChar(0x000000F7);
    QString m_times_sign = QChar(0x000000D7);
    QString m_plus_sign = "+";
    QString m_minus_sign ="-";
    QString m_percentClicked = "%";

    QString currentOperator;    // Текущий оператор
    double firstOperand;         // Первое число

    bool calculate(double operand1, double operand2, double &result);
    bool waitingForOperand;


};
#endif // CALCULATOR_H
