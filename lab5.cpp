#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <iomanip>
constexpr int N = 5, GOOD_GRADE = 4, BAD_GRADE = 2;
constexpr wchar_t LINE_RL = L'\u2550';
constexpr wchar_t LINE_TB = L'\u2551';
constexpr wchar_t LINE_TR = L'\u255A';
constexpr wchar_t LINE_TL = L'\u255D';
constexpr wchar_t LINE_BR = L'\u2554';
constexpr wchar_t LINE_BL = L'\u2557';
constexpr wchar_t LINE_TBR = L'\u2560';
constexpr wchar_t LINE_TBL = L'\u2563';
constexpr wchar_t LINE_BRL = L'\u2566';
constexpr wchar_t LINE_TRL = L'\u2569';
constexpr wchar_t LINE_TBRL = L'\u256C';
static void out_sep(int W1, int W2, int W3, bool begin)
{
	int step = W3 / (N - 1);
	std::wcout << '\n' << LINE_TBR;
	for (int i = 0; i < W1; i++)
	{
		std::wcout << LINE_RL;
	}
	std::wcout << LINE_TBRL;
	for (int i = 0; i < W2; i++)
	{
		std::wcout << LINE_RL;
	}
	std::wcout << LINE_TBRL;
	for (int i = 0; i < W3; i++)
	{
		if (i % step == 1)
		{
			if (begin)
			{
				std::wcout << LINE_BRL;
			}
			else
			{
				std::wcout << LINE_TBRL;
			}
		}
		else
		{
			std::wcout << LINE_RL;
		}
	}
	std::wcout << LINE_TBL << '\n';
}
static void out_array(int ALIGN_W, int LEN, const char* const name, double* a)
{
	std::wcout << LINE_TBL << '\n' << LINE_TB;
	std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << name;
	std::wcout << LINE_TB;
	for (int i = 0; i < LEN; i++)
	{
		std::wcout << std::right << std::setw(ALIGN_W) << std::setfill(L' ') << a[i];
		std::wcout << LINE_TB;
	}
}
static void out_begin(int ALIGN_W, int LEN, int n, const char* const* const names, double** arrs)
{
	std::wcout << LINE_TR;
	for (int i = 0; i < LEN + 1; i++)
	{
		for (int j = 0; j < ALIGN_W; j++)
		{
			std::wcout << LINE_RL;
		}
		if (i < LEN)
		{
			std::wcout << LINE_BRL;
		}
	}
	std::wcout << LINE_TL << '\n' << LINE_TB;
	std::wcout << std::left << std::setw(ALIGN_W) << std::setfill(L' ') << "idx";
}
static void out_end(int W1, int W2, int W3)
{
	int step = W3 / (N - 1);
	std::wcout << '\n' << LINE_TR;
	for (int i = 0; i < W1; i++)
	{
		std::wcout << LINE_RL;
	}
	std::wcout << LINE_TRL;
	for (int i = 0; i < W2; i++)
	{
		std::wcout << LINE_RL;
	}
	std::wcout << LINE_TRL;
	for (int i = 0; i < W3; i++)
	{
		if (i % step == 1)
		{
			std::wcout << LINE_TRL;
		}
		else
		{
			std::wcout << LINE_RL;
		}
	}
	std::wcout << LINE_TL << '\n';
}
struct student
{
	std::wstring name;
	int group = 0;
	int grades[N]{};
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
int wmain(int argc, wchar_t* argv[])
{
	if (!(_setmode(_fileno(stdout), _O_U8TEXT) && _setmode(_fileno(stdin), _O_U16TEXT) && _setmode(_fileno(stderr), _O_U8TEXT)))
		return 1;
	bool autoui = true;
	if (argc <= 1 || std::wcsncmp(argv[1], L"false", sizeof(L"false") - 1) != 0)
	{
		autoui = false;
	}
	int n;
	std::wcin >> n;
	student* students = new student[n];
	std::pair<student, int>* good_grades = new std::pair<student, int>[n];
	int grade_cnt = 0;
	int* groups = new int[3 * n];
	int group_cnt = 0;
	int max_len = 3;
	int max_group_len = 6;
	for (int i = 0; i < n; i++)
	{
		while (students[i].name.length() == 0)
		{
			std::getline(std::wcin, students[i].name);
		}
		if (students[i].name.length() > max_len)
		{
			max_len = students[i].name.length();
		}
		std::wcin >> students[i].group;
		int len = std::snprintf(nullptr, 0, "%.2f", students[i].group);
		if (len > max_group_len)
		{
			max_group_len = len;
		}
		int sum = 0;
		bool has_bad_grades = false;
		for (auto& grade : students[i].grades)
		{
			std::wcin >> grade;
			sum += grade;
			if (grade <= BAD_GRADE)
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
	if (autoui)
	{
		for (int i = 0; i < n; i++)
		{
			std::wcout << students[i].group << L" - " << students[i].name << ": ";
			for (int j = 0; j < N; j++)
			{
				std::wcout << students[i].grades[j];
				if (j < N - 1)
				{
					std::wcout << ", ";
				}
			}
			std::wcout << '\n';
		}
	}
	else
	{
		std::wcout << LINE_BR;
		for (int i = 0; i < max_len; i++)
		{
			std::wcout << LINE_RL;
		}
		std::wcout << LINE_BRL;
		for (int i = 0; i < max_group_len; i++)
		{
			std::wcout << LINE_RL;
		}
		std::wcout << LINE_BRL;
		for (int i = 0; i < 2 * N - 1; i++)
		{
			std::wcout << LINE_RL;
		}
		std::wcout << LINE_BL << '\n' << LINE_TB;
		std::wcout << std::left << std::setw(max_len) << std::setfill(L' ') << L"ФИО";
		std::wcout << LINE_TB;
		std::wcout << std::left << std::setw(max_group_len) << std::setfill(L' ') << L"Группа";
		std::wcout << LINE_TB;
		std::wcout << std::left << std::setw(2 * N - 1) << std::setfill(L' ') << L"Оценки";
		std::wcout << LINE_TB;
		out_sep(max_len, max_group_len, 2 * N - 1, true);
		for (int i = 0; i < n; i++)
		{
			std::wcout << LINE_TB;
			std::wcout << std::left << std::setw(max_len) << std::setfill(L' ') << students[i].name;
			std::wcout << LINE_TB;
			std::wcout << std::left << std::setw(max_group_len) << std::setfill(L' ') << students[i].group;
			std::wcout << LINE_TB;
			for (int j = 0; j < N; j++)
			{
				std::wcout << students[i].grades[j] << LINE_TB;
			}
			if (i < n - 1)
			{
				out_sep(max_len, max_group_len, 2 * N - 1, false);
			}
		}
		out_end(max_len, max_group_len, 2 * N - 1);
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
	delete[] groups;
	delete[] good_grades;
	return 0;
}
