///////////////////////////////////////////////////////////////////////////////
// usertool.h
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
//  Author:			John Williston
//  Description:	Declaration for SECUserTool
//  Created:		August 1996
//

#ifndef __USERTOOL_H__
#define __USERTOOL_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
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

/////////////////////////////////////////////////////////////////////////////
// SECUserTool

/////////////////////////////
// AutoDuck tag block block for SECUserTool 

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | GetMenuText | The filename of the user-tool will frequently be too long or too cryptic to
// display as a tool name in a menu.  For this reason, user-tools have an alias, or alternate name, that is shown in menus.
//@rdesc The menu text associated with this user-tool.
//@xref<mf SECUserTool::SetMenuText>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc BOOL | SECUserTool | IsWaitEnabled | Indicates whether the wait state is enabled or disabled for the application.
//@rdesc Nonzero if the wait state is enabled; otherwise 0.
//@xref<mf SECUserTool::SetWaitEnabled>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc BOOL | SECUserTool | SetWaitEnabled | Sets the "wait" state to force your application to wait for a spawned process
// to terminate before continuing.  If you want your app to spawn a process, and then continue on as before, you should
// disable the wait.  By default, the wait is enabled.
//@rdesc Nonzero if the wait state is successfully set; otherwise 0.
//@parm BOOL | b | Flag to enable/disable wait state.  Default is enabled.
//@xref<mf SECUserTool::IsWaitEnabled>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | SetMenuText | The filename of the user-tool will frequently be too long or too cryptic to
// display as a tool name in a menu.  For this reason, user-tools have an alias, or alternate name, that is shown in menus.
// Use this method to initialize or modify a user-tool�s menu text.
//@parm LPCTSTR | str |The menu text to associate with the user-tool.
//@xref<mf SECUserTool::GetMenuText>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | GetCommand | Returns the absolute path and filename of the executable that is the user-defined tool.
//@rdesc The filename of the executable that is the user-tool.
//@xref<mf SECUserTool::SetCommand>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | SetCommand | Sets the filename of the executable that is the user-tool.  The filename must be a full,
// absolute path to a file with execute permissions.
//@parm LPCTSTR | str | The filename of this user-tool.
//@xref<mf SECUserTool::GetCommand>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | GetArgs | Returns the command-line arguments that will be passed to the user-defined tool upon execution.
//@rdesc The command-line arguments passed to the user-tool upon execution.
//@xref<mf SECUserTool::SetArgs>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | SetArgs | Sets the command-line arguments that will be passed to the user-tool upon execution.
//@parm LPCTSTR | str |The command-line arguments to the user-tool.
//@xref<mf SECUserTool::GetArgs>
//@xref<c SECUserTool>

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | GetDirectory | Returns the absolute path of the directory in which the user-defined tool
// will be initially executed.
//@rdesc  The initial directory in which the user-tool is run.
//@xref<mf SECUserTool::SetDirectory>
//@xref<c SECUserTool>	

//@doc SECUserTool
//@mfunc LPCTSTR | SECUserTool | SetDirectory | Sets the initial directory in which the user-tool will be run.
//@parm LPCTSTR | str | The initial directory to run the user-tool in.
//@xref<mf SECUserTool::GetDirectory>
//@xref<c SECUserTool>	
	
//@doc SECUserTool
//@mfunc UINT | SECUserTool | GetShowFlag | Returns show window status.
//@rdesc Returns the current ShowWindow flag (ex. SW_SHOWNORMAL). 
//@xref<mf SECUserTool::SetShowFlag>
//@xref<c SECUserTool>	

//@doc SECUserTool
//@mfunc UINT | SECUserTool | SetShowFlag | Sets the appropriate ShowWindow flag (ex. SW_SHOWNORMAL).
//@parm UINT | i | Flag for show window status. Can be a combination of SW_* window flags.  Consult the MFC documentation
// for more information.
//@xref<mf SECUserTool::GetShowFlag>
//@xref<c SECUserTool>	

