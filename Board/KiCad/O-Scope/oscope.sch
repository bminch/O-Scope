EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 1 3
Title "O-Scope"
Date "2021-06-14"
Rev ""
Comp "Olin College"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4300 1250 4300 1200
Connection ~ 4300 1200
Wire Wire Line
	3000 1200 3000 1250
Wire Wire Line
	4700 1250 4700 1200
Connection ~ 4700 1200
NoConn ~ 950  2300
NoConn ~ 1050 2300
NoConn ~ 1150 2300
NoConn ~ 1250 2300
NoConn ~ 1350 2300
NoConn ~ 1450 2300
NoConn ~ 1950 1800
Wire Wire Line
	1950 2000 2000 2000
Wire Wire Line
	2000 2000 2000 2050
Wire Wire Line
	1950 1600 2200 1600
Wire Wire Line
	2200 1600 2200 3200
Wire Wire Line
	2200 3200 3100 3200
Wire Wire Line
	1950 1400 2400 1400
Wire Wire Line
	2400 1400 2400 3000
Wire Wire Line
	2400 3000 3100 3000
Wire Wire Line
	3100 2800 2600 2800
Wire Wire Line
	2600 2800 2600 1700
Wire Wire Line
	2600 1400 2600 1200
Connection ~ 2600 1200
Wire Wire Line
	3100 9200 3050 9200
Wire Wire Line
	3050 9200 3050 9400
Wire Wire Line
	3100 9400 3050 9400
Connection ~ 3050 9400
Wire Wire Line
	3100 9600 3050 9600
Connection ~ 3050 9600
Wire Wire Line
	3100 9800 3050 9800
Connection ~ 3050 9800
Wire Wire Line
	2400 9050 2400 9000
Wire Wire Line
	2400 9000 2750 9000
Wire Wire Line
	2750 9050 2750 9000
Connection ~ 2750 9000
Wire Wire Line
	2650 7400 2650 7800
Wire Wire Line
	2650 7400 2700 7400
Wire Wire Line
	2700 8600 2650 8600
Connection ~ 2650 8600
Wire Wire Line
	2700 8200 2650 8200
Connection ~ 2650 8200
Wire Wire Line
	2700 7800 2650 7800
Connection ~ 2650 7800
Wire Wire Line
	3000 7800 3050 7800
Wire Wire Line
	3000 7400 3050 7400
Wire Wire Line
	3050 7350 3050 7400
Connection ~ 3050 7400
Wire Wire Line
	3050 7750 3050 7800
Connection ~ 3050 7800
Wire Wire Line
	3050 8150 3050 8200
Wire Wire Line
	3000 8200 3050 8200
Connection ~ 3050 8200
Wire Wire Line
	3000 8600 3050 8600
Wire Wire Line
	3050 8550 3050 8600
Connection ~ 3050 8600
Wire Wire Line
	1200 4400 1600 4400
Wire Wire Line
	1200 4700 1600 4700
Wire Wire Line
	1600 4700 1600 4600
Wire Wire Line
	1600 4600 3100 4600
Wire Wire Line
	1200 4800 3100 4800
Wire Wire Line
	1900 3650 1900 3700
Wire Wire Line
	1900 3700 2200 3700
Wire Wire Line
	2200 3700 2200 4200
Wire Wire Line
	2200 4200 3100 4200
Connection ~ 1900 3700
Wire Wire Line
	1300 3650 1300 3700
Wire Wire Line
	1300 3700 1600 3700
Wire Wire Line
	1600 3700 1600 4400
Connection ~ 1600 4400
Connection ~ 1300 3700
Wire Wire Line
	5500 9400 5600 9400
Wire Wire Line
	5500 9600 5600 9600
Wire Wire Line
	5500 9800 5600 9800
Wire Wire Line
	5900 9600 6000 9600
Wire Wire Line
	5900 9400 6000 9400
Wire Wire Line
	5900 9800 6000 9800
Wire Wire Line
	6400 9400 6300 9400
Wire Wire Line
	6400 9800 6300 9800
Wire Wire Line
	6300 9600 6400 9600
Connection ~ 6400 9600
Connection ~ 6400 9800
Text Label 5500 3400 0    60   ~ 0
DAC1
Text Label 5500 5800 0    60   ~ 0
DAC2
Text Label 5500 4600 0    60   ~ 0
VREF
Wire Wire Line
	4300 1200 4700 1200
Wire Wire Line
	4700 1200 4900 1200
Wire Wire Line
	3050 9400 3050 9600
Wire Wire Line
	3050 9600 3050 9800
Wire Wire Line
	2750 9000 3100 9000
Wire Wire Line
	2650 8600 2650 8650
Wire Wire Line
	2650 8200 2650 8600
Wire Wire Line
	2650 7800 2650 8200
