#include "pch.h"
#include "Game.h"
#include<algorithm>
#define KEYDOWN(vk)(GetAsyncKeyState(vk) & 0x8000)
CGame::CGame()
{
	GameInitOne2Bot();
	m_menuselect.m_pParent = this;
	m_menubackup.m_pParent = this;
}
CGame::~CGame()
{

}
void CGame::SetHandle(HWND hwnd)
{
	m_hwnd = hwnd;
}
bool CGame::EnterFrame(DWORD dwTime)
{
	GameRunDraw();
	GameRunLogic();
	return false;
}

//��������ƶ��¼�
void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
	//ѡ��׶�
	if (m_estep == EGameTypeMenu) {
           m_menuselect.OnMouseMove(nFlags, point);
	}
	else {
		m_menubackup.OnMouseMove(nFlags, point);
	}
}
void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_estep == EGameTypeMenu) {
		m_menuselect.OnLButtonUp(nFlags, point);
	}
	else {
		m_menubackup.OnLButtonUp(nFlags, point);
	}
}

void CGame::SetStep(CGame::EGameType step)
{
	m_estep = step;
	GameInit();
}
void CGame::GameRunDraw()
{
	HDC hdc = ::GetDC(m_hwnd);
	CRect rc;
	GetClientRect(m_hwnd, &rc);

	//˫�����ͼ��
	CDC* dc = CClientDC::FromHandle(hdc);
	CDC m_dcMemory;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* p0ldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());
	gh.Clear(Color::White);
	gh.ResetClip();

	DrawFps(gh);
	//{
	//	CRect rc;
	//	GetClientRect(m_hwnd, rc);
	//	Gdiplus::Image* img = Image::FromFile(_T("menu_background.png"));
	//	gh.DrawImage(img, rc.left, rc.top, rc.Width(), rc.Height());
	//}
	//
	(this->*m_drawFunc[m_estep])(gh);//�����ڴ�
	//m_menu.Draw(gh);
	//m_menuselect.Draw(gh);


	//{
	//	m_map.Draw(gh);//������ͼ
	//	m_player01.Draw(gh);//����̹��
	//	for (auto& blt : m_lstBullets) {
	//		blt.Draw(gh);
	//	}
	//}

	//������ͼ�ο�������Ļ����
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(), m_dcMemory.GetSafeHdc(), 0, 0,SRCCOPY);
	::ReleaseDC(m_hwnd, hdc);
	return;
}

//ѡ��׶�
void CGame::GameRunDrawMenu(Graphics& gh)
{
	m_menuselect.Draw(gh);
}

//�˻���ս���˵��׶�
void CGame::GameRunDrawOne2BotMenu(Graphics& gh)
{
	m_menu.Draw(gh);//������
	m_keymenu01.Draw(gh);//���˵�
}

//�˻���ս
void CGame::GameRunDrawOne2Bot(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_bot.Draw(gh);
	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}
	DrawFps(gh);
}

//�˻���ս����
void CGame::GameRunDrawOne2BotEnd(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_bot.Draw(gh);
	DrawFps(gh);

	if (m_player01.IsBombEnd() || m_bot.IsBombEnd()) {
		m_estep = EGameTypeMenu;
	}
}

//˫�˴�ս�˵��׶�
void CGame::GameRunDrawOne2OneMenu(Graphics& gh)
{
	m_menu.Draw(gh);
	m_keymenu01.Draw(gh);
	m_keymenu02.Draw(gh);
}

