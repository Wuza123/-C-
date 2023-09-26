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
	//��ʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();

	~speechManage();

	vector<int> v1;//����12������

	vector<int> v2;//����6������

	vector<int> vVictory;//��ʤ������

	map<int, speaker> m_speaker;//��źͶ�Ӧѡ��

	int index;//��������

	void speechStart();

	void initSpeech();//��ʼ������

	void createSpeaker();//����������Ա

	void speechDraw();//��ǩ

	void speechContest();//����

	void showScore();//��ʾ�������

	void saveRecord();//��������

	void loadRecord();//��ȡ��¼

	bool fileIsempty;//�ļ��Ƿ�Ϊ�ձ�־

	map<int, vector<string>>m_Record;//��������¼����

	void showRecord();//��ʾ�����¼

	void clearRecord();//��ռ�¼

	void test2();
};
