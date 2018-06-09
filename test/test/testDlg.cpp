
// testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


center::center()//���캯��
{
	state=0;
	mode=0;
	A_charge=0;
	B_charge=0;
}

room::room()//���캯��
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

// CtestDlg �Ի���




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


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//��ȡϵͳʱ��
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
	    case 0:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 1:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d������һ %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 2:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�����ڶ� %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 3:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 4:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 5:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
		case 6:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,second);break;}
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
	HANDLE thread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetTime,NULL,0,NULL);//�������߳�(��ȡ��ǰʱ��)
	HANDLE thread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetMode,NULL,0,NULL);//�������߳�(��ȡ����յ���ǰ����ģʽ)
	HANDLE thread3 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetCenterState,NULL,0,NULL);//�������߳�(��ȡ����յ���ǰ����״̬)
	HANDLE thread4 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomAState,NULL,0,NULL);//�������߳�(��ȡ����A��ǰ����״̬)
	HANDLE thread5 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomBState,NULL,0,NULL);//�������߳�(��ȡ����B��ǰ����״̬)
	HANDLE thread6 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeCenterState,NULL,0,NULL);//�������߳�(�ı�����յ���ǰ����״̬)
	HANDLE thread7 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomAState,NULL,0,NULL);//�������߳�(�ı䷿��A��ǰ����״̬)
	HANDLE thread8 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomBState,NULL,0,NULL);//�������߳�(�ı䷿��B��ǰ����״̬)
	HANDLE thread9 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetCenterACharge,NULL,0,NULL);//�������߳�(��ȡ����յ�����A����)
	HANDLE thread10 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetCenterBCharge,NULL,0,NULL);//�������߳�(��ȡ����յ�����B����)
	HANDLE thread11 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomARealTemperature,NULL,0,NULL);//�������߳�(��ȡ����Aʵ���¶�)
	HANDLE thread12 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetRoomBRealTemperature,NULL,0,NULL);//�������߳�(��ȡ����Bʵ���¶�)
	HANDLE thread13 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomARealTemperature,NULL,0,NULL);//�������߳�(�ı䷿��Aʵ���¶�)
	HANDLE thread14 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomBRealTemperature,NULL,0,NULL);//�������߳�(�ı䷿��Bʵ���¶�)
	HANDLE thread15 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomACharge,NULL,0,NULL);//�������߳�(�ı䷿��A����)
	HANDLE thread16 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ChangeRoomBCharge,NULL,0,NULL);//�������߳�(�ı䷿��B����)
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDlg::OnBnClickedBexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}

UINT GetTime(LPVOID pParam)//��ȡ��ǰʱ��
{
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//��ȡϵͳʱ��
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
	    GetLocalTime(&SystemTime);//��ȡϵͳʱ��
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
	            case 0:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 1:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d������һ %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 2:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�����ڶ� %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 3:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 4:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 5:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        case 6:{cstr_time.Format(_T("��ǰʱ�䣺%04d��%02d��%02d�������� %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
		        default:{break;}
	        }
	        dlg_backup->SetDlgItemText(IDC_STIME,cstr_time);
        }
	}
}

void CtestDlg::OnBnClickedRswitch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedRmode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(mode_choice==0)//��ů
	{
		center_control->mode=0;
	}
	else if(mode_choice==1)//����
	{
		center_control->mode=1;
	}
}


void CtestDlg::OnBnClickedRswitchA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedRspeedA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(room_A->state==2)//����
	{
		SYSTEMTIME SystemTime;
	    GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		int num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
		if(num>=0)
		{
			room_A->endtime[num]=SystemTime;
			room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		}
		room_A->num++;
		num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
		room_A->speed[num]=speed_A_choice;
		room_A->starttime[num]=SystemTime;
		room_A->settemperature[num]=dlg_backup->settemperature_A;
		room_A->startrealtemperature[num]=dlg_backup->realtemperature_A;
	}
}


void CtestDlg::OnBnClickedRswitchB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedRspeedB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(room_B->state==2)//����
	{
		SYSTEMTIME SystemTime;
	    GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		int num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
		if(num>=0)
		{
			room_B->endtime[num]=SystemTime;
			room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		}
		room_B->num++;
		num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
		room_B->speed[num]=speed_B_choice;
		room_B->starttime[num]=SystemTime;
		room_B->settemperature[num]=dlg_backup->settemperature_B;
		room_B->startrealtemperature[num]=dlg_backup->realtemperature_B;
	}
}


