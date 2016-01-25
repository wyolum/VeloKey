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
Sheet 1 1
Title "VeloKey"
Date "2016-01-24"
Rev "rev 1"
Comp "WyoLum"
Comment1 "A Strava Keyboard"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R_Small R1
U 1 1 565719DA
P 2025 1975
F 0 "R1" H 2075 1975 40  0000 L CNB
F 1 "1M" V 2025 1975 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 2025 1975 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/301010151.pdf" H 2025 1975 40  0001 C CNB
F 4 "RC0603FR-071ML" H 2025 1975 60  0001 C CNN "manf#"
	1    2025 1975
	1    0    0    -1  
$EndComp
$Comp
L C_Small C5
U 1 1 56571A23
P 1700 1975
F 0 "C5" H 1775 1975 40  0000 L CNB
F 1 "4.7nF" H 1775 1900 40  0000 L CNN
F 2 "hack-footprints:C_0603_HandSoldering" H 1700 1975 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0100850P1.pdf" H 1700 1975 40  0001 C CNB
F 4 "CC0603KRX7R9BB472" H 1700 1975 60  0001 C CNN "manf#"
	1    1700 1975
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 56573EBE
P 2225 2100
F 0 "#PWR01" H 2225 1850 40  0001 C CNB
F 1 "GND" H 2225 1950 40  0000 C CNB
F 2 "" H 2225 2100 40  0000 C CNB
F 3 "" H 2225 2100 40  0000 C CNB
	1    2225 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5657449C
P 3175 2100
F 0 "#PWR02" H 3175 1850 40  0001 C CNB
F 1 "GND" H 3175 1950 40  0000 C CNB
F 2 "" H 3175 2100 40  0000 C CNB
F 3 "" H 3175 2100 40  0000 C CNB
	1    3175 2100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 56575AA6
P 2100 4550
F 0 "#PWR03" H 2100 4300 40  0001 C CNB
F 1 "GND" H 2100 4400 40  0000 C CNB
F 2 "" H 2100 4550 40  0000 C CNB
F 3 "" H 2100 4550 40  0000 C CNB
	1    2100 4550
	1    0    0    -1  
$EndComp
$Comp
L C_Small C6
U 1 1 56575F2E
P 1500 4350
F 0 "C6" H 1575 4350 40  0000 L CNB
F 1 "10pF" H 1575 4275 40  0000 L CNN
F 2 "hack-footprints:C_0603_HandSoldering" H 1500 4350 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/302010097.pdf" H 1500 4350 40  0001 C CNB
F 4 "CC0603JRNPO9BN100" H 1500 4350 60  0001 C CNN "manf#"
	1    1500 4350
	1    0    0    -1  
$EndComp
$Comp
L Led_Small D1
U 1 1 56587FAD
P 8075 5450
F 0 "D1" V 8075 5400 40  0000 R CNB
F 1 "RED" V 8000 5400 40  0000 R CNN
F 2 "hack-footprints:LED_0603_HandSoldering" V 8075 5450 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/S_110_LTST-C190KRKT.pdf" V 8075 5450 40  0001 C CNB
F 4 "LTST-C190KRKT" V 8075 5450 60  0001 C CNN "manf#"
	1    8075 5450
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R2
U 1 1 56588562
P 8075 5125
F 0 "R2" H 8125 5125 40  0000 L CNB
F 1 "330" V 8075 5125 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 8075 5125 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0011330P1.pdf" H 8075 5125 40  0001 C CNB
F 4 "RC0603FR-07330RL" H 8075 5125 60  0001 C CNN "manf#"
	1    8075 5125
	1    0    0    -1  
$EndComp
$Comp
L SPST-M S1
U 1 1 5658420D
P 9275 2475
F 0 "S1" V 9275 2650 40  0000 L CNB
F 1 "RST" V 9200 2650 40  0000 L CNN
F 2 "hack-footprints:SPST-PTS_810" H 9275 2475 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/311020045.pdf" H 9275 2475 40  0001 C CNB
F 4 "PTS810 SJM 250 SMTR LFS" V 9275 2475 60  0001 C CNN "manf#"
	1    9275 2475
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR05
U 1 1 56587427
P 8900 2950
F 0 "#PWR05" H 8900 2700 40  0001 C CNB
F 1 "GND" H 8900 2800 40  0000 C CNB
F 2 "" H 8900 2950 40  0000 C CNB
F 3 "" H 8900 2950 40  0000 C CNB
	1    8900 2950
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 565868F0
P 8075 6275
F 0 "#PWR06" H 8075 6025 40  0001 C CNB
F 1 "GND" H 8075 6125 40  0000 C CNB
F 2 "" H 8075 6275 40  0000 C CNB
F 3 "" H 8075 6275 40  0000 C CNB
	1    8075 6275
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 56599C96
P 2150 3550
F 0 "#PWR07" H 2150 3300 40  0001 C CNB
F 1 "GND" H 2150 3400 40  0000 C CNB
F 2 "" H 2150 3550 40  0000 C CNB
F 3 "" H 2150 3550 40  0000 C CNB
	1    2150 3550
	1    0    0    -1  
