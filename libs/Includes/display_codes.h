/*
 * This file contains definitions of Display Codes.
 * Connections:
 * Board Pins | Display Pins
 * PB0 		  | A
 * PB1 		  | B
 * PB2 		  | C
 * PB3 		  | D
 * PB4 		  | E
 * PB5 		  | F
 * PB6 		  | G
 * PB7        | Anode DIG-1
 * PB8        | Anode DIG-2
 * PB9        | Anode DIG-3
 * PB10       | Anode DIG-4
 * PB11       | Anode DIG-5
 * PB12       | Anode DIG-6
 *
 *	  PB0
 * PB5   PB1
 * PB5   PB1
 *    PB6
 * PB4   PB2
 * PB4   PB2
 *    PB3
 */

#define DISP_0 0x3F
#define DISP_1 0x06
#define DISP_2 0x5B
#define DISP_3 0x4F
#define DISP_4 0x66
#define DISP_5 0x6D
#define DISP_6 0x7D
#define DISP_7 0x07
#define DISP_8 0x7F
#define DISP_9 0x6F
#define DISP_H 0x76 
#define DISP_A 0x77
#define DISP_E 0x79
#define DISP_L 0x38
#define DISP_P 0x33
#define DIG1_MSK 0x1F00
#define DIG2_MSK 0x1E80
#define DIG3_MSK 0x1D80
#define DIG4_MSK 0x1B80
#define DIG5_MSK 0x1780
#define DIG6_MSK 0xF80
