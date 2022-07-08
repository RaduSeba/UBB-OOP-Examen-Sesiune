#include <QApplication>
#include <QPushButton>
#include "UI.h"

int main(int argc, char *argv[]) {

    test_domain();
    test_repo();
    test_service();

    QApplication a(argc, argv);

    auto rp=FileRepo{"ba.txt"};
    auto srv=Service{rp};
    auto gui=GUI{srv};

    gui.show();

    return QApplication::exec();
}