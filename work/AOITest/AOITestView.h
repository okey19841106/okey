
// AOITestView.h : CAOITestView ��Ľӿ�
//

#pragma once


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
};

#ifndef _DEBUG  // AOITestView.cpp �еĵ��԰汾
inline CAOITestDoc* CAOITestView::GetDocument() const
   { return reinterpret_cast<CAOITestDoc*>(m_pDocument); }
#endif

