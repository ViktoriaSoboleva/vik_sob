#include <QLabel>
#include <QWidget>
#include <QPushButton>

namespace biv {
    class WelcomeWindow : public QWidget {
        Q_OBJECT
    public:
        WelcomeWindow(QWidget* parent = nullptr);
    signals:
        void switch_to_keyboard();
    private:
        QPushButton* go_button;
        QLabel* welcome_label;
    };
}
