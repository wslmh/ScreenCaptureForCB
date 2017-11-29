//---------------------------------------------------------------------------

#ifndef ScrnCapWndH
#define ScrnCapWndH
//---------------------------------------------------------------------------
#include "WndImpl.h"
#include "DrawGraph.h"
#include "ToolWnd.h"
#include <vector>
#include <stack>

typedef enum
{
	ACTION_CHOOSING,
	ACTION_ADJUST,
	ACTION_RECT,
	ACTION_ELLIPSE,
	ACTION_ARROW,
	ACTION_SCRAWL,
	ACTION_HIGHLIGHT,
	ACTION_SAVE,
	ACTION_UNDO,
	ACTION_REDO
}ACTION;

//���췽��L:left,R:right,U:up,D:down
typedef enum
{
	STRETCH_NO,
	STRETCH_L,
	STRETCH_U,
	STRETCH_R,
	STRETCH_D,
	STRETCH_LU,
	STRETCH_RU,
	STRETCH_LD,
	STRETCH_RD
}STRETCH;

class CScrnCapWnd: public CWndImpl
{
public:
	CScrnCapWnd();
	~CScrnCapWnd();

public:
	LPCTSTR   GetWindowClassName() const;
	void Initialize(void);

	LRESULT ProcessMsg(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//sys msg processing
	LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDbClk(WPARAM wParam, LPARAM lParam);
	LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);

	//user msg processing
	LRESULT OnRecap(WPARAM wParam, LPARAM lParam);
	LRESULT OnSaveImage(WPARAM wParam, LPARAM lParam);
	LRESULT OnRectangle(WPARAM wParam, LPARAM lParam);
	LRESULT OnEllipse(WPARAM wParam, LPARAM lParam);
	LRESULT OnArrowLine(WPARAM wParam, LPARAM lParam);
	LRESULT OnScrawl(WPARAM wParam, LPARAM lParam);
	LRESULT OnHighlight(WPARAM wParam, LPARAM lParam);
	LRESULT OnUndo(WPARAM wParam, LPARAM lParam);
	LRESULT OnRedo(WPARAM wParam, LPARAM lParam);
	LRESULT OnCancel(WPARAM wParam, LPARAM lParam);
	LRESULT OnFinish(WPARAM wParam, LPARAM lParam);

	LRESULT OnPenSizeChange(WPARAM wParam, LPARAM lParam);
	LRESULT OnPenColorChange(WPARAM wParam, LPARAM lParam);

public:
	void InitializeDC(void);

	// @brief  ��������������
	void CreateToolWnd(void);
	// @brief  ������ɫѡ���
	void CreateColorWnd(BOOL bShow);
	// @brief  �Զ�ʶ�𴰿�
	BOOL AutoRecognizeWnd(const POINT& ptMousePos);

	// @brief  ������ѡ����
	void Stretch_Adjust(const STRETCH& emStretch,RectX& rcStretch,int cxOffset,int cyOffset);
	void Drag_Adjust(RectX& rcDrag,int cxOffset,int cyOffset);
	BOOL Adjust(int cxOffset,int cyOffset);

	// @brief  ��������������λ��
	void AdjustToolPos(void);

	void Enlarge(RectX& rcEnlarge, int iSpeed);

	//@brief  ��m_hMemPaintDC�ϻ�����ѡ(������)����
	void PaintSelRgn(void);

	void Undo(void);
	void Redo(void);

	BOOL Save(void);

	void Finish(void);

	void ClearUndoStack(void);
	void ClearRedoStack(void);

	//@brief  API rewriting
	static BOOL BitBltEx(HDC hDestDC,RectX rc,HDC hSrcDC, POINT ptStart, DWORD dwRop);
	static int  DrawTextEx(HDC hDC, const AnsiString& strTx, RectX rc, UINT uFormat);

	static BOOL RectangleX(HDC hDC, RectX rc);


	//Painting

	//@brief  �ھ��ε�ÿ�������е�Ͷ��㻭ʵ��С����
	static void DrawAdjustSquare(HDC hDC,const RectX& rc, const int iSide);
	static void DrawRect(HDC hDC, const RectX& rcDraw, const int& iPenWidth, const int& iPenStyle);
	static void DrawSizeTx(HDC hDC, const RectX& rcSel);

