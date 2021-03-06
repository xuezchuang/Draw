///////////////////////////////////////////////////////////////////////////////
// SCutCmds.h
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
//  Author:			Jim Beveridge
//  Description:	Command description classes - Implementation
//  Created:		Sun Jan 28 10:10:29 1996
//
//

#ifndef __SCUTCMDS_H__
#define __SCUTCMDS_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifdef WIN32
#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif // __AFXTEMPL_H__

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

//
// These modifiers always seemed to be defined whenever an accelerator is defined.
// This is empirical, I am not positive what the "real" behavior should be.
const WORD kStandardAcceleratorFlags = FVIRTKEY | FNOINVERT;

namespace SECShortcutUtils {
	TOOLKIT_API void AccelToHotKey(const ACCEL& accel, DWORD* destHotkey);
	TOOLKIT_API void HotKeyToAccel( DWORD destHotkey, ACCEL* accel );
	TOOLKIT_API CString VkToName(UINT nChar, BOOL bExt);
	TOOLKIT_API BOOL GetHotKeyDescription(DWORD hotkey, CString& strKeyName);
	TOOLKIT_API BOOL GetMenuItemString(HMENU hMenu, UINT nIDItem, LPTSTR lpString, int nMaxCount, UINT nFlags);
}

/************************************************************************
 *
 *		SECDefaultCommandId
 *
 *	@class	This structure holds a command id, its short name
 *			its description.  To customize which command id's
 *			the user may assign a macro to, create an array
 *			of this structure and fill it in.
 *
 *
 * For example, this declaration gives the system a
 * list of macro-able command id's, but all of the
 * short names and descriptions are figured out from
 * the corresponding string ids.
 *
 *	const SECDefaultCommandId defaultCommands[] =
 *	{
 *		{ ID_VIEW_TOOLBAR },
 *		{ ID_FILE_SAVE },
 *		// etc.
 *		{ ID_FILE_PRINT }
 *	};
 */
 
//@doc SECCommandList 
//@struct SECDefaultCommandId | This structure holds a command id, its short name and its description.  To customize which
// command ID's the user may assign a macro to, create an array of this structure and fill it in.
//@field UINT | m_nID | The ID of the command, such as ID_VIEW_TOOLBAR
//@field UINT | m_nName | String ID that gives the short name of the command. If this is zero then the menu name or tooltip text is used.
//@field UINT | m_nDescription | String ID that gives the description of the command. If zero then the status bar text is used.	
//@ex Creating a list of macro-able command ID's. | This declaration of an array of SECDefaultCommandId structures gives the system
// a list of macro-able command ID's, but overrides some of the default names and descriptions.
//const SECDefaultCommandId defaultCommands[] =
//	{
//		{ ID_VIEW_TOOLBAR, IDS_MAC_VIEW_TOOLBAR, IDS_DESC_VIEW_TOOLBAR },
//		{ ID_FILE_OPEN, 0, IDS_DESC_FILE_OPEN },	// Default name
//		{ ID_FILE_SAVE, IDS_MAC_FILE_SAVE, 0 },		// Default description
//		// etc.
//		{ ID_FILE_PRINT }							// Default both
//	};
//@xref<c SECCommandList>
struct SECDefaultCommandId
{
	// Id of this command, such as ID_VIEW_TOOLBAR
	UINT	m_nID;

	// String ID that gives the short name of the
	// command.  This name appears in the 
	// "Select a macro:" listbox.  If this is
	// zero, then the menu name or toolhelp text is used.
	UINT	m_nName;

	// String ID that gives the description of the
	// command.  This name appears in the 
	// "Description:" listbox.  If this is zero,
	// then the status bar text for this id is used.
	UINT	m_nDescription;
};



struct SECCommand 
{
	TOOLKIT_API SECCommand();
	TOOLKIT_API SECCommand(UINT nID);

	UINT	m_nID;
	CString	m_strName;
	CString	m_strDescription;
};

//@doc SECCommandList
//@mfunc void  | SECCommandList | SetRules | Call this function to define the invalid 
// combinations and the default modifier combination for a hot key control.The legal values are
// from CHotKeyCtrl::SetRules	.
//@parm WORD  | wInvalidComb | Specifies invalid key combinations.
//@parm WORD | wModifiers | Specifies the key combination to use when an invalid combination is entered. 
//@xref<c SECCommandList>

