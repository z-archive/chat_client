#ifndef _CHAT_CLIENT_DEBUG_H_
#define _CHAT_CLIENT_DEBUG_H_

#include <QWidget>

class QListWidget;

class Debug : public QWidget
{
  Q_OBJECT
public:
  Debug(QWidget *parent= 0);
  virtual ~Debug();

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

#endif /* _CHAT_CLIENT_DEBUG_H_ */
