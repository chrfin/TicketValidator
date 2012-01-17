//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
// This is a part of the Active Template Library.
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __ATLWIN_H__
#define __ATLWIN_H__

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLBASE_H__
	#error atlwin.h requires atlbase.h to be included first
#endif

struct _ATL_WNDCLASSINFOA;
struct _ATL_WNDCLASSINFOW;

#if defined(_WIN32_WCE)
	#if (_WIN32_WCE <= 210)
		extern "C" LPVOID MapPtrToProcess(LPVOID lpv, HANDLE hProc);
	#else
		extern "C" LPVOID WINAPI MapPtrToProcess(LPVOID lpv, HANDLE hProc);
	#endif
#endif // _WIN32_WCE

#ifndef _ATL_DLL_IMPL
namespace ATL
{
#endif

ATLAPI_(ATOM) AtlModuleRegisterWndClassInfoA(_ATL_MODULE* pM, _ATL_WNDCLASSINFOA* p, WNDPROC* pProc);
ATLAPI_(ATOM) AtlModuleRegisterWndClassInfoW(_ATL_MODULE* pM, _ATL_WNDCLASSINFOW* p, WNDPROC* pProc);

#ifdef UNICODE
#define AtlModuleRegisterWndClassInfo AtlModuleRegisterWndClassInfoW
#else
#define AtlModuleRegisterWndClassInfo AtlModuleRegisterWndClassInfoA
#endif


#define HIMETRIC_PER_INCH   2540
#define MAP_PIX_TO_LOGHIM(x,ppli)   ( (HIMETRIC_PER_INCH*(x) + ((ppli)>>1)) / (ppli) )
#define MAP_LOGHIM_TO_PIX(x,ppli)   ( ((ppli)*(x) + HIMETRIC_PER_INCH/2) / HIMETRIC_PER_INCH )

ATLAPI_(HDC) AtlCreateTargetDC(HDC hdc, DVTARGETDEVICE* ptd);
ATLAPI_(void) AtlHiMetricToPixel(const SIZEL * lpSizeInHiMetric, LPSIZEL lpSizeInPix);
ATLAPI_(void) AtlPixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric);


#ifndef _ATL_DLL_IMPL
}; //namespace ATL
#endif

#if defined(_WIN32_WCE)
struct _ATL_WNDCLASSINFOW
{
	WNDCLASS m_wc;
	LPCTSTR m_lpszOrigName;
	WNDPROC pWndProc;
	LPCTSTR m_lpszCursorID;
	BOOL m_bSystemCursor;
	ATOM m_atom;
	TCHAR m_szAutoName[13];
	ATOM Register(WNDPROC* p)
	{
		return AtlModuleRegisterWndClassInfoW(&_Module, this, p);
	}
};
#else // _WIN32_WCE
struct _ATL_WNDCLASSINFOA
{
	WNDCLASSEXA m_wc;
	LPCSTR m_lpszOrigName;
	WNDPROC pWndProc;
	LPCSTR m_lpszCursorID;
	BOOL m_bSystemCursor;
	ATOM m_atom;
	CHAR m_szAutoName[13];
	ATOM Register(WNDPROC* p)
	{
		return AtlModuleRegisterWndClassInfoA(&_Module, this, p);
	}
};
struct _ATL_WNDCLASSINFOW
{
	WNDCLASSEXW m_wc;
	LPCWSTR m_lpszOrigName;
	WNDPROC pWndProc;
	LPCWSTR m_lpszCursorID;
	BOOL m_bSystemCursor;
	ATOM m_atom;
	WCHAR m_szAutoName[13];
	ATOM Register(WNDPROC* p)
	{
		return AtlModuleRegisterWndClassInfoW(&_Module, this, p);
	}
};
#endif // _WIN32_WCE

namespace ATL
{

/////////////////////////////////////////////////////////////////////////////
// Forward declarations

class CWindow;
#ifndef _ATL_NO_HOSTING
template <class TBase = CWindow> class CAxWindowT;
#endif //!_ATL_NO_HOSTING
class CMessageMap;
class CDynamicChain;
typedef _ATL_WNDCLASSINFOA CWndClassInfoA;
typedef _ATL_WNDCLASSINFOW CWndClassInfoW;
#ifdef UNICODE
#define CWndClassInfo CWndClassInfoW
#else
#define CWndClassInfo CWndClassInfoA
#endif
template <class T, class TBase = CWindow, class TWinTraits = CControlWinTraits> class CWindowImpl;
template <class T, class TBase = CWindow> class CDialogImpl;
#ifndef _ATL_NO_HOSTING
template <class T, class TBase = CWindow> class CAxDialogImpl;
#endif //!_ATL_NO_HOSTING
template <WORD t_wDlgTemplateID, BOOL t_bCenter = TRUE> class CSimpleDialog;
template <class TBase = CWindow, class TWinTraits = CControlWinTraits> class CContainedWindowT;

/////////////////////////////////////////////////////////////////////////////
// CWindow - client side for a Windows window

class CWindow
{
protected:
#if defined(_WIN32_WCE_AYGSHELL) && (_WIN32_WCE >= 300)
	BOOL m_bShowDoneButton;
	HWND m_hWndCB;
#endif // _WIN32_WCE_AYGSHELL
public:
	static RECT rcDefault;
	HWND m_hWnd;

	CWindow(HWND hWnd = NULL)
	{
#if defined(_WIN32_WCE_AYGSHELL) && (_WIN32_WCE >= 300)
		m_bShowDoneButton = FALSE;
		m_hWndCB = NULL;
#endif // _WIN32_WCE_AYGSHELL
		m_hWnd = hWnd;
	}

	CWindow& operator=(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	static LPCTSTR GetWndClassName()
	{
		return NULL;
	}

	void Attach(HWND hWndNew)
	{
		ATLASSERT(::IsWindow(hWndNew));
		m_hWnd = hWndNew;
	}

	HWND Detach()
	{
		HWND hWnd = m_hWnd;
		m_hWnd = NULL;
		return hWnd;
	}

	HWND Create(LPCTSTR lpstrWndClass, HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		m_hWnd = ::CreateWindowEx(dwExStyle, lpstrWndClass, szWindowName,
			dwStyle, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
			rcPos.bottom - rcPos.top, hWndParent, (HMENU)nID,
			_Module.GetModuleInstance(), lpCreateParam);
		return m_hWnd;
	}

	HWND Create(LPCTSTR lpstrWndClass, HWND hWndParent, LPRECT lpRect = NULL, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			HMENU hMenu = NULL, LPVOID lpCreateParam = NULL)
	{
		if(lpRect == NULL)
			lpRect = &rcDefault;
		m_hWnd = ::CreateWindowEx(dwExStyle, lpstrWndClass, szWindowName,
			dwStyle, lpRect->left, lpRect->top, lpRect->right - lpRect->left,
			lpRect->bottom - lpRect->top, hWndParent, hMenu,
			_Module.GetModuleInstance(), lpCreateParam);
		return m_hWnd;
	}

	BOOL DestroyWindow()
	{
		ATLASSERT(::IsWindow(m_hWnd));

#if defined(_WIN32_WCE_AYGSHELL) && (_WIN32_WCE >= 300)
		if (m_hWndCB != NULL)
		{
			if (!::DestroyWindow(m_hWndCB))
				return FALSE;
			m_hWndCB = NULL;
		}
#endif // _WIN32_WCE_AYGSHELL

		if(!::DestroyWindow(m_hWnd))
			return FALSE;

		m_hWnd = NULL;
		return TRUE;
	}

// Attributes

	operator HWND() const { return m_hWnd; }

	DWORD GetStyle() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (DWORD)::GetWindowLong(m_hWnd, GWL_STYLE);
	}

	DWORD GetExStyle() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (DWORD)::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	}

	LONG GetWindowLong(int nIndex) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowLong(m_hWnd, nIndex);
	}

	LONG SetWindowLong(int nIndex, LONG dwNewLong)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowLong(m_hWnd, nIndex, dwNewLong);
	}

#if !defined(_WIN32_WCE)
	WORD GetWindowWord(int nIndex) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowWord(m_hWnd, nIndex);
	}

	WORD SetWindowWord(int nIndex, WORD wNewWord)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowWord(m_hWnd, nIndex, wNewWord);
	}
#endif // _WIN32_WCE

// Message Functions

	LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SendMessage(m_hWnd,message,wParam,lParam);
	}

	BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::PostMessage(m_hWnd,message,wParam,lParam);
	}

	BOOL SendNotifyMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SendNotifyMessage(m_hWnd, message, wParam, lParam);
	}

	// support for C style macros
	static LRESULT SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ATLASSERT(::IsWindow(hWnd));
		return ::SendMessage(hWnd, message, wParam, lParam);
	}

// Window Text Functions

	BOOL SetWindowText(LPCTSTR lpszString)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowText(m_hWnd, lpszString);
	}

	int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowText(m_hWnd, lpszStringBuf, nMaxCount);
	}

	int GetWindowTextLength() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowTextLength(m_hWnd);
	}

// Font Functions

	void SetFont(HFONT hFont, BOOL bRedraw = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(bRedraw, 0));
	}

	HFONT GetFont() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0);
	}

// Menu Functions (non-child windows only)

#if !defined(_WIN32_WCE)
	HMENU GetMenu() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetMenu(m_hWnd);
	}

	BOOL SetMenu(HMENU hMenu)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetMenu(m_hWnd, hMenu);
	}
#endif // _WIN32_WCE

	BOOL DrawMenuBar()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::DrawMenuBar(m_hWnd);
	}

#if defined(_WIN32_WCE)
#pragma warning( disable : 4100 )
#undef GetSystemMenu
	HMENU GetSystemMenu(BOOL bRevert) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (HMENU)(m_hWnd);
	}
#pragma warning( default : 4100 )

#else // _WIN32_WCE
	HMENU GetSystemMenu(BOOL bRevert) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetSystemMenu(m_hWnd, bRevert);
	}
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE)
	BOOL HiliteMenuItem(HMENU hMenu, UINT uItemHilite, UINT uHilite)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::HiliteMenuItem(m_hWnd, hMenu, uItemHilite, uHilite);
	}

// Window Size and Position Functions

	BOOL IsIconic() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::IsIconic(m_hWnd);
	}

	BOOL IsZoomed() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::IsZoomed(m_hWnd);
	}
#endif // _WIN32_WCE

	BOOL MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::MoveWindow(m_hWnd, x, y, nWidth, nHeight, bRepaint);
	}

	BOOL MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::MoveWindow(m_hWnd, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
	}

	BOOL SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowPos(m_hWnd, hWndInsertAfter, x, y, cx, cy, nFlags);
	}

	BOOL SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowPos(m_hWnd, hWndInsertAfter, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, nFlags);
	}

#if !defined(_WIN32_WCE)
	UINT ArrangeIconicWindows()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ArrangeIconicWindows(m_hWnd);
	}
#endif // _WIN32_WCE

	BOOL BringWindowToTop()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::BringWindowToTop(m_hWnd);
	}

	BOOL GetWindowRect(LPRECT lpRect) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowRect(m_hWnd, lpRect);
	}

	BOOL GetClientRect(LPRECT lpRect) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetClientRect(m_hWnd, lpRect);
	}

#if !defined(_WIN32_WCE)
	BOOL GetWindowPlacement(WINDOWPLACEMENT FAR* lpwndpl) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowPlacement(m_hWnd, lpwndpl);
	}

	BOOL SetWindowPlacement(const WINDOWPLACEMENT FAR* lpwndpl)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowPlacement(m_hWnd, lpwndpl);
	}
#endif // _WIN32_WCE

// Coordinate Mapping Functions

	BOOL ClientToScreen(LPPOINT lpPoint) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ClientToScreen(m_hWnd, lpPoint);
	}

	BOOL ClientToScreen(LPRECT lpRect) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		if(!::ClientToScreen(m_hWnd, (LPPOINT)lpRect))
			return FALSE;
		return ::ClientToScreen(m_hWnd, ((LPPOINT)lpRect)+1);
	}

	BOOL ScreenToClient(LPPOINT lpPoint) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ScreenToClient(m_hWnd, lpPoint);
	}

	BOOL ScreenToClient(LPRECT lpRect) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		if(!::ScreenToClient(m_hWnd, (LPPOINT)lpRect))
			return FALSE;
		return ::ScreenToClient(m_hWnd, ((LPPOINT)lpRect)+1);
	}

	int MapWindowPoints(HWND hWndTo, LPPOINT lpPoint, UINT nCount) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::MapWindowPoints(m_hWnd, hWndTo, lpPoint, nCount);
	}

	int MapWindowPoints(HWND hWndTo, LPRECT lpRect) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::MapWindowPoints(m_hWnd, hWndTo, (LPPOINT)lpRect, 2);
	}

// Update and Painting Functions

	HDC BeginPaint(LPPAINTSTRUCT lpPaint)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::BeginPaint(m_hWnd, lpPaint);
	}

	void EndPaint(LPPAINTSTRUCT lpPaint)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::EndPaint(m_hWnd, lpPaint);
	}

	HDC GetDC()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetDC(m_hWnd);
	}

	HDC GetWindowDC()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowDC(m_hWnd);
	}

	int ReleaseDC(HDC hDC)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ReleaseDC(m_hWnd, hDC);
	}

#if !defined(_WIN32_WCE)
	void Print(HDC hDC, DWORD dwFlags) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, WM_PRINT, (WPARAM)hDC, dwFlags);
	}

	void PrintClient(HDC hDC, DWORD dwFlags) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, WM_PRINTCLIENT, (WPARAM)hDC, dwFlags);
	}
#endif // _WIN32_WCE

	BOOL UpdateWindow()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::UpdateWindow(m_hWnd);
	}

	void SetRedraw(BOOL bRedraw = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, WM_SETREDRAW, (WPARAM)bRedraw, 0);
	}

	BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetUpdateRect(m_hWnd, lpRect, bErase);
	}

	int GetUpdateRgn(HRGN hRgn, BOOL bErase = FALSE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetUpdateRgn(m_hWnd, hRgn, bErase);
	}

	BOOL Invalidate(BOOL bErase = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::InvalidateRect(m_hWnd, NULL, bErase);
	}

	BOOL InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::InvalidateRect(m_hWnd, lpRect, bErase);
	}

	BOOL ValidateRect(LPCRECT lpRect)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ValidateRect(m_hWnd, lpRect);
	}

#if !defined(_WIN32_WCE)
	void InvalidateRgn(HRGN hRgn, BOOL bErase = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		::InvalidateRgn(m_hWnd, hRgn, bErase);
	}

	BOOL ValidateRgn(HRGN hRgn)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ValidateRgn(m_hWnd, hRgn);
	}
