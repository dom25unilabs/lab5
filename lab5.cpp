#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
constexpr int N = 5, GOOD_GRADE = 4, BAD_GRADE = 2;
struct student
{
	std::wstring name;
	int group = 0;
	int marks[N]{};
};

int main()
{
	if (!(_setmode(_fileno(stdout), _O_U8TEXT) && _setmode(_fileno(stdin), _O_U16TEXT) && _setmode(_fileno(stderr), _O_U8TEXT)))
		return 1;
	int n;
	std::wcin >> n;
	student* students = new student[n];
	std::vector<std::pair<student, int>> good_grades(0);
	std::unordered_map<int, std::pair<int, int>> groups(0);
	for (int i = 0; i < n; i++)
	{
		while (students[i].name.length() == 0)
		{
			std::getline(std::wcin, students[i].name);
		}
		std::wcin >> students[i].group;
		int sum = 0;
		bool has_bad_grades = false;
		for (auto& mark : students[i].marks)
		{
			std::wcin >> mark;
			sum += mark;
			if (mark <= BAD_GRADE)
			{
				has_bad_grades = true;
			}
		}
		if (groups.find(students[i].group) == groups.end())
		{
			groups[students[i].group] = std::make_pair(1, has_bad_grades);
		}
		else
		{
			groups[students[i].group].first++;
			groups[students[i].group].second += has_bad_grades;
		}
		if (sum > N * GOOD_GRADE)
		{
			good_grades.push_back(std::make_pair(students[i], sum));
		}
	}
	std::vector<std::tuple<int, int, int>> groupsv(groups.size());
	int i = 0;
	for (auto kv : groups)
	{
		groupsv[i++] = std::make_tuple(kv.first, kv.second.first, kv.second.second);
	}
	std::sort(students, students+n, [](student a, student b) {return a.group < b.group; });
	std::sort(good_grades.begin(), good_grades.end(), [](std::pair<student, int> a, std::pair<student, int> b) {return a.second > b.second; });
	std::sort(groupsv.begin(), groupsv.end(), [](std::tuple<int, int, int> a, std::tuple<int, int, int> b) {return std::get<2>(a) > std::get<2>(b); });
	for (int i = 0; i < n; i++)
	{
		std::wcout << students[i].group << L" - " << students[i].name << ": ";
		for (int j = 0; j < N; j++)
		{
			std::wcout << students[i].marks[j];
			if (j < N - 1)
			{
				std::wcout << ", ";
			}
		}
		std::wcout << '\n';
	}
	for (int i = 0; i < good_grades.size(); i++)
	{
		std::wcout << good_grades[i].first.group << L", " << good_grades[i].first.name << " - " << (double)(good_grades[i].second) / N << '\n';
	}
	for (int i = 0; i < groupsv.size(); i++)
	{
		std::wcout << std::get<0>(groupsv[i]) << L" - " << std::get<1>(groupsv[i]) << " - " << std::get<2>(groupsv[i]) << '\n';
	}
	delete[] students;
	return 0;
}