$EndComp
$Comp
L R_Small R3
U 1 1 5659B02E
P 8900 1700
F 0 "R3" H 8950 1700 40  0000 L CNB
F 1 "10k" V 8900 1700 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 8900 1700 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0011240P1.pdf" H 8900 1700 40  0001 C CNB
F 4 "RC0603FR-0710KL" H 8900 1700 60  0001 C CNN "manf#"
	1    8900 1700
	1    0    0    1   
$EndComp
NoConn ~ 1800 3200
$Comp
L C_Small C1
U 1 1 567ADE21
P 1500 3350
F 0 "C1" H 1575 3350 40  0000 L CNB
F 1 "2.2uF" H 1575 3275 40  0000 L CNN
F 2 "hack-footprints:C_0603_HandSoldering" H 1500 3350 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/UPY-GPHC_X5R_4V-to-50V_14_0717-202131.pdf" H 1500 3350 40  0001 C CNB
F 4 "CC0603MRX5R5BB225" H 1500 3350 60  0001 C CNN "manf#"
	1    1500 3350
	1    0    0    -1  
$EndComp
$Comp
L FIDUCIAL FID1
U 1 1 567C2921
P 8950 6850
F 0 "FID1" H 8950 7000 40  0000 C CNB
F 1 "FIDUCIAL" H 8950 6700 40  0000 C CNB
F 2 "hack-footprints:FIDUCIAL" H 8950 6850 40  0001 C CNB
F 3 "" H 8950 6850 40  0000 C CNB
	1    8950 6850
	1    0    0    -1  
$EndComp
$Comp
L FIDUCIAL FID2
U 1 1 567C2A0D
P 9375 6850
F 0 "FID2" H 9375 7000 40  0000 C CNB
F 1 "FIDUCIAL" H 9375 6700 40  0000 C CNB
F 2 "hack-footprints:FIDUCIAL" H 9375 6850 40  0001 C CNB
F 3 "" H 9375 6850 40  0000 C CNB
	1    9375 6850
	1    0    0    -1  
$EndComp
$Comp
L FIDUCIAL FID3
U 1 1 567C2EF2
P 9800 6850
F 0 "FID3" H 9800 7000 40  0000 C CNB
F 1 "FIDUCIAL" H 9800 6700 40  0000 C CNB
F 2 "hack-footprints:FIDUCIAL" H 9800 6850 40  0001 C CNB
F 3 "" H 9800 6850 40  0000 C CNB
	1    9800 6850
	1    0    0    -1  
$EndComp
NoConn ~ 1650 1600
Text Label 1200 2150 0    40   ~ 0
shield
$Comp
L PWR_FLAG #FLG010
U 1 1 56824C17
P 2800 2925
F 0 "#FLG010" H 2800 3020 50  0001 C CNN
F 1 "PWR_FLAG" H 2800 3105 40  0000 C CNN
F 2 "" H 2800 2925 50  0000 C CNN
F 3 "" H 2800 2925 50  0000 C CNN
	1    2800 2925
	1    0    0    -1  
$EndComp
$Comp
L OSHW LOGO1
U 1 1 56826CD5
P 10775 7000
F 0 "LOGO1" H 10775 6950 40  0001 C CNN
F 1 "OSHW" H 10775 7100 40  0001 C CNN
F 2 "hack-footprints:OSHW-LOGO" H 10775 7000 60  0001 C CNN
F 3 "" H 10775 7000 60  0000 C CNN
F 4 "mfr_pn" H 10775 7000 60  0001 C CNN "manf#"
	1    10775 7000
	1    0    0    -1  
$EndComp
Text Notes 825  875  0    40   ~ 8
USB_IN + FILTER
Text Notes 825  2475 0    40   ~ 8
V_REG
Text Notes 825  4075 0    40   ~ 8
CRYSTAL
Text Notes 825  4925 0    40   ~ 8
INTERFACES
Text Notes 4325 875  0    40   ~ 8
MICRO CONTROLLER
Connection ~ 1500 3100
Wire Wire Line
	1500 3450 1500 3500
Wire Wire Line
	2800 3500 2800 3450
Wire Wire Line
	2800 3200 2500 3200
Wire Wire Line
	2500 3100 2925 3100
Wire Wire Line
	2800 2925 2800 3250
Connection ~ 2800 3200
Connection ~ 2800 3100
Wire Wire Line
	1650 1400 1925 1400
Wire Wire Line
	1650 1500 1925 1500
Wire Wire Line
	1650 1700 2225 1700
Wire Wire Line
	1700 1700 1700 1875
Wire Wire Line
	2025 1700 2025 1875
Connection ~ 1700 1700
Wire Wire Line
	2025 2150 2025 2075
Wire Wire Line
	1100 2150 2025 2150
Wire Wire Line
	1100 1850 1100 2150
Wire Wire Line
	1700 2075 1700 2150
Connection ~ 1700 2150
Connection ~ 2025 1700
Wire Wire Line
	2225 1700 2225 2100
Wire Wire Line
	2725 1400 2775 1400
Wire Wire Line
	2725 1500 2775 1500
Wire Wire Line
	2725 1300 3175 1300
Wire Wire Line
	1500 4450 1500 4500