#endif // _WIN32_WCE

	BOOL ShowWindow(int nCmdShow)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ShowWindow(m_hWnd, nCmdShow);
	}

	BOOL IsWindowVisible() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::IsWindowVisible(m_hWnd);
	}

#if defined(_WIN32_WCE_AYGSHELL) && (_WIN32_WCE >= 300)
	void ShowDoneButton(BOOL bShow)
	{
		if(bShow)
		{
			::SHDoneButton(m_hWnd, SHDB_SHOW);
			m_bShowDoneButton = TRUE;
		}
		else
		{
			// The OS will not allow hiding the done button if the taskbar
			// is the foreground window, so make sure that's not the case.
			::SetForegroundWindow(m_hWnd);

			if(::SHDoneButton(m_hWnd, SHDB_HIDE))
			{
				m_bShowDoneButton = FALSE;
			}
		}
	}

	HWND LoadSHMenuBar(LPCTSTR lpszResourceName)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		ATLASSERT(lpszResourceName != NULL);

		// Create the SHMenuBar
		SHMENUBARINFO mbi;
		memset(&mbi, 0, sizeof(SHMENUBARINFO));
		mbi.cbSize     = sizeof(SHMENUBARINFO);
		mbi.hwndParent = m_hWnd;
		mbi.nToolBarId = (int)lpszResourceName;
		mbi.hInstRes   = _Module.GetResourceInstance(); 

		if (!SHCreateMenuBar(&mbi)) 
			return NULL;

		m_hWndCB = mbi.hwndMB;
		return m_hWndCB;
	}
#endif // _WIN32_WCE_AYGSHELL
#if !defined(_WIN32_WCE)
	BOOL ShowOwnedPopups(BOOL bShow = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ShowOwnedPopups(m_hWnd, bShow);
	}
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE) || (_WIN32_WCE >= 210)
	HDC GetDCEx(HRGN hRgnClip, DWORD flags)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetDCEx(m_hWnd, hRgnClip, flags);
	}
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE)
	BOOL LockWindowUpdate(BOOL bLock = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::LockWindowUpdate(bLock ? m_hWnd : NULL);
	}
#endif // _WIN32_WCE

#if defined(_WIN32_WCE)
#pragma warning( disable : 4100 )
#endif

    BOOL RedrawWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
#if defined(_WIN32_WCE)
		Invalidate();
		return(UpdateWindow());
#else // _WIN32_WCE
		return ::RedrawWindow(m_hWnd, lpRectUpdate, hRgnUpdate, flags);
#endif // _WIN32_WCE
	}

#if defined(_WIN32_WCE)
#pragma warning( default : 4100 )
#endif

// Timer Functions

	UINT SetTimer(UINT nIDEvent, UINT nElapse)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetTimer(m_hWnd, nIDEvent, nElapse, NULL);
	}

	BOOL KillTimer(UINT nIDEvent)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::KillTimer(m_hWnd, nIDEvent);
	}

// Window State Functions

	BOOL IsWindowEnabled() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::IsWindowEnabled(m_hWnd);
	}

	BOOL EnableWindow(BOOL bEnable = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::EnableWindow(m_hWnd, bEnable);
	}

	HWND SetActiveWindow()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetActiveWindow(m_hWnd);
	}

	HWND SetCapture()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetCapture(m_hWnd);
	}

	HWND SetFocus()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetFocus(m_hWnd);
	}

// Dialog-Box Item Functions

	BOOL CheckDlgButton(int nIDButton, UINT nCheck)
	{
		ATLASSERT(::IsWindow(m_hWnd));
#if defined(_WIN32_WCE)
		::SendMessage( GetDlgItem(nIDButton), BM_SETCHECK, (WPARAM)nCheck, (LPARAM)0 );
		return TRUE;
#else // _WIN32_WCE
		return ::CheckDlgButton(m_hWnd, nIDButton, nCheck);
#endif // _WIN32_WCE
	}

	BOOL CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::CheckRadioButton(m_hWnd, nIDFirstButton, nIDLastButton, nIDCheckButton);
	}

#if !defined(_WIN32_WCE)
	int DlgDirList(LPTSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT nFileType)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::DlgDirList(m_hWnd, lpPathSpec, nIDListBox, nIDStaticPath, nFileType);
	}

	int DlgDirListComboBox(LPTSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT nFileType)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::DlgDirListComboBox(m_hWnd, lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);
	}

	BOOL DlgDirSelect(LPTSTR lpString, int nCount, int nIDListBox)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::DlgDirSelectEx(m_hWnd, lpString, nCount, nIDListBox);
	}

	BOOL DlgDirSelectComboBox(LPTSTR lpString, int nCount, int nIDComboBox)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::DlgDirSelectComboBoxEx(m_hWnd, lpString, nCount, nIDComboBox);
	}
#endif // _WIN32_WCE

	UINT GetDlgItemInt(int nID, BOOL* lpTrans = NULL, BOOL bSigned = TRUE) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetDlgItemInt(m_hWnd, nID, lpTrans, bSigned);
	}

	UINT GetDlgItemText(int nID, LPTSTR lpStr, int nMaxCount) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
#if defined(_WIN32_WCE)
  		return ::GetWindowText(GetDlgItem(nID), lpStr, nMaxCount);
#else // _WIN32_WCE
		return ::GetDlgItemText(m_hWnd, nID, lpStr, nMaxCount);
#endif // _WIN32_WCE
	}
	BOOL GetDlgItemText(int nID, BSTR& bstrText) const
	{
		ATLASSERT(::IsWindow(m_hWnd));

		HWND hWndCtl = GetDlgItem(nID);
		if(hWndCtl == NULL)
			return FALSE;

		return CWindow(hWndCtl).GetWindowText(bstrText);
	}
	HWND GetNextDlgGroupItem(HWND hWndCtl, BOOL bPrevious = FALSE) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetNextDlgGroupItem(m_hWnd, hWndCtl, bPrevious);
	}

	HWND GetNextDlgTabItem(HWND hWndCtl, BOOL bPrevious = FALSE) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetNextDlgTabItem(m_hWnd, hWndCtl, bPrevious);
	}

	UINT IsDlgButtonChecked(int nIDButton) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
#if defined(_WIN32_WCE)
		return (UINT)::SendMessage( GetDlgItem(nIDButton), BM_GETCHECK, (WPARAM)0, (LPARAM)0 );
#else // _WIN32_WCE
		return ::IsDlgButtonChecked(m_hWnd, nIDButton);
#endif // _WIN32_WCE
	}

	LRESULT SendDlgItemMessage(int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));
#if defined(_WIN32_WCE)
		return (LRESULT)SendMessage(GetDlgItem(nID), message, wParam, lParam);
#else // _WIN32_WCE
		return ::SendDlgItemMessage(m_hWnd, nID, message, wParam, lParam);
#endif // _WIN32_WCE
	}

	BOOL SetDlgItemInt(int nID, UINT nValue, BOOL bSigned = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetDlgItemInt(m_hWnd, nID, nValue, bSigned);
	}

	BOOL SetDlgItemText(int nID, LPCTSTR lpszString)
	{
		ATLASSERT(::IsWindow(m_hWnd));
#if defined(_WIN32_WCE)
		return ::SetWindowText(GetDlgItem(nID),lpszString);
#else // _WIN32_WCE
		return ::SetDlgItemText(m_hWnd, nID, lpszString);
#endif // _WIN32_WCE
	}

#ifndef _ATL_NO_HOSTING
	HRESULT GetDlgControl(int nID, REFIID iid, void** ppUnk)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		ATLASSERT(ppUnk != NULL);
		HRESULT hr = E_FAIL;
		HWND hWndCtrl = GetDlgItem(nID);
		if (hWndCtrl != NULL)
		{
			*ppUnk = NULL;
			CComPtr<IUnknown> spUnk;
			hr = AtlAxGetControl(hWndCtrl, &spUnk);
			if (SUCCEEDED(hr))
				hr = spUnk->QueryInterface(iid, ppUnk);
		}
		return hr;
	}
#endif //!_ATL_NO_HOSTING

// Scrolling Functions

#if defined(_WIN32_WCE)
	int GetScrollPos(int nBar) const
	{
		SCROLLINFO si;
		ATLASSERT(::IsWindow(m_hWnd));
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		if(::GetScrollInfo(m_hWnd, nBar, &si))
			return si.nPos;
		return 0;
	}

	BOOL GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const
	{
		SCROLLINFO si;
		ATLASSERT(::IsWindow(m_hWnd));

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE;
		BOOL bResult = ::GetScrollInfo(m_hWnd, nBar, &si);
		*lpMinPos = si.nMin;
		*lpMaxPos = si.nMax;

		return bResult;
	}
#else // _WIN32_WCE
	int GetScrollPos(int nBar) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetScrollPos(m_hWnd, nBar);
	}

	BOOL GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetScrollRange(m_hWnd, nBar, lpMinPos, lpMaxPos);
	}
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE)
	BOOL ScrollWindow(int xAmount, int yAmount, LPCRECT lpRect = NULL, LPCRECT lpClipRect = NULL)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ScrollWindow(m_hWnd, xAmount, yAmount, lpRect, lpClipRect);
	}
#endif // _WIN32_WCE

	int ScrollWindowEx(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate, UINT uFlags)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ScrollWindowEx(m_hWnd, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
	}

	int ScrollWindowEx(int dx, int dy, UINT uFlags, LPCRECT lpRectScroll = NULL, LPCRECT lpRectClip = NULL, HRGN hRgnUpdate = NULL, LPRECT lpRectUpdate = NULL)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ScrollWindowEx(m_hWnd, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
	}

	int SetScrollPos(int nBar, int nPos, BOOL bRedraw = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetScrollPos(m_hWnd, nBar, nPos, bRedraw);
	}

	BOOL SetScrollRange(int nBar, int nMinPos, int nMaxPos, BOOL bRedraw = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetScrollRange(m_hWnd, nBar, nMinPos, nMaxPos, bRedraw);
	}

#if !defined(_WIN32_WCE)
	BOOL ShowScrollBar(UINT nBar, BOOL bShow = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ShowScrollBar(m_hWnd, nBar, bShow);
	}

	BOOL EnableScrollBar(UINT uSBFlags, UINT uArrowFlags = ESB_ENABLE_BOTH)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::EnableScrollBar(m_hWnd, uSBFlags, uArrowFlags);
	}
#endif // _WIN32_WCE

// Window Access Functions

	HWND ChildWindowFromPoint(POINT point) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ChildWindowFromPoint(m_hWnd, point);
	}

#if !defined(_WIN32_WCE)
	HWND ChildWindowFromPointEx(POINT point, UINT uFlags) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ChildWindowFromPointEx(m_hWnd, point, uFlags);
	}

	HWND GetTopWindow() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetTopWindow(m_hWnd);
	}
#endif // _WIN32_WCE

	HWND GetWindow(UINT nCmd) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindow(m_hWnd, nCmd);
	}

#if !defined(_WIN32_WCE)
	HWND GetLastActivePopup() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetLastActivePopup(m_hWnd);
	}
#endif // _WIN32_WCE

	BOOL IsChild(HWND hWnd) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::IsChild(m_hWnd, hWnd);
	}

	HWND GetParent() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetParent(m_hWnd);
	}

	HWND SetParent(HWND hWndNewParent)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetParent(m_hWnd, hWndNewParent);
	}

// Window Tree Access

	int GetDlgCtrlID() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetDlgCtrlID(m_hWnd);
	}

	int SetDlgCtrlID(int nID)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (int)::SetWindowLong(m_hWnd, GWL_ID, nID);
	}

	HWND GetDlgItem(int nID) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetDlgItem(m_hWnd, nID);
	}

// Alert Functions

#if !defined(_WIN32_WCE)
	BOOL FlashWindow(BOOL bInvert)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::FlashWindow(m_hWnd, bInvert);
	}
#endif // _WIN32_WCE

	int MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption = _T(""), UINT nType = MB_OK)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::MessageBox(m_hWnd, lpszText, lpszCaption, nType);
	}

// Clipboard Functions

#if !defined(_WIN32_WCE)
	BOOL ChangeClipboardChain(HWND hWndNewNext)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ChangeClipboardChain(m_hWnd, hWndNewNext);
	}

	HWND SetClipboardViewer()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetClipboardViewer(m_hWnd);
	}
#endif // _WIN32_WCE

	BOOL OpenClipboard()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::OpenClipboard(m_hWnd);
	}

// Caret Functions

	BOOL CreateCaret(HBITMAP hBitmap)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::CreateCaret(m_hWnd, hBitmap, 0, 0);
	}

	BOOL CreateSolidCaret(int nWidth, int nHeight)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::CreateCaret(m_hWnd, (HBITMAP)0, nWidth, nHeight);
	}

	BOOL CreateGrayCaret(int nWidth, int nHeight)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::CreateCaret(m_hWnd, (HBITMAP)1, nWidth, nHeight);
	}

	BOOL HideCaret()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::HideCaret(m_hWnd);
	}

	BOOL ShowCaret()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ShowCaret(m_hWnd);
	}

#if !defined(_WIN32_WCE)
#ifdef _INC_SHELLAPI
// Drag-Drop Functions
	void DragAcceptFiles(BOOL bAccept = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd)); ::DragAcceptFiles(m_hWnd, bAccept);
	}
#endif
#endif // _WIN32_WCE

// Icon Functions

	HICON SetIcon(HICON hIcon, BOOL bBigIcon = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (HICON)::SendMessage(m_hWnd, WM_SETICON, bBigIcon, (LPARAM)hIcon);
	}

	HICON GetIcon(BOOL bBigIcon = TRUE) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (HICON)::SendMessage(m_hWnd, WM_GETICON, bBigIcon, 0);
	}

#if !defined(_WIN32_WCE)
// Help Functions

	BOOL WinHelp(LPCTSTR lpszHelp, UINT nCmd = HELP_CONTEXT, DWORD dwData = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::WinHelp(m_hWnd, lpszHelp, nCmd, dwData);
	}

	BOOL SetWindowContextHelpId(DWORD dwContextHelpId)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowContextHelpId(m_hWnd, dwContextHelpId);
	}

	DWORD GetWindowContextHelpId() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowContextHelpId(m_hWnd);
	}

