
// testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


center::center()//构造函数
{
	state=0;
	mode=0;
	A_charge=0;
	B_charge=0;
}

room::room()//构造函数
{
	state=0;
	statenum=0;
	for(int i=0;i<100;i++)
	{
		speed[i]=0;
		starttime[i]=0;
		endtime[i]=0;
		settemperature[i]=0;
	    startrealtemperature[i]=0;
	    endrealtemperature[i]=0;
	}
	num=0;
}

CtestDlg* dlg_backup;
center *center_control;
room *room_A,*room_B;

// CtestDlg 对话框




CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestDlg::IDD, pParent)
	, switch_choice(1)
	, mode_choice(0)
	, switch_A_choice(1)
	, speed_A_choice(0)
	, switch_B_choice(1)
	, speed_B_choice(0)
	, realtemperature_A(0)
	, settemperature_A(0)
	, realtemperature_B(0)
	, settemperature_B(0)
	, A_charge(0)
	, B_charge(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RSWITCHOPEN_CENTER, switch_choice);
	DDX_Radio(pDX, IDC_RMODEHOT_CENTER, mode_choice);
	DDX_Radio(pDX, IDC_RSWITCHOPEN_A, switch_A_choice);
	DDX_Radio(pDX, IDC_RSPEEDHIGH_A, speed_A_choice);
	DDX_Radio(pDX, IDC_RSWITCHOPEN_B, switch_B_choice);
	DDX_Radio(pDX, IDC_RSPEEDHIGH_B, speed_B_choice);
	DDX_Text(pDX, IDC_EREALTEMPERATURE_A, realtemperature_A);
	DDX_Text(pDX, IDC_ESETTEMPERATURE_A, settemperature_A);
	DDX_Text(pDX, IDC_EREALTEMPERATURE_B, realtemperature_B);
	DDX_Text(pDX, IDC_ESETTEMPERATURE_B, settemperature_B);
	DDX_Text(pDX, IDC_EACHARGE_CENTER, A_charge);
	DDX_Text(pDX, IDC_EBCHARGE_CENTER, B_charge);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEXIT, &CtestDlg::OnBnClickedBexit)
	ON_BN_CLICKED(IDC_RSWITCHOPEN_CENTER, &CtestDlg::OnBnClickedRswitch)
	ON_BN_CLICKED(IDC_RSWITCHCLOSE_CENTER, &CtestDlg::OnBnClickedRswitch)
	ON_BN_CLICKED(IDC_RMODEHOT_CENTER, &CtestDlg::OnBnClickedRmode)
	ON_BN_CLICKED(IDC_RMODECOLD_CENTER, &CtestDlg::OnBnClickedRmode)
	ON_BN_CLICKED(IDC_RSWITCHOPEN_A, &CtestDlg::OnBnClickedRswitchA)
	ON_BN_CLICKED(IDC_RSWITCHCLOSE_A, &CtestDlg::OnBnClickedRswitchA)
	ON_BN_CLICKED(IDC_RSPEEDHIGH_A, &CtestDlg::OnBnClickedRspeedA)
	ON_BN_CLICKED(IDC_RSPEEDMIDDLE_A, &CtestDlg::OnBnClickedRspeedA)
	ON_BN_CLICKED(IDC_RSPEEDLOW_A, &CtestDlg::OnBnClickedRspeedA)
	ON_BN_CLICKED(IDC_RSWITCHOPEN_B, &CtestDlg::OnBnClickedRswitchB)
	ON_BN_CLICKED(IDC_RSWITCHCLOSE_B, &CtestDlg::OnBnClickedRswitchB)
	ON_BN_CLICKED(IDC_RSPEEDHIGH_B, &CtestDlg::OnBnClickedRspeedB)
	ON_BN_CLICKED(IDC_RSPEEDMIDDLE_B, &CtestDlg::OnBnClickedRspeedB)
	ON_BN_CLICKED(IDC_RSPEEDLOW_B, &CtestDlg::OnBnClickedRspeedB)
	ON_BN_CLICKED(IDC_BOUTALOG_CENTER, &CtestDlg::OnBnClickedBoutalogCenter)
	ON_BN_CLICKED(IDC_BOUTBLOG_CENTER, &CtestDlg::OnBnClickedBoutblogCenter)
	ON_BN_CLICKED(IDC_BREALTEMPERATURE_A, &CtestDlg::OnBnClickedBrealtemperatureA)
	ON_BN_CLICKED(IDC_BSETTEMPERATURE_A, &CtestDlg::OnBnClickedBsettemperatureA)
	ON_BN_CLICKED(IDC_BREALTEMPERATURE_B, &CtestDlg::OnBnClickedBrealtemperatureB)
	ON_BN_CLICKED(IDC_BSETTEMPERATURE_B, &CtestDlg::OnBnClickedBsettemperatureB)
