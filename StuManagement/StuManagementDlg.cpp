
// StuManagementDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuManagement.h"
#include "StuManagementDlg.h"
#include "afxdialogex.h"
#include "management.h"
#include <shlwapi.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStuManagementDlg �Ի���



CStuManagementDlg::CStuManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, Edit_id(0)
	, Edit_math(0)
	, Edit_cpp(0)
	, Edit_name(_T(""))
	, Radiomale(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStuManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, LISTC);
	DDX_Text(pDX, IDC_ID, Edit_id);
	DDX_Text(pDX, IDC_MATH, Edit_math);
	DDV_MinMaxDouble(pDX, Edit_math, 0, 100);			//���ø����༭��ֻ������0-100
	DDX_Text(pDX, IDC_CPP, Edit_cpp);
	DDV_MinMaxDouble(pDX, Edit_cpp, 0, 100);			//���ó�����Ʊ༭��ֻ������0-100
	DDX_Text(pDX, IDC_NAME, Edit_name);
}

BEGIN_MESSAGE_MAP(CStuManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CStuManagementDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTONread, &CStuManagementDlg::OnBnClickedButtonread)
	ON_BN_CLICKED(IDC_BUTTONmod, &CStuManagementDlg::OnBnClickedButtonmod)
	ON_BN_CLICKED(IDC_BUTTONadd, &CStuManagementDlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTONdel, &CStuManagementDlg::OnBnClickedButtondel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CStuManagementDlg::OnLvnColumnclickList1)
END_MESSAGE_MAP()


// CStuManagementDlg ��Ϣ�������

BOOL CStuManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	DWORD dwStyle = LISTC.GetExtendedStyle();                    //����б���������

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	LISTC.SetExtendedStyle(dwStyle);

	LISTC.InsertColumn(0, "ѧ��", LVCFMT_LEFT, 105);				//����б��⣬����룬���
	LISTC.InsertColumn(1, "����", LVCFMT_LEFT, 80); 
	LISTC.InsertColumn(2, "�Ա�", LVCFMT_LEFT, 55);
	LISTC.InsertColumn(3, "�ߵ���ѧ", LVCFMT_LEFT, 75);
	LISTC.InsertColumn(4, "�������", LVCFMT_LEFT, 75);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CStuManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStuManagementDlg::OnPaint()
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
HCURSOR CStuManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CStuManagementDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)		//�б���
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int hang;
	POSITION pos = LISTC.GetFirstSelectedItemPosition();//��ȡ���������Ŀ��λ��
	hang = LISTC.GetNextSelectedItem(pos);//��ȡ�������
	Edit_id = _ttoi(LISTC.GetItemText(hang, 0));//��ȡ��hang�е�0������
	Edit_name = LISTC.GetItemText(hang, 1);
	Edit_math = _ttoi(LISTC.GetItemText(hang, 3));
	Edit_cpp = _ttoi(LISTC.GetItemText(hang, 4));
	if (LISTC.GetItemText(hang, 2) == "��")		//����Ա�Ϊ���С�����ѡ�С��С���ѡ��ť����ѡ�С�Ů����ѡ��ť
	{
		((CButton *)GetDlgItem(IDC_RADIOmale))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIOfemale))->SetCheck(0);
	}
	else											//�����෴
	{
		((CButton *)GetDlgItem(IDC_RADIOmale))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIOfemale))->SetCheck(1);
	}
	UpdateData(false);					//ˢ������
}


void CStuManagementDlg::OnBnClickedButtonread()			//��ȡ��ť
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	Management templist;
	LISTC.DeleteAllItems();				//�������������ظ�
	templist.show();				//����show����
	list<Student>::iterator c;			
	c = templist._list.begin();			//����ȫ������
	CString temp = "";
	for (int i = 0; c != templist._list.end(); ++c, i++)		//��������ʾ���б�ؼ���
	{
		temp.Format("%d", c->id);			//���ַ�������ת�����ͣ���Ϊlist control�ﶼ��CString����
		LISTC.InsertItem(i, temp); 
		LISTC.SetItemText(i, 1, c->name);
		LISTC.SetItemText(i, 2, c->sex);
		temp.Format("%d", c->math);
		LISTC.SetItemText(i, 3, temp);
		temp.Format("%d", c->cpp);
		LISTC.SetItemText(i, 4, temp);
	}
	UpdateData(false);
}


