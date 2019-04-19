#include "dcMainWindow.h"


MainWindow::MainWindow(int wid, QWidget *parent) : QMainWindow(parent) {

  rootDir = "/home/dulain/c++/Burro/";
  loadcnt = 1;

  hh = 30;
  ww = wid*0.99;
  ww2 = 960;
  ndownrunning = 0;

  bgcolors[0] = "#B10CED";
  bgcolors[1] = "#F0A626";
  bgcolors[2] = "#D92929";

  fgcolors[0] = "#FFFFF8";
  fgcolors[1] = "#000000";

  ops.clear();

  this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
  this->setContentsMargins(0,0,0,0);
  this->setStyleSheet("QWidget {background-color: #333333;color: #fffff8;} ");

  //keyCtrlP = new QShortcut(this);
  keyCtrlQ = new QShortcut(this);
  keyCtrlE = new QShortcut(this);
  keyCtrlD = new QShortcut(this);
  keyCtrlT = new QShortcut(this);
  keyCtrlF = new QShortcut(this);
  keyCtrlY = new QShortcut(this);
  //keyCtrlD = new QShortcut(this);
  window = new QWidget();
  layout = new QVBoxLayout();

  //keyCtrlP->setKey(Qt::CTRL + Qt::Key_P);
  //connect(keyCtrlP, SIGNAL(activated()), this, SLOT(slotShortcutCtrlP()));

  keyCtrlQ->setKey(Qt::CTRL + Qt::Key_Q);
  connect(keyCtrlQ, SIGNAL(activated()), this, SLOT(slotShortcutCtrlQ()));

  keyCtrlE->setKey(Qt::CTRL + Qt::Key_E);
  connect(keyCtrlE, SIGNAL(activated()), this, SLOT(slotShortcutCtrlE()));

  keyCtrlD->setKey(Qt::CTRL + Qt::Key_D);
  connect(keyCtrlD, SIGNAL(activated()), this, SLOT(slotShortcutCtrlD()));

  keyCtrlT->setKey(Qt::CTRL + Qt::Key_T);
  connect(keyCtrlT, SIGNAL(activated()), this, SLOT(slotShortcutCtrlT()));

  keyCtrlF->setKey(Qt::CTRL + Qt::Key_F);
  connect(keyCtrlF, SIGNAL(activated()), this, SLOT(slotShortcutCtrlF()));

  keyCtrlY->setKey(Qt::CTRL + Qt::Key_Y);
  connect(keyCtrlY, SIGNAL(activated()), this, SLOT(slotShortcutCtrlY()));


  //QTimer::singleShot(0, this, SIGNAL(appStarting()));

  tw = new QTableWidget(1,1);
  tw->horizontalHeader()->setStretchLastSection(true);
  tw->setHorizontalHeaderLabels(QStringList() << tr("To Do"));
  int w1 = ww*(10.0/10.5);
  //int w2 = ww*(8.0/10.5);
  //printf("%i \t %i \n",w1,w2);
  tw->setColumnWidth(0, w1);
  //tw->setColumnWidth(1, w2);
  //tw->setAlternatingRowColors(true);
  tw->setStyleSheet("QWidget {background-color: #333333;color: #000000;}  QHeaderView::section {background-color: #646464;padding: 4px;border: 1px solid #fffff8;font-size: 10pt;}  QTableWidget { gridline-color: #fffff8;font-size: 12pt;} QTableWidget QTableCornerButton::section { background-color: #646464; border: 1px solid #fffff8;}");

  ProcessDirectory(rootDir);
  listFilesFound();
  loadButtons();

  layout->setSpacing(0);
  layout->setMargin(0);
  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(tw);

  window->setStyleSheet("margin: 0px; padding: 0px;");
  window->setLayout(layout);
  //window->setStyleSheet("margin: 0px; padding: 0px;");

  this->setCentralWidget(window);

  window->resize(ww,500);
  resize(ww,500);
  window->setFixedSize(ww,500);
  setFixedSize(ww,500);

}

MainWindow::~MainWindow() {
}

void MainWindow::slotShortcutCtrlP() {
  pcnt++;
}

void MainWindow::slotShortcutCtrlQ() {
  QApplication::quit();
}

void MainWindow::slotShortcutCtrlE() {
}

void MainWindow::slotShortcutCtrlD() {
  int i = system("evince /home/dulain/c++/Doccer/logbook.pdf &");
  (void)i;
}

void MainWindow::slotShortcutCtrlT() {
  int i = system("/home/dulain/c++/Doccer/runCreateTEX &");
  (void)i;
}

void MainWindow::slotShortcutCtrlF() {
  QString text = QInputDialog::getText(this,"Filter","String to filter");
  filterTable(text);
}

void MainWindow::slotShortcutCtrlY() {

}