Wire Wire Line
	1500 4500 2700 4500
Wire Wire Line
	2700 4500 2700 4450
Wire Wire Line
	1375 4200 1800 4200
Wire Wire Line
	1500 4200 1500 4250
Connection ~ 1500 4200
Wire Wire Line
	2400 4200 2825 4200
Wire Wire Line
	2700 4200 2700 4250
Connection ~ 2700 4200
Wire Wire Line
	2100 4550 2100 4500
Connection ~ 2100 4500
Wire Wire Line
	8075 5225 8075 5350
Wire Wire Line
	8075 5550 8075 5650
Wire Wire Line
	9275 2700 8900 2700
Wire Wire Line
	8900 2575 8900 2950
Wire Wire Line
	8900 1800 8900 2375
Connection ~ 8900 1850
Connection ~ 8900 2700
Wire Wire Line
	8900 1400 8900 1600
Wire Wire Line
	9275 2250 9275 2325
Wire Wire Line
	9275 1850 9275 2050
Wire Wire Line
	1375 3100 1800 3100
Wire Wire Line
	1500 3100 1500 3250
Wire Wire Line
	1375 3500 2800 3500
Connection ~ 2100 3500
Connection ~ 2200 3500
Wire Wire Line
	2150 3500 2150 3550
Connection ~ 2150 3500
Wire Wire Line
	1650 1300 1925 1300
Wire Wire Line
	9275 2625 9275 2700
Connection ~ 1500 3500
Wire Wire Line
	8075 5025 8075 4725
Wire Notes Line
	800  800  3300 800 
Wire Notes Line
	3300 800  3300 2300
Wire Notes Line
	3300 2300 800  2300
Wire Notes Line
	800  2300 800  800 
Wire Notes Line
	800  2400 3300 2400
Wire Notes Line
	3300 2400 3300 3900
Wire Notes Line
	3300 3900 800  3900
Wire Notes Line
	800  3900 800  2400
Wire Notes Line
	800  4000 3300 4000
Wire Notes Line
	3300 4000 3300 4750
Wire Notes Line
	3300 4750 800  4750
Wire Notes Line
	800  4750 800  4000
Wire Wire Line
	3175 1300 3175 2100
Wire Notes Line
	800  4850 3300 4850
Wire Notes Line
	3300 4850 3300 7100
Wire Notes Line
	800  7100 800  4850
Wire Notes Line
	4300 800  9800 800 
Wire Notes Line
	9800 800  9800 3900
Wire Notes Line
	9800 3900 4300 3900
Wire Notes Line
	4300 3900 4300 800 
Wire Bus Line
	1100 2150 2025 2150
Wire Bus Line
	1375 3500 2800 3500
Wire Bus Line
	1500 4500 2700 4500
NoConn ~ 9225 2325
NoConn ~ 9225 2625
$Comp
L USB_micro P1
U 1 1 568DEDE0
P 1250 1150
F 0 "P1" H 1250 1200 40  0000 C CNB
F 1 "USB_micro" H 1250 1100 40  0000 C CNB
F 2 "hack-footprints:ST-USB-001G" H 1250 1150 60  0001 C CNN
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/10118193.pdf" H 1250 1200 60  0001 C CNN
F 4 "10118193-0001LF" H 1350 1300 60  0001 C CNN "manf#"
	1    1250 1150
	1    0    0    -1  
$EndComp
$Comp
L STF202 U2
U 1 1 568E01AF
P 2325 1150
F 0 "U2" H 2075 1200 40  0000 C CNB
F 1 "STF202" H 2325 1200 40  0000 C CNB
F 2 "hack-footprints:TSOP-6" H 1975 1100 60  0001 C CNN
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/STF202-22T1-D-117165.pdf" H 2075 1200 60  0001 C CNN
F 4 "STF202-22T1G" H 2175 1300 60  0001 C CNN "manf#"
	1    2325 1150
	1    0    0    -1  
$EndComp
$Comp
L MIC5528 U1
U 1 1 568E0B91
P 2150 3150
F 0 "U1" H 2150 3400 40  0000 C CNB
F 1 "MIC5528" H 2150 3300 40  0000 C CNB
F 2 "hack-footprints:DFN-6-1EP_1.2x1.2mm_Pitch0.4mm" H 2150 3350 60  0001 C CNN
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/MIC5528-779152.pdf" H 2150 3350 60  0001 C CNN
F 4 "MIC5528-3.3YMT-TR" H 2250 3500 60  0001 C CNN "manf#"
	1    2150 3150
	1    0    0    -1  
$EndComp
$Comp
L C_Small C2
U 1 1 568E114E
P 2800 3350
F 0 "C2" H 2875 3350 40  0000 L CNB
F 1 "2.2uF" H 2875 3275 40  0000 L CNN
F 2 "hack-footprints:C_0603_HandSoldering" H 2800 3350 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/UPY-GPHC_X5R_4V-to-50V_14_0717-202131.pdf" H 2800 3350 40  0001 C CNB
F 4 "CC0603MRX5R5BB225" H 2800 3350 60  0001 C CNN "manf#"
	1    2800 3350
	1    0    0    -1  