// Hot Key Functions

	int SetHotKey(WORD wVirtualKeyCode, WORD wModifiers)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (int)::SendMessage(m_hWnd, WM_SETHOTKEY, MAKEWORD(wVirtualKeyCode, wModifiers), 0);
	}

	DWORD GetHotKey() const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SendMessage(m_hWnd, WM_GETHOTKEY, 0, 0);
	}
#endif // _WIN32_WCE

// Misc. Operations

//N new
	BOOL GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetScrollInfo(m_hWnd, nBar, lpScrollInfo);
	}
	BOOL SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetScrollInfo(m_hWnd, nBar, lpScrollInfo, bRedraw);
	}
	BOOL IsDialogMessage(LPMSG lpMsg)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::IsDialogMessage(m_hWnd, lpMsg);
	}

	void NextDlgCtrl() const
        {
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, WM_NEXTDLGCTL, 0, 0L);
	}
	void PrevDlgCtrl() const
        {
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, WM_NEXTDLGCTL, 1, 0L);
	}
	void GotoDlgCtrl(HWND hWndCtrl) const
        {
		ATLASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, WM_NEXTDLGCTL, (WPARAM)hWndCtrl, 1L);
	}

#if !defined(_WIN32_WCE)
	BOOL ResizeClient(int nWidth, int nHeight, BOOL bRedraw = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));

		RECT rcWnd;
		if(!GetClientRect(&rcWnd))
			return FALSE;

		if(nWidth != -1)
			rcWnd.right = nWidth;
		if(nHeight != -1)
			rcWnd.bottom = nHeight;

		if(!::AdjustWindowRectEx(&rcWnd, GetStyle(), (!(GetStyle() & WS_CHILD) && (GetMenu() != NULL)), GetExStyle()))
			return FALSE;

		UINT uFlags = SWP_NOZORDER | SWP_NOMOVE;
		if(!bRedraw)
			uFlags |= SWP_NOREDRAW;

		return SetWindowPos(NULL, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top, uFlags);
	}
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE) || (_WIN32_WCE >= 300)
	int GetWindowRgn(HRGN hRgn)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowRgn(m_hWnd, hRgn);
	}
	int SetWindowRgn(HRGN hRgn, BOOL bRedraw = FALSE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetWindowRgn(m_hWnd, hRgn, bRedraw);
	}
#endif // _WIN32_WCE

#if !defined(_WIN32_WCE) || (_WIN32_WCE >= 210)
	HDWP DeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::DeferWindowPos(hWinPosInfo, m_hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
	}
#endif // _WIN32_WCE
	DWORD GetWindowThreadID()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowThreadProcessId(m_hWnd, NULL);
	}
	DWORD GetWindowProcessID()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		DWORD dwProcessID;
		::GetWindowThreadProcessId(m_hWnd, &dwProcessID);
		return dwProcessID;
	}
	BOOL IsWindow()
	{
		return ::IsWindow(m_hWnd);
	}
	BOOL IsWindowUnicode()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return WCE_IF(TRUE, ::IsWindowUnicode(m_hWnd));
	}
	BOOL IsParentDialog()
	{
		ATLASSERT(::IsWindow(m_hWnd));
#if defined(_WIN32_WCE)
		TCHAR szBuf[256]; // "Dialog" + NUL character
		GetClassName(GetParent(), szBuf, sizeof(szBuf)/sizeof(TCHAR));
		return lstrcmp(szBuf, _T("Dialog")) == 0;
#else
		TCHAR szBuf[8]; // "#32770" + NUL character
		GetClassName(GetParent(), szBuf, sizeof(szBuf)/sizeof(TCHAR));
		return lstrcmp(szBuf, _T("#32770")) == 0;
#endif // _WIN32_WCE
	}
#if !defined(_WIN32_WCE)
	BOOL ShowWindowAsync(int nCmdShow)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::ShowWindowAsync(m_hWnd, nCmdShow);
	}

	HWND GetDescendantWindow(int nID) const
	{
		ATLASSERT(::IsWindow(m_hWnd));

		// GetDlgItem recursive (return first found)
		// breadth-first for 1 level, then depth-first for next level

		// use GetDlgItem since it is a fast USER function
		HWND hWndChild, hWndTmp;
		CWindow wnd;
		if((hWndChild = ::GetDlgItem(m_hWnd, nID)) != NULL)
		{
			if(::GetTopWindow(hWndChild) != NULL)
			{
				// children with the same ID as their parent have priority
				wnd.Attach(hWndChild);
				hWndTmp = wnd.GetDescendantWindow(nID);
				if(hWndTmp != NULL)
					return hWndTmp;
			}
			return hWndChild;
		}

		// walk each child
		for(hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
			hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
		{
			wnd.Attach(hWndChild);
			hWndTmp = wnd.GetDescendantWindow(nID);
			if(hWndTmp != NULL)
				return hWndTmp;
		}

		return NULL;    // not found
	}

	void SendMessageToDescendants(UINT message, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bDeep = TRUE)
	{
		CWindow wnd;
		for(HWND hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
			hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
		{
			::SendMessage(hWndChild, message, wParam, lParam);

			if(bDeep && ::GetTopWindow(hWndChild) != NULL)
			{
				// send to child windows after parent
				wnd.Attach(hWndChild);
				wnd.SendMessageToDescendants(message, wParam, lParam, bDeep);
			}
		}
	}
#endif // _WIN32_WCE

	BOOL CenterWindow(HWND hWndCenter = NULL)
	{
		ATLASSERT(::IsWindow(m_hWnd));

		// determine owner window to center against
		DWORD dwStyle = GetStyle();
		if(hWndCenter == NULL)
		{
			if(dwStyle & WS_CHILD)
				hWndCenter = ::GetParent(m_hWnd);
			else
				hWndCenter = ::GetWindow(m_hWnd, GW_OWNER);
		}

		// get coordinates of the window relative to its parent
		RECT rcDlg;
		::GetWindowRect(m_hWnd, &rcDlg);
		RECT rcArea;
		RECT rcCenter;
		HWND hWndParent;
		if(!(dwStyle & WS_CHILD))
		{
			// don't center against invisible or minimized windows
			if(hWndCenter != NULL)
			{
				DWORD dwStyle = ::GetWindowLong(hWndCenter, GWL_STYLE);
				if(!(dwStyle & WS_VISIBLE) || (dwStyle & WS_MINIMIZE))
					hWndCenter = NULL;
			}

			// center within screen coordinates
			::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
			if(hWndCenter == NULL)
				rcCenter = rcArea;
			else
				::GetWindowRect(hWndCenter, &rcCenter);
		}
		else
		{
			// center within parent client coordinates
			hWndParent = ::GetParent(m_hWnd);
			ATLASSERT(::IsWindow(hWndParent));

			::GetClientRect(hWndParent, &rcArea);
			ATLASSERT(::IsWindow(hWndCenter));
			::GetClientRect(hWndCenter, &rcCenter);
			::MapWindowPoints(hWndCenter, hWndParent, (POINT*)&rcCenter, 2);
		}

		int DlgWidth = rcDlg.right - rcDlg.left;
		int DlgHeight = rcDlg.bottom - rcDlg.top;

		// find dialog's upper left based on rcCenter
		int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
		int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

		// if the dialog is outside the screen, move it inside
		if(xLeft < rcArea.left)
			xLeft = rcArea.left;
		else if(xLeft + DlgWidth > rcArea.right)
			xLeft = rcArea.right - DlgWidth;

		if(yTop < rcArea.top)
			yTop = rcArea.top;
		else if(yTop + DlgHeight > rcArea.bottom)
			yTop = rcArea.bottom - DlgHeight;

		// map screen coordinates to child coordinates
		return ::SetWindowPos(m_hWnd, NULL, xLeft, yTop, -1, -1,
			SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));

		DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
		DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
		if(dwStyle == dwNewStyle)
			return FALSE;

		::SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);
		if(nFlags != 0)
		{
			::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
				SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
		}

		return TRUE;
	}

	BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));

		DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
		DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
		if(dwStyle == dwNewStyle)
			return FALSE;

		::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewStyle);
		if(nFlags != 0)
		{
			::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
				SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
		}

		return TRUE;
	}

	BOOL GetWindowText(BSTR* pbstrText)
	{
		return GetWindowText(*pbstrText);
	}
	BOOL GetWindowText(BSTR& bstrText)
	{
		USES_CONVERSION;
		ATLASSERT(::IsWindow(m_hWnd));
		if (bstrText != NULL)
		{
			SysFreeString(bstrText);
			bstrText = NULL;
		}

		int nLen = ::GetWindowTextLength(m_hWnd);
		if(nLen == 0)
		{
			bstrText = ::SysAllocString(OLESTR(""));
			return (bstrText != NULL) ? TRUE : FALSE;
		}

		LPTSTR lpszText = (LPTSTR)_alloca((nLen+1)*sizeof(TCHAR));

		if(!::GetWindowText(m_hWnd, lpszText, nLen+1))
			return FALSE;

		bstrText = ::SysAllocString(T2OLE(lpszText));
		return (bstrText != NULL) ? TRUE : FALSE;
	}
	HWND GetTopLevelParent() const
	{
		ATLASSERT(::IsWindow(m_hWnd));

		HWND hWndParent = m_hWnd;
		HWND hWndTmp;
		while((hWndTmp = ::GetParent(hWndParent)) != NULL)
			hWndParent = hWndTmp;

		return hWndParent;
	}

	HWND GetTopLevelWindow() const
	{
		ATLASSERT(::IsWindow(m_hWnd));

		HWND hWndParent;
		HWND hWndTmp = m_hWnd;

		do
		{
			hWndParent = hWndTmp;
			hWndTmp = (::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) ? ::GetParent(hWndParent) : ::GetWindow(hWndParent, GW_OWNER);
		}
		while(hWndTmp != NULL);

		return hWndParent;
	}
};

_declspec(selectany) RECT CWindow::rcDefault = { CW_USEDEFAULT, CW_USEDEFAULT, 0, 0 };

/////////////////////////////////////////////////////////////////////////////
// CAxWindow - client side for an ActiveX host window

#ifndef _ATL_NO_HOSTING

template <class TBase /* = CWindow */>
class CAxWindowT : public TBase
{
public:
// Constructors
	CAxWindowT(HWND hWnd = NULL) : TBase(hWnd)
	{ }

	CAxWindowT< TBase >& operator=(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

// Attributes
	static LPCTSTR GetWndClassName()
	{
		return _T("AtlAxWin");
	}

// Operations
	HWND Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		return CWindow::Create(GetWndClassName(), hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
	}
	HWND Create(HWND hWndParent, LPRECT lpRect = NULL, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			HMENU hMenu = NULL, LPVOID lpCreateParam = NULL)
	{
		return CWindow::Create(GetWndClassName(), hWndParent, lpRect, szWindowName, dwStyle, dwExStyle, hMenu, lpCreateParam);
	}

	HRESULT CreateControl(LPCOLESTR lpszName, IStream* pStream = NULL, IUnknown** ppUnkContainer = NULL)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return AtlAxCreateControl(lpszName, m_hWnd, pStream, ppUnkContainer);
	}

	HRESULT CreateControl(DWORD dwResID, IStream* pStream = NULL, IUnknown** ppUnkContainer = NULL)
	{
		TCHAR szModule[_MAX_PATH];
		GetModuleFileName(_Module.GetModuleInstance(), szModule, _MAX_PATH);

		CComBSTR bstrURL(OLESTR("res://"));
		bstrURL.Append(szModule);
		bstrURL.Append(OLESTR("/"));
		TCHAR szResID[11];
		wsprintf(szResID, _T("%0d"), dwResID);
		bstrURL.Append(szResID);

		ATLASSERT(::IsWindow(m_hWnd));
		return AtlAxCreateControl(bstrURL, m_hWnd, pStream, ppUnkContainer);
	}

	HRESULT CreateControlEx(LPCOLESTR lpszName, IStream* pStream = NULL, 
			IUnknown** ppUnkContainer = NULL, IUnknown** ppUnkControl = NULL,
			REFIID iidSink = IID_NULL, IUnknown* punkSink = NULL)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return AtlAxCreateControlEx(lpszName, m_hWnd, pStream, ppUnkContainer, ppUnkControl, iidSink, punkSink);
	}

	HRESULT CreateControlEx(DWORD dwResID,  IStream* pStream = NULL, 
			IUnknown** ppUnkContainer = NULL, IUnknown** ppUnkControl = NULL,
			REFIID iidSink = IID_NULL, IUnknown* punkSink = NULL)
	{
		TCHAR szModule[_MAX_PATH];
		GetModuleFileName(_Module.GetModuleInstance(), szModule, _MAX_PATH);

		CComBSTR bstrURL(OLESTR("res://"));
		bstrURL.Append(szModule);
		bstrURL.Append(OLESTR("/"));
		TCHAR szResID[11];
		wsprintf(szResID, _T("%0d"), dwResID);
		bstrURL.Append(szResID);

		ATLASSERT(::IsWindow(m_hWnd));
		return AtlAxCreateControlEx(bstrURL, m_hWnd, pStream, ppUnkContainer, ppUnkControl, iidSink, punkSink);
	}

	HRESULT AttachControl(IUnknown* pControl, IUnknown** ppUnkContainer)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return AtlAxAttachControl(pControl, m_hWnd, ppUnkContainer);
	}
	HRESULT QueryHost(REFIID iid, void** ppUnk)
	{
		ATLASSERT(ppUnk != NULL);
		HRESULT hr;
		*ppUnk = NULL;
		CComPtr<IUnknown> spUnk;
		hr = AtlAxGetHost(m_hWnd, &spUnk);
		if (SUCCEEDED(hr))
			hr = spUnk->QueryInterface(iid, ppUnk);
		return hr;
	}
	template <class Q>
	HRESULT QueryHost(Q** ppUnk)
	{
		return QueryHost(__uuidof(Q), (void**)ppUnk);
	}
	HRESULT QueryControl(REFIID iid, void** ppUnk)
	{
		ATLASSERT(ppUnk != NULL);
		HRESULT hr;
		*ppUnk = NULL;
		CComPtr<IUnknown> spUnk;
		hr = AtlAxGetControl(m_hWnd, &spUnk);
		if (SUCCEEDED(hr))
			hr = spUnk->QueryInterface(iid, ppUnk);
		return hr;
	}
	template <class Q>
	HRESULT QueryControl(Q** ppUnk)
	{
		return QueryControl(__uuidof(Q), (void**)ppUnk);
	}
	HRESULT SetExternalDispatch(IDispatch* pDisp)
	{
		HRESULT hr;
		CComPtr<IAxWinHostWindow> spHost;
		hr = QueryHost(IID_IAxWinHostWindow, (void**)&spHost);
		if (SUCCEEDED(hr))
			hr = spHost->SetExternalDispatch(pDisp);
		return hr;
	}
