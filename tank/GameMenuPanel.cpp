#include "pch.h"
#include "GameMenuPanel.h"
#include "Game.h"

CGameMenuPanel::CGameMenuPanel()
{
	m_imgBackground = Image::FromFile(_T("menu_background.png"));

	//�˵�ѡ��˻���ս
	m_menuItems[0].index = 0;
	for (int i = 0; i < 2; ++i)
	{
		TCHAR path[MAX_PATH];
		_stprintf_s(path, _T("menu_1player_%d.png"), i);
		auto imgPtr = Image::FromFile(path);
		RectF rc(0, 300, static_cast<float>(imgPtr->GetWidth()), static_cast<float>(imgPtr->GetHeight()));
		m_menuItems[0].vImageInfoptr.push_back(make_tuple(imgPtr, rc));
	}

	//�˵��˫�˴���ս
	m_menuItems[1].index = 0;
	for (int i = 0; i < 2; ++i)
	{
		TCHAR path[MAX_PATH];
		_stprintf_s(path, _T("menu_1player_%d.png"), i);
		auto imgPtr = Image::FromFile(path);
		RectF rc(600, 200, static_cast<float>(imgPtr->GetWidth()), static_cast<float>(imgPtr->GetHeight()));
		m_menuItems[1].vImageInfoptr.push_back(make_tuple(imgPtr, rc));
		//AfxMessageBox(_T("˫����ս����ʧ��"));
	}
}

CGameMenuPanel::~CGameMenuPanel()
{

}
//�����Լ�
void CGameMenuPanel::Draw(Graphics& gh)const
{
	gh.DrawImage(m_imgBackground, m_rect);//��������ͼƬ
	//���Ӳ˵�
	//auto img1 = get<0>(m_menuItems[0].vImageInfoptr[0]);
	//auto rect1 = get<1>(m_menuItems[0].vImageInfoptr[0]);
	//gh.DrawImage(img1, rect1);
	//auto img2 = get<0>(m_menuItems[1].vImageInfoptr[0]);
	//auto rect2 = get<1>(m_menuItems[1].vImageInfoptr[0]);
	//gh.DrawImage(img2, rect2);
	for (int i=0;i<2;i++)
	{
		auto menuItem = m_menuItems[i];
		auto img = get<0>(menuItem.vImageInfoptr[menuItem.index]);
		auto &rect = get<1>(menuItem.vImageInfoptr[menuItem.index]);
		gh.DrawImage(img, rect);
		
		//AfxMessageBox(_T("�ڼ���ѭ��"));
	}
}

//��������ƶ��¼�
void CGameMenuPanel::OnMouseMove(UINT nFlags, CPoint point)
{
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
	for (auto& menuItem : m_menuItems)
	{
		auto img = get<0>(menuItem.vImageInfoptr[menuItem.index]);
		auto &rect = get<1>(menuItem.vImageInfoptr[menuItem.index]);
		if (rect.Contains(pt))
		{
			menuItem.index = 1;
		}
		else
		{
			menuItem.index = 0;
		}
	}
}

//����������̧���¼�
void CGameMenuPanel::OnLButtonUp(UINT nFlags, CPoint point)
{
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
	{
		auto menuItem = m_menuItems[0];
		auto img = get<0>(menuItem.vImageInfoptr[menuItem.index]);
		auto &rect = get<1>(menuItem.vImageInfoptr[menuItem.index]);
		if (rect.Contains(pt))
		{
			m_pParent->SetStep(CGame::EGameTypeOne2BotMenu);
			return;
		}
	}
	{
		auto menuItem = m_menuItems[1];
		auto img = get<0>(menuItem.vImageInfoptr[menuItem.index]);
		auto &rect = get<1>(menuItem.vImageInfoptr[menuItem.index]);
		if (rect.Contains(pt))
		{
			m_pParent->SetStep(CGame::EGameTypeOne2OneMenu);
			return;
		}
	}
}