END_MESSAGE_MAP()


// CtestDlg 消息处理程序

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//获取系统时间
	int year=SystemTime.wYear;
	int month=SystemTime.wMonth;
	int day=SystemTime.wDay;
	int week=SystemTime.wDayOfWeek;
	int hour=SystemTime.wHour;
	int minute=SystemTime.wMinute;
	int second=SystemTime.wSecond;
	CString cstr_time=_T("");
	switch(week)
	{
	    case 0:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期日 %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 1:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期一 %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 2:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期二 %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 3:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期三 %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 4:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期四 %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 5:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期五 %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 6:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期六 %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		default:{break;}
	}
	SetDlgItemText(IDC_STIME,cstr_time);
	dlg_backup=this;
	center_control=new center();
    room_A=new room();
	room_B=new room();
	realtemperature_A=25;
	settemperature_A=25;
	realtemperature_B=25;
	settemperature_B=25;
	SetDlgItemText(IDC_EREALTEMPERATURE_A,_T("25"));
	SetDlgItemText(IDC_ESETTEMPERATURE_A,_T("25"));
	SetDlgItemText(IDC_EREALTEMPERATURE_B,_T("25"));
	SetDlgItemText(IDC_ESETTEMPERATURE_B,_T("25"));
	HANDLE thread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetTime,NULL,0,NULL);//启动多线程(获取当前时间)
	HANDLE thread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetMode,NULL,0,NULL);//启动多线程(获取中央空调当前工作模式)
	HANDLE thread3 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetCenterState,NULL,0,NULL);//启动多线程(获取中央空调当前工作状态)
	HANDLE thread4 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomAState,NULL,0,NULL);//启动多线程(获取房间A当前工作状态)
	HANDLE thread5 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomBState,NULL,0,NULL);//启动多线程(获取房间B当前工作状态)
	HANDLE thread6 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeCenterState,NULL,0,NULL);//启动多线程(改变中央空调当前工作状态)
	HANDLE thread7 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomAState,NULL,0,NULL);//启动多线程(改变房间A当前工作状态)
	HANDLE thread8 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomBState,NULL,0,NULL);//启动多线程(改变房间B当前工作状态)
	HANDLE thread9 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetCenterACharge,NULL,0,NULL);//启动多线程(获取中央空调房间A费用)
	HANDLE thread10 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetCenterBCharge,NULL,0,NULL);//启动多线程(获取中央空调房间B费用)
	HANDLE thread11 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomARealTemperature,NULL,0,NULL);//启动多线程(获取房间A实际温度)
	HANDLE thread12 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomBRealTemperature,NULL,0,NULL);//启动多线程(获取房间B实际温度)
	HANDLE thread13 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomARealTemperature,NULL,0,NULL);//启动多线程(改变房间A实际温度)
	HANDLE thread14 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomBRealTemperature,NULL,0,NULL);//启动多线程(改变房间B实际温度)
	HANDLE thread15 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomACharge,NULL,0,NULL);//启动多线程(改变房间A费用)
	HANDLE thread16 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomBCharge,NULL,0,NULL);//启动多线程(改变房间B费用)
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDlg::OnBnClickedBexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

