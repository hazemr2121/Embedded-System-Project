# Embedded-System-Project
Alarm Clock Project for Embedded System Course using Atmega 32
General Idea: Have an alarm that displays the current time and the
alarm time in the format HH: MM: SS PM/AM, and when the alarm
time comes, the buzzer and the red Led are turned on until the user
turns them off.
• The current time is displayed on the LCD and the user can control it
through the keypad.
• When the clock starts, the user should adjust the time in HH: MM:
SS PM/AM format.
• After that, the clock should work typically: when the seconds reach
59, the seconds should reset to 0, and the minutes should increment
by 1. When the minutes reach 59, the minutes should reset to 0, the
hour increment by 1, and so on.
• There should be three specific buttons—the first one to be able to
adjust the time at any time.
• The second button is to be able to enter the alarm time mode. In this
mode, the user can enter the alarm time. When the user presses this
button again after entering the alarm time, the clock will return to
the normal mode, which is the time mode.
• The third button is to turn off the buzzer and the red LED when the
alarm time comes.
• Note: You must implement any needed driver for the used H/W
component. It is not allowed to write all the code in the main.
