#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#define MAXNUM 10


using namespace std;

//�����ķ��ṹ��
struct rule {
	char ssymbol;//���ս��
	string tuidao;//������Ƶ�ʽ
	int loc;//���λ��
};

struct status {
	vector<rule>  rules;
	int state;//
};

vector<rule> rulelist;
char startlist[MAXNUM] = { "#" };
string endlist[MAXNUM] = { "#" };
string list[MAXNUM] = { "#" };
vector<status> statuslist;
//vector<vector<rule>>  status;
vector<vector<int>> table;



int snum;//״̬��
int endnum = 0;
int startnum = 0;//���ս������
int num = 0;

//search��������startlist�в��ҷ��ս����λ�ã�����λ��
int search(char s) {
	
	for (int i = 0; i < startnum; i++) {
		if (startlist[i] == s)
			return i;
	}
	return -1;
}
//=============================================================



//check��������endlist���в����ս����λ�ã�����λ��
int check(string s) {
	int location = -1;
	int len = 0;
	for (int i = 0; i < endnum; i++) {
		int n = endlist[i].length();
		if (s.substr(0, n) == endlist[i] && n > len) {
			len = n;
			location = i;
		}
	}
	return location;
}
//================================================================

//strsearch��������ָ���ս����endlist���λ�ã�����λ��
int strsearch(string token) {
	for (int i = 0; i < endnum; i++) {
		if (endlist[i] == token)
			return i;
	}
	return -1;
}
//==================================================================

//�����ķ������б�λ��
int findrule(rule temp)
{
	for (int i = 0; i < num; i++) {
		if (rulelist[i].ssymbol == temp.ssymbol)
			if (rulelist[i].tuidao == temp.tuidao)
				return i;
	}
	return -1;
}
//=====================================================================

//���Ҹ�״̬��״̬�б��λ��
int checkStatus(status tmp)
{

	int flag = 0;
	for (int i = 0; i < snum; i++)
	{
		flag = 0;
		//if(tmp.state==statuslist[i].state )
			if (tmp.rules.size() == statuslist[i].rules.size())
			{
				
				for (int j = 0; j < tmp.rules.size()&& flag==0; j++) {
					flag = 1;

					for (int m = 0; m < statuslist[i].rules.size() && flag == 1; m++) {
						if (tmp.rules[j].loc == statuslist[i].rules[m].loc)
							if (tmp.rules[j].ssymbol == statuslist[i].rules[m].ssymbol)
								if (tmp.rules[j].tuidao == statuslist[i].rules[m].tuidao)
									flag = 0;
					}
				}
				if (flag == 0)
				{
					return i;
				}
			}
			else
				flag = 1;
			
			
	}
	return -1;
}

//=================================================================================

//��ָ��״̬����û��ָ���ķ�,0Ϊû�У�1Ϊ��
bool checkrule(status slist, rule rulel)
{
	for (int i = 0; i < slist.rules.size(); i++) {
		if (slist.rules[i].loc == rulel.loc)
			if (slist.rules[i].ssymbol == rulel.ssymbol)
				if (slist.rules[i].tuidao == rulel.tuidao)
					return 1;
	}
	return 0;
}


