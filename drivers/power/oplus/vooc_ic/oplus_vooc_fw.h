
#ifndef __OPLUS_VOOC_FW_H__

#define __OPLUS_VOOC_FW_H__

#ifdef CONFIG_OPLUS_CHARGER_MTK
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/kobject.h>
#include <linux/platform_device.h>
#include <asm/atomic.h>

#include <linux/xlog.h>
//#include <upmu_common.h>
//#include <mt-plat/mtk_gpio.h>
//#include <linux/irqchip/mtk-eic.h>
#else
#include <linux/i2c.h>
#include <linux/debugfs.h>
#include <linux/gpio.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/power_supply.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/bitops.h>
#include <linux/mutex.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/of_regulator.h>
#include <linux/regulator/machine.h>

#endif

#include "../oplus_charger.h"
#include "../oplus_gauge.h"
#include "../oplus_vooc.h"

/*
enum {
	VOOC_CHARGER_MODE,
	HEADPHONE_MODE,
	NORMAL_CHARGER_MODE,
};
*/

#define OPLUS_VOOC_RESET_MCU_EN			83
#define OPLUS_VOOC_MCU_AP_CLK			13
#define OPLUS_VOOC_MCU_AP_DATA			14
#define OPLUS_VOOC_SW_CTRL_EVT			42
#define OPLUS_VOOC_SW_CTRL_DVT			42
#define CUST_EINT_MCU_AP_DATA 			14

#ifndef CONFIG_OPLUS_CHARGER_MTK
enum {
	HW_VERSION_UNKNOWN,
	HW_VERSION__EVT,
	HW_VERSION__DVT,
	HW_VERSION__MCU,
	HW_VERSION__15041,
};
#endif
enum {
	VOOC_FW_TYPE_INVALID,
	VOOC_FW_TYPE_STM8S_4350,
	VOOC_FW_TYPE_STM8S_4400_ORI,
	VOOC_FW_TYPE_STM8S_4400_AVOID_FAKE_ADAPTER,
	VOOC_FW_TYPE_STM8S_4400_AVOID_FG_I2C_ERR,
	VOOC_FW_TYPE_STM8S_4400_AVOID_OVER_TEMP,
	VOOC_FW_TYPE_STM8S_4400_AVOID_OVER_TEMP_NTC61C,
	VOOC_FW_TYPE_STM8S_4400_VOOC_FFC_09C,
	VOOC_FW_TYPE_STM8S_4400_VOOC_FFC_15C,//FV4430mV
	VOOC_FW_TYPE_STM8S_4400_VOOC_FFC_15C_FV4450,
	VOOC_FW_TYPE_STM8S_4450_FFC = 10,
	VOOC_FW_TYPE_STM8S_4450_FFC_5V6A,
	VOOC_FW_TYPE_STM8S_4400_VOOC_FFC_15C_TI411,
	VOOC_FW_TYPE_STM8S_4450_FFC_5C_VOOC,
	VOOC_FW_TYPE_STM8S_4400_FFC_5V5P9A,
	VOOC_FW_TYPE_STM8S_4450_FFC_5V6A_VOOC_4052MA_3BIT,
	VOOC_FW_TYPE_STM8S_4450_FFC_5V4A_VOOC_4052MA_3BIT,
	VOOC_FW_TYPE_STM8S_4400_VOOC_FFC_15C_18041,//FV4430mV
	VOOC_FW_TYPE_STM8S_4450_VOOC_FFC_5V6A_19365,
	VOOC_FW_TYPE_STM8S_4450_FFC_SHORT_RESET_WINDOW,
	VOOC_FW_TYPE_STM8S_4400_SVOOC_3500MA = 0x20,
	VOOC_FW_TYPE_STM8S_4400_SVOOC_1000MA = 0x21,
	VOOC_FW_TYPE_STM8S_4400_SVOOC_5000MA = 0x22,
	VOOC_FW_TYPE_STM8S_4400_SVOOC_6500MA = 0x23,
	VOOC_FW_TYPE_STM8S_4450_SVOOC_6500MA = 0x24,
	VOOC_FW_TYPE_STM8S_4450_SVOOC_6500MA_FV4490 = 0x25,
	VOOC_FW_TYPE_STM8S_4450_SVOOC_6500MA_disableI2C = 0x26,
	VOOC_FW_TYPE_STM8S_4400_SVOOC_6500MA_8250 = 0x27,
	VOOC_FW_TYPE_STM8S_4450_SVOOC_6500MA_8250 = 0x28,
	VOOC_FW_TYPE_STM8S_4400_SVOOC_6500MA_8250_LINK = 0x29,
	VOOC_FW_TYPE_STM8S_4400_SVOOC_6500MA_8250_LINK_LITE = 0x2A,
};

