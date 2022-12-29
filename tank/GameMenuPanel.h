#pragma once
#include<tuple>
#include<vector>
#include "GameEntry.h"
using namespace std;

class CGame;
class CGameMenuPanel:public CGameEntryMoveable
{
public:
	CGameMenuPanel();
	~CGameMenuPanel();

	void SetParent(CGame* g)
	{
		m_pParent = g;
	};
	CGame *m_pParent{ nullptr };
	virtual void Draw(Graphics& gh)const;//���Լ� 
	RectF m_rect{ 0,0,800,600 };
	void OnMouseMove(UINT nFlags, CPoint point);//��������ƶ��¼�
	void OnLButtonUp(UINT nFlags, CPoint point);//�������̧���¼�
	Image *m_imgBackground;
	struct {
		vector<tuple<Image*, RectF>>vImageInfoptr;//ͼƬ��ָ��ͷ�Χ
		int index;
	}m_menuItems[2];
};

