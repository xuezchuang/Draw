///////////////////////////////////////////////////////////////////////////////
// SECPANVW.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
// 
//  Author:		Scot Wingo
//  Description:	Declarations for SECPanView
//  Created:		Fri Jun 16 13:43:57 1995
//
//  CHANGELOG
//
//   MSW      9/30/95  Code Review
//
//

#ifndef __SECPANVW_H__
#define __SECPANVW_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SECZMVW_H__
#include "toolkit\seczmvw.h"
#endif

#include <StingrayExportDefs.h>

//
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

//CR MSW: move this into the class.
typedef enum {SEC_PANDELAY,SEC_PANINSTANT} SECPanMode;

// Forward declarations
class SECPanWnd; //lives in secpanwn.h/panwnd.cpp

/////////////////////////////
// AutoDuck tag block block for SECPanView 

//@doc SECPanView
//@mfunc SECPanMode  | SECPanView | GetPanMode | Retrieves the current pan mode, either SEC_PANINSTANT or SEC_PANDELAY.
//@rdesc Returns the pan mode.
//@xref<c SECPanView> <mf SECPanView::SetPanMode>

//@doc SECPanView
//@mfunc BOOL  | SECPanView | IsPanning | Call this function to see if the view is currently panning.
//@rdesc Nonzero if the view is panning, otherwise 0.
//@xref<c SECPanView> <mf SECPanView::StartPan> <mf SECPanView::ContinuePan> <mf SECPanView::EndPan>

//@doc SECPanView
//@mfunc BOOL  | SECPanView | IsOverviewShown | Call this function to see if the overview window is being displayed.
//@rdesc Nonzero if the overview window is visible, otherwise 0.
//@xref<c SECPanView> <mf SECPanView::ShowOverviewWnd> <mf SECPanView::HideOverviewWnd>

// adinsert AutoDuck insertion point for SECPanView 
//@doc SECPanView 
//@class SECPanView adds full panning support to class SECZoomView.  
//@comm
// This allows the user to 
// 'grab' the view with the mouse and drag it to reveal a new visible portion of the view.  
// Panning is a popular alternative to scrollbars, because it adds the flexibility of not having to 
// move the mouse all the way over to a scrollbar.  Also, two degrees of motion are 
// available and views can be panned diagonally, whereas with scrollbars, a series of clicks and 
// mouse moves are necessary to achieve diagonal movement of the view.
//@comm
// SECPanView supports two modes of operation: SEC_PANDELAY and SEC_PANINSTANT.  In SEC_PANDELAY 
// mode, the user moves the view and then the view moves to reflect the new visible area once the 
// user is done.  In SEC_PANINSTANT mode, the user gets instant feedback with every movement of 
// the mouse.
//
// Three key SECPanView member functions are called to perform panning:
//
// <mf SECPanView::StartPan>		A user has started a pan.<nl>
// <mf SECPanView::ContinuePan>	The user is continuing to pan after starting, usually tied to a mouse move.  Updates the view if in SEC_PANINSTANT mode.<nl>
// <mf SECPanView::EndPan>		The user has stopped panning.  Updates the view if in SEC_PANDELAY mode.
//
// Each of these member functions takes a point as an argument so the amount of panning can be calculated.
//
// SECPanView also provides an overview window that shows the user a miniaturization of the entire view.  
// The user can use the overview window to pan the visible portion of the view and also to see where 
// the visible area lies in relation to other portions of the view.  The overview window is especially 
// helpful at large zoom levels when it is possible to lose track of the current location in a complex 
// view.
//
// The CLOUD sample in the \SAMPLES\TOOLKIT\STANDARD\VIEWS\CLOUD directory demonstrates SECPanView.  
// Since SECPanView is derived from <c SECZoomView>, you can mix the two view enhancements together as 
// demonstrated in the CLOUD sample.  CLOUD has all SECPanView and <c SECZoomView> calls highlighted by 
// comments with the class name in them. (e.g., //SECPanView or //SECZoomView).
//@xref<c SECPanWnd> <c SECZoomView>
//@BASE public | SECZoomView
class SECPanView : public SECZoomView
{
    friend class SECPanWnd;
    TOOLKIT_DECLARE_DYNAMIC(SECPanView);

// Construction    
protected:
	// protected constructor used by dynamic creation
	//@Access Constructors
	//@cmember
	/* Creates an SECPanView. This is not called directly.*/
    TOOLKIT_API SECPanView();         

// Attributes
public:
	//@Access Public Members
    //Panning Operations
	//@cmember
	/* Sets the pan mode to one of SEC_PANDELAY or SEC_PANINSTANT.*/
    TOOLKIT_API void SetPanMode(SECPanMode panMode);

