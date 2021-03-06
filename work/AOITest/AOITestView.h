
// AOITestView.h : CAOITestView 类的接口
//

#pragma once

#include "Hexagon.h"

class CAOITestView : public CView
{
protected: // 仅从序列化创建
	CAOITestView();
	DECLARE_DYNCREATE(CAOITestView)

// 特性
public:
	CAOITestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CAOITestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // AOITestView.cpp 中的调试版本
inline CAOITestDoc* CAOITestView::GetDocument() const
   { return reinterpret_cast<CAOITestDoc*>(m_pDocument); }
#endif

