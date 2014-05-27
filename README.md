# Simple QT-based Pomodoro timer

## About

Needed a [Pomodoro](http://pomodorotechnique.com/) timer for Linux. Since I couldn't easily find one and wanted to learn QT, I built one with a UI similar to [TomatoTimer](http://tomato-timer.com/). 

## Building

Re-generate Makefile by running qmake -o Makefile qtomato.pro

## TODO

* Consider using QT timers instead of a separate thread.
* D-bus and/or sound-based notifications
* Persistent state: being able to add, remove, and work through a list of tasks.
