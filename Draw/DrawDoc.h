
// DrawDoc.h: CDrawDoc 类的接口
//


#pragma once
#include "../DB/DBDoc.h"

#include "ElementColor.h"
#include "ElementType.h"
#include "Element.h"

#include <list>
typedef std::list<CPElement>::const_iterator SketchInerator;
class CDrawDoc : public CDBDoc
{
protected: // 仅从序列化创建
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	SketchInerator begin()const { return std::begin(m_Sketch); }
	SketchInerator end()const { return std::end(m_Sketch); }
	void AddElement(const CPElement& pElement);
	void DeleteElement(const CPElement& pElement);
	CPElement FindElement(const CPoint& point)const
	{
		for (auto& pElement : m_Sketch)
			if (pElement->GetEnclosingRect().PtInRect(point))
				return pElement;
		return nullptr;
	}
private:
	int m_PenStyle;
	ElementType m_Element;
	ElementColor m_Color;
	std::list<CPElement>m_Sketch;
	
public:
	int GetPenStyle()const { return m_PenStyle; }
	ElementType GetElementType()const { return m_Element; }
	ElementColor GetElementColor()const { return m_Color; }
protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnTest();
	afx_msg void OnTest1Ontest();
	afx_msg void OnColorBlack();
	afx_msg void OnColorBlue();
	afx_msg void OnColorGreen();
	afx_msg void OnColorRed();
	afx_msg void OnElementLine();
	afx_msg void OnElementDefault();
	afx_msg void OnElementRectangle();

	afx_msg void OnRedo();//回头应该把editredo和redo用一个函数,消息来合并起来
	afx_msg void OnEditRedo();
	afx_msg void OnUndo();
	afx_msg void OnEditUndo();

	virtual void SetTitle(LPCTSTR lpszTitle);
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementDefault(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
	afx_msg void OnStructPropMaterial();
	afx_msg void OnStructPropSection();
};
