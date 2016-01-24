EESchema Schematic File Version 2
LIBS:velokey
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:microcontrollers
LIBS:microchip
LIBS:interface
LIBS:display
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:velokey-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SAMD21G18A U?
U 2 1 56A50B8E
P 3575 5450
F 0 "U?" H 2825 5650 40  0000 L CNB
F 1 "SAMD21G18A" H 3175 5650 40  0000 L CNB
F 2 "" H 2925 5450 60  0000 C CNN
F 3 "https://github.com/Wyolum/VeloKey/tree/master/kicad/data/Atmel-42181-SAM-D21_Datasheet.pdf" H 4775 5850 60  0001 C CNN
F 4 "SAMD21G18A-AUT" H 2825 5750 60  0001 C CNN "manf#"
	2    3575 5450
	1    0    0    -1  
$EndComp
$Comp
L FERRITE_BEAD L?
U 1 1 56A5171F
P 1625 5450
F 0 "L?" H 1590 5540 40  0000 L CNB
F 1 "FERRITE_BEAD" H 1440 5355 40  0000 L CNB
F 2 "" H 1625 5450 60  0000 C CNN
F 3 "" H 1590 5540 60  0000 C CNN
F 4 "BLM18EG221SN1D" H 1690 5640 40  0000 C CNN "manf#"
	1    1625 5450
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A517C5
P 2275 5550
F 0 "C?" H 2300 5600 40  0000 L CNB
F 1 "100nF" H 2300 5475 40  0000 L CNB
F 2 "" H 2275 5550 50  0000 C CNN
F 3 "" H 2275 5550 50  0000 C CNN
	1    2275 5550
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C?
U 1 1 56A518E4
P 1975 5550
F 0 "C?" H 2000 5600 40  0000 L CNB
F 1 "10uF" H 1985 5470 40  0000 L CNB
F 2 "" H 1975 5550 50  0000 C CNN
F 3 "" H 1975 5550 50  0000 C CNN
	1    1975 5550
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A51978
P 1975 7050
F 0 "C?" H 2000 7100 40  0000 L CNB
F 1 "100nF" H 2000 6975 40  0000 L CNB
F 2 "" H 1975 7050 50  0000 C CNN
F 3 "" H 1975 7050 50  0000 C CNN
	1    1975 7050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A51AD2
P 2275 7050
F 0 "C?" H 2300 7100 40  0000 L CNB
F 1 "100nF" H 2300 6975 40  0000 L CNB
F 2 "" H 2275 7050 50  0000 C CNN
F 3 "" H 2275 7050 50  0000 C CNN
	1    2275 7050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A51B78
P 2275 6450
F 0 "C?" H 2300 6500 40  0000 L CNB
F 1 "100nF" H 2300 6375 40  0000 L CNB
F 2 "" H 2275 6450 50  0000 C CNN
F 3 "" H 2275 6450 50  0000 C CNN
	1    2275 6450
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A51BE0
P 2275 6050
F 0 "C?" H 2300 6100 40  0000 L CNB
F 1 "100nF" H 2300 5975 40  0000 L CNB
F 2 "" H 2275 6050 50  0000 C CNN
F 3 "" H 2275 6050 50  0000 C CNN
	1    2275 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1775 5450 2725 5450
Connection ~ 2275 5450
Connection ~ 1975 5450
Wire Wire Line
	1225 5650 2725 5650
Connection ~ 2275 5650
Connection ~ 1975 5650
Wire Wire Line
	1475 5450 1225 5450
$Comp
L SAMD21G18A U?
U 1 1 56A527CA
P 6800 1750
F 0 "U?" H 6050 1950 40  0000 L CNB
F 1 "SAMD21G18A" H 6400 1950 40  0000 L CNB
F 2 "" H 6150 1750 60  0000 C CNN
F 3 "https://github.com/Wyolum/VeloKey/tree/master/kicad/data/Atmel-42181-SAM-D21_Datasheet.pdf" H 8000 2150 60  0001 C CNN
F 4 "SAMD21G18A-AUT" H 6050 2050 60  0001 C CNN "manf#"
	1    6800 1750
	1    0    0    -1  
$EndComp
Text Label 1225 5650 0    40   ~ 8
GND
Text Label 2550 7150 0    40   ~ 8
GND
Text Label 2550 7350 0    40   ~ 8
GND
Text Label 2275 6150 2    40   ~ 8
GND
Text Label 2275 6550 2    40   ~ 8
GND
Wire Wire Line
	5550 1750 5050 1750
Wire Wire Line
	5050 1850 5550 1850
Wire Wire Line
	5050 1950 5550 1950
Wire Wire Line
	5050 2050 5550 2050
Wire Wire Line
	5050 2150 5550 2150
Wire Wire Line
	5050 2250 5550 2250
Wire Wire Line
	5050 2350 5550 2350
Wire Wire Line
	5050 2450 5550 2450
Wire Wire Line
	5050 2550 5550 2550
Wire Wire Line
	5050 2650 5550 2650
Wire Wire Line
	5050 2850 5550 2850
Wire Wire Line
	5050 2950 5550 2950
Wire Wire Line
	5050 3050 5550 3050