void CtestDlg::OnBnClickedBoutalogCenter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	errno_t err;
	FILE *fp_write;
	err=fopen_s(&fp_write,"log_A.txt","w");
	if(err!=0)
	{
		AfxMessageBox(_T("��־��������"),MB_OK,NULL);
		return;
	}
	fprintf(fp_write,"����ţ�����A\n\n");
	fprintf(fp_write,"�ܿ��ػ�������%d\n\n",room_A->statenum);
	int num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
	for(int i=0;i<num;i++)
	{
		fprintf(fp_write,"�¿�����ʼʱ��:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_A->starttime[i])));
		fprintf(fp_write,"�¿��������ʱ��:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_A->endtime[i])));
		fprintf(fp_write,"�¿�����ʼʵ���¶�:%d\n",room_A->startrealtemperature[i]);
		fprintf(fp_write,"�¿��������ʵ���¶�:%d\n",room_A->endrealtemperature[i]);
		fprintf(fp_write,"�¿������趨�¶�:%d\n",room_A->settemperature[i]);
		float rate=-1;
		if(room_A->speed[i]==0)
		{
			rate=1.3;
			fprintf(fp_write,"�¿����������С:��\n");
		}
		else if(room_A->speed[i]==1)
		{
			rate=1;
			fprintf(fp_write,"�¿����������С:��\n");
		}
		else if(room_A->speed[i]==2)
		{
			rate=0.8;
			fprintf(fp_write,"�¿����������С:��\n");
		}
		float charge=0;
		CTimeSpan span=(CTime)room_A->endtime[i]-(CTime)room_A->starttime[i];
		long seconds=span.GetTotalSeconds();
		charge=seconds*rate*5;
		fprintf(fp_write,"�¿�����˴η���:%g\n\n",charge);
	}
	fclose(fp_write);
	AfxMessageBox(_T("����A��־�����ɹ����ļ�λ�ڴ˳���ǰĿ¼�µ�\"log_A.txt\"��"),MB_OK,NULL);
}


void CtestDlg::OnBnClickedBoutblogCenter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	errno_t err;
	FILE *fp_write;
	err=fopen_s(&fp_write,"log_B.txt","w");
	if(err!=0)
	{
		AfxMessageBox(_T("��־��������"),MB_OK,NULL);
		return;
	}
	fprintf(fp_write,"����ţ�����B\n\n");
	fprintf(fp_write,"�ܿ��ػ�������%d\n\n",room_B->statenum);
	int num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
	for(int i=0;i<num;i++)
	{
		fprintf(fp_write,"�¿�����ʼʱ��:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_B->starttime[i])));
		fprintf(fp_write,"�¿��������ʱ��:%s\n",MyCStringToConstChar(CTimeConvertToCString(room_B->endtime[i])));
		fprintf(fp_write,"�¿�����ʼʵ���¶�:%d\n",room_B->startrealtemperature[i]);
		fprintf(fp_write,"�¿��������ʵ���¶�:%d\n",room_B->endrealtemperature[i]);
		fprintf(fp_write,"�¿������趨�¶�:%d\n",room_B->settemperature[i]);
		float rate=-1;
		if(room_B->speed[i]==0)
		{
			rate=1.3;
			fprintf(fp_write,"�¿����������С:��\n");
		}
		else if(room_B->speed[i]==1)
		{
			rate=1;
			fprintf(fp_write,"�¿����������С:��\n");
		}
		else if(room_B->speed[i]==2)
		{
			rate=0.8;
			fprintf(fp_write,"�¿����������С:��\n");
		}
		float charge=0;
		CTimeSpan span=(CTime)room_B->endtime[i]-(CTime)room_B->starttime[i];
		long seconds=span.GetTotalSeconds();
		charge=seconds*rate*5;
		fprintf(fp_write,"�¿�����˴η���:%g\n\n",charge);
	}
	fclose(fp_write);
	AfxMessageBox(_T("����B��־�����ɹ����ļ�λ�ڴ˳���ǰĿ¼�µ�\"log_B.txt\"��"),MB_OK,NULL);
}


void CtestDlg::OnBnClickedBrealtemperatureA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CtestDlg::OnBnClickedBsettemperatureA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(center_control->mode==0)//��ů
	{
		if(settemperature_A<25 || settemperature_A>30)
		{
			AfxMessageBox(_T("��ůģʽ���趨�¶ȱ���Ϊ25��30֮����������趨����"),MB_OK,NULL);
			return;
		}
	}
	else if(center_control->mode==1)//����
	{
		if(settemperature_A<18 || settemperature_A>25)
		{
			AfxMessageBox(_T("��ůģʽ���趨�¶ȱ���Ϊ18��25֮����������趨����"),MB_OK,NULL);
			return;
		}
	}
}


