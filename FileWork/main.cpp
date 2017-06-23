#include"windows.h"
#include <stdio.h>
#include <regex>
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <time.h>


//[2015-5-31_11:2:12][sf afa]\t100\t[fffaf1jjoasjfo;joafjofjaofj
std::string matchDataString = "^\\[[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}_[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}\\].*$";
std::string searchDataString = "[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}_[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}";

std::map<time_t, std::string> dataMap;



time_t StringToDatetime(std::string str);
void AlignedByTime(
	std::map<time_t, std::string>& inDateMap,
	std::map<time_t, std::string>& outDateMap,
	time_t beginTime, time_t endTime, int intervalTIme = 4);


void LoadConfig(std::string fileName)
{
	std::ifstream fin(fileName);
	std::string dataString;
	while (!fin.eof())
	{
		std::getline(fin, dataString);
		matchDataString = dataString;
	}
}

void LoadFile(std::string fileName, std::map<time_t, std::string>& outDataMap)
{
	std::ifstream fin(fileName);
	std::string dataString;
	std::regex re(matchDataString);
	std::smatch reResult;
	while (!fin.eof())
	{
		std::getline(fin, dataString);
		if (std::regex_match(dataString, reResult, re))
		{
			//get date
			std::regex searchhRe(searchDataString);
			bool r = std::regex_search(dataString, reResult, searchhRe);
			if (r)
			{
				time_t t = StringToDatetime(reResult[0]);

				//put in map

				outDataMap[t] = reResult[0].second._Ptr;
			}		
		}
	}
}

void AlignedByTime(
	std::map<time_t, std::string>& inDateMap,
	std::map<time_t, std::string>& outDateMap,
	int intervalTIme, time_t beginTime, time_t endTime)
{
	//timeGetTime();
}


time_t StringToDatetime(std::string str)
{
	tm tm_;

	int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
	sscanf(str.c_str(), "%d-%d-%d_%d:%d:%d", &year, &month, &day, &hour, &minute, &second);// 将string存储的日期时间，转换为int临时变量。

	tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
	tm_.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
	tm_.tm_mday = day;                         // 日。
	tm_.tm_hour = hour;                        // 时。
	tm_.tm_min = minute;                       // 分。
	tm_.tm_sec = second;                       // 秒。
	tm_.tm_isdst = 0;                          // 非夏令时。
	time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。

	return t_;
}
int main()
{
	//LoadConfig("config.txt");
	
	LoadFile("data.txt", dataMap);
	return 0;
}