void MainWindow::slotUKeyForDocCell() {
  for(int i=0; i<ops.size(); i++) {
    if(ops[i].strike) {
      string oldname = rootDir+"/Dos/"+ops[i].file;
      string newname = rootDir+"/Dones/"+ops[i].file;
      int res = rename(oldname.c_str(),newname.c_str());
      printf("Striking file %i: %s \t %i \n",i,ops[i].file.c_str(),res);
      ops.erase(ops.begin()+i);
      tw->removeRow(i);
      i--;
    }
  }
}

void MainWindow::slotNKeyForDocCell() {

  string indexFile = rootDir+"/INDEX";

  string indexstr;
  ifstream ifile(indexFile.c_str());
  getline(ifile,indexstr);
  ifile.close();

  int newindex = atoi(indexstr.c_str())+1;
  /*
  ofstream ofile(indexFile.c_str(),std::ofstream::trunc);
  ofile << to_string(newindex);
  ofile.close();
  */
  printf("ID: %i \n",newindex);

  QString dtext = QInputDialog::getText(this,"","Thing to do?");
  ImpBox *IMPB = new ImpBox();
  
  //QString itext = QInputDialog::getText(this,"","Importance?");

  int import = 1;//atoi(itext.toStdString().c_str());
  if(import<1 || import>3) import = 1;

  string outfilename = "e-"+to_string(newindex)+"-"+to_string(import)+".txt";
  string outname = rootDir+"/Dos/"+outfilename;

  printf("New file: %s \n",outfilename.c_str());
  /*
  ofstream outentry(outname.c_str());
  outentry << dtext.toStdString();
  outentry.close();
  */
  QFont fontt( "Arial", 20, QFont::Bold);

  int vi = ops.size();

  printf("Vector index: %i \n",vi);

  ops.push_back(entryData());
  //sscanf(file.c_str(),"e-%i-%i.txt",&icolor,&ievt);
  //printf("%s: Color: %i \t Event %6i \n",file.c_str(),icolor,ievt);
  ops[vi].file = outfilename;
  ops[vi].color = import;
  ops[vi].strike = false;
  ops[vi].des = dtext.toStdString();

  docV.push_back(new DocCell(vi));
  docV[vi]->setReadOnly(true);
  connect(docV[vi],&DocCell::signalEnterKeyFromDocCell,this,&MainWindow::slotEnterKeyForDocCell);
  connect(docV[vi],&DocCell::signalNKeyFromDocCell,this,&MainWindow::slotNKeyForDocCell);
  connect(docV[vi],&DocCell::signalUKeyFromDocCell,this,&MainWindow::slotUKeyForDocCell);
  docV[vi]->setFont(fontt);
  docV[vi]->setText(dtext);

  string stystr = "QWidget {background-color: "+bgcolors[ops[vi].color-1]+";color: "+fgcolors[1]+";} QLineEdit:focus{ color: "+fgcolors[0]+"; }";
  docV[vi]->setStyleSheet(stystr.c_str());
  /*
    if(ops[vi].color==1) docV[vi]->setStyleSheet("QWidget {background-color: #B10CED;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
    if(ops[vi].color==2) docV[vi]->setStyleSheet("QWidget {background-color: #F0A626;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
    if(ops[vi].color==3) docV[vi]->setStyleSheet("QWidget {background-color: #D92929;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
  */
  if((vi+1)>tw->rowCount()) tw->insertRow(vi);
  tw->setCellWidget(vi,0,docV[vi]);

}

void MainWindow::slotEnterKeyForDocCell(int id) {

  string stystr = "QWidget {background-color: "+bgcolors[ops[id].color-1]+";color: "+fgcolors[1]+";";
  if(!ops[id].strike) {
    stystr += "text-decoration:line-through;";
    ops[id].strike = true;
  }
  else ops[id].strike = false;
  stystr += "} QLineEdit:focus{ color: "+fgcolors[0]+"; }";
  docV[id]->setStyleSheet(stystr.c_str());

  /*
    if(!ops[id].strike) {
    if(ops[id].color==1) docV[id]->setStyleSheet("QWidget {background-color: #B10CED;color: #000000;text-decoration:line-through;} QLineEdit:focus{ color: #fffff8; }");
    if(ops[id].color==2) docV[id]->setStyleSheet("QWidget {background-color: #F0A626;color: #000000;text-decoration:line-through;} QLineEdit:focus{ color: #fffff8; }");
    if(ops[id].color==3) docV[id]->setStyleSheet("QWidget {background-color: #D92929;color: #000000;text-decoration:line-through;} QLineEdit:focus{ color: #fffff8; }");
    ops[id].strike = true;
    }
    else {
    if(ops[id].color==1) docV[id]->setStyleSheet("QWidget {background-color: #B10CED;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
    if(ops[id].color==2) docV[id]->setStyleSheet("QWidget {background-color: #F0A626;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
    if(ops[id].color==3) docV[id]->setStyleSheet("QWidget {background-color: #D92929;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
    ops[id].strike = false;
    }
  */

}