enum {
	VOOC_FW_TYPE_N76E_INVALID,
	VOOC_FW_TYPE_N76E_4400_AVOID_OVER_TEMP_NTC61C,
	VOOC_FW_TYPE_N76E_4400_VOOC_FFC_15C,//FV4430mV
	VOOC_FW_TYPE_N76E_4400_VOOC_FFC_15C_FV4450,
};

enum {
	VOOC_FW_TYPE_RK826_INVALID,
	VOOC_FW_TYPE_RK826_4400_VOOC_FFC_15C,//FV4430
	VOOC_FW_TYPE_RK826_4450_VOOC_FFC_5V6A_4BIT,
	VOOC_FW_TYPE_RK826_4450_SVOOC_FFC_5V6A_CHAKA,
	VOOC_FW_TYPE_RK826_4450_SVOOC_FFC_6300MA_HIMA,
	VOOC_FW_TYPE_RK826_4450_SVOOC_FFC_6300MA_HOREE,
	VOOC_FW_TYPE_RK826_4450_SVOOC_FFC_5V6A_DALI,
	VOOC_FW_TYPE_RK826_4450_SVOOC_FFC_6300MA_LEMON,
	VOOC_FW_TYPE_RK826_4450_VOOC_FFC_5V6A_7BIT_DARWIN,
	VOOC_FW_TYPE_RK826_4450_SVOOC_FFC_5V6A_WALLE,
	VOOC_FW_TYPE_RK826_4450_SVOOC_6300MA = 0x20,
};

enum {
	VOOC_FW_TYPE_OP10_INVALID,
	VOOC_FW_TYPE_OP10_4400_VOOC_FFC_15C,//FV4430
	VOOC_FW_TYPE_OP10_4450_VOOC_FFC_5V4A_4BIT,
	VOOC_FW_TYPE_OP10_4250_VOOC_FFC_10V6A_4BIT,
	VOOC_FW_TYPE_OP10_4450_VOOC_FFC_5V6A_4BIT,
};

enum {
	VOOC_FW_TYPE_RT5125_INVALID,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_15C,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_5V6A_7BIT,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_10V5A_7BIT,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_10V6P5A_7BIT,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_5V6A_4BIT,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_5V6A_7BIT_ZEUS,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_5V6A_7BIT_DARWIN,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_10V5A_7BIT_LUNA,
	VOOC_FW_TYPE_RT5125_4450_VOOC_FFC_10V6P5A_7BIT_JIN,
	VOOC_FW_TYPE_RT5125_4500_VOOC_FFC_10V6P5A_7BIT_20817,
	VOOC_FW_TYPE_RT5125_4500_VOOC_FFC_5V6A_7BIT_walle,
};

extern int g_hw_version;
extern void init_hw_version(void);
extern int get_vooc_mcu_type(struct oplus_vooc_chip *chip);
extern bool chargin_hw_init_done_vooc;



int oplus_vooc_gpio_dt_init(struct oplus_vooc_chip *chip);

void opchg_set_clock_active(struct oplus_vooc_chip *chip);
void opchg_set_clock_sleep(struct oplus_vooc_chip *chip);

void opchg_set_data_active(struct oplus_vooc_chip *chip);
void opchg_set_data_sleep(struct oplus_vooc_chip *chip);

bool is_allow_fast_chg_real(struct oplus_vooc_chip *chip);
int opchg_get_gpio_ap_data(struct oplus_vooc_chip *chip);
int opchg_read_ap_data(struct oplus_vooc_chip *chip);
void opchg_reply_mcu_data(struct oplus_vooc_chip *chip, int ret_info,
	int device_type);
void opchg_reply_mcu_data_4bits(struct oplus_vooc_chip *chip, int ret_info,
	int device_type);
void opchg_set_reset_active(struct oplus_vooc_chip *chip);
void opchg_set_reset_active_force(struct oplus_vooc_chip *chip);
void opchg_set_reset_sleep(struct oplus_vooc_chip *chip);
void opchg_set_vooc_chargerid_switch_val(struct oplus_vooc_chip *chip,
	int value);
