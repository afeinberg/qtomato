#include "tomato_main.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TomatoMain w;
  w.show();

  return a.exec();
}