//˫�˴�ս
void CGame::GameRunDrawOne2One(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_player02.Draw(gh);

	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}
	DrawFps(gh);
}
//˫�˴�ս����
void CGame::GameRunDrawOne2OneEnd(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_player02.Draw(gh);
	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}
	DrawFps(gh);
	if (m_player01.IsBombEnd() || m_player02.IsBombEnd()) {
		m_estep = EGameTypeMenu;
	}
}
void CGame::GameRunLogic()
{
	(this->*m_logicFunc[m_estep])();
//#define KEYDOWN(vk) (GetAsyncKeyState(vk) & 0x8000)
//	{
//		if (KEYDOWN(VK_LEFT))
//		{
//			m_player01.RotateLeft();
//		}
//		if (KEYDOWN(VK_RIGHT))
//		{
//			m_player01.RotateRight();
//		}
//		if (KEYDOWN(VK_UP))
//		{
//			//̹��ײǽ���
//			{
//				if (m_map.IsHitTheWall(m_player01, true)) {
//					m_player01.ChangeDirection(true);
//				}
//				else {
//					m_player01.Forward();
//				}
//			}
//		}
//		if (KEYDOWN(VK_DOWN))
//		{
//			if (m_map.IsHitTheWall(m_player01, false)) {
//				m_player01.ChangeDirection(true);
//			}
//			else {
//				m_player01.Backward();
//			}
//			
//		}
//		//if (KEYDOWN(VK_LEFT))
//		//{
//		//	m_player01.RotateLeft();
//		//}
//		if (KEYDOWN('M'))
//		{
//			CBullet blt;
//				if (m_player01.Fire(blt)) {
//					m_lstBullets.push_back(blt);
//				}
//		}
//		//�ӵ�ײǽ����
//	}
//	for (auto& blt : m_lstBullets) {
//		m_map.HitWallProcess(blt);
//		blt.Move();
//		if (m_player01.IsHitted(blt));
//		{
//			m_player01.Bomb();
//		}
//		break;
//	}
//	//�Ƴ���ʱ���ӵ�
//	{
//		auto itRemove = std::remove_if(m_lstBullets.begin(), m_lstBullets.end(),
//			[](CBullet& blt)->bool {return blt.IsTimeout(); });
//
//		for (auto it = itRemove; it != m_lstBullets.end(); ++it) {
//			it->SetActive(false);
//			it->GetOwner()->AddBullet(*it);
//		}
//		//�ӱ���ɾ���ӵ�
//		m_lstBullets.erase(itRemove, m_lstBullets.end());
//	}
}

//ѡ��׶ε��߼�����
void CGame::GameRunLogicOnMenu()
{

}

//�˻���ս�˵��׶��߼�����
void CGame::GameRunLogicOnOne2BotMenu()
{
	if (KEYDOWN('M'))
	{
		m_keymenu01.SetStop();
	}
	if (m_keymenu01.GetStop()) {
		SetStep(EGameTypeOne2Bot);
	}
}

//�˻���ս
void CGame::GameRunLogicOnOne2Bot()
{
	RemoveTimeoutBullets();
	for (auto& blt : m_lstBullets) {
		if (m_bot.IsHitted(blt)) {
			m_bot.Bomb();
			m_estep = EGameTypeOne2BotEnd;
			blt.SetActive(false);
		}
		if (m_player01.IsHitted(blt)) {
			m_player01.Bomb();
			m_estep = EGameTypeOne2BotEnd;
			blt.SetActive(false);
		}
		break;
	}
	ProcessHitBullets();
	AI();
	//��������
	{
		if (KEYDOWN(VK_LEFT))
		{
			m_player01.RotateLeft();
		}
		if (KEYDOWN(VK_RIGHT))
		{
			m_player01.RotateRight();
		}
		if (KEYDOWN(VK_UP))
		{
			//̹��ײǽ���
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true);
				}
				else {
					m_player01.Forward();
				}
			}
		}
		if (KEYDOWN(VK_DOWN))
		{
			if (m_map.IsHitTheWall(m_player01, false)) {
				m_player01.ChangeDirection(true);
			}
			else {
				m_player01.Backward();
			}

		}
		//if (KEYDOWN(VK_LEFT))
		//{
		//	m_player01.RotateLeft();
		//}
		if (KEYDOWN('M'))
		{
			CBullet blt;
			if (m_player01.Fire(blt)) {
				m_lstBullets.push_back(blt);
			}
		}
		if (KEYDOWN('I')) {
			//�����ˣ����һ���ڵ�λ��
			int startX, startY, targetX, targetY;
				if (!m_map.FindObjPosition(m_bot, startX, startY)|| !m_map.FindObjPosition(m_player01, targetX, targetY)) {
			return;
		}
		float fDirNext = 0;//��������һ���ķ���
		if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetX)) {
			return;
		}
		PointF ptTankCenter = m_bot.GetCenterPoint();
		PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startX);
		RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

		if (!rc.Contains(ptTankCenter)) {
			m_bot.Forward();
			return;
		}
		else {
			m_bot.SetDirection(fDirNext);
			m_bot.Forward();
		}
		}
		
	}
}

//�˻���ս��������Ϸ�߼�
void CGame::GameRunLogicOnOne2BotEnd()
{
	RemoveTimeoutBullets();
	ProcessHitBullets();

}



//˫�˴�ս�˵��׶���Ϸ�߼�
void CGame::GameRunLogicOnOne2OneMenu()
{
	if (KEYDOWN('M')) {//����M��ֹͣ����
		m_keymenu01.SetStop();
	}
	if (KEYDOWN('Q')) {//����Q��ֹͣ����
		m_keymenu02.SetStop();
	}
	//����������ˡ���ʼ��Ϸ
	if (m_keymenu01.GetStop() && m_keymenu02.GetStop()) {
		SetStep(EGameTypeOne2One);
	}
}

