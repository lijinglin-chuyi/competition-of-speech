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
};