$EndComp
$Comp
L C_Small C7
U 1 1 568E1524
P 2700 4350
F 0 "C7" H 2775 4350 40  0000 L CNB
F 1 "10pF" H 2775 4275 40  0000 L CNN
F 2 "hack-footprints:C_0603_HandSoldering" H 2700 4350 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/302010097.pdf" H 2700 4350 40  0001 C CNB
F 4 "CC0603JRNPO9BN100" H 2700 4350 60  0001 C CNN "manf#"
	1    2700 4350
	1    0    0    -1  
$EndComp
$Comp
L ABS07 X1
U 1 1 568E18BC
P 2100 4200
F 0 "X1" H 2100 4350 40  0000 C CNB
F 1 "ABS07" H 2100 4200 40  0000 C CNB
F 2 "hack-footprints:xtal_3.2x1.5mm" H 2100 4200 60  0001 C CNN
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/306010055.pdf" H 2100 4050 60  0001 C CNN
F 4 "ABS07-32.768KHZ-7-T" H 2200 4150 60  0001 C CNN "manf#"
	1    2100 4200
	1    0    0    -1  
$EndComp
$Comp
L R_Small R4
U 1 1 568E44C5
P 9275 2150
F 0 "R4" H 9325 2150 40  0000 L CNB
F 1 "39" V 9275 2150 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 9275 2150 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0011330P1.pdf" H 9275 2150 40  0001 C CNB
F 4 "RC0603FR-07330RL" H 9275 2150 60  0001 C CNN "manf#"
	1    9275 2150
	1    0    0    -1  
$EndComp
$Comp
L C_Small C11
U 1 1 568E4FE1
P 8900 2475
F 0 "C11" H 8825 2475 40  0000 R CNB
F 1 "100nF" H 8825 2400 40  0000 R CNN
F 2 "hack-footprints:C_0603_HandSoldering" H 8900 2475 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0100020P1.pdf" H 8900 2475 40  0001 C CNB
F 4 "CC0603KRX7R9BB104" H 8900 2475 60  0001 C CNN "manf#"
	1    8900 2475
	-1   0    0    -1  
$EndComp
$Comp
L SAMD21G18A U?
U 1 1 56A63B98
P 6525 1350
AR Path="/56A50B22/56A63B98" Ref="U?"  Part="1" 
AR Path="/56A63B98" Ref="U?"  Part="1" 
F 0 "U?" H 5775 1550 40  0000 L CNB
F 1 "SAMD21G18A" H 6125 1550 40  0000 L CNB
F 2 "" H 5875 1350 60  0000 C CNN
F 3 "https://github.com/Wyolum/VeloKey/tree/master/kicad/data/Atmel-42181-SAM-D21_Datasheet.pdf" H 7725 1750 60  0001 C CNN
F 4 "SAMD21G18A-AUT" H 5775 1650 60  0001 C CNN "manf#"
	1    6525 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5275 1350 4775 1350
Wire Wire Line
	4775 1450 5275 1450
Wire Wire Line
	4775 1550 5275 1550
Wire Wire Line
	4775 1650 5275 1650
Wire Wire Line
	4775 1750 5275 1750
Wire Wire Line
	4775 1850 5275 1850
Wire Wire Line
	4775 1950 5275 1950
Wire Wire Line
	4775 2050 5275 2050
Wire Wire Line
	4775 2150 5275 2150
Wire Wire Line
	4775 2250 5275 2250
Wire Wire Line
	4775 2450 5275 2450
Wire Wire Line
	4775 2550 5275 2550
Wire Wire Line
	4775 2650 5275 2650
Wire Wire Line
	4775 2750 5275 2750
Wire Wire Line
	4775 2850 5275 2850
Wire Wire Line
	4775 2950 5275 2950
Wire Wire Line
	4775 3050 5275 3050
Wire Wire Line
	4775 3150 5275 3150
Wire Wire Line
	4775 3250 5275 3250
Wire Wire Line
	4775 3350 5275 3350
Wire Wire Line
	8275 1350 7775 1350
Wire Wire Line
	7775 1450 8275 1450
Wire Wire Line
	7775 1550 8275 1550
Wire Wire Line
	7775 1650 8275 1650
Wire Wire Line
	7775 1750 8275 1750
Wire Wire Line
	7775 1850 8625 1850
Wire Wire Line
	7775 1950 8275 1950
Wire Wire Line
	7775 2050 8275 2050
Wire Wire Line
	7775 2150 8275 2150
Wire Wire Line
	7775 2450 8275 2450
Wire Wire Line
	7775 2550 8275 2550
Wire Wire Line
	7775 2650 8275 2650
Wire Wire Line
	7775 2750 8275 2750
Wire Wire Line
	7775 2850 8275 2850
Wire Wire Line
	7775 2950 8275 2950
Wire Wire Line
	7775 3050 8275 3050
Wire Wire Line
	7775 3150 8275 3150
Wire Wire Line
	7775 3250 8275 3250
Wire Wire Line
	7775 3350 8275 3350