Wire Wire Line
	5050 3150 5550 3150
Wire Wire Line
	5050 3250 5550 3250
Wire Wire Line
	5050 3350 5550 3350
Wire Wire Line
	5050 3450 5550 3450
Wire Wire Line
	5050 3550 5550 3550
Wire Wire Line
	5050 3650 5550 3650
Wire Wire Line
	5050 3750 5550 3750
Wire Wire Line
	8550 1750 8050 1750
Wire Wire Line
	8050 1850 8550 1850
Wire Wire Line
	8050 1950 8550 1950
Wire Wire Line
	8050 2050 8550 2050
Wire Wire Line
	8050 2150 8550 2150
Wire Wire Line
	8050 2250 8550 2250
Wire Wire Line
	8050 2350 8550 2350
Wire Wire Line
	8050 2450 8550 2450
Wire Wire Line
	8050 2550 8550 2550
Wire Wire Line
	8050 2850 8550 2850
Wire Wire Line
	8050 2950 8550 2950
Wire Wire Line
	8050 3050 8550 3050
Wire Wire Line
	8050 3150 8550 3150
Wire Wire Line
	8050 3250 8550 3250
Wire Wire Line
	8050 3350 8550 3350
Wire Wire Line
	8050 3450 8550 3450
Wire Wire Line
	8050 3550 8550 3550
Wire Wire Line
	8050 3650 8550 3650
Wire Wire Line
	8050 3750 8550 3750
Text Label 5050 3150 0    40   ~ 8
D0
Text Label 5050 3050 0    40   ~ 8
D1
Text Label 5050 2850 0    40   ~ 8
D2
Text Label 5050 2950 0    40   ~ 8
D3
Text Label 5050 3650 0    40   ~ 8
D4
Text Label 5050 3750 0    40   ~ 8
D5
Text Label 8550 3350 0    40   ~ 8
D6
Text Label 8550 3250 0    40   ~ 8
D7
Text Label 5050 2550 0    40   ~ 8
D8
Text Label 5050 2650 0    40   ~ 8
D9
Text Label 8550 3550 0    40   ~ 8
SS
Text Label 8550 3750 0    40   ~ 8
MOSI
Text Label 8550 3450 0    40   ~ 8
MISO
Text Label 8550 3650 0    40   ~ 8
SCK
Text Label 5050 1950 0    40   ~ 8
A0
Text Label 5050 2150 0    40   ~ 8
A1
Text Label 5050 2250 0    40   ~ 8
A2
Text Label 5050 2350 0    40   ~ 8
A3
Text Label 5050 2450 0    40   ~ 8
A4
Text Label 8550 1850 0    40   ~ 8
A5
Text Label 5050 2050 0    40   ~ 8
AREF
Text Label 8550 3150 0    40   ~ 8
SDA
Text Label 8550 3050 0    40   ~ 8
SCL
Text Label 8550 2950 0    40   ~ 8
USB_N
Text Label 8550 2850 0    40   ~ 8
USB_P
Text Label 5050 1750 0    40   ~ 8
XIN32
Text Label 5050 1850 0    40   ~ 8
XOUT32
Text Label 5050 3250 0    40   ~ 8
DBG_MOSI
Text Label 5050 3350 0    40   ~ 8
DBG_SCK
Text Label 5050 3450 0    40   ~ 8
DBG_MISO
Wire Wire Line
	2725 5950 2275 5950
Wire Wire Line
	2275 6150 2725 6150
Wire Wire Line
	2275 6350 2725 6350
Wire Wire Line
	2275 6550 2725 6550
Wire Wire Line
	1975 6950 1975 6750
Wire Wire Line
	1575 6750 2725 6750
Wire Wire Line
	2275 6950 2725 6950
Wire Wire Line
	1675 7150 2725 7150
Connection ~ 2275 7150
Wire Wire Line
	2550 7350 2725 7350
$Comp
L CP_Small C?
U 1 1 56A555E3
P 1675 7050
F 0 "C?" H 1685 7120 40  0000 L CNB
F 1 "CP_Small" H 1685 6970 40  0000 L CNB
F 2 "" H 1675 7050 50  0000 C CNN
F 3 "" H 1675 7050 50  0000 C CNN
	1    1675 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1675 6950 1675 6750
Connection ~ 1975 6750
Connection ~ 1975 7150
$Comp
L L_Small L?
U 1 1 56A55698
P 1475 6750
F 0 "L?" H 1505 6790 40  0000 L CNB
F 1 "L_Small" H 1505 6710 40  0000 L CNB
F 2 "" H 1475 6750 50  0000 C CNN
F 3 "" H 1505 6790 50  0000 C CNN
F 4 "ELL-VFG100MC" H 1605 6890 40  0000 C CNN "manf#"
	1    1475 6750
	0    -1   -1   0   
$EndComp
Connection ~ 1675 6750
Wire Wire Line
	1375 6750 1000 6750
Text Label 1000 6750 0    40   ~ 8
3V3
Text Label 2275 6350 2    40   ~ 8
3V3
Text Label 2275 5950 2    40   ~ 8
3V3
Text Label 1225 5450 0    40   ~ 8
3V3
$EndSCHEMATC
