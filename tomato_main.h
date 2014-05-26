#ifndef TOMATO_MAIN_H
#define TOMATO_MAIN_H

#include <memory>
#include <thread>
#include <mutex>

#include <QMainWindow>

namespace Ui {
class TomatoMain;
}

using std::unique_ptr;

class TomatoMain : public QMainWindow {
  Q_OBJECT

 public:
  explicit TomatoMain(QWidget *parent = 0);
  
  ~TomatoMain();

 private slots:
  void SlotStartClicked();
  
  void SlotStopClicked();

  void SlotResetClicked();

 private:
  enum {
    kDefaultSecs = 0,
    kDefaultMins = 25
  };

  void DisplayTimeOnLcd();

  void TimerThread();

  unique_ptr<Ui::TomatoMain> ui_;
  unique_ptr<std::thread> timer_thread_;

  mutable std::mutex lock_;

  int mins_;
  int secs_;
  bool stopped_;
  bool reset_;
};

#endif // TOMATO_MAIN_H
