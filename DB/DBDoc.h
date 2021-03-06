#pragma once
#include "../BaseLib/DocBase.h"
#include "HeaderPre.h"
class CDataMemb;
class CMatlDB;
class CSectDB;
class CAttrCtrl;
class CDataCtrl;
class CEditData;
class CUndoCtrl;
class CModelessDlgCtrl;
class CViewBuff;
class CUndoRedo;
class CUndoRedoDlg;
extern __declspec(dllexport) void ConverCharStr(char chSource[],CString& strDestin,int nChar);
class __MY_EXT_CLASS__ CDBDoc : public CDocBase
{
	//friend class CEditData;
	friend class CViewBuff;

	friend class CUndoCtrl;
	DECLARE_DYNCREATE(CDBDoc)
protected:
	CDBDoc();
	static CDBDoc* m_pDBDoc;
	BOOL m_bIsUndoRedoVisible;
	CUndoRedoDlg* m_pUndoRedoDlg;
public:
	CEditData * m_pEditData;
	CUndoCtrl * m_pUndoCtrl;
public:
	CAttrCtrl * m_pAttrCtrl;
	CDataCtrl* m_pDataCtrl;
	CMatlDB* m_pMatlDB;
	CSectDB* m_pSectDB;
	CDataMemb* m_memb;
	CViewBuff* m_pViewBuff;
	static CDBDoc* GetDocPoint();

	CUndoRedo * m_undo;				//undo buffer
	CUndoRedo * m_redo;				//redo buffer
private:
	CUndoRedo * m_vbuff;			//update view buffer
public:
	void CloseUDRDVisible();
	void UpdateViews(LPARAM lUpdataType);
	void UpdateAllViews(CView* pSender, LPARAM lHint, CObject* pHint = NULL);
	void DoUndoOnly();
	void DoRedo();
	void DoUndo();
	CString GetProgramPath();
	DECLARE_MESSAGE_MAP()
};
#include "HeaderPost.h"
