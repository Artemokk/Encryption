#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

long long encrypt(long long i, long long e, long long n);
long long decrypt(long long i, long long d, long long n);

long long power(long long a, long long b, long long P);

bool isPrime(long int prime);
long long calculateE(long long t);
long long gcd(long long a, long long b);
long long calculateD(long long e, long long t);

int main()
{
    setlocale(LC_ALL, "Rus");


    long long p, q, n, t, e, d;

    bool flag;
    string msg;

    vector<long long> encryptedText;
    vector<long long> decryptedText;

    // Cоздание открытого и секретного ключей

    // 1. Выбираются два различных случайных простых числа p и q заданного размера

    do
    {
        cout << "Введите простое число p: ";
        cin >> p;
        flag = isPrime(p);

        if (!flag)
        {
            cout << "\nОшибка! Введите простое число!\n" << endl;
        }
    } while (!flag);


    do
    {
        cout << "Введите простое число  q: ";
        cin >> q;
        flag = isPrime(q);

        if (!flag)
        {
            cout << "\nОшибка! Введите простое число!\n" << endl;
        }
    } while (!flag);

    // 2. Вычисляется их произведение n = p ⋅ q, которое называется модулем.
    n = p * q;
    cout << "\nМодуль n = p*q = " << n << endl;

    // 3. Вычисляется значение функции Эйлера от числа n: φ(n) = (p−1)⋅(q−1)
    t = (p - 1) * (q - 1);
    cout << "Функция эйлера t = " << t << endl;

    // 4. Выбирается целое число e ( 1 < e < φ(n) ), взаимно простое со значением функции Эйлера (t)
    //	  Число e называется открытой экспонентой
    e = calculateE(t);

    // 5. Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))
    d = calculateD(e, t);

    // 6. Пара {e, n} публикуется в качестве открытого ключа RSA
    cout << "\nОткрытый ключ (n = " << n << ", e = " << e << ")" << endl;

    // 7. Пара {d, n} играет роль закрытого ключа RSA и держится в секрете
    cout << "Закрытый ключ (n = " << n << ", d = " << d << ")" << endl;


    cout << "\nВведите сообщение для шифрования: ";

    cin.ignore();

    getline(cin, msg);

    // Шифрование
    // msg^e mod n

    cout << "\nЗашифрованное сообщение:" << endl;

    for (long long i = 0; i < msg.length(); i++)
    {
        encryptedText.push_back(0);
        encryptedText[i] = encrypt(msg[i], e, n);
        cout << encryptedText[i] << " ";
    }

    cout << endl;

    for (long long i = 0; i < msg.length(); i++)
    {
        printf("%c", (char)encryptedText[i]);
    }


    // Расшифрование
    // c^d mod n


    cout << "\n\nРасшифроанное сообщение:" << endl;

    for (long long i = 0; i < msg.length(); i++)
    {
        decryptedText.push_back(0);
        decryptedText[i] = decrypt(encryptedText[i], d, n);
        cout << decryptedText[i] << " ";
    }

    cout << endl;

    for (long long i = 0; i < msg.length(); i++)
    {
        printf("%c", (char)decryptedText[i]);
    }

    return 0;
}


long long encrypt(long long i, long long e, long long n)
{
    long int current, result;

    current = i;
    result = 1;

    for (long int j = 0; j < e; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result;

    //return power(i, e, n);
}

long long decrypt(long long i, long long d, long long n)
{
    long int current, result;

    current = i;
    result = 1;

    for (long int j = 0; j < d; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result;

    //return power(i, d, n);
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


bool isPrime(long int prime)
{
    long int i, j;

    j = (long int)sqrt((long double)prime);

    for (i = 2; i <= j; i++)
    {
        if (prime % i == 0)
        {
            return false;
        }
    }

    return true;
}

long long calculateE(long long t)
{
    // Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)

    long long e = 2;

    while (e < t)
    {
        if (gcd(e, t) == 1)
        {
            break;
        }
        else
        {
            e++;
        }
    }

    return e;
}


long long gcd(long long a, long long b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

long long calculateD(long long e, long long t)
{
    // Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    long long x, d;

    for (int i = 1; i <= 10; i++)
    {
        x = 1 + i * t;
        if (x % e == 0)
        {
            d = x / e;
            break;
        }
    }

    return d;

}
