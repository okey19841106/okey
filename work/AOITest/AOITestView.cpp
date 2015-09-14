
// AOITestView.cpp : CAOITestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "AOITest.h"
#endif

#include "AOITestDoc.h"
#include "AOITestView.h"

#include "Hexagon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAOITestView

IMPLEMENT_DYNCREATE(CAOITestView, CView)

BEGIN_MESSAGE_MAP(CAOITestView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CAOITestView ����/����

CAOITestView::CAOITestView()
{
	// TODO: �ڴ˴���ӹ������

}

CAOITestView::~CAOITestView()
{
}

BOOL CAOITestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CAOITestView ����

void CAOITestView::OnDraw(CDC* pDC)
{
	CAOITestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	_hexagon.Draw(pDC);
}

void CAOITestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAOITestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAOITestView ���

#ifdef _DEBUG
void CAOITestView::AssertValid() const
{
	CView::AssertValid();
}

void CAOITestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAOITestDoc* CAOITestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAOITestDoc)));
	return (CAOITestDoc*)m_pDocument;
}
#endif //_DEBUG


// CAOITestView ��Ϣ�������
