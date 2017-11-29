//---------------------------------------------------------------------------


#pragma hdrstop

#include <vcl.h>
#include <windows.h>
#include <tchar.h>
#include "ScreenCapture.h"
#include "WndImpl.h"
#include "ScrnCapWnd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxGraphics"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "dxSkinMetropolisDark"
#pragma link "dxSkinsCore"
#pragma link "dxSkinVisualStudio2013Dark"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cxButton1Click(TObject *Sender)
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, _T("ScreenCapture"));
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return ;
	}

    HINSTANCE hInstance = GetModuleHandle("ScreenCaptureProj.exe");
	CWndImpl::SetInstance(hInstance);
	CScrnCapWnd* pScrnCap = new CScrnCapWnd;
	pScrnCap->Create(NULL, _T("ScrnCap"), WS_POPUP|WS_VISIBLE, WS_EX_TOPMOST|WS_EX_TOOLWINDOW, SCREEN_RC);
	UpdateWindow(pScrnCap->GetSafeHwnd());

	CWndImpl::MsgLoop();

	CloseHandle(hMutex);
    if(pScrnCap)
    {
        delete pScrnCap;
        pScrnCap = NULL;
    }
}
//---------------------------------------------------------------------------

