
#ifndef __SETGAMETABLE_H_
#define __SETGAMETABLE_H_

class SetCard;
class SetCardEditor;

class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;
class QSpinBox;
class QPushButton;
#include <QVector>
#include <QWidget>

class SetGameTable : public QWidget
{
    Q_OBJECT
  public:
    SetGameTable(QWidget* pParent = 0);
    ~SetGameTable();
    int count() const;
  public slots:
    void setCount(int nCount);
    void randomize();
    void findMatches();
  private:
    // parts of constructor
    void createGui();
    // layouts
    QVBoxLayout* layoutParent;
    QHBoxLayout* layoutToolBar;
    QGridLayout* layoutTable;
    // widgets
    QSpinBox*    spinCount;
    QPushButton* btnRandomize;
    QPushButton* btnFindMatches;
    // data
    int m_nCount;
    QVector<SetCard*> m_vCards;
    QVector<SetCardEditor*> m_vEditors;
};

#endif

