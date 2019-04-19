#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sys/stat.h>
#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <sstream>
#include "time.h"

#include <QApplication>
#include <QMainWindow>
#include <QShortcut>
#include <QMessageBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QProgressBar>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QHeaderView>
#include <QProcess>
#include <QTimer>
#include <QKeyEvent>
#include <QLineEdit>
#include <QInputDialog>
#include <QPlainTextEdit>
#include <QTableWidgetItem>
#include <QCalendarWidget>
#include <QGroupBox>

#include "DocCell.h"
#include "ImpBox.h"

using namespace std;

struct entryData {
  string file;
  string des;
  int color;
  bool strike;
};
  
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(int wid=1000, QWidget *parent=0);
  void show();
  ~MainWindow();

  private slots:

    void slotShortcutCtrlP();
    void slotShortcutCtrlQ();
    void slotShortcutCtrlE();
    void slotShortcutCtrlD();
    void slotShortcutCtrlT();
    void slotShortcutCtrlF();
    void slotShortcutCtrlY();
    
    void slotNKeyForDocCell();
    void slotUKeyForDocCell();
    void slotEnterKeyForDocCell(int id);
            
 signals:
    void windowShown();
    void windowLoaded();
    void appStarting();
      
 private:
    QShortcut       *keyCtrlP;
    QShortcut       *keyCtrlQ;
    QShortcut       *keyCtrlE;
    QShortcut       *keyCtrlD;
    QShortcut       *keyCtrlT;
    QShortcut       *keyCtrlF;
    QShortcut       *keyCtrlY;
    QWidget *window;
    QVBoxLayout *layout;
    string finfilename;
    int fcnt;
    int pcnt;
    QTableWidget *tw;
    bool firstload;
    bool firstTimeShown;
    string ftemptitle;
    string foutdir;
    string rootDir;
    vector<DocCell*> docV;
      
    int hh, ww, ww2;
    int ndownrunning;
    string bgcolors[3];
    string fgcolors[3];
    
    int loadcnt;
    void loadButtons();
    void listFilesFound();
    void filterTable(QString filter);
    
    std::vector<entryData> ops;
      
    void ProcessDirectory(std::string directory);
    void ProcessEntity(std::string directory, struct dirent* entity);
    void ProcessFile(std::string file);
    string fileContentsToString(string filename);
    string fileContentsToString(ifstream& in);
      
};

#endif // MAINWINDOW_H