int oplus_vooc_get_reset_gpio_val(struct oplus_vooc_chip *chip);
int oplus_vooc_get_switch_gpio_val(struct oplus_vooc_chip *chip);
int oplus_vooc_get_ap_clk_gpio_val(struct oplus_vooc_chip *chip);
int opchg_get_clk_gpio_num(struct oplus_vooc_chip *chip);
int opchg_get_data_gpio_num(struct oplus_vooc_chip *chip);

bool oplus_is_power_off_charging(struct oplus_vooc_chip *chip);
bool oplus_is_charger_reboot(struct oplus_vooc_chip *chip);

void switch_fast_chg(struct oplus_vooc_chip *chip);
void oplus_vooc_delay_reset_mcu_init(struct oplus_vooc_chip *chip);
extern void opchg_set_switch_mode(struct oplus_vooc_chip *chip, int mode);

extern void reset_fastchg_after_usbout(struct oplus_vooc_chip *chip);

void oplus_vooc_eint_register(struct oplus_vooc_chip *chip);
void oplus_vooc_eint_unregister(struct oplus_vooc_chip *chip);

void oplus_pps_eint_register(struct oplus_vooc_chip *chip);
void oplus_pps_eint_unregister(struct oplus_vooc_chip *chip);
int oplus_pps_get_gpio_value(struct oplus_vooc_chip *chip);

// Add for vooc batt 4.40
void oplus_vooc_fw_type_dt(struct oplus_vooc_chip *chip);

#ifdef VOOC_MCU_PIC16F
unsigned char Pic16F_firmware_data[] = {};

#endif


#ifdef VOOC_MCU_STM8S

/* CONFIG_VOOC_BATTERY_4350MV, fw_ver: 0x0 ~ 0x2f */

unsigned char Stm8s_firmware_data_4350mv[] = {0};

/* CONFIG_VOOC_BATTERY_4400MV, fw_ver: 0x30 - 0x7f */

unsigned char Stm8s_firmware_data_4400mv[] = {0};

unsigned char Stm8s_fw_data_4400_avoid_fake_adapter[] = {0};

unsigned char Stm8s_fw_data_4400_avoid_fg_i2c_err[] = {0};

unsigned char Stm8s_fw_data_4400_avoid_over_temp[] = {0};

unsigned char Stm8s_fw_data_4400_avoid_over_temp_ntc61c[] = {0};

unsigned char Stm8s_fw_data_4400_vooc_ffc_09c[] = {0};

unsigned char Stm8s_fw_data_4400_vooc_ffc_15c[] = {0};

unsigned char Stm8s_fw_data_4400_vooc_ffc_15c_fv4450[] = {0};

unsigned char Stm8s_fw_data_4450_ffc[] = {0};

unsigned char Stm8s_fw_data_4450_ffc_5c_vooc[] = {0};

#ifdef CONFIG_OPLUS_SM8150R_CHARGER
unsigned char Stm8s_fw_data_4450_ffc_5v6a[] = {0};
#else
unsigned char Stm8s_fw_data_4450_ffc_5v6a[] = {0};
#endif

unsigned char Stm8s_fw_data_4400_vooc_ffc_15c_ti411[] = {0};

unsigned char Stm8s_fw_data_4400_ffc_5v5p9a[] = {0};

unsigned char Stm8s_fw_data_4450_ffc_5v6a_3bit[] = {0};

unsigned char Stm8s_fw_data_4450_vooc_ffc_5v4a_3bit[] = {0};

//only for 18041
unsigned char Stm8s_fw_data_4400_vooc_ffc_15c_18041[] = {0};
//only for 19365
unsigned char Stm8s_fw_data_4450_VOOC_FFC_5V6A_19365[] = {0};
unsigned char Stm8s_fw_data_4450_ffc_ShortResetWindow[] = {0};


unsigned char Stm8s_fw_data_4400_svooc_3500MA[] = {0};

unsigned char Stm8s_fw_data_4400_svooc_1000MA[] = {0};

#ifdef CONFIG_OPLUS_SM8150R_CHARGER
unsigned char Stm8s_fw_data_4400_svooc_5000MA[] = {0};
#else
unsigned char Stm8s_fw_data_4400_svooc_5000MA[] = {0};
#endif