Wire Wire Line
	3050 7400 3100 7400
Wire Wire Line
	3050 7800 3100 7800
Wire Wire Line
	3050 8200 3100 8200
Wire Wire Line
	3050 8600 3100 8600
Wire Wire Line
	1900 3700 1900 3750
Wire Wire Line
	1600 4400 3100 4400
Wire Wire Line
	1300 3700 1300 3750
Wire Wire Line
	6400 9600 6400 9800
Wire Wire Line
	6400 9800 6400 9900
Wire Wire Line
	6400 9400 6400 9600
$Comp
L power:GND #PWR017
U 1 1 5CF5073F
P 3050 10050
F 0 "#PWR017" H 3050 9800 50  0001 C CNN
F 1 "GND" H 3055 9877 50  0000 C CNN
F 2 "" H 3050 10050 50  0001 C CNN
F 3 "" H 3050 10050 50  0001 C CNN
	1    3050 10050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5CF50DCD
P 2750 9200
F 0 "C2" H 2635 9154 50  0000 R CNN
F 1 "0.1µF" H 2700 9300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2788 9050 50  0001 C CNN
F 3 "~" H 2750 9200 50  0001 C CNN
	1    2750 9200
	1    0    0    1   
$EndComp
$Comp
L Device:C C1
U 1 1 5CF50F38
P 2400 9200
F 0 "C1" H 2285 9154 50  0000 R CNN
F 1 "10µF" H 2350 9300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2438 9050 50  0001 C CNN
F 3 "~" H 2400 9200 50  0001 C CNN
	1    2400 9200
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5CF51025
P 2750 9350
F 0 "#PWR011" H 2750 9100 50  0001 C CNN
F 1 "GND" H 2755 9177 50  0000 C CNN
F 2 "" H 2750 9350 50  0001 C CNN
F 3 "" H 2750 9350 50  0001 C CNN
	1    2750 9350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5CF510FE
P 2400 9350
F 0 "#PWR09" H 2400 9100 50  0001 C CNN
F 1 "GND" H 2405 9177 50  0000 C CNN
F 2 "" H 2400 9350 50  0001 C CNN
F 3 "" H 2400 9350 50  0001 C CNN
	1    2400 9350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5D038B00
P 6400 9900
F 0 "#PWR08" H 6400 9650 50  0001 C CNN
F 1 "GND" H 6405 9727 50  0000 C CNN
F 2 "" H 6400 9900 50  0001 C CNN
F 3 "" H 6400 9900 50  0001 C CNN
	1    6400 9900
	-1   0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR013
U 1 1 5D039A1B
P 3050 7350
F 0 "#PWR013" H 3050 7200 50  0001 C CNN
F 1 "+3V3" H 3065 7523 50  0000 C CNN
F 2 "" H 3050 7350 50  0001 C CNN
F 3 "" H 3050 7350 50  0001 C CNN
	1    3050 7350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR014
U 1 1 5D039B67
P 3050 7750
F 0 "#PWR014" H 3050 7600 50  0001 C CNN
F 1 "+3V3" H 3065 7923 50  0000 C CNN
F 2 "" H 3050 7750 50  0001 C CNN
F 3 "" H 3050 7750 50  0001 C CNN
	1    3050 7750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR015
U 1 1 5D039CB3
P 3050 8150
F 0 "#PWR015" H 3050 8000 50  0001 C CNN
F 1 "+3V3" H 3065 8323 50  0000 C CNN
F 2 "" H 3050 8150 50  0001 C CNN
F 3 "" H 3050 8150 50  0001 C CNN
	1    3050 8150
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR016
U 1 1 5D039DFF
P 3050 8550
F 0 "#PWR016" H 3050 8400 50  0001 C CNN
F 1 "+3V3" H 3065 8723 50  0000 C CNN
F 2 "" H 3050 8550 50  0001 C CNN
F 3 "" H 3050 8550 50  0001 C CNN
	1    3050 8550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5D039F4B
P 2850 7400
F 0 "C3" V 3102 7400 50  0000 C CNN
F 1 "0.1µF" V 3011 7400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 7250 50  0001 C CNN
F 3 "~" H 2850 7400 50  0001 C CNN
	1    2850 7400
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 5D03A17B
P 2850 7800
F 0 "C4" V 3102 7800 50  0000 C CNN
F 1 "0.1µF" V 3011 7800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 7650 50  0001 C CNN
F 3 "~" H 2850 7800 50  0001 C CNN
	1    2850 7800
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C5
U 1 1 5D03A260
P 2850 8200
F 0 "C5" V 3102 8200 50  0000 C CNN
F 1 "0.1µF" V 3011 8200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 8050 50  0001 C CNN
F 3 "~" H 2850 8200 50  0001 C CNN
	1    2850 8200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C6
