#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

long long decrypt(long long a, long long b, long long x, long long p);
pair<long long, long long> encrypt(long long i, long long y, long long g, long long p);
bool isPrime(long int prime);

long long power(long long a, long long b, long long p);
long long mul(long long a, long long b, long long p);

int numGenerator(int min, int max);

long long calculate_K_inverse(long long k, long long t);

long long gcd(long long a, long long b);


int main()
{
    setlocale(LC_ALL, "Rus");

    long long p, y, g, k, r, k_inverse, s;
    double x;

    bool flag1 = false, flag2 = false, flag3 = false;

    string msg;

    vector<pair<long long, long long>> encryptedText;
    vector<long long> decryptedText;

    //Генерируется случайное простое число p.

    cout << mul(-137, 9, 22) << endl;

    do
    {
        cout << "Введите простое число p: ";
        cin >> p;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        flag1 = isPrime(p);

        if (!flag1)
        {
            cout << "\nОшибка! Введите простое число!\n" << endl;
        }
    } while (!flag1);

    //Выбирается целое число g — первообразный корень p.

    do
    {
        cout << "Введите простое число g: ";
        cin >> g;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        flag1 = isPrime(g);
        flag2 = g < p;

        if (!flag1 || !flag2)
        {
            cout << "\nОшибка! Введенное число G должно быть простым и быть меньше P!\n" << endl;
        }
    } while (!flag1 || !flag2);

    //Выбирается случайное целое число x такое, что (1 < x < p - 1).

    do
    {
        cout << "Введите целое число X такое, что (1 < x < p - 1): ";
        cin >> x;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        flag1 = int(x) == x;
        flag2 = x > 1;
        flag3 = x < (p - 1);

        if (!flag1 || !flag2 || !flag3)
        {
            cout << "\nОшибка! Введенное число X должно быть целым и удовлетворять условию (1 < x < p - 1)!\n" << endl;
        }
    } while (!flag1 || !flag2 || !flag3);

    //Вычисляется y = g^x mod p.

    y = power(g, x, p);

    //Открытым ключом является (y,g,p) закрытым ключом — число x.

    cout << "\nОткрытый ключ (y = " << y << ", g = " << g << ", p = " << p << ")" << endl;

    cout << "Закрытый ключ (x = " << x << ")" << endl;


    cout << "\nВведите сообщение для подписи: ";

    cin.ignore();

    getline(cin, msg);

    //Вычисляем хеш-функцию

    //hash<string> h;
    //long long hash_msg = h(msg);
    //long long hash_msg = hash<string>()(msg);

    long long hash_msg = 0;

    for (int i = 0; i < msg.length(); i++)
    {
        hash_msg += (int)msg[i];
    }

    hash_msg %= p;

    cout << "Хеш-сумма сообщения: " << hash_msg << endl;

    //Выбирается случайное целое число k взаимно простое с (p-1) такое, что (1 < k < p - 1).

    do
    {
        cout << "Введите целое число k взаимно простое с (p-1) такое, что (1 < k < p - 1): ";
        cin >> k;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        if (gcd(k, p - 1) == 1)
            flag1 = true;
        else
            flag1 = false;

        flag2 = k > 1;
        flag3 = k < (p - 1);

        if (!flag1 || !flag2 || !flag3)
        {
            cout << "\nОшибка! Введенное число k должно быть взаимно простым с (p-1) и удовлетворять условию (1 < k < p - 1)!\n" << endl;
        }
    } while (!flag1 || !flag2 || !flag3);

    //Вычисляем r = g^k mod p 

    r = power(g, k, p);

    // Вычисляется число k^-1, мультипликативно обратное к числу k по модулю (p-1):

    k_inverse = calculate_K_inverse(k, p - 1);

    //cout << "\n" << k_inverse << endl;

    //Вычисляем s = (m - x*r) * k^-1 mod (p - 1)

    s = mul((hash_msg - x * r), k_inverse, p - 1);

    //Подписью сообщения M является пара (r,s).

    cout << "ЭЦП: " << "(" << r << ", " << s << ")" << endl;

    // ПРОВЕРКА ПОДЛИННОСТИ ЭЦП

    // Проверяем выполнение условия: y^r * r^s mod p = g^m mod p
    long long left, right;

    //Вычисляем левую часть
    left = mul(power(y, r, p), power(r, s, p), p);

    //Вычисляем правую часть
    right = power(g, hash_msg, p);

    cout << "\n\nПроверка ЭЦП" << endl << endl;

    cout << "Левая часть: " << left << endl;
    cout << "Правая часть: " << right << endl;

}

long long decrypt(long long a, long long b, long long x, long long p)
{
    // M = b * a^(p-1-x) mod p
    long long M = mul(b, power(a, p - 1 - x, p), p);

    return M;
}

pair<long long, long long> encrypt(long long i, long long y, long long g, long long p)
{
    pair<long long, long long> a_b;

    long long a, b, k;

    //Выбирается случайное целое число k такое, что (1 < k < p - 1).
    k = numGenerator(1, p - 1);

    //a = g^k mod p
    a = power(g, k, p);

    //b = y^k * M mod p
    b = mul(power(y, k, p), i, p);

    a_b = make_pair(a, b);

    return a_b;

    //return power(i, e, n);
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

long long power(long long a, long long b, long long p) {

    long int current, result;

    current = a;
    result = 1;

    for (long int j = 0; j < b; j++)
    {
        result = result * current;
        result = result % p;
    }

    return result;

}

long long mul(long long  a, long long  b, long long  p) {// a*b mod p

    long long  sum = 0;

    for (int i = 0; i < b; i++) {
        sum += a;

        if (sum < 0)
            for (; sum < 0; sum += p);
        else
            for (; sum >= p; sum -= p);

    }

    return sum;
}

int numGenerator(int min, int max) {
    return min + rand() % (max - min + 1);
}

long long calculate_K_inverse(long long k, long long t)
{
    // Вычисляется число k^-1, мультипликативно обратное к числу k по модулю (p-1):
    long long x, d, i = 0;

    //for (int i = 1; i <= t; i++)
    //{
    //    x = 1 + i * t;
    //    if (x % k == 0)
    //    {
    //        d = x / k;
    //        break;
    //    }
    //}

    while (true)
    {
        i++;
        x = 1 + i * t;
        if (x % k == 0)
        {
            d = x / k;
            break;
        }
    }

    return d;

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