UINT GetTime(LPVOID pParam)//获取当前时间
{
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//获取系统时间
	int year;
	int month;
	int day;
	int week;
	int hour;
	int minute;
	int oldsecond=SystemTime.wSecond;
	int newsecond=SystemTime.wSecond;
	CString cstr_time=_T("");
    while(1)
    {
	    GetLocalTime(&SystemTime);//获取系统时间
		newsecond=SystemTime.wSecond;
		if(newsecond!=oldsecond)
		{
			oldsecond=newsecond;
			year=SystemTime.wYear;
	        month=SystemTime.wMonth;
	        day=SystemTime.wDay;
	        week=SystemTime.wDayOfWeek;
	        hour=SystemTime.wHour;
	        minute=SystemTime.wMinute;
			switch(week)
	        {
	            case 0:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期日 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 1:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期一 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 2:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期二 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 3:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期三 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 4:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期四 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 5:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期五 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 6:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期六 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        default:{break;}
	        }
	        dlg_backup->SetDlgItemText(IDC_STIME,cstr_time);
        }
	}
}

void CtestDlg::OnBnClickedRswitch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedRmode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(mode_choice==0)//供暖
	{
		center_control->mode=0;
	}
	else if(mode_choice==1)//制冷
	{
		center_control->mode=1;
	}
}


void CtestDlg::OnBnClickedRswitchA()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedRspeedA()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(room_A->state==2)//工作
	{
		SYSTEMTIME SystemTime;
	    GetLocalTime(&SystemTime);//获取系统时间
		int num=room_A->num;//防止多线程时出现冲突
		if(num>=0)
		{
			room_A->endtime[num]=SystemTime;
			room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		}
		room_A->num++;
		num=room_A->num;//防止多线程时出现冲突
		room_A->speed[num]=speed_A_choice;
		room_A->starttime[num]=SystemTime;
		room_A->settemperature[num]=dlg_backup->settemperature_A;
		room_A->startrealtemperature[num]=dlg_backup->realtemperature_A;
	}
}


void CtestDlg::OnBnClickedRswitchB()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedRspeedB()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(room_B->state==2)//工作
	{
		SYSTEMTIME SystemTime;
	    GetLocalTime(&SystemTime);//获取系统时间
		int num=room_B->num;//防止多线程时出现冲突
		if(num>=0)
		{
			room_B->endtime[num]=SystemTime;
			room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		}
		room_B->num++;
		num=room_B->num;//防止多线程时出现冲突
		room_B->speed[num]=speed_B_choice;
		room_B->starttime[num]=SystemTime;
		room_B->settemperature[num]=dlg_backup->settemperature_B;
		room_B->startrealtemperature[num]=dlg_backup->realtemperature_B;
	}
}


