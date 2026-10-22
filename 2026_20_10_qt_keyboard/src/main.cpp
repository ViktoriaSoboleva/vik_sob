#include <QApplication>

#include "keyboard_window.hpp"
#include "welcome_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
	
    biv::WelcomeWindow welcome_window;
    biv::KeyBoardWindow keyboard_window;

    QObject::connect(
        &welcome_window,
        &biv::WelcomeWindow::switch_to_keyboard,
        [&]() {
            welcome_window.hide();
            keyboard_window.show();
        }
    );
	welcome_window.show();

    return app.exec();
}
