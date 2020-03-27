#pragma once

#include <QPushButton>

class QMenu;
class QMouseEvent;
class QPaintEvent;
class OptionPushButton : public QPushButton {
  Q_OBJECT

 public:
  OptionPushButton(QWidget* parent);
  ~OptionPushButton();

  bool event(QEvent* e) override;
  void paintEvent(QPaintEvent* event) override;

  // add option menu
  void addMenu(QMenu* menu);

signals:
    void signal_ActionButtonPressed(QAction* action);

 private:
  QRect getArrowRect();
  bool shouldShowMenu();
  bool isOptionEnabled();
  QAction* showMenu();
  QAction* getCheckedAction();
  bool handleMouseMoveEvent(QMouseEvent* e);
  bool handleMousePressEvent(QMouseEvent* e);


  QMenu* m_pMenu;
};
