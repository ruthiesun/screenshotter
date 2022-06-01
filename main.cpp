#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setAttribute(Qt::WA_QuitOnClose);
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}

/* NTS:
 * AESTHETIC
 * highlight selected node in tree
 * save drawings outside original rect
 * implement highlighter
 * http://colormind.io/api-access/
 *
 */