#if !defined(_WIN32_WCE) || (_WIN32_WCE >= 300)
	HRESULT SetExternalUIHandler(IDocHostUIHandlerDispatch* pUIHandler)
	{
		HRESULT hr;
		CComPtr<IAxWinHostWindow> spHost;
		hr = QueryHost(IID_IAxWinHostWindow, (void**)&spHost);
		if (SUCCEEDED(hr))
			hr = spHost->SetExternalUIHandler(pUIHandler);
		return hr;
	}
#endif // _WIN32_WCE
};

typedef CAxWindowT<CWindow> CAxWindow;

#endif //_ATL_NO_HOSTING

/////////////////////////////////////////////////////////////////////////////
// WindowProc thunks

#if defined(_WIN32_WCE)
#if defined(_WIN32_WCE_CEPC) || defined(_WIN32_WCE_EMULATION) || defined(_M_IX86)
	#pragma pack(push,1)
#else
	#pragma pack(push,4)
#endif
struct _WndProcThunk
{
#if defined(_WIN32_WCE_CEPC) || defined(_WIN32_WCE_EMULATION) || defined(_M_IX86)
	DWORD   m_mov;          // mov ecx, pThis
	DWORD   m_this;         //
	BYTE    m_movedx; 		//mov edx, proc
	DWORD   m_proc;
	WORD    m_jmp;          // jmp edx
#elif defined(_MIPS_) || defined(_MIPS16_)
	WORD	m_pFuncHi;
	WORD	m_lui_t0;		// lui		t0,PFUNC_HIGH
	WORD	m_pFuncLo;
	WORD	m_ori_t0;		// ori		t0,t0,PFUNC_LOW
	WORD	m_pThisHi;
	WORD	m_lui_a0;		// lui		a0,PTHIS_HIGH
	DWORD	m_jr_t0;		// jr		t0
	WORD	m_pThisLo;
	WORD	m_ori_a0;		// ori		a0,PTHIS_LOW
#elif defined(_SHX_) || defined(_SH3_) || defined(_SH4_)
	WORD	m_mov_r0;		// mov.l	pFunc,r0
	WORD	m_mov_r1;		// mov.l	pThis,r1
	WORD	m_jmp;			// jmp		@r0
	WORD	m_nop;			// nop
	DWORD	m_pFunc;
	DWORD	m_pThis;
#elif defined(_ARM_) && defined(_M_THUMB)
	WORD	m_ldr_r0_3;		// ldr r0,  [pc, 3 * 4] (pFunc)
	WORD	m_mov_r12_r0;	// mov r12, r0
	WORD	m_ldr_r0_1;		// ldr r0,  [pc, 1 * 4] (pThis)
	WORD 	m_bx_r12;   	// mov pc, r12 (OR bx 12)
	DWORD	dwDummy;
	DWORD	m_pThis;
	DWORD	m_pFunc;
#elif defined(_ARM_) && defined(_M_ARMT)
	DWORD   m_ldr_r0;		// ldr r0,	[pc, 4]
	DWORD   m_ldr_r12;		// ldr r12,	[pc, 4]
	DWORD   m_bx_r12;	    // bx  r12
	DWORD	m_pThis;
	DWORD	m_pFunc;
#elif defined(_ARM_) 
	DWORD   m_ldr_r0;		// ldr r0,	[pc, 4]
	DWORD   m_ldr_r12;		// ldr r12,	[pc, 4]
	DWORD   m_mov_pc_r12;	// mov pc,	r12
	DWORD	m_pThis;
	DWORD	m_pFunc;
#elif defined(_M_PPC)
	DWORD	lis_r12;        // lis  r12, HIWORD(func)
	DWORD	ori_r12;        // ori  r12, r12, LOWORD(func)(r12)
	DWORD	lis_r3;         // lis  r3, HIWORD(this)
	DWORD	mtctr_r12;      // mtctr r12
	DWORD	ori_r3;         // ori  r3, r3, LOWORD(this)
	DWORD	bctr;           // bctr
#elif defined(_WIN32_WCE_CEF)
	// Use helper__CreateAtlceThunk and helper__DeleteAtlceThunk in CEFRTL.DLL
#else
	#error No _WndProcThunk implementation found for this CPU.
#endif
};
#pragma pack(pop)
#else // _WIN32_WCE
#if defined(_M_IX86)	// DESKTOP ATL IMPLEMENTATION--DO NOT MODIFY
#pragma pack(push,1)
struct _WndProcThunk
{
	DWORD   m_mov;          // mov dword ptr [esp+0x4], pThis (esp+0x4 is hWnd)
	DWORD   m_this;         //
	BYTE    m_jmp;          // jmp WndProc
	DWORD   m_relproc;      // relative jmp
};
#pragma pack(pop)
#elif defined (_M_ALPHA)	// DESKTOP ATL IMPLEMENTATION--DO NOT MODIFY
// For ALPHA we will stick the this pointer into a0, which is where
// the HWND is.  However, we don't actually need the HWND so this is OK.
#pragma pack(push,4)
struct _WndProcThunk //this should come out to 20 bytes
{
	DWORD ldah_at;      //  ldah    at, HIWORD(func)
	DWORD ldah_a0;      //  ldah    a0, HIWORD(this)
	DWORD lda_at;       //  lda     at, LOWORD(func)(at)
	DWORD lda_a0;       //  lda     a0, LOWORD(this)(a0)
	DWORD jmp;          //  jmp     zero,(at),0
};
#pragma pack(pop)
#else
#error Only Alpha and X86 supported
#endif
#endif // _WIN32_WCE

#if defined(_WIN32_WCE_CEF)
class CWndProcThunk
{
public:
	_AtlCreateWndData cd;
	DWORD dwThunkHandle;
	CWndProcThunk() : dwThunkHandle(NULL) { }
	void Init(HWND hWnd, WNDPROC newProc, void* pThis, BOOL bDlgProc, WNDPROC* pThunkProc, WNDPROC* pOldProc)
	{
		dwThunkHandle = helper__CreateAtlceThunk(hWnd, newProc, pThis, bDlgProc, pThunkProc, pOldProc);
		ATLASSERT(dwThunkHandle != NULL);
	}
	void Cleanup()
	{
		if(dwThunkHandle != NULL)
		{
			helper__DeleteAtlceThunk(dwThunkHandle);
			dwThunkHandle = NULL;
		}
	}
	~CWndProcThunk()
		{ Cleanup(); } // fallback call
};
#elif defined(_WIN32_WCE)

#if ( _WIN32_WCE < 420 )

//
// CeZeroPointer support exists only on 420 and greater.  Supply implementation  
// for CE versions less than 420 and only if ZeroPtrABS is not defined (pkfuncs.h).
//

#if !defined(ZeroPtrABS)

#define SECTION_SHIFT 25     // Must be in sync with VA_SECTION in kapi.h, mem_*.h
// secure section related defs
#define SECURE_SECTION      0x61    // VM at 0xC2XXXXXX
#define SECURE_VMBASE       (SECURE_SECTION << SECTION_SHIFT)
#define IsSecureVa(va)      (SECURE_SECTION == ((DWORD) (va) >> SECTION_SHIFT))

#define MAX_PROCESSES 32
#define RESERVED_SECTIONS 1     // reserve section 0 for current process

#define FIRST_MAPPER_ADDRESS ((MAX_PROCESSES+RESERVED_SECTIONS) << SECTION_SHIFT)
#define LAST_MAPPER_ADDRESS 0x7E000000

#define ZeroPtrABS(P) ((((DWORD)(P) & 0x80000000) && !IsSecureVa(P)) ? \
    (DWORD)(P) : ((DWORD)(P) & ((1<<SECTION_SHIFT)-1)))

#define CeZeroPointer(P)  ((((DWORD)(P) < (2<<SECTION_SHIFT)) || ((int) (P) >= FIRST_MAPPER_ADDRESS)) ? \
    (DWORD) (P) : ZeroPtrABS(P))

#endif  // #if !defined(ZeroPtrABS)

#endif // #if ( _WIN32_WCE < 420 )


class CWndProcThunk
{
public:
	union
	{
		_AtlCreateWndData cd;
		_WndProcThunk thunk;
	};
	void Init(WNDPROC proc, void* pThis)
	{
		proc = (WNDPROC)CeZeroPointer((LPVOID)proc);
#if defined(_WIN32_WCE_CEPC) || defined(_WIN32_WCE_EMULATION) || defined(_M_IX86)
		thunk.m_mov  = 0x042444C7;
		thunk.m_this = (DWORD)pThis;
		thunk.m_movedx = 0xba;      //mov edx, proc
		thunk.m_proc = (DWORD)proc;
		thunk.m_jmp  = 0xe2ff;      //jmp edx
#elif defined(_MIPS_) || defined(_MIPS16_)
		thunk.m_pFuncHi = HIWORD(proc);
		thunk.m_lui_t0  = 0x3c08;
		thunk.m_pFuncLo = LOWORD(proc);
		thunk.m_ori_t0  = 0x3508;
		thunk.m_pThisHi = HIWORD(pThis);
		thunk.m_lui_a0  = 0x3c04;
		thunk.m_jr_t0   = 0x01000008;
		thunk.m_pThisLo = LOWORD(pThis);
		thunk.m_ori_a0  = 0x3484;
#elif defined(_SHX_) || defined(_SH3_) || defined(_SH4_)
		thunk.m_mov_r0 = 0xd001;
		thunk.m_mov_r1 = 0xd402;
		thunk.m_jmp    = 0x402b;
		thunk.m_nop    = 0x0009;
		thunk.m_pFunc  = (DWORD)proc;
		thunk.m_pThis  = (DWORD)pThis;
#elif defined(_ARM_) && defined(_M_THUMB)
		thunk.m_ldr_r0_3     = 0x4803;	// ldr r0,  [pc, 3 * 4] (pFunc)
		thunk.m_mov_r12_r0 = 0x4684;		// mov r12, r0
		thunk.m_ldr_r0_1     = 0x4801;	// ldr r0,  [pc, 1 * 4] (pThis)
		thunk.m_bx_r12     = 0x4760;   	// bx  r12	// correctly branch to 16 or 32 bit code
		thunk.dwDummy = 0;
		thunk.m_pThis = (DWORD)pThis;
		thunk.m_pFunc = (DWORD)proc;
#elif defined(_ARM_) && defined(_M_ARMT)		
		thunk.m_ldr_r0  = 0xE59F0004;  // ldr R0, [PC, 4] (pThis)
		thunk.m_ldr_r12 = 0xE59FC004;  // ldr R12, [PC, 4] (proc)
		thunk.m_bx_r12  = 0xe12fff1c;  // bx   r12
		thunk.m_pThis   = (DWORD)pThis;
		thunk.m_pFunc   = (DWORD)proc;
#elif defined(_ARM_)
		thunk.m_ldr_r0     = 0xE59F0004;  // ldr R0, [PC, 4] (pThis)
		thunk.m_ldr_r12    = 0xE59FC004;  // ldr R12, [PC, 4] (proc)
		thunk.m_mov_pc_r12 = 0xe1a0f00C;  // mov PC, R12
		thunk.m_pThis      = (DWORD)pThis;
		thunk.m_pFunc      = (DWORD)proc;
#elif defined(_PPC_)
		thunk.lis_r12   = 0x3d800000 | HIWORD(proc);
		thunk.ori_r12   = 0x618C0000 | LOWORD(proc);
		thunk.lis_r3    = 0x3c600000 | HIWORD(pThis);
		thunk.mtctr_r12 = 0x7d8903a6;
		thunk.ori_r3    = 0x60630000 | LOWORD(pThis);
		thunk.bctr      = 0x4e800420;
#else
		#error No thunk initialization found for this CPU
#endif
		FlushInstructionCache(GetCurrentProcess(), &thunk, sizeof(thunk));
	}
};
#else // _WIN32_WCE
class CWndProcThunk
{
public:
	union
	{
		_AtlCreateWndData cd;
		_WndProcThunk thunk;
	};
	void Init(WNDPROC proc, void* pThis)
	{
#if defined (_M_IX86)		// DESKTOP ATL IMPLEMENTATION--DO NOT MODIFY
		thunk.m_mov = 0x042444C7;  //C7 44 24 0C
		thunk.m_this = (DWORD)pThis;
		thunk.m_jmp = 0xe9;
		thunk.m_relproc = (int)proc - ((int)this+sizeof(_WndProcThunk));
#elif defined (_M_ALPHA)	// DESKTOP ATL IMPLEMENTATION--DO NOT MODIFY
		thunk.ldah_at = (0x279f0000 | HIWORD(proc)) + (LOWORD(proc)>>15);
		thunk.ldah_a0 = (0x261f0000 | HIWORD(pThis)) + (LOWORD(pThis)>>15);
		thunk.lda_at = 0x239c0000 | LOWORD(proc);
		thunk.lda_a0 = 0x22100000 | LOWORD(pThis);
		thunk.jmp = 0x6bfc0000;
#endif
		// write block from data cache and
		//  flush from instruction cache
		FlushInstructionCache(GetCurrentProcess(), &thunk, sizeof(thunk));
	}
};
#endif //_WIN32_WCE

/////////////////////////////////////////////////////////////////////////////
// CMessageMap - abstract class that provides an interface for message maps

class ATL_NO_VTABLE CMessageMap
{
public:
	virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
		LRESULT& lResult, DWORD dwMsgMapID) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Message map

