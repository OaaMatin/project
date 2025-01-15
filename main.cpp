#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Get the handle to the standard output
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



string paranthesis(string str);
string remove_space(string str);
string calculate(string str);

int main()
{
    string str, hist;
    getline(cin, str);
    fstream calHis;
    while (true)
    {
        if (str == "h" or str == "H")
        {
            calHis.open("History.txt", ios::in);
            if (calHis.is_open())
            {
                string line;
                int i = 1;
                while (getline(calHis, str))
                {
                    cout << i << ": " << str << endl;
                    i++;
                }
                if (i == 1)
                    cout << "\"SEMNAN\"";

                calHis.close();
            }
        }
        // clearing the history and terminal
        else if (str == "c" or str == "C")
        {
            system("cls");
            ofstream file("History.txt", ios::out | ios::trunc);
        }
        // turning the calculator off without clearing the history file
        else if (str == "off")
            break;

        else
        {
            calHis.open("History.txt", ios::app);
            if (calHis.is_open())
            {
                calHis << str << endl;
                calHis.close();
            }
            str = remove_space(str);
            if (str[0] == '+' or str[0] == '-' or str[0] == '*' or str[0] == '/' or str[0] == '^')
            {
                str = hist.substr(0, hist.end() - hist.begin() - 1) + str.substr(0, hist.end() - hist.begin() - 1);
                str = remove_space(str);
            }
            str = paranthesis(str);
            str = calculate(str);
            calHis << "=" << str << endl;
            system("cls");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            cout <<str;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            hist = str;
            str = "";
        }

        char ch= getch();
        system("color 0f");


        while(ch!=13){
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            if (ch == '+')
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                cout << ch;
            }
            else if (isdigit(ch))
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << ch;
            }
            if (ch == '-')
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                cout << ch;
            }

            ch = getch();
        }
        


        getline(cin, str);

    }
    return 0;
}

// removing spacebars

string remove_space(string str)
{
    string str2 = "";
    for (int i = 0; i < str.length(); ++i)
        if (str[i] != ' ')
            str2 = str2 + str[i];
    return str2;
}

// reomiving the  paranthesis

string paranthesis(string str)
{
    int f_par = -1;
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == '(')
            f_par = i;

        if (str[i] == ')')
        {

            string nstr = str.substr((f_par) + 1, i - (f_par)-1);
            str.replace(f_par, i - (f_par) + 1, calculate(nstr));
            i = 0;
        }
    }
    return str;
}

// other stuff

