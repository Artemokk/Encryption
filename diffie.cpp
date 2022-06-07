#include <iostream>


using namespace std;
bool isprime(int num);
long long power(long long a, long long b, long long P);
unsigned long long powerMod(unsigned long long a, unsigned long long b, unsigned long long P);


int main()
{
    setlocale(LC_ALL, "Rus");

    int P, G, A, B;
    int oA, oB;
    int sA, sB;
    bool flag = true;

    while (flag)
    {
        cout << "Введите публичное число P: ";
        cin >> P;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        if (!isprime(P) || P < 0) {
            cout << "Ошибка! Число должно быть простым!" << endl;
        }
        else
            flag = false;
    }

    flag = true;

    while (flag)
    {
        cout << "Введите публичное число G: ";
        cin >> G;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        if (G < 0 || G > P) 
            cout << "Ошибка! Число должно быть натуральным и быть меньше P!" << endl;
        else
            flag = false;

    }

    flag = true;

    while (flag)
    {
        cout << "Введите закрытый ключ A: ";
        cin >> A;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        if (A < 0) {
            cout << "Ошибка! Число должно быть натуральным!" << endl;
        }
        else
            flag = false;
    }

    flag = true;

    while (flag)
    {
        cout << "Введите закрытый ключ B: ";
        cin >> B;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        if (B < 0) {
            cout << "Ошибка! Число должно быть натуральным!" << endl;
        }
        else
            flag = false;
    }

    oA = power(G, A, P);
    //oA = powerMod(G, A, P);

    cout << "Открытый ключ A: " << oA << endl;

    oB = power(G, B, P);
    //oB = powerMod(G, B, P);

    cout << "Открытый ключ B: " << oB << endl;

    sA = power(oB, A, P); 
    //sA = powerMod(oB, A, P);

    cout << "Секретный ключ A: " << sA << endl;

    sB = power(oA, B, P);
    //sB = powerMod(oA, B, P);

    cout << "Секретный ключ B: " << sB << endl;

    if (sA != sB)
        cout << "Ошибка! Секретные ключи не совпадают! Попробуйте ввести другие цифры.";
    
}

bool isprime(int num) {
    for (int i = 2; i <= sqrt(num) + 1; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

unsigned long long powerMod(unsigned long long a, unsigned long long b, unsigned long long P)
{
    unsigned long long res = 1;
    a = a % P;


    if (a == 0) return 0;

    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % P;

        a = a * a;
        b = b >> 1;
    }
    return res;
}


long long power(long long a, long long b, long long P)
{

    if (b == 1)
        return a;

    else {
        int count = 0;
        int binary[10000];
        int num = b;

        //переводим в двоичную систему счисления
        while (num >= 1) {
            binary[count] = num % 2;
            num /= 2;
            count++;
        }
        int n = count;

        int* row = new int[n];
        row[0] = a;

        //последовательно вычисляем элементы
        for (int i = 1; i < n; i++) {
            row[i] = (row[i - 1] * row[i - 1]) % P;
        }

        long long res = 1;
        for (int i = 0; i < n; i++)
        {
            if (binary[i] > 0) {
                res *= binary[i] * row[i];
            }
        }

        return res % P;
    }
}