// adinsert AutoDuck insertion point for SECCommandList 
//@doc SECCommandList 
//@class SECCommandList contains the list of all command IDs that can be assigned, together with a 
//short name and a long description.  
//@comm
// Any and all parts of SECCommandList may be defaulted.
//
// SECCommandList maintains a list of command IDs that may be accelerated.  The accelerator keys 
// themselves are not kept in this structure, because it is a one-to-many relationship.
//
// See the SHORTCUT sample in the \SAMPLES\TOOLKIT\STANDARD\UIEXT\SHORTCUT directory for a demonstration of this class.
//@xref<t SECDefaultCommandId> <c SECShortcutTable> <c SECShortcutDlg> 
//@BASE public|CArray<lt>SECCommand,SECCommand&<gt>
class SECCommandList : public CArray<SECCommand, SECCommand&>
{
//@access Public Members
public:
	//@cmember
	/* Creates an SECCommandList instance.*/
	TOOLKIT_API SECCommandList(BOOL bInitRules=TRUE);
	TOOLKIT_API virtual ~SECCommandList();

	// Use this to allow various key combinations.  The legal values
	// are from CHotKeyCtrl::SetRules	
	//@cmember
	/* Use this function to allow various key combinations. */
	inline virtual void SetRules( WORD wInvalidComb, WORD wModifiers )
		{ m_wInvalidComb = wInvalidComb; m_wModifiers = wModifiers; }

	// You automatically get all the menus.  Call this to
	// get rid of them.
	//@cmember
	/* Call this command to get rid of all the default command IDs.*/
	TOOLKIT_API virtual void ClearCommandIds();

	// Takes an array of DefaultCommandId and adds
	// each entry into the list of legal commands.
	// Non-zero names and descriptions are loaded automatically.
	//@cmember
	/* Installs the custom list of IDs.*/
	TOOLKIT_API virtual void AddCommandIds(const SECDefaultCommandId ids[], int count);

	// Returns TRUE if id should be excluded.
	//@cmember
	/* Determines whether an ID should be excluded.*/
	TOOLKIT_API virtual BOOL QueryExcludeId(UINT nID);

	//@cmember
	/* Fills empty strings.*/
	TOOLKIT_API virtual BOOL FillEmpties();

	//@cmember
	/* Automatically fills empty strings from the menu.*/
	TOOLKIT_API virtual BOOL AutoFillEmptiesFromMenus();
	//@cmember
	/* Automatically fills empty strings from the string IDs.*/
	TOOLKIT_API virtual BOOL AutoFillFromStringIds();

	// Fill in reasonable defaults from the menus, tooltips, etc.
	//@cmember
	/* Loads defaults from the menus, tooltips, etc.,*/
	TOOLKIT_API virtual void DeriveDefaults();

	//@cmember
	/* Verifies the validity of the ID.*/
	TOOLKIT_API virtual int Find(UINT nID);

	// The default implementation loads all the menu ID's.
	//@cmember
	/* Loads all the menu IDs.*/
	TOOLKIT_API virtual BOOL AddDefaultIds();

	//@cmember
	/* Fills empty strings from the menu*/
	TOOLKIT_API virtual BOOL FillEmptiesFromMenu(HMENU hMenu, const CString& strPrevious = _T(""));
	
	//@cmember
	/* Loads IDs from the menu*/
	TOOLKIT_API virtual void LoadIdsFromMenu(HMENU hMenu);
	
	//@cmember
	/* Loads Ids from the accelerator table.*/
	TOOLKIT_API virtual void LoadIdsFromAccelTable();

	// Get rid of the accelerator, the &, the (&x), and the ...
	//@cmember
	/* Extracts accelerator characters from the menu string.*/
	TOOLKIT_API virtual void ExtractMenuItemName(LPTSTR str);

protected:

// Attributes
public:
	WORD	m_wInvalidComb;
	WORD	m_wModifiers;

};


#if _MFC_VER < 0x0400
// VC 4.0  handles this problem all by itself.
TOOLKIT_API void ConstructElements(SECCommand* pTarget, int iCount);
TOOLKIT_API void DestructElements(SECCommand* pTarget, int iCount);
#endif	//  _MFC_VER < 0x0400

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // WIN32
#endif	// __SCUTCMDS_H__