void CStuManagementDlg::OnBnClickedButtonmod()				//�޸İ�ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);				//����ˢ������

	Management m;
	Student temp;

	temp.id = Edit_id;				//��Ҫ�޸ĵ�ֵ��ֵ��temp
	strcpy_s(temp.name, (LPCSTR)Edit_name);
	temp.math = Edit_math;
	temp.cpp = Edit_cpp;

	int gg = 0;
	if (temp.math < 0 || temp.math>100 || temp.cpp < 0 || temp.cpp>100)
	{
		gg = 1;
	}
	if (gg == 0)
	{
		if (((CButton *)GetDlgItem(IDC_RADIOmale))->GetCheck())		//���ݵ�ѡ��ť״̬�����ݶ�Ӧ���Ա��ַ���
		{
			strcpy_s(temp.sex, "��");
		}
		else
			strcpy_s(temp.sex, "Ů");

		m.mod(temp);				//����mod����
		OnBnClickedButtonread();		//�������밴ťˢ��
	}
}


void CStuManagementDlg::OnBnClickedButtonadd()				//��Ӱ�ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	Management m;
	UpdateData(true);			//����ˢ������
	Student temp;

	temp.id = Edit_id;				//��Ҫ��ӵ�ֵ��ֵ��temp
	strcpy_s(temp.name, (LPCSTR)Edit_name);
	temp.math = Edit_math;
	temp.cpp = Edit_cpp;
	if (((CButton *)GetDlgItem(IDC_RADIOmale))->GetCheck())		//���ݵ�ѡ��ť״̬�����ݶ�Ӧ���Ա��ַ���
	{
		strcpy_s(temp.sex, "��");
	}
	else
		strcpy_s(temp.sex, "Ů");
	//�ж�ѧ���Ƿ��ظ�
	fstream fat("D:\\student.dat", ios::in | ios::binary);			
	fat.seekg(0, ios::beg);
	Student temp1;
	fat.read((char *)&temp1, sizeof(Student));
	int gg = 0;
	if (temp.math < 0 || temp.math>100 || temp.cpp < 0 || temp.cpp>100)
	{
		gg = 1;
	}
	while (!fat.eof())			//�����������
	{
		if (temp1.id == temp.id)		//���Դ����򵯳�����������ѭ��
		{
			gg = 1;						//��gg��Ϊ1
			MessageBox("ѧ���Ѵ��ڣ�");
			break;
		}
		else
			fat.read((char *)&temp1, sizeof(Student));		//���������ȡ
	}
	fat.close();
	if (gg == 0)
	{							//ggΪ0ʱ�ŵ���add����
		m.add(temp);
	}
	else
	{
		Edit_id = temp.id;
		Edit_math = temp.math;
		Edit_cpp = temp.cpp;
	}
	
	OnBnClickedButtonread();
}


void CStuManagementDlg::OnBnClickedButtondel()				//ɾ����ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UINT i;
	i = MessageBox(TEXT("ȷ��Ҫɾ����"), TEXT("ɾ��"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDNO)
	{
		return;
	}

	Management m;
	UpdateData(true);
	Student temp;

	temp.id = Edit_id;

	m.del(temp);			//�������ѧ�Ÿ�ֵ��del
	
	OnBnClickedButtonread();
}


int SortFlag = 0;

void CStuManagementDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int pos;
	Management temp;

	pos = pNMLV->iSubItem;      //������򣨻�ȡ�����������

	//int state = ((CButton *)GetDlgItem(IDC_CHECKsort))->GetCheck();	//��ȡcheckbox��״̬

	if (SortFlag == 1)
	{
		temp.sort(pos);
		SortFlag = 0;
	}
	else
	{
		temp.sort(pos+5);
		SortFlag = 1;
	}

	OnBnClickedButtonread();
}

