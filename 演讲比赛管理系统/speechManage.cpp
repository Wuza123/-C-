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

	this->createSpeaker();//����������Ա

	this->loadRecord();
}

speechManage::~speechManage() {

}

void speechManage::showMenu() {
	cout << "***********************************" << endl;
	cout << "��ӭ�μ��ݽ�����" << endl;
	cout << "1.��ʼ�ݽ�����" << endl;
	cout << "2.�鿴�������" << endl;
	cout << "3.�뿴������¼" << endl;
	cout << "4.�˳�ϵͳ" << endl;
	cout << "***********************************" << endl;
}

void speechManage::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void speechManage::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i<nameSeed.size();i++) {
		string name = "ѡ��";
		name += nameSeed[i];
		speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Scores[j] = 0;
		}
		//����ѡ�ֱ�ţ����뵽v1��
		this->v1.push_back(10001 + i);
		this->m_speaker.insert(make_pair(10001 + i, sp));
	}
}

void speechManage::speechDraw() {
	cout << "��" << this->index << "��ѡ�����ڳ�ǩ" << endl;
	cout << "��ǩ�Ľ������" << endl;
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
	cout << "��" << this->index << "��ѡ�ֱ�����ʼ" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;//����������6��һ��
	vector<int> v_Src;//��������
	if (this->index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//����ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		//����ȥ����߷ֺ���ͷ�
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg = sum / (double)d.size();
		//��ӡƽ����
		//cout << "���:" << *it << "����:" <<this->m_speaker[*it].m_Name << "ƽ����Ϊ:" << avg << endl;
		//�浽speaker��ȥ
		this->m_speaker[*it].m_Scores[this->index - 1] = avg;
		//�浽��ʱ������ȥ
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "���:" << it->second << "����:" << this->m_speaker[it->second].m_Name << "ƽ����Ϊ:" << it->first << endl;
			}
			//ȡ��ǰ����
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
	cout << "******��" << this->index << "�ֱ�������******" << endl;
}

void speechManage::showScore() {
	cout << "*******��" << this->index << "�ֽ������:*****" << endl;
	vector<int> v;
	if (this->index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "���:" << *it << "����:" << this->m_speaker[*it].m_Name << "ƽ����Ϊ:" << this->m_speaker[*it].m_Scores[this->index - 1] << endl;
	}
}

void speechManage::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//������ķ�ʽ���ļ�

	//������д���ļ�
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_speaker[*it].m_Scores[1] << ",";
	}
	ofs << endl;

	ofs.close();

	this->fileIsempty = false;

	cout << "��¼�ѱ��棬�����������" << endl;
}

void speechManage::speechStart() {
	this->speechDraw();//��ǩ
	this->speechContest();//����
	this->showScore();//չʾ���
	this->index++;
	this->speechDraw();//�ڶ��ֳ�ǩ
	this->speechContest();//����
	this->showScore();//չʾ���
	this->saveRecord();//������

	this->initSpeech();

	this->createSpeaker();//����������Ա

	this->loadRecord();
}

void speechManage::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsempty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ���յ����
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsempty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsempty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż���
	string data;
	
	int index = 0;//��¼�ڼ���
	while (ifs>>data) {
		//cout << data << endl;
		int pos = -1;
		int start = 0;
		vector<string> v;
		//��������
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
		cout << "�ļ������ڻ�Ϊ��" << endl;
		return;
	}
	for (int i = 0; i < this->m_Record.size(); i++) {
		cout << "��" << i + 1 << "��"
			<< "�ھ����" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " "
			<< "�Ǿ����" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << " "
			<< "�������" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << endl;

	}
	system("pause");
	system("cls");
}

void speechManage::clearRecord() {
	cout << "�Ƿ����" << endl;
	cout << "1����  2����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);//ɾ�����ؽ�
		ofs.close();

		this->initSpeech();

		this->createSpeaker();//����������Ա

		this->loadRecord();
	}
	system("pause");
}