U 1 1 5D03A33F
P 2850 8600
F 0 "C6" V 3102 8600 50  0000 C CNN
F 1 "0.1µF" V 3011 8600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 8450 50  0001 C CNN
F 3 "~" H 2850 8600 50  0001 C CNN
	1    2850 8600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5D03A5DD
P 2650 8650
F 0 "#PWR010" H 2650 8400 50  0001 C CNN
F 1 "GND" H 2655 8477 50  0000 C CNN
F 2 "" H 2650 8650 50  0001 C CNN
F 3 "" H 2650 8650 50  0001 C CNN
	1    2650 8650
	1    0    0    -1  
$EndComp
$Comp
L Eclectronics:USB_microB_2040002-1 J2
U 1 1 5D0B4B45
P 1300 1600
F 0 "J2" H 1405 2289 60  0000 C CNN
F 1 "USB_microB_2040002-1" H 1405 2183 60  0000 C CNN
F 2 "Eclectronics:USB_microB_2040002-1" H 1650 1750 50  0001 C CNN
F 3 "" H 1650 1750 50  0001 C CNN
	1    1300 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5D0B4C18
P 2000 2050
F 0 "#PWR07" H 2000 1800 50  0001 C CNN
F 1 "GND" H 2005 1877 50  0000 C CNN
F 2 "" H 2000 2050 50  0001 C CNN
F 3 "" H 2000 2050 50  0001 C CNN
	1    2000 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D0B4D7D
P 2600 1550
F 0 "R3" H 2670 1596 50  0000 L CNN
F 1 "90.9K" H 2670 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2530 1550 50  0001 C CNN
F 3 "~" H 2600 1550 50  0001 C CNN
	1    2600 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5D0B5734
P 3000 1400
F 0 "C7" H 3115 1446 50  0000 L CNN
F 1 "10µF" H 3115 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3038 1250 50  0001 C CNN
F 3 "~" H 3000 1400 50  0001 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5D0B57BA
P 4300 1400
F 0 "C8" H 4415 1446 50  0000 L CNN
F 1 "10µF" H 4415 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4338 1250 50  0001 C CNN
F 3 "~" H 4300 1400 50  0001 C CNN
	1    4300 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5D0B58D5
P 4700 1400
F 0 "R7" H 4770 1446 50  0000 L CNN
F 1 "1K" H 4770 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4630 1400 50  0001 C CNN
F 3 "~" H 4700 1400 50  0001 C CNN
	1    4700 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_ALT D4
U 1 1 5D0B59A7
P 4700 1700
F 0 "D4" V 4738 1582 50  0000 R CNN
F 1 "PWR" V 4647 1582 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 4700 1700 50  0001 C CNN
F 3 "~" H 4700 1700 50  0001 C CNN
	1    4700 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5D0B5B27
P 4700 1850
F 0 "#PWR022" H 4700 1600 50  0001 C CNN
F 1 "GND" H 4705 1677 50  0000 C CNN
F 2 "" H 4700 1850 50  0001 C CNN
F 3 "" H 4700 1850 50  0001 C CNN
	1    4700 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5D0B5BAA
P 4300 1550
F 0 "#PWR021" H 4300 1300 50  0001 C CNN
F 1 "GND" H 4305 1377 50  0000 C CNN
F 2 "" H 4300 1550 50  0001 C CNN
F 3 "" H 4300 1550 50  0001 C CNN
	1    4300 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5D0B5CC3
P 3000 1550
F 0 "#PWR012" H 3000 1300 50  0001 C CNN
F 1 "GND" H 3005 1377 50  0000 C CNN
F 2 "" H 3000 1550 50  0001 C CNN
F 3 "" H 3000 1550 50  0001 C CNN
	1    3000 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5D0B5D46
P 3650 1700
F 0 "#PWR020" H 3650 1450 50  0001 C CNN
F 1 "GND" H 3655 1527 50  0000 C CNN
F 2 "" H 3650 1700 50  0001 C CNN
F 3 "" H 3650 1700 50  0001 C CNN
	1    3650 1700
	1    0    0    -1  
$EndComp
$Comp
L Eclectronics:MCP1702T-3302E_CB U1
U 1 1 5D0B5EAB
P 3650 1300
F 0 "U1" H 3650 1687 60  0000 C CNN
F 1 "MCP1702T-3302E_CB" H 3650 1581 60  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3650 1350 60  0001 C CNN
F 3 "" H 3650 1350 60  0001 C CNN
	1    3650 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D0B6700
P 1300 3500
F 0 "R1" H 1370 3546 50  0000 L CNN
F 1 "10K" H 1370 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1230 3500 50  0001 C CNN
F 3 "~" H 1300 3500 50  0001 C CNN
	1    1300 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D0B67B4