string calculate(string str)
{
    // calculating POWER whthout exp
    for (int i = str.length() - 1; i >= 0; --i)
    {
        if (str[i] == '^')
        {
            string num1 = "";
            int j = i - 1;
            while (isdigit(str[j]) or str[j] == '.')
            {
                num1 = str[j] + num1;
                j--;
            }
            int z = j + 1;
            j = i + 1;
            string num2 = "";
            while (isdigit(str[j]) or str[j] == '.')
            {
                num2 = num2 + str[j];
                j++;
            }
            float power = pow(stof(num1), stof(num2));
            str.replace(z, j - z, to_string(power));
        }

        if (i >= 2)
        {

            // EXP EXP EXP

            if (str[i] == 'p' and str[i - 1] == 'x' and str[i - 2] == 'e')
            {
                int j = i + 1;
                string num2 = "";
                while (isdigit(str[j]) or str[j] == '.')
                {
                    num2 = num2 + str[j];
                    j++;
                }
                float a = stoi(num2);
                str.replace(i - 2, j - i + 2, to_string(exp(a)));
            }

            // RADICAL RADICAL RADICAL

            else if (tolower(str[i]) == 'd' and tolower(str[i - 1]) == 'a' and tolower(str[i - 2]) == 'r')
            {
                int j = i + 1;
                string num2 = "";
                while (isdigit(str[j]) or str[j] == '.')
                {
                    num2 = num2 + str[j];
                    j++;
                }
                float a = stof(num2);
                if (i != 2)
                {
                    if (isdigit(str[i - 3]))
                    {
                        int z = i - 3;
                        string n = "";
                        while (isdigit(str[z]) or str[z] == '.')
                        {
                            n = str[z] + n;
                            z--;
                        }
                        if (stof(n) == 0)
                        {
                            return "Can not calculate the 0th root of a number";
                        }
                        else
                        {
                            str.replace(i - 3, j - i + 3, to_string(pow(a, (1 / stof(n)))));
                        }
                    }
                }
                else
                {
                    str.replace(i - 2, j - i + 2, to_string(pow(a, 0.5)));
                }
            }

            // LOG LOG LOG LOG

            else if (tolower(str[i]) == 'g' and tolower(str[i - 1]) == 'o' and tolower(str[i - 2]) == 'l')
            {
                int j = i + 1;
                string num2 = "";
                while (isdigit(str[j]) or str[j] == '.')
                {
                    num2 = num2 + str[j];
                    j++;
                }
                float a = stof(num2);
                if (i != 2)
                {
                    if (isdigit(str[i - 3]))
                    {
                        int z = i - 3;
                        string n = "";
                        while (isdigit(str[z]) or str[z] == '.')
                        {
                            n = str[z] + n;
                            z--;
                        }
                        if (stof(n) == 0)
                        {
                            return "0 can not be the base of a log";
                        }
                        else
                        {
                            str.replace(i - 3, j - i + 3, to_string(log10(a) / log10(stof(n))));
                        }
                    }
                }
                else
                {
                    str.replace(i - 2, j - i + 2, to_string(log10(a)));
                }
            }
            // SIN SIN SIN

            else if (tolower(str[i]) == 'n' and tolower(str[i - 1]) == 'i' and tolower(str[i - 2]) == 's')
            {
                int j = i + 1;
                string num2 = "";
                while (isdigit(str[j]) or str[j] == '.')
                {
                    num2 = num2 + str[j];
                    j++;
                }
                float a = stof(num2);
                str.replace(i - 2, j - i + 2, to_string(sin(a * M_PI / 180)));
            }

            // COS COS COS

            else if (tolower(str[i]) == 's' and tolower(str[i - 1]) == 'o' and tolower(str[i - 2]) == 'c')
            {
                int j = i + 1;
                string num2 = "";
                while (isdigit(str[j]) or str[j] == '.')
                {
                    num2 = num2 + str[j];
                    j++;
                }
                float a = stof(num2);
                str.replace(i - 2, j - i + 2, to_string(cos(a * M_PI / 180)));
            }

            // TAN TAN TAN

            else if (tolower(str[i]) == 'n' and tolower(str[i - 1]) == 'a' and tolower(str[i - 2]) == 't')
            {
                int j = i + 1;
                string num2 = "";
                while (isdigit(str[j]) or str[j] == '.')
                {
                    num2 = num2 + str[j];
                    j++;
                }
                float a = stof(num2);
                str.replace(i - 2, j - i + 2, to_string(tan(a * M_PI / 180)));
            }
        }
    }

    // MULTIPLYING AND DIVIDING

    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == '*')
        {
            string num1 = "";
            int j = i - 1;
            while (isdigit(str[j]) or str[j] == '.')
            {
                num1 = str[j] + num1;
                j--;
            }
            int z = j + 1;
            j = i + 1;
            string num2 = "";
            while (isdigit(str[j]) or str[j] == '.')
            {
                num2 = num2 + str[j];
                j++;
            }
            str.replace(z, j - z, to_string(stof(num1) * stof(num2)));
            i = 0;
        }

        else if (str[i] == '/')
        {
            string num1 = "";
            int j = i - 1;
            while (isdigit(str[j]) or str[j] == '.')
            {
                num1 = str[j] + num1;
                j--;
            }
            int z = j + 1;
            j = i + 1;
            string num2 = "";
            while (isdigit(str[j]) or str[j] == '.')
            {
                num2 = num2 + str[j];
                j++;
            }
            str.replace(z, j - z, to_string(stof(num1) / stof(num2)));
            i = 0;
        }
    }

    // PLUS AND MINUS

    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == '+')
        {
            string num1 = "";
            int j = i - 1;
            while (isdigit(str[j]) or str[j] == '.')
            {
                num1 = str[j] + num1;
                j--;
            }
            int z = j + 1;
            j = i + 1;
            string num2 = "";
            while (isdigit(str[j]) or str[j] == '.')
            {
                num2 = num2 + str[j];
                j++;
            }
            str.replace(z, j - z, to_string(stof(num1) + stof(num2)));
            i = 0;
        }

        else if (str[i] == '-')
        {
            string num1 = "";
            int j = i - 1;
            while (isdigit(str[j]) or str[j] == '.')
            {
                num1 = str[j] + num1;
                j--;
            }
            int z = j + 1;
            j = i + 1;
            string num2 = "";
            while (isdigit(str[j]) or str[j] == '.')
            {
                num2 = num2 + str[j];
                j++;
            }
            str.replace(z, j - z, to_string(stof(num1) - stof(num2)));
            i = 0;
        }
    }
    return str;
}