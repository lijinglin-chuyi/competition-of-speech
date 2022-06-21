#include <iostream>
#include "speechManager.h"

using namespace std;

int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	//测试12名选手的创建
	//for (auto it =  sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first << "	姓名：" << it->second.m_Name << "	年龄：" << it->second.m_Score[0] << endl;
	//}
	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2: //查看往届比赛
			sm.showRecord();
			break;
		case 3: //清空比赛记录
			sm.clearRecord();
			break;
		case 0: //退出系统
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