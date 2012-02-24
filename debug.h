#ifndef _CHAT_CLIENT_DEBUG_H_
#define _CHAT_CLIENT_DEBUG_H_

#include "window.h"

class QListWidget;

class Debug : public Window
{
  Q_OBJECT
public:
  Debug();
  virtual ~Debug();

public slots:
  void trace(const QString&);

private:
  void setupUi();
  
private:
  QListWidget *m_event_list;
};

#endif /* _CHAT_CLIENT_DEBUG_H_ */
