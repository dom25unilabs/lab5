#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <algorithm>
constexpr int N = 5, GOOD_GRADE = 4, BAD_GRADE = 2;
struct student
{
	std::wstring name;
	int group = 0;
	int marks[N]{};
};
static void sort_students(int n, student* a)
{
	int i, j, min_idx;
	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j].group < a[min_idx].group)
			{
				min_idx = j;
			}
		}
		std::swap(a[min_idx], a[i]);
	}
}
static void sort_grades(int n, std::pair<student, int>* a)
{
	int i, j, min_idx;
	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j].second > a[min_idx].second)
			{
				min_idx = j;
			}
		}
		std::swap(a[min_idx], a[i]);
	}
}
static void sort_groups(int cnt, int n, int* a)
{
	int i, j, min_idx;
	for (i = 0; i < cnt - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < cnt; j++)
		{
			if (a[2 * n + j] > a[2 * n + min_idx])
			{
				min_idx = j;
			}
		}
		std::swap(a[min_idx], a[i]);
		std::swap(a[n + min_idx], a[n + i]);
		std::swap(a[2 * n + min_idx], a[2 * n + i]);
	}
}
int main()
{
	if (!(_setmode(_fileno(stdout), _O_U8TEXT) && _setmode(_fileno(stdin), _O_U16TEXT) && _setmode(_fileno(stderr), _O_U8TEXT)))
		return 1;
	int n;
	std::wcin >> n;
	student* students = new student[n];
	std::pair<student, int>* good_grades = new std::pair<student, int>[n];
	int grade_cnt = 0;
	int* groups = new int[3 * n];
	int group_cnt = 0;
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
		int* group_idx = std::find(groups, groups + group_cnt, students[i].group);
		if (group_idx == groups + group_cnt)
		{
			groups[group_cnt] = students[i].group;
			groups[n + group_cnt] = 1;
			groups[2 * n + group_cnt++] = has_bad_grades;
		}
		else
		{
			int group_idx_int = group_idx - groups;
			groups[n + group_idx_int] += 1;
			groups[2 * n + group_idx_int] += has_bad_grades;
		}
		if (sum > N * GOOD_GRADE)
		{
			good_grades[grade_cnt++] = std::make_pair(students[i], sum);
		}
	}
	sort_students(n, students);
	sort_grades(grade_cnt, good_grades);
	sort_groups(group_cnt, n, groups);
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
	for (int i = 0; i < grade_cnt; i++)
	{
		std::wcout << good_grades[i].first.group << L", " << good_grades[i].first.name << " - " << (double)(good_grades[i].second) / N << '\n';
	}
	for (int i = 0; i < group_cnt; i++)
	{
		std::wcout << groups[i] << L" - " << groups[n + i] << " - " << groups[2 * n + i] << '\n';
	}
	delete[] students;
	return 0;
}

