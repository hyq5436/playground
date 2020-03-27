#include "AnimatedLabel.h"
#include <QPainter>

AnimatedLabel::AnimatedLabel(const QString &image, const int imageCount,
                             QWidget *parent)
    : QLabel(parent), currentPixmap(0)
{
  ui.setupUi(this);
  setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::Tool);
  setAttribute(Qt::WA_TranslucentBackground);
  QPixmap pixmap;
  for (int i = 0; i < 30; i++) {
    pixmap.load(QString("GiftAnimation/gift_%1").arg(i, 2, 10, QChar('0')));
    pixmaps.push_back(pixmap);
  }

  connect(&timer, SIGNAL(timeout()), SLOT(changeImage()));
  timer.start(100);
  changeImage();
}

void AnimatedLabel::changeImage() {
  if (currentPixmap >= pixmaps.length()) {
    currentPixmap = 0;
  } else {
    setPixmap(pixmaps.at(currentPixmap));
    currentPixmap++;
  }
}

AnimatedLabel::~AnimatedLabel()
{
}
