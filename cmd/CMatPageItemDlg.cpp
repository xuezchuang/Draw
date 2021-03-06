// CMatPageItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "CMatPageItemDlg.h"
#include "../BaseLib/DlgUtil.h"
#include "../DB/MatlDB.h"
#include "../DB/DataCtrl.h"
#include "../DB/AttrCtrl.h"
//#include "afxdialogex.h"

#define CCM_TYPE_STEEL  _ULS(S)
#define CCM_TYPE_CONCR  _ULS(C)
#define CCM_TYPE_SRC    _ULS(SRC)
#define CCM_TYPE_USER   _ULS(U)
#define CCM_TYPE_ALUMNI _ULS(A)

#define CCM_STEEL       _LS(IDS_WG_CMD__ADDD__Steel)
#define CCM_CONCR       _LS(IDS_WG_CMD__ADDD__Concrete)
#define CCM_SRC         _LS(IDS_WG_CMD__ADDD__SRC)
#define CCM_USER        _LS(IDS_WG_CMD__ADDD__User)
#define CCM_ALUMINIUM   _LS(IDS_WG_CMD__ADDD__Aluminium)

#define CCM_TYPE_STEEL_I  0
#define CCM_TYPE_CONCR_I  1
#define CCM_TYPE_SRC_I    2
#define CCM_TYPE_ALUMI_I  3
#define CCM_TYPE_USER_I   4
#define CDialog CDialogMove
IMPLEMENT_DYNAMIC(CCMatPageItemDlg, CDialog)

CCMatPageItemDlg::CCMatPageItemDlg(CDBDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CMD_MP_ITEM_DLG, pParent)
{
	m_pDoc = pDoc;
	m_pBitmap = 0;
	m_bModify = FALSE;

	m_aCtrlThermalConc.Add(IDC_CMD_MP_ITEM_CODE);
	m_aCtrlThermalConc.Add(IDC_CMD_MP_ITEM_CBO);
	m_aCtrlThermalSteel.Add(IDC_CMD_MP_ITEM_CBO2);
	m_aCtrlThermalSteel.Add(IDC_CMD_MP_ITEM_CODE2);
}

CCMatPageItemDlg::~CCMatPageItemDlg()
{
}

void CCMatPageItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_wndID);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_TYPE, m_wndType);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_CODE, m_wndConcrCode);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_CODE2, m_wndSteelCode);
	DDX_Control(pDX, IDC_CMD_FRAME, m_wndStlCodeFrame);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_CBO, m_wndConcName);
	DDX_Control(pDX, IDC_CMD_MP_ITEM_CBO2, m_wndSteelName);
	DDX_Control(pDX, IDC_EDIT2, m_wndName);
}


BEGIN_MESSAGE_MAP(CCMatPageItemDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_CMD_MP_ITEM_TYPE, &CCMatPageItemDlg::OnChangeType)
	ON_BN_CLICKED(IDOK, &CCMatPageItemDlg::OnBtnOk)
	ON_CBN_SELCHANGE(IDC_CMD_MP_ITEM_CODE2, &CCMatPageItemDlg::OnChangeSteelCode)
	ON_CBN_SELCHANGE(IDC_CMD_MP_ITEM_CODE, &CCMatPageItemDlg::OnChangeConcrCode)
	ON_EN_CHANGE(IDC_EDIT1, &CCMatPageItemDlg::OnChangeID)
	ON_EN_CHANGE(IDC_EDIT2, &CCMatPageItemDlg::OnChangeName)
	ON_CBN_SELCHANGE(IDC_CMD_MP_ITEM_CBO2, &CCMatPageItemDlg::OnChangeSteelName)
	ON_BN_CLICKED(IDCANCEL2, &CCMatPageItemDlg::OnApply)
END_MESSAGE_MAP()


// CCMatPageItemDlg 消息处理程序
void CCMatPageItemDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}

