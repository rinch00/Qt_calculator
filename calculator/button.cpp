#include "button.h"

button::button(const QString &text, QWidget *parent) : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);

    QFont buttonFont = font(); // Получаем текущий шрифт кнопки
    buttonFont.setPointSize(buttonFont.pointSize() + 2); // Увеличиваем размер шрифта на 2 пункта
    setFont(buttonFont); // Устанавливаем новый шрифт для кнопки
}

QSize button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());

    return size;
}


