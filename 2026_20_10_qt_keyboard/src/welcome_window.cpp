#include "welcome_window.hpp"
#include <QVBoxLayout>

namespace biv {
    WelcomeWindow::WelcomeWindow (QWidget* parent)
    : QWidget(parent)
    {
        setWindowTitle("Клавиатура от Тани");
        welcome_label = new QLabel("Вас приветствует клавиатура от Тани", this);
        auto* layout = new QVBoxLayout(this);
        layout -> addWidget(welcome_label);

        go_button = new QPushButton("Перейти к клавиатуре", this);
        layout -> addWidget(go_button);

        connect(go_button,&QPushButton::clicked,this,&WelcomeWindow::switch_to_keyboard);

    }
}