void CtestDlg::OnBnClickedBoutalogCenter()
{
	// TODO: 在此添加控件通知处理程序代码
	errno_t err;
	FILE *fp_write;
	err=fopen_s(&fp_write,"log_A.txt","w");
	if(err!=0)
	{
		AfxMessageBox(_T("日志导出出错"),MB_OK,NULL);
		return;
	}
	fprintf(fp_write,"房间号：房间A\n\n");
	fprintf(fp_write,"总开关机次数：%d\n\n",room_A->statenum);
	int num=room_A->num;//防止多线程时出现冲突
	for(int i=0;i<num;i++)
	{
		fprintf(fp_write,"温控请求开始时间:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_A->starttime[i])));
		fprintf(fp_write,"温控请求结束时间:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_A->endtime[i])));
		fprintf(fp_write,"温控请求开始实际温度:%d\n",room_A->startrealtemperature[i]);
		fprintf(fp_write,"温控请求结束实际温度:%d\n",room_A->endrealtemperature[i]);
		fprintf(fp_write,"温控请求设定温度:%d\n",room_A->settemperature[i]);
		float rate=-1;
		if(room_A->speed[i]==0)
		{
			rate=1.3;
			fprintf(fp_write,"温控请求风量大小:高\n");
		}
		else if(room_A->speed[i]==1)
		{
			rate=1;
			fprintf(fp_write,"温控请求风量大小:中\n");
		}
		else if(room_A->speed[i]==2)
		{
			rate=0.8;
			fprintf(fp_write,"温控请求风量大小:低\n");
		}
		float charge=0;
		CTimeSpan span=(CTime)room_A->endtime[i]-(CTime)room_A->starttime[i];
		long seconds=span.GetTotalSeconds();
		charge=seconds*rate*5;
		fprintf(fp_write,"温控请求此次费用:%g\n\n",charge);
	}
	fclose(fp_write);
	AfxMessageBox(_T("房间A日志导出成功，文件位于此程序当前目录下的\"log_A.txt\"中"),MB_OK,NULL);
}


void CtestDlg::OnBnClickedBoutblogCenter()
{
	// TODO: 在此添加控件通知处理程序代码
	errno_t err;
	FILE *fp_write;
	err=fopen_s(&fp_write,"log_B.txt","w");
	if(err!=0)
	{
		AfxMessageBox(_T("日志导出出错"),MB_OK,NULL);
		return;
	}
	fprintf(fp_write,"房间号：房间B\n\n");
	fprintf(fp_write,"总开关机次数：%d\n\n",room_B->statenum);
	int num=room_B->num;//防止多线程时出现冲突
	for(int i=0;i<num;i++)
	{
		fprintf(fp_write,"温控请求开始时间:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_B->starttime[i])));
		fprintf(fp_write,"温控请求结束时间:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_B->endtime[i])));
		fprintf(fp_write,"温控请求开始实际温度:%d\n",room_B->startrealtemperature[i]);
		fprintf(fp_write,"温控请求结束实际温度:%d\n",room_B->endrealtemperature[i]);
		fprintf(fp_write,"温控请求设定温度:%d\n",room_B->settemperature[i]);
		float rate=-1;
		if(room_B->speed[i]==0)
		{
			rate=1.3;
			fprintf(fp_write,"温控请求风量大小:高\n");
		}
		else if(room_B->speed[i]==1)
		{
			rate=1;
			fprintf(fp_write,"温控请求风量大小:中\n");
		}
		else if(room_B->speed[i]==2)
		{
			rate=0.8;
			fprintf(fp_write,"温控请求风量大小:低\n");
		}
		float charge=0;
		CTimeSpan span=(CTime)room_B->endtime[i]-(CTime)room_B->starttime[i];
		long seconds=span.GetTotalSeconds();
		charge=seconds*rate*5;
		fprintf(fp_write,"温控请求此次费用:%g\n\n",charge);
	}
	fclose(fp_write);
	AfxMessageBox(_T("房间B日志导出成功，文件位于此程序当前目录下的\"log_B.txt\"中"),MB_OK,NULL);
}


void CtestDlg::OnBnClickedBrealtemperatureA()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedBsettemperatureA()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(center_control->mode==0)//供暖
	{
		if(settemperature_A<25 || settemperature_A>30)
		{
			AfxMessageBox(_T("供暖模式下设定温度必须为25到30之间的整数，设定有误！"),MB_OK,NULL);
			return;
		}
	}
	else if(center_control->mode==1)//制冷
	{
		if(settemperature_A<18 || settemperature_A>25)
		{
			AfxMessageBox(_T("供暖模式下设定温度必须为18到25之间的整数，设定有误！"),MB_OK,NULL);
			return;
		}
	}
}


void CtestDlg::OnBnClickedBrealtemperatureB()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(center_control->mode==0)//供暖
	{
		if(settemperature_B<25 || settemperature_B>30)
		{
			AfxMessageBox(_T("供暖模式下设定温度必须为25到30之间的整数，设定有误！"),MB_OK,NULL);
			return;
		}
	}
	else if(center_control->mode==1)//制冷
	{
		if(settemperature_B<18 || settemperature_B>25)
		{
			AfxMessageBox(_T("供暖模式下设定温度必须为18到25之间的整数，设定有误！"),MB_OK,NULL);
			return;
		}
	}
}


void CtestDlg::OnBnClickedBsettemperatureB()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

UINT GetMode(LPVOID pParam)//获取中央空调当前工作模式
{
	int lastmode=-1;
	while(1)
	{
		if(center_control->mode!=lastmode)
		{
			if(center_control->mode==0)
			{
				dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_A,_T("中央空调当前工作模式：供暖"));
			    dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_B,_T("中央空调当前工作模式：供暖"));
			}
			else if(center_control->mode==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_A,_T("中央空调当前工作模式：制冷"));
			    dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_B,_T("中央空调当前工作模式：制冷"));
		    }
			lastmode=center_control->mode;
		}
	}
}

