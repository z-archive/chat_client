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
};

#endif /* _CHAT_CLIENT_ACCOUNT_H_ */
