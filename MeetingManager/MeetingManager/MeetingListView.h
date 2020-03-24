#pragma once

#include <QListView>
namespace Ui { class MeetingListView; };

class QStandardItemModel;
class MeetingListViewDelegate;
class CVideoConfHistoryInfo
{
public:
	CVideoConfHistoryInfo();

	~CVideoConfHistoryInfo();

	void setRoomID(const QString& strRoomID)
	{
		m_strRoomID = strRoomID;
	}
	QString getRoomID() const
	{
		return m_strRoomID;
	}

	void setCreatorID(const QString& strCreatorID)
	{
		m_strCreatorID = strCreatorID;
	}
	QString getCreatorID() const
	{
		return m_strCreatorID;
	}

	void setConfSubject(const QString& strSubject)
	{
		m_strConfSubject = strSubject;
	}
	QString getConfSubject() const
	{
		return m_strConfSubject;
	}

	void setCreatTime(qint64 iCreatTime)
	{
		m_iConfCreatTime = iCreatTime;
	}
	qint64 getCreatTime() const
	{
		return m_iConfCreatTime;
	}

	void setRoomNumber(const QString& strNumber)
	{
		m_strRoomNumber = strNumber;
	}
	QString getRoomNumber() const
	{
		return m_strRoomNumber;
	}

	void setDurationTime(const qint64 iDuration)
	{
		m_iDurationTime = iDuration;
	}
	qint64 getDurationTime() const
	{
		return m_iDurationTime;
	}

	void setIsJoined(bool bIsJoin)
	{
		m_bIsJoined = bIsJoin;
	}
	bool getIsJoined() const
	{
		return m_bIsJoined;
	}

	void setCreatorName(const QString& strName)
	{
		m_strCreatorName = strName;
	}
	QString getCreatorName() const
	{
		return m_strCreatorName;
	}

	void setCreatorIcon(const QString& strIcon)
	{
		m_strCreatorIcon = strIcon;
	}
	QString getCreatorIcon() const
	{
		return m_strCreatorIcon;
	}

	void setType(int nType)
	{
		m_nMeetingType = nType;
	}
	int getType() const
	{
		return m_nMeetingType;
	}

private:
	QString m_strRoomID;      //房间ID
	QString m_strRoomNumber;  // 房间编号
	QString m_strCreatorID;   //创建者ID
	QString m_strCreatorName; // 创建者名称
	QString m_strCreatorIcon; // 创建者头像
	QString m_strConfSubject; // 会议主题
	qint64  m_iConfCreatTime; //会议创建时间
	qint64  m_iDurationTime;  // 会议时长
	bool    m_bIsJoined;      // 是否已加入过
	int     m_nMeetingType;   // 会议类型 0-直播会议,10-语音会议,11-视频会议
};

class MeetingListView : public QListView {
    Q_OBJECT

public:
    MeetingListView(QWidget* parent = Q_NULLPTR);
    ~MeetingListView();
    void addItem(const CVideoConfHistoryInfo& info);
    void addItems(const QList<CVideoConfHistoryInfo>& infos);

private:
    Ui::MeetingListView* ui;
    QStandardItemModel* m_pModel;
    MeetingListViewDelegate* m_pDelegate;
};
