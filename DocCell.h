#ifndef DOCCELL_H
#define DOCCELL_H

#include "stdio.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include <QLineEdit>
#include <QKeyEvent>

class DocCell : public QLineEdit {

  Q_OBJECT

 public:

  int id;
  DocCell(int iid);
  ~DocCell();

  public slots:

    void keyPressEvent(QKeyEvent *keyevt);
    
 signals:
    
    void signalEnterKeyFromDocCell(int id);
    void signalNKeyFromDocCell();
    void signalUKeyFromDocCell();
    //void updateNameText(const DocCell *tname);
    
};

#endif 
