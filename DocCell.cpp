
#include "DocCell.h"

DocCell::DocCell(int iid) {
  id = iid;
}

DocCell::~DocCell() {

}

void DocCell::keyPressEvent(QKeyEvent *keyevt) {
  QLineEdit::keyPressEvent(keyevt);
  if(this->hasFocus()) {
    if(keyevt->key()==Qt::Key_Return) {
      printf("%s \n",(this->text().toStdString()).c_str());
      emit signalEnterKeyFromDocCell(id);
    }
    if(keyevt->key()==Qt::Key_N) {
      emit signalNKeyFromDocCell();      
    }
    if(keyevt->key()==Qt::Key_U) {
      emit signalUKeyFromDocCell();      
    }
  }
}