void CtestDlg::OnBnClickedBrealtemperatureB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(center_control->mode==0)//��ů
	{
		if(settemperature_B<25 || settemperature_B>30)
		{
			AfxMessageBox(_T("��ůģʽ���趨�¶ȱ���Ϊ25��30֮����������趨����"),MB_OK,NULL);
			return;
		}
	}
	else if(center_control->mode==1)//����
	{
		if(settemperature_B<18 || settemperature_B>25)
		{
			AfxMessageBox(_T("��ůģʽ���趨�¶ȱ���Ϊ18��25֮����������趨����"),MB_OK,NULL);
			return;
		}
	}
}


void CtestDlg::OnBnClickedBsettemperatureB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

UINT GetMode(LPVOID pParam)//��ȡ����յ���ǰ����ģʽ
{
	int lastmode=-1;
	while(1)
	{
		if(center_control->mode!=lastmode)
		{
			if(center_control->mode==0)
			{
				dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_A,_T("����յ���ǰ����ģʽ����ů"));
			    dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_B,_T("����յ���ǰ����ģʽ����ů"));
			}
			else if(center_control->mode==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_A,_T("����յ���ǰ����ģʽ������"));
			    dlg_backup->SetDlgItemText(IDC_SCENTERSTATE_B,_T("����յ���ǰ����ģʽ������"));
		    }
			lastmode=center_control->mode;
		}
	}
}

UINT GetCenterState(LPVOID pParam)//��ȡ����յ���ǰ����״̬
{
	int laststate=-1;
	while(1)
	{
		if(center_control->state!=laststate)
		{
			if(center_control->state==0)
			{
				dlg_backup->SetDlgItemText(IDC_SSTATE_CENTER,_T("��ǰ״̬���ػ�"));
			}
			else if(center_control->state==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_CENTER,_T("��ǰ״̬������"));
		    }
			else if(center_control->state==2)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_CENTER,_T("��ǰ״̬������"));
		    }
			laststate=center_control->state;
		}
	}
}

UINT GetRoomAState(LPVOID pParam)//��ȡ����A��ǰ����״̬
{
	int laststate=-1;
	while(1)
	{
		if(room_A->state!=laststate)
		{
			if(room_A->state==0)
			{
				dlg_backup->SetDlgItemText(IDC_SSTATE_A,_T("��ǰ״̬���ػ�"));
			}
			else if(room_A->state==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_A,_T("��ǰ״̬������"));
		    }
			else if(room_A->state==2)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_A,_T("��ǰ״̬������"));
		    }
			laststate=room_A->state;
		}
	}
}

UINT GetRoomBState(LPVOID pParam)//��ȡ����B��ǰ����״̬
{
	int laststate=-1;
	while(1)
	{
		if(room_B->state!=laststate)
		{
			if(room_B->state==0)
			{
				dlg_backup->SetDlgItemText(IDC_SSTATE_B,_T("��ǰ״̬���ػ�"));
			}
			else if(room_B->state==1)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_B,_T("��ǰ״̬������"));
		    }
			else if(room_B->state==2)
		    {
			    dlg_backup->SetDlgItemText(IDC_SSTATE_B,_T("��ǰ״̬������"));
		    }
			laststate=room_B->state;
		}
	}
}

UINT ChangeCenterState(LPVOID pParam)//�ı�����յ���ǰ����״̬
{
	while(1)
	{
	    if(dlg_backup->switch_choice==0)//��
	    {
		    if(room_A->state!=2 && room_B->state!=2)
		    {
			    center_control->state=1;//����
		    }
		    else
		    {
		    	center_control->state=2;//����
		    }
	    }
	    else if(dlg_backup->switch_choice==1)//��
	    {
		    center_control->state=0;//��
	    }
	}
}

