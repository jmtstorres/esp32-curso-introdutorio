#ifndef MUSIC_H
#define MUSIC_H

#define TEMPO 500 //MS

#define BREVE         TEMPO*8 //MS
#define SEMIBREVE     TEMPO*4 //MS
#define MINIMA        TEMPO*2 //MS
#define SEMINIMA      TEMPO   //MS
#define COLCHEIA      TEMPO/2 //MS
#define SEMICOLCHEIA  TEMPO/4 //MS
#define FUSA          TEMPO/8 //MS
#define SEMIFUSA      TEMPO/16//MS

#define PAUSA 0

#define N_C0	16
#define N_CS0 17
#define N_DB0 17
#define N_D0	18
#define N_DS0 19
#define N_EB0 19
#define N_E0	20
#define N_F0	21
#define N_FS0 23
#define N_GB0 23
#define N_G0	24
#define N_GS0 25
#define N_AB0 25
#define N_A0	27
#define N_AS0 29
#define N_BB0 29
#define N_B0	30
#define N_C1	32
#define N_CS1 34
#define N_DB1 34
#define N_D1	36
#define N_DS1 38
#define N_EB1 38
#define N_E1	41
#define N_F1	43
#define N_FS1 46
#define N_GB1 46
#define N_G1	49
#define N_GS1 51
#define N_AB1 51
#define N_A1	55
#define N_AS1 58
#define N_BB1 58
#define N_B1	61
#define N_C2	65
#define N_CS2 69
#define N_DB2 69
#define N_D2	73
#define N_DS2 77
#define N_EB2 77
#define N_E2	82
#define N_F2	87
#define N_FS2 92
#define N_GB2 92
#define N_G2	98
#define N_GS2 103
#define N_AB2 103
#define N_A2	110
#define N_AS2 116
#define N_BB2 116
#define N_B2	123
#define N_C3	130
#define N_CS3 138
#define N_DB3 138
#define N_D3	146
#define N_DS3 155
#define N_EB3 155
#define N_E3	164
#define N_F3	174
#define N_FS3 185
#define N_GB3 185
#define N_G3	196
#define N_GS3 207
#define N_AB3 207
#define N_A3	220
#define N_AS3 233
#define N_BB3 233
#define N_B3	246
#define N_C4	261
#define N_CS4	277
#define N_DB4	277
#define N_D4	293
#define N_DS4	311
#define N_EB4	311
#define N_E4	329
#define N_F4	349
#define N_FS4	369
#define N_GB4	369
#define N_G4	392
#define N_GS4	415
#define N_AB4	415
#define N_A4	440
#define N_AS4	466
#define N_BB4	466
#define N_B4	493
#define N_C5	523
#define N_CS5	554
#define N_DB5	554
#define N_D5	587
#define N_DS5	622
#define N_EB5	622
#define N_E5	659
#define N_F5	698
#define N_FS5	739
#define N_GB5	739
#define N_G5	783
#define N_GS5	830
#define N_AB5	830
#define N_A5	880
#define N_AS5	932
#define N_BB5	932
#define N_B5	987
#define N_C6	1046
#define N_CS6	1108
#define N_DB6	1108
#define N_D6	1174
#define N_DS6	1244
#define N_EB6	1244
#define N_E6	1318
#define N_F6	1396
#define N_FS6	1479
#define N_GB6	1479
#define N_G6	1567
#define N_GS6	1661
#define N_AB6	1661
#define N_A6	1760
#define N_AS6	1864
#define N_BB6	1864
#define N_B6	1975
#define N_C7	2093
#define N_CS7	2217
#define N_DB7	2217
#define N_D7	2349
#define N_DS7	2489
#define N_EB7	2489
#define N_E7	2637
#define N_F7	2793
#define N_FS7	2959
#define N_GB7	2959
#define N_G7	3135
#define N_GS7	3322
#define N_AB7	3322
#define N_A7	3520
#define N_AS7	3729
#define N_BB7	3729
#define N_B7	3951
#define N_C8	4186
#define N_CS8	4434
#define N_DB8	4434
#define N_D8	4698
#define N_DS8	4978
#define N_EB8	4978
#define N_E8	5274
#define N_F8	5587
#define N_FS8	5919
#define N_GB8	5919
#define N_G8	6271
#define N_GS8	6644
#define N_AB8	6644
#define N_A8	7040
#define N_AS8	7458
#define N_BB8	7458
#define N_B8	7902

#include <Arduino.h>

void initializeBuzzer();
void play(int partitura[][2]);
void playInitSong();
void playAcessSong();
void playDeniedSong();

#endif