Text Label 4775 2750 0    40   ~ 8
D0
Text Label 4775 2650 0    40   ~ 8
D1
Text Label 4775 2450 0    40   ~ 8
D2
Text Label 4775 2550 0    40   ~ 8
D3
Text Label 4775 3250 0    40   ~ 8
D4
Text Label 4775 3350 0    40   ~ 8
D5
Text Label 8275 2950 0    40   ~ 8
D6
Text Label 8275 2850 0    40   ~ 8
D7
Text Label 4775 2150 0    40   ~ 8
D8
Text Label 4775 2250 0    40   ~ 8
D9
Text Label 8275 3150 0    40   ~ 8
SS
Text Label 8275 3350 0    40   ~ 8
MOSI
Text Label 8275 3050 0    40   ~ 8
MISO
Text Label 8275 3250 0    40   ~ 8
SCK
Text Label 4775 1550 0    40   ~ 8
A0
Text Label 4775 1750 0    40   ~ 8
A1
Text Label 4775 1850 0    40   ~ 8
A2
Text Label 4775 1950 0    40   ~ 8
A3
Text Label 4775 2050 0    40   ~ 8
A4
Text Label 8275 1450 0    40   ~ 8
A5
Text Label 4775 1650 0    40   ~ 8
AREF
Text Label 8275 2750 0    40   ~ 8
SDA
Text Label 8275 2650 0    40   ~ 8
SCL
Text Label 8275 2550 0    40   ~ 8
USB_N
Text Label 8275 2450 0    40   ~ 8
USB_P
Text Label 4775 1350 0    40   ~ 8
XIN32
Text Label 4775 1450 0    40   ~ 8
XOUT32
Text Label 2075 5225 0    40   ~ 8
DBG_MISO
Text Label 4775 2950 0    40   ~ 8
DBG_SCK
Text Label 4775 3050 0    40   ~ 8
DBG_MISO
$Comp
L SAMD21G18A U?
U 2 1 56A64203
P 6750 4425
AR Path="/56A50B22/56A64203" Ref="U?"  Part="2" 
AR Path="/56A64203" Ref="U?"  Part="2" 
F 0 "U?" H 6000 4625 40  0000 L CNB
F 1 "SAMD21G18A" H 6350 4625 40  0000 L CNB
F 2 "" H 6100 4425 60  0000 C CNN
F 3 "https://github.com/Wyolum/VeloKey/tree/master/kicad/data/Atmel-42181-SAM-D21_Datasheet.pdf" H 7950 4825 60  0001 C CNN
F 4 "SAMD21G18A-AUT" H 6000 4725 60  0001 C CNN "manf#"
	2    6750 4425
	1    0    0    -1  
$EndComp
$Comp
L FERRITE_BEAD L?
U 1 1 56A6420B
P 4800 4425
F 0 "L?" H 4765 4515 40  0000 L CNB
F 1 "FERRITE_BEAD" H 4615 4330 40  0000 L CNB
F 2 "" H 4800 4425 60  0000 C CNN
F 3 "" H 4765 4515 60  0000 C CNN
F 4 "BLM18EG221SN1D" H 4865 4615 40  0000 C CNN "manf#"
	1    4800 4425
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A64212
P 5450 4525
F 0 "C?" H 5475 4575 40  0000 L CNB
F 1 "100nF" H 5475 4450 40  0000 L CNB
F 2 "" H 5450 4525 50  0000 C CNN
F 3 "" H 5450 4525 50  0000 C CNN
	1    5450 4525
	1    0    0    -1  
$EndComp
$Comp
L CP_Small C?
U 1 1 56A64219
P 5150 4525
F 0 "C?" H 5175 4575 40  0000 L CNB
F 1 "10uF" H 5160 4445 40  0000 L CNB
F 2 "" H 5150 4525 50  0000 C CNN
F 3 "" H 5150 4525 50  0000 C CNN
	1    5150 4525
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A64220
P 5150 6025
F 0 "C?" H 5175 6075 40  0000 L CNB
F 1 "100nF" H 5175 5950 40  0000 L CNB
F 2 "" H 5150 6025 50  0000 C CNN
F 3 "" H 5150 6025 50  0000 C CNN
	1    5150 6025
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A64227
P 5450 6025
F 0 "C?" H 5475 6075 40  0000 L CNB
F 1 "100nF" H 5475 5950 40  0000 L CNB
F 2 "" H 5450 6025 50  0000 C CNN
F 3 "" H 5450 6025 50  0000 C CNN
	1    5450 6025
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A6422E
P 5450 5425
F 0 "C?" H 5475 5475 40  0000 L CNB
F 1 "100nF" H 5475 5350 40  0000 L CNB
F 2 "" H 5450 5425 50  0000 C CNN
F 3 "" H 5450 5425 50  0000 C CNN
	1    5450 5425
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 56A64235
P 5450 5025
F 0 "C?" H 5475 5075 40  0000 L CNB
F 1 "100nF" H 5475 4950 40  0000 L CNB
F 2 "" H 5450 5025 50  0000 C CNN
F 3 "" H 5450 5025 50  0000 C CNN
	1    5450 5025
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4425 5900 4425
Connection ~ 5450 4425
Connection ~ 5150 4425
Wire Wire Line
	4400 4625 5900 4625
