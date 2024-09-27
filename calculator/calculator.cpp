#include "calculator.h"
#include "button.h"

#include <QGridLayout>
#include <QMessageBox>


calculator::calculator() : waitingForOperand(true)
{
    QGridLayout* mainLayout = new QGridLayout;

    display = new QLineEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(20);


    QFont font = display->font(); // создание локальной переменной, с инициализацией в текущий шрифт
    font.setPointSize(font.pointSize() + 10); // увеличение новго размера шрифта
    display->setFont(font);

    display->setText("0");

    for (int i = 0; i < 10; i++) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
        digitButtons[i]->setStyleSheet("background-color: gray; color: white");
    }


    button *backspaceButton = createButton("back", SLOT(backspaceClicked()));
    backspaceButton->setStyleSheet("background-color: gray; color: white");

    button *clearAllButton = createButton("AC", SLOT(clearAll()));
    clearAllButton->setStyleSheet("background-color: red; color: white");

    button *divisionButton = createButton(m_division_sign, SLOT(doubleOperationClicked()));
    divisionButton->setStyleSheet("background-color: orange; color: white");

    button *timesButton = createButton(m_times_sign, SLOT(doubleOperationClicked()));
    timesButton->setStyleSheet("background-color: orange; color: white");

    button *minusButton = createButton("-", SLOT(doubleOperationClicked()));
    minusButton->setStyleSheet("background-color: orange; color white");

    button *plusButton = createButton("+", SLOT(doubleOperationClicked()));
    plusButton->setStyleSheet("background-color: orange; color white");

    button *percentButton = createButton(m_percentClicked, SLOT(percentClicked()));
    percentButton->setStyleSheet("background-color: gray; color white");

    button *equalButton = createButton("=", SLOT(equalClicked()));
    equalButton->setStyleSheet("background-color: orange; color white");

    button *pustoF = createButton(" ", SLOT(pusto()));
    pustoF->setStyleSheet("background-color: gray; color: white");

    button *pustoS = createButton(" ", SLOT(pusto()));
    pustoS->setStyleSheet("background-color: gray; color: white");

    button *pustoT = createButton(" ", SLOT(pusto()));
    pustoT->setStyleSheet("background-color: gray; color: white");



    mainLayout->addWidget(display, 0, 0, 1, 6);
    setLayout(mainLayout);
    setWindowTitle("Calculator");

    for (int i = 0; i < 10; ++i) {
        int row =((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 2);
    mainLayout->addWidget(clearAllButton, 1, 1);
    mainLayout->addWidget(pustoF, 1, 3);
    mainLayout->addWidget(backspaceButton, 1, 2);
    mainLayout->addWidget(pustoS, 5, 1);
    mainLayout->addWidget(pustoT, 5, 3);
    mainLayout->addWidget(divisionButton, 1, 4);
    mainLayout->addWidget(timesButton, 2, 4);
    mainLayout->addWidget(minusButton, 3, 4);
    mainLayout->addWidget(plusButton, 4, 4);
    mainLayout->addWidget(equalButton, 5, 4);


}

void calculator::digitClicked()
{
    button *clickeckedButton = (button*) sender();
    int digit = clickeckedButton->text().toInt();
    if (display->text() == "0" && digit == 0.0)
        return;
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }

    display->setText(display->text() + QString::number(digit));
}

void calculator::percentClicked()
{
    button *clickedButton = (button*) sender();
    QString m_operation = clickedButton->text();

    double operand = display->text().toDouble();
    double result = 0.0;

    if (m_operation == m_percentClicked) {
        result = operand / 100.0;
    }

    display->setText(QString::number(result));

}


void calculator::doubleOperationClicked()
{
    button *clickedButton = (button*)sender();
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    QString displayText = display->text();
    if (!displayText.isEmpty() && !displayText[displayText.length() - 1].isDigit()) {
        display->setText(displayText + clickedOperator);
        currentOperator = clickedOperator;
        return;
    }

    if (!currentOperator.isEmpty() && !waitingForOperand) {
        equalClicked();
    }
    firstOperand = display->text().toDouble();
    currentOperator = clickedOperator;

    display->setText(displayText + clickedOperator);

    waitingForOperand = false;
}


void calculator::equalClicked()
{
    if (currentOperator.isEmpty())
        return;

    QString displayText = display->text();

    int operatorIndex = displayText.indexOf(currentOperator, displayText.startsWith('-') ? 1 : 0);

    if (operatorIndex == -1) {
        return;
    }

    QString secondOperandStr = displayText.mid(operatorIndex + currentOperator.length());
    double secondOperand = secondOperandStr.toDouble();

    double result = 0.0;
    if (!calculate(firstOperand, secondOperand, result)) {
        QMessageBox::warning(this, "Ошибка", "Неизвестная операция");
        return;
    }
    display->setText(QString::number(result));
    currentOperator.clear();

    waitingForOperand = false;
}

void calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);

    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;

    }

    display->setText(text);
}

void calculator::clearAll()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}

button *calculator::createButton(const QString &text, const char *member)
{
    button* btn = new button(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

bool calculator::calculate(double operand1, double operand2, double &result) {
    if (currentOperator == m_plus_sign) {
        result = operand1 + operand2;
    }
    else if (currentOperator == m_minus_sign) {
        result = operand1 - operand2;
    }
    else if (currentOperator == m_times_sign) {
        result = operand1 * operand2;
    }
    else if (currentOperator == m_division_sign) {
        if (operand2 == 0.0) {
            QMessageBox::warning(this, "Ошибка", "Деление на ноль невозможно!");
            return false;
        }
        result = operand1 / operand2;
    }
    return true;
}

void calculator::pusto() {

}



