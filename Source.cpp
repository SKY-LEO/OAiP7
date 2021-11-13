#include <iostream>
#include <conio.h>
#define SHOW_INT_NUMBERS 1//иначе вывод подстрокой
const int VALUE_OF_STRING = 255;
using namespace std;
void checkInputString(char*);
void generateArrayOfPointsOrCommas(char*, int*, int&, int&, int&);
int checkStringLength(char*);
int countPointsOrCommasInString(char*);
int firstDigit(char*, int&);
int lastDigit(char*, int&);
void genarateRealNumberString(char*, char*, int*, int, int&, int&, int&, int&);
void showNumberString(char*);
void showNumberInt(char*, int&);
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
			cout << "Enter string on English keyboard:" << endl;
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
		char* my_string_numbers;
		int comma_or_point;
		my_string_numbers = new char[index_of_last_digit - index_of_first_digit + 3];//+1 место для "+" или "-" и +1 для нуль-терминатора +1  для "." или ","
		genarateRealNumberString(my_string, my_string_numbers, array_of_points_and_commas_indexes, index_number, length, index_of_first_digit, index_of_last_digit, comma_or_point);
		if (SHOW_INT_NUMBERS)
		{
			showNumberInt(my_string_numbers, comma_or_point);
		}
		else
		{
			showNumberString(my_string_numbers);
		}
		delete[]array_of_points_and_commas_indexes;
		delete[]my_string_numbers;
		cout << "Do you want to continue? Y/N" << endl;
		code = _getch();
	} while (code == 'y' || code == 'Y');
	return 0;
}

void checkInputString(char* my_string)
{
	int i = 0;
	while (true)
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

int checkStringLength(char* my_string)
{
	int length = 0;
	for (length = 0; my_string[length] != '\0'; length++);
	return length;
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

void genarateRealNumberString(char* my_string, char* my_string_numbers, int* array_of, int index_number, int& length, int& index_of_first_digit, int& index_of_last_digit, int& comma_or_point)
{
	int count = 0;
	bool flag = false;
	for (int i = index_of_first_digit; i >= 0; i--)
	{
		if (my_string[i] == '+' || my_string[i] == '-')
		{
			my_string_numbers[count] = my_string[i];//находим знак "+" или "-" максимально близкий к 1 цифре, если он есть
			flag = true;
			break;
		}
	}
	if (flag) count++;
	for (int i = index_of_first_digit; i < array_of[index_number]; i++)
	{
		if (my_string[i] >= '0' && my_string[i] <= '9')
		{
			my_string_numbers[count] = my_string[i];
			count++;
		}
	}
	my_string_numbers[count] = my_string[array_of[index_number]];//для знака препинания
	comma_or_point = count;
	count++;
	for (int i = array_of[index_number]; i <= index_of_last_digit; i++)
	{
		if (my_string[i] >= '0' && my_string[i] <= '9')
		{
			my_string_numbers[count] = my_string[i];
			count++;
		}
	}
	my_string_numbers[count] = '\0';
}

void showNumberString(char* my_string_numbers)
{
	for (int i = 0; my_string_numbers[i] != '\0'; i++)
	{
		cout << my_string_numbers[i];
	}
	cout << endl;
}

void showNumberInt(char* my_string_numbers, int& comma_or_point)
{
	double number_int = 0;
	double x = 1;
	double variable = 0;
	int start_point = 0;
	bool negative_number = false;
	if (my_string_numbers[0] == '+')
	{
		start_point = 1;
	}
	else if (my_string_numbers[0] == '-')
	{
		start_point = 1;
		negative_number = true;
	}
	for (int i = comma_or_point - 1; i >= start_point; i--)//индекс точки, поэтому -1
	{
		variable = ((double)my_string_numbers[i] - '0') * x;
		number_int += variable;
		x *= 10;
	}
	double number_double = 0;
	variable = 0;
	x = 0.1;
	for (int i = comma_or_point + 1; my_string_numbers[i] != '\0'; i++)//индекс точки, поэтому +1
	{
		variable = ((double)my_string_numbers[i] - '0') * x;
		number_double += variable;
		x *= 0.1;
	}
	if (negative_number)
	{
		cout << 0 - (number_int + number_double) << endl;
	}
	else {
		cout << number_int + number_double << endl;
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