	//@brief  ö�����д���
	static BOOL CALLBACK EnumGrandChildWindowsProc(HWND hwnd,LPARAM lParam);
	static BOOL CALLBACK EnumChildWindowsProc(HWND hwnd,LPARAM lParam);
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam);
	static BOOL InsertWndRect(HWND hwnd);
	static std::vector<RectX> GetAllWndRect();

	static void ConvertToGrayBitmap(HBITMAP hSourceBmp,HDC sourceDC);


	//@brief  �������
	void SetScrnCursor(HWND hWnd, const RectX& rcCursorLie, const BOOL& bLButtonDown, const ACTION& m_emAction, STRETCH& emStretch);
	static void SetStretchCursor(const RectX& rc,const POINT& ptPos, STRETCH& emStretch);
	//@brief  �������λ�û����������
	static STRETCH GetStrechDrct(const RectX& rc,const POINT& ptPos);


	//�������
	static BOOL GetSaveFilePath(HINSTANCE hInstance,HWND hWnd, TCHAR* szFilePath, TCHAR* szFileTitle,int& nFilterIndex);
	static void GetCurTimeString(AnsiString& strCurDateTime);
	static void SetDefFileName(AnsiString& strDefName);

	static BOOL GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	/**
	 * @brief  ��HBITMAP����Ϊָ����ʽͼƬ
	 * @param  hImage[IN]��λͼ���
	 * @param  pFileName[IN]��ָ��������·����ͼƬ��
	 * @param  strFormat[IN]��ͼƬ��ʽ������"image/png"
	 * @return �����Ƿ�ɹ�
	**/
	static BOOL SaveAsPic(HBITMAP hImage, const AnsiString& strFileName, const AnsiString& strFormat);

	//@brief  ����������
	static BOOL CopyBMP2Clipboard(HBITMAP hBMP,HWND hWnd);



private:

	HDC  m_hClientDC;       //��ĻDC��չʾ��������
	HDC  m_hMemPaintDC;     //����DC����Ҫ��m_hClientDC�ṩ����
	HDC  m_hMemDC;          //��m_hMemPaintDC�ṩ��ɫ����
	HDC  m_hMemCurScrnDC;   //����m_hMemPaintDC�Ĵ�������

	HBITMAP m_hScrnBMP, m_hOldScrnBMP;       //����BMP
	HBITMAP m_hGrayBMP, m_hOldGrayBMP;
	HBITMAP m_hGrayBMP2, m_hOldGrayBMP2;
	HBITMAP m_hCurScrnBMP, m_hOldCurScrnBMP; //��Ӧm_hMemCurScrnDC

	HBITMAP m_hGraphBMP, m_hOldGraphBMP;     //����˫���廭��Ƥ�����/��Բ/��ͷ


	HBITMAP m_hCurBMP, m_hOldCurBMP;         //ѹ��ջ��������Ļ
	std::stack<HBITMAP> m_stackUndoGraph;    //"����"ջ
	std::stack<HBITMAP> m_stackRedoGraph;    //"�ָ�"ջ


	POINT m_ptStart;
	POINT m_ptMoving;

	BOOL m_bLBtnDown;    //�������
	BOOL m_bStretching;  //�Ƿ���������

	ACTION m_emAction;    //�û�����
	STRETCH m_emStrech;   //���췽�򣬵��ҽ���m_emActionΪACTION_ADJUST

	RectX m_rcSel;       //��ѡ�������򣨽���������ʼ��Ϊ��׼���Σ�
	RectX m_rcChoosing;  //��̬����
	RectX m_rcSelRedo;   //��������ָ�����ǰ�Ľ�ͼ����

	IGraph *m_pGraph;
	CToolWnd* m_pToolWnd;
	CColorWnd* m_pColorWnd;

	int m_nPenWidth;
	COLORREF m_dwPenColor;

private:
	static HCURSOR m_hCursor;
	static std::vector<RectX> m_vecAllWndRect;
};

#endif
