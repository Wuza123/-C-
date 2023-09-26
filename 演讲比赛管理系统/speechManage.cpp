#include "speechManage.h"

void speechManage::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	this->index = 1;
	this->m_Record.clear();
}

speechManage::speechManage() {
	this->initSpeech();

	this->createSpeaker();//创建比赛人员

	this->loadRecord();
}

speechManage::~speechManage() {

}

void speechManage::showMenu() {
	cout << "***********************************" << endl;
	cout << "欢迎参加演讲比赛" << endl;
	cout << "1.开始演讲比赛" << endl;
	cout << "2.查看往届比赛" << endl;
	cout << "3.请看比赛记录" << endl;
	cout << "4.退出系统" << endl;
	cout << "***********************************" << endl;
}

void speechManage::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void speechManage::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i<nameSeed.size();i++) {
		string name = "选手";
		name += nameSeed[i];
		speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Scores[j] = 0;
		}
		//创建选手编号，存入到v1中
		this->v1.push_back(10001 + i);
		this->m_speaker.insert(make_pair(10001 + i, sp));
	}
}

void speechManage::speechDraw() {
	cout << "第" << this->index << "轮选手正在抽签" << endl;
	cout << "抽签的结果如下" << endl;
	if (this->index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
}

void speechManage::speechContest() {
	cout << "第" << this->index << "轮选手比赛开始" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;//比赛人数，6人一组
	vector<int> v_Src;//比赛容器
	if (this->index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//遍历选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		//排序，去掉最高分和最低分
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg = sum / (double)d.size();
		//打印平均分
		//cout << "编号:" << *it << "姓名:" <<this->m_speaker[*it].m_Name << "平均分为:" << avg << endl;
		//存到speaker中去
		this->m_speaker[*it].m_Scores[this->index - 1] = avg;
		//存到临时数组中去
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号:" << it->second << "姓名:" << this->m_speaker[it->second].m_Name << "平均分为:" << it->first << endl;
			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++) {
				if (this->index == 1) {
					v2.push_back((*it).second);
					count++;
				}
				else {
					vVictory.push_back((*it).second);
					count++;
				}
			}
			groupScore.clear();
		}
	}
	cout << "******第" << this->index << "轮比赛结束******" << endl;
}

void speechManage::showScore() {
	cout << "*******第" << this->index << "轮结果如下:*****" << endl;
	vector<int> v;
	if (this->index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号:" << *it << "姓名:" << this->m_speaker[*it].m_Name << "平均分为:" << this->m_speaker[*it].m_Scores[this->index - 1] << endl;
	}
}

void speechManage::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用输出的方式打开文件

	//将数据写入文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_speaker[*it].m_Scores[1] << ",";
	}
	ofs << endl;

	ofs.close();

	this->fileIsempty = false;

	cout << "记录已保存，本届比赛结束" << endl;
}

void speechManage::speechStart() {
	this->speechDraw();//抽签
	this->speechContest();//比赛
	this->showScore();//展示结果
	this->index++;
	this->speechDraw();//第二轮抽签
	this->speechContest();//比赛
	this->showScore();//展示结果
	this->saveRecord();//保存结果

	this->initSpeech();

	this->createSpeaker();//创建比赛人员

	this->loadRecord();
}

void speechManage::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsempty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件清空的情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空" << endl;
		this->fileIsempty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsempty = false;
	ifs.putback(ch);//将上面读取的单个字符放回来
	string data;
	
	int index = 0;//记录第几届
	while (ifs>>data) {
		//cout << data << endl;
		int pos = -1;
		int start = 0;
		vector<string> v;
		//解析数据
		while (1) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void speechManage::showRecord() {
	if (this->fileIsempty) {
		cout << "文件不存在或为空" << endl;
		return;
	}
	for (int i = 0; i < this->m_Record.size(); i++) {
		cout << "第" << i + 1 << "届"
			<< "冠军编号" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
			<< "亚军编号" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " "
			<< "季军编号" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << endl;

	}
	system("pause");
	system("cls");
}

void speechManage::clearRecord() {
	cout << "是否清空" << endl;
	cout << "1、是  2、否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);//删除并重建
		ofs.close();

		this->initSpeech();

		this->createSpeaker();//创建比赛人员

		this->loadRecord();
	}
	system("pause");
}