unsigned char Stm8s_fw_data_4400_svooc_6500MA[] = {0};

unsigned char Stm8s_fw_data_4450_svooc_6500MA[] = {0};

//only for 20075
unsigned char Stm8s_fw_data_4450_svooc_6500MA_fv4490[] = {0};

unsigned char Stm8s_fw_data_4450_svooc_6500MA_disableI2C[] = {0};


unsigned char Stm8s_fw_data_4400_svooc_6500MA_8250[] = {0};

unsigned char Stm8s_fw_data_4450_svooc_6500MA_8250[] = {0};

unsigned char Stm8s_fw_data_4400_svooc_6500MA_8250_link[] = {0};

unsigned char Stm8s_fw_data_4400_svooc_6500MA_8250_link_lite[] = {0};

#endif	/* VOOC_MCU_STM8S */


#ifdef VOOC_MCU_N76E
unsigned char n76e_fw_data_4400[] = {0};

unsigned char n76e_fw_data_4400_ntc61c[] = {0};

unsigned char n76e_fw_data_4400_vooc_ffc_15c[] = {0};
unsigned char n76e_fw_data_4400_vooc_ffc_15c_fv4450[] = {0};

#endif	/* VOOC_MCU_N76E */

#ifdef VOOC_ASIC_RK826

unsigned char rk826_fw_data_4400_vooc_ffc_15c[] = {0};

unsigned char rk826_fw_data_4450_vooc_ffc_5v6a_4bit[] = {0};

unsigned char rk826_fw_data_4450_svooc_ffc_5v6a_chaka[] = {0};

unsigned char rk826_fw_data_4450_svooc_ffc_6300mA_hima[] = {0};

unsigned char rk826_fw_data_4450_svooc_ffc_6300mA_horee[] = {0};

unsigned char rk826_fw_data_4450_svooc_ffc_5v6a_dali[] = {0};

unsigned char rk826_fw_data_4450_vooc_ffc_5v6a_7bit_darwin[] = {0};

unsigned char rk826_fw_data_4450_svooc_evt2_4500ma[] = {0};

unsigned char rk826_fw_data_4450_svooc_6300ma[] = {0};

unsigned char rk826_fw_data_4450_svooc_ffc_6300mA_lemon[] = {0};

unsigned char rk826_fw_data_4450_svooc_ffc_5v6a_walle[] = {0};
#endif /* VOOC_ASIC_RK826 */

#ifdef VOOC_ASIC_OP10 /* VOOC_ASIC_OP10 */

unsigned char op10_fw_data_4400_vooc_ffc_15c[] = {0};

unsigned char op10_fw_data_4450_vooc_ffc_5v4a_4bit[] = {0};


unsigned char op10_fw_data_4250_vooc_ffc_10v6a_4bit[] = {0};
unsigned char op10_fw_data_4450_vooc_ffc_5v6a_4bit[] = {0};
#endif /* VOOC_ASIC_OP10 */

#ifdef VOOC_ASIC_RT5125 /*VOOC_ASIC_RT5125*/

unsigned char rt5125_fw[]= {0};


unsigned char rt5125_fw_data_4450_vooc_ffc_5v6a_7bit[]= {0};



unsigned char rt5125_fw_data_4450_vooc_ffc_10v5a_7bit[]= {0};

unsigned char rt5125_fw_data_4450_vooc_ffc_10v6p5a_7bit[]= {0};

unsigned char rt5125_fw_data_4450_vooc_ffc_5v6a_4bit[]= {0};

unsigned char rt5125_fw_data_4450_vooc_ffc_5v6a_7bit_zeus[]= {0};

unsigned char rt5125_fw_data_4450_vooc_ffc_5v6a_7bit_darwin[]= {0};

unsigned char rt5125_fw_data_4450_vooc_ffc_5v6a_7bit_luna[]= {0};

unsigned char rt5125_fw_data_4450_vooc_ffc_10v6p5a_7bit_jin[]= {0};

unsigned char rt5125_fw_data_4500_svooc_ffc_6500ma_7bit_20817[]= {0};

unsigned char rt5125_fw_data_4500_svooc_ffc_6500ma_7bit_walle[]= {0};
#endif /* VOOC_ASIC_RT5125 */

#endif	/* __OPLUS_VOOC_FW_H__ */