UINT GetCenterState(LPVOID pParam)//获取中央空调当前工作状态
{
	int laststate=-1;
	while(1)
	{
		if(center_control->state!=laststate)
		{
			if(center_control->state==0)
			{
				dlg_backup->SetDlgItemText(IDC_SSTATE_CENTER,_T("当前状态：关机"));
			}
			else if(center_control->state==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_CENTER,_T("当前状态：待机"));
		    }
			else if(center_control->state==2)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_CENTER,_T("当前状态：工作"));
		    }
			laststate=center_control->state;
		}
	}
}

UINT GetRoomAState(LPVOID pParam)//获取房间A当前工作状态
{
	int laststate=-1;
	while(1)
	{
		if(room_A->state!=laststate)
		{
			if(room_A->state==0)
			{
				dlg_backup->SetDlgItemText(IDC_SSTATE_A,_T("当前状态：关机"));
			}
			else if(room_A->state==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_A,_T("当前状态：待机"));
		    }
			else if(room_A->state==2)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_A,_T("当前状态：工作"));
		    }
			laststate=room_A->state;
		}
	}
}

UINT GetRoomBState(LPVOID pParam)//获取房间B当前工作状态
{
	int laststate=-1;
	while(1)
	{
		if(room_B->state!=laststate)
		{
			if(room_B->state==0)
			{
				dlg_backup->SetDlgItemText(IDC_SSTATE_B,_T("当前状态：关机"));
			}
			else if(room_B->state==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_B,_T("当前状态：待机"));
		    }
			else if(room_B->state==2)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_B,_T("当前状态：工作"));
		    }
			laststate=room_B->state;
		}
	}
}

UINT ChangeCenterState(LPVOID pParam)//改变中央空调当前工作状态
{
	while(1)
	{
	    if(dlg_backup->switch_choice==0)//开
	    {
		    if(room_A->state!=2 && room_B->state!=2)
		    {
			    center_control->state=1;//待机
		    }
		    else
		    {
		    	center_control->state=2;//工作
		    }
	    }
	    else if(dlg_backup->switch_choice==1)//关
	    {
		    center_control->state=0;//关
	    }
	}
}