void MainWindow::filterTable(QString filter) {
  printf("Rows: %i \t Columns: %i \n",tw->rowCount(),tw->columnCount());
  for(int i=0; i<tw->rowCount(); i++) {
    bool match = false;
    for(int j=0; j<tw->columnCount(); j++) {
      //QTableWidgetItem *item = tw->item(i,0);
      DocCell *tdc = (DocCell*)tw->cellWidget(i,j);
      //printf("%s\n",tdc->displayText().toStdString().c_str());
      if(tdc->text().toLower().contains(filter.toLower())) {
	match = true;
	break;
      }
    }
    tw->setRowHidden( i, !match );
  }
}

void MainWindow::show() {
  QMainWindow::show();
  QApplication::processEvents();
  emit windowShown();
  if (firstTimeShown == true) {
    firstTimeShown = false;
    emit windowLoaded();
  }
}

void MainWindow::loadButtons() {

  for(int i=0; i<int(ops.size()); i++) {

    string ds = ops[i].des;

    QFont fontt( "Arial", 20, QFont::Bold);

    docV.push_back(new DocCell(i));
    docV[i]->setReadOnly(true);
    connect(docV[i],&DocCell::signalEnterKeyFromDocCell,this,&MainWindow::slotEnterKeyForDocCell);
    connect(docV[i],&DocCell::signalNKeyFromDocCell,this,&MainWindow::slotNKeyForDocCell);
    connect(docV[i],&DocCell::signalUKeyFromDocCell,this,&MainWindow::slotUKeyForDocCell);
    docV[i]->setFont(fontt);
    docV[i]->setText(QString(ds.c_str()));

    string stystr = "QWidget {background-color: "+bgcolors[ops[i].color-1]+";color: "+fgcolors[1]+";} QLineEdit:focus{ color: "+fgcolors[0]+"; }";
    docV[i]->setStyleSheet(stystr.c_str());
    /*
      if(ops[i].color==1) docV[i]->setStyleSheet("QWidget {background-color: #B10CED;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
      if(ops[i].color==2) docV[i]->setStyleSheet("QWidget {background-color: #F0A626;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
      if(ops[i].color==3) docV[i]->setStyleSheet("QWidget {background-color: #D92929;color: #000000;} QLineEdit:focus{ color: #fffff8; }");
    */

    if((i+1)>tw->rowCount()) tw->insertRow(i);
    tw->setCellWidget(i,0,docV[i]);

  }

}

void MainWindow::listFilesFound() {

  for(int i=0; i<int(ops.size()); i++) {
    printf("%s\n",ops[i].file.c_str());
  }

}

void MainWindow::ProcessDirectory(std::string directory) {
  std::string dirToOpen = directory + "/Dos/";
  DIR *dir = opendir(dirToOpen.c_str());
  //std::cout << "Input directory: " << directory.c_str() << std::endl;
  //std::cout << "Process directory: " << dirToOpen.c_str() << std::endl;
  if(NULL==dir) {
    std::cout << "ProcessDirectory: could not open directory: " << dirToOpen.c_str() << std::endl;
    return;
  }
  struct dirent *entity = readdir(dir);
  while(entity!=NULL) {
    ProcessEntity(dirToOpen,entity);
    entity = readdir(dir);
  }
  closedir(dir);
}

void MainWindow::ProcessEntity(std::string directory, struct dirent* entity) {
  if(entity->d_type == DT_DIR) {
    if(entity->d_name[0] == '.') return;
    ProcessDirectory(directory+std::string(entity->d_name));
    return;
  }
  if(entity->d_type == DT_REG) {
    ProcessFile(std::string(entity->d_name));
    return;
  }
  std::cout << "ProcessEntity: Not a file or directory: " << directory.c_str() << entity->d_name << std::endl;
}

void MainWindow::ProcessFile(std::string file) {
  if(file.find(".txt")!=string::npos) {
    int icolor, ievt;
    ops.push_back(entryData());
    sscanf(file.c_str(),"e-%i-%i.txt",&ievt,&icolor);
    //printf("%s: Color: %i \t Event %6i \n",file.c_str(),icolor,ievt);
    ops[ops.size()-1].file = file;
    ops[ops.size()-1].color = icolor;
    ops[ops.size()-1].strike = false;
    ops[ops.size()-1].des = fileContentsToString(rootDir+"/Dos/"+file);
  }
  return;
}

string MainWindow::fileContentsToString(string filename) {
  ifstream infile(filename);
  stringstream sstr;
  sstr << infile.rdbuf();
  infile.close();
  std::cout << filename << ":  " << sstr.str() << std::endl;
  return sstr.str();
}

string MainWindow::fileContentsToString(ifstream& in) {
  stringstream sstr;
  sstr << in.rdbuf();
  return sstr.str();
}