//˫�˴�ս��Ϸ�߼�
void CGame::GameRunLogicOnOne2One()
{
	//��������
	{
		if (KEYDOWN(VK_LEFT))
		{
			m_player01.RotateLeft();
		}
		if (KEYDOWN(VK_RIGHT))
		{
			m_player01.RotateRight();
		}
		if (KEYDOWN(VK_UP))
		{
			//̹��ײǽ���
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true);
				}
				else {
					m_player01.Forward();
				}
			}
		}
		if (KEYDOWN(VK_DOWN))
		{
			if (m_map.IsHitTheWall(m_player01, false)) {
				m_player01.ChangeDirection(false);
			}
			else {
				m_player01.Backward();
			}

		}
		//if (KEYDOWN(VK_LEFT))
		//{
		//	m_player01.RotateLeft();
		//}
		if (KEYDOWN('M'))
		{
			CBullet blt;
			if (m_player01.Fire(blt)) {
				m_lstBullets.push_back(blt);
			}
		}
		//��Ҷ�
		if (KEYDOWN('A')) {
			m_player02.RotateLeft();
		}
		if (KEYDOWN('D')) {
			m_player02.RotateRight();
		}
		if (KEYDOWN('W')) {
			//̹��ײǽ���
			{
				if (m_map.IsHitTheWall(m_player02, true)) {
					m_player02.ChangeDirection(true);
				}
				else {
					m_player02.Forward();
				}
			}
		}
		if (KEYDOWN('S')) {
			//̹��ײǽ���
			{
				if (m_map.IsHitTheWall(m_player02, false)) {
					m_player02.ChangeDirection(false);
				}
				else {
					m_player02.Backward();
				}
			}
		}
		if (KEYDOWN('Q')) {
			CBullet blt;
			if (m_player02.Fire(blt)) {
				m_lstBullets.push_back(blt);
			}
		}
		if (KEYDOWN('Z')) {
			if (m_map.IsCanKillTarget(m_player01, m_player02)) {
				AfxMessageBox(_T("���Դ�"));
			}
		}
	}
	RemoveTimeoutBullets();

	//����ӵ��Ƿ����̹�ˣ�����Ҫʹ̹�˱�ը����Ϸ������
	for (auto& blt : m_lstBullets) {
		if (!blt.IsActive()) {
			continue;
		}
		if (m_player01.IsHitted(blt)) {
			m_player01.Bomb();
			m_estep = EGameTypeOne2OneEnd;
			blt.SetActive(false);
		}
		if (m_player02.IsHitted(blt)) {
			m_player02.Bomb();
			m_estep = EGameTypeOne2OneEnd;
			blt.SetActive(false);
		}
	}

	ProcessHitBullets();
}

//˫�˴�ս����
void CGame::GameRunLogicOnOne2OneEnd()
{
	RemoveTimeoutBullets();
	ProcessHitBullets();
}


bool CGame::GameInit()
{
	srand(GetTickCount64());//���Ե���Gettickcount�����Ա�������ظ�����������
		return (this->*m_initFunc[m_estep])();
}

bool CGame::GameInitMenu()
{
	return true;
}
//�˻���ս�˵��׶γ�ʼ��
bool CGame::GameInitOne2BotMenu()
{
	RECT rc;
	GetWindowRect(m_hwnd, &rc);
	PointF pt;
	pt.X = (rc.left + (rc.right - rc.left) / 2.0f);
	pt.Y = (rc.top + (rc.bottom - rc.top) / 2.0f);
	m_keymenu01.SetCenterPoint(pt);
	m_keymenu01.SetStop(false);
	return true;
}

