#pragma once

#include <QStyledItemDelegate>
#include <QString>

enum MeetingListRoleType {
    MLRT_TOPIC = Qt::UserRole + 1,  // 主题
    MLRT_CREATOR,                   // 创建人
    MLRT_TIME,                      // 创建时间
    MLRT_MEETING_NUMBER,            // 直播号/房间号
    MLRT_MEETING_TYPE,              // 会议类型 0-直播会议,10-语音会议,11-视频会议
    MLRT_MEETING_STATUS,            // 会议状态(0 - 正在进行; 1- 已结束)
};

struct MLVDParam {
    static const int iRowHeight = 76;
    static const int iPaddingLeft = 20;                   // 20px
    static const int iIconPaddingTop = 14;                   // 20px
    static const int iIconWidth = 50;                   // 20px
    static const int iIconHeight = 48;                   // 20px
    static const int iPaddingBetweenIconAndTopic = 10;  // 5px
    static const int iTopicPaddingTop = 16;               // 16px
    static const int iTopicHeight = 20;                   // 20px
    static const int iPaddingBetweenTopicAndCreator = 5;  // 5px
    static const int iCreatorAndTimeHeight = 18;          // 18px
    static const int iPaddingRight = 20;                  // 20px
    static const int iButtonPaddingTop = 26;                  // 20px
    static const int iMinimumButtonWidth = 69;
    static const int iButtonHeight = 24;
    static const int iPaddingButton = 15;                // 15px
};

class MeetingListViewDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    MeetingListViewDelegate(QWidget* parent);
    ~MeetingListViewDelegate();

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    QString getSecondLine(const QModelIndex& index) const;
    QRect getDatailOrJoinRect(const QStyleOptionViewItem& option) const;
    QRect getLaunchRect(const QStyleOptionViewItem& option) const;
    void drawButton(QPainter* painter, const QRect& rect, const QString& text) const;

signals:
    void signal_CheckDetail(const QString& no);
    void signal_ReCreate(const QString& no);
    void signal_Join(const QString& no);

private:
    QWidget* m_parent;
};
