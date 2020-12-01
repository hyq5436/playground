#include "Chart3DWidget.h"
#include "./ui_Chart3DWidget.h"

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QThread>
#include <QTimer>
#include "mgl2/canvas_wnd.h"

namespace {
    std::vector<double> g_data_x{
        0, 0, 0
    };
    std::vector<double> g_data_y{
    0, 0, 0
    };
    std::vector<double> g_data_z{
    0, 0, 0
    };
    mglData data_x;
    mglData data_y;
    mglData data_z;
    static int count = 0;
}

int example(mglGraph* gr)
{
    gr->Alpha(true);
    gr->Light(false);
    gr->SetTranspType(0);
    char background_color[] = {22, 20, 24};
    //gr->Clf(22, 20, 24);
    gr->Clf();
    gr->Clf(background_color);
    //gr->Clf(22, 20, 24);
    {
        gr->SetRanges(0, 4, -1, 1, 0, 8);
        if (data_x[count] > 4) {
            gr->SetRanges(data_x[count] - 4, data_x[count], -1, 1, 0, 8);
        }
        gr->SetTickLen(0.01);
        gr->Title("SLT", "", -1.5);

    	gr->Rotate(50, 60);
        //gr->Box("b3");
        gr->Axis("xyzUAKDTVISO", "{x0089cb}-3");
        gr->Grid("xyz", "{x007381}-");
        //gr->Label('x', "#W{X}", 1);   gr->Label('y', "Y", 0);   gr->Label('z', "Z", 1);
        gr->Label('x', "X", 1);   gr->Label('y', "Y", 1);   gr->Label('z', "Z", 1);
    }


    mglPoint pntStart;
    mglPoint pntEnd;
    for (int i = count, j = 0; i >= 0 && j < 50; i--, j++)
    {
        pntStart = mglPoint(data_x[i - 1], data_y[i - 1], data_z[i - 1]);
        pntEnd = mglPoint(data_x[i], data_y[i], data_z[i]);
        gr->Line(pntStart, pntEnd, "r2");
    }

int start = data_x[count];
{
    mglPoint p1(start, 0, 1);
    mglPoint p2(start + 1, 0, 1);
    mglPoint p3(start, 1, 1);
    mglPoint p4(start + 1, 1, 1);
    gr->Face(p1, p2, p3, p4);
}

{
    mglPoint p1(start, 0, 3);
    mglPoint p2(start + 1, 0, 3);
    mglPoint p3(start, 1, 3);
    mglPoint p4(start + 1, 1, 3);
    gr->Face(p1, p2, p3, p4);
}

{
    mglPoint p1(start, 0, 1);
    mglPoint p2(start, 1, 1);
    mglPoint p3(start, 0, 3);
    mglPoint p4(start, 1, 3);
    gr->Face(p1, p2, p3, p4);
}

{
    mglPoint p1(start + 1, 0, 1);
    mglPoint p2(start + 1, 1, 1);
    mglPoint p3(start + 1, 0, 3);
    mglPoint p4(start + 1, 1, 3);
    gr->Face(p1, p2, p3, p4);
}

{
    mglPoint p1(start, 0, 1);
    mglPoint p2(start + 1, 0, 1);
    mglPoint p3(start, 0, 3);
    mglPoint p4(start + 1, 0, 3);
    gr->Face(p1, p2, p3, p4);
}

{
    mglPoint p1(start, 1, 1);
    mglPoint p2(start + 1, 1, 1);
    mglPoint p3(start, 1, 3);
    mglPoint p4(start + 1, 1, 3);
    gr->Face(p1, p2, p3, p4);
}
    return 0;
}

Chart3DWidget::Chart3DWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chart3DWidget)
{
    ui->setupUi(this);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(22, 20, 24));
    setPalette(pal);

    // generate data
    {
        g_data_x.resize(200);
        g_data_y.resize(200);
        g_data_z.resize(200);
        for (int i = 0; i < 200; i++) {
            double x = 0.08 * i;
            double y = sin(x);
            g_data_x[i] = x;
            g_data_y[i] = y;
            g_data_z[i] = 4;
        }
        data_x.Set(g_data_x);
        data_y.Set(g_data_y);
        data_z.Set(g_data_z);
    }

    mglGraph gr(0, width(), height());
    ui->qgr->setGraph(&gr);
    ui->qgr->setDraw(example);
    ui->qgr->setDotsPreview(false);
    ui->qgr->setRotate(true);
    ui->qgr->setZoom(false);
    ui->qgr->update();

    QTimer* pTimer = new QTimer(this);
    pTimer->setInterval(100);
    connect(pTimer, &QTimer::timeout, this, [this, pTimer]() {
        count++;
        ui->qgr->update();
        if (count >= 199)
        {
            pTimer->stop();
            return;
        }
     });
    connect(ui->btnShift, &QPushButton::clicked, this, [this, pTimer](bool) {
        pTimer->start();
    });

}

Chart3DWidget::~Chart3DWidget()
{
    delete ui;
}

void Chart3DWidget::paintEvent(QPaintEvent* e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(e);
#if 0
    mglGraph gr(0, width(), height());

    gr.Alpha(true);
    gr.Light(true);
    example(&gr);

    // Qt don't support RGB format as is. So, let convert it to BGRN.
    long w = gr.GetWidth(), h = gr.GetHeight();
    unsigned char* buf = new uchar[4 * w * h];
    gr.GetBGRN(buf, 4 * w * h);
    QPixmap pic = QPixmap::fromImage(QImage(buf, w, h, QImage::Format_ARGB32));
    QPainter paint;
    paint.begin(this);  paint.drawPixmap(0, 0, pic);  paint.end();
    delete[]buf;
#endif
}
