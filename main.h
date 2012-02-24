#ifndef _CHAT_CLIENT_MAIN_H_
#define _CHAT_CLIENT_MAIN_H_

#include "window.h"

class QPushButton;

class Main : public Window
{
  Q_OBJECT

public:
  Main();
  virtual ~Main();

private:
  void addWindow(Window*, QPushButton* = 0);

private:
  void setupUi();
};

#endif /* _CHAT_CLIENT_MAIN_H_ */
