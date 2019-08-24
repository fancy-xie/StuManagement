
// StuManagementDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CStuManagementDlg 对话框



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
	DDV_MinMaxDouble(pDX, Edit_math, 0, 100);			//设置高数编辑框只能输入0-100
	DDX_Text(pDX, IDC_CPP, Edit_cpp);
	DDV_MinMaxDouble(pDX, Edit_cpp, 0, 100);			//设置程序设计编辑框只能输入0-100
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


// CStuManagementDlg 消息处理程序

BOOL CStuManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	DWORD dwStyle = LISTC.GetExtendedStyle();                    //添加列表框的网格线

	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	LISTC.SetExtendedStyle(dwStyle);

	LISTC.InsertColumn(0, "学号", LVCFMT_LEFT, 105);				//添加列标题，左对齐，宽度
	LISTC.InsertColumn(1, "姓名", LVCFMT_LEFT, 80); 
	LISTC.InsertColumn(2, "性别", LVCFMT_LEFT, 55);
	LISTC.InsertColumn(3, "高等数学", LVCFMT_LEFT, 75);
	LISTC.InsertColumn(4, "程序设计", LVCFMT_LEFT, 75);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStuManagementDlg::OnPaint()
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
HCURSOR CStuManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CStuManagementDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)		//列表函数
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int hang;
	POSITION pos = LISTC.GetFirstSelectedItemPosition();//获取被点击的项目的位置
	hang = LISTC.GetNextSelectedItem(pos);//获取点击行数
	Edit_id = _ttoi(LISTC.GetItemText(hang, 0));//获取第hang列第0列数据
	Edit_name = LISTC.GetItemText(hang, 1);
	Edit_math = _ttoi(LISTC.GetItemText(hang, 3));
	Edit_cpp = _ttoi(LISTC.GetItemText(hang, 4));
	if (LISTC.GetItemText(hang, 2) == "男")		//如果性别为“男”，则选中“男”单选按钮，不选中“女”单选按钮
	{
		((CButton *)GetDlgItem(IDC_RADIOmale))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIOfemale))->SetCheck(0);
	}
	else											//否则相反
	{
		((CButton *)GetDlgItem(IDC_RADIOmale))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIOfemale))->SetCheck(1);
	}
	UpdateData(false);					//刷新数据
}


void CStuManagementDlg::OnBnClickedButtonread()			//读取按钮
{

	// TODO: 在此添加控件通知处理程序代码
	
	Management templist;
	LISTC.DeleteAllItems();				//清空所有项，避免重复
	templist.show();				//调用show函数
	list<Student>::iterator c;			
	c = templist._list.begin();			//遍历全部数据
	CString temp = "";
	for (int i = 0; c != templist._list.end(); ++c, i++)		//将数据显示在列表控件中
	{
		temp.Format("%d", c->id);			//非字符串需先转化类型，因为list control里都是CString变量
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


void CStuManagementDlg::OnBnClickedButtonmod()				//修改按钮
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);				//向下刷新数据

	Management m;
	Student temp;

	temp.id = Edit_id;				//将要修改的值赋值给temp
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
		if (((CButton *)GetDlgItem(IDC_RADIOmale))->GetCheck())		//根据单选按钮状态，传递对应的性别字符串
		{
			strcpy_s(temp.sex, "男");
		}
		else
			strcpy_s(temp.sex, "女");

		m.mod(temp);				//调用mod函数
		OnBnClickedButtonread();		//调用载入按钮刷新
	}
}


void CStuManagementDlg::OnBnClickedButtonadd()				//添加按钮
{
	// TODO: 在此添加控件通知处理程序代码

	Management m;
	UpdateData(true);			//向下刷新数据
	Student temp;

	temp.id = Edit_id;				//将要添加的值赋值给temp
	strcpy_s(temp.name, (LPCSTR)Edit_name);
	temp.math = Edit_math;
	temp.cpp = Edit_cpp;
	if (((CButton *)GetDlgItem(IDC_RADIOmale))->GetCheck())		//根据单选按钮状态，传递对应的性别字符串
	{
		strcpy_s(temp.sex, "男");
	}
	else
		strcpy_s(temp.sex, "女");
	//判断学号是否重复
	fstream fat("D:\\student.dat", ios::in | ios::binary);			
	fat.seekg(0, ios::beg);
	Student temp1;
	fat.read((char *)&temp1, sizeof(Student));
	int gg = 0;
	if (temp.math < 0 || temp.math>100 || temp.cpp < 0 || temp.cpp>100)
	{
		gg = 1;
	}
	while (!fat.eof())			//检查所有数据
	{
		if (temp1.id == temp.id)		//若以存在则弹出弹窗并结束循环
		{
			gg = 1;						//将gg设为1
			MessageBox("学号已存在！");
			break;
		}
		else
			fat.read((char *)&temp1, sizeof(Student));		//否则继续读取
	}
	fat.close();
	if (gg == 0)
	{							//gg为0时才调用add函数
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


void CStuManagementDlg::OnBnClickedButtondel()				//删除按钮
{
	// TODO: 在此添加控件通知处理程序代码

	UINT i;
	i = MessageBox(TEXT("确认要删除吗？"), TEXT("删除"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDNO)
	{
		return;
	}

	Management m;
	UpdateData(true);
	Student temp;

	temp.id = Edit_id;

	m.del(temp);			//将输入的学号赋值给del
	
	OnBnClickedButtonread();
}


int SortFlag = 0;

void CStuManagementDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int pos;
	Management temp;

	pos = pNMLV->iSubItem;      //点击排序（获取点击的列数）

	//int state = ((CButton *)GetDlgItem(IDC_CHECKsort))->GetCheck();	//获取checkbox的状态

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

