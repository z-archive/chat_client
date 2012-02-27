#ifndef _CHAT_CLIENT_ACCOUNT_H_
#define _CHAT_CLIENT_ACCOUNT_H_

#include <QWidget>
#include <TelepathyQt4/Types>
#include <QItemSelectionModel>

class QDataWidgetMapper;
class QCheckBox;
class QLineEdit;
class QSpinBox;
class QHBoxLayout;
class AccountModel;

class Account : public QWidget
{
  Q_OBJECT
private:
  enum EState
  {
    eNothing,
    eView,
    eEdit,
    eCreate,
    eLoad
  };

public:
  Account(AccountModel *model, QWidget *parent);
  virtual ~Account();

signals:
  void currentSelection(const QModelIndex&);

public slots:
  void currentChanged(const QModelIndex& selected, const QModelIndex& deselected);
  
private:
  void setupUi();
  void setupMapping();
  bool isValid();
  void setCurrentIndex(const QModelIndex&);
  
private slots:
  void updateUi();
  void toView();
  void toEdit();
  void submit();
  void revert();
  
private:
  QModelIndex        m_current;
  EState             m_state;
  AccountModel      *m_model;
  QDataWidgetMapper *m_mapper;
  
private:
  QCheckBox *m_valid;
  QCheckBox *m_enabled;
  QLineEdit *m_connectionManager;
  QLineEdit *m_protocolName;
  QLineEdit *m_displayName;
  QLineEdit *m_nickName;
  QCheckBox *m_connectsAutomatically;
  QVector<QWidget*> m_widget_vector;
private:
  QWidget *m_buttonGroup;
};

#endif /* _CHAT_CLIENT_ACCOUNT_H_ */
