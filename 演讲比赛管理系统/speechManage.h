#pragma once
#include <iostream>
#include <vector>
#include <map>
#include<algorithm>
#include <numeric>
#include<deque>
#include <fstream>
#include "speaker.h"
using namespace std;

class speechManage {
public:
	speechManage();
	//显示菜单
	void showMenu();

	//退出系统
	void exitSystem();

	~speechManage();

	vector<int> v1;//初赛12人容器

	vector<int> v2;//决赛6人容器

	vector<int> vVictory;//获胜者容器

	map<int, speaker> m_speaker;//编号和对应选手

	int index;//比赛轮数

	void speechStart();

	void initSpeech();//初始化容器

	void createSpeaker();//创建比赛人员

	void speechDraw();//抽签

	void speechContest();//比赛

	void showScore();//显示比赛结果

	void saveRecord();//保存数据

	void loadRecord();//读取记录

	bool fileIsempty;//文件是否为空标志

	map<int, vector<string>>m_Record;//存放往届记录容器

	void showRecord();//显示往届记录

	void clearRecord();//清空记录

	void test2();
};
