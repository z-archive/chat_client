#ifndef _CHAT_CLIENT_DEBUG_WINDOW_H_
#define _CHAT_CLIENT_DEBUG_WINDOW_H_

#include <QDialog>

class QListWidget;

class DebugWindow : public QDialog
{
  Q_OBJECT
public:
  DebugWindow(QWidget *parent= 0);
  virtual ~DebugWindow();

public slots:
  void addEvent(const QString&);

private:
  void setupUi();
  
private:
  QListWidget *m_event_list;
};

#endif /* _CHAT_CLIENT_DEBUG_WINDOW_H_ */