	//@cmember
	/* Retrieves the current pan mode.*/
    inline SECPanMode GetPanMode() {return m_panMode;};
     
	//Are we in a pan mode? 
	//@cmember
	/* Is the view currently panning?*/
    inline BOOL IsPanning() { return m_bPanning; }
  
// Operations - virtual so you can change behavior or enhance it.
public:
    //Panning operations
	//@cmember
	/* Put the SECPanView into panning mode.*/
    TOOLKIT_API virtual void StartPan(CPoint * ptPan,
		           UINT nCursorID = 0);

	//@cmember
	/* Continues the pan, causes the view to be updated if in SEC_PANINSTANT mode.*/
    TOOLKIT_API virtual void ContinuePan(CPoint *ptPan);

	//@cmember
	/* Stops the pan, causes the view to be updated if in SEC_PANDELAY mode.*/
    TOOLKIT_API virtual void EndPan(CPoint *ptPan);

	//@Access Overview Window Operations
	//@cmember
	/* Is the overview window being displayed?*/
    inline BOOL IsOverviewShown() { return m_pOverview != NULL; }
    
    //Overview Window operations
	//@cmember
	/* Displays the overview PanWnd window.*/
    TOOLKIT_API virtual BOOL ShowOverviewWnd(CRect);

	//@cmember
	/* Hides the overview PanWnd window.*/
    TOOLKIT_API virtual BOOL HideOverviewWnd();
    
	//@cmember
	/* Call to update the overview window.*/
    TOOLKIT_API virtual void UpdateOverviewWnd(CView * pSender,
				   LPARAM lHint = 0L,
				   CObject * pHint = NULL);

	//@cmember
	/* When overview window is updated, invalidates all of the window or, using hints, only some regions for repainting.*/
    TOOLKIT_API virtual void OnUpdateOverview(CView * pSender,
				  LPARAM lHint,CObject * pHint,
				  CDC * pOverviewDC, CWnd * pWndOverview);

// Overrideables - OverRide this to get notifications of zoom level change
protected:    
    TOOLKIT_API virtual void ZoomLevelChanged(void); //From SECZoomView
    
// Implementation
public:
    TOOLKIT_API virtual ~SECPanView();
#ifdef _DEBUG
    TOOLKIT_API void Dump(CDumpContext&) const;
    TOOLKIT_API void AssertValid() const;
#endif //_DEBUG

protected:
    TOOLKIT_API virtual void OnDraw(CDC* pDC) = 0; // Pass on Pure Virtual from SECZoomView
    //Internal functions
    TOOLKIT_API void PerformPan(CPoint *ptEndPan,BOOL bReversePan = FALSE);
    TOOLKIT_API void UpdateOverviewRect();
    TOOLKIT_API void PreOverview();
    TOOLKIT_API void PostOverview();
    TOOLKIT_API void OverviewDestroyed();
    TOOLKIT_API virtual void UpdatePanViewport(CPoint * lpPtNewLog);
    
protected:
    // Member variables
    UINT       m_nCursorID;
    SECPanMode m_panMode;
    BOOL       m_bPanning;
    HCURSOR    m_hOrigCursor;
    HCURSOR    m_hDragCursor;
    CPoint     m_ptLogStartDrag; //Logical coords of pan start
    SECPanWnd *  m_pOverview;    //The overview window.
	CPtrList   m_listAllocOverview;

    //These member store state needed for the overview window.
    CSize       m_orig_szTotalDev;
    BOOL        m_orig_bCenter;
    UINT        m_orig_zoomMode;    
    BOOL        DoScroll(CSize sizeScroll, BOOL bDoScroll);
    
public:
    // Generated message map functions
    //{{AFX_MSG(SECPanView)
    TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    TOOLKIT_API afx_msg void OnHScroll(UINT,UINT,CScrollBar*);
    TOOLKIT_API afx_msg void OnVScroll(UINT,UINT,CScrollBar*);
    TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    //}}AFX_MSG

    TOOLKIT_DECLARE_MESSAGE_MAP();
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SECPANVW_H__