P 1900 3500
F 0 "R2" H 1970 3546 50  0000 L CNN
F 1 "10K" H 1970 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1830 3500 50  0001 C CNN
F 3 "~" H 1900 3500 50  0001 C CNN
	1    1900 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR03
U 1 1 5D0B68CA
P 1300 3350
F 0 "#PWR03" H 1300 3200 50  0001 C CNN
F 1 "+3V3" H 1315 3523 50  0000 C CNN
F 2 "" H 1300 3350 50  0001 C CNN
F 3 "" H 1300 3350 50  0001 C CNN
	1    1300 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR05
U 1 1 5D0B692C
P 1900 3350
F 0 "#PWR05" H 1900 3200 50  0001 C CNN
F 1 "+3V3" H 1915 3523 50  0000 C CNN
F 2 "" H 1900 3350 50  0001 C CNN
F 3 "" H 1900 3350 50  0001 C CNN
	1    1900 3350
	1    0    0    -1  
$EndComp
$Comp
L Eclectronics:SW S1
U 1 1 5D0B69E3
P 1300 3900
F 0 "S1" H 1348 3946 50  0000 L CNN
F 1 "RST" H 1348 3855 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_B3U-1000P" V 1350 4000 60  0001 C CNN
F 3 "" V 1350 4000 60  0001 C CNN
	1    1300 3900
	1    0    0    -1  
$EndComp
$Comp
L Eclectronics:SW S2
U 1 1 5D0B6A56
P 1900 3900
F 0 "S2" H 1948 3946 50  0000 L CNN
F 1 "SW1" H 1948 3855 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_B3U-1000P" V 1950 4000 60  0001 C CNN
F 3 "" V 1950 4000 60  0001 C CNN
	1    1900 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D0B6B1F
P 1300 4050
F 0 "#PWR04" H 1300 3800 50  0001 C CNN
F 1 "GND" H 1305 3877 50  0000 C CNN
F 2 "" H 1300 4050 50  0001 C CNN
F 3 "" H 1300 4050 50  0001 C CNN
	1    1300 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5D0B6B87
P 1900 4050
F 0 "#PWR06" H 1900 3800 50  0001 C CNN
F 1 "GND" H 1905 3877 50  0000 C CNN
F 2 "" H 1900 4050 50  0001 C CNN
F 3 "" H 1900 4050 50  0001 C CNN
	1    1900 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR018
U 1 1 5D0B6E22
P 3100 2600
F 0 "#PWR018" H 3100 2450 50  0001 C CNN
F 1 "+3V3" V 3115 2728 50  0000 L CNN
F 2 "" H 3100 2600 50  0001 C CNN
F 3 "" H 3100 2600 50  0001 C CNN
	1    3100 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR019
U 1 1 5D0B6E8A
P 3100 3400
F 0 "#PWR019" H 3100 3250 50  0001 C CNN
F 1 "+3V3" V 3115 3528 50  0000 L CNN
F 2 "" H 3100 3400 50  0001 C CNN
F 3 "" H 3100 3400 50  0001 C CNN
	1    3100 3400
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR01
U 1 1 5D0B731C
P 1200 4500
F 0 "#PWR01" H 1200 4350 50  0001 C CNN
F 1 "+3V3" V 1200 4650 50  0000 L CNN
F 2 "" H 1200 4500 50  0001 C CNN
F 3 "" H 1200 4500 50  0001 C CNN
	1    1200 4500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5D0B737B
P 1200 4600
F 0 "#PWR02" H 1200 4350 50  0001 C CNN
F 1 "GND" V 1200 4450 50  0000 R CNN
F 2 "" H 1200 4600 50  0001 C CNN
F 3 "" H 1200 4600 50  0001 C CNN
	1    1200 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_ALT D1
U 1 1 5D0F218E
P 6150 9400
F 0 "D1" H 6150 9500 50  0000 C CNN
F 1 "G" H 6250 9350 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6150 9400 50  0001 C CNN
F 3 "~" H 6150 9400 50  0001 C CNN
	1    6150 9400
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED_ALT D2
U 1 1 5D0F226B
P 6150 9600
F 0 "D2" H 6150 9700 50  0000 C CNN
F 1 "R" H 6250 9550 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6150 9600 50  0001 C CNN
F 3 "~" H 6150 9600 50  0001 C CNN
	1    6150 9600
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED_ALT D3
U 1 1 5D0F22EF
P 6150 9800
F 0 "D3" H 6150 9900 50  0000 C CNN
F 1 "B" H 6250 9750 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6150 9800 50  0001 C CNN
F 3 "~" H 6150 9800 50  0001 C CNN
	1    6150 9800
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5D0F23B7
P 5750 9400
F 0 "R4" V 5650 9400 50  0000 C CNN
F 1 "1K" V 5750 9400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5680 9400 50  0001 C CNN
F 3 "~" H 5750 9400 50  0001 C CNN
	1    5750 9400
	0    -1   1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5D0F2466
