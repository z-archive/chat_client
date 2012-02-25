#ifndef _CHAT_CLIENT_ACCOUNT_H_
#define _CHAT_CLIENT_ACCOUNT_H_

#include <QWidget>
#include <TelepathyQt4/Types>

class QDataWidgetMapper;
class QCheckBox;
class QLineEdit;
class QSpinBox;

class AccountModel;

class Account : public QWidget
{
  Q_OBJECT

public:
  Account(AccountModel *model, QWidget *parent);
  virtual ~Account();

public slots:
  void setCurrentModelIndex(const QModelIndex &index);
  
private:
  void setupUi(AccountModel *model);

private:
  QDataWidgetMapper *m_mapper;
  QCheckBox *m_valid;
  QCheckBox *m_enabled;
  QLineEdit *m_connection_manager;
  QLineEdit *m_protocol_name;
  QLineEdit *m_display_name;
  QLineEdit *m_nickname;
  QCheckBox *m_connects_automaticly;
  QLineEdit *m_automatic_presence;
  QLineEdit *m_current_presence;
  QLineEdit *m_requested_presence;
  QCheckBox *m_is_changing_presence;
  QSpinBox  *m_connection_status;
  QLineEdit *m_connection;
};

#endif /* _CHAT_CLIENT_ACCOUNT_H_ */
