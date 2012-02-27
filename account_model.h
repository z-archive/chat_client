#ifndef _CHAT_CLIENT_ACCOUNT_MODEL_H_
#define _CHAT_CLIENT_ACCOUNT_MODEL_H_

#include <QAbstractListModel>
#include <TelepathyQt4/Types>

namespace Tp
{
class PendingOperation;
}

class AccountModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum EColumn
  {
    eValid,
    eEnabled,
    eConnectionManager,
    eProtocolName,
    eDisplayName,
    eNickName,
    eConnectsAutomatically,
    eColumnCount
  };

public:
  AccountModel(QObject *parent= 0);
  virtual ~AccountModel();

public:
  int rowCount(const QModelIndex &parent= QModelIndex()) const;
  int columnCount(const QModelIndex &parent= QModelIndex()) const;

public:
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  QVariant data(const QModelIndex &index, int role= Qt::DisplayRole) const;

public:
  QVariant headerData(int section,
                      Qt::Orientation orientation= Qt::Horizontal,
                      int role= Qt::DisplayRole) const;

private:
  /*
    It is related to TelepathyQt4 bug: signal about
    completed operation (change attribute) emited before
    real attribute change.
    As workaround I handle the signal about property changes.
  */
  void connect_account(const Tp::AccountPtr &account);

private slots:
  virtual void reset();
  void added(const Tp::AccountPtr &account);
  void removed();
  void changedValid();
  void changedEnabled();
  void changedDisplayName();
  void changedNickName();
  void changedConnectsAutomatically();

private:
  void changed(QObject* account, int column);
private:
  Tp::AccountManagerPtr m_account_manager;
  QList<Tp::AccountPtr> m_account_list;
};

#endif /* _CHAT_CLIENT_ACCOUNT_MODEL_H_ */
