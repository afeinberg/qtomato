#include "tomato_main.h"
#include "ui_tomato_main.h"

#include <chrono>
#include <functional>

using std::bind;
using std::unique_lock;
using std::mutex;

TomatoMain::TomatoMain(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::TomatoMain),
      mins_(kDefaultMins),
      secs_(kDefaultSecs),
      stopped_(true),
      reset_(false) {
  ui_->setupUi(this);
  DisplayTimeOnLcd();
  connect(ui_->startButton, SIGNAL(clicked()), this, SLOT(SlotStartClicked()));
  connect(ui_->stopButton, SIGNAL(clicked()), this, SLOT(SlotStopClicked()));
  connect(ui_->resetButton, SIGNAL(clicked()), this, SLOT(SlotResetClicked()));
}

// Display mins_ and secs_ on the LCD.
void TomatoMain::DisplayTimeOnLcd() {
  ui_->minsRemainingLcd->display(mins_);
  ui_->secsRemainingLcd->display(secs_);
}

void TomatoMain::SlotStopClicked() {
  unique_lock<mutex> lock(lock_);
  stopped_ = true;
}

void TomatoMain::SlotResetClicked() {
  unique_lock<mutex> lock(lock_);

  if (!stopped_) {
    reset_ = true;
  }

  mins_ = kDefaultMins;
  secs_ = kDefaultSecs;

  DisplayTimeOnLcd();
}

void TomatoMain::SlotStartClicked() {
  {
    unique_lock<mutex> lock(lock_);
    if (!stopped_) {
      return;
    }
    stopped_ = false;
  }

  timer_thread_.reset(new std::thread(bind(&TomatoMain::TimerThread, this)));
  timer_thread_->detach();
}

void TomatoMain::TimerThread() {
  int mins_remaining = mins_;
  int secs_remaining = secs_;

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    unique_lock<mutex> lock(lock_);

    if (reset_) {
      reset_ = false;
      stopped_ = true;
      break;
    }

    if (stopped_) {
      if (secs_remaining != 0 || mins_remaining != 0) {
        secs_ = secs_remaining;
        mins_ = mins_remaining;
      }
      break;
    }
    
    if (secs_remaining == 0) {
      secs_remaining = 59;
      --mins_remaining;
    } else {
      --secs_remaining;
    }

    ui_->minsRemainingLcd->display(mins_remaining);
    ui_->secsRemainingLcd->display(secs_remaining);
  
    if (mins_remaining == 0 && secs_remaining == 0) {
      stopped_ = true;
      DisplayTimeOnLcd();
      break;
    }
  }
}

TomatoMain::~TomatoMain() {
}
