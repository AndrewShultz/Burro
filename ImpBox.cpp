
#include "ImpBox.h"

ImpBox::ImpBox() {

  QHBoxLayout *mainLayout = new QHBoxLayout;
  QPushButton *lbutton = new QPushButton("Low");
  QPushButton *mbutton = new QPushButton("Medium");
  QPushButton *hbutton = new QPushButton("High");
  mainLayout->addWidget(lbutton);
  mainLayout->addWidget(mbutton);
  mainLayout->addWidget(hbutton);

  this->setLayout(mainLayout);
  this->show();
  
  connect(lbutton,keyPressEvent,this,keyPressEventLB);

}

ImpBox::~ImpBox() {

}

int ImpBox::GutherImp() {

  this->show();

}

void ImpBox::keyPressEventLB(QKeyEvent *keyevt) {

  
  
  /*
  if(keyevt->key()==Qt::Key_Return) {
    printf("%s \n",(this->text().toStdString()).c_str());
    emit signalEnterKeyFromDocCell(id);
  }
  */
}
