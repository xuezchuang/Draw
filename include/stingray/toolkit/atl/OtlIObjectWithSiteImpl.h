///////////////////////////////////////////////////////////////////////////////
// OtlIObjectWithSiteImpl.h
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

#ifndef __OTLOBJECTWITHSITE_H__
#define __OTLOBJECTWITHSITE_H__

#ifndef __OTLBASE_H__
	#error otliobjectwithsiteimpl.h requires otlbase.h to be included first
#endif

#include <shlobj.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace StingrayOTL 
{
/////////////////////////////////////////////////////////////////////////////
// OtlIObjectWithSiteImpl<T>
// for creating shell extension band objects,
// base class must implement a "Create" function, or derive from CWindowImpl

template <class T>
class ATL_NO_VTABLE OtlIObjectWithSiteImpl : public IObjectWithSiteImpl<T>
{
public:
	CComQIPtr<IInputObjectSite, &IID_IInputObjectSite> m_pInputObjectSite;
public:
	// IObjectWithSite
	inline STDMETHOD(SetSite)(IUnknown *pUnkSite)
	{

		HRESULT hr = IObjectWithSiteImpl<T>::SetSite(pUnkSite);
		if (FAILED(hr))
				return hr;
		//If punkSite is not NULL, a new site is being set.
		if(pUnkSite)
		{
			//Get the parent window.
			CComQIPtr<IOleWindow> spOleWindow(pUnkSite);
			HWND hwndParent = 0;
			spOleWindow->GetWindow(&hwndParent);
			if(!hwndParent)
				return E_FAIL;
			// create
			T* pBase = static_cast<T*>(this);
			if(!pBase->m_hWnd)
			{
				RECT rc;
				::GetClientRect(hwndParent, &rc);
				if(!pBase->Create(hwndParent, rc))
					return E_FAIL;
			}
			//Get and keep the IInputObjectSite pointer.
			m_pInputObjectSite = pUnkSite;
		}
		
		return S_OK;
	}

};

}; // namespace StingrayOTL

#endif // __OTLOBJECTWITHSITE_H__
