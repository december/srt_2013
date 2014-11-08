#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
using namespace std;

string filename;
string dataname;
string resultname;
string start;
string end;
string dungod;
int succ;
int fail;

struct time
{
	int hour;
	int min;
	int sec;
	time(string s = ":");
};

int readtime(string s, int &i)
{
	int answer = 0;
	while (s[i] != ':' && i < s.size())
	{
		answer = answer * 10 + s[i] - '0';
		i++;
	}
	i++;
	return answer;
}

time::time(string s)
{
	int i = 0;
	hour = readtime(s, i);
	min = readtime(s, i);
	sec = readtime(s, i);
}

bool operator>(time a, time b)
{
	if (a.hour > b.hour)
		return true;
	if (a.hour == b.hour && a.min > b.min)
		return true;
	if (a.hour == b.hour && a.min == b.min && a.sec > b.sec)
		return true;
	return false;
}

time operator-(time a, time b)
{
	time c;
	c.hour = a.hour - b.hour;
	c.min = a.min - b.min;
	if (c.min < 0)
	{
		c.min += 60;
		c.hour--;
	}
	c.sec = a.sec - b.sec;
	if (c.sec < 0)
	{
		c.sec += 60;
		c.min--;
	}
	return c;
}

int findpoint(string s)
{
    for (int i = 0;i < s.size();i++)
        if (s[i] == '.')
            return i;
    return -1;
}

bool calctime()
{
	time head(start);
	time tail(end);
	if (tail > head)
	{
		tail = tail - head;
		stringstream aaa;
		aaa << tail.hour << ":" << tail.min << ":" << tail.sec;
		aaa >> end;
		return true;
	}
	return false;
}

string rename(string s)
{
    string t(s, 0, s.size() - 4);
    t += ".wav";
    return t;
}

int main ()
{
	cout << "请输入要分割的音频文件名：" << endl;
	cin >> filename;
	cout << "请输入分割指令所在文件名：" << endl;
	cin >> dataname;

	ifstream fin;
	fin.open(dataname.c_str());
	while (fin >> resultname >> start >> end)
	{
		cout << resultname << " " << start << " " << end << endl;
		getline(fin, dungod);
		int pos = findpoint(filename);
		if (pos <= 0)
		{
            cout << "音频文件名错误，请输入含扩展名的全名。" << endl;
            break;
		}
		if (filename.substr(filename.size() - 4, filename.size()) != ".wav")
		{
		    stringstream ss;
		    ss << "ffmpeg -i " << filename << " -ac 1 -ar 16000 -acodec pcm_s16le -f wav " << rename(filename);
		    system(ss.str().c_str());
		    cout << filename << "不是wav格式，已成功自动转换。" << endl;
		    filename = rename(filename);
		}
		else
		{
		    stringstream ss;
		    ss << "ffmpeg -i " << filename << " -ac 1 -ar 16000 -acodec pcm_s16le " << filename;
		    system(ss.str().c_str());
		    cout << filename << "已成功自动转换为规定格式。" << endl;
		}
		if (calctime())
		{
			stringstream ss;
			ss << "ffmpeg -ss " << start << " -t " << end << " -i " << filename << " " <<resultname;
			system(ss.str().c_str());
			succ++;
			cout << resultname << "输出成功！" <<endl;

		}
		else
		{
			fail++;
			cout << resultname << "输出失败！" <<endl;
		}
	}
	cout << "本次共处理" << succ + fail << "条指令，" << "其中" << succ << "条成功输出，" << fail << "条输出失败。" <<endl;
	cout << "音频处理结束，按任意键承认梁盾大神万岁。" << endl;
	system("pause");
	return 0;
}