BOOL CCMatPageItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_wndName.SetWindowText(CString(_T("")));
	m_Key = m_pDoc->m_pAttrCtrl->GetStartNumMatl();
	m_Data.initialize();
	m_Data.Type = CCM_TYPE_STEEL;

	//GetDefaultCode();
	SetAutoChangeNameFlag(m_Data.Name);
	SetTypeCombo();
	ShowDataToDlg();
	return TRUE;  
}

void CCMatPageItemDlg::GetDefaultCode()
{
	CArray<CString, CString&> aConcrCodeList;
	m_pDoc->m_pMatlDB->GetDesignCodeList(CString("C"), aConcrCodeList);
}

void CCMatPageItemDlg::ShowDataToDlg()
{
	CString csValue;
	csValue.Format(_T("%d"), m_Key);
	m_wndID.SetWindowText(csValue);
	ChangeDlgCtrls();
}

void CCMatPageItemDlg::SetTypeCombo()
{
	CDlgUtil::CobxAddItem(m_wndType, CCM_STEEL, CCM_TYPE_STEEL_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_CONCR, CCM_TYPE_CONCR_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_SRC, CCM_TYPE_SRC_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_ALUMINIUM, CCM_TYPE_ALUMI_I);
	CDlgUtil::CobxAddItem(m_wndType, CCM_USER, CCM_TYPE_USER_I);
	CDlgUtil::CobxSetCurSelItemData(m_wndType, CCM_TYPE_STEEL_I);
}

void CCMatPageItemDlg::SetCode(CComboBox* pCombo, const CString & strType)
{
	pCombo->ResetContent();
	CArray<CString, CString&>aDesignCodeList;
	m_pDoc->m_pMatlDB->GetDesignCodeList(strType, aDesignCodeList);
	int nSize = (int)aDesignCodeList.GetSize();
	for (int i = 0; i < nSize; i++)
		pCombo->AddString(aDesignCodeList[i]);
}

void CCMatPageItemDlg::SetNameCombo(CComboBox* pCombo, const CString& strType, const CString& csCode)
{
	pCombo->ResetContent();
	CArray<CString, CString&> aNameList;
	if (strType == CCM_TYPE_STEEL)
		m_pDoc->m_pMatlDB->GetSteelNameList(csCode, aNameList);
	for (int i = 0; i < aNameList.GetSize(); i++)
		pCombo->AddString(aNameList[i]);
}

void CCMatPageItemDlg::SetSteelCode(int nTypeIndex)
{
	if (nTypeIndex == CCM_TYPE_STEEL_I || nTypeIndex == CCM_TYPE_SRC_I)SetCode(&m_wndSteelCode, CCM_TYPE_STEEL);
	else if (nTypeIndex == CCM_TYPE_ALUMI_I)SetCode(&m_wndConcrCode, CCM_TYPE_ALUMNI);
	else if (nTypeIndex == CCM_TYPE_USER_I)SetCode(&m_wndConcrCode, CCM_TYPE_USER);
	else if (nTypeIndex == CCM_TYPE_CONCR_I)m_wndSteelCode.ResetContent();
	else ASSERT(FALSE);
}

void CCMatPageItemDlg::SetConcrCode(int nTypeIndex)
{
	if (nTypeIndex == CCM_TYPE_CONCR_I || nTypeIndex == CCM_TYPE_SRC_I)SetCode(&m_wndConcrCode, CCM_TYPE_CONCR);
	else if (nTypeIndex == CCM_TYPE_USER_I || nTypeIndex == CCM_TYPE_ALUMI_I || nTypeIndex == CCM_TYPE_STEEL_I)
		m_wndConcrCode.ResetContent();
	else ASSERT(FALSE);
}

void CCMatPageItemDlg::SetFrameName(int nTypeIndex)
{
	CString strTitle = CCM_STEEL;
	if (nTypeIndex == CCM_TYPE_ALUMI_I)
		strTitle = CCM_ALUMINIUM;
	else if (nTypeIndex == CCM_TYPE_USER_I)
		strTitle = CCM_USER;
	m_wndStlCodeFrame.SetWindowText(strTitle);
}

