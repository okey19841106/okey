
// AOITestView.cpp : CAOITestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CAOITestView 构造/析构

CAOITestView::CAOITestView()
{
	// TODO: 在此处添加构造代码

}

CAOITestView::~CAOITestView()
{
}

BOOL CAOITestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CAOITestView 绘制

void CAOITestView::OnDraw(CDC* pDC)
{
	CAOITestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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


// CAOITestView 诊断

#ifdef _DEBUG
void CAOITestView::AssertValid() const
{
	CView::AssertValid();
}

void CAOITestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAOITestDoc* CAOITestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAOITestDoc)));
	return (CAOITestDoc*)m_pDocument;
}
#endif //_DEBUG


// CAOITestView 消息处理程序
