alfavit_RU = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'
action = input('Выберите действие 1 - зашифровать / 2 - расшифровать: ')
if action == '1':
    smeshenie = int(input('Шаг шифровки: '))
    message = input("Сообщение для шифровки: ").upper()
    itog = ''
    for i in message:
        mesto = alfavit_RU.find(i) #Вычисляем места символов в списке
        new_mesto = (mesto + smeshenie) % 32 #Сдвигаем символы на указанный в переменной smeshenie шаг
        if i in alfavit_RU:
            itog += alfavit_RU[new_mesto]
        else:
            itog += i
    print(itog)
elif action == '2':
    message = input("Сообщение для ДЕшифровки: ").upper()
    smeshenie = int(input('Шаг шифровки: '))
    itog = ''
    for i in message:
        mesto = alfavit_RU.find(i) #Вычисляем места символов в списке
        new_mesto = (mesto - smeshenie) % 32 #Сдвигаем символы на указанный в переменной smeshenie шаг
        if i in alfavit_RU:
            itog += alfavit_RU[new_mesto]
        else:
            itog += i
    print(itog)