void CCMatPageItemDlg::ChangeBitmap(int nBitmap)
{
	UINT aBitmap[] = { IDB_CMD_BITMAP1,IDB_CMD_BITMAP2,IDB_CMD_BITMAP3,IDB_CMD_BITMAP4,IDB_CMD_BITMAP5 };
	if (m_pBitmap) delete m_pBitmap;
	m_pBitmap = new CBitmap;
	CStatic* pImage = (CStatic*)GetDlgItem(IDC_CMD_PICTURE);
	m_pBitmap->LoadBitmap(aBitmap[nBitmap]);
	pImage->SetBitmap(HBITMAP(*m_pBitmap));
}

void CCMatPageItemDlg::ChangeDlgCtrls()
{
	int nTypeIndex = GetTypeIndex(m_Data.Type);
	//m_wndSteelCode.ResetContent();
	SetFrameName(nTypeIndex);
	SetConcrCode(nTypeIndex);
	SetSteelCode(nTypeIndex);
	SetNameCombo(&m_wndSteelName, m_Data.Type, m_Data.Data1.CodeName);
	SetNameCombo(&m_wndConcName, m_Data.Type, m_Data.Data1.CodeName);
	BOOL bThermalSteel = FALSE;
	BOOL bThermalConc = FALSE;
	if (nTypeIndex == CCM_TYPE_STEEL_I)
	{
		bThermalSteel = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_CONCR_I)
	{
		bThermalConc = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_SRC_I)
	{
		bThermalConc = TRUE;
		bThermalSteel = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_ALUMI_I)
	{
		bThermalSteel = TRUE;
	}
	else if (nTypeIndex == CCM_TYPE_USER_I)
	{
		bThermalConc = TRUE;
		bThermalSteel = TRUE;
	}
	else ASSERT(0);
#pragma region 22
	CDlgUtil::CtrlEnableDisable(this, m_aCtrlThermalSteel, bThermalSteel);
	CDlgUtil::CtrlEnableDisable(this, m_aCtrlThermalConc, bThermalConc);
#pragma endregion 22
}

void CCMatPageItemDlg::SetAutoChangeNameFlag(CString csName)
{
	if (csName == _T(""))
		m_bAutoChangeName = TRUE;
	else
	{
		CString csTempSteelName, csTemtpConcName;
		m_wndSteelName.GetWindowText(csTempSteelName);
		m_wndConcName.GetWindowText(csTemtpConcName);
		if(csTempSteelName == csName || csTemtpConcName == csName)
			m_bAutoChangeName = TRUE;
		else
			m_bAutoChangeName = FALSE;
	}
		
}

int CCMatPageItemDlg::GetTypeIndex(CString strType) const
{
	if (strType == CCM_TYPE_STEEL) return CCM_TYPE_STEEL_I;
	if (strType == CCM_TYPE_ALUMNI) return CCM_TYPE_ALUMI_I;
	if (strType == CCM_TYPE_CONCR) return CCM_TYPE_CONCR_I;
	if (strType == CCM_TYPE_USER) return CCM_TYPE_USER_I;
	if (strType == CCM_TYPE_SRC) return CCM_TYPE_SRC_I;
	ASSERT(0);
	return 0;
}

CString CCMatPageItemDlg::GetTypeCode(int nTypeIndex) const
{
	if (nTypeIndex == CCM_TYPE_STEEL_I) return CCM_TYPE_STEEL;
	if (nTypeIndex == CCM_TYPE_ALUMI_I) return CCM_TYPE_ALUMNI;
	if (nTypeIndex == CCM_TYPE_CONCR_I) return CCM_TYPE_CONCR;
	if (nTypeIndex == CCM_TYPE_USER_I) return CCM_TYPE_USER;
	if (nTypeIndex == CCM_TYPE_SRC_I) return CCM_TYPE_SRC;
	ASSERT(0);
	return  _T("");
}

