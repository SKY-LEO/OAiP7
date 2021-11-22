#include <iostream>
#include <conio.h>
#include <iomanip>
const int VALUE_OF_STRING = 256;
const int PRECISION = 10;
using namespace std;
void checkInputString(char*);
void generateArrayOfPointsOrCommas(char*, int*, int&, int&, int&);
int checkStringLength(char*);
int countPointsOrCommasInString(char*);
int firstDigit(char*, int&);
int lastDigit(char*, int&);
void showNumberString(char*, int*, int, int, int&);
void showNumberInt(char*, int*, int, int&, int&);
int checkInputNumber();

int main()
{
	char code;
	char my_string[VALUE_OF_STRING];
	int* array_of_points_and_commas_indexes;
	do
	{
		int count_points_or_commas = 0;
		do {
			cout << "Enter string on English keyboard(MAX " << VALUE_OF_STRING - 1 << "):" << endl;
			checkInputString(my_string);
			count_points_or_commas = countPointsOrCommasInString(my_string);
		} while (count_points_or_commas == 0);
		int length = checkStringLength(my_string);
		int index_of_first_digit = firstDigit(my_string, length);
		int index_of_last_digit = lastDigit(my_string, length);
		array_of_points_and_commas_indexes = new int[count_points_or_commas];
		generateArrayOfPointsOrCommas(my_string, array_of_points_and_commas_indexes, length, index_of_first_digit, index_of_last_digit);
		int index_number = 0;
		if (count_points_or_commas != 1) {
			cout << "\nThere are " << count_points_or_commas << " true commas or points in the string" << endl;
			do
			{
				cout << "To which one do you want show whole part?" << endl;
				index_number = checkInputNumber() - 1;//-1, т.к. запрашиваю номер с 1, а не с 0
			} while (index_number < 0 || index_number >= count_points_or_commas);
		}
		else {
			cout << "\nThere is only 1 true comma or point in the string" << endl;//index_number не меняем, т.к. он уже 0
		}
		cout << "What type of variable do you want to print the number?\n1. String\n2. Double" << endl;
		bool flag = false;
		do
		{
			switch (checkInputNumber()) {
			case 1:
				showNumberString(my_string, array_of_points_and_commas_indexes, index_number, index_of_first_digit, index_of_last_digit);
				flag = true;
				break;
			case 2:
				showNumberInt(my_string, array_of_points_and_commas_indexes, index_number, index_of_first_digit, index_of_last_digit);
				flag = true;
				break;
			default: cout << "Try again!" << endl;
			}
		} while (!flag);
		delete[]array_of_points_and_commas_indexes;
		cout << "Do you want to continue? Y/N" << endl;
		code = _getch();
	} while (code == 'y' || code == 'Y');
	return 0;
}

void checkInputString(char* my_string)
{
	int i = 0;
	while (i < VALUE_OF_STRING - 1)//последний элемент для терминатора
	{
		my_string[i] = _getch();
		if (my_string[i] == 13) break;//enter
		if (my_string[i] == 8) {//backspace
			cout << "\b \b";
			i--;
			continue;
		}
		if (!((my_string[i] >= '+' && my_string[i] <= '.') || (my_string[i] >= '0' && my_string[i] <= '9') || (my_string[i] >= 'A' && my_string[i] <= 'Z') || (my_string[i] >= 'a' && my_string[i] <= 'z')))
		{
			continue;
		}
		cout << my_string[i];
		i++;
	}
	my_string[i] = '\0';
}

int checkStringLength(char* my_string)
{
	int length = 0;
	for (length = 0; my_string[length] != '\0'; length++);
	return length;
}

int countPointsOrCommasInString(char* my_string)
{
	int count = 0;
	int length = checkStringLength(my_string);
	int index_of_first_digit = firstDigit(my_string, length);
	int index_of_last_digit = lastDigit(my_string, length);
	for (int i = index_of_first_digit; i < index_of_last_digit; i++)
	{
		if (my_string[i] == ',' || my_string[i] == '.')
		{
			count++;
		}
	}
	return count;
}

