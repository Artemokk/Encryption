#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

bool isPrime(long int prime);

long long power(long long a, long long b, long long p);

long long gcd(long long a, long long b);
long long calculate_inverse(long long a, long long p);


int main()
{
    setlocale(LC_ALL, "Rus");

    long long p, cA, dA, cB, dB, M1, M2, M3, M4;
    double x;

    bool flag1 = false, flag2 = false, flag3 = false;

    string msg;

    vector<long long> encryptedText;
    vector<long long> decryptedText;

    //Генерируется случайное простое число p.

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

    //Выбирается случайное целое число cA взаимно простое с (p-1).

    do
    {
        cout << "Введите целое число cA взаимно простое с (p-1): ";
        cin >> cA;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        if (gcd(cA, p - 1) == 1)
            flag1 = true;
        else
            flag1 = false;


        if (!flag1)
        {
            cout << "\nОшибка! Введенное число cA должно быть взаимно простым с (p-1)!\n" << endl;
        }
    } while (!flag1);

    //Вычисляется число dA, мультипликативно обратное к числу cA по модулю (p-1):

    dA = calculate_inverse(cA, p - 1);

    //Выбирается случайное целое число cB взаимно простое с (p-1).

    do
    {
        cout << "Введите целое число cB взаимно простое с (p-1): ";
        cin >> cB;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Проверьте корректность введенного числа" << endl;
            continue;
        }

        if (gcd(cB, p - 1) == 1)
            flag1 = true;
        else
            flag1 = false;


        if (!flag1)
        {
            cout << "\nОшибка! Введенное число cB должно быть взаимно простым с (p-1)!\n" << endl;
        }
    } while (!flag1);

    //Вычисляется число dB, мультипликативно обратное к числу cB по модулю (p-1):

    dB = calculate_inverse(cB, p - 1);

    cout << "Секретные ключи Алисы: (" << cA << ", " << dA << ")" << endl;

    cout << "Секретные ключи Боба: (" << cB << ", " << dB << ")" << endl;

    cout << "\nВведите сообщение для шифрования: ";

    cin.ignore();

    getline(cin, msg);

    // Шифрование

    cout << "\nАлиса отправила Бобу зашифрованное сообщение:" << endl;

    for (long long i = 0; i < msg.length(); i++)
    {
        encryptedText.push_back(0);

        //Вычисляется M1 = M^cA mod p. (зашифрованное сообщение, которое отправляет Алиса - Бобу)
        M1 = power(msg[i], cA, p);
        encryptedText[i] = M1;
        cout << encryptedText[i] << " ";
    }

    cout << "\n\nБоб отправляет Алисе ответное сообщение:" << endl;

    for (long long i = 0; i < encryptedText.size(); i++)
    {
        //Вычисляется M2 = M1^cB mod p

        decryptedText.push_back(0);
        M2 = power(encryptedText[i], cB, p);
        decryptedText[i] = M2;
        cout << decryptedText[i] << " ";
    }

    cout << "\n\nАлиса вычисляет D и отправляет Бобу:" << endl;

    for (long long i = 0; i < decryptedText.size(); i++)
    {
        //Вычисляется M3 = M2^dA mod p

        M3 = power(decryptedText[i], dA, p);
        encryptedText[i] = M3;
        cout << encryptedText[i] << " ";
    }

    cout << "\n\nБоб расшифровывает сообщение:" << endl;

    for (long long i = 0; i < encryptedText.size(); i++)
    {
        //Вычисляется M4 = M3^dB mod p

        M4 = power(encryptedText[i], dB, p);
        decryptedText[i] = M4;
        cout << decryptedText[i] << " ";
    }

    cout << endl;

    for (long long i = 0; i < decryptedText.size(); i++)
    {
        printf("%c", (char)decryptedText[i]);
    }

    cout << endl << endl;

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

long long calculate_inverse(long long a, long long p)
{
    // Вычисляется число, мультипликативно обратное к числу a по модулю p:
    long long x, d, i = 0;

    while (true)
    {
        i++;
        x = 1 + i * p;
        if (x % a == 0)
        {
            d = x / a;
            break;
        }
    }

    return d;

}