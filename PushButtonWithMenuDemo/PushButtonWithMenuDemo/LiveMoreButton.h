#pragma once

#include <QPushButton>

class LiveMoreButton : public QPushButton {
    Q_OBJECT

public:
    LiveMoreButton(QWidget* parent);
    ~LiveMoreButton();

    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;
};
