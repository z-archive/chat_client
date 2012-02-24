#ifndef _CHAT_CLIENT_DEBUG_WINDOW_H_
#define _CHAT_CLIENT_DEBUG_WINDOW_H_

#include <QWidget>

class QListWidget;

class DebugWindow : public QWidget
{
  Q_OBJECT
public:
  DebugWindow(QWidget *parent= 0);
  virtual ~DebugWindow();

signals:
  void quit();
	     
public slots:
  void trace(const QString&);

protected:
  virtual void closeEvent(QCloseEvent*);

private:
  void setupUi();
  
private:
  QListWidget *m_event_list;
};

#endif /* _CHAT_CLIENT_DEBUG_WINDOW_H_ */
