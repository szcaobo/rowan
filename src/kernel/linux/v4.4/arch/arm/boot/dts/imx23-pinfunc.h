/*
 * Header providing constants for i.MX23 pinctrl bindings.
 *
 * Copyright (C) 2013 Lothar Waßmann <LW@KARO-electronics.de>
 *
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#ifndef __DT_BINDINGS_MX23_PINCTRL_H__
#define __DT_BINDINGS_MX23_PINCTRL_H__

#include "mxs-pinfunc.h"

#define MX23_PAD_GPMI_D00__GPMI_D00			0x0000
#define MX23_PAD_GPMI_D01__GPMI_D01			0x0010
#define MX23_PAD_GPMI_D02__GPMI_D02			0x0020
#define MX23_PAD_GPMI_D03__GPMI_D03			0x0030
#define MX23_PAD_GPMI_D04__GPMI_D04			0x0040
#define MX23_PAD_GPMI_D05__GPMI_D05			0x0050
#define MX23_PAD_GPMI_D06__GPMI_D06			0x0060
#define MX23_PAD_GPMI_D07__GPMI_D07			0x0070
#define MX23_PAD_GPMI_D08__GPMI_D08			0x0080
#define MX23_PAD_GPMI_D09__GPMI_D09			0x0090
#define MX23_PAD_GPMI_D10__GPMI_D10			0x00a0
#define MX23_PAD_GPMI_D11__GPMI_D11			0x00b0
#define MX23_PAD_GPMI_D12__GPMI_D12			0x00c0
#define MX23_PAD_GPMI_D13__GPMI_D13			0x00d0
#define MX23_PAD_GPMI_D14__GPMI_D14			0x00e0
#define MX23_PAD_GPMI_D15__GPMI_D15			0x00f0
#define MX23_PAD_GPMI_CLE__GPMI_CLE			0x0100
#define MX23_PAD_GPMI_ALE__GPMI_ALE			0x0110
#define MX23_PAD_GPMI_CE2N__GPMI_CE2N			0x0120
#define MX23_PAD_GPMI_RDY0__GPMI_RDY0			0x0130
#define MX23_PAD_GPMI_RDY1__GPMI_RDY1			0x0140
#define MX23_PAD_GPMI_RDY2__GPMI_RDY2			0x0150
#define MX23_PAD_GPMI_RDY3__GPMI_RDY3			0x0160
#define MX23_PAD_GPMI_WPN__GPMI_WPN			0x0170
#define MX23_PAD_GPMI_WRN__GPMI_WRN			0x0180
#define MX23_PAD_GPMI_RDN__GPMI_RDN			0x0190
#define MX23_PAD_AUART1_CTS__AUART1_CTS			0x01a0
#define MX23_PAD_AUART1_RTS__AUART1_RTS			0x01b0
#define MX23_PAD_AUART1_RX__AUART1_RX			0x01c0
#define MX23_PAD_AUART1_TX__AUART1_TX			0x01d0
#define MX23_PAD_I2C_SCL__I2C_SCL			0x01e0
#define MX23_PAD_I2C_SDA__I2C_SDA			0x01f0
#define MX23_PAD_LCD_D00__LCD_D00			0x1000
#define MX23_PAD_LCD_D01__LCD_D01			0x1010
#define MX23_PAD_LCD_D02__LCD_D02			0x1020
#define MX23_PAD_LCD_D03__LCD_D03			0x1030
#define MX23_PAD_LCD_D04__LCD_D04			0x1040
#define MX23_PAD_LCD_D05__LCD_D05			0x1050
#define MX23_PAD_LCD_D06__LCD_D06			0x1060
#define MX23_PAD_LCD_D07__LCD_D07			0x1070
#define MX23_PAD_LCD_D08__LCD_D08			0x1080
#define MX23_PAD_LCD_D09__LCD_D09			0x1090
#define MX23_PAD_LCD_D10__LCD_D10			0x10a0
#define MX23_PAD_LCD_D11__LCD_D11			0x10b0
#define MX23_PAD_LCD_D12__LCD_D12			0x10c0
#define MX23_PAD_LCD_D13__LCD_D13			0x10d0
#define MX23_PAD_LCD_D14__LCD_D14			0x10e0
#define MX23_PAD_LCD_D15__LCD_D15			0x10f0
#define MX23_PAD_LCD_D16__LCD_D16			0x1100
#define MX23_PAD_LCD_D17__LCD_D17			0x1110
#define MX23_PAD_LCD_RESET__LCD_RESET			0x1120
#define MX23_PAD_LCD_RS__LCD_RS				0x1130
#define MX23_PAD_LCD_WR__LCD_WR				0x1140
#define MX23_PAD_LCD_CS__LCD_CS				0x1150
#define MX23_PAD_LCD_DOTCK__LCD_DOTCK			0x1160
#define MX23_PAD_LCD_ENABLE__LCD_ENABLE			0x1170
#define MX23_PAD_LCD_HSYNC__LCD_HSYNC			0x1180
#define MX23_PAD_LCD_VSYNC__LCD_VSYNC			0x1190
#define MX23_PAD_PWM0__PWM0				0x11a0
#define MX23_PAD_PWM1__PWM1				0x11b0
#define MX23_PAD_PWM2__PWM2				0x11c0
#define MX23_PAD_PWM3__PWM3				0x11d0
#define MX23_PAD_PWM4__PWM4				0x11e0
#define MX23_PAD_SSP1_CMD__SSP1_CMD			0x2000
#define MX23_PAD_SSP1_DETECT__SSP1_DETECT		0x2010
#define MX23_PAD_SSP1_DATA0__SSP1_DATA0			0x2020
#define MX23_PAD_SSP1_DATA1__SSP1_DATA1			0x2030
#define MX23_PAD_SSP1_DATA2__SSP1_DATA2			0x2040
#define MX23_PAD_SSP1_DATA3__SSP1_DATA3			0x2050
#define MX23_PAD_SSP1_SCK__SSP1_SCK			0x2060
#define MX23_PAD_ROTARYA__ROTARYA			0x2070
#define MX23_PAD_ROTARYB__ROTARYB			0x2080
#define MX23_PAD_EMI_A00__EMI_A00			0x2090
#define MX23_PAD_EMI_A01__EMI_A01			0x20a0
#define MX23_PAD_EMI_A02__EMI_A02			0x20b0
#define MX23_PAD_EMI_A03__EMI_A03			0x20c0
#define MX23_PAD_EMI_A04__EMI_A04			0x20d0
#define MX23_PAD_EMI_A05__EMI_A05			0x20e0
#define MX23_PAD_EMI_A06__EMI_A06			0x20f0
#define MX23_PAD_EMI_A07__EMI_A07			0x2100
#define MX23_PAD_EMI_A08__EMI_A08			0x2110
#define MX23_PAD_EMI_A09__EMI_A09			0x2120
#define MX23_PAD_EMI_A10__EMI_A10			0x2130
#define MX23_PAD_EMI_A11__EMI_A11			0x2140
#define MX23_PAD_EMI_A12__EMI_A12			0x2150
#define MX23_PAD_EMI_BA0__EMI_BA0			0x2160
#define MX23_PAD_EMI_BA1__EMI_BA1			0x2170
#define MX23_PAD_EMI_CASN__EMI_CASN			0x2180
#define MX23_PAD_EMI_CE0N__EMI_CE0N			0x2190
#define MX23_PAD_EMI_CE1N__EMI_CE1N			0x21a0
#define MX23_PAD_GPMI_CE1N__GPMI_CE1N			0x21b0
#define MX23_PAD_GPMI_CE0N__GPMI_CE0N			0x21c0
#define MX23_PAD_EMI_CKE__EMI_CKE			0x21d0
#define MX23_PAD_EMI_RASN__EMI_RASN			0x21e0
#define MX23_PAD_EMI_WEN__EMI_WEN			0x21f0
#define MX23_PAD_EMI_D00__EMI_D00			0x3000
#define MX23_PAD_EMI_D01__EMI_D01			0x3010
#define MX23_PAD_EMI_D02__EMI_D02			0x3020
#define MX23_PAD_EMI_D03__EMI_D03			0x3030
#define MX23_PAD_EMI_D04__EMI_D04			0x3040
#define MX23_PAD_EMI_D05__EMI_D05			0x3050
#define MX23_PAD_EMI_D06__EMI_D06			0x3060
#define MX23_PAD_EMI_D07__EMI_D07			0x3070
#define MX23_PAD_EMI_D08__EMI_D08			0x3080
#define MX23_PAD_EMI_D09__EMI_D09			0x3090
#define MX23_PAD_EMI_D10__EMI_D10			0x30a0
#define MX23_PAD_EMI_D11__EMI_D11			0x30b0
#define MX23_PAD_EMI_D12__EMI_D12			0x30c0
#define MX23_PAD_EMI_D13__EMI_D13			0x30d0
#define MX23_PAD_EMI_D14__EMI_D14			0x30e0
#define MX23_PAD_EMI_D15__EMI_D15			0x30f0
#define MX23_PAD_EMI_DQM0__EMI_DQM0			0x3100
#define MX23_PAD_EMI_DQM1__EMI_DQM1			0x3110
#define MX23_PAD_EMI_DQS0__EMI_DQS0			0x3120
#define MX23_PAD_EMI_DQS1__EMI_DQS1			0x3130
#define MX23_PAD_EMI_CLK__EMI_CLK			0x3140
#define MX23_PAD_EMI_CLKN__EMI_CLKN			0x3150
#define MX23_PAD_GPMI_D00__LCD_D8			0x0001
#define MX23_PAD_GPMI_D01__LCD_D9			0x0011
#define MX23_PAD_GPMI_D02__LCD_D10			0x0021
#define MX23_PAD_GPMI_D03__LCD_D11			0x0031
#define MX23_PAD_GPMI_D04__LCD_D12			0x0041
#define MX23_PAD_GPMI_D05__LCD_D13			0x0051
#define MX23_PAD_GPMI_D06__LCD_D14			0x0061
#define MX23_PAD_GPMI_D07__LCD_D15			0x0071
#define MX23_PAD_GPMI_D08__LCD_D18			0x0081
#define MX23_PAD_GPMI_D09__LCD_D19			0x0091
#define MX23_PAD_GPMI_D10__LCD_D20			0x00a1
#define MX23_PAD_GPMI_D11__LCD_D21			0x00b1
#define MX23_PAD_GPMI_D12__LCD_D22			0x00c1
#define MX23_PAD_GPMI_D13__LCD_D23			0x00d1
#define MX23_PAD_GPMI_D14__AUART2_RX			0x00e1
#define MX23_PAD_GPMI_D15__AUART2_TX			0x00f1
#define MX23_PAD_GPMI_CLE__LCD_D16			0x0101
#define MX23_PAD_GPMI_ALE__LCD_D17			0x0111
#define MX23_PAD_GPMI_CE2N__ATA_A2			0x0121
#define MX23_PAD_AUART1_RTS__IR_CLK			0x01b1
#define MX23_PAD_AUART1_RX__IR_RX			0x01c1
#define MX23_PAD_AUART1_TX__IR_TX			0x01d1
#define MX23_PAD_I2C_SCL__GPMI_RDY2			0x01e1
#define MX23_PAD_I2C_SDA__GPMI_CE2N			0x01f1
#define MX23_PAD_LCD_D00__ETM_DA8			0x1001
#define MX23_PAD_LCD_D01__ETM_DA9			0x1011
#define MX23_PAD_LCD_D02__ETM_DA10			0x1021
#define MX23_PAD_LCD_D03__ETM_DA11			0x1031
#define MX23_PAD_LCD_D04__ETM_DA12			0x1041
#define MX23_PAD_LCD_D05__ETM_DA13			0x1051
#define MX23_PAD_LCD_D06__ETM_DA14			0x1061
#define MX23_PAD_LCD_D07__ETM_DA15			0x1071
#define MX23_PAD_LCD_D08__ETM_DA0			0x1081
#define MX23_PAD_LCD_D09__ETM_DA1			0x1091
#define MX23_PAD_LCD_D10__ETM_DA2			0x10a1
#define MX23_PAD_LCD_D11__ETM_DA3			0x10b1
#define MX23_PAD_LCD_D12__ETM_DA4			0x10c1
#define MX23_PAD_LCD_D13__ETM_DA5			0x10d1
#define MX23_PAD_LCD_D14__ETM_DA6			0x10e1
#define MX23_PAD_LCD_D15__ETM_DA7			0x10f1
#define MX23_PAD_LCD_RESET__ETM_TCTL			0x1121
#define MX23_PAD_LCD_RS__ETM_TCLK			0x1131
#define MX23_PAD_LCD_DOTCK__GPMI_RDY3			0x1161
#define MX23_PAD_LCD_ENABLE__I2C_SCL			0x1171
#define MX23_PAD_LCD_HSYNC__I2C_SDA			0x1181
#define MX23_PAD_LCD_VSYNC__LCD_BUSY			0x1191
#define MX23_PAD_PWM0__ROTARYA				0x11a1
#define MX23_PAD_PWM1__ROTARYB				0x11b1
#define MX23_PAD_PWM2__GPMI_RDY3			0x11c1
#define MX23_PAD_PWM3__ETM_TCTL				0x11d1
#define MX23_PAD_PWM4__ETM_TCLK				0x11e1
#define MX23_PAD_SSP1_DETECT__GPMI_CE3N			0x2011
#define MX23_PAD_SSP1_DATA1__I2C_SCL			0x2031
#define MX23_PAD_SSP1_DATA2__I2C_SDA			0x2041
#define MX23_PAD_ROTARYA__AUART2_RTS			0x2071
#define MX23_PAD_ROTARYB__AUART2_CTS			0x2081
#define MX23_PAD_GPMI_D00__SSP2_DATA0			0x0002
#define MX23_PAD_GPMI_D01__SSP2_DATA1			0x0012
#define MX23_PAD_GPMI_D02__SSP2_DATA2			0x0022
#define MX23_PAD_GPMI_D03__SSP2_DATA3			0x0032
#define MX23_PAD_GPMI_D04__SSP2_DATA4			0x0042
#define MX23_PAD_GPMI_D05__SSP2_DATA5			0x0052
#define MX23_PAD_GPMI_D06__SSP2_DATA6			0x0062
#define MX23_PAD_GPMI_D07__SSP2_DATA7			0x0072
#define MX23_PAD_GPMI_D08__SSP1_DATA4			0x0082
#define MX23_PAD_GPMI_D09__SSP1_DATA5			0x0092
#define MX23_PAD_GPMI_D10__SSP1_DATA6			0x00a2
#define MX23_PAD_GPMI_D11__SSP1_DATA7			0x00b2
#define MX23_PAD_GPMI_D15__GPMI_CE3N			0x00f2
#define MX23_PAD_GPMI_RDY0__SSP2_DETECT			0x0132
#define MX23_PAD_GPMI_RDY1__SSP2_CMD			0x0142
#define MX23_PAD_GPMI_WRN__SSP2_SCK			0x0182
#define MX23_PAD_AUART1_CTS__SSP1_DATA4			0x01a2
#define MX23_PAD_AUART1_RTS__SSP1_DATA5			0x01b2
#define MX23_PAD_AUART1_RX__SSP1_DATA6			0x01c2
#define MX23_PAD_AUART1_TX__SSP1_DATA7			0x01d2
#define MX23_PAD_I2C_SCL__AUART1_TX			0x01e2
#define MX23_PAD_I2C_SDA__AUART1_RX			0x01f2
#define MX23_PAD_LCD_D08__SAIF2_SDATA0			0x1082
#define MX23_PAD_LCD_D09__SAIF1_SDATA0			0x1092
#define MX23_PAD_LCD_D10__SAIF_MCLK_BITCLK		0x10a2
#define MX23_PAD_LCD_D11__SAIF_LRCLK			0x10b2
#define MX23_PAD_LCD_D12__SAIF2_SDATA1			0x10c2
#define MX23_PAD_LCD_D13__SAIF2_SDATA2			0x10d2
#define MX23_PAD_LCD_D14__SAIF1_SDATA2			0x10e2
#define MX23_PAD_LCD_D15__SAIF1_SDATA1			0x10f2
#define MX23_PAD_LCD_D16__SAIF_ALT_BITCLK		0x1102
#define MX23_PAD_LCD_RESET__GPMI_CE3N			0x1122
#define MX23_PAD_PWM0__DUART_RX				0x11a2
#define MX23_PAD_PWM1__DUART_TX				0x11b2
#define MX23_PAD_PWM3__AUART1_CTS			0x11d2
#define MX23_PAD_PWM4__AUART1_RTS			0x11e2
#define MX23_PAD_SSP1_CMD__JTAG_TDO			0x2002
#define MX23_PAD_SSP1_DETECT__USB_OTG_ID		0x2012
#define MX23_PAD_SSP1_DATA0__JTAG_TDI			0x2022
#define MX23_PAD_SSP1_DATA1__JTAG_TCLK			0x2032
#define MX23_PAD_SSP1_DATA2__JTAG_RTCK			0x2042
#define MX23_PAD_SSP1_DATA3__JTAG_TMS			0x2052
#define MX23_PAD_SSP1_SCK__JTAG_TRST			0x2062
#define MX23_PAD_ROTARYA__SPDIF				0x2072
#define MX23_PAD_ROTARYB__GPMI_CE3N			0x2082
#define MX23_PAD_GPMI_D00__GPIO_0_0			0x0003
#define MX23_PAD_GPMI_D01__GPIO_0_1			0x0013
#define MX23_PAD_GPMI_D02__GPIO_0_2			0x0023
#define MX23_PAD_GPMI_D03__GPIO_0_3			0x0033
#define MX23_PAD_GPMI_D04__GPIO_0_4			0x0043
#define MX23_PAD_GPMI_D05__GPIO_0_5			0x0053
#define MX23_PAD_GPMI_D06__GPIO_0_6			0x0063
#define MX23_PAD_GPMI_D07__GPIO_0_7			0x0073
#define MX23_PAD_GPMI_D08__GPIO_0_8			0x0083
#define MX23_PAD_GPMI_D09__GPIO_0_9			0x0093
#define MX23_PAD_GPMI_D10__GPIO_0_10			0x00a3
#define MX23_PAD_GPMI_D11__GPIO_0_11			0x00b3
#define MX23_PAD_GPMI_D12__GPIO_0_12			0x00c3
#define MX23_PAD_GPMI_D13__GPIO_0_13			0x00d3
#define MX23_PAD_GPMI_D14__GPIO_0_14			0x00e3
#define MX23_PAD_GPMI_D15__GPIO_0_15			0x00f3
#define MX23_PAD_GPMI_CLE__GPIO_0_16			0x0103
#define MX23_PAD_GPMI_ALE__GPIO_0_17			0x0113
#define MX23_PAD_GPMI_CE2N__GPIO_0_18			0x0123
#define MX23_PAD_GPMI_RDY0__GPIO_0_19			0x0133
#define MX23_PAD_GPMI_RDY1__GPIO_0_20			0x0143
#define MX23_PAD_GPMI_RDY2__GPIO_0_21			0x0153
#define MX23_PAD_GPMI_RDY3__GPIO_0_22			0x0163
#define MX23_PAD_GPMI_WPN__GPIO_0_23			0x0173
#define MX23_PAD_GPMI_WRN__GPIO_0_24			0x0183
#define MX23_PAD_GPMI_RDN__GPIO_0_25			0x0193
#define MX23_PAD_AUART1_CTS__GPIO_0_26			0x01a3
#define MX23_PAD_AUART1_RTS__GPIO_0_27			0x01b3
#define MX23_PAD_AUART1_RX__GPIO_0_28			0x01c3
#define MX23_PAD_AUART1_TX__GPIO_0_29			0x01d3
#define MX23_PAD_I2C_SCL__GPIO_0_30			0x01e3
#define MX23_PAD_I2C_SDA__GPIO_0_31			0x01f3
#define MX23_PAD_LCD_D00__GPIO_1_0			0x1003
#define MX23_PAD_LCD_D01__GPIO_1_1			0x1013
#define MX23_PAD_LCD_D02__GPIO_1_2			0x1023
#define MX23_PAD_LCD_D03__GPIO_1_3			0x1033
#define MX23_PAD_LCD_D04__GPIO_1_4			0x1043
#define MX23_PAD_LCD_D05__GPIO_1_5			0x1053
#define MX23_PAD_LCD_D06__GPIO_1_6			0x1063
#define MX23_PAD_LCD_D07__GPIO_1_7			0x1073
#define MX23_PAD_LCD_D08__GPIO_1_8			0x1083
#define MX23_PAD_LCD_D09__GPIO_1_9			0x1093
#define MX23_PAD_LCD_D10__GPIO_1_10			0x10a3
#define MX23_PAD_LCD_D11__GPIO_1_11			0x10b3
#define MX23_PAD_LCD_D12__GPIO_1_12			0x10c3
#define MX23_PAD_LCD_D13__GPIO_1_13			0x10d3
#define MX23_PAD_LCD_D14__GPIO_1_14			0x10e3
#define MX23_PAD_LCD_D15__GPIO_1_15			0x10f3
#define MX23_PAD_LCD_D16__GPIO_1_16			0x1103
#define MX23_PAD_LCD_D17__GPIO_1_17			0x1113
#define MX23_PAD_LCD_RESET__GPIO_1_18			0x1123
#define MX23_PAD_LCD_RS__GPIO_1_19			0x1133
#define MX23_PAD_LCD_WR__GPIO_1_20			0x1143
#define MX23_PAD_LCD_CS__GPIO_1_21			0x1153
#define MX23_PAD_LCD_DOTCK__GPIO_1_22			0x1163
#define MX23_PAD_LCD_ENABLE__GPIO_1_23			0x1173
#define MX23_PAD_LCD_HSYNC__GPIO_1_24			0x1183
#define MX23_PAD_LCD_VSYNC__GPIO_1_25			0x1193
#define MX23_PAD_PWM0__GPIO_1_26			0x11a3
#define MX23_PAD_PWM1__GPIO_1_27			0x11b3
#define MX23_PAD_PWM2__GPIO_1_28			0x11c3
#define MX23_PAD_PWM3__GPIO_1_29			0x11d3
#define MX23_PAD_PWM4__GPIO_1_30			0x11e3
#define MX23_PAD_SSP1_CMD__GPIO_2_0			0x2003
#define MX23_PAD_SSP1_DETECT__GPIO_2_1			0x2013
#define MX23_PAD_SSP1_DATA0__GPIO_2_2			0x2023
#define MX23_PAD_SSP1_DATA1__GPIO_2_3			0x2033
#define MX23_PAD_SSP1_DATA2__GPIO_2_4			0x2043
#define MX23_PAD_SSP1_DATA3__GPIO_2_5			0x2053
#define MX23_PAD_SSP1_SCK__GPIO_2_6			0x2063
#define MX23_PAD_ROTARYA__GPIO_2_7			0x2073
#define MX23_PAD_ROTARYB__GPIO_2_8			0x2083
#define MX23_PAD_EMI_A00__GPIO_2_9			0x2093
#define MX23_PAD_EMI_A01__GPIO_2_10			0x20a3
#define MX23_PAD_EMI_A02__GPIO_2_11			0x20b3
#define MX23_PAD_EMI_A03__GPIO_2_12			0x20c3
#define MX23_PAD_EMI_A04__GPIO_2_13			0x20d3
#define MX23_PAD_EMI_A05__GPIO_2_14			0x20e3
#define MX23_PAD_EMI_A06__GPIO_2_15			0x20f3
#define MX23_PAD_EMI_A07__GPIO_2_16			0x2103
#define MX23_PAD_EMI_A08__GPIO_2_17			0x2113
#define MX23_PAD_EMI_A09__GPIO_2_18			0x2123
#define MX23_PAD_EMI_A10__GPIO_2_19			0x2133
#define MX23_PAD_EMI_A11__GPIO_2_20			0x2143
#define MX23_PAD_EMI_A12__GPIO_2_21			0x2153
#define MX23_PAD_EMI_BA0__GPIO_2_22			0x2163
#define MX23_PAD_EMI_BA1__GPIO_2_23			0x2173
#define MX23_PAD_EMI_CASN__GPIO_2_24			0x2183
#define MX23_PAD_EMI_CE0N__GPIO_2_25			0x2193
#define MX23_PAD_EMI_CE1N__GPIO_2_26			0x21a3
#define MX23_PAD_GPMI_CE1N__GPIO_2_27			0x21b3
#define MX23_PAD_GPMI_CE0N__GPIO_2_28			0x21c3
#define MX23_PAD_EMI_CKE__GPIO_2_29			0x21d3
#define MX23_PAD_EMI_RASN__GPIO_2_30			0x21e3
#define MX23_PAD_EMI_WEN__GPIO_2_31			0x21f3

#endif /* __DT_BINDINGS_MX23_PINCTRL_H__ */
