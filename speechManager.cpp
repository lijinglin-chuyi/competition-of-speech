#include "speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();
}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::show_Menu()
{
	cout << "***********************************" << endl;
	cout << "******  欢迎参加演讲比赛  *********" << endl;
	cout << "******  1.开始演讲比赛    *********" << endl;
	cout << "******  2.查看往届比赛    *********" << endl;
	cout << "******  3.清空比赛记录    *********" << endl;
	cout << "******  0.退出比赛程序    *********" << endl;
	cout << "***********************************" << endl;
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear(); 
	this->m_Speaker.clear();
	this->m_Record.clear();

	//初始化比赛轮数
	this->m_Index = 1;
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		//创建具体选手
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		//创建选手编号，并且放到v1容器中
		this->v1.push_back(i + 10001);
		
		//选手编号以及对应选手放到map容器中
		this->m_Speaker.insert(pair<int, Speaker>(i + 10001, sp));

		
	}

}

void SpeechManager::startSpeech()
{
	//第一轮开始比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();
	//第二轮比赛开始
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showScore();

	//4.保存结果
	this->saveRecord();
	cout << "本届比赛已保存" << endl;

	//一届比赛结束后应该重置所有容器，重新初始化
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	system("pause");
	
	system("cls");

}

void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for_each(v1.begin(), v1.end(), MyPrint());
		cout << endl;
	}
	else
	{
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for_each(v2.begin(), v2.end(), MyPrint());
		cout << endl;
	}
	cout << "--------------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//比赛
void SpeechManager::speechContest()
{
	cout << "第" << this->m_Index << "轮比赛正式开始" << endl;
	cout << "---------------------------------------" << endl;

	//准备临时容器，存放小组成绩,排序规则为降序
	multimap<double, int,greater<double>> groupScore;

	//记录小组人数
	int num = 0;

	vector<int>v_Src;//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		deque<double>d;
		//10个评委打分
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //60-100
			d.push_back(score);
			//cout << score << " ";
		}
		//cout << endl;
		//排序删除头尾
		sort(d.begin(), d.end(),greater<double>());
		d.pop_back();//去除最低分
		d.pop_front();//去除最高分
		double sum = accumulate(d.begin(),d.end(),0.0f);//总分
		double avg = sum / (double)d.size();//平均分

		//打印平均分
		//cout << "编号：" << *it << "姓名：" << this->m_Speaker[*it].m_Name << "获取平均分：" << avg << endl;
		//将平均分放到map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(pair<double, int>(avg, *it));//分数为键值，自动降序，val为编号
		if (num%6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_Speaker[it->second].m_Name << "成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}
			//取走前三名
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
			groupScore.clear();//小组容器清空
			cout << endl;
		}
		

		
	}
	cout << "----------------------" << "第" << this->m_Index << "轮比赛完毕---------------------" << endl;
}

//显示得分
void SpeechManager::showScore()
{
	cout << "---------------------第" << this->m_Index << "轮晋级选手信息-------------------" << endl;
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
		cout << "编号：" << *it << "	姓名：" << this->m_Speaker[*it].m_Name << "	得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	show_Menu();
}

//保存数据
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//以追加方式写文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已保存" << endl;
	this->fileIsEmpty = false;
}

//读取往届数据
void SpeechManager::loadRecord()
{
	ifstream ifs;
	int index = 1;//默认1届
	ifs.open("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//文件清空情况
	char ch;
	//读取一个字符
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		ifs.close();
		this->fileIsEmpty = true;
		return;
	}

	//文件存在且不为空
	//将读取走的单个字符返回来
	ifs.putback(ch);
	string data;
	while (ifs >> data)
	{
		vector<string>v;
		//cout << data << endl;
		int pos = -1;//查到，位置的变量
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//没有找到或者寻找完毕退出循环
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
	//	cout << it->first << "冠军编号：" << it->second[0] << " 分数：" << it->second[1] << endl;
	//}
}

//显示往届记录
void SpeechManager::showRecord()
{
	//判断文件是否为空
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		//创建起始迭代器
		auto it = m_Record.begin();
		for (int i = 0; i < m_Record.size(); i++, it++)
		{
			vector<string> temp = it->second;
			cout << "第" << i + 1 << "届 "
				<< " 冠军编号：" << temp[0] << "得分：" << temp[1]
				<< " 亚军编号：" << temp[2] << "得分：" << temp[3]
				<< " 季军编号：" << temp[4] << "得分：" << temp[5] << endl;

		}
	}
	system("pause");
	system("cls");
}

//清空文件
void SpeechManager::clearRecord()
{
	cout << "是否确定清空文件？" << endl;
	cout << "1. 是" << endl;
	cout << "2. 否" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();

		//重新初始化12名选手
		this->createSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}