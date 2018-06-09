
// testDlg.h : 头文件
//

#pragma once


// CtestDlg 对话框
class CtestDlg : public CDialogEx
{
// 构造
public:
	CtestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBexit();
	afx_msg void OnBnClickedRswitch();
	afx_msg void OnBnClickedRmode();
	afx_msg void OnBnClickedRswitchA();
	afx_msg void OnBnClickedRspeedA();
	afx_msg void OnBnClickedRswitchB();
	afx_msg void OnBnClickedRspeedB();
	afx_msg void OnBnClickedBoutalogCenter();
	afx_msg void OnBnClickedBoutblogCenter();
	afx_msg void OnBnClickedBrealtemperatureA();
	afx_msg void OnBnClickedBsettemperatureA();
	afx_msg void OnBnClickedBrealtemperatureB();
	afx_msg void OnBnClickedBsettemperatureB();
	int switch_choice;
	int mode_choice;
	int switch_A_choice;
	int speed_A_choice;
	int switch_B_choice;
	int speed_B_choice;
	int realtemperature_A;
	int settemperature_A;
	int realtemperature_B;
	int settemperature_B;
	float A_charge;
	float B_charge;
};


class center
{
public:
	int state;//当前状态：0关；1待机(开)；2工作(开)。
	int mode;//模式：0供暖；1制冷。
	float A_charge;//房间A费用
	float B_charge;//房间B费用
	center();//构造函数
};

class room
{
public:
	int state;//当前状态：0关；1待机(开)；2工作(开)。
	int statenum;//开关机次数
	int speed[100];//风速：0高；1中；2低。
	CTime starttime[100];//请求开始时间
	CTime endtime[100];//请求结束时间
	int settemperature[100];//请求设置温度
	int startrealtemperature[100];//请求开始时实际温度
	int endrealtemperature[100];//请求结束时实际温度
	int num;//请求次数
	room();//构造函数
};


UINT GetTime(LPVOID pParam);//获取当前时间
UINT GetMode(LPVOID pParam);//获取中央空调当前工作模式
UINT GetCenterState(LPVOID pParam);//获取中央空调当前工作状态
UINT GetRoomAState(LPVOID pParam);//获取房间A当前工作状态
UINT GetRoomBState(LPVOID pParam);//获取房间B当前工作状态
UINT ChangeCenterState(LPVOID pParam);//改变中央空调当前工作状态
UINT ChangeRoomAState(LPVOID pParam);//改变房间A当前工作状态
UINT ChangeRoomBState(LPVOID pParam);//改变房间B当前工作状态
UINT GetCenterACharge(LPVOID pParam);//获取中央空调房间A费用
UINT GetCenterBCharge(LPVOID pParam);//获取中央空调房间B费用
UINT GetRoomARealTemperature(LPVOID pParam);//获取房间A实际温度
UINT GetRoomBRealTemperature(LPVOID pParam);//获取房间B实际温度
UINT ChangeRoomARealTemperature(LPVOID pParam);//改变房间A实际温度
UINT ChangeRoomBRealTemperature(LPVOID pParam);//改变房间B实际温度
CString CTimeConvertToCString(CTime ct);//将时间转化为CString型变量
UINT ChangeRoomACharge(LPVOID pParam);//改变房间A费用
UINT ChangeRoomBCharge(LPVOID pParam);//改变房间B费用