void getlr()
{
	snum = 1;
	int i = 0;
	while (i < snum)
	{
		vector<int> a;
		a.resize(startnum + endnum);
		table.push_back(a);
		//statuslist[i]�Բ�ͬ������ֵ������ͬ��״̬
		for (int j = 1; j < startnum; j++)
		{
			
			char str = startlist[j];
			status tmp;
			//������״̬���ҵ���Ӧ������ķ�
			for (int m = 0; m < statuslist[i].rules.size(); m++)
			{
				
				int w = statuslist[i].rules[m].loc;
				if (statuslist[i].rules[m].tuidao[w] == str)
				{
					
					rule temp;                                                     
					temp = statuslist[i].rules[m];
					temp.loc++;
					tmp.rules.push_back(temp);
					if (str == '$')
						tmp.state = -2;
					else if (temp.loc == temp.tuidao.size()) {
						int wei = findrule(temp);
						tmp.state = wei;
					}
					else {
						tmp.state = -1;
					}
					
				}
			}
			if (!tmp.rules.empty())
			{
				
				int n = 0;
				while (n < tmp.rules.size())
				{
					int w = tmp.rules[n].loc;
					if (search(tmp.rules[n].tuidao[w]) != -1)
					{
						char s = tmp.rules[n].tuidao[w];
						for (int x = 0; x < num; x++)
						{
							if (rulelist[x].ssymbol == s && checkrule(tmp, rulelist[x]) == 0)
							{
								tmp.rules.push_back(rulelist[x]);
							}
						}
					}
					n++;
				}
				//��״̬�б���û���²�����״̬����״̬ѹ��״̬�б�
				if (checkStatus(tmp) == -1 )
				{
					statuslist.push_back(tmp);
					snum++;
					table[i][j] = snum - 1;
				}
				else {
					table[i][j] = checkStatus(tmp);
				}
			}
			
			
			
		}
		
		//statuslist[i]�Բ�ͬ������ֵ������ͬ��״̬
		for (int j = 0; j < endnum; j++)
		{
			string str = endlist[j];
			status tmp;
			//������״̬���ҵ���Ӧ������ķ�
			for (int m = 0; m < statuslist[i].rules.size(); m++)
			{
				int w = statuslist[i].rules[m].loc;
				int len = str.length();
				if (statuslist[i].rules[m].tuidao.substr(w,len) == str)
				{ 
					rule temp;
					temp = statuslist[i].rules[m];
					temp.loc= temp.loc+len;
					tmp.rules.push_back(temp);
					if (str == "$")
						tmp.state =-2;
					else if (temp.loc == temp.tuidao.size()) {
						int wei = findrule(temp);
						tmp.state = wei;
					}
					else {
						tmp.state = -1;
					}

				}
				
			}
			if (!tmp.rules.empty())
			{

				int n = 0;
				while (n < tmp.rules.size())
				{
					int w = tmp.rules[n].loc;
					if (search(tmp.rules[n].tuidao[w]) != -1)
					{
						char s = tmp.rules[n].tuidao[w];
						for (int x = 0; x < num; x++)
						{
							if (rulelist[x].ssymbol == s && checkrule(tmp, rulelist[x]) == 0)
							{
								tmp.rules.push_back(rulelist[x]);
							}
						}
					}
					n++;
				}
				//��״̬�б���û���²�����״̬����״̬ѹ��״̬�б�
				if (checkStatus(tmp) == -1)
				{
					statuslist.push_back(tmp);
					snum++;
					table[i][j+startnum] = snum - 1;
				}
				else {
					table[i][j+startnum] = checkStatus(tmp);
				}
			}
			
		}
		i++;
	}
}


void getLR()
{
	
	status slist;
	slist.rules.push_back(rulelist[0]);
	int i = 0;
	
	while (i < slist.rules.size())
	{
		int wei = slist.rules[i].loc;
		
		if (search(slist.rules[i].tuidao[wei]) != -1)
		{
			char s = slist.rules[i].tuidao[wei];
			for (int j = 0; j < num; j++)
			{
				if (rulelist[j].ssymbol == s && checkrule(slist,rulelist[j])==0) {
					slist.rules.push_back(rulelist[j]);
				}
			}
		}
		i++;
	}
	slist.state =-1;
	statuslist.push_back(slist);
	getlr();
}

void displaygoto()
{
	cout << setw(10) << setfill(' ') << ' ';
	for (int i = 0; i < startnum; i++) {
		cout << setiosflags(ios::left) << setw(10);
		//cout << setw(10) << setfill(' ') << item[i];
		cout << startlist[i];
	}
	for (int i = 0; i < endnum; i++) {
		cout << setiosflags(ios::left) << setw(10);
		//cout << setw(10) << setfill(' ') << item[i];
		cout << endlist[i];
	}
	cout << endl;

	for (int i = 0; i < snum; i++)
	{

		cout << setiosflags(ios::left) << setw(10) << i;//���״̬
		for (int j = 0; j <startnum+endnum; j++)
		{
			if (table[i][j] == NULL)
				cout << setw(10) << setfill(' ') << " ";
			else
				cout << setiosflags(ios::left) << setw(10) << table[i][j];
			//cout << table[i][j];
		/*if (dfa[i][j] == NULL)
			cout << setw(10) << setfill(' ') << "-1";
		else {
			cout << setiosflags(ios::left) << setw(10);
			cout << dfa[i][j];
		}*/
		}
		cout << endl;
	}
}


