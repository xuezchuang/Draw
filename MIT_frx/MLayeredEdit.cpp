#include "StdAfx.h"
#include "MLayeredEdit.h"
#include "MLayeredPropList.h"
#include "MLayeredDockingControlBar.h"

using namespace mit;
using namespace mit::frx;

IMPLEMENT_DYNAMIC(MLayeredEdit, CEdit)
MLayeredEdit::MLayeredEdit(void)
{
	m_bTrack = FALSE;
}

MLayeredEdit::~MLayeredEdit(void)
{
}

BEGIN_MESSAGE_MAP(MLayeredEdit, CEdit)
	//{{AFX_MSG_MAP(MLayeredButton)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MLayeredEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_bTrack == FALSE )
	{
		TRACKMOUSEEVENT MouseEvent;

		::ZeroMemory( &MouseEvent, sizeof( MouseEvent ) );

		// 최초 변수 생성 후 ZeroMemory를 사용해 초기화
		// cbSize에 sizeof를 사용해 크기 저장
		MouseEvent.cbSize       = sizeof( MouseEvent );

		// dwFlag는 TME_LEAVE, WM_MOUSELEAVE 메시지를 수신,
		MouseEvent.dwFlags      = TME_LEAVE;

		// CWnd의 핸들 m_hWnd를 넣어 준다.
		MouseEvent.hwndTrack    = m_hWnd;

		// 마우스 커서가 현재 윈도우에 존재하면 TRUE
		m_bTrack = ::_TrackMouseEvent( &MouseEvent );
	}

	CWnd* pParent = GetParent();
	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
		{
			MLayeredDockingControlBar* pDockWnd = (MLayeredDockingControlBar*)pParent;

			pDockWnd->UpdateFrame(TRUE);
		}
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredPropList)) )
		{
			MLayeredPropList* pPropList = (MLayeredPropList*)pParent;
			pPropList->MakeTransparent(TRUE);
		}
	}

	CEdit::OnMouseMove(nFlags, point);
}

void MLayeredEdit::OnMouseLeave()
{
	m_bTrack = FALSE;

	CWnd* pParent = GetParent();
	if( pParent && pParent->GetSafeHwnd() )
	{
		if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredDockingControlBar)) )
		{
			MLayeredDockingControlBar* pOutputWnd = (MLayeredDockingControlBar*)pParent;

			pOutputWnd->UpdateFrame(FALSE);
		}
		else if( pParent->IsKindOf(RUNTIME_CLASS(MLayeredPropList)) )
		{
			//MLayeredPropList* pPropList = (MLayeredPropList*)pParent; // cppcheck - 사용안됨
			//pPropList->MakeTransparent(FALSE);
		}
	}

	CEdit::OnMouseLeave();
}