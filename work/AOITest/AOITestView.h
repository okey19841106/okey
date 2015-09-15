
// AOITestView.h : CAOITestView ��Ľӿ�
//

#pragma once

#include "Hexagon.h"

class CAOITestView : public CView
{
protected: // �������л�����
	CAOITestView();
	DECLARE_DYNCREATE(CAOITestView)

// ����
public:
	CAOITestDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CAOITestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

protected:
	okey::Hexagon _hexagon;
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // AOITestView.cpp �еĵ��԰汾
inline CAOITestDoc* CAOITestView::GetDocument() const
   { return reinterpret_cast<CAOITestDoc*>(m_pDocument); }
#endif
