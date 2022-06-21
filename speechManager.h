/*
* 1.�ṩ�˵��������û�����
* 2.���ݽ��������̽��п���
* 3.���ļ��Ķ�д����
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

	//չʾ�˵�
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������
	//�����һ�ֱ�����ѡ��
	vector<int>v1;
	//����ڶ��ֱ�����ѡ��
	vector<int>v2;
	//����ʤ����ѡ��
	vector<int>vVictory;
	//��ű���Լ���Ӧ��ѡ��
	map<int, Speaker>m_Speaker;

	//��ű�������
	int m_Index;

	//��ʼ����Ա����
	void initSpeech();

	//����12��ѡ��
	void createSpeaker();

	//��ʼ�����������������̿��ƺ���
	void startSpeech();

	//������ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//��������
	void saveRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>>m_Record;

	//��ȡ�����¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//��ռ�¼
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