UINT ChangeRoomAState(LPVOID pParam)//�ı䷿��A��ǰ����״̬
{
	while(1)
	{
	    if(dlg_backup->switch_A_choice==0)//��
	    {
		    if(center_control->state==0)//����յ���
		    {
				if(room_A->state==2)//����
				{
					SYSTEMTIME SystemTime;
	                GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		            int num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
		            room_A->endtime[num]=SystemTime;
				    room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		            room_A->num++;
				    room_A->state=1;//����
				}
				else if(room_A->state==0)//�ػ�
				{
					room_A->state=1;//����
				}
		    }
		    else if(room_A->state!=2 && abs(dlg_backup->realtemperature_A-dlg_backup->settemperature_A)>1)//����A֮ǰ������ػ����²����1
		    {
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		        int num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
				room_A->speed[num]=dlg_backup->speed_A_choice;
		        room_A->starttime[num]=SystemTime;
				room_A->settemperature[num]=dlg_backup->settemperature_A;
		        room_A->startrealtemperature[num]=dlg_backup->realtemperature_A;
				room_A->state=2;//����
		    }
			else if(room_A->state!=2 && abs(dlg_backup->realtemperature_A-dlg_backup->settemperature_A)<=1)//����A֮ǰ������ػ����²�С�ڵ���1
		    {
			    room_A->state=1;//����
		    }
			else if(room_A->state==2 && abs(dlg_backup->realtemperature_A-dlg_backup->settemperature_A)<0.01)//����A֮ǰ�������²�С��0.01
			{
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		        int num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
		        room_A->endtime[num]=SystemTime;
				room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		        room_A->num++;
				room_A->state=1;//����
			}
	    }
	    else if(dlg_backup->switch_A_choice==1)//��
	    {
		    if(room_A->state!=0)
		    {
				room_A->statenum++;
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		        int num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
		        room_A->endtime[num]=SystemTime;
				room_A->endrealtemperature[num]=dlg_backup->realtemperature_A;
		        room_A->num++;
				room_A->state=0;//��
		    }
	    }
	}
}

UINT ChangeRoomBState(LPVOID pParam)//�ı䷿��B��ǰ����״̬
{
	while(1)
	{
	    if(dlg_backup->switch_B_choice==0)//��
	    {
		    if(center_control->state==0)//����յ���
		    {
				if(room_B->state==2)//����
				{
					SYSTEMTIME SystemTime;
	                GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		            int num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
		            room_B->endtime[num]=SystemTime;
				    room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		            room_B->num++;
				    room_B->state=1;//����
				}
				else if(room_B->state==0)//�ػ�
				{
					room_B->state=1;//����
				}
		    }
		    else if(room_B->state!=2 && abs(dlg_backup->realtemperature_B-dlg_backup->settemperature_B)>1)//����B֮ǰ������ػ����²����1
		    {
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		        int num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
				room_B->speed[num]=dlg_backup->speed_B_choice;
		        room_B->starttime[num]=SystemTime;
				room_B->settemperature[num]=dlg_backup->settemperature_B;
		        room_B->startrealtemperature[num]=dlg_backup->realtemperature_B;
				room_B->state=2;//����
		    }
			else if(room_B->state!=2 && abs(dlg_backup->realtemperature_B-dlg_backup->settemperature_B)<=1)//����B֮ǰ������ػ����²�С�ڵ���1
		    {
			    room_A->state=1;//����
		    }
			else if(room_B->state==2 && abs(dlg_backup->realtemperature_B-dlg_backup->settemperature_B)<0.01)//����B֮ǰ�������²�С��0.01
			{
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		        int num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
		        room_B->endtime[num]=SystemTime;
				room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		        room_B->num++;
				room_B->state=1;//����
			}
	    }
	    else if(dlg_backup->switch_B_choice==1)//��
	    {
		    if(room_B->state!=0)
		    {
				room_B->statenum++;
				SYSTEMTIME SystemTime;
	            GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		        int num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
		        room_B->endtime[num]=SystemTime;
				room_B->endrealtemperature[num]=dlg_backup->realtemperature_B;
		        room_B->num++;
				room_B->state=0;//��
		    }
	    }
	}
}

