/*
* 1.提供菜单界面与用户交互
* 2.对演讲比赛流程进行控制
* 3.与文件的读写交互
*/

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include <fstream>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

class SpeechManager
{
public:
	SpeechManager();
	~SpeechManager();

	//展示菜单
	void show_Menu();

	//退出系统
	void exitSystem();

	//初始化属性
	//保存第一轮比赛的选手
	vector<int>v1;
	//保存第二轮比赛的选手
	vector<int>v2;
	//保存胜利的选手
	vector<int>vVictory;
	//存放编号以及对应的选手
	map<int, Speaker>m_Speaker;

	//存放比赛轮数
	int m_Index;

	//初始化成员属性
	void initSpeech();

	//创建12名选手
	void createSpeaker();

	//开始比赛，比赛整个流程控制函数
	void startSpeech();

	//比赛抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存数据
	void saveRecord();

	//判断文件是否为空
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>>m_Record;

	//读取往届记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空记录
	void clearRecord();
};

class MyPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

