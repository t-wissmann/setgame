#ifndef __SETCARDEDITOR_H_
#define __SETCARDEDITOR_H_

#include <QWidget>

class SetCard;

// widgets
class SetCardWidget;
class QComboBox;
class QSpinBox;
// layouts
class QHBoxLayout;
class QVBoxLayout;


class SetCardEditor : public QWidget
{
    Q_OBJECT
  public:
    SetCardEditor(QWidget* pParent = 0);
    ~SetCardEditor();
    void setSetCard(SetCard* pSetCard);
  public slots:
    void updateCard();
    void updateOptions();
  private:
    // parts of constructor
    void createGui();
    // widgets
    SetCardWidget* wdgSetCard;
    QComboBox*     cmbShape;
    QComboBox*     cmbFill;
    QComboBox*     cmbColor;
    QComboBox*     cmbCount;
    // layouts
    QHBoxLayout* layoutParent;
    QVBoxLayout* layoutOptions;
    // member vars
    SetCard* m_pSetCard;
};

#endif