#define BEGIN_MSG_MAP(theClass) \
public: \
	BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) \
	{ \
		BOOL bHandled = TRUE; \
		hWnd; \
		uMsg; \
		wParam; \
		lParam; \
		lResult; \
		bHandled; \
		switch(dwMsgMapID) \
		{ \
		case 0:

#define ALT_MSG_MAP(msgMapID) \
		break; \
		case msgMapID:

#define MESSAGE_HANDLER(msg, func) \
	if(uMsg == msg) \
	{ \
		bHandled = TRUE; \
		lResult = func(uMsg, wParam, lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define MESSAGE_RANGE_HANDLER(msgFirst, msgLast, func) \
	if(uMsg >= msgFirst && uMsg <= msgLast) \
	{ \
		bHandled = TRUE; \
		lResult = func(uMsg, wParam, lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_HANDLER(id, code, func) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam)) \
	{ \
		bHandled = TRUE; \
		lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_ID_HANDLER(id, func) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam)) \
	{ \
		bHandled = TRUE; \
		lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_CODE_HANDLER(code, func) \
	if(uMsg == WM_COMMAND && code == HIWORD(wParam)) \
	{ \
		bHandled = TRUE; \
		lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_RANGE_HANDLER(idFirst, idLast, func) \
	if(uMsg == WM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
	{ \
		bHandled = TRUE; \
		lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_HANDLER(id, cd, func) \
	if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom && cd == ((LPNMHDR)lParam)->code) \
	{ \
		bHandled = TRUE; \
		lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_ID_HANDLER(id, func) \
	if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom) \
	{ \
		bHandled = TRUE; \
		lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_CODE_HANDLER(cd, func) \
	if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code) \
	{ \
		bHandled = TRUE; \
		lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_RANGE_HANDLER(idFirst, idLast, func) \
	if(uMsg == WM_NOTIFY && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
	{ \
		bHandled = TRUE; \
		lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define CHAIN_MSG_MAP(theChainClass) \
	{ \
		if(theChainClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
			return TRUE; \
	}

#define CHAIN_MSG_MAP_MEMBER(theChainMember) \
	{ \
		if(theChainMember.ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
			return TRUE; \
	}

#define CHAIN_MSG_MAP_ALT(theChainClass, msgMapID) \
	{ \
		if(theChainClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID)) \
			return TRUE; \
	}

#define CHAIN_MSG_MAP_ALT_MEMBER(theChainMember, msgMapID) \
	{ \
		if(theChainMember.ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID)) \
			return TRUE; \
	}

#define CHAIN_MSG_MAP_DYNAMIC(dynaChainID) \
	{ \
		if(CDynamicChain::CallChain(dynaChainID, hWnd, uMsg, wParam, lParam, lResult)) \
			return TRUE; \
	}

#define END_MSG_MAP() \
			break; \
		default: \
			ATLTRACE2(atlTraceWindowing, 0, _T("Invalid message map ID (%i)\n"), dwMsgMapID); \
			ATLASSERT(FALSE); \
			break; \
		} \
		return FALSE; \
	}


// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);


// Empty message map macro

#define DECLARE_EMPTY_MSG_MAP() \
public: \
	BOOL ProcessWindowMessage(HWND, UINT, WPARAM, LPARAM, LRESULT&, DWORD) \
	{ \
		return FALSE; \
	}

// Message reflection macros

#define REFLECT_NOTIFICATIONS() \
	{ \
		bHandled = TRUE; \
		lResult = ReflectNotifications(uMsg, wParam, lParam, bHandled); \
		if(bHandled) \
			return TRUE; \
	}

#define DEFAULT_REFLECTION_HANDLER() \
	if(DefaultReflectionHandler(hWnd, uMsg, wParam, lParam, lResult)) \
		return TRUE;

/////////////////////////////////////////////////////////////////////////////
// CDynamicChain - provides support for dynamic chaining

class CDynamicChain
{
public:
	struct ATL_CHAIN_ENTRY
	{
		DWORD m_dwChainID;
		CMessageMap* m_pObject;
		DWORD m_dwMsgMapID;
	};

	CSimpleArray<ATL_CHAIN_ENTRY*> m_aChainEntry;

	CDynamicChain()
	{ }

	~CDynamicChain()
	{
		for(int i = 0; i < m_aChainEntry.GetSize(); i++)
		{
			if(m_aChainEntry[i] != NULL)
				delete m_aChainEntry[i];
		}
	}

	BOOL SetChainEntry(DWORD dwChainID, CMessageMap* pObject, DWORD dwMsgMapID = 0)
	{
	// first search for an existing entry

		for(int i = 0; i < m_aChainEntry.GetSize(); i++)
		{
			if(m_aChainEntry[i] != NULL && m_aChainEntry[i]->m_dwChainID == dwChainID)
			{
				m_aChainEntry[i]->m_pObject = pObject;
				m_aChainEntry[i]->m_dwMsgMapID = dwMsgMapID;
				return TRUE;
			}
		}

	// create a new one

		ATL_CHAIN_ENTRY* pEntry = NULL;
		ATLTRY(pEntry = new ATL_CHAIN_ENTRY);

		if(pEntry == NULL)
			return FALSE;

		pEntry->m_dwChainID = dwChainID;
		pEntry->m_pObject = pObject;
		pEntry->m_dwMsgMapID = dwMsgMapID;

	// search for an empty one

		for(i = 0; i < m_aChainEntry.GetSize(); i++)
		{
			if(m_aChainEntry[i] == NULL)
			{
				m_aChainEntry[i] = pEntry;
				return TRUE;
			}
		}

	// add a new one

		BOOL bRet = m_aChainEntry.Add(pEntry);

		if(!bRet)
		{
			delete pEntry;
			return FALSE;
		}

		return TRUE;
	}

	BOOL RemoveChainEntry(DWORD dwChainID)
	{
		for(int i = 0; i < m_aChainEntry.GetSize(); i++)
		{
			if(m_aChainEntry[i] != NULL && m_aChainEntry[i]->m_dwChainID == dwChainID)
			{
				delete m_aChainEntry[i];
				m_aChainEntry[i] = NULL;
				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL CallChain(DWORD dwChainID, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		for(int i = 0; i < m_aChainEntry.GetSize(); i++)
		{
			if(m_aChainEntry[i] != NULL && m_aChainEntry[i]->m_dwChainID == dwChainID)
				return (m_aChainEntry[i]->m_pObject)->ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, m_aChainEntry[i]->m_dwMsgMapID);
		}

		return FALSE;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CWndClassInfo - Manages Windows class information
#if defined(_WIN32_WCE)
#define DECLARE_WND_CLASS(WndClassName) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ CS_HREDRAW|CS_VREDRAW, StartWindowProc, \
		  0, 0, 0, 0, 0, (HBRUSH)(COLOR_WINDOW+1), 0, WndClassName }, \
		NULL, NULL, NULL, TRUE, 0, _T("") \
	}; \
	return wc; \
}

#define DECLARE_WND_SUPERCLASS(WndClassName, OrigWndClassName) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ NULL, StartWindowProc, \
		  0, 0, 0, 0, 0, NULL, 0, WndClassName }, \
		OrigWndClassName, NULL, NULL, TRUE, 0, _T("") \
	}; \
	return wc; \
}
#else // _WIN32_WCE
#define DECLARE_WND_CLASS(WndClassName) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, StartWindowProc, \
		  0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, WndClassName, NULL }, \
		NULL, NULL, IDC_ARROW, TRUE, 0, _T("") \
	}; \
	return wc; \
}

#define DECLARE_WND_CLASS_EX(WndClassName, style, bkgnd) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ sizeof(WNDCLASSEX), style, StartWindowProc, \
		  0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd + 1), NULL, WndClassName, NULL }, \
		NULL, NULL, IDC_ARROW, TRUE, 0, _T("") \
	}; \
	return wc; \
}

#define DECLARE_WND_SUPERCLASS(WndClassName, OrigWndClassName) \
static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
	{ \
		{ sizeof(WNDCLASSEX), 0, StartWindowProc, \
		  0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL }, \
		OrigWndClassName, NULL, NULL, TRUE, 0, _T("") \
	}; \
	return wc; \
}
#endif //_WIN32_WCE

/////////////////////////////////////////////////////////////////////////////
// CWinTraits - Defines various default values for a window

template <DWORD t_dwStyle  = 0 , DWORD t_dwExStyle  = 0 >
class CWinTraits
{
public:
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return dwStyle == 0 ? t_dwStyle : dwStyle;
	}
	static DWORD GetWndExStyle(DWORD dwExStyle)
	{
		return dwExStyle == 0 ? t_dwExStyle : dwExStyle;
	}
};

typedef CWinTraits<WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0>					CControlWinTraits;
typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE>		CFrameWinTraits;
typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_MDICHILD>	CMDIChildWinTraits;

typedef CWinTraits<0, 0> CNullTraits;

template <DWORD t_dwStyle = 0, DWORD t_dwExStyle = 0, class TWinTraits = CControlWinTraits>
class CWinTraitsOR
{
public:
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return dwStyle | t_dwStyle | TWinTraits::GetWndStyle(dwStyle);
	}
	static DWORD GetWndExStyle(DWORD dwExStyle)
	{
		return dwExStyle | t_dwExStyle | TWinTraits::GetWndExStyle(dwExStyle);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CWindowImpl - Implements a window

template <class TBase = CWindow>
class ATL_NO_VTABLE CWindowImplRoot : public TBase, public CMessageMap
{
public:
	CWndProcThunk m_thunk;
	const MSG* m_pCurrentMsg;

// Constructor/destructor
	CWindowImplRoot() : m_pCurrentMsg(NULL)
	{ }

	~CWindowImplRoot()
	{
#ifdef _DEBUG
		if(m_hWnd != NULL)	// should be cleared in WindowProc
		{
			ATLTRACE2(atlTraceWindowing, 0, _T("ERROR - Object deleted before window was destroyed\n"));
			ATLASSERT(FALSE);
		}
#endif //_DEBUG
	}

// Current message
	const MSG* GetCurrentMessage() const
	{
		return m_pCurrentMsg;
	}

// Message reflection support
	LRESULT ReflectNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static BOOL DefaultReflectionHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
};

template <class TBase>
LRESULT CWindowImplRoot< TBase >::ReflectNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hWndChild = NULL;

	switch(uMsg)
	{
	case WM_COMMAND:
		if(lParam != NULL)	// not from a menu
			hWndChild = (HWND)lParam;
		break;
	case WM_NOTIFY:
		hWndChild = ((LPNMHDR)lParam)->hwndFrom;
		break;
#if !defined(_WIN32_WCE)
	case WM_PARENTNOTIFY:
		switch(LOWORD(wParam))
		{
		case WM_CREATE:
		case WM_DESTROY:
			hWndChild = (HWND)lParam;
			break;
		default:
			hWndChild = GetDlgItem(HIWORD(wParam));
			break;
		}
		break;
#endif // _WIN32_WCE
	case WM_DRAWITEM:
		if(wParam)	// not from a menu
			hWndChild = ((LPDRAWITEMSTRUCT)lParam)->hwndItem;
		break;
	case WM_MEASUREITEM:
		if(wParam)	// not from a menu
			hWndChild = GetDlgItem(((LPMEASUREITEMSTRUCT)lParam)->CtlID);
		break;
	case WM_COMPAREITEM:
		if(wParam)	// not from a menu
			hWndChild = GetDlgItem(((LPCOMPAREITEMSTRUCT)lParam)->CtlID);
		break;
	case WM_DELETEITEM:
		if(wParam)	// not from a menu
			hWndChild = GetDlgItem(((LPDELETEITEMSTRUCT)lParam)->CtlID);
		break;
	case WM_VKEYTOITEM:
	case WM_CHARTOITEM:
	case WM_HSCROLL:
	case WM_VSCROLL:
		hWndChild = (HWND)lParam;
		break;
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
		hWndChild = (HWND)lParam;
		break;
	default:
		break;
	}

	if(hWndChild == NULL)
	{
		bHandled = FALSE;
		return 1;
	}

	ATLASSERT(::IsWindow(hWndChild));
	return ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
}

template <class TBase>
BOOL CWindowImplRoot< TBase >::DefaultReflectionHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	switch(uMsg)
	{
	case OCM_COMMAND:
	case OCM_NOTIFY:
#if !defined(_WIN32_WCE)
	case OCM_PARENTNOTIFY:
#endif // _WIN32_WCE
	case OCM_DRAWITEM:
	case OCM_MEASUREITEM:
	case OCM_COMPAREITEM:
	case OCM_DELETEITEM:
	case OCM_VKEYTOITEM:
	case OCM_CHARTOITEM:
	case OCM_HSCROLL:
	case OCM_VSCROLL:
	case OCM_CTLCOLORBTN:
	case OCM_CTLCOLORDLG:
	case OCM_CTLCOLOREDIT:
	case OCM_CTLCOLORLISTBOX:
	case OCM_CTLCOLORMSGBOX:
	case OCM_CTLCOLORSCROLLBAR:
	case OCM_CTLCOLORSTATIC:
		lResult = ::DefWindowProc(hWnd, uMsg - OCM__BASE, wParam, lParam);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

template <class TBase = CWindow, class TWinTraits = CControlWinTraits>
class ATL_NO_VTABLE CWindowImplBaseT : public CWindowImplRoot< TBase >
{
public:
	WNDPROC m_pfnSuperWindowProc;

	CWindowImplBaseT() : m_pfnSuperWindowProc(::DefWindowProc)
	{}

	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return TWinTraits::GetWndStyle(dwStyle);
	}
	static DWORD GetWndExStyle(DWORD dwExStyle)
	{
		return TWinTraits::GetWndExStyle(dwExStyle);
	}

	virtual WNDPROC GetWindowProc()
	{
		return WindowProc;
	}
	static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName,
			DWORD dwStyle, DWORD dwExStyle, UINT nID, ATOM atom, LPVOID lpCreateParam = NULL);
	BOOL DestroyWindow()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::DestroyWindow(m_hWnd);
	}
	BOOL SubclassWindow(HWND hWnd);
	HWND UnsubclassWindow(BOOL bForce = FALSE);

	LRESULT DefWindowProc()
	{
		const MSG* pMsg = m_pCurrentMsg;
		LRESULT lRes = 0;
		if (pMsg != NULL)
			lRes = DefWindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
		return lRes;
	}

	LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
#ifdef STRICT
		return ::CallWindowProc(m_pfnSuperWindowProc, m_hWnd, uMsg, wParam, lParam);
#else
		return ::CallWindowProc((FARPROC)m_pfnSuperWindowProc, m_hWnd, uMsg, wParam, lParam);
#endif
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		// override to do something, if needed
	}
};

typedef CWindowImplBaseT<CWindow>	CWindowImplBase;

template <class TBase, class TWinTraits>
LRESULT CALLBACK CWindowImplBaseT< TBase, TWinTraits >::StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindowImplBaseT< TBase, TWinTraits >* pThis = (CWindowImplBaseT< TBase, TWinTraits >*)_Module.ExtractCreateWndData();
	ATLASSERT(pThis != NULL);
	pThis->m_hWnd = hWnd;
#if defined(_WIN32_WCE_CEF)
	WNDPROC pProc, pOldProc;
	pThis->m_thunk.Init(hWnd, pThis->GetWindowProc(), pThis, FALSE, &pProc, &pOldProc);
#else // _WIN32_WCE_CEF
	pThis->m_thunk.Init(pThis->GetWindowProc(), pThis);
	WNDPROC pProc = (WNDPROC)&(pThis->m_thunk.thunk);