Connection ~ 5450 4625
Connection ~ 5150 4625
Wire Wire Line
	4650 4425 4400 4425
Text Label 4400 4625 0    40   ~ 8
GND
Text Label 5725 6125 0    40   ~ 8
GND
Text Label 5725 6325 0    40   ~ 8
GND
Text Label 5450 5125 2    40   ~ 8
GND
Text Label 5450 5525 2    40   ~ 8
GND
Wire Wire Line
	5900 4925 5450 4925
Wire Wire Line
	5450 5125 5900 5125
Wire Wire Line
	5450 5325 5900 5325
Wire Wire Line
	5450 5525 5900 5525
Wire Wire Line
	5150 5725 5150 5925
Wire Wire Line
	4750 5725 5900 5725
Wire Wire Line
	5450 5925 5900 5925
Wire Wire Line
	4850 6125 5900 6125
Connection ~ 5450 6125
Wire Wire Line
	5725 6325 5900 6325
$Comp
L CP_Small C?
U 1 1 56A64252
P 4850 6025
F 0 "C?" H 4860 6095 40  0000 L CNB
F 1 "CP_Small" H 4860 5945 40  0000 L CNB
F 2 "" H 4850 6025 50  0000 C CNN
F 3 "" H 4850 6025 50  0000 C CNN
	1    4850 6025
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5925 4850 5725
Connection ~ 5150 5725
Connection ~ 5150 6125
$Comp
L L_Small L?
U 1 1 56A6425D
P 4650 5725
F 0 "L?" H 4680 5765 40  0000 L CNB
F 1 "L_Small" H 4680 5685 40  0000 L CNB
F 2 "" H 4650 5725 50  0000 C CNN
F 3 "" H 4680 5765 50  0000 C CNN
F 4 "ELL-VFG100MC" V 4600 5775 40  0000 C CNN "manf#"
	1    4650 5725
	0    -1   -1   0   
$EndComp
Connection ~ 4850 5725
Wire Wire Line
	4550 5725 4175 5725
Text Label 4175 5725 0    40   ~ 8
3V3
Text Label 5450 5325 2    40   ~ 8
3V3
Text Label 5450 4925 2    40   ~ 8
3V3
Text Label 4400 4425 0    40   ~ 8
3V3
Wire Wire Line
	8825 1850 9275 1850
$Comp
L R_Small R?
U 1 1 56A6573A
P 8725 1850
F 0 "R?" H 8775 1850 40  0000 L CNB
F 1 "330" V 8725 1850 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 8725 1850 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0011330P1.pdf" H 8725 1850 40  0001 C CNB
F 4 "RC0603FR-07330RL" H 8725 1850 60  0001 C CNN "manf#"
	1    8725 1850
	0    1    1    0   
$EndComp
Text Label 8900 1400 0    40   ~ 8
3V3
Text Label 8275 2150 0    40   ~ 8
TXD
Text Label 8275 2050 0    40   ~ 8
RXD
Text Label 8275 1950 0    40   ~ 8
TX_LED
Text Label 8275 1350 0    40   ~ 8
RX_LED
Text Label 8275 1750 0    40   ~ 8
USB_HOST_EN
Text Label 8275 1650 0    40   ~ 8
SWCLK
Text Label 8275 1550 0    40   ~ 8
SWDIO
Text Label 2775 1500 0    40   ~ 8
USB_P
Text Label 2775 1400 0    40   ~ 8
USB_N
Text Label 1700 1300 0    40   ~ 8
VBUS
Text Label 1700 1400 0    40   ~ 8
D_N
Text Label 1700 1500 0    40   ~ 8
D_P
Text Label 4775 3150 0    40   ~ 8
BLINK
Text Label 8450 5900 0    40   ~ 8
BLINK
$Comp
L MMBF170 Q?
U 1 1 56A69564
P 8175 5850
F 0 "Q?" H 8375 5925 40  0000 L CNB
F 1 "MMBF170" H 8375 5850 40  0000 L CNN
F 2 "SOT-23" H 8375 5775 40  0001 L CIN
F 3 "" H 8175 5850 50  0000 L CNN
	1    8175 5850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8075 6050 8075 6275
Wire Wire Line
	8375 5900 8450 5900
Text Label 8075 4725 0    40   ~ 8
3V3
$Comp
L Led_Small D?
U 1 1 56A6A71E
P 8875 5450
F 0 "D?" V 8875 5400 40  0000 R CNB
F 1 "RED" V 8800 5400 40  0000 R CNN
F 2 "hack-footprints:LED_0603_HandSoldering" V 8875 5450 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/S_110_LTST-C190KRKT.pdf" V 8875 5450 40  0001 C CNB
F 4 "LTST-C190KRKT" V 8875 5450 60  0001 C CNN "manf#"
	1    8875 5450
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R?
U 1 1 56A6A725
P 8875 5125
F 0 "R?" H 8925 5125 40  0000 L CNB
F 1 "330" V 8875 5125 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 8875 5125 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0011330P1.pdf" H 8875 5125 40  0001 C CNB
F 4 "RC0603FR-07330RL" H 8875 5125 60  0001 C CNN "manf#"
	1    8875 5125
	1    0    0    -1  