UINT ChangeRoomAState(LPVOID pParam)//改变房间A当前工作状态
{
	while(1)
	{
	    if(dlg_backup->switch_A_choice==0)//开
	    {
		    if(center_control->state==0)//中央空调关
		    {
				if(room_A->state==2)//工作
				{
					SYSTEMTIME SystemTime;
	                GetLocalTime(&SystemTime);//获取系统时间
		            int num=room_A->num;//防止多线程时出现冲突
		            room_A->endtime[num]=SystemTime;
				    room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		            room_A->num++;
				    room_A->state=1;//待机
				}
				else if(room_A->state==0)//关机
				{
					room_A->state=1;//待机
				}
		    }
		    else if(room_A->state!=2 && abs(dlg_backup->realtemperature_A-dlg_backup->settemperature_A)>1)//房间A之前待机或关机且温差大于1
		    {
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//获取系统时间
		        int num=room_A->num;//防止多线程时出现冲突
				room_A->speed[num]=dlg_backup->speed_A_choice;
		        room_A->starttime[num]=SystemTime;
				room_A->settemperature[num]=dlg_backup->settemperature_A;
		        room_A->startrealtemperature[num]=dlg_backup->realtemperature_A;
				room_A->state=2;//工作
		    }
			else if(room_A->state!=2 && abs(dlg_backup->realtemperature_A-dlg_backup->settemperature_A)<=1)//房间A之前待机或关机且温差小于等于1
		    {
			    room_A->state=1;//待机
		    }
			else if(room_A->state==2 && abs(dlg_backup->realtemperature_A-dlg_backup->settemperature_A)<0.01)//房间A之前工作且温差小于0.01
			{
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//获取系统时间
		        int num=room_A->num;//防止多线程时出现冲突
		        room_A->endtime[num]=SystemTime;
				room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		        room_A->num++;
				room_A->state=1;//待机
			}
	    }
	    else if(dlg_backup->switch_A_choice==1)//关
	    {
		    if(room_A->state!=0)
		    {
				room_A->statenum++;
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//获取系统时间
		        int num=room_A->num;//防止多线程时出现冲突
		        room_A->endtime[num]=SystemTime;
				room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		        room_A->num++;
				room_A->state=0;//关
		    }
	    }
	}
}

UINT ChangeRoomBState(LPVOID pParam)//改变房间B当前工作状态
{
	while(1)
	{
	    if(dlg_backup->switch_B_choice==0)//开
	    {
		    if(center_control->state==0)//中央空调关
		    {
				if(room_B->state==2)//工作
				{
					SYSTEMTIME SystemTime;
	                GetLocalTime(&SystemTime);//获取系统时间
		            int num=room_B->num;//防止多线程时出现冲突
		            room_B->endtime[num]=SystemTime;
				    room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		            room_B->num++;
				    room_B->state=1;//待机
				}
				else if(room_B->state==0)//关机
				{
					room_B->state=1;//待机
				}
		    }
		    else if(room_B->state!=2 && abs(dlg_backup->realtemperature_B-dlg_backup->settemperature_B)>1)//房间B之前待机或关机且温差大于1
		    {
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//获取系统时间
		        int num=room_B->num;//防止多线程时出现冲突
				room_B->speed[num]=dlg_backup->speed_B_choice;
		        room_B->starttime[num]=SystemTime;
				room_B->settemperature[num]=dlg_backup->settemperature_B;
		        room_B->startrealtemperature[num]=dlg_backup->realtemperature_B;
				room_B->state=2;//工作
		    }
			else if(room_B->state!=2 && abs(dlg_backup->realtemperature_B-dlg_backup->settemperature_B)<=1)//房间B之前待机或关机且温差小于等于1
		    {
			    room_A->state=1;//待机
		    }
			else if(room_B->state==2 && abs(dlg_backup->realtemperature_B-dlg_backup->settemperature_B)<0.01)//房间B之前工作且温差小于0.01
			{
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//获取系统时间
		        int num=room_B->num;//防止多线程时出现冲突
		        room_B->endtime[num]=SystemTime;
				room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		        room_B->num++;
				room_B->state=1;//待机
			}
	    }
	    else if(dlg_backup->switch_B_choice==1)//关
	    {
		    if(room_B->state!=0)
		    {
				room_B->statenum++;
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//获取系统时间
		        int num=room_B->num;//防止多线程时出现冲突
		        room_B->endtime[num]=SystemTime;
				room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		        room_B->num++;
				room_B->state=0;//关
		    }
	    }
	}
}

