
#ifndef IMPBOX_H
#define IMPBOX_H

#include "stdio.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include <QWidget>
#include <QKeyEvent>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QPushButton>

class ImpBox : public QWidget {

  Q_OBJECT

 public:

  ImpBox();
  ~ImpBox();

  public slots:

  void keyPressEventLB(QKeyEvent *keyevt);
    
};

#endif 