$EndComp
Wire Wire Line
	8875 5225 8875 5350
Wire Wire Line
	8875 5025 8875 4725
Wire Wire Line
	8875 5550 8875 6175
Text Label 8875 4725 0    40   ~ 8
3V3
$Comp
L Led_Small D?
U 1 1 56A6A918
P 9350 5450
F 0 "D?" V 9350 5400 40  0000 R CNB
F 1 "RED" V 9275 5400 40  0000 R CNN
F 2 "hack-footprints:LED_0603_HandSoldering" V 9350 5450 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/S_110_LTST-C190KRKT.pdf" V 9350 5450 40  0001 C CNB
F 4 "LTST-C190KRKT" V 9350 5450 60  0001 C CNN "manf#"
	1    9350 5450
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R?
U 1 1 56A6A91F
P 9350 5125
F 0 "R?" H 9400 5125 40  0000 L CNB
F 1 "330" V 9350 5125 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 9350 5125 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0011330P1.pdf" H 9350 5125 40  0001 C CNB
F 4 "RC0603FR-07330RL" H 9350 5125 60  0001 C CNN "manf#"
	1    9350 5125
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 5225 9350 5350
Wire Wire Line
	9350 5025 9350 4725
Wire Wire Line
	9350 5550 9350 6175
Text Label 9350 4725 0    40   ~ 8
3V3
Text Label 8875 6175 0    40   ~ 8
RX_LED
Text Label 9350 6175 0    40   ~ 8
TX_LED
$Comp
L R_Small R?
U 1 1 56A6AEDB
P 8400 6075
F 0 "R?" H 8450 6075 40  0000 L CNB
F 1 "330" V 8400 6075 40  0000 C CNN
F 2 "hack-footprints:R_0603_HandSoldering" H 8400 6075 40  0001 C CNB
F 3 "https://github.com/MickMad/HACK/tree/master/kicad/datasheets/0011330P1.pdf" H 8400 6075 40  0001 C CNB
F 4 "RC0603FR-07330RL" H 8400 6075 60  0001 C CNN "manf#"
	1    8400 6075
	-1   0    0    1   
$EndComp
Wire Wire Line
	8400 5975 8400 5900
Connection ~ 8400 5900
Wire Wire Line
	8400 6175 8400 6225
Wire Wire Line
	8400 6225 8075 6225
Connection ~ 8075 6225
$Comp
L CONN_02X5 P?
U 1 1 56A6DCF0
P 1450 5425
F 0 "P?" H 1400 5725 40  0000 L CNB
F 1 "CONN_02X5" H 1300 5125 40  0000 L CNB
F 2 "" H 1400 5375 50  0000 C CNN
F 3 "" H 1400 5375 50  0000 C CNN
	1    1450 5425
	-1   0    0    -1  
$EndComp
$Comp
L CONN_02X3 P?
U 1 1 56A6DE71
P 2650 5325
F 0 "P?" H 2600 5525 40  0000 L CNB
F 1 "SPI" H 2600 5125 40  0000 L CNB
F 2 "" H 2600 5175 50  0000 C CNN
F 3 "" H 2600 5175 50  0000 C CNN
	1    2650 5325
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P?
U 1 1 56A6E6FD
P 1400 6375
F 0 "P?" H 1475 6750 40  0000 L CNB
F 1 "POWER" V 1500 6225 40  0000 L CNB
F 2 "" H 1400 6125 50  0000 C CNN
F 3 "" H 1400 6125 50  0000 C CNN
	1    1400 6375
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P?
U 1 1 56A6E864
P 1400 7300
F 0 "P?" H 1400 7650 40  0000 L CNB
F 1 "ANALOG" V 1500 7125 40  0000 L CNB
F 2 "" H 1400 7300 50  0000 C CNN
F 3 "" H 1400 7300 50  0000 C CNN
	1    1400 7300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P?
U 1 1 56A6EAD7
P 2700 7200
F 0 "P?" H 2775 7575 40  0000 L CNB
F 1 "DIGITAL_01" V 2800 7050 40  0000 L CNB
F 2 "" H 2700 6950 50  0000 C CNN
F 3 "" H 2700 6950 50  0000 C CNN
	1    2700 7200
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X10 P?
U 1 1 56A6F095
P 2700 6275
F 0 "P?" H 2775 6750 40  0000 L CNB
F 1 "DIGITAL_02" V 2800 6075 40  0000 L CNB
F 2 "" H 2700 6125 50  0000 C CNN
F 3 "" H 2700 6125 50  0000 C CNN
	1    2700 6275
	-1   0    0    1   
$EndComp
Text Label 975  5225 0    40   ~ 8
SWDIO
Text Label 975  5325 0    40   ~ 8
SWCLK
Wire Wire Line
	975  5225 1200 5225
Wire Wire Line
	975  5325 1200 5325
NoConn ~ 1200 5425
NoConn ~ 1200 5525
Text Label 8275 1850 0    40   ~ 8
RESET
Text Label 9275 1850 0    40   ~ 8
RST
Text Label 975  5625 0    40   ~ 8
RST
Wire Wire Line
	975  5625 1200 5625
