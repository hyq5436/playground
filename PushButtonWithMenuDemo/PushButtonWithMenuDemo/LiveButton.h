#pragma once

#include <QPushButton>

class QMouseEvent;
class QPaintEvent;
class LiveButton : public QPushButton {
    Q_OBJECT

public:
    LiveButton(QWidget* parent);
    ~LiveButton();

    bool event(QEvent* e) override;
    void paintEvent(QPaintEvent* event) override;

    QSize sizeHint() const override;

    void setData(QChar icon, const QString& text);
    void setIcon(QChar normalIcon);
    void setCheckedIcon(QChar checkedIcon);
    void setCheckedText(const QString& text);

private:
    bool handleMouseMoveEvent(QMouseEvent* e);
    bool handleMousePressEvent(QMouseEvent* e);

    QChar m_normalIcon;
    QChar m_checkedIcon;
    QString m_checkedText;
};