UINT GetCenterACharge(LPVOID pParam)//��ȡ����յ�����A����
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

UINT GetCenterBCharge(LPVOID pParam)//��ȡ����յ�����B����
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

UINT GetRoomARealTemperature(LPVOID pParam)//��ȡ����Aʵ���¶�
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

UINT GetRoomBRealTemperature(LPVOID pParam)//��ȡ����Bʵ���¶�
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

UINT ChangeRoomARealTemperature(LPVOID pParam)//�ı䷿��Aʵ���¶�
{
	int lastspeed=-1;
	int num=-1;
	SYSTEMTIME SystemTime1;
	SYSTEMTIME SystemTime2;
	int lastseconds=-1;
	GetLocalTime(&SystemTime1);//��ȡϵͳʱ��
	while(1)
	{
		if(room_A->state==2)//����
		{
			num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
			if(room_A->speed[num]==lastspeed)
			{
				GetLocalTime(&SystemTime2);//��ȡϵͳʱ��
                CTimeSpan span=(CTime)SystemTime2-(CTime)SystemTime1;
				long seconds=span.GetTotalSeconds();
				if(seconds!=lastseconds && span>0 && seconds%(lastspeed+3)==0)
				{
					lastseconds=seconds;
					if(center_control->mode==0)//��ů
					{
						dlg_backup->realtemperature_A++;
						CString cstr=_T("");
						cstr.Format(_T("%d"),dlg_backup->realtemperature_A);
						dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_A,cstr);
					}
					else if(center_control->mode==1)//����
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
				GetLocalTime(&SystemTime1);//��ȡϵͳʱ��
			}
		}
	}
}

UINT ChangeRoomBRealTemperature(LPVOID pParam)//�ı䷿��Bʵ���¶�
{
	int lastspeed=-1;
	int num=-1;
	SYSTEMTIME SystemTime1;
	SYSTEMTIME SystemTime2;
	int lastseconds=-1;
	GetLocalTime(&SystemTime1);//��ȡϵͳʱ��
	while(1)
	{
		if(room_B->state==2)//����
		{
			num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
			if(room_B->speed[num]==lastspeed)
			{
				GetLocalTime(&SystemTime2);//��ȡϵͳʱ��
                CTimeSpan span=(CTime)SystemTime2-(CTime)SystemTime1;
				long seconds=span.GetSeconds();
				if(seconds!=lastseconds && span>0 && seconds%(lastspeed+3)==0)
				{
					lastseconds=seconds;
					if(center_control->mode==0)//��ů
					{
						dlg_backup->realtemperature_B++;
						CString cstr=_T("");
						cstr.Format(_T("%d"),dlg_backup->realtemperature_B);
						dlg_backup->SetDlgItemText(IDC_EREALTEMPERATURE_B,cstr);
					}
					else if(center_control->mode==1)//����
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
				GetLocalTime(&SystemTime1);//��ȡϵͳʱ��
			}
		}
	}
}

CString CTimeConvertToCString(CTime ct)//��ʱ��ת��ΪCString�ͱ���
{
	CString cstr=_T("");
	switch(ct.GetDayOfWeek())
	{
		case 0:{cstr.Format(_T("%04d��%02d��%02d�������� %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 1:{cstr.Format(_T("%04d��%02d��%02d������һ %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 2:{cstr.Format(_T("%04d��%02d��%02d�����ڶ� %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 3:{cstr.Format(_T("%04d��%02d��%02d�������� %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 4:{cstr.Format(_T("%04d��%02d��%02d�������� %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 5:{cstr.Format(_T("%04d��%02d��%02d�������� %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		case 6:{cstr.Format(_T("%04d��%02d��%02d�������� %02d:%02d:%02d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());break;}
		default:{break;}
	}
	return cstr;
}

UINT ChangeRoomACharge(LPVOID pParam)//�ı䷿��A����
{
	int num=-1;
	int lastcharge=-1;
	while(1)
	{
		float charge=0;
	    num=room_A->num;//��ֹ���߳�ʱ���ֳ�ͻ
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

UINT ChangeRoomBCharge(LPVOID pParam)//�ı䷿��B����
{
	int num=-1;
	int lastcharge=-1;
	while(1)
	{
		float charge=0;
	    num=room_B->num;//��ֹ���߳�ʱ���ֳ�ͻ
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