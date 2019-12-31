// copyFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "copyFile.h"
#include "copyFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyFileDlg dialog

CCopyFileDlg::CCopyFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyFileDlg)
	m_ebx_cpfrom = _T("");
	m_cbx_cpto = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopyFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyFileDlg)
	DDX_Control(pDX, BTN_BROWSE2, m_browse_to);
	DDX_Control(pDX, BTN_BROWSE1, m_browse_from);
	DDX_Control(pDX, BTN_CP, m_btn_cp);
	DDX_Control(pDX, IDC_PROGRESSBAR, m_cp_progress);
	DDX_Text(pDX, EBX_CPFROM, m_ebx_cpfrom);
	DDX_Text(pDX, EBX_CPTO, m_cbx_cpto);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCopyFileDlg, CDialog)
	//{{AFX_MSG_MAP(CCopyFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_BROWSE1, OnBrowse1)
	ON_EN_UPDATE(EBX_CPFROM, OnEnter_CP_From)
	ON_BN_CLICKED(BTN_BROWSE2, OnBrowse2)
	ON_BN_CLICKED(BTN_CP, OnCp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyFileDlg message handlers

BOOL CCopyFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCopyFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCopyFileDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCopyFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCopyFileDlg::OnBrowse1() 
{
	// TODO: Add your control notification handler code here
	CString path_str;
    //constructs a CFileDialog object (with initial parameters)
    CFileDialog OpenLink(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, NULL, NULL);
    OpenLink.m_ofn.lpstrTitle = NULL;
    
    OpenLink.m_ofn.lpstrInitialDir = path_str;
    OpenLink.DoModal();
    
    path_str = OpenLink.GetPathName();
   

    
    m_ebx_cpfrom = path_str;
    UpdateData(FALSE);

	
}

void CCopyFileDlg::OnEnter_CP_From() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here

	
}

void CCopyFileDlg::OnBrowse2() 
{
	// TODO: Add your control notification handler code here
    CString path_str;
    //constructs a CFileDialog object (with initial parameters)
    CFileDialog OpenLink(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, NULL, NULL);
    OpenLink.m_ofn.lpstrTitle = NULL;
    
    OpenLink.m_ofn.lpstrInitialDir = path_str;
    OpenLink.DoModal();
    
    path_str = OpenLink.GetPathName();
    
    m_cbx_cpto = path_str;
    UpdateData(FALSE);
    

	
}

DWORD ThreadFunction( LPVOID param )
{
    CCopyFileDlg* ptr = (CCopyFileDlg*)param;
    ptr->copy_file();
    return 0;
}

void CCopyFileDlg::OnCp() 
{

    m_cp_progress.SetPos(0);
    // CProgressCtrl
    //copy_file();
    CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadFunction, this, NULL, NULL );


}

void CCopyFileDlg::copy_file()
{
    m_btn_cp.EnableWindow(FALSE);
    m_browse_from.EnableWindow(FALSE);
    m_browse_to.EnableWindow(FALSE);
    FILE* file_src = fopen(m_ebx_cpfrom.GetBuffer(0), "rb");

    //check if successfully opened the file using file_src
    if ( !file_src  )
    {
        m_btn_cp.EnableWindow(TRUE);
        m_browse_from.EnableWindow(TRUE);
        m_browse_to.EnableWindow(TRUE);
        return;
    }
    
    //finds the size of the file source being copied

    //sets the file pointer to the end of the file (with SEEK_END)
    fseek(file_src, 0, SEEK_END);
    //ftell obtains the current position of the file pointer (thus size of the file is obtained)
    int size = ftell(file_src);
    //set the file pointer back to its initial position
    fseek(file_src, 0, SEEK_SET);
    


    //opens the destination file 
    FILE* file_dest = fopen(m_cbx_cpto.GetBuffer(0), "wb");


    //check if successfully opens the destination file, if not -> need to close the successfully opened source file
    if ( !file_dest )
    {
        fclose(file_src);
        m_browse_from.EnableWindow(TRUE);
        m_browse_to.EnableWindow(TRUE);
        m_btn_cp.EnableWindow(TRUE);
        return;
    }


    // occupies the space for a buffer - size of 4096(4K) with character array
    char buffer[4096];

    int ncount = 0;
   
    do{
        
        //reads the file_src into the buffer occupied (with fread)
        int _read  = fread(buffer, sizeof(char), 4096, file_src);
        //writes the information in the buffer into file_dest
        fwrite(buffer, sizeof(char), _read, file_dest);

        //since the scope of variable _read is in the do-while loop, it will be set to zero while looping
        //ncount variable is declared outside of the loop to count the bytes being read
        ncount += _read;

        //percentage of the copied bytes calculated 
        float percent = (float)ncount / (float)size;
        int nPercent = (int)(percent * 100);

        
        m_cp_progress.SetPos(nPercent);

        if ( feof(file_src) )
        {
            break;
        }
    }while(1);
    
    fclose(file_src);
    fclose(file_dest);
    m_browse_from.EnableWindow(TRUE);
    m_browse_to.EnableWindow(TRUE);
    m_btn_cp.EnableWindow(TRUE);
}


