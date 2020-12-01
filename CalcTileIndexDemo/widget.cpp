#pragma execution_character_set("utf-8")
#define _USE_MATH_DEFINES
#include "widget.h"
#include "ui_widget.h"
#include "TransformClassBing.h"
#include "TransformClassSlippy.h"
#include "TransformClassTMS.h"

#include <memory>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lblQuadKey->setVisible(false);
    ui->edtQuadKey->setVisible(false);
    connect(ui->tileTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        if (index == 2) {
            ui->lblQuadKey->setVisible(true);
            ui->edtQuadKey->setVisible(true);
        }
        else
        {
            ui->lblQuadKey->setVisible(false);
            ui->edtQuadKey->setVisible(false);
        }
    });

    // 
    // 0: ¹È¸èXYZ
    // 1: TMS
    // 2: QuadTree
    // 3: °Ù¶ÈXYZ
    connect(ui->btnLatLongToXY, &QPushButton::clicked, this, [this](bool) {
        int index = ui->tileTypeComboBox->currentIndex();
        int level = ui->levelSpinBox->value();
        double lng = ui->edtLong->text().toDouble();
        double lat = ui->edtLat->text().toDouble();
        if (index == 0)
        {
            std::unique_ptr<TransformClassNormal> pTransform(new TransformClassNormal(20, 0));
            int tileX = pTransform->lngToTileX(lng, level);
            int tileY = pTransform->latToTileY(lat, level);
            setXY(tileX, tileY);
        }
        else if (index == 1)
        {
            std::unique_ptr<TransformClassTMS> pTransform(new TransformClassTMS(20, 0));
            int tileX = pTransform->lngToTileX(lng, level);
            int tileY = pTransform->latToTileY(lat, level);
            setXY(tileX, tileY);
        }
        else if (index == 2)
        {
            std::unique_ptr<TransformClassBing> pTransform(new TransformClassBing(20, 0));
            int tileX = pTransform->lngToTileX(lng, level);
            int tileY = pTransform->latToTileY(lat, level);
            setXY(tileX, tileY);
            std::string strQuadKey = pTransform->lnglatToQuadkey(tileX, tileY, level);
            ui->edtQuadKey->setText(QString::fromStdString(strQuadKey));
        }
    });
    connect(ui->btnXYToLatLong, &QPushButton::clicked, this, [this](bool) {
        int index = ui->tileTypeComboBox->currentIndex();
        if (index == 0)
        {
            auto* pTransformClassNormal = new TransformClassNormal(20, 0);
            double longitude = pTransformClassNormal->pixelXTolng(0, ui->edtTileX->text().toInt(), ui->levelSpinBox->value());
            double latitude = pTransformClassNormal->pixelYToLat(0, ui->edtTileY->text().toInt(), ui->levelSpinBox->value());
            setLongLat(longitude, latitude);
        }
        else if (index == 1)
        {
            auto* pTransformClassNormal = new TransformClassNormal(20, 0);
            double longitude = pTransformClassNormal->pixelXTolng(0, ui->edtTileX->text().toInt(), ui->levelSpinBox->value());
            double latitude = pTransformClassNormal->pixelYToLat(0, ui->edtTileY->text().toInt(), ui->levelSpinBox->value());
            setLongLat(longitude, latitude);
        }
        else if (index == 2)
        {
            auto* pTransformClassNormal = new TransformClassBing(20, 0);
            double longitude = pTransformClassNormal->pixelXTolng(0, ui->edtTileX->text().toInt(), ui->levelSpinBox->value());
            double latitude = pTransformClassNormal->pixelYToLat(0, ui->edtTileY->text().toInt(), ui->levelSpinBox->value());
            setLongLat(longitude, latitude);
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setXY(const int x, const int y)
{
    ui->edtTileX->setText(QString::number(x));
    ui->edtTileY->setText(QString::number(y));

}

void Widget::setLongLat(double longitude, double latitude)
{
    ui->edtLong->setText(QString::number(longitude, 'g', 10));
    ui->edtLat->setText(QString::number(latitude, 'g', 10));
}