UINT GetCenterACharge(LPVOID pParam)//获取中央空调房间A费用
{
	float lastcharge=-1;
	while(1)
	{
		if(center_control->A_charge!=lastcharge)
		{
			dlg_backup->A_charge=center_control->A_charge;
			CString cstr=_T("");
			cstr.Format(_T("%g"),dlg_backup->A_charge);
			dlg_backup->SetDlgItemText(IDC_EACHARGE_CENTER,cstr);
			lastcharge=center_control->A_charge;
		}
	}
}

UINT GetCenterBCharge(LPVOID pParam)//获取中央空调房间B费用
{
    float lastcharge=-1;
	while(1)
	{
		if(center_control->B_charge!=lastcharge)
		{
			dlg_backup->B_charge=center_control->B_charge;
			CString cstr=_T("");
			cstr.Format(_T("%g"),dlg_backup->B_charge);
			dlg_backup->SetDlgItemText(IDC_EBCHARGE_CENTER,cstr);
			lastcharge=center_control->B_charge;
		}
	}
}

UINT GetRoomARealTemperature(LPVOID pParam)//获取房间A实际温度
{
	int lasttemperature=-1;
	while(1)
	{
		if(dlg_backup->realtemperature_A!=lasttemperature)
		{
			lasttemperature=dlg_backup->realtemperature_A;
			CString cstr=_T("");
			cstr.Format(_T("%d"),dlg_backup->realtemperature_A);
			dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_A,cstr);
		}
	}
}

UINT GetRoomBRealTemperature(LPVOID pParam)//获取房间B实际温度
{
	int lasttemperature=-1;
	while(1)
	{
		if(dlg_backup->realtemperature_B!=lasttemperature)
		{
			lasttemperature=dlg_backup->realtemperature_B;
			CString cstr=_T("");
			cstr.Format(_T("%d"),dlg_backup->realtemperature_B);
			dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_B,cstr);
		}
	}
}

UINT ChangeRoomARealTemperature(LPVOID pParam)//改变房间A实际温度
{
	int lastspeed=-1;
	int num=-1;
	SYSTEMTIME SystemTime1;
	SYSTEMTIME SystemTime2;
	int lastseconds=-1;
	GetLocalTime(&SystemTime1);//获取系统时间
	while(1)
	{
		if(room_A->state==2)//工作
		{
			num=room_A->num;//防止多线程时出现冲突
			if(room_A->speed[num]==lastspeed)
			{
				GetLocalTime(&SystemTime2);//获取系统时间
                CTimeSpan span=(CTime)SystemTime2-(CTime)SystemTime1;
				long seconds=span.GetTotalSeconds();
				if(seconds!=lastseconds && span>0 && seconds%(lastspeed+3)==0)
				{
					lastseconds=seconds;
					if(center_control->mode==0)//供暖
					{
						dlg_backup->realtemperature_A++;
						CString cstr=_T("");
						cstr.Format(_T("%d"),dlg_backup->realtemperature_A);
						dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_A,cstr);
					}
					else if(center_control->mode==1)//制冷
					{
						dlg_backup->realtemperature_A--;
						CString cstr=_T("");
						cstr.Format(_T("%d"),dlg_backup->realtemperature_A);
						dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_A,cstr);
					}
				}
			}
			else
			{
				lastspeed=room_A->speed[num];
				GetLocalTime(&SystemTime1);//获取系统时间
			}
		}
	}
}

