#include <iostream>
#include "speechManager.h"

using namespace std;

int main()
{
	SpeechManager sm;

	int choice = 0;
	while (true)
	{
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			break;
		case 2: //�鿴�������
			break;
		case 3: //��ձ�����¼
			break;
		case 0: //�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	sm.show_Menu();


	system("pause");
	return 0;
}