BOOL CCMatPageItemDlg::CheckData()
{
	int nId;
	CString csName;
	if (!m_wndID.GetEditValue(nId))
	{
		AfxMessageBox(_LS(IDS_WG_CMD__ADDD__Error___Invalid_material_number_));
		return FALSE;
	}

	m_wndName.GetWindowText(csName);
	csName.TrimLeft(); csName.TrimRight();
	if (csName == _T(""))
	{
		AfxMessageBox(_LS(IDS_WG_CMD__ADDD__Error___Missing_material_name_));
		return FALSE;
	}
	m_Data.Name = csName;
	CString csType;
	m_wndType.GetWindowText(csType);
	if(csType == CCM_STEEL)
	{
		if(m_wndSteelCode.GetCount() == 0)
		{
			AfxMessageBox(_LS(IDS_WG_CMD__ADDD__Error___Missing_material_STEEL_CODE));
			return FALSE;
		}
		else if(m_wndSteelName.GetCount() == 0)
		{
			AfxMessageBox(_LS(IDS_WG_CMD__ADDD__Error___Missing_material_STEEL_NAME));
			return FALSE;
		}
	}
	else if(csType == CCM_CONCR)
	{
		if(m_wndConcrCode.GetCount() == 0)
		{
			AfxMessageBox(_LS(IDS_WG_CMD__ADDD__Error___Missing_material_CONC_CODE));
			return FALSE;
		}
		else if(m_wndConcName.GetCount() == 0)
		{
			AfxMessageBox(_LS(IDS_WG_CMD__ADDD__Error___Missing_material_CONC_NAME));
			return FALSE;
	}
	}
	return TRUE;
}

void CCMatPageItemDlg::OnChangeType()
{
	DWORD dwType;
	if (!CDlgUtil::CobxGetItemDataByCurSel(m_wndType, dwType))dwType = -1;
	int nTypeIndex = dwType;
	ChangeBitmap(nTypeIndex);
	m_Data.Type = GetTypeCode(nTypeIndex);
	ShowDataToDlg();
}
void CCMatPageItemDlg::OnApply()
{
	if (!CheckData())return;
	m_pDoc->m_pDataCtrl->AddMatl(m_Key, m_Data);
	OnInitDialog();

}
void CCMatPageItemDlg::OnBtnOk()
{
	if (!CheckData())return;
	if(m_pDoc->m_pDataCtrl->AddMatl(m_Key, m_Data))
		CDialog::OnOK();
}

void CCMatPageItemDlg::OnChangeSteelCode()
{
	CString csCode;
	m_wndSteelCode.GetWindowText(csCode);
	m_Data.Data1.CodeName = csCode;
	SetNameCombo(&m_wndSteelName, m_Data.Type, csCode);
}

void CCMatPageItemDlg::OnChangeConcrCode()
{
	CString csCode;
	m_wndConcrCode.GetWindowText(csCode);
	m_Data.Data1.CodeName = csCode;
	SetNameCombo(&m_wndConcName, m_Data.Type, csCode);
}

void CCMatPageItemDlg::OnChangeSteelName()
{
	CString csName;
	m_wndSteelName.GetWindowText(csName);
	m_Data.Data1.CodeMatlName = csName;
	if (m_bAutoChangeName)
	{
		m_Data.Name = csName;
		m_wndName.SetWindowText(csName);
	}
}

void CCMatPageItemDlg::OnChangeID()
{
	int nId;
	if (m_wndID.GetEditValue(nId))
		m_Key = nId;
}

void CCMatPageItemDlg::OnChangeName()
{
	CString csName;
	m_wndName.GetWindowText(csName);
	//m_Data.Name = csName;
	SetAutoChangeNameFlag(csName);
}

