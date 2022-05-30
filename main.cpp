#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setAttribute(Qt::WA_QuitOnClose);
    w.show();
    return a.exec();
}

/* NTS:
 * AESTHETIC
 * main window default fullscreen
 * highlight selected node in tree
 * spaces between tree nodes
 * make nodes smaller
 * save location of camera
 * pen dots consistent with line width
 * save drawings outside original rect
 * implement highlighter
 * http://colormind.io/api-access/
 *
 * OPTIMIZATIONS
 * turn some fields from pointers to static
 *
 *
 */
