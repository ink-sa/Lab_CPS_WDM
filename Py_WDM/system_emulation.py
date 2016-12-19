import serial
import time
import os
import sys

state = 0
s = 0
#открываем порт
ser = serial.Serial('COM13', 115200,timeout = 0)

while True:

    s = ser.read(2)
    if (s == b'\x00\xff'):                  #Если получили от STM32 команду 0x00 0xff то, перезагрузка - state = 0
        s = 0
        state = 0

    if state == 0:
        time.sleep(1)                       #Синхронизация включения программы и STM32
        ser.write(b'\x00\x00')
        state = 1
        continue
    elif state == 1:                        #Состояние 1 - состояние сразу после включения системы
        time.sleep(0.3)                     #Задержка 300мс на инициализацию системы
        ser.write(b'\xff\x02')              #Метка перехода в состояние 2 - команда 0xff
        state = 2                           #Переходим в состояние 2
        continue
    elif state == 2:                        #Состояние 2 - первое рабочее состояние
        time.sleep(1)                       #Задержка 1000мс
        ser.write(b'\x01\x01')              #Отсылаем параметр 0x01 со значением 0x01
        time.sleep(0.4)                     #Задержка 400мс
        ser.write(b'\xff\x03')              #Метка перехода в состояние 3 - команда 0xff
        state = 3                           #Переходим в состояние 3
        continue
    elif state == 3:                        #Состояние 3
        time.sleep(1)                       #Задержка 1000мс
        ser.write(b'\x02\x06')              #Отсылаем параметр 0x02 со значением 0x06
        time.sleep(0.4)                     #Задержка 400мс
        ser.write(b'\xff\x01')              #Метка перехода в состояние 1 - команда 0xff
        state = 1
        continue


ser.close()