#if defined(_WIN32_WCE) && defined (_M_THUMB)
	pProc = (WNDPROC)(((DWORD)pProc) | 1);
#endif // _WIN32_WCE
	WNDPROC pOldProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
#endif // _WIN32_WCE_CEF
#ifdef _DEBUG
	// check if somebody has subclassed us already since we discard it
	if(pOldProc != StartWindowProc)
		ATLTRACE2(atlTraceWindowing, 0, _T("Subclassing through a hook discarded.\n"));
#else
	pOldProc;	// avoid unused warning
#endif
	return pProc(hWnd, uMsg, wParam, lParam);
}

template <class TBase, class TWinTraits>
LRESULT CALLBACK CWindowImplBaseT< TBase, TWinTraits >::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindowImplBaseT< TBase, TWinTraits >* pThis = (CWindowImplBaseT< TBase, TWinTraits >*)hWnd;
	// set a ptr to this message and save the old value
	MSG msg = { pThis->m_hWnd, uMsg, wParam, lParam, 0, { 0, 0 } };
	const MSG* pOldMsg = pThis->m_pCurrentMsg;
	pThis->m_pCurrentMsg = &msg;
	// pass to the message map to process
	LRESULT lRes;
	BOOL bRet = pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, 0);
	// restore saved value for the current message
	ATLASSERT(pThis->m_pCurrentMsg == &msg);
	pThis->m_pCurrentMsg = pOldMsg;
	// do the default processing if message was not handled
	if(!bRet)
	{
		if(uMsg != WCE_IF(WM_DESTROY,WM_NCDESTROY))
		{
#if defined(_WIN32_WCE_AYGSHELL) && (_WIN32_WCE >= 300)
			if (uMsg == WM_ACTIVATE) 
			{
				if (pThis->m_bShowDoneButton)
				{
					switch(LOWORD(wParam)) 
					{
						case WA_INACTIVE:
							::SHDoneButton(pThis->m_hWnd, SHDB_HIDE);					
							break;
						case WA_ACTIVE:
						case WA_CLICKACTIVE:
							::SHDoneButton(pThis->m_hWnd, SHDB_SHOW);
							break;
						default:
							break;
					}
				}
			} 
#endif // _WIN32_WCE_AYGSHELL
			lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
		}
		else
		{
			// unsubclass, if needed
			LONG pfnWndProc = ::GetWindowLong(pThis->m_hWnd, GWL_WNDPROC);
			lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
#if defined(_WIN32_WCE_CEF)
			pThis->m_thunk.Cleanup();
#else // _WIN32_WCE_CEF		
			if(pThis->m_pfnSuperWindowProc != ::DefWindowProc && ::GetWindowLong(pThis->m_hWnd, GWL_WNDPROC) == pfnWndProc)
				::SetWindowLong(pThis->m_hWnd, GWL_WNDPROC, (LONG)pThis->m_pfnSuperWindowProc);
#endif // _WIN32_WCE_CEF
			// clear out window handle
			HWND hWnd = pThis->m_hWnd;
			pThis->m_hWnd = NULL;
			// clean up after window is destroyed
			pThis->OnFinalMessage(hWnd);
		}
	}
	return lRes;
}

template <class TBase, class TWinTraits>
HWND CWindowImplBaseT< TBase, TWinTraits >::Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName,
		DWORD dwStyle, DWORD dwExStyle, UINT nID, ATOM atom, LPVOID lpCreateParam)
{
	ATLASSERT(m_hWnd == NULL);

	if(atom == 0)
		return NULL;

	_Module.AddCreateWndData(&m_thunk.cd, this);

	if(nID == 0 && (dwStyle & WS_CHILD))
		nID = (UINT)this;

	HWND hWnd = ::CreateWindowEx(dwExStyle, (LPCTSTR)MAKELONG(atom, 0), szWindowName,
		dwStyle, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
		rcPos.bottom - rcPos.top, hWndParent, (HMENU)nID,
		_Module.GetModuleInstance(), lpCreateParam);

	ATLASSERT(m_hWnd == hWnd);

	return hWnd;
}

template <class TBase, class TWinTraits>
BOOL CWindowImplBaseT< TBase, TWinTraits >::SubclassWindow(HWND hWnd)
{
	ATLASSERT(m_hWnd == NULL);
	ATLASSERT(::IsWindow(hWnd));

#if defined(_WIN32_WCE_CEF)
	WNDPROC pfnWndProc;
	m_thunk.Init(hWnd, GetWindowProc(), this, FALSE, NULL, &pfnWndProc);
#else // _WIN32_WCE_CEF
	m_thunk.Init(GetWindowProc(), this);
	WNDPROC pProc = (WNDPROC)&(m_thunk.thunk);
#if defined(_WIN32_WCE) && defined (_M_THUMB)
	pProc = (WNDPROC)(((DWORD)pProc) | 1);
#endif // _WIN32_WCE
	WNDPROC pfnWndProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
#endif // _WIN32_WCE_CEF
	if(pfnWndProc == NULL)
		return FALSE;
	m_pfnSuperWindowProc = pfnWndProc;
	m_hWnd = hWnd;
	return TRUE;
}

// Use only if you want to subclass before window is destroyed,
// WindowProc will automatically subclass when  window goes away
template <class TBase, class TWinTraits>
HWND CWindowImplBaseT< TBase, TWinTraits >::UnsubclassWindow(BOOL bForce /*= FALSE*/)
{
	ATLASSERT(m_hWnd != NULL);

	WNDPROC pActiveProc = (WNDPROC)::GetWindowLong(m_hWnd, GWL_WNDPROC);
#if defined (_WIN32_WCE_CEF)
	m_thunk.Cleanup();
	WNDPROC pOurProc = pActiveProc;
#else // !_WIN32_WCE_CEF
	WNDPROC pOurProc = (WNDPROC)&(m_thunk.thunk);
#endif // _WIN32_WCE_CEF

	HWND hWnd = NULL;
	if (bForce || pOurProc == pActiveProc)
	{
#if !defined (_WIN32_WCE_CEF)
		if(!::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pfnSuperWindowProc))
			return NULL;
#endif // !_WIN32_WCE_CEF

		m_pfnSuperWindowProc = ::DefWindowProc;
		hWnd = m_hWnd;
		m_hWnd = NULL;
	}
	return hWnd;
}

template <class T, class TBase /* = CWindow */, class TWinTraits /*= CControlWinTraits */>
class ATL_NO_VTABLE CWindowImpl : public CWindowImplBaseT< TBase, TWinTraits >
{
public:
	DECLARE_WND_CLASS(NULL)

	HWND Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		if (T::GetWndClassInfo().m_lpszOrigName == NULL)
			T::GetWndClassInfo().m_lpszOrigName = GetWndClassName();
		ATOM atom = T::GetWndClassInfo().Register(&m_pfnSuperWindowProc);

		dwStyle = T::GetWndStyle(dwStyle);
		dwExStyle = T::GetWndExStyle(dwExStyle);

		return CWindowImplBaseT< TBase, TWinTraits >::Create(hWndParent, rcPos, szWindowName,
			dwStyle, dwExStyle, nID, atom, lpCreateParam);
	}

};

/////////////////////////////////////////////////////////////////////////////
// CDialogImpl - Implements a dialog box

template <class TBase = CWindow>
class ATL_NO_VTABLE CDialogImplBaseT : public CWindowImplRoot< TBase >
{
public:
	virtual WNDPROC GetDialogProc()
	{
		return DialogProc;
	}
	static LRESULT CALLBACK StartDialogProc(HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL MapDialogRect(LPRECT lpRect)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::MapDialogRect(m_hWnd, lpRect);
	}
	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		// override to do something, if needed
	}
	// has no meaning for a dialog, but needed for handlers that use it
	LRESULT DefWindowProc()
	{
		return 0;
	}
};

template <class TBase>
LRESULT CALLBACK CDialogImplBaseT< TBase >::StartDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDialogImplBaseT< TBase >* pThis = (CDialogImplBaseT< TBase >*)_Module.ExtractCreateWndData();
	ATLASSERT(pThis != NULL);
	pThis->m_hWnd = hWnd;
#if defined(_WIN32_WCE_CEF)
	WNDPROC pProc, pOldProc;
	pThis->m_thunk.Init(hWnd, pThis->GetDialogProc(), pThis, TRUE, &pProc, &pOldProc);
#else // _WIN32_WCE_CEF
	pThis->m_thunk.Init(pThis->GetDialogProc(), pThis);
	WNDPROC pProc = (WNDPROC)&(pThis->m_thunk.thunk);
#if defined(_WIN32_WCE) && defined (_M_THUMB)
	pProc = (WNDPROC)(((DWORD)pProc) | 1);
#endif // _WIN32_WCE
	WNDPROC pOldProc = (WNDPROC)::SetWindowLong(hWnd, DWL_DLGPROC, (LONG)pProc);
#endif // _WIN32_WCE_CEF
#ifdef _DEBUG
	// check if somebody has subclassed us already since we discard it
	if(pOldProc != StartDialogProc)
		ATLTRACE2(atlTraceWindowing, 0, _T("Subclassing through a hook discarded.\n"));
#else
	pOldProc;	// avoid unused warning
#endif
	return pProc(hWnd, uMsg, wParam, lParam);
}

template <class TBase>
LRESULT CALLBACK CDialogImplBaseT< TBase >::DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDialogImplBaseT< TBase >* pThis = (CDialogImplBaseT< TBase >*)hWnd;
	// set a ptr to this message and save the old value
	MSG msg = { pThis->m_hWnd, uMsg, wParam, lParam, 0, { 0, 0 } };
	const MSG* pOldMsg = pThis->m_pCurrentMsg;
	pThis->m_pCurrentMsg = &msg;
	// pass to the message map to process
	LRESULT lRes;
	BOOL bRet = pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, 0);
	// restore saved value for the current message
	ATLASSERT(pThis->m_pCurrentMsg == &msg);
	pThis->m_pCurrentMsg = pOldMsg;
	// set result if message was handled
	if(bRet)
	{
		switch (uMsg)
		{
		case WM_INITDIALOG:
#if defined(_WIN32_WCE_AYGSHELL) && (_WIN32_WCE >= 300)
		{
			SHINITDLGINFO	shidi;
			memset(&shidi, 0, sizeof(SHINITDLGINFO));
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;			
			shidi.hDlg = pThis->m_hWnd;
			if (!SHInitDialog(&shidi))
			{
				DWORD dwError = GetLastError();
				ATLTRACE(_T("Warning: Making Fullscreen dialog failed during dialog init. Error # %d\n"),dwError);				
			}
		}
		// fall-thru
#endif // _WIN32_WCE_AYGSHELL
		case WM_COMPAREITEM:
		case WM_VKEYTOITEM:
		case WM_CHARTOITEM:
		case WM_QUERYDRAGICON:
		case WM_CTLCOLORMSGBOX:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
			return lRes;
			break;
		}
		::SetWindowLong(pThis->m_hWnd, DWL_MSGRESULT, lRes);
		return TRUE;
	}
	if(uMsg == WCE_IF(WM_DESTROY,WM_NCDESTROY))
	{
		// clear out window handle
		HWND hWnd = pThis->m_hWnd;
		pThis->m_hWnd = NULL;
		// clean up after dialog is destroyed
		pThis->OnFinalMessage(hWnd);
	}
	return FALSE;
}

typedef CDialogImplBaseT<CWindow>	CDialogImplBase;

template <class T, class TBase /* = CWindow */>
class ATL_NO_VTABLE CDialogImpl : public CDialogImplBaseT< TBase >
{
public:
#ifdef _DEBUG
	bool m_bModal;
	CDialogImpl() : m_bModal(false) { }
#endif //_DEBUG
	// modal dialogs
	int DoModal(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);
		_Module.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT< TBase >*)this);
#ifdef _DEBUG
		m_bModal = true;
#endif // _DEBUG
		return ::DialogBoxParam(_Module.GetResourceInstance(), MAKEINTRESOURCE(T::IDD),
					hWndParent, (DLGPROC)T::StartDialogProc, dwInitParam);
	}
	BOOL EndDialog(int nRetCode)
	{
		ATLASSERT(::IsWindow(m_hWnd));
#ifdef _DEBUG
		ATLASSERT(m_bModal);	// must be a modal dialog
#endif // _DEBUG
		return ::EndDialog(m_hWnd, nRetCode);
	}
	// modeless dialogs
	HWND Create(HWND hWndParent, LPARAM dwInitParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);
		_Module.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT< TBase >*)this);
#ifdef _DEBUG
		m_bModal = false;
#endif // _DEBUG
		HWND hWnd = ::CreateDialogParam(_Module.GetResourceInstance(), MAKEINTRESOURCE(T::IDD),
					hWndParent, (DLGPROC)T::StartDialogProc, dwInitParam);
		ATLASSERT(m_hWnd == hWnd);
		return hWnd;
	}
	// for CComControl
	HWND Create(HWND hWndParent, RECT&, LPARAM dwInitParam = NULL)
	{
		return Create(hWndParent, dwInitParam);
	}
	BOOL DestroyWindow()
	{
		ATLASSERT(::IsWindow(m_hWnd));
#ifdef _DEBUG
		ATLASSERT(!m_bModal);	// must not be a modal dialog
#endif // _DEBUG
		return ::DestroyWindow(m_hWnd);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CAxDialogImpl - Implements a dialog box that hosts ActiveX controls

#ifndef _ATL_NO_HOSTING

template <class T, class TBase /* = CWindow */>
class ATL_NO_VTABLE CAxDialogImpl : public CDialogImplBaseT< TBase >
{
public:
#ifdef _DEBUG
	bool m_bModal;
	CAxDialogImpl() : m_bModal(false) { }
#endif //_DEBUG
	// modal dialogs
	int DoModal(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);
		_Module.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT< TBase >*)this);
#ifdef _DEBUG
		m_bModal = true;
#endif // _DEBUG
		return AtlAxDialogBox(_Module.GetResourceInstance(), MAKEINTRESOURCE(T::IDD),
					hWndParent, (DLGPROC)T::StartDialogProc, dwInitParam);
	}
	BOOL EndDialog(int nRetCode)
	{
		ATLASSERT(::IsWindow(m_hWnd));
#ifdef _DEBUG
		ATLASSERT(m_bModal);	// must be a modal dialog
#endif // _DEBUG
		return ::EndDialog(m_hWnd, nRetCode);
	}
	// modeless dialogs
	HWND Create(HWND hWndParent, LPARAM dwInitParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);
		_Module.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT< TBase >*)this);