NoConn ~ 1700 5525
Wire Wire Line
	1700 5225 1825 5225
Wire Wire Line
	1700 5325 1825 5325
Wire Wire Line
	1825 5325 1825 5625
Wire Wire Line
	1825 5625 1700 5625
Wire Wire Line
	1700 5425 1825 5425
Connection ~ 1825 5425
Text Label 1825 5225 2    40   ~ 8
3V3
Text Label 1825 5325 2    40   ~ 8
GND
Text Label 3225 5225 2    40   ~ 8
3V3
Text Label 4775 2850 0    40   ~ 8
DBG_MOSI
Text Label 2075 5325 0    40   ~ 8
DBG_SCK
Text Label 3225 5325 2    40   ~ 8
DBG_MISO
Text Label 2075 5425 0    40   ~ 8
RST
Text Label 3225 5425 2    40   ~ 8
GND
Wire Wire Line
	2075 5225 2400 5225
Wire Wire Line
	2075 5325 2400 5325
Wire Wire Line
	2075 5425 2400 5425
Wire Wire Line
	3225 5225 2900 5225
Wire Wire Line
	3225 5325 2900 5325
Wire Wire Line
	3225 5425 2900 5425
Text Label 1375 3100 2    40   ~ 8
VBUS
Text Label 1375 3500 2    40   ~ 8
GND
Text Label 2925 3100 0    40   ~ 8
3V3
Text Label 1375 4200 2    40   ~ 8
XIN32
Text Label 2825 4200 0    40   ~ 8
XOUT32
Text Label 975  7050 0    40   ~ 8
A0
Text Label 975  7150 0    40   ~ 8
A1
Text Label 975  7250 0    40   ~ 8
A2
Text Label 975  7350 0    40   ~ 8
A3
Text Label 975  7450 0    40   ~ 8
A4
Text Label 975  7550 0    40   ~ 8
A5
Wire Wire Line
	975  7050 1200 7050
Wire Wire Line
	975  7150 1200 7150
Wire Wire Line
	975  7250 1200 7250
Wire Wire Line
	975  7350 1200 7350
Wire Wire Line
	975  7450 1200 7450
Wire Wire Line
	975  7550 1200 7550
Text Label 3225 7550 2    40   ~ 8
D0
Wire Wire Line
	3225 7550 2900 7550
Text Label 3225 7450 2    40   ~ 8
D1
Wire Wire Line
	3225 7450 2900 7450
Text Label 3225 7350 2    40   ~ 8
D2
Wire Wire Line
	3225 7350 2900 7350
Text Label 3225 7250 2    40   ~ 8
D3
Wire Wire Line
	3225 7250 2900 7250
Text Label 3225 7150 2    40   ~ 8
D4
Wire Wire Line
	3225 7150 2900 7150
Text Label 3225 7050 2    40   ~ 8
D5
Wire Wire Line
	3225 7050 2900 7050
Text Label 3225 6950 2    40   ~ 8
D6
Wire Wire Line
	3225 6950 2900 6950
Text Label 3225 6850 2    40   ~ 8
D7
Wire Wire Line
	3225 6850 2900 6850
Text Label 3225 6725 2    40   ~ 8
D8
Wire Wire Line
	3225 6725 2900 6725
Text Label 3225 6625 2    40   ~ 8
D9
Wire Wire Line
	3225 6625 2900 6625
Text Label 3225 6525 2    40   ~ 8
SS
Wire Wire Line
	3225 6525 2900 6525
Text Label 3225 6425 2    40   ~ 8
MOSI
Wire Wire Line
	3225 6425 2900 6425
Text Label 3225 6325 2    40   ~ 8
MISO
Wire Wire Line
	3225 6325 2900 6325
Text Label 3225 6225 2    40   ~ 8
SCK
Wire Wire Line
	3225 6225 2900 6225
Text Label 3225 6125 2    40   ~ 8
GND
Wire Wire Line
	3225 6125 2900 6125
Text Label 3225 6025 2    40   ~ 8
AREF
Wire Wire Line
	3225 6025 2900 6025
Wire Wire Line
	3225 5925 2900 5925
Wire Wire Line
	2900 5825 3225 5825
Text Label 3225 5925 2    40   ~ 8
SDA
Text Label 3225 5825 2    40   ~ 8
SCL
Wire Wire Line
	975  6725 1200 6725
Wire Wire Line
	1200 6625 975  6625
Wire Wire Line
	975  6525 1200 6525
Wire Wire Line
	1200 6425 975  6425
Wire Wire Line
	975  6325 1200 6325
Wire Wire Line
	1200 6225 975  6225
Wire Wire Line
	975  6125 1200 6125
Wire Wire Line
	1200 6025 975  6025
Text Label 975  6725 0    40   ~ 8
VIN
Text Label 975  6625 0    40   ~ 8
GND
Text Label 975  6525 0    40   ~ 8
GND
Text Label 975  6425 0    40   ~ 8
5V
Text Label 975  6325 0    40   ~ 8
3V3
Text Label 975  6225 0    40   ~ 8
RST
Text Label 975  6125 0    40   ~ 8
3V3
NoConn ~ 975  6025
$EndSCHEMATC