P 5750 9600
F 0 "R5" V 5650 9600 50  0000 C CNN
F 1 "1K" V 5750 9600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5680 9600 50  0001 C CNN
F 3 "~" H 5750 9600 50  0001 C CNN
	1    5750 9600
	0    -1   1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5D0F2518
P 5750 9800
F 0 "R6" V 5650 9800 50  0000 C CNN
F 1 "1K" V 5750 9800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5680 9800 50  0001 C CNN
F 3 "~" H 5750 9800 50  0001 C CNN
	1    5750 9800
	0    -1   1    0   
$EndComp
Wire Wire Line
	2600 1200 3000 1200
Wire Wire Line
	1950 1200 2400 1200
$Comp
L power:+3V3 #PWR023
U 1 1 5D01D557
P 4900 1200
F 0 "#PWR023" H 4900 1050 50  0001 C CNN
F 1 "+3V3" V 4915 1328 50  0000 L CNN
F 2 "" H 4900 1200 50  0001 C CNN
F 3 "" H 4900 1200 50  0001 C CNN
	1    4900 1200
	0    1    1    0   
$EndComp
$Comp
L Eclectronics:MCP1501T-20E_CHY U3
U 1 1 5D157410
P 8300 9600
F 0 "U3" H 8300 10017 50  0000 C CNN
F 1 "MCP1501T-20E_CHY" H 8300 9926 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 8300 9600 60  0001 C CNN
F 3 "" H 8300 9600 60  0001 C CNN
	1    8300 9600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5D17271D
P 8800 9800
F 0 "C10" H 8915 9846 50  0000 L CNN
F 1 "100pF" H 8915 9755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8838 9650 50  0001 C CNN
F 3 "~" H 8800 9800 50  0001 C CNN
	1    8800 9800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5D18CF78
P 8800 9950
F 0 "#PWR030" H 8800 9700 50  0001 C CNN
F 1 "GND" H 8805 9777 50  0000 C CNN
F 2 "" H 8800 9950 50  0001 C CNN
F 3 "" H 8800 9950 50  0001 C CNN
	1    8800 9950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR029
U 1 1 5D18D13B
P 8450 10000
F 0 "#PWR029" H 8450 9750 50  0001 C CNN
F 1 "GND" H 8455 9827 50  0000 C CNN
F 2 "" H 8450 10000 50  0001 C CNN
F 3 "" H 8450 10000 50  0001 C CNN
	1    8450 10000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5D18D222
P 8300 10000
F 0 "#PWR028" H 8300 9750 50  0001 C CNN
F 1 "GND" H 8305 9827 50  0000 C CNN
F 2 "" H 8300 10000 50  0001 C CNN
F 3 "" H 8300 10000 50  0001 C CNN
	1    8300 10000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5D18D309
P 8150 10000
F 0 "#PWR027" H 8150 9750 50  0001 C CNN
F 1 "GND" H 8155 9827 50  0000 C CNN
F 2 "" H 8150 10000 50  0001 C CNN
F 3 "" H 8150 10000 50  0001 C CNN
	1    8150 10000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 9400 7800 9450
Wire Wire Line
	7800 9450 7800 9600
Wire Wire Line
	7800 9600 7850 9600
Connection ~ 7800 9450
Wire Wire Line
	7800 9450 7850 9450
$Comp
L Device:C C9
U 1 1 5D215A92
P 7800 9800
F 0 "C9" H 7915 9846 50  0000 L CNN
F 1 "0.1µF" H 7915 9755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7838 9650 50  0001 C CNN
F 3 "~" H 7800 9800 50  0001 C CNN
	1    7800 9800
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5D215BFE
P 7800 9950
F 0 "#PWR026" H 7800 9700 50  0001 C CNN
F 1 "GND" H 7805 9777 50  0000 C CNN
F 2 "" H 7800 9950 50  0001 C CNN
F 3 "" H 7800 9950 50  0001 C CNN
	1    7800 9950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 9650 7800 9600
Connection ~ 7800 9600
$Comp
L power:+3V3 #PWR025
U 1 1 5D24D9C6
P 7800 9400
F 0 "#PWR025" H 7800 9250 50  0001 C CNN
F 1 "+3V3" H 7800 9550 50  0000 C CNN
F 2 "" H 7800 9400 50  0001 C CNN
F 3 "" H 7800 9400 50  0001 C CNN
	1    7800 9400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 9600 8800 9600
Wire Wire Line
	8800 9650 8800 9600