#ifdef _DEBUG
		m_bModal = false;
#endif // _DEBUG
		HWND hWnd = AtlAxCreateDialog(_Module.GetResourceInstance(), MAKEINTRESOURCE(T::IDD),
					hWndParent, (DLGPROC)T::StartDialogProc, dwInitParam);
		ATLASSERT(m_hWnd == hWnd);
		return hWnd;
	}
	// for CComControl
	HWND Create(HWND hWndParent, RECT&, LPARAM dwInitParam = NULL)
	{
		return Create(hWndParent, dwInitParam);
	}
	BOOL DestroyWindow()
	{
		ATLASSERT(::IsWindow(m_hWnd));
#ifdef _DEBUG
		ATLASSERT(!m_bModal);	// must not be a modal dialog
#endif
		return ::DestroyWindow(m_hWnd);
	}
};

#endif //_ATL_NO_HOSTING

/////////////////////////////////////////////////////////////////////////////
// CSimpleDialog - Prebuilt modal dialog that uses standard buttons

template <WORD t_wDlgTemplateID, BOOL t_bCenter /* = TRUE */>
class CSimpleDialog : public CDialogImplBase
{
public:
	int DoModal(HWND hWndParent = ::GetActiveWindow())
	{
		ATLASSERT(m_hWnd == NULL);
		_Module.AddCreateWndData(&m_thunk.cd, (CDialogImplBase*)this);
		int nRet = ::DialogBox(_Module.GetResourceInstance(),
			MAKEINTRESOURCE(t_wDlgTemplateID), hWndParent, (DLGPROC)StartDialogProc);
		m_hWnd = NULL;
		return nRet;
	}

	typedef CSimpleDialog<t_wDlgTemplateID, t_bCenter>	thisClass;
	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_RANGE_HANDLER(IDOK, IDNO, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if(t_bCenter)
			CenterWindow(GetParent());
		return TRUE;
	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::EndDialog(m_hWnd, wID);
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CContainedWindow - Implements a contained window

template <class TBase /* = CWindow*/, class TWinTraits /* = CControlWinTraits */>
class CContainedWindowT : public TBase
{
public:
	CWndProcThunk m_thunk;
	LPCTSTR m_lpszClassName;
	WNDPROC m_pfnSuperWindowProc;
	CMessageMap* m_pObject;
	DWORD m_dwMsgMapID;
	const MSG* m_pCurrentMsg;

	// If you use this constructor you must supply
	// the Window Class Name, Object* and Message Map ID
	// Later to the Create call
	CContainedWindowT() : m_pCurrentMsg(NULL)
	{ }

    ~CContainedWindowT()
    {
        if(m_lpszClassName)
        {
            LPTSTR szBuff = (LPTSTR)_alloca((lstrlen(m_lpszClassName) + 14) * sizeof(TCHAR));
            lstrcpy(szBuff, TEXT("ATL:"));
            lstrcat(szBuff, m_lpszClassName);
            ::UnregisterClass(szBuff, _Module.GetModuleInstance());
        }
    }

	CContainedWindowT(LPTSTR lpszClassName, CMessageMap* pObject, DWORD dwMsgMapID = 0)
		: m_lpszClassName(lpszClassName),
		m_pfnSuperWindowProc(::DefWindowProc),
		m_pObject(pObject), m_dwMsgMapID(dwMsgMapID),
		m_pCurrentMsg(NULL)
	{ }

	CContainedWindowT(CMessageMap* pObject, DWORD dwMsgMapID = 0)
		: m_lpszClassName(TBase::GetWndClassName()),
		m_pfnSuperWindowProc(::DefWindowProc),
		m_pObject(pObject), m_dwMsgMapID(dwMsgMapID),
		m_pCurrentMsg(NULL)
	{ }

	void SwitchMessageMap(DWORD dwMsgMapID)
	{
		m_dwMsgMapID = dwMsgMapID;
	}

	const MSG* GetCurrentMessage() const
	{
		return m_pCurrentMsg;
	}

	LRESULT DefWindowProc()
	{
		const MSG* pMsg = m_pCurrentMsg;
		LRESULT lRes = 0;
		if (pMsg != NULL)
			lRes = DefWindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
		return lRes;
	}

	LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
#ifdef STRICT
		return ::CallWindowProc(m_pfnSuperWindowProc, m_hWnd, uMsg, wParam, lParam);
#else
		return ::CallWindowProc((FARPROC)m_pfnSuperWindowProc, m_hWnd, uMsg, wParam, lParam);
#endif
	}
	static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam)
	{
		CContainedWindowT< TBase >* pThis = (CContainedWindowT< TBase >*)_Module.ExtractCreateWndData();
		ATLASSERT(pThis != NULL);
		pThis->m_hWnd = hWnd;
#if defined(_WIN32_WCE_CEF)
		WNDPROC pProc, pOldProc;
		pThis->m_thunk.Init(hWnd, WindowProc, pThis, FALSE, &pProc, &pOldProc);
#else // _WIN32_WCE_CEF
		pThis->m_thunk.Init(WindowProc, pThis);
		WNDPROC pProc = (WNDPROC)&(pThis->m_thunk.thunk);
#if defined(_WIN32_WCE) && defined (_M_THUMB)
	pProc = (WNDPROC)(((DWORD)pProc) | 1);
#endif // _WIN32_WCE
		WNDPROC pOldProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
#endif // _WIN32_WCE_CEF
#ifdef _DEBUG
		// check if somebody has subclassed us already since we discard it
		if(pOldProc != StartWindowProc)
			ATLTRACE2(atlTraceWindowing, 0, _T("Subclassing through a hook discarded.\n"));
#else
		pOldProc;	// avoid unused warning
#endif
		return pProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		CContainedWindowT< TBase >* pThis = (CContainedWindowT< TBase >*)hWnd;
		ATLASSERT(pThis->m_hWnd != NULL);
		ATLASSERT(pThis->m_pObject != NULL);
		// set a ptr to this message and save the old value
		MSG msg = { pThis->m_hWnd, uMsg, wParam, lParam, 0, { 0, 0 } };
		const MSG* pOldMsg = pThis->m_pCurrentMsg;
		pThis->m_pCurrentMsg = &msg;
		// pass to the message map to process
		LRESULT lRes;
		BOOL bRet = pThis->m_pObject->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, pThis->m_dwMsgMapID);
		// restore saved value for the current message
		ATLASSERT(pThis->m_pCurrentMsg == &msg);
		pThis->m_pCurrentMsg = pOldMsg;
		// do the default processing if message was not handled
		if(!bRet)
		{
			if(uMsg != WCE_IF(WM_DESTROY, WM_NCDESTROY))
			{
#if defined(_WIN32_WCE_AYGSHELL) && (_WIN32_WCE >= 300)
				if (uMsg == WM_ACTIVATE) 
				{
					if (pThis->m_bShowDoneButton)
					{
						switch(LOWORD(wParam)) 
						{
						case WA_INACTIVE:
							::SHDoneButton(pThis->m_hWnd, SHDB_HIDE);					
							break;
						case WA_ACTIVE:
						case WA_CLICKACTIVE:
							::SHDoneButton(pThis->m_hWnd, SHDB_SHOW);
							break;
						default:
							break;
						}
					}
				} 
#endif // _WIN32_WCE_AYGSHELL			
				lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
			}
			else
			{
				// unsubclass, if needed
				LONG pfnWndProc = ::GetWindowLong(pThis->m_hWnd, GWL_WNDPROC);
				lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
				if(pThis->m_pfnSuperWindowProc != ::DefWindowProc && ::GetWindowLong(pThis->m_hWnd, GWL_WNDPROC) == pfnWndProc)
					::SetWindowLong(pThis->m_hWnd, GWL_WNDPROC, (LONG)pThis->m_pfnSuperWindowProc);
				// clear out window handle
				pThis->m_hWnd = NULL;
			}
		}
		return lRes;
	}

	ATOM RegisterWndSuperclass()
	{
		ATOM atom = 0;
		LPTSTR szBuff = (LPTSTR)_alloca((lstrlen(m_lpszClassName) + 14) * sizeof(TCHAR));

#if defined(_WIN32_WCE)
		WNDCLASS wc;
#else // _WIN32_WCE
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
#endif // _WIN32_WCE

		// Try global class
		if(!::WCE_IF(GetClassInfo,GetClassInfoEx)(NULL, m_lpszClassName, &wc))
		{
			// try local class
			if(!::WCE_IF(GetClassInfo,GetClassInfoEx)(_Module.GetModuleInstance(), m_lpszClassName, &wc))
				return atom;
		}

		m_pfnSuperWindowProc = wc.lpfnWndProc;
		lstrcpy(szBuff, _T("ATL:"));
		lstrcat(szBuff, m_lpszClassName);

#if defined(_WIN32_WCE)
		WNDCLASS wc1;
#else // _WIN32_WCE
		WNDCLASSEX wc1;
		wc1.cbSize = sizeof(WNDCLASSEX);
#endif // _WIN32_WCE
		atom = (ATOM)::WCE_IF(GetClassInfo,GetClassInfoEx)(_Module.GetModuleInstance(), szBuff, &wc1);

		if(atom == 0)   // register class
		{
			wc.lpszClassName = szBuff;
			wc.lpfnWndProc = StartWindowProc;
			wc.hInstance = _Module.GetModuleInstance();
			wc.style &= ~CS_GLOBALCLASS;	// we don't register global classes

			atom = ::WCE_IF(RegisterClass,RegisterClassEx)(&wc);
		}

		return atom;
	}
	HWND Create(CMessageMap* pObject, DWORD dwMsgMapID, HWND hWndParent, RECT* prcPos,
		LPCTSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0,
		UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		m_lpszClassName = TBase::GetWndClassName();
		m_pfnSuperWindowProc = ::DefWindowProc;
		m_pObject = pObject;
		m_dwMsgMapID = dwMsgMapID;
		return Create(hWndParent, prcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
	}

	HWND Create(LPCTSTR lpszClassName, CMessageMap* pObject, DWORD dwMsgMapID, HWND hWndParent, RECT* prcPos, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0, UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		m_lpszClassName = lpszClassName;
		m_pfnSuperWindowProc = ::DefWindowProc;
		m_pObject = pObject;
		m_dwMsgMapID = dwMsgMapID;
		return Create(hWndParent, prcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
	}


	// This function is Deprecated, use the version
	// which takes a RECT* instead
	HWND Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		return Create(hWndParent, &rcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
	}

	HWND Create(HWND hWndParent, RECT* prcPos, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		ATLASSERT(m_hWnd == NULL);

		ATOM atom = RegisterWndSuperclass();
		if(atom == 0)
			return NULL;

		_Module.AddCreateWndData(&m_thunk.cd, this);

		if(nID == 0 && (dwStyle & WS_CHILD))
			nID = (UINT)this;

		dwStyle = TWinTraits::GetWndStyle(dwStyle);
		dwExStyle = TWinTraits::GetWndExStyle(dwExStyle);

		HWND hWnd = ::CreateWindowEx(dwExStyle, (LPCTSTR)MAKELONG(atom, 0), szWindowName,
								dwStyle,
								prcPos->left, prcPos->top,
								prcPos->right - prcPos->left,
								prcPos->bottom - prcPos->top,
								hWndParent, (HMENU)nID,
								_Module.GetModuleInstance(), lpCreateParam);
		ATLASSERT(m_hWnd == hWnd);
		return hWnd;
	}

	BOOL SubclassWindow(HWND hWnd)
	{
		ATLASSERT(m_hWnd == NULL);
		ATLASSERT(::IsWindow(hWnd));
#if defined(_WIN32_WCE_CEF)
		WNDPROC pProc, pOldProc;
		pThis->m_thunk.Init(hWnd, WindowProc, this, FALSE, &pProc, &pOldProc);
#else // _WIN32_WCE_CEF
		m_thunk.Init(WindowProc, this);
		WNDPROC pProc = (WNDPROC)&m_thunk.thunk;
#if defined(_WIN32_WCE) && defined (_M_THUMB)
	pProc = (WNDPROC)(((DWORD)pProc) | 1);
#endif // _WIN32_WCE
		WNDPROC pfnWndProc = (WNDPROC)::SetWindowLong(hWnd, GWL_WNDPROC, (LONG)pProc);
#endif // _WIN32_WCE_CEF
		if(pfnWndProc == NULL)
			return FALSE;
		m_pfnSuperWindowProc = pfnWndProc;
		m_hWnd = hWnd;
		return TRUE;
	}

	// Use only if you want to subclass before window is destroyed,
	// WindowProc will automatically subclass when  window goes away
	HWND UnsubclassWindow(BOOL bForce = FALSE)
	{
		ATLASSERT(m_hWnd != NULL);

		WNDPROC pOurProc = (WNDPROC)&(m_thunk.thunk);
		WNDPROC pActiveProc = (WNDPROC)::GetWindowLong(m_hWnd, GWL_WNDPROC);

		HWND hWnd = NULL;
		if (bForce || pOurProc == pActiveProc)
		{
			if(!::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pfnSuperWindowProc))
				return NULL;

			m_pfnSuperWindowProc = ::DefWindowProc;
			hWnd = m_hWnd;
			m_hWnd = NULL;
		}
		return hWnd;
	}
};

typedef CContainedWindowT<CWindow>	CContainedWindow;

/////////////////////////////////////////////////////////////////////////////
// _DialogSizeHelper - helpers for calculating the size of a dialog template

class _DialogSizeHelper
{
public:
//local struct used for implementation
#pragma pack(push, 1)
	struct _ATL_DLGTEMPLATEEX
	{
		WORD dlgVer;
		WORD signature;
		DWORD helpID;
		DWORD exStyle;
		DWORD style;
		WORD cDlgItems;
		short x;
		short y;
		short cx;
		short cy;
	};
#pragma pack(pop)

	static void GetDialogSize(const DLGTEMPLATE* pTemplate, SIZE* pSize)
	{
		// If the dialog has a font we use it otherwise we default
		// to the system font.
		if (HasFont(pTemplate))
		{
			TCHAR szFace[LF_FACESIZE];
			WORD  wFontSize = 0;
			GetFont(pTemplate, szFace, &wFontSize);
			GetSizeInDialogUnits(pTemplate, pSize);
			ConvertDialogUnitsToPixels(szFace, wFontSize, pSize);
		}
		else
		{
			GetSizeInDialogUnits(pTemplate, pSize);
			LONG nDlgBaseUnits = GetDialogBaseUnits();
			pSize->cx = WCE_ATL_FCTN(MulDiv)(pSize->cx, LOWORD(nDlgBaseUnits), 4);
			pSize->cy = WCE_ATL_FCTN(MulDiv)(pSize->cy, HIWORD(nDlgBaseUnits), 8);
		}
	}