int firstDigit(char* my_string, int& length)
{
	int index_of_first_digit;
	for (index_of_first_digit = 0; index_of_first_digit < length; index_of_first_digit++)
	{
		if (my_string[index_of_first_digit] >= '0' && my_string[index_of_first_digit] <= '9')
		{
			break;
		}
	}
	return index_of_first_digit;
}

int lastDigit(char* my_string, int& length)
{
	int index_of_last_digit;
	for (index_of_last_digit = length; index_of_last_digit > 0; index_of_last_digit--)
	{
		if (my_string[index_of_last_digit] >= '0' && my_string[index_of_last_digit] <= '9')
		{
			break;
		}
	}
	return index_of_last_digit;
}

void generateArrayOfPointsOrCommas(char* my_string, int* array, int& length, int& index_of_first_digit, int& index_of_last_digit)
{
	int count = 0;
	for (int i = index_of_first_digit; i < index_of_last_digit; i++)
	{
		if (my_string[i] == ',' || my_string[i] == '.')
		{
			array[count] = i;
			count++;
		}
	}
}

void showNumberString(char* my_string, int* array_of, int index_number, int index_of_first_digit, int& index_of_last_digit)
{
	for (int i = index_of_first_digit; i >= 0; i--)
	{
		if (my_string[i] == '+' || my_string[i] == '-')
		{
			cout << my_string[i];//находим знак "+" или "-" максимально близкий к 1 цифре, если он есть
			break;
		}
	}
	for (int i = index_of_first_digit + 1; i < index_of_last_digit; i++)
	{
		if (my_string[index_of_first_digit] == '0')//проверка на 0, стоящий на 1 месте
		{
			if (my_string[i] >= '0' && my_string[i] <= '9')//если есть ещё цифры
			{
				if (array_of[index_number] - i > 0)//если разность индекса нужной запятой и цифры больше 0
				{
					index_of_first_digit = i;//эта цифра становится первой
				}
			}
		}
		else {
			break;
		}
	}
	for (int i = index_of_first_digit; i < array_of[index_number]; i++)
	{
		if (my_string[i] >= '0' && my_string[i] <= '9')
		{
			cout << my_string[i];
		}
	}
	cout << my_string[array_of[index_number]];//для знака препинания
	int count_after_comma = 0;
	for (int i = array_of[index_number]; i <= index_of_last_digit; i++)
	{
		if (my_string[i] >= '0' && my_string[i] <= '9' && count_after_comma < PRECISION)
		{
			cout << my_string[i];
			count_after_comma++;
		}
	}
	cout << endl;
}

void showNumberInt(char* my_string, int* array_of, int index_number, int& index_of_first_digit, int& index_of_last_digit)
{
	double number_int = 0;
	double x = 1;
	double variable = 0;
	bool negative_number = false;
	for (int i = index_of_first_digit; i >= 0; i--)
	{
		if (my_string[i] == '+')
		{
			//находим знак "+" или "-" максимально близкий к 1 цифре, если он есть
			break;
		}
		else if (my_string[i] == '-')
		{
			negative_number = true;
			break;
		}
	}
	for (int i = array_of[index_number] - 1; i >= index_of_first_digit; i--)//индекс точки, поэтому -1
	{
		if (my_string[i] >= '0' && my_string[i] <= '9')
		{
			variable = ((double)my_string[i] - '0') * x;
			number_int += variable;
			x *= 10;
		}

	}
	double number_double = 0;
	variable = 0;
	x = 0.1;
	int count_after_comma = 0;
	for (int i = array_of[index_number] + 1; i <= index_of_last_digit; i++)//индекс точки, поэтому +1
	{
		if (my_string[i] >= '0' && my_string[i] <= '9' && count_after_comma < PRECISION)
		{
			variable = ((double)my_string[i] - '0') * x;
			number_double += variable;
			x *= 0.1;
			count_after_comma++;
		}
	}
	if (negative_number)
	{
		cout << 0 - (number_int + number_double) << endl;
	}
	else {
		cout << setprecision(PRECISION) << number_int + number_double << endl;
	}
}

int checkInputNumber()
{
	int a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error, please write int number!\n" << "Try again!" << endl;
		}
	}
	return a;
}