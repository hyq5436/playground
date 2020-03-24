#pragma execution_character_set("utf-8")
#include "MeetingListView.h"
#include "ui_MeetingListView.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include "MeetingListViewDelegate.h"

MeetingListView::MeetingListView(QWidget* parent) : QListView(parent) {
    ui = new Ui::MeetingListView();
    ui->setupUi(this);

    m_pModel = new QStandardItemModel;
    m_pDelegate = new MeetingListViewDelegate(this);
    this->setModel(m_pModel);
    this->setItemDelegate(m_pDelegate);

    auto* pItem = new QStandardItem();
    pItem->setData(QString("项目沟通会"), MLRT_TOPIC);
    pItem->setData(0, MLRT_MEETING_TYPE);
    pItem->setData(QString("胡寅秋 09:30 (直播号123456)"), MLRT_CREATOR);
    m_pModel->appendRow(pItem);
    pItem = new QStandardItem();
    pItem->setData(QString("项目沟通会"), MLRT_TOPIC);
    pItem->setData(1, MLRT_MEETING_TYPE);
    pItem->setData(QString("胡寅秋 09:30 (直播号123456)"), MLRT_CREATOR);
    m_pModel->appendRow(pItem);
    pItem = new QStandardItem();
    pItem->setData(QString("项目沟通会"), MLRT_TOPIC);
    pItem->setData(0x11, MLRT_MEETING_TYPE);
    pItem->setData(QString("胡寅秋 09:30 (直播号123456)"), MLRT_CREATOR);
    m_pModel->appendRow(pItem);
    pItem = new QStandardItem();
    pItem->setData(QString("项目沟通会"), MLRT_TOPIC);
    pItem->setData(1, MLRT_MEETING_TYPE);
    pItem->setData(QString("胡寅秋 09:30 (直播号123456)"), MLRT_CREATOR);
    m_pModel->appendRow(pItem);
}

MeetingListView::~MeetingListView() {
    delete ui;
}

void MeetingListView::addItem(const CVideoConfHistoryInfo& info) {
    auto* pItem = new QStandardItem();
    pItem = new QStandardItem();

    // 会议类型
    pItem->setData(info.getType(), MLRT_MEETING_TYPE);

    // 创建时间
    pItem->setData(info.getCreatTime(), MLRT_TIME);

    // 主题
    pItem->setData(info.getConfSubject(), MLRT_TOPIC);

    // 创建人
    pItem->setData(info.getCreatorName(), MLRT_CREATOR);

    // 会议状态
    pItem->setData(info.getCreatorName(), MLRT_MEETING_STATUS);

    m_pModel->appendRow(pItem);
}

void MeetingListView::addItems(const QList<CVideoConfHistoryInfo>& infos) {
    for (auto& info : infos) {
        addItem(info);
    }
}
