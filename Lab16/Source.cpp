#include<iostream>

struct Student
{
	char school[20];
	char name[20];
	int course;
};

void scanStudent(Student& s)
{
	scanf_s("%s%s%d", s.school, 20, s.name, 20, &s.course);
}

void printStudent(Student s)
{
	printf("%s - %s - %d\n", s.school, s.name, s.course);
}

int scanArrSize()
{
	int n;
	do {
		printf("Введите размер массива от 1 до 100\n");
		scanf_s("%d", &n);
	} while (n > 100 || n < 1);
	return n;
}

int askUserScan()
{
	int choise;
	do {
		printf("Введите:\n1 - заполнить массив с клавиатуры\n2 - заполнить из txt\n3 - заполнить из bin\nВыбор:");
		scanf_s("%d", &choise);
	} while (choise > 3 || choise < 1);
	return choise;
}

int scanCourse()
{
	int c;
	do {
		printf("Введите номер класса = "); scanf_s("%d", &c);
	} while (c > 11 || c < 1);
	return c;
}

void readFileTxt(const char filename[], Student mas[], int& size)
{
	FILE* f;
	if (fopen_s(&f, filename, "r") != 0)
		exit(1);
	fscanf_s(f, "%d", &size);
	for (int i = 0; i < size; i++)
		fscanf_s(f, "%s%s%d", &mas[i].school, 20, &mas[i].name, 20, &mas[i].course);
	fclose(f);
}

void readFileBin(const char filename[], Student mas[], int& size)
{
	FILE* f;
	if (fopen_s(&f, filename, "rb") != 0)
		exit(1);

	fread(&size, sizeof(int), 1, f);

	fread(mas, sizeof(Student), size, f);

	fclose(f);
}

void writeToBinFile(const char filename[], Student mas[], int size)
{
	FILE* f;
	if (fopen_s(&f, filename, "wb") != 0)
		exit(1);

	fwrite(&size, sizeof(int), 1, f);

	fwrite(mas, sizeof(Student), size, f);
	fclose(f);
}

int main()
{
	//18.	Известны следующие данные о N учениках нескольких школ: фамилия, школа и класс. Вывести на экран фамилии и школы тех учеников, 
	//которые учатся в определенном классе (номер класса вводится с клавиатуры).
	system("chcp 1251");

	const int N = 100;
	Student mas[N];
	int size;

	switch (askUserScan())
	{
	case 1:
	{
		int n = scanArrSize();

		for (int i = 0; i < n; i++)
			scanStudent(mas[i]);
		writeToBinFile("2.bin", mas, n);
		break;
	}
	case 2:
	{
		readFileTxt("1.txt", mas, size);
		break;
	}
	case 3:
		readFileBin("2.bin", mas, size);
		break;
	}

	int c = scanCourse();
	for (int i = 0; i < size; i++)
		if (mas[i].course == c)
			printStudent(mas[i]);

	return 0;
}