Connection ~ 8800 9600
Text Label 5500 4400 0    60   ~ 0
CH1
Text Label 5500 4200 0    60   ~ 0
CH2
Text Label 8900 9600 0    60   ~ 0
VREF
Text Label 5500 6000 0    60   ~ 0
D0
Text Label 5500 6200 0    60   ~ 0
D1
Text Label 5500 6800 0    60   ~ 0
D2
Text Label 5500 7000 0    60   ~ 0
D3
NoConn ~ 5500 7400
NoConn ~ 5500 7600
NoConn ~ 5500 7800
NoConn ~ 5500 8000
NoConn ~ 5500 8200
NoConn ~ 5500 8400
NoConn ~ 5500 10000
Text Label 14450 6300 2    60   ~ 0
1+
Text Label 14450 6200 2    60   ~ 0
1-
Text Label 14450 6100 2    60   ~ 0
2+
Text Label 14450 6000 2    60   ~ 0
2-
$Comp
L power:GND #PWR033
U 1 1 5D6F6DD6
P 14450 6600
F 0 "#PWR033" H 14450 6350 50  0001 C CNN
F 1 "GND" V 14455 6472 50  0000 R CNN
F 2 "" H 14450 6600 50  0001 C CNN
F 3 "" H 14450 6600 50  0001 C CNN
	1    14450 6600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5D6F7593
P 14450 7600
F 0 "#PWR032" H 14450 7350 50  0001 C CNN
F 1 "GND" V 14455 7472 50  0000 R CNN
F 2 "" H 14450 7600 50  0001 C CNN
F 3 "" H 14450 7600 50  0001 C CNN
	1    14450 7600
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR031
U 1 1 5D6F78C3
P 14450 6500
F 0 "#PWR031" H 14450 6350 50  0001 C CNN
F 1 "+3V3" V 14465 6628 50  0000 L CNN
F 2 "" H 14450 6500 50  0001 C CNN
F 3 "" H 14450 6500 50  0001 C CNN
	1    14450 6500
	0    -1   -1   0   
$EndComp
Text Label 14450 6700 2    60   ~ 0
D0
Text Label 14450 6800 2    60   ~ 0
D1
Text Label 14450 6900 2    60   ~ 0
D2
Text Label 14450 7000 2    60   ~ 0
D3
Text Label 5500 9000 0    60   ~ 0
CH1GAIN
Text Label 5500 8800 0    60   ~ 0
CH2GAIN
Wire Wire Line
	3000 1200 3150 1200
Connection ~ 3000 1200
Wire Wire Line
	4150 1200 4300 1200
NoConn ~ 3100 5400
NoConn ~ 3100 5800
NoConn ~ 5500 2600
NoConn ~ 5500 3200
NoConn ~ 5500 4000
$Sheet
S 9800 6300 2650 1600
U 5EDBCC9E
F0 "scope" 60
F1 "scope.sch" 60
F2 "VREF" I L 9800 7700 60 
F3 "1+" I L 9800 6900 60 
F4 "1-" I L 9800 7100 60 
F5 "2+" I L 9800 7300 60 
F6 "2-" I L 9800 7500 60 
F7 "CH1GAIN" I L 9800 6500 60 
F8 "CH2GAIN" I L 9800 6700 60 
F9 "CH1" O R 12450 6500 60 
F10 "CH2" O R 12450 6700 60 
$EndSheet
$Sheet
S 9800 2800 2650 2600
U 5EEE711A
F0 "wavegen" 60
F1 "wavegen.sch" 60
F2 "VREF" I L 9800 5200 60 
F3 "~SQ" I L 9800 3800 60 
F4 "DAC2" I L 9800 5000 60 
F5 "DAC1" I L 9800 4800 60 
F6 "VOFF" O R 12450 4200 60 
F7 "VOUT" O R 12450 4000 60 
F8 "WGGAIN" I L 9800 4600 60 
F9 "MCLK_DDS" I L 9800 3600 60 
F10 "MOSI_DDS" I L 9800 3400 60 
F11 "SCK_DDS" I L 9800 3200 60 
F12 "NCS_DDS" I L 9800 3000 60 
F13 "SCK_POT" I L 9800 4400 60 
F14 "MOSI_POT" I L 9800 4200 60 
F15 "NCS_POT" I L 9800 4000 60 
$EndSheet
Text Label 9750 7700 2    60   ~ 0
VREF
Wire Wire Line
	9750 7700 9800 7700
Wire Wire Line
	9750 5200 9800 5200
Text Label 9750 5200 2    60   ~ 0
VREF
Wire Wire Line
	9800 4800 9750 4800
Wire Wire Line
	9800 5000 9750 5000
Text Label 9750 5000 2    60   ~ 0
DAC2
Text Label 9750 4800 2    60   ~ 0
DAC1
Text Label 9750 6500 2    60   ~ 0
CH1GAIN
Text Label 9750 6700 2    60   ~ 0
CH2GAIN
Wire Wire Line
	9750 6500 9800 6500
Wire Wire Line
	9750 6700 9800 6700
