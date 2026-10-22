#include "keyboard_window.hpp"
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>


using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Довольная Клавиатура");
	
	QPixmap pixmap("img/vesoli_smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	//display->setText("Помоги мне заработать лучше...");

	keyboard = new KeyBoard(keyboard_width);
	display->installEventFilter(this);
	keyboard->installEventFilter(this);
	for (QPushButton* button : keyboard->findChildren<QPushButton*>()) {
		button->installEventFilter(this);
	}

setFocusPolicy(Qt::StrongFocus);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);

	connect(keyboard, &KeyBoard::key_pressed, this, [this](const QString& text){display->setText(display->text() + text);});
	connect(keyboard, &KeyBoard::backspace_pressed, this, [this]() {QString text = display->text();text.chop(1);display->setText(text);});

}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    

    const QString text = event->text();

    if (text.size() == 1 && (text.at(0).isLetter() || text.at(0).isDigit())) {
        display->setText(display->text() + text);
    }
}
bool KeyBoardWindow::eventFilter(QObject* watched, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* key_event = static_cast<QKeyEvent*>(event);

        if (key_event->key() == Qt::Key_Backspace) {
            QString text = display->text();
            text.chop(1);
            display->setText(text);
            return true;
        }

        if (key_event->key() == Qt::Key_Space) {
            display->setText(display->text() + QStringLiteral(" "));
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}