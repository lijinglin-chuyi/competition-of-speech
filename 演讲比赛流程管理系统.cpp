#include <iostream>
#include "speechManager.h"

using namespace std;

int main()
{
	//���������
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	//����12��ѡ�ֵĴ���
	//for (auto it =  sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first << "	������" << it->second.m_Name << "	���䣺" << it->second.m_Score[0] << endl;
	//}
	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2: //�鿴�������
			sm.showRecord();
			break;
		case 3: //��ձ�����¼
			sm.clearRecord();
			break;
		case 0: //�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}