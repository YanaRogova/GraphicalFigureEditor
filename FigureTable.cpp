#include "pch.h"
#include "FigureTable.h"

CFigureTable::CFigureTable()
{
}

CFigureTable::~CFigureTable()
{
}

void CFigureTable::UpdateListView(CEditorView* pView)
{
	m_List2.DeleteAllItems();
	CString str;
	for (int i = 0; i < pView->m_GraphicalWindow.m_Figure.size(); i++)
	{
		str.Format(L"%d", i + 1);
		int Index = m_List2.InsertItem(0, str);
		m_List2.SetItemText(Index, 1, pView->m_GraphicalWindow.m_Figure[i]->GetName());
		m_List2.SetItemText(Index, 2, pView->m_GraphicalWindow.m_Figure[i]->GetID());
		m_List2.SetItemText(Index, 3, pView->m_GraphicalWindow.m_Figure[i]->GetFigure());
		m_List2.SetItemText(Index, 4, pView->m_GraphicalWindow.m_Figure[i]->GetCenter());
		m_List2.SetItemText(Index, 5, pView->m_GraphicalWindow.m_Figure[i]->GetCoordinates());
		m_List2.SetItemText(Index, 6, pView->m_GraphicalWindow.m_Figure[i]->GetAngle());
	}
}

