
// testDlg.h : ͷ�ļ�
//

#pragma once


// CtestDlg �Ի���
class CtestDlg : public CDialogEx
{
// ����
public:
	CtestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	int state;//��ǰ״̬��0�أ�1����(��)��2����(��)��
	int mode;//ģʽ��0��ů��1���䡣
	float A_charge;//����A����
	float B_charge;//����B����
	center();//���캯��
};

class room
{
public:
	int state;//��ǰ״̬��0�أ�1����(��)��2����(��)��
	int statenum;//���ػ�����
	int speed[100];//���٣�0�ߣ�1�У�2�͡�
	CTime starttime[100];//����ʼʱ��
	CTime endtime[100];//�������ʱ��
	int settemperature[100];//���������¶�
	int startrealtemperature[100];//����ʼʱʵ���¶�
	int endrealtemperature[100];//�������ʱʵ���¶�
	int num;//�������
	room();//���캯��
};


UINT GetTime(LPVOID pParam);//��ȡ��ǰʱ��
UINT GetMode(LPVOID pParam);//��ȡ����յ���ǰ����ģʽ
UINT GetCenterState(LPVOID pParam);//��ȡ����յ���ǰ����״̬
UINT GetRoomAState(LPVOID pParam);//��ȡ����A��ǰ����״̬
UINT GetRoomBState(LPVOID pParam);//��ȡ����B��ǰ����״̬
UINT ChangeCenterState(LPVOID pParam);//�ı�����յ���ǰ����״̬
UINT ChangeRoomAState(LPVOID pParam);//�ı䷿��A��ǰ����״̬
UINT ChangeRoomBState(LPVOID pParam);//�ı䷿��B��ǰ����״̬
UINT GetCenterACharge(LPVOID pParam);//��ȡ����յ�����A����
UINT GetCenterBCharge(LPVOID pParam);//��ȡ����յ�����B����
UINT GetRoomARealTemperature(LPVOID pParam);//��ȡ����Aʵ���¶�
UINT GetRoomBRealTemperature(LPVOID pParam);//��ȡ����Bʵ���¶�
UINT ChangeRoomARealTemperature(LPVOID pParam);//�ı䷿��Aʵ���¶�
UINT ChangeRoomBRealTemperature(LPVOID pParam);//�ı䷿��Bʵ���¶�
CString CTimeConvertToCString(CTime ct);//��ʱ��ת��ΪCString�ͱ���
UINT ChangeRoomACharge(LPVOID pParam);//�ı䷿��A����
UINT ChangeRoomBCharge(LPVOID pParam);//�ı䷿��B����