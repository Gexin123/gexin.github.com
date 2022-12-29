#pragma once
#include "GameMenuBackground.h"
#include "GameMenuPanel.h"
#include "TankEntry.h"
#include "Bot.h"
#include "Bullet.h"
#include "Player.h"
#include "GameMap.h"
#include "Wall.h"
#include "Bullet.h"
#include "Player.h"
#include "Bot.h"
#include "GameMap.h"
#include "GameMenuPanel.h"
#include "GameMenuPanel2.h"
#include "GameMenuBackground.h"
#include "KeyMenuPlayer01.h"
#include "KeyMenuPlayer02.h"
class CGame
{
public:
	CGame();
	~CGame();
	void SetHandle(HWND hwnd);
	bool EnterFrame(DWORD dwTime);
	void OnMouseMove(UINT nFlags, CPoint point);//��������ƶ��¼�
	void OnLButtonUp(UINT nFlags, CPoint point);//�������̧���¼�
	//��ǰ��Ϸ�����Ľ׶�
	enum EGameType {
		EGameTypeMenu = 0,
		EGameTypeOne2BotMenu,//1
		EGameTypeOne2Bot,//2
		EGameTypeOne2BotEnd,
		EGameTypeOne2OneMenu,
		EGameTypeOne2One,
		EGameTypeOne2OneEnd,
		EGameTypeCount,//7
	};
	//���õ�ǰ��Ϸ�����Ľ׶Σ������ݲ����ʼ��
	void SetStep(CGame::EGameType step);
private:
	HWND m_hwnd;//����
	//��Ϸ��ʼ��
	bool GameInit();
	bool GameInitMenu();
	bool GameInitOne2BotMenu();
	bool GameInitOne2Bot();
	bool GameInitOne2BotEnd();
	bool GameInitOne2OneMenu();
	bool GameInitOne2One();
	bool GameInitOne2OneEnd();
	//����һ������ָ������
	bool (CGame::* m_initFunc[EGameTypeCount])() = {
		&CGame::GameInitMenu,
		&CGame::GameInitOne2BotMenu,
		&CGame::GameInitOne2Bot,
		&CGame::GameInitOne2BotEnd,
		&CGame::GameInitOne2OneMenu,
		&CGame::GameInitOne2One,
		&CGame::GameInitOne2OneEnd
	};
	//��Ϸ��ͼ��������滭��Ϸ�ӵĶ���
	void GameRunDraw();
	void GameRunDrawMenu(Graphics &gh);
	void GameRunDrawOne2BotMenu(Graphics& gh);
	void GameRunDrawOne2Bot(Graphics& gh);
	void GameRunDrawOne2BotEnd(Graphics& gh);
	void GameRunDrawOne2OneMenu(Graphics& gh);
	void GameRunDrawOne2One(Graphics& gh);
	void GameRunDrawOne2OneEnd(Graphics& gh);
	void(CGame::* m_drawFunc[EGameTypeCount])(Graphics&) = {
		&CGame::GameRunDrawMenu,
		&CGame::GameRunDrawOne2BotMenu,
		&CGame::GameRunDrawOne2Bot,
		&CGame::GameRunDrawOne2BotEnd,
		&CGame::GameRunDrawOne2OneMenu,
		&CGame::GameRunDrawOne2One,
		&CGame::GameRunDrawOne2OneEnd
	};
	//��Ϸ�߼�����ά���ӵ��������ˣ����̹�˵�״̬
	void GameRunLogic();
	void GameRunLogicOnMenu();//ѡ��׶�
	void GameRunLogicOnOne2BotMenu();//�˻���ս�˵�
	void GameRunLogicOnOne2Bot();//�˻���ս
	void GameRunLogicOnOne2BotEnd();//�˻���վ����
	void GameRunLogicOnOne2OneMenu();//˫�˴�ս�˵�
	void GameRunLogicOnOne2One();//˫�˴�ս
	void GameRunLogicOnOne2OneEnd();//˫�˴�ս����
	void(CGame::* m_logicFunc[EGameTypeCount])() = {
		&CGame::GameRunLogicOnMenu,
		&CGame::GameRunLogicOnOne2BotMenu,
		&CGame::GameRunLogicOnOne2Bot,
		&CGame::GameRunLogicOnOne2BotEnd,
		&CGame::GameRunLogicOnOne2OneMenu,
		&CGame::GameRunLogicOnOne2One,
		&CGame::GameRunLogicOnOne2OneEnd
	};
private:
	void RemoveTimeoutBullets();
	void ProcessHitBullets();
	void AI();
	void DrawFps(Graphics& gh);
private:
	int m_fps{ 0 };
	EGameType m_estep{ EGameTypeMenu };
	CPlayer m_player01;
	CPlayer m_player02;
	CBot m_bot;
	std::list<CBullet>m_lstBullets;
	CGameMap m_map{ 10,10,780,580 };
	CGameMenuPanel m_menuselect;
	CGameMenuBackground m_menu;
	CGameMenuPanel2 m_menubackup;//���ز˵�
	CKeyMenuPlayer01 m_keymenu01;
	CKeyMenuPlayer02 m_keymenu02;


	//CGameMenuPanel m_menuSelect;
	//CGameMenuBackground m_menu;
	//��Ϸ�Ļ�ͼ
	//void DrawFps(Graphics& gh);
	//	int m_fps{ 0 };

	//CPlayer m_player01{ 100,100,_T("tank_player1.png") };
	//CPlayer m_player02{ 200,100,_T("tank_player2.png") };
	//CBot m_bot{ 300,200,_T("tank_bot.png") };
	//std::list<CBullet>m_lstBullets;//����һ���б��������Ѿ�����������ӵ�
	//CGameMap m_map{ 10,10,780,580 };//��ʼ����һ����ͼ����
	//bool CGame::GameInitOne2Bot();//��Ϸ��ʼ�����˻���ս
};