int searchpos(string sen)
{
	for (int i = 0; i < startnum; i++) {
		if (sen[0] == startlist[i])
			return  i;
	}
	for (int i = 0; i < endnum; i++) {
		int n = endlist[i].length();
		if (sen.substr(0, n) == endlist[i])
			return i + startnum;

	}
	return -1;
}


//����ָ���ķ����е�token��
int calculate(string tuidao)
{
	int tonum = 0;
	int pos = 0;
	while (pos < tuidao.length()) {
		for (int i = 0; i < startnum; i++) {
			if (tuidao[pos] == startlist[i]) {
				tonum++;
				pos++;
				break;
			}
		}
		int tmp = 0;
		for (int i = 0; i < endnum; i++) {
			int n = endlist[i].length();
			if (tuidao.substr(pos, n) == endlist[i]) {
				if (n > tmp)
					tmp = n;  
				
			}
		}
		if (tmp != 0) {
			tonum++;
			pos += tmp;
		}
	}
	return tonum;
}

//�ж�����Ƿ���ȷ��1Ϊ���ϣ�0Ϊ������
bool judge(string sen) {
	
	stack<int> proce;
	proce.push(0);
	int position = 0;//��¼����������е�λ��
	while (position <= sen.length()) {
		int sta = statuslist[proce.top()].state;
		cout << sen << "  " << position << endl;//=============
		
		if ( sta== -2) {
			if (position == sen.length())
				return 1;
			else
				return 0;
		}
		else if (sta == -1)
		{
			int pos=searchpos(sen.substr(position));
			
			if (pos < 0)
				return 0;
			else if (pos > startnum)
			{
				position += endlist[pos - startnum].length();
			}
			else
				position += 1;
			if (table[proce.top()][pos] == NULL)
				return 0;
			else
				proce.push(table[proce.top()][pos]);
		}
		else
		{
			int n = rulelist[sta].tuidao.length();
			int tonum = calculate(rulelist[sta].tuidao);
			sen = sen.substr(0,position-n)+ rulelist[sta].ssymbol+sen.substr(position);
			
			position = position - n;
			for (int i = 0; i < tonum; i++)
			{
				proce.pop();
			}
			
		}
	}
}

int main() {
	//��ʼ���洢������ķ�
	string sen;
	cout << "�������ķ������� ";
	int r;
	cin>>r;
	getline(cin, sen);
	int i = 0;
	while(getline(cin, sen) && i<r){
		i++;
		num++;
		rule t;
		t.ssymbol = sen[0];
		t.tuidao = sen.substr(3);
		t.loc = 0;
		rulelist.push_back(t);
		
		if (search(sen[0]) == -1) {
			startlist[startnum++] = sen[0];
		}
	}

	for (int i = 0; i < num; i++) {
		string str = rulelist[i].tuidao;
		string token;
		for (int j = 0; j < str.length(); j++) {
			if (search(str[j]) == -1 && str[j] != '#')
			{
				token = token + str[j];
			}
			else {
				if (!token.empty() && strsearch(token) == -1)
				{
					endlist[endnum++] = token;
					
				}
				token.erase(0);
			}
		}
		if (!token.empty() && strsearch(token) == -1)
		{
			endlist[endnum++] = token;
		}
	}

	getLR();

	cout << "action��\n";
	for (int i = 0; i < snum; i++) {
		cout << i << "   ";// <<  << endl;
		switch (statuslist[i].state) {
		case -2: {
			cout << "accept\n";
			break;
		}
		case -1: {
			cout << "shift\n";
			break;
		}
		default: {
			cout << "r" << statuslist[i].state << endl;
			break;
		}
		}
	}
	
	cout << "goto��\n";
	displaygoto();

	//������ӣ��ж��Ƿ�����ķ�
	cout << "��������ӣ� \n";
	string sentence;
	getline(cin, sentence);
	if (judge(sentence) == 0)
		cout << "����䲻�����ķ�\n";
	else
		cout << "���������ķ�\n";/**/
}