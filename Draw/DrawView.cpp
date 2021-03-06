
// DrawView.cpp: CDrawView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDrawView 构造/析构

CDrawView::CDrawView()
{
	// TODO: 在此处添加构造代码

}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawView 绘图

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	for (auto it = pDoc->begin(); it != pDoc->end(); it++)
	{
		CPElement pElement(*it);
		if(pDC->RectVisible(pElement->GetEnclosingRect()))
			pElement->Draw(pDC,m_pSelectElement);
	}
}


// CDrawView 打印


void CDrawView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_ELEMENT_MENU);
	CMenu* pContext(nullptr);
	if (m_pSelectElement)
		pContext = menu.GetSubMenu(0);
	else
	{
		pContext = menu.GetSubMenu(1);
		ElementType mtype = GetDocument()->GetElementType();
		pContext->CheckMenuItem(ID_ELEMENT_LINE, mtype == ElementType::LINE ? MFS_CHECKED : MF_UNCHECKED | MF_BYCOMMAND);
		pContext->CheckMenuItem(ID_ELEMENT_RECTANGLE, mtype == ElementType::RECTANGLE ? MFS_CHECKED : MF_UNCHECKED | MF_BYCOMMAND);
		pContext->CheckMenuItem(ID_ELEMENT_DEFAULT, mtype == ElementType::DEFAULT ? MFS_CHECKED : MF_UNCHECKED | MF_BYCOMMAND);
		ElementColor mcolor = GetDocument()->GetElementColor();
		pContext->CheckMenuItem(ID_COLOR_BLACK, mcolor == ElementColor::BLACK ? MFS_CHECKED : MF_UNCHECKED | MF_BYCOMMAND);
		pContext->CheckMenuItem(ID_COLOR_GREEN, mcolor == ElementColor::GREEN ? MFS_CHECKED : MF_UNCHECKED | MF_BYCOMMAND);
		pContext->CheckMenuItem(ID_COLOR_RED, mcolor == ElementColor::RED ? MFS_CHECKED : MF_UNCHECKED | MF_BYCOMMAND);
		pContext->CheckMenuItem(ID_COLOR_BLUE, mcolor == ElementColor::BLUE ? MFS_CHECKED : MF_UNCHECKED | MF_BYCOMMAND);
	}
	ASSERT(pContext != nullptr);
	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


// CDrawView 诊断

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView 消息处理程序


int CDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect1(5, 5, 100, 25);
	m_EleStatic.Create(_T("Element:"), WS_CHILD | WS_VISIBLE | SS_CENTER, rect1, this, 1235);
	m_EleStatic.MoveWindow(&rect1);
	m_EleStatic.ShowWindow(SW_SHOW);
	CRect rect(100, 5, 200, 25);
	// m_RichEdit是在头文件中添加的CRichEditCtrl型的成员变量
	m_RichEdit.Create(WS_CHILD | WS_CLIPSIBLINGS | WS_EX_TOOLWINDOW | WS_BORDER,
		rect, this, 1234);
	m_RichEdit.MoveWindow(&rect);
	m_RichEdit.ShowWindow(SW_SHOW);

	return 0;
}


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);
	m_FirstPoint = point;
	SetCapture();
}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
		ReleaseCapture();
	if (m_pElement)
	{
		CClientDC aDC(this);
		OnPrepareDC(&aDC);
		aDC.LPtoDP(&point);
		CRect aRect = m_pElement->GetEnclosingRect();
		InvalidateRect(aRect);
		if (GetDocument()->GetElementType() != ElementType::DEFAULT)
			GetDocument()->AddElement(m_pElement);
		m_pElement.reset();
	}

}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);
	m_SecondPoint = point;
	if ((nFlags&MK_LBUTTON) && (this == GetCapture()))
	{
		if (m_pElement)
		{
			aDC.SetROP2(R2_NOTXORPEN);
			m_pElement->Draw(&aDC);
		}
		m_pElement.reset(CreateElement());
		m_pElement->Draw(&aDC);
	}
	else
	{
		auto pOldElement(m_pSelectElement);
		m_pSelectElement = GetDocument()->FindElement(point);
		if ((pOldElement != m_pSelectElement) && (pOldElement || m_pSelectElement))
		{
			if (pOldElement)
				GetDocument()->UpdateAllViews(nullptr, 0, pOldElement.get());
			else
				GetDocument()->UpdateAllViews(nullptr, 0, m_pSelectElement.get());
		}
	}
	
}
#include "Rectangle.h"
#include "Line.h"
#include "DeRectangle.h"


CElement* CDrawView::CreateElement()const
{
	CDrawDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	COLORREF color = static_cast<COLORREF>(pDoc->GetElementColor());
	int lineStyle = pDoc->GetPenStyle();
	switch (pDoc->GetElementType())
	{
	case ElementType::RECTANGLE:
		return new CRectangle(m_FirstPoint, m_SecondPoint, color, lineStyle);
	case ElementType::LINE:
		return new CLine(m_FirstPoint, m_SecondPoint, color, lineStyle);
	case ElementType::DEFAULT:
		//COLORREF jjjj = static_cast<COLORREF>(ElementColor::BLACK);
		return new CDeRectangle(m_FirstPoint, m_SecondPoint, ElementColor::BLACK, lineStyle);
	default:
		return nullptr;
	}
}