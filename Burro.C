#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <QScrollArea>
#include <QProcess>
#include <QMenu>
#include <QtCore>
#include <QObject>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QSlider>
#include <QShortcut>
#include "dcMainWindow.h"

#include <QScreen>

MainWindow *mainWindow = 0;

int main(int argc, char **argv) {

  QApplication app (argc, argv);
  QRect screenrect = app.primaryScreen()->geometry();
  mainWindow = new MainWindow(screenrect.width());
  mainWindow->move(screenrect.left(), screenrect.top());
  mainWindow->show();
  
  return app.exec();
  
}
