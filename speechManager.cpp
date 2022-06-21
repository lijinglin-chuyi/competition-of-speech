#include "speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	//���������¼
	this->loadRecord();
}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::show_Menu()
{
	cout << "***********************************" << endl;
	cout << "******  ��ӭ�μ��ݽ�����  *********" << endl;
	cout << "******  1.��ʼ�ݽ�����    *********" << endl;
	cout << "******  2.�鿴�������    *********" << endl;
	cout << "******  3.��ձ�����¼    *********" << endl;
	cout << "******  0.�˳���������    *********" << endl;
	cout << "***********************************" << endl;
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear(); 
	this->m_Speaker.clear();
	this->m_Record.clear();

	//��ʼ����������
	this->m_Index = 1;
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		//��������ѡ��
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		//����ѡ�ֱ�ţ����ҷŵ�v1������
		this->v1.push_back(i + 10001);
		
		//ѡ�ֱ���Լ���Ӧѡ�ַŵ�map������
		this->m_Speaker.insert(pair<int, Speaker>(i + 10001, sp));

		
	}

}

void SpeechManager::startSpeech()
{
	//��һ�ֿ�ʼ����
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();
	//�ڶ��ֱ�����ʼ
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showScore();

	//4.������
	this->saveRecord();
	cout << "��������ѱ���" << endl;

	//һ�����������Ӧ�������������������³�ʼ��
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	system("pause");
	
	system("cls");

}

void SpeechManager::speechDraw()
{
	cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->m_Index == 1)
	{
		//��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for_each(v1.begin(), v1.end(), MyPrint());
		cout << endl;
	}
	else
	{
		//�ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for_each(v2.begin(), v2.end(), MyPrint());
		cout << endl;
	}
	cout << "--------------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//����
void SpeechManager::speechContest()
{
	cout << "��" << this->m_Index << "�ֱ�����ʽ��ʼ" << endl;
	cout << "---------------------------------------" << endl;

	//׼����ʱ���������С��ɼ�,�������Ϊ����
	multimap<double, int,greater<double>> groupScore;

	//��¼С������
	int num = 0;

	vector<int>v_Src;//����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		deque<double>d;
		//10����ί���
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //60-100
			d.push_back(score);
			//cout << score << " ";
		}
		//cout << endl;
		//����ɾ��ͷβ
		sort(d.begin(), d.end(),greater<double>());
		d.pop_back();//ȥ����ͷ�
		d.pop_front();//ȥ����߷�
		double sum = accumulate(d.begin(),d.end(),0.0f);//�ܷ�
		double avg = sum / (double)d.size();//ƽ����

		//��ӡƽ����
		//cout << "��ţ�" << *it << "������" << this->m_Speaker[*it].m_Name << "��ȡƽ���֣�" << avg << endl;
		//��ƽ���ַŵ�map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(pair<double, int>(avg, *it));//����Ϊ��ֵ���Զ�����valΪ���
		if (num%6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_Speaker[it->second].m_Name << "�ɼ���" << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}
			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
			}
			groupScore.clear();//С���������
			cout << endl;
		}
		

		
	}
	cout << "----------------------" << "��" << this->m_Index << "�ֱ������---------------------" << endl;
}

//��ʾ�÷�
void SpeechManager::showScore()
{
	cout << "---------------------��" << this->m_Index << "�ֽ���ѡ����Ϣ-------------------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "��ţ�" << *it << "	������" << this->m_Speaker[*it].m_Name << "	�÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	show_Menu();
}

//��������
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӷ�ʽд�ļ�
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�ѱ���" << endl;
	this->fileIsEmpty = false;
}

//��ȡ��������
void SpeechManager::loadRecord()
{
	ifstream ifs;
	int index = 1;//Ĭ��1��
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//�ļ�������
	char ch;
	//��ȡһ���ַ�
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		this->fileIsEmpty = true;
		return;
	}

	//�ļ������Ҳ�Ϊ��
	//����ȡ�ߵĵ����ַ�������
	ifs.putback(ch);
	string data;
	while (ifs >> data)
	{
		vector<string>v;
		//cout << data << endl;
		int pos = -1;//�鵽��λ�õı���
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//û���ҵ�����Ѱ������˳�ѭ��
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}
		this->m_Record.insert(pair<int,vector<string>>(index,v));
		index++;
	}
	ifs.close();
	//for (map<int,vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	//{
	//	cout << it->first << "�ھ���ţ�" << it->second[0] << " ������" << it->second[1] << endl;
	//}
}

//��ʾ�����¼
void SpeechManager::showRecord()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		//������ʼ������
		auto it = m_Record.begin();
		for (int i = 0; i < m_Record.size(); i++, it++)
		{
			vector<string> temp = it->second;
			cout << "��" << i + 1 << "�� "
				<< " �ھ���ţ�" << temp[0] << "�÷֣�" << temp[1]
				<< " �Ǿ���ţ�" << temp[2] << "�÷֣�" << temp[3]
				<< " ������ţ�" << temp[4] << "�÷֣�" << temp[5] << endl;

		}
	}
	system("pause");
	system("cls");
}

//����ļ�
void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "1. ��" << endl;
	cout << "2. ��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();

		//���³�ʼ��12��ѡ��
		this->createSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}