Text Label 12500 6500 0    60   ~ 0
CH1
Text Label 12500 6700 0    60   ~ 0
CH2
Wire Wire Line
	12450 6500 12500 6500
Wire Wire Line
	9750 3000 9800 3000
Wire Wire Line
	9750 3200 9800 3200
Wire Wire Line
	9750 3400 9800 3400
Wire Wire Line
	9750 3600 9800 3600
Wire Wire Line
	9750 3800 9800 3800
Wire Wire Line
	9750 4000 9800 4000
Wire Wire Line
	9750 4200 9800 4200
Wire Wire Line
	9750 4400 9800 4400
Wire Wire Line
	9750 4600 9800 4600
Text Label 9750 3000 2    60   ~ 0
NCS_DDS
Text Label 9750 3200 2    60   ~ 0
SCK_DDS
Text Label 9750 3400 2    60   ~ 0
MOSI_DDS
Text Label 9750 3600 2    60   ~ 0
MCLK_DDS
Text Label 9750 3800 2    60   ~ 0
~SQ
Text Label 9750 4000 2    60   ~ 0
NCS_POT
Text Label 9750 4200 2    60   ~ 0
MOSI_POT
Text Label 9750 4400 2    60   ~ 0
SCK_POT
Text Label 9750 4600 2    60   ~ 0
WGGAIN
Text Label 5500 5600 0    60   ~ 0
NCS_DDS
Text Label 5500 8600 0    60   ~ 0
~SQ
Text Label 5500 9200 0    60   ~ 0
WGGAIN
Text Label 5500 6400 0    60   ~ 0
MCLK_DDS
Text Label 5500 6600 0    60   ~ 0
MOSI_POT
Text Label 5500 7200 0    60   ~ 0
SCK_POT
Text Label 3100 3800 2    60   ~ 0
NCS_POT
Text Label 5500 3600 0    60   ~ 0
MISO_POT
Text Label 5500 3800 0    60   ~ 0
MISO_DDS
Text Label 14450 5800 2    60   ~ 0
VOUT
Text Label 14450 5900 2    60   ~ 0
VOFF
Text Label 12500 4200 0    60   ~ 0
VOFF
Text Label 12500 4000 0    60   ~ 0
VOUT
Wire Wire Line
	12450 4000 12500 4000
Wire Wire Line
	12450 4200 12500 4200
Wire Wire Line
	9800 6900 9750 6900
Wire Wire Line
	9800 7100 9750 7100
Wire Wire Line
	9800 7300 9750 7300
Wire Wire Line
	9800 7500 9750 7500
Text Label 9750 6900 2    60   ~ 0
1+
Text Label 9750 7300 2    60   ~ 0
2+
Text Label 9750 7500 2    60   ~ 0
2-
Text Label 9750 7100 2    60   ~ 0
1-
$Comp
L Connector:Conn_01x06_Male J3
U 1 1 5EAE0F41
P 14650 6100
F 0 "J3" H 14622 5982 50  0000 R CNN
F 1 "Analog" H 14622 6073 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 14650 6100 50  0001 C CNN
F 3 "~" H 14650 6100 50  0001 C CNN
	1    14650 6100
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Male J4
U 1 1 5EAE2ADE
P 14650 6800
F 0 "J4" H 14622 6682 50  0000 R CNN
F 1 "Digital" H 14622 6773 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 14650 6800 50  0001 C CNN
F 3 "~" H 14650 6800 50  0001 C CNN
	1    14650 6800
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5EAE3424
P 14650 7300
F 0 "J5" H 14622 7182 50  0000 R CNN
F 1 "Power1" H 14622 7273 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 7300 50  0001 C CNN
F 3 "~" H 14650 7300 50  0001 C CNN
	1    14650 7300
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5EAE3BB1
P 14650 7600
F 0 "J6" H 14622 7482 50  0000 R CNN
F 1 "Power2" H 14622 7573 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 14650 7600 50  0001 C CNN
F 3 "~" H 14650 7600 50  0001 C CNN
	1    14650 7600
	-1   0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR082
U 1 1 5EB0CAC3
P 14450 7500
F 0 "#PWR082" H 14450 7350 50  0001 C CNN
F 1 "+3V3" V 14465 7628 50  0000 L CNN
F 2 "" H 14450 7500 50  0001 C CNN
F 3 "" H 14450 7500 50  0001 C CNN
	1    14450 7500
	0    -1   -1   0   
$EndComp
$Comp
L Eclectronics:TLE2426D U11
U 1 1 5EB6C984
P 10400 9600
F 0 "U11" H 10400 10087 60  0000 C CNN
F 1 "TLE2426D" H 10400 9981 60  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 10400 9700 60  0001 C CNN
F 3 "" H 10400 9700 60  0001 C CNN
	1    10400 9600
	1    0    0    -1  