	static void ConvertDialogUnitsToPixels(LPCTSTR pszFontFace, WORD wFontSize, SIZE* pSizePixel)
	{
		// Attempt to create the font to be used in the dialog box
		UINT cxSysChar, cySysChar;
		LOGFONT lf;
		HDC hDC = ::GetDC(NULL);
		int cxDlg = pSizePixel->cx;
		int cyDlg = pSizePixel->cy;

		ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = -WCE_ATL_FCTN(MulDiv)(wFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		lf.lfWeight = FW_NORMAL;
		lf.lfCharSet = DEFAULT_CHARSET;
		lstrcpy(lf.lfFaceName, pszFontFace);

		HFONT hNewFont = CreateFontIndirect(&lf);
		if (hNewFont != NULL)
		{
			TEXTMETRIC  tm;
			SIZE        size;
			HFONT       hFontOld = (HFONT)SelectObject(hDC, hNewFont);
			GetTextMetrics(hDC, &tm);
			cySysChar = tm.tmHeight + tm.tmExternalLeading;
			::GetTextExtentPoint(hDC,
				_T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"), 52,
				&size);
			cxSysChar = (size.cx + 26) / 52;
			SelectObject(hDC, hFontOld);
			DeleteObject(hNewFont);
		}
		else
		{
			// Could not create the font so just use the system's values
			cxSysChar = LOWORD(GetDialogBaseUnits());
			cySysChar = HIWORD(GetDialogBaseUnits());
		}
		::ReleaseDC(NULL, hDC);

		// Translate dialog units to pixels
		pSizePixel->cx = WCE_ATL_FCTN(MulDiv)(cxDlg, cxSysChar, 4);
		pSizePixel->cy = WCE_ATL_FCTN(MulDiv)(cyDlg, cySysChar, 8);
	}

	static BOOL IsDialogEx(const DLGTEMPLATE* pTemplate)
	{
		return ((_ATL_DLGTEMPLATEEX*)pTemplate)->signature == 0xFFFF;
	}

	static BOOL HasFont(const DLGTEMPLATE* pTemplate)
	{
		return (DS_SETFONT &
			(IsDialogEx(pTemplate) ?
				((_ATL_DLGTEMPLATEEX*)pTemplate)->style : pTemplate->style));
	}

	static BYTE* GetFontSizeField(const DLGTEMPLATE* pTemplate)
	{
		BOOL bDialogEx = IsDialogEx(pTemplate);
		WORD* pw;

		if (bDialogEx)
			pw = (WORD*)((_ATL_DLGTEMPLATEEX*)pTemplate + 1);
		else
			pw = (WORD*)(pTemplate + 1);

		if (*pw == (WORD)-1)        // Skip menu name string or ordinal
			pw += 2; // WORDs
		else
			while(*pw++);

		if (*pw == (WORD)-1)        // Skip class name string or ordinal
			pw += 2; // WORDs
		else
			while(*pw++);

		while (*pw++);          // Skip caption string

		return (BYTE*)pw;
	}

	static BOOL GetFont(const DLGTEMPLATE* pTemplate, TCHAR* pszFace, WORD* pFontSize)
	{
		USES_CONVERSION;
		if (!HasFont(pTemplate))
			return FALSE;

		BYTE* pb = GetFontSizeField(pTemplate);
		*pFontSize = *(WORD*)pb;
		// Skip over font attributes to get to the font name
		pb += sizeof(WORD) * (IsDialogEx(pTemplate) ? 3 : 1);

		_tcscpy(pszFace, W2T((WCHAR*)pb));
		return TRUE;
	}

	static void GetSizeInDialogUnits(const DLGTEMPLATE* pTemplate, SIZE* pSize)
	{
		if (IsDialogEx(pTemplate))
		{
			pSize->cx = ((_ATL_DLGTEMPLATEEX*)pTemplate)->cx;
			pSize->cy = ((_ATL_DLGTEMPLATEEX*)pTemplate)->cy;
		}
		else
		{
			pSize->cx = pTemplate->cx;
			pSize->cy = pTemplate->cy;
		}
	}
};

inline void AtlGetDialogSize(const DLGTEMPLATE* pTemplate, SIZE* pSize)
{
	_DialogSizeHelper::GetDialogSize(pTemplate, pSize);
}

}; //namespace ATL

#ifndef _ATL_DLL_IMPL
#ifndef _ATL_DLL
#define _ATLWIN_IMPL
#endif
#endif

#endif // __ATLWIN_H__

//All exports go here
#ifdef _ATLWIN_IMPL

#ifndef _ATL_DLL_IMPL
namespace ATL
{
#endif

#if !defined(_WIN32_WCE)
ATLINLINE ATLAPI_(ATOM) AtlModuleRegisterWndClassInfoA(_ATL_MODULE* pM, _ATL_WNDCLASSINFOA* p, WNDPROC* pProc)
{
	if (p->m_atom == 0)
	{
		::EnterCriticalSection(&pM->m_csWindowCreate);
		if(p->m_atom == 0)
		{
			HINSTANCE hInst = pM->m_hInst;
			if (p->m_lpszOrigName != NULL)
			{
				ATLASSERT(pProc != NULL);
				LPCSTR lpsz = p->m_wc.lpszClassName;
				WNDPROC proc = p->m_wc.lpfnWndProc;

				WNDCLASSEXA wc;
				wc.cbSize = sizeof(WNDCLASSEX);
				// Try global class
				if(!::GetClassInfoExA(NULL, p->m_lpszOrigName, &wc))
				{
					// try process local
					if(!::GetClassInfoExA(_Module.GetModuleInstance(), p->m_lpszOrigName, &wc))
					{
						::LeaveCriticalSection(&pM->m_csWindowCreate);
						return 0;
					}
				}
				memcpy(&p->m_wc, &wc, sizeof(WNDCLASSEX));
				p->pWndProc = p->m_wc.lpfnWndProc;
				p->m_wc.lpszClassName = lpsz;
				p->m_wc.lpfnWndProc = proc;
			}
			else
			{
				p->m_wc.hCursor = ::LoadCursorA(p->m_bSystemCursor ? NULL : hInst,
					p->m_lpszCursorID);
			}

			p->m_wc.hInstance = hInst;
			p->m_wc.style &= ~CS_GLOBALCLASS;	// we don't register global classes
			if (p->m_wc.lpszClassName == NULL)
			{
				wsprintfA(p->m_szAutoName, "ATL:%8.8X", (DWORD)&p->m_wc);
				p->m_wc.lpszClassName = p->m_szAutoName;
			}
			WNDCLASSEXA wcTemp;
			memcpy(&wcTemp, &p->m_wc, sizeof(WNDCLASSEXW));
			p->m_atom = (ATOM)::GetClassInfoExA(p->m_wc.hInstance, p->m_wc.lpszClassName, &wcTemp);
			if (p->m_atom == 0)
				p->m_atom = ::RegisterClassExA(&p->m_wc);
		}
		::LeaveCriticalSection(&pM->m_csWindowCreate);
	}

	if (p->m_lpszOrigName != NULL)
	{
		ATLASSERT(pProc != NULL);
		ATLASSERT(p->pWndProc != NULL);
		*pProc = p->pWndProc;
	}
	return p->m_atom;
}
#endif // _WIN32_WCE

ATLINLINE ATLAPI_(ATOM) AtlModuleRegisterWndClassInfoW(_ATL_MODULE* pM, _ATL_WNDCLASSINFOW* p, WNDPROC* pProc)
{
	if (p->m_atom == 0)
	{
		::EnterCriticalSection(&pM->m_csWindowCreate);
		if(p->m_atom == 0)
		{
			HINSTANCE hInst = pM->m_hInst;
			if (p->m_lpszOrigName != NULL)
			{
				ATLASSERT(pProc != NULL);
				LPCWSTR lpsz = p->m_wc.lpszClassName;
				WNDPROC proc = p->m_wc.lpfnWndProc;

#if defined(_WIN32_WCE)
				WNDCLASS wc;
#else // _WIN32_WCE
				WNDCLASSEXW wc;
				wc.cbSize = sizeof(WNDCLASSEX);
#endif // _WIN32_WCE
				// Try global class
				if(!::WCE_IF(GetClassInfo,GetClassInfoExW)(NULL, p->m_lpszOrigName, &wc))
				{
					// try process local
					if(!::WCE_IF(GetClassInfo,GetClassInfoExW)(_Module.GetModuleInstance(), p->m_lpszOrigName, &wc))
					{
						::LeaveCriticalSection(&pM->m_csWindowCreate);
						return 0;
					}
				}
				memcpy(&p->m_wc, &wc, sizeof(WCE_IF(WNDCLASS,WNDCLASSEX)));
				p->pWndProc = p->m_wc.lpfnWndProc;
				p->m_wc.lpszClassName = lpsz;
				p->m_wc.lpfnWndProc = proc;
			}
			else
			{
				p->m_wc.hCursor = ::LoadCursorW(p->m_bSystemCursor ? NULL : hInst,
					p->m_lpszCursorID);
			}

			p->m_wc.hInstance = hInst;
			p->m_wc.style &= ~CS_GLOBALCLASS;	// we don't register global classes
			if (p->m_wc.lpszClassName == NULL)
			{
				wsprintfW(p->m_szAutoName, L"ATL:%8.8X", (DWORD)&p->m_wc);
				p->m_wc.lpszClassName = p->m_szAutoName;
			}
			WCE_IF(WNDCLASS,WNDCLASSEXW) wcTemp;
			memcpy(&wcTemp, &p->m_wc, sizeof(WCE_IF(WNDCLASS,WNDCLASSEXW)));
			p->m_atom = (ATOM)::WCE_IF(GetClassInfo,GetClassInfoExW)(p->m_wc.hInstance, p->m_wc.lpszClassName, &wcTemp);
			if (p->m_atom == 0)
            {
				p->m_atom = WCE_IF(RegisterClass,::RegisterClassExW)(&p->m_wc);

			    if(p->m_atom)
                    pM->m_rgWindowClassAtoms.Add(p->m_atom);
            }
		}
		::LeaveCriticalSection(&pM->m_csWindowCreate);
	}

	if (p->m_lpszOrigName != NULL)
	{
		ATLASSERT(pProc != NULL);
		ATLASSERT(p->pWndProc != NULL);
		*pProc = p->pWndProc;
	}
	return p->m_atom;
}

ATLINLINE ATLAPI_(HDC) AtlCreateTargetDC(HDC hdc, DVTARGETDEVICE* ptd)
{
	USES_CONVERSION;

	// cases  hdc, ptd, hdc is metafile, hic
//  NULL,    NULL,  n/a,    Display
//  NULL,   !NULL,  n/a,    ptd
//  !NULL,   NULL,  FALSE,  hdc
//  !NULL,   NULL,  TRUE,   display
//  !NULL,  !NULL,  FALSE,  ptd
//  !NULL,  !NULL,  TRUE,   ptd

#if defined(_WIN32_WCE)
	if (ptd != NULL)
		RETAILMSG(1, (TEXT("AtlCreateTargetDC: Returning whatever I'm passed... hdc=0x%08lx\r\n"), hdc));
	return hdc;
#else // _WIN32_WCE
	if (ptd != NULL)
	{
		LPDEVMODEOLE lpDevMode;
		LPOLESTR lpszDriverName;
		LPOLESTR lpszDeviceName;
		LPOLESTR lpszPortName;

		if (ptd->tdExtDevmodeOffset == 0)
			lpDevMode = NULL;
		else
			lpDevMode  = (LPDEVMODEOLE) ((LPSTR)ptd + ptd->tdExtDevmodeOffset);

		lpszDriverName = (LPOLESTR)((BYTE*)ptd + ptd->tdDriverNameOffset);
		lpszDeviceName = (LPOLESTR)((BYTE*)ptd + ptd->tdDeviceNameOffset);
		lpszPortName   = (LPOLESTR)((BYTE*)ptd + ptd->tdPortNameOffset);

		return ::CreateDC(OLE2CT(lpszDriverName), OLE2CT(lpszDeviceName),
			OLE2CT(lpszPortName), DEVMODEOLE2T(lpDevMode));
	}
	else if (hdc == NULL || GetDeviceCaps(hdc, TECHNOLOGY) == DT_METAFILE)
		return ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	else
		return hdc;
#endif // _WIN32_WCE
}

ATLINLINE ATLAPI_(void) AtlHiMetricToPixel(const SIZEL * lpSizeInHiMetric, LPSIZEL lpSizeInPix)
{
	int nPixelsPerInchX;    // Pixels per logical inch along width
	int nPixelsPerInchY;    // Pixels per logical inch along height

	HDC hDCScreen = GetDC(NULL);
	ATLASSERT(hDCScreen != NULL);
	nPixelsPerInchX = GetDeviceCaps(hDCScreen, LOGPIXELSX);
	nPixelsPerInchY = GetDeviceCaps(hDCScreen, LOGPIXELSY);
	ReleaseDC(NULL, hDCScreen);

	lpSizeInPix->cx = MAP_LOGHIM_TO_PIX(lpSizeInHiMetric->cx, nPixelsPerInchX);
	lpSizeInPix->cy = MAP_LOGHIM_TO_PIX(lpSizeInHiMetric->cy, nPixelsPerInchY);
}

ATLINLINE ATLAPI_(void) AtlPixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric)
{
	int nPixelsPerInchX;    // Pixels per logical inch along width
	int nPixelsPerInchY;    // Pixels per logical inch along height

	HDC hDCScreen = GetDC(NULL);
	ATLASSERT(hDCScreen != NULL);
	nPixelsPerInchX = GetDeviceCaps(hDCScreen, LOGPIXELSX);
	nPixelsPerInchY = GetDeviceCaps(hDCScreen, LOGPIXELSY);
	ReleaseDC(NULL, hDCScreen);

	lpSizeInHiMetric->cx = MAP_PIX_TO_LOGHIM(lpSizeInPix->cx, nPixelsPerInchX);
	lpSizeInHiMetric->cy = MAP_PIX_TO_LOGHIM(lpSizeInPix->cy, nPixelsPerInchY);
}


#ifndef _ATL_DLL_IMPL
}; //namespace ATL
#endif

//Prevent pulling in second time 
#undef _ATLWIN_IMPL

#endif // _ATLWIN_IMPL