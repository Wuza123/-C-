#include "speechManage.h"
#include <ctime>

int main() {
	srand((unsigned int)time(NULL));
	speechManage sm;
	//����12����Ա
	//for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++) {
	//	cout << "ѡ�ֱ�ţ�" << it->first << "������" << it->second.m_Name << endl;
	//}
	int choice = 0;
	while (true) {
		sm.showMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.speechStart();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
		}
	}
}