$EndComp
NoConn ~ 10250 9950
NoConn ~ 10400 9950
NoConn ~ 10550 9950
NoConn ~ 10700 9950
$Comp
L power:GND #PWR083
U 1 1 5EB8A1E2
P 10100 9950
F 0 "#PWR083" H 10100 9700 50  0001 C CNN
F 1 "GND" H 10105 9777 50  0000 C CNN
F 2 "" H 10100 9950 50  0001 C CNN
F 3 "" H 10100 9950 50  0001 C CNN
	1    10100 9950
	1    0    0    -1  
$EndComp
Text Label 14450 7300 2    60   ~ 0
2V5
Text Label 10900 9400 0    60   ~ 0
2V5
$Comp
L power:GND #PWR084
U 1 1 5EB90BE6
P 10950 9950
F 0 "#PWR084" H 10950 9700 50  0001 C CNN
F 1 "GND" H 10955 9777 50  0000 C CNN
F 2 "" H 10950 9950 50  0001 C CNN
F 3 "" H 10950 9950 50  0001 C CNN
	1    10950 9950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 9600 10950 9600
Wire Wire Line
	10950 9600 10950 9650
Text Label 3100 5000 2    60   ~ 0
SCK_DDS
Text Label 3100 5200 2    60   ~ 0
MOSI_DDS
NoConn ~ 5500 4800
NoConn ~ 5500 5000
NoConn ~ 5500 5200
NoConn ~ 5500 5400
Wire Wire Line
	12450 6700 12500 6700
NoConn ~ 3100 6000
NoConn ~ 3100 6200
NoConn ~ 3100 6400
$Comp
L power:+5V #PWR0104
U 1 1 5ECB6A5D
P 2400 1150
F 0 "#PWR0104" H 2400 1000 50  0001 C CNN
F 1 "+5V" H 2415 1323 50  0000 C CNN
F 2 "" H 2400 1150 50  0001 C CNN
F 3 "" H 2400 1150 50  0001 C CNN
	1    2400 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1150 2400 1200
Connection ~ 2400 1200
Wire Wire Line
	2400 1200 2600 1200
$Comp
L power:+5V #PWR0105
U 1 1 5ECC3C2D
P 14450 7200
F 0 "#PWR0105" H 14450 7050 50  0001 C CNN
F 1 "+5V" V 14465 7328 50  0000 L CNN
F 2 "" H 14450 7200 50  0001 C CNN
F 3 "" H 14450 7200 50  0001 C CNN
	1    14450 7200
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5ECC5625
P 9850 9350
F 0 "#PWR0106" H 9850 9200 50  0001 C CNN
F 1 "+5V" H 9865 9523 50  0000 C CNN
F 2 "" H 9850 9350 50  0001 C CNN
F 3 "" H 9850 9350 50  0001 C CNN
	1    9850 9350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 9350 9850 9400
Wire Wire Line
	9850 9400 9900 9400
$Comp
L Device:C C38
U 1 1 5EB8FD94
P 10950 9800
F 0 "C38" H 11065 9846 50  0000 L CNN
F 1 "1µF" H 11065 9755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10988 9650 50  0001 C CNN
F 3 "~" H 10950 9800 50  0001 C CNN
	1    10950 9800
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 5EDF4CEE
P 9050 9600
F 0 "TP1" V 9004 9788 50  0000 L CNN
F 1 "VREF" V 9095 9788 50  0000 L CNN
F 2 "Eclectronics:60mil_testpoint" H 9250 9600 50  0001 C CNN
F 3 "~" H 9250 9600 50  0001 C CNN
	1    9050 9600
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 9600 9050 9600
$Comp
L Eclectronics:PIC24FJ128GC006-I_MR U2
U 1 1 60C8A594
P 4300 6300
F 0 "U2" H 4300 10287 60  0000 C CNN
F 1 "PIC24FJ128GC006-I_MR" H 4300 10181 60  0000 C CNN
F 2 "Eclectronics:pic24fj128gc006" H 4300 6700 60  0001 C CNN
F 3 "" H 4300 6700 60  0001 C CNN
	1    4300 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 9800 3050 10000
Wire Wire Line
	3100 10000 3050 10000
Connection ~ 3050 10000
Wire Wire Line
	3050 10000 3050 10050
NoConn ~ 5500 2800
NoConn ~ 5500 3000
NoConn ~ 1200 4900
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 60D2439A
P 1000 4600
F 0 "J1" H 1000 4950 50  0000 C CNN
F 1 "ICD3 Header" H 1000 4150 50  0000 C CNN
F 2 "Eclectronics:ICD3_header" H 1000 4600 50  0001 C CNN
F 3 "~" H 1000 4600 50  0001 C CNN
	1    1000 4600
	-1   0    0    -1  
$EndComp
$EndSCHEMATC