UINT ChangeRoomBRealTemperature(LPVOID pParam)//改变房间B实际温度
{
	int lastspeed=-1;
	int num=-1;
	SYSTEMTIME SystemTime1;
	SYSTEMTIME SystemTime2;
	int lastseconds=-1;
	GetLocalTime(&SystemTime1);//获取系统时间
	while(1)
	{
		if(room_B->state==2)//工作
		{
			num=room_B->num;//防止多线程时出现冲突
			if(room_B->speed[num]==lastspeed)
			{
				GetLocalTime(&SystemTime2);//获取系统时间
                CTimeSpan span=(CTime)SystemTime2-(CTime)SystemTime1;
				long seconds=span.GetSeconds();
				if(seconds!=lastseconds && span>0 && seconds%(lastspeed+3)==0)
				{
					lastseconds=seconds;
					if(center_control->mode==0)//供暖
					{
						dlg_backup->realtemperature_B++;
						CString cstr=_T("");
						cstr.Format(_T("%d"),dlg_backup->realtemperature_B);
						dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_B,cstr);
					}
					else if(center_control->mode==1)//制冷
					{
						dlg_backup->realtemperature_B--;
						CString cstr=_T("");
						cstr.Format(_T("%d"),dlg_backup->realtemperature_B);
						dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_B,cstr);
					}
				}
			}
			else
			{
				lastspeed=room_B->speed[num];
				GetLocalTime(&SystemTime1);//获取系统时间
			}
		}
	}
}

CString CTimeConvertToCString(CTime ct)//将时间转化为CString型变量
{
	CString cstr=_T("");
	switch(ct.GetDayOfWeek())
	{
		case 0:{cstr.Format(_T("%04d年%02d月%02d日星期日 %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 1:{cstr.Format(_T("%04d年%02d月%02d日星期一 %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 2:{cstr.Format(_T("%04d年%02d月%02d日星期二 %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 3:{cstr.Format(_T("%04d年%02d月%02d日星期三 %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 4:{cstr.Format(_T("%04d年%02d月%02d日星期四 %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 5:{cstr.Format(_T("%04d年%02d月%02d日星期五 %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 6:{cstr.Format(_T("%04d年%02d月%02d日星期六 %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		default:{break;}
	}
	return cstr;
}

UINT ChangeRoomACharge(LPVOID pParam)//改变房间A费用
{
	int num=-1;
	int lastcharge=-1;
	while(1)
	{
		float charge=0;
	    num=room_A->num;//防止多线程时出现冲突
		for(int i=0;i<num;i++)
		{
			float rate=-1;
		    if(room_A->speed[i]==0)
		    {
			    rate=1.3;
		    }
		    else if(room_A->speed[i]==1)
		    {
			    rate=1;
			}
		    else if(room_A->speed[i]==2)
		    {
			    rate=0.8;
		    }
		    CTimeSpan span=(CTime)room_A->endtime[i]-(CTime)room_A->starttime[i];
		    long seconds=span.GetTotalSeconds();
		    if(seconds>0)
			{
				charge+=seconds*rate*5;
			}
		}
		if(charge!=lastcharge)
		{
			lastcharge=charge;
			center_control->A_charge=charge;
		}
	}
}

UINT ChangeRoomBCharge(LPVOID pParam)//改变房间B费用
{
	int num=-1;
	int lastcharge=-1;
	while(1)
	{
		float charge=0;
	    num=room_B->num;//防止多线程时出现冲突
		for(int i=0;i<num;i++)
		{
			float rate=-1;
		    if(room_B->speed[i]==0)
		    {
			    rate=1.3;
		    }
		    else if(room_B->speed[i]==1)
		    {
			    rate=1;
			}
		    else if(room_B->speed[i]==2)
		    {
			    rate=0.8;
		    }
		    CTimeSpan span=(CTime)room_A->endtime[i]-(CTime)room_A->starttime[i];
		    long seconds=span.GetTotalSeconds();
			if(seconds>0)
			{
				charge+=seconds*rate*5;
			}
		}
		if(charge!=lastcharge)
		{
			lastcharge=charge;
			center_control->B_charge=charge;
		}
	}
}