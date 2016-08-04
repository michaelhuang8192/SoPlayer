// CDsopocx.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDsopocx

class CDsopocx : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDsopocx)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8FEFF364, 0x6A5F, 0x4966, { 0xA9, 0x17, 0xA3, 0xAC, 0x28, 0x41, 0x16, 0x59 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:

// Operations
public:

	void SetSopAddress(LPCTSTR SopAddress)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SopAddress);
	}
	CString GetSopAddress()
	{
		CString result;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetChannelName(LPCTSTR ChannelName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ChannelName);
	}
	CString GetChannelName()
	{
		CString result;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetUserID(long UserID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, UserID);
	}
	CString GetUserID()
	{
		CString result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetUsername(LPCTSTR Username)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Username);
	}
	CString GetUsername()
	{
		CString result;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetPassword(LPCTSTR Password)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Password);
	}
	CString GetPassword()
	{
		CString result;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetLanguage(LPCTSTR Language)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Language);
	}
	CString GetLanguage()
	{
		CString result;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetCookieString(LPCTSTR CookieString)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CookieString);
	}
	CString GetCookieString()
	{
		CString result;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetAuthUrl(LPCTSTR AuthUrl)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AuthUrl);
	}
	CString GetAuthUrl()
	{
		CString result;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetExternalPlayer(LPCTSTR exPlayer)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, exPlayer);
	}
	CString GetExternalPlayer()
	{
		CString result;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetServAddress(LPCTSTR exPlayer)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3e9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, exPlayer);
	}
	CString GetServAddress()
	{
		CString result;
		InvokeHelper(0x3ea, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void Play()
	{
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Stop()
	{
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetFullscreen()
	{
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PlayPause(long iAction)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iAction);
	}
	void SetMute(long bMute)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bMute);
	}
	long GetState(long lParam)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lParam);
		return result;
	}
	CString GetVersion()
	{
		CString result;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetChannelList(long iType)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, iType);
		return result;
	}
	CString GetUrlAddress()
	{
		CString result;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void AddFavorite(long channelID, LPCTSTR ChannelName, LPCTSTR SopAddress)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, channelID, ChannelName, SopAddress);
	}
	void DelFavorite(long channelID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, channelID);
	}
	CString GetFavorites()
	{
		CString result;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void InitPlayer()
	{
		InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetPlayerName()
	{
		InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString GetDomain()
	{
		CString result;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetAdsUrl(LPCTSTR adsUrl)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms, adsUrl);
	}
	CString GetRecSchedules()
	{
		CString result;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetRecSchedules(LPCTSTR recSchedules)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms, recSchedules);
	}
	CString GetRecDirectory()
	{
		CString result;
		InvokeHelper(0x76, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetRecDirectory(LPCTSTR recDirectory)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, parms, recDirectory);
	}
	void SetStartPlayer(long bStart)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bStart);
	}


	DECLARE_MESSAGE_MAP()
};
