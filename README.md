# Synchronizačný firmvér pre STM32 LiDAR + GPS + IMU

## Prehľad

Tento projekt obsahuje aplikáciu  STM32 navrhnutú na synchronizáciu a emuláciu:

* Časových správ GPS (NMEA GPRMC)
* Zberu dát z IMU senzora
* Synchronizačného signálu pre LiDAR (PPS)
* Hardvérového triggerovania kamery

Firmvér je implementovaný na mikrokontroléri STM32F103C8T6 (Bluepill) s využitím ovládačov STM32 HAL vygenerovaných nástrojom STM32CubeMX.

Projekt využíva:

* UART komunikáciu
* DMA prenosy
* I2C zber dát z IMU
* Synchronizáciu pomocou externých prerušení* Časovanie PPS (Pulse Per Second) založené na časovačoch
* PWM výstupy

Riešenie je navrhnuté vzhľadom na nasledujúcu špecifikáciu:
- LiDAR: Hesai XT-16 ([odkaz na datasheet](https://www.hesaitech.com/wp-content/uploads/2025/04/PandarXT-16_User_Manual_X02-en-250410.pdf))
- IMU: ICM-40609-D ([odkaz na datasheet](https://www.mouser.com/datasheet/2/400/ds_000330_icm_40609_d_v1_2-3420717.pdf?srsltid=AfmBOortTJJlb19XL3UqeWnBT42KF1afshsWXbI3Jm0jdUoGn5Cy7GmG))
- Požiadavky pre FAST-LIVO2 synchronizáciu ([odkaz na repozitár](https://github.com/Rhymer-Lcy/FAST-LIVO2-ROS2-MID360-Fisheye))

---

# Návod na spustenie

## Požiadavky

Požadované nástroje:

* STM32CubeIDE
* ST-Link Utility alebo STM32CubeProgrammer
* Programátor/debugger ST-Link V2

---

## Postup kompilácie

1. Otvorte projekt v prostredí STM32CubeIDE.
2. Vyberte:

```text
Project -> Build Configurations -> Set Active -> Release
```

3. Kompilácia firmvéru:

```text
Project -> Build Project
```

Vygenerovaný binárny súbor sa bude nachádzať v priečinku:

```text
/Release
```

---

## Postup nahrávania

1. Pripojte programátor ST-Link k vývojovej doske STM32F103 Bluepill.
2. Otvorte ST-Link Utility alebo STM32CubeProgrammer.
3. Pripojte sa k cieľovému zariadeniu (target).
4. Načítajte vygenerovaný súbor `.hex` alebo `.bin`.
5. Nahrajte firmvér.

---

## Postup po nahratí

Po dokončení nahrávania:

1. Reštartujte alebo odpojte a znova pripojte napájanie STM32.
2. Firmvér sa stane plne funkčným až po reštarte.

Tento reštart je nevyhnutný pre správnu inicializáciu synchronizačných periférií a stavových automatov DMA.

---

## Postup obnovy

V prípade zlyhania synchronizácie alebo neočakávaného správania počas behu programu **reštartujte zariadenie STM32**, stačí odpojiť a pripojiť napájanie.

Nie je potrebný žiadny dodatočný postup obnovy.

---

## Vývojové prostredie

Projekt využíva nasledujúce nástroje:

* STM32CubeIDE
* STM32CubeMX
* STM32 HAL (knižnica)

Cieľová rada MCU:

```text
STM32F1xx
```

V tomto projekte využívame dosku STM32F103 Bluepill.

---

# Hlavné funkcie

## Emulácia GPS NMEA

Firmvér periodicky generuje platnú NMEA vetu `$GPRMC` a odosiela ju cez UART s využitím DMA prenosu.

Príklad vygenerovanej vety:

```text
$GPRMC,121530,A,4808.0000,N,01706.0000,E,0.0,0.0,090323,,,A*XX
```

Kontrolný súčet sa vypočítava dynamicky pred každým odoslaním.

### Tok programu pri prenose GPS

1. Nastane udalosť časovača
2. Interné softvérové hodiny sa inkrementujú
3. Firmvér vygeneruje správu GPRMC pre aktuálny čas
4. Vypočíta sa NMEA kontrolný súčet
5. Správa sa odošle cez UART1 pomocou DMA

---

## Zber dát z IMU

Firmvér komunikuje s 6DOF IMU senzorom cez zbernicu I2C.

Ovládač IMU podporuje:

* Konfiguráciu akcelerometra
* Konfiguráciu gyroskopu
* Meranie teploty
* Sekvenčné čítanie surových dát
* Overenie zariadenia pomocou registra `WHO_AM_I`
* Reset zariadenia

Relevantné súbory:

* `Core/Src/IMU.c`
* `Core/Inc/IMU.h`

---

# Synchronizačná architektúra

## Synchronizácia externým prerušením

Pin IMU senzora indikujúci pripravenosť dát (DRDY - Data Ready) spúšťa prerušenie EXTI.

Vo vnútri rutiny prerušenia sa vykoná:

* Zachytenie aktuálneho tiku časovača
* Pridanie metadát s časovou pečiatkou (timestamp)
* Nastavenie príznakov (flags) pre bezpečný zber dát pomocou DMA

To umožňuje:

* Presné priradenie času
* Synchronizáciu medzi dátovými tokmi LiDAR / GPS / IMU
* Deterministické časovanie zberu dát

---

# Konfigurácia UART

## USART1

Použitie:

* Prenos GPS NMEA viet

Konfigurácia:

* Prenosová rýchlosť: 9600 Bd
* DMA prenos

## USART2

Použitie:

* Výstup surových dát z IMU
* Diagnostika (Debug)

Konfigurácia:

* Prenosová rýchlosť: 115200 Bd

---

# Konfigurácia časovačov

## TIM1

TIM1 sa používa ako hlavný synchronizačný časovač. Generuje 1 Hz PPS signál pre synchronizácu LiDARu a poskytuje čas s vysokým rozlíšením pre dáta IMU.

Pre hodnotu ARR (Auto-Reload Register) sme zvolili hodnotu blízku maximu 16-bitového celého čísla bez znamienka, aby sme dosiahli maximálne rozlíšenie časovej značky.

Konfigurácia časovača:

* Prescaler = 1200 - 1
* Period = 60000 - 1
* PWM výstup
* PWM pulse = 30000

---

## TIM2

TIM2 sa používa na hardvérové spúšťanie (triggerovanie) kamery.

Časovač je nakonfigurovaný ako PWM výstup a generuje periodický spúšťací impulz vhodný pre externú synchronizáciu kamery.

Konfigurácia časovača:

* Prescaler = 7199
* Period = 999
* PWM pulse = 499

### Výpočet frekvencie TIM2

Taktovacia frekvencia systému:

```text
72 MHz
```

Vstupný takt časovača:

```text
72 MHz / 7200 = 10 kHz
```

Frekvencia PWM:

```text
10 kHz / 1000 = 10 Hz
```

Preto:

```text
Spúšťacia frekvencia TIM2 = 10 Hz
```

Strieda PWM (PWM znamená ŠIM):

```text
500 / 1000 = 50%
```

Tento časovač poskytuje periodické spúšťacie impulzy pre kameru s frekvenciou 10 Hz.

---

# Výpočty časovania

## Systémový takt (System Clock)

MCU využíva:

* Externý oscilátor HSE
* Násobičku PLL x9

Typický takt pre STM32F103:

```text
8 MHz × 9 = 72 MHz
```

Preto:

```text
SYSCLK = 72 MHz
```

---

## Frekvencia tikov TIM1

Preddelička časovača:

```text
PSC = 1200 - 1
```

Takt časovača:

```text
72 MHz / 1200 = 60 kHz
```

Perióda jedného tiku časovača:

```text
1 / 60000 = 16.67 us
```

---

## Perióda pretečenia TIM1

Perióda časovača (ARR):

```text
ARR = 60000 - 1
```

Frekvencia pretečenia:

```text
60000 / 60000 Hz = 1 sekunda
```

Preto:

```text
Perióda pretečenia TIM1 = 1 sekunda
```

Tento časovač sa používa ako zdroj PPS.

---

## Logika časovania PPS

Datasheed LiDAR-u uvádza, že GPRMC veta má byť poslaná po klesajúcej hrane PPS signálu, čo v našom projekte predstavuje čas približne 500ms od začiatku periódy. Naša implementácia využíva prerušenie pri klesajúcej hrane PPS signálu, v rámci ktorého sa nastaví príznak (flag), ktorý v hlavnej slučke spúšťa posielanie GPRMC vety. 

To zaisťuje:

* Posielanie GPS času LiDAR-u v súlade s dokumentáciou
* Stabilné časovanie hrán PPS
* Deterministické generovanie časových pečiatok

---

# Využitie DMA

DMA sa používa na UART prenos GPS správ.

Výhody:

* Zníženie zaťaženia procesora v hlavnej slučke
* Neblokujúce prenosy cez UART
* Lepší determinizmus časovania

---

# Použité callback funkcie prerušení

Projekt sa vo veľkej miere spolieha na HAL callback funkcie.

Implementované callbacky zahŕňajú:

* `HAL_GPIO_EXTI_Callback`
* `HAL_TIM_PeriodElapsedCallback`
* `HAL_I2C_MemRxCpltCallback`
* `HAL_I2C_ErrorCallback`

Tieto callbacky zabezpečujú:

* Asynchrónny zber dát zo senzorov
* Udalosťami riadenú synchronizáciu
* Spracovanie časových pečiatok

---

# Štruktúra dátového balíka IMU

Firmvér alokuje:

```c
#define IMU_DATA_RAW_SIZE (14 + 4 + 2)
```

Zloženie balíka:

| Sekcia | Veľkosť |
| --- | --- |
| Surové dáta z IMU | 14 bajtov |
| Hlavná časť časovej pečiatky (Timestamp major) | 2 bajty |
| Vedľajšia časť časovej pečiatky (Timestamp minor) | 2 bajty |
| Ukončenie riadka - pomáha so synchronizáciou | 2 bajty |

Celkovo:

```text
20 bajtov
```

---

# Softvérová architektúra

## Hlavná slučka

Hlavná slučka vykonáva:

1. Plánovanie správ GPS
2. Riadenie stavu DMA pre IMU
3. Čítanie z pamäte cez I2C
4. Správu synchronizácie
5. Riadenie časovania spúšťania kamery

Architektúra je primárne:

* Riadená prerušeniami
* Využívajúca DMA prenosy
* Neblokujúca

---

# Dôležité zdrojové súbory

| Súbor | Účel |
| --- | --- |
| `main.c` | Hlavná logika aplikácie |
| `IMU.c` | Implementácia ovládača IMU |
| `IMU.h` | Rozhranie ovládača IMU |
| `usart.c` | Konfigurácia UART |
| `tim.c` | Konfigurácia časovačov |
| `gpio.c` | Inicializácia GPIO |
| `i2c.c` | Konfigurácia I2C |

---

# Ako to funguje

## Prehľad toku na vysokej úrovni

### Emulácia GPRMC

```text
TIM1 -> Časovanie PPS
        ↓
Vygenerovanie GPS správy
        ↓
Odoslanie GPS cez UART DMA
```

### Zber dát z IMU

```text
Nastane prerušenie DRDY z IMU
        ↓
Zachytenie presného času
        ↓
Spustenie sekvenčného čítania cez I2C
        ↓
Odoslanie dát z IMU cez UART2
```

### Hardvérové časovanie kamery

```text
PWM výstup z TIM2
        ↓
Generovanie taktovacieho signálu s frekvenciou 10 Hz
        ↓
Spúšťací impulz kamery
```

---

# Poznámky

Projekt je zameraný na presnú časovú synchronizáciu medzi:

* Časovaním GPS
* Spúšťaním LiDARu
* Zberom dát z IMU
* Hardvérovým spúšťaním kamery

Implementácia využíva efektívne techniky vnorených systémov:

* DMA
* Prerušenia
* Časové značky
* Asynchrónne prenosy
* PWM synchronizáciu

Vďaka tomu je tento firmvér vhodný pre našu aplikáciu vyžadujúcu synchronizáciu senzorov v reálnom čase.