// adinsert AutoDuck insertion point for SECUserTool 
//@doc SECUserTool 
//@class The SECUserTool class provides an abstraction of a user-tool.  
//@comm
// A user-tool is an executable that can be spawned 
// programmatically by the application.  An SECUserTool object encapsulates the filename, command-line arguments and 
// initial directory that describe how and where the executable should be run.  In addition, the SECUserTool interface 
// contains an Execute member function that uses these attributes to launch the user-defined tool.
//
// In addition to the SECUserTool member functions, several global functions exist for operating on a set of user-tools.
// For example, to serialize an array of user-tools, use the ReadUserToolFile or WriteUserToolFile functions.  To append 
// an array of user-tools to a menu, use the AppendUserTools function.  Finally, to delete an array of user-tools, use the
// EmptyUserToolArray function.
//
// See the TOOLMENU sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\TOOLMENU directory for a demonstration of this class.
//@xref <c SECUserToolsDlg>
//@BASE public|CObject
class SECUserTool : public CObject
{
	TOOLKIT_DECLARE_SERIAL(SECUserTool);

	BOOL m_bWait;
	CString m_strMenuText;
	CString m_strCommand;
	CString m_strArgs;
	CString m_strDirectory;
	UINT m_uiShowFlag;

	TOOLKIT_API BOOL ParseReplacement(LPCTSTR p, CString& strKey, CString& strData) const;
	TOOLKIT_API BOOL Run(LPCTSTR pcszDir, LPCTSTR pcszCmd, UINT uiShow, BOOL bWait) const;

public:
//@Access Public Members
	
	TOOLKIT_API SECUserTool();

	TOOLKIT_API SECUserTool(const SECUserTool& rhs);

	TOOLKIT_API virtual void Serialize(CArchive& archive);

	//@cmember
	/* Indicates whether the "wait" state is enabled or disabled for your application.*/
	inline BOOL IsWaitEnabled() const { return m_bWait; }

	//@cmember
	/* Sets the "wait" state to force your application to wait for a spawned process to terminate before*/
	// continuing.  By default, the wait is enabled.
	inline BOOL SetWaitEnabled(BOOL b) { return m_bWait = b; }

	//@cmember
	/* Returns the menu text associated with this user-defined tool.*/
	inline LPCTSTR GetMenuText() const	{ return m_strMenuText; }

	//@cmember
	/* Sets the menu text associated with this user-tool.*/
	inline LPCTSTR SetMenuText(LPCTSTR str)	{ return m_strMenuText = str; }

	//@cmember
	/* Returns the absolute path and filename of the executable that is the user-defined tool.*/
	inline LPCTSTR GetCommand() const	{ return m_strCommand; }

	//@cmember
	/* Sets the absolute path and filename of the executable that is the user-tool.*/
	inline LPCTSTR SetCommand(LPCTSTR str)
		{ return m_strCommand = str; }

	//@cmember
	/* Returns the command-line arguments that will be passed to the user-defined tool upon execution.*/
	inline LPCTSTR GetArgs() const
		{ return m_strArgs; }

	//@cmember
	/* Sets the command-line arguments that will be passed to the user-tool upon execution.*/
	inline LPCTSTR SetArgs(LPCTSTR str)
		{ return m_strArgs = str; }

	//@cmember
	/* Returns the absolute path of the directory in which the user-defined tool will be initially executed.*/
	inline LPCTSTR GetDirectory() const
		{ return m_strDirectory; }

	//@cmember
	/* Sets the absolute path of the directory in which the user-tool will be initially executed.*/
	inline LPCTSTR SetDirectory(LPCTSTR str)
		{ return m_strDirectory = str; }

	//@cmember
	/* Returns show window status.*/
	inline UINT GetShowFlag() const
		{ return m_uiShowFlag; }

	//@cmember
	/* Sets flag for show window status.*/
	inline UINT SetShowFlag(UINT i)
		{ return m_uiShowFlag = i; }

	//@cmember
	/* Runs the user-tool.*/
	TOOLKIT_API BOOL Execute(CStringList* pReplacements) const;

	//@cmember
	/* Sets the members of one SECUserTool based on another.*/
	TOOLKIT_API SECUserTool& operator=(const SECUserTool& rhs);

	//@cmember
	/* Makes a copy of this SECUserTool object.*/
	TOOLKIT_API SECUserTool* Clone() const;
};


TOOLKIT_API BOOL ReadUserToolFile(LPCTSTR pcszFilename, CObArray& a);

TOOLKIT_API BOOL WriteUserToolFile(LPCTSTR pcszFilename, CObArray& a);

TOOLKIT_API BOOL AppendUserTools(CMenu* pMenu, UINT uiFirstID, const CObArray& a);

TOOLKIT_API void EmptyUserToolArray(CObArray& a);

/////////////////////////////////////////////////////////////////////////////

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif	// __USERTOOL_H__