//�˻���ս��ʼ��
bool CGame::GameInitOne2Bot()
{
	for(; ;)
	{
		m_map.LoadMap();
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("�������1λ��ʧ��"));
			}
			else {
				//�������1�����ĵ㣬�����1���ڵ�ͼ���ӵ����м�λ��
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		//������
		{
			m_bot = CBot(0, 0, _T("tank_bot.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter))
			{
				AfxMessageBox(_T("����Botλ��ʧ��"));
			}
			else
			{
				m_bot.SetCenterPoint(ptCenter);
			}
		}
		//�ӵ�
		m_lstBullets.clear();
		//�ж��Ƿ�Ϸ�
		{
			int startX, startY, targetX, targetY;
			m_map.FindObjPosition(m_bot, startX, startY);
			m_map.FindObjPosition(m_player01, targetX, targetY);
			//if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY));	
			//{
			//	AfxMessageBox(_T("�˻���ս��ʼ����ȡ̹�˵�λ�÷�������"));            
			//}
			VPath path;
			m_map.FindPath(startX, startY, targetX, targetY, path);
			if (!path.empty())
			{
				break;
			}
		}
	}
	return true;
}

//�˻���ս������ʼ��
bool CGame::GameInitOne2BotEnd()
{
	return true;
}

//˫�˴�ս�˵���ʼ��
bool CGame::GameInitOne2OneMenu()
{
	RECT rc;
	GetWindowRect(m_hwnd, &rc);
	PointF pt;
	pt.X = rc.left +m_keymenu01.GetRect().Width / 2.0f+100;
	pt.Y = rc.top + (rc.bottom - rc.top) / 2.0f;
	m_keymenu01.SetCenterPoint(pt);
	m_keymenu01.SetStop(false);

	pt.X = rc.left + m_keymenu01.GetRect().Width / 2.0f - 100;
	pt.Y = rc.top + (rc.bottom - rc.top) / 2.0f;
	m_keymenu01.SetCenterPoint(pt);
	m_keymenu01.SetStop(false);
	return true;
}

//˫�˴�ս��ʼ��
bool CGame::GameInitOne2One()
{
	for (;;) {
		m_map.LoadMap();
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("�������1λ��ʧ��"));
			}
			else {
				//�������1�����ĵ㣬�����1���ڵ�ͼ���ӵ����м�λ��
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		//���2
		{
			m_player02 = CPlayer(0, 0, _T("tank_player2.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("�������02λ��ʧ��"));
			}
			else {
				//�������1�����ĵ㣬�����1���ڵ�ͼ���ӵ����м�λ��
				m_player02.SetCenterPoint(ptCenter);
			}
		}
		//�ӵ�
		m_lstBullets.clear();
		//�ж��Ƿ�Ϸ�
		{
			int startX, startY, targetX, targetY;
			m_map.FindObjPosition(m_player02, startX, startY);
			m_map.FindObjPosition(m_player01, targetX, targetY);
			//if (!m_map.FindObjPosition(m_player02, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY));
			//{
			//	AfxMessageBox(_T("˫�˴�ս��ʼ����ȡ̹�˵�λ�÷�������"));
			//}
			//�ж���������Ƿ������ͨ
			VPath path;
			m_map.FindPath(startX, startY, targetX, targetY, path);
			if (!path.empty())
			{
				break;
			}
		}
	}
	return true;
}

//˫�˴�ս������ʼ��
bool CGame::GameInitOne2OneEnd()
{
	return true;
}

//��fps
void CGame::DrawFps(Graphics& gh)
{
	static int fps = 0;
	m_fps++;
	static DWORD dwLast = GetTickCount64();
	if (GetTickCount64() - dwLast >= 1000)
	{
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount64();
	}
	//���fps
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);
		SolidBrush brush(Color(0x00, 0x00, 0xFF));//��ɫΪ��ɫ
		Gdiplus::Font font(_T("����"), 10.0);//����
		CRect rc;
		::GetClientRect(m_hwnd, &rc);
		//���ֵ�λ�ã��ڴ��ڵ����Ͻ���ʾ
		PointF origin(static_cast<float>(rc.right - 50), static_cast<float>(rc.top + 2));//������ֱ��תΪ������
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}

//�Ƴ���ʱ���ӵ�
void CGame::RemoveTimeoutBullets()
{
	auto itRemove = std::remove_if(m_lstBullets.begin(), m_lstBullets.end(), [](CBullet& blt)->bool {return blt.IsTimeout(); });

	//���ӵ��Ƴ������Ҹ���Ӧ��̹�������ӵ�
	for (auto it = itRemove; it != m_lstBullets.end(); ++it)
	{
		it->SetActive(false);
		it->GetOwner()->AddBullet(*it);
	}
	m_lstBullets.erase(itRemove, m_lstBullets.end());
}

//�ӵ��˶���ά��
void CGame::ProcessHitBullets()
{
	for (auto& blt : m_lstBullets) {
		m_map.HitWallProcess(blt);
		blt.Move();
	}
}

//ά�������Զ� Ѱ·����
void CGame::AI()
{
	static CGameTimer acTimer(-1, 150);
	if (acTimer.IsTimeval()) {
		int startX, startY, targetX, targetY;
		if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
			return;
		}
		float fDirNext = 0;
		if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetY)) {
			return;
		}
		PointF ptTankCenter = m_bot.GetCenterPoint();
		PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startY);
		RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

		if (!rc.Contains(ptTankCenter)) {
			m_bot.Forward();
			return;
		}
		else {
			m_bot.SetDirection(fDirNext);
			float dir;
			if (m_map.IsCanKillTarget(m_bot, m_player01, &dir)) {
				CBullet blt;
				if (m_bot.Fire(blt)) {
					m_lstBullets.push_back(blt);
				}
				return;
			}
			m_bot.Forward();
		}
	}
}