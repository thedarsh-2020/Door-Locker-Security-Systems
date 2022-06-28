# Door-Locker-Security-Systems
* Developing a system to unlock a door using a password.

## Drivers:
* GPIO, Keypad, LCD, Timer, UART, I2C, EEPROM, Buzzer and DC-Motor.

## Microcontroller:
* ATmega16

## Project Descryption:
* Two Microcontroller (HMI-ECU, Control-ECU)
* At the begining of project user is creating password by entering from HMI-ECU and send data byte by byte to Control-ECU by UART two times to check them
then storing password in EEPROM in case two password is matched, otherwise ECU will asking user to re-enter password again two times till it matched.
then go to Home Screen wich display two options to user ('+': openinig Door, '-': Changing Password)

1. '+' option: Asking user to enter password then send password to Control-ECU by UART to get current password from EEPROM to match it with entered password from user
* Case password is matching: Turn DC motor On to rotate Clock_wise for 15 Sec. as door is opening
then DC motor rotate Anti-ClockWise for 15 Sec. as door is closing
* Case password unmatching: in case user enter wrong password fr 3 times, Turn ON BUZZER for 1 Min. then back to Home Screen.

2. '-' Option: to change password must user current enter password then send password to Control-ECU by UART to get current password from EEPROM to match it with entered password from user
* Case Password is matching: asking user to enter new password two times to check them then storing password in EEPROM in case two password is matched, otherwise ECU will asking user to re-enter password again two times till it matched.
* Case password unmatching: in case user enter wrong password fr 3 times, Turn ON BUZZER for 1 Min. then back to Home Screen.
