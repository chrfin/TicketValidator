/******************************************************************************
;***                                                                        ***
;***    Product name : BHT-400B/QW-CE                                       ***
;***    File name    : BHTLIB.H                                             ***
;***                                                                        ***
;***            Copyright(C) DENSO WAVE INCORPORATED. All rights reserved.  ***
;*****************************************************************************/

#ifndef __BHTLIB_H__
#define __BHTLIB_H__

/*+-------------------------------------+*/
/*|     Include File                    |*/
/*+-------------------------------------+*/
#include <windows.h>

#ifdef __cplusplus
extern "C"{
#endif

/*+-------------------------------------+*/
/*|     Macro Definition                |*/
/*+-------------------------------------+*/

#define BHT400                                                    /* BHT ID code */

/* + ----   Control Code for System Property    ---- + */
/* System Information */
#define FUNC_BHT_SYS        ((DWORD)0x00000000)
#define BHT_SYS_OS_VERSION          (FUNC_BHT_SYS + (DWORD)0)       /* Version                */
#define BHT_SYS_RAMSIZE             (FUNC_BHT_SYS + (DWORD)2)       /* Total RAM Size         */
#define BHT_SYS_ROMSIZE             (FUNC_BHT_SYS + (DWORD)3)       /* Total ROM Size         */
#define BHT_SYS_MACHINE_NAME        (FUNC_BHT_SYS + (DWORD)4)       /* Machine Name           */
#define BHT_SYS_MACHINE_NUMBER      (FUNC_BHT_SYS + (DWORD)5)       /* Machine Number         */
#define BHT_SYS_SERIAL_NUMBER       (FUNC_BHT_SYS + (DWORD)6)       /* Machine Serial Number  */

/* Power Management */
#define FUNC_BHT_PM         ((DWORD)0x00000100)
#define BHT_PM_STBYTIME             (FUNC_BHT_PM + (DWORD)0)        /* Time of Transition To Standby  */
#define BHT_PM_BATTPOWEROFF         (FUNC_BHT_PM + (DWORD)1)        /* Transition Time (With Battery) */
#define BHT_PM_EXTPOWEROFF          (FUNC_BHT_PM + (DWORD)2)        /* Transition Time (On Charger)   */
#define BHT_PM_CPU_CLOCK            (FUNC_BHT_PM + (DWORD)3)        /* CPU Clock Speed                */
#define BHT_PM_SUSPEND_SLOT0        (FUNC_BHT_PM + (DWORD)4)        /* Allow to suspend for Slot0     */
#define BHT_PM_SUSPEND_SLOT1        (FUNC_BHT_PM + (DWORD)5)        /* Allow to suspend for Slot1     */

/* Display */
#define FUNC_BHT_DISP       ((DWORD)0x00000200)
//#define BHT_DISP_CONTRAST           (FUNC_BHT_DISP + (DWORD)1)      /* Value of Contrast            */

/* Beep & Vibrator */
#define FUNC_BHT_BEEP_VIB   ((DWORD)0x00000300)
#define BHT_BEEP_VIB_SELECT         (FUNC_BHT_BEEP_VIB + (DWORD)0)  /* Select Device                      */
#define BHT_BEEP_VIB_VOLUME         (FUNC_BHT_BEEP_VIB + (DWORD)1)  /* Volume                             */
#define BHT_BEEP_VIB_KEY            (FUNC_BHT_BEEP_VIB + (DWORD)2)  /* Volume of Key Click                */
#define BHT_BEEP_VIB_TAP            (FUNC_BHT_BEEP_VIB + (DWORD)3)  /* Volume of Stylus Tap               */
#define BHT_BEEP_VIB_TRGKEY         (FUNC_BHT_BEEP_VIB + (DWORD)4)  /* Click Sound ON/OFF for Trigger Key */
#define BHT_BEEP_VIB_HALFKEY        (FUNC_BHT_BEEP_VIB + (DWORD)5)  /* Volume of Half-Key Click           */
#define BHT_BEEP_VIB_LASERKEY       (FUNC_BHT_BEEP_VIB + (DWORD)6)  /* Click Sound ON/OFF for Laser Key   */

/* Backlight */
#define FUNC_BHT_BACKLIGHT  ((DWORD)0x00000400)
#define BHT_BACKLIGHT_BATT_TIME     (FUNC_BHT_BACKLIGHT + (DWORD)0) /* Backlight On-duration (With Battery) */
#define BHT_BACKLIGHT_KEY           (FUNC_BHT_BACKLIGHT + (DWORD)1) /* Control Key                          */
#define BHT_BACKLIGHT_AC_TIME       (FUNC_BHT_BACKLIGHT + (DWORD)3) /* Backlight On-duration (On Charger)   */
#define BHT_BACKLIGHT_BRIGHTNESS    (FUNC_BHT_BACKLIGHT + (DWORD)4) /* Value of Brightness Level            */
#define BHT_BACKLIGHT_POWERSAVE     (FUNC_BHT_BACKLIGHT + (DWORD)5) /* Value of Power Save Mode             */
#define BHT_BACKLIGHT_BRIGHTNESS2   (BHT_BACKLIGHT_POWERSAVE)       /* Value of Power Save Mode             */

/* Frontlight */
#define FUNC_BHT_FRONTLIGHT (FUNC_BHT_BACKLIGHT)
#define BHT_FRONTLIGHT_BATT_TIME    (BHT_BACKLIGHT_BATT_TIME)
#define BHT_FRONTLIGHT_KEY          (BHT_BACKLIGHT_KEY)
#define BHT_FRONTLIGHT_AC_TIME      (BHT_BACKLIGHT_AC_TIME)
#define BHT_FRONTLIGHT_BRIGHTNESS   (BHT_BACKLIGHT_BRIGHTNESS)

/* Barcode Reading */
#define FUNC_BHT_BAR        ((DWORD)0x00000500)
#define BHT_BAR_CRTIME              (FUNC_BHT_BAR + (DWORD)0)       /* Prevention Time of double-reading           */
#define BHT_BAR_INVERT              (FUNC_BHT_BAR + (DWORD)1)       /* Black/White reversal                        */
#define BHT_BAR_DCD_LEVEL           (FUNC_BHT_BAR + (DWORD)2)       /* Decoding level                              */
#define BHT_BAR_MINDGT_ITF          (FUNC_BHT_BAR + (DWORD)3)       /* Minimum digit number of ITF                 */
#define BHT_BAR_MINDGT_STF          (FUNC_BHT_BAR + (DWORD)4)       /* Minimum digit number of STF (BHT-200B Only) */
#define BHT_BAR_MINDGT_NW7          (FUNC_BHT_BAR + (DWORD)5)       /* Minimum digit number of NW7                 */
#define BHT_BAR_MINDGT_CODABAR      (FUNC_BHT_BAR + (DWORD)5)       /* Minimum digit number of CODABAR             */
#define BHT_BAR_MARKER              (FUNC_BHT_BAR + (DWORD)6)       /* Marker mode                                 */
#define BHT_BAR_REVERSE             (FUNC_BHT_BAR + (DWORD)7)       /* Reversal reading (BHT-200Q Only)            */
#define BHT_BAR_SCAN_MODE           (FUNC_BHT_BAR + (DWORD)9)       /* Scan mode (BHT-200Q Only)                   */
#define BHT_BAR_OPTION_DATA         (FUNC_BHT_BAR + (DWORD)10)      /* Option data (BHT-200Q Only)                 */

/* Keyboard */
#define FUNC_BHT_KEY        ((DWORD)0x00000600)
#define BHT_KEY_SHIFT_MODE          (FUNC_BHT_KEY + (DWORD)0)       /* Operation mode of Shift key                  */
#define BHT_KEY_M1_MODE             (FUNC_BHT_KEY + (DWORD)1)       /* Operation mode of Magic key1                 */
#define BHT_KEY_M2_MODE             (FUNC_BHT_KEY + (DWORD)2)       /* Operation mode of Magic key2                 */
#define BHT_KEY_M3_MODE             (FUNC_BHT_KEY + (DWORD)3)       /* Operation mode of Magic key3                 */
#define BHT_KEY_M4_MODE             (FUNC_BHT_KEY + (DWORD)4)       /* Operation mode of Magic key4                 */
#define BHT_KEY_M5_MODE             (FUNC_BHT_KEY + (DWORD)5)       /* Operation mode of Magic key5                 */
#define BHT_KEY_INPUT_METHOD        (FUNC_BHT_KEY + (DWORD)6)       /* Key-in method                                */
#define BHT_PWRDOWN_KEY_WAIT_TIME   (FUNC_BHT_KEY + (DWORD)7)       /* Power key pressed duration for Power Down    */
#define BHT_KEY_M3H_MODE            (FUNC_BHT_KEY + (DWORD)8)       /* Operation mode of Magic key3 for Half Click  */
#define BHT_KEY_M4H_MODE            (FUNC_BHT_KEY + (DWORD)9)       /* Operation mode of Magic key4 for Half Click  */
#define BHT_KEY_M5H_MODE            (FUNC_BHT_KEY + (DWORD)10)      /* Operation mode of Magic key5 for Half Click  */
#define BHT_KEY_SCAN_MODE           (FUNC_BHT_KEY + (DWORD)11)      /* Operation mode of SCAN Key                   */
#define BHT_KEY_INPUT_DISABLE       (FUNC_BHT_KEY + (DWORD)12)      /* Status of Alphabet Input method              */
#define BHT_DISABLE_KEYMODE_CHANGE_KEY  (BHT_KEY_INPUT_DISABLE)     /* Status of Alphabet Input method              */
#define BHT_KEY_FUNCTION            (FUNC_BHT_KEY + (DWORD)13)      /* Status of Function mode                      */
#define BHT_KEYBOARD_TYPE           (FUNC_BHT_KEY + (DWORD)14)      /* Keyboard Type (31 or 50 Key)                 */
#define BHT_HANDLE_STATUS           (FUNC_BHT_KEY + (DWORD)15)      /* Grip Handle                                  */
#define BHT_FNKEY_ASSIGNMENT        (FUNC_BHT_KEY + (DWORD)16)      /* Function key assignment                      */
#define BHT_ALPHABET2               (FUNC_BHT_KEY + (DWORD)17)      /* Alphabet Entry Mode #2                       */
#define BHT_KEYBD_EMULATION         (FUNC_BHT_KEY + (DWORD)18)      /* Keyboard Emulation for Terminal Services     */
#define BHT_EMULATED_KEYBD          (FUNC_BHT_KEY + (DWORD)19)      /* Emulated Keyboard Layouts                    */
#define BHT_KEY_DEFAULT_CAPS_MODE   (FUNC_BHT_KEY + (DWORD)20)      /* Default Caps Mode of Alphabet Entry          */

/* Display System Status */
#define FUNC_BHT_ICON       ((DWORD)0x00000700)
#define BHT_ICON_BATTERY            (FUNC_BHT_ICON + (DWORD)0)      /* Battery voltage status       */
#define BHT_ICON_SHIFTKEY           (FUNC_BHT_ICON + (DWORD)1)      /* Shift key status             */
#define BHT_ICON_STANDBY            (FUNC_BHT_ICON + (DWORD)2)      /* CPU standby status           */
#define BHT_ICON_STANBY             (BHT_ICON_STANDBY)              /* CPU standby status           */
#define BHT_ICON_RADIO_INTENSE      (FUNC_BHT_ICON + (DWORD)3)      /* Radio Field Intense status   */
#define BHT_ICON_WIRELESS           (BHT_ICON_RADIO_INTENSE)        /* Same As Upper                */
#define BHT_ICON_SIP                (FUNC_BHT_ICON + (DWORD)4)      /* Software Input Panel         */
#define BHT_ICON_IN_ALPHA           (FUNC_BHT_ICON + (DWORD)5)      /* Alphabet Entry               */
#define BHT_ICON_FUNC               (FUNC_BHT_ICON + (DWORD)6)      /* Function Mode                */
#define BHT_ICON_BLUETOOTH          (FUNC_BHT_ICON + (DWORD)7)      /* Bluetooth power status       */

/* Communication */
#define FUNC_BHT_COM        ((DWORD)0x00000800)
#define BHT_ACTSYNC_AUTOCNCT        (FUNC_BHT_COM + (DWORD)0)       /* ActiveSync automatic connection */

/* Touch Screen */
#define FUNC_BHT_TOUCH      ((DWORD)0x00000900)
#define BHT_TOUCH_DEVICE            (FUNC_BHT_TOUCH + (DWORD)1)     /* Touch Screen Disabling   */

/*** Bluetooth ***/
#define FUNC_BHT_BLUETOOTH  ((DWORD)0x00000B00)
#define BHT_BT_INITIAL_POWER_STATUS (FUNC_BHT_BLUETOOTH + (DWORD)0) /* Initial power status */

/*** Power Management ***/
#define CPU_CLK_NORMAL      ((DWORD)0)      /* CPU Clock Normal */
#define CPU_CLK_FAST        ((DWORD)4)      /* CPU Clock Fast   */
#define SUSPEND_ENABLE      ((DWORD)1)      /* Allow to suspend while no access */
#define SUSPEND_DISABLE     ((DWORD)0)      /* Disallow to suspend while no access */

/*** LED ***/
/* LED Status */
#define NO_LED_ON           ((DWORD)0x00)                           /* All LED OFF */
#define LED_OFF             (NO_LED_ON)
#define RED_LED_ON          ((DWORD)0x01)                           /* Red LED ON         */
#define GREEN_LED_ON        ((DWORD)0x02)                           /* Green LED ON       */
#define RED_GREEN_LED_ON    ((DWORD)(RED_LED_ON | GREEN_LED_ON))    /* Red & Green LED ON */
#define BOTH_LED_ON         (RED_GREEN_LED_ON)
#define YELLOW_LED_ON       ((DWORD)0x10)                           /* Yellow LED ON */
/* LED Device */
#define LED_BAR             ((DWORD)0)                              /* LED for Barcode Reading  */
#define LED_RF              ((DWORD)1)                              /* LED for RF Communication */
/* LED Number */
#define RED_LED             (RED_LED_ON)                            /* Red LED    */
#define GREEN_LED           (GREEN_LED_ON)                          /* Green LED  */
#define YELLOW_LED          (YELLOW_LED_ON)                         /* Yellow LED */
/* LED Usage */
#define USE_RF              ((DWORD)0x01)                           /* LED for RF Only     */
#define USE_APL             ((DWORD)0x02)                           /* LED for Application */

/*** Beep and Vibrator ***/
/* Select Device */
#define BEEP_SELECT         ((DWORD)0x01)                           /* Beep             */
#define VIB_SELECT          ((DWORD)0x02)                           /* Vibrator         */
#define BEEP_VIB_SELECT     ((DWORD)(BEEP_SELECT | VIB_SELECT))     /* Beep & Vibrator  */
/* Volume Level Max:5, Min:1. Off:0 */
#define VOLUME_LEVEL_OFF    ((DWORD)0)
#define VOLUME_LEVEL_1      ((DWORD)1)
#define VOLUME_LEVEL_2      ((DWORD)2)
#define VOLUME_LEVEL_3      ((DWORD)3)
#define VOLUME_LEVEL_4      ((DWORD)4)
#define VOLUME_LEVEL_5      ((DWORD)5)
/* Trigger Key Click Sound ON/OFF*/
#define CLICK_SOUND_OFF     ((DWORD)0)      /* OFF */
#define CLICK_SOUND_ON      ((DWORD)1)      /* ON  */

/*** Barcode ***/
/* Marker Mode */
#define MARKER_NORMAL           (0)     /* Normal           */
#define MARKER_AHEAD            (1)     /* Always lighting  */
#define MARKER_DISABLE          (2)     /* Disable lighting */
/* Scan Mode */
#define SCAN_MODE_NORMAL        (0)     /* Normal               */
#define SCAN_MODE_POINT         (1)     /* Point scan           */
#define SCAN_MODE_1D            (2)     /* Barcode reading mode */
/* Encoding method for read data */
#define READ_CODE_BINARY        (0)     /* Binary (w/o encoding) */
#define READ_CODE_UNICODE       (1)     /* Unicode               */
/* Maximum number of digits */
#define MAX_LEN_CODE_1D         (99)            /* for 1dim code */
#define MAX_LEN_CODE_2D         (8192 + 128)    /* for 2dim code */
#define MAX_LEN_CODE            (MAX_LEN_CODE_2D)
/* Maximum number of code in the 2d code */
#define MAX_NUM_CODE_1D_SCANNER (1)     /* for 1dim scanner */
#define MAX_NUM_CODE_2D_SCANNER (3)     /* for 2dim scanner */
#define MAX_NUM_CODE            (MAX_NUM_CODE_2D_SCANNER)

/*** Keyboard ***/
/* Shift Key Mode */
#define KEY_NON_LOCK            ((DWORD)0)          /* Non Lock */
#define KEY_ONE_TIME            ((DWORD)1)          /* One Time */
/* Magic Key Mode */
#define MAGIC_FUNC_NONE         ((DWORD)0)          /* Nothing                  */
#define MAGIC_FUNC_ENTER        ((DWORD)1)          /* ENTER key                */
#define MAGIC_FUNC_TRG          ((DWORD)2)          /* Scan Trigger             */
#define MAGIC_FUNC_SHIFT        ((DWORD)3)          /* SHIFT key                */
#define MAGIC_FUNC_BLT          ((DWORD)4)          /* Backlight Control        */
#define MAGIC_FUNC_TAB          ((DWORD)5)          /* TAB key                  */
#define MAGIC_FUNC_IM           ((DWORD)6)          /* Change Input Method      */
#define MAGIC_FUNC_LAZER        ((DWORD)7)          /* Laser                    */
#define MAGIC_FUNC_LASER        ((DWORD)7)          /* Laser                    */
#define MAGIC_FUNC_CTRL         ((DWORD)8)          /* CTRL key                 */
#define MAGIC_FUNC_ALT          ((DWORD)9)          /* ALT key                  */
#define MAGIC_FUNC_CLEAR        ((DWORD)10)         /* CLEAR key                */
#define MAGIC_FUNC_USERDEF      ((DWORD)0x80000000) /* User definition key code */
/* Key Input Method */
#define INPUT_METHOD_NUMERIC    ((DWORD)0)          /* Input Method Numerical   */
#define INPUT_METHOD_ALPHABET   ((DWORD)1)          /* Input Method Alphabet    */
#define INPUT_METHOD_ALPHABET1  ((DWORD)1)          /* Input Method Alphabet #1 */
#define INPUT_METHOD_ALPHABET2  ((DWORD)2)          /* Input Method Alphabet #2 */
/* Disable Change of Input Method */
#define ENABLE_KEY_TOCHANGE_ALPHABET    ((DWORD)0)
#define DISABLE_KEY_TOCHANGE_ALPHABET   ((DWORD)1)
/* Enable/Disable of Function Mode */
#define KEY_FUNCTION_OFF        ((DWORD)0)
#define KEY_FUNCTION_ON         ((DWORD)1)
/* Keyboard Type */
#define KEYBOARD_TYPE1          ((DWORD)0)          /* 31-key pad   */
#define KEYBOARD_TYPE2          ((DWORD)1)          /* 50-key pad   */
#define KEYBOARD_TYPE1P         ((DWORD)0x00000000) /* 31-key pad (Phone-type key layout)       */
#define KEYBOARD_TYPE2P         ((DWORD)0x00000001) /* 50-key pad (Phone-type key layout)       */
#define KEYBOARD_TYPE1C         ((DWORD)0x00010000) /* 31-key pad (Calculator-type key layout)  */
#define KEYBOARD_TYPE2C         ((DWORD)0x00010001) /* 50-key pad (Calculator-type key layout)  */
#define KEYBOARD_TYPE_MASK      ((DWORD)0x0000FFFF)
/* Grip Handle Existing */
#define HANDLE_STATUS_NO_HANDLE ((DWORD)0)
#define HANDLE_STATUS_LOADED    ((DWORD)1)
/* Function key assignment */
#define BHT_ORIGINAL_ASSIGNMENT ((DWORD)0)
#define FULL_FNKEY_ASSIGNMENT   ((DWORD)1)
/* Alphabet Entry Mode #2 */
#define DISABLE_ALPHABET2       ((DWORD)0)
#define ENABLE_ALPHABET2        ((DWORD)1)
/* Keyboard Emulation for Terminal Services */
#define DISABLE_KEYBD_EMULATION ((DWORD)0)
#define ENABLE_KEYBD_EMULATION  ((DWORD)1)
/* Emulated Keyboard Layouts */
#define EMULATED_KEYBD_US       (TEXT("kbdus.tbl"))
#define EMULATED_KEYBD_JPN      (TEXT("kbdjpn.tbl"))
/* Default Caps Mode of Alphabet Entry */
#define DEFAULT_CAPS_ON         ((DWORD)0)
#define DEFAULT_CAPS_OFF        ((DWORD)1)
/* BHT-400 Origunal Virtual Key Code Definition */
#define VK_M1               (0xC1)              /* M1 Key               */
#define VK_M2               (0xC2)              /* M2 Key               */
#define VK_M3               (0xC3)              /* M3 Key               */
#define VK_M4               (0xC4)              /* M4 Key               */
#define VK_M5               (0xC5)              /* M5 Key               */
#define VK_M3H              (0xC8)              /* M3 Half-press        */
#define VK_M4H              (0xC9)              /* M4 Half-press        */
#define VK_M5H              (0xCA)              /* M5 Half-press        */
#define VK_ALP              (0xD0)              /* ALP(alphabet key)    */
#define VK_SCAN             (0xD1)              /* SCAN key             */
#define VK_FUNC             (0xD2)              /* FUNC key             */
#define VK_SEND             (0xD3)              /* SEND key             */

/*** Backlight ***/
/* Status */
#define BLT_ENABLE_ON       (0)                 /* Lighting Enable & ON  */
#define BLT_ENABLE_OFF      (1)                 /* Lighting Enable & OFF */
#define BLT_DISABLE_OFF     (2)                 /* Lighting Disable      */
#define BHT_BL_ENABLE_ON    (BLT_ENABLE_ON)     /* Same as Upper */
#define BHT_BL_ENABLE_OFF   (BLT_ENABLE_OFF)    /* Same as Upper */
#define BHT_BL_DISABLE      (BLT_DISABLE_OFF)   /* Same as Upper */

/*** Communication ***/
/* ActiveSync automatic connection */
#define ACTSYNC_AUTOCNCT_DISABLE    ((DWORD)0x00000000)   /* Disable              */
#define ACTSYNC_AUTOCNCT_INFRARED   ((DWORD)0x00000001)   /* Infrared connections */
#define ACTSYNC_AUTOCNCT_USB        ((DWORD)0x00000002)   /* USB connections      */
#define ACTSYNC_AUTOCNCT_RS232C     ((DWORD)0x00000004)   /* RS232C connections   */

/*** Battery ***/
/* Battery level */
#define BHT_BATTERY_FLAG_HIGH       (0)     /* High level    */
#define BHT_BATTERY_FLAG_MID        (1)     /* Mid level     */
#define BHT_BATTERY_FLAG_LOW        (2)     /* Low level     */
#define BHT_BATTERY_FLAG_WARNING    (3)     /* Warning level */
#define BHT_BATTERY_FLAG_CRITICAL   (4)     /* Critical      */
#define BHT_BATTERY_FLAG_NO_BATTERY (0x80)  /* No Battery    */

/*** Wait Statement ***/
#define MAX_EVT_NUM             (8)
#define MAX_EVT                 (MAX_EVT_NUM)
/* Event Mask */
#define EVT_MASK_KEYDOWN        ((DWORD)0x00000001)     /* Key Down Event                */
#define EVT_MASK_TRGDOWN        ((DWORD)0x00000002)     /* Trigger Down Event            */
#define EVT_MASK_TCHUP          ((DWORD)0x00000004)     /* Touch Pen Up                  */
#define EVT_MASK_DECODE         ((DWORD)0x00000008)     /* Complete Decoding             */
#define EVT_MASK_RECEIVE_IRDA   ((DWORD)0x00000010)     /* Receive Data with IrDA I/F    */
#define EVT_MASK_RECEIVE_RS232C ((DWORD)0x00000040)     /* Receive Data with RS-232C I/F */
#define EVT_MASK_RECEIVE_USB    ((DWORD)0x00000080)     /* Receive Data with USB I/F     */
#define EVT_MASK_RECEIVE        (EVT_MASK_RECEIVE_IRDA) /* Receive Data with IrDA I/F    */
#define EVT_MASK_LASERKEYDOWN   ((DWORD)0x00000020)     /* Laser Key Down Event          */
#define EVT_MASK_TIMEOUT        ((DWORD)0x10000000)     /* Time Up                       */
#define EVT_MASK_EXIT_STANDBY_WAIT  ((DWORD)0x40000000) /* Exit Standby Wait Procedure   */
/* Event Name */
#define BHT_EVT_NAME_KEYDOWN        (TEXT("EVT_NAME_KEYDOWN"))          /* Key Down Event                */
#define BHT_EVT_NAME_TRGDOWN        (TEXT("EVT_NAME_TRGDOWN"))          /* Trigger Down Event            */
#define BHT_EVT_NAME_TCHUP          (TEXT("EVT_NAME_TCHUP"))            /* Touch Pen Up                  */
#define BHT_EVT_NAME_DECODE         (TEXT("EVT_BAR_END"))               /* Deocde Success                */
#define BHT_EVT_NAME_RECEIVE_IRDA   (TEXT("EVT_NAME_RECEIVE"))          /* Receive Data with IrDA I/F    */
#define BHT_EVT_NAME_RECEIVE_RS232C (TEXT("EVT_NAME_RECEIVE_RS232C"))   /* Receive Data with RS-232C I/F */
#define BHT_EVT_NAME_RECEIVE_USB    (TEXT("EVT_NAME_RECEIVE_USB"))      /* Receive Data with USB I/F     */
#define BHT_EVT_NAME_RECEIVE        (BHT_EVT_NAME_RECEIVE_IRDA)         /* Receive Data with IrDA I/F    */
#define BHT_EVT_NAME_LASERKEYDOWN   (TEXT("EVT_NAME_LASERKEYDOWN"))     /* Laser Key Down Event          */

/*** Shut Down Statement ***/
#define BHT_PWR_WARM                ((DWORD)0)
#define BHT_PWR_SUSPEND             ((DWORD)1)
#define BHT_PWR_COLD_REGINIT        ((DWORD)2)
#define BHT_PWR_COLD_REGREMAIN      ((DWORD)3)
#define BHT_PWR_SYSMODIFY           ((DWORD)4)
#define BHT_PWR_COLD                ((DWORD)5)
#define PWR_WARM                    (BHT_PWR_WARM)
#define PWR_SUSPEND                 (BHT_PWR_SUSPEND)
#define PWR_COLD_REGINIT            (BHT_PWR_COLD_REGINIT)
#define PWR_COLD_REGREMAIN          (BHT_PWR_COLD_REGREMAIN)
#define PWR_SYSMODIFY               (BHT_PWR_SYSMODIFY)
#define PWR_COLD                    (BHT_PWR_COLD)

/*** System Modify ***/
#define SYSMODIFY_POWEROFF      ((DWORD)0)
#define SYSMODIFY_REBOOT        ((DWORD)1)
#define SYSMDFY_POWEROFF        ((DWORD)0)
#define SYSMDFY_REBOOT          ((DWORD)1)

/*** Wireless ***/
#define P_PWRSAVE_CAM           (0)     /* CAM(Continuous access mode)         */
#define P_PWRSAVE_PSP           (1)     /* PSP(Power saving polling)           */
#define P_PWRSAVE_FASTPSP       (2)     /* Not support                         */
#define P_PWRSAVE_FULL          (P_PWRSAVE_CAM)
#define P_PWRSAVE_MOST          (P_PWRSAVE_PSP)
#define P_PWRSAVE_MORE          (P_PWRSAVE_PSP)
#define P_PWRSAVE_MID           (P_PWRSAVE_PSP)
#define P_PWRSAVE_LESS          (P_PWRSAVE_PSP)
#define P_PWRSAVE_LEAST         (P_PWRSAVE_PSP)

/* Transmit Rate */
#define P_RATE_AUTO             (0)     /*    Auto                  */
#define P_RATE_1MBPS            (1)     /*   1Mbps Only             */
#define P_RATE_2MBPS            (2)     /*   2Mbps Only             */
#define P_RATE_5_5MBPS          (3)     /* 5.5Mbps Only             */
#define P_RATE_11MBPS           (4)     /*  11Mbps Only             */
#define P_RATE_OVER11MBPS       (5)     /* Over 11Mbps              */
#define P_RATE_NOT_LINK         (0)     /* Not Link to Access Point */

/* Authentication */
#define P_AUTH_OPEN                 (0)     /* Open                     */
#define P_AUTH_SHAREDKEY40          (1)     /* Shared Key               */
#define P_AUTH_SHAREDKEY128         (2)     /* WEP 128bit               */
#define P_AUTH_KERBEROS             (3)     /* Kerberos                 */
#define P_AUTH_SHARED               (4)     /* Shared for Zero Config   */
#define P_AUTH_WPA                  (5)     /* WPA for Zero Config      */
#define P_AUTH_WPAPSK               (6)     /* Not support              */

/* Encryption */
#define P_ENCRYPT_DISABLE           (0)
#define P_ENCRYPT_WEP               (1)
#define P_ENCRYPT_TKIP              (2)
#define P_ENCRYPT_AES               (3)     /* Not support */

/* EAP type for 802.1x */
#define P_8021X_DISABLE             (0)     /* Disable           */
#define P_8021X_MD5CHALLENGE        (1)     /* Use MD5 Challenge */
#define P_8021X_PEAP                (2)     /* Use PEAP          */
#define P_8021X_TLS                 (3)     /* Use EAP-TLS       */

/* Wep Key Size*/
#define P_WEP_SIZE_40               (0)     /*  40bit */
#define P_WEP_SIZE_128              (1)     /* 128bit */

/* RF Controller */
#define P_CTRL_ZEROCONFIG           (0)
#define P_CTRL_NICCTRL              (1)

/* Parameter No for String */
#define P_STR_VERSION               (1)     /* Version for Driver           */
#define P_STR_MACADDRESS            (2)     /* MAC address                  */
#define P_STR_SSID1                 (3)     /* SSID 1                       */
#define P_STR_SSID2                 (4)     /* Not support                  */
#define P_STR_SSID3                 (5)     /* Not support                  */
#define P_STR_CLIENTNAME            (6)     /* Not support                  */
#define P_STR_DESTMACADDRESS1       (7)     /* MAC Address to Specified AP1 */
#define P_STR_DESTMACADDRESS2       (8)     /* Not support                  */
#define P_STR_DESTMACADDRESS3       (9)     /* Not support                  */
#define P_STR_DESTMACADDRESS4       (10)    /* Not support                  */
#define P_STR_KERBEROS_KDC          (11)    /* Not support                  */
#define P_STR_KERBEROS_REALM        (12)    /* Not support                  */
#define P_STR_HW_VERSION            (13)    /* Version for Hardware         */
#define P_STR_FW_VERSION            (14)    /* Version for Firmware         */
#define P_STR_PRESHAREDKEY          (15)    /* PreSharedKey for WPA-PSK     */
#define P_STR_WEPKEY1               (16)    /* WEP Key 1                    */
#define P_STR_WEPKEY2               (17)    /* Not support                  */
#define P_STR_WEPKEY3               (18)    /* Not support                  */
#define P_STR_WEPKEY4               (19)    /* Not support                  */

/* Parameter No for Numerical value */
#define P_INT_POWERSAVE             (1)     /* Power Save Mode                      */
#define P_INT_WEP                   (2)     /* Not support                          */
#define P_INT_AUTHENTICATE          (3)     /* Authentication                       */
#define P_INT_DATARATE              (4)     /* Not support                          */
#define P_INT_NETWORKTYPE           (5)     /* Not support                          */
#define P_INT_SCANMODE              (6)     /* Not support                          */
#define P_INT_PROBEDELAY            (7)     /* Not support                          */
#define P_INT_INTERNATIONAL         (8)     /* Not support                          */
#define P_INT_CHANNEL               (9)     /* Not support                          */
#define P_INT_CONTROLLER            (10)    /* Controller(ZeroConf, NicCtrl)        */
#define P_INT_ENCRYPTION            (11)    /* Encryption for Zero Config           */
#define P_INT_8021X                 (12)    /* EAP type for Zero Config             */
#define P_INT_PRIORITY              (13)    /* Priority of profile for Zero Config  */
#define P_INT_INDEXKEY              (14)    /* Index key for Zero Config            */
#define P_INT_TR                    (15)    /* Not support                          */
#define P_INT_TC                    (16)    /* Not support                          */
#define P_INT_TP                    (17)    /* Not support                          */
#define P_INT_TF                    (18)    /* Not support                          */

/* Command for BHT_RF_IoControl */
#define RF_UPDATE_PROFILE           (1)
#define RF_COMMIT_PROFILE           (2)
#define RF_SET_EDITMODE             (3)     /* Not support  */
#define RF_SET_PROFILE              (4)
#define RF_REMOVE_PROFILE           (5)
#define RF_GET_PROFILE_COUNT        (6)
#define RF_GET_PROFILE_KEY          (7)
#define ADD_CERT_ROOT               (8)     /* Not support  */
#define ADD_CERT_CLIENT             (9)     /* Not support  */
#define REMOVE_CERT                 (10)    /* Not support  */

/* Control mode for RF_SET_EDITMODE */
#define RF_EDIT_NICCTRL             (1)
#define RF_EDIT_ZEROCONFIG          (2)

/* Infrastructure mode for Profile Key */
#define INFRA_INFRASTRUCTURE        (0)
#define INFRA_ADHOC                 (1)

#define P_RATE_INFO                 (1)     /* Current Transmit Rate */
#define P_CHANNEL_INFO              (2)     /* Current Channel       */
#define P_APMAC_INFO                (3)     /* MAC Address to AP     */
#define P_RATE_INFO2                (4)     /* Current Transmit Rate(immediate value) */

/* RF Open API Argument */
#define COMM_NORMAL                 (0)     /* RF Open(equivalent to BHT_RF_Open/Close) */
#define COMM_CONTINUOUS             (1)     /* RF Open Continuously */

/* Communicative Quality for Site Survey */
#define LQ_UNSYNC                   (0)     /* Not associate with AP */
#define LQ_POOR                     (1)     /* Poor     (   - 20%)   */
#define LQ_FAIR                     (2)     /* Fair     (20%- 40%)   */
#define LQ_GOOD                     (3)     /* Good     (40%- 75%)   */
#define LQ_EXCELLENT                (4)     /* Excellent(75%-100%)   */

/* Size */
#define SSID_MAX                    (32)    /* Size of ESSID              */
#define MAC_SIZE                    (6)     /* Size of MAC Address        */
#define WEPINDEX_MAX                (4)     /* Number of WEP Key Index    */
#define WEP40_SIZE                  (5)     /* Size of 40bit WEP Key      */
#define WEP128_SIZE2                (13)    /* Size of 128bit WEP Key     */
#define KERBEROS_KDC_SIZE           (32)    /* Size of KDC for Kerberos   */
#define KERBEROS_REALM_SIZE         (32)    /* Size of REALM for Kerberos */

/* Length of String */
#define STRLEN_MAC                  (17)    /* Length of MAC Address (ex. 12:34:56:78:9A:BC) */
#define STRLEN_DRV_VER              (14)    /* Length of Driver Version (ex. 12.345.678.901) */
#define STRLEN_FW_VER               (14)    /* Length of Firmware Version (ex. F12.34-56)    */
#define STRLEN_HW_VER               (6)     /* Length of Harware Version (ex. V12.34)        */


/*** Communication ***/
#ifdef UNDER_CE
#define NUM_COM                 (3)     /* COM port(On WinCE) */
#else
#define NUM_COM                 (9)     /* COM port(Not on WinCE) */
#endif
#define NUM_BAUDRATE            (10)    /* Baud rate    */
#define NUM_DATABIT             (2)     /* Databit      */
#define NUM_PARITY              (3)     /* Parity       */
#define NUM_STOPBIT             (2)     /* Stopbit      */
#define NUM_FLOW                (3)     /* Flow control */

/* COM port */
#ifdef UNDER_CE
#define COM1                    (1)     /* Serial   */
#define COM3                    (3)     /* IrCOMM   */
#define COM4                    (4)     /* Raw-IrDA */
#else
#define COM1                    (1)
#define COM2                    (2)
#define COM3                    (3)
#define COM4                    (4)
#define COM5                    (5)
#define COM6                    (6)
#define COM7                    (7)
#define COM8                    (8)
#define COM9                    (9)
#endif

/* BaudRate(These are defined in "winbase.h".) */
/*#define CBR_110                 (100)    */
/*#define CBR_300                 (300)    */
/*#define CBR_1200                (1200)   */
/*#define CBR_2400                (2400)   */
/*#define CBR_4800                (4800)   */
/*#define CBR_9600                (9600)   */
/*#define CBR_19200               (19200)  */
/*#define CBR_38400               (38400)  */
/*#define CBR_57600               (57600)  */
/*#define CBR_115200              (115200) */

/* Databit */
#define DATABIT7                (7)
#define DATABIT8                (8)

/* Parity(These are defined in "winbase.h".) */
/*#define NOPARITY                (0) */
/*#define ODDPARITY               (1) */
/*#define EVENPARITY              (2) */

/* StopBit(These are defined in "winbase.h".) */
/*#define ONESTOPBIT              (0) */
/*#define TWOSTOPBITS             (2) */

/* Flow control */
#define FLOW_XONXOFF            (0)
#define FLOW_HARDWARE           (1)
#define FLOW_NONE               (2)

#define PURGE_ALL   (PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR)

#define FT_FILENAME_LENGTH      (90)

#define TRANSFER_READY          (0)
#define TRANSFER_SEND           (1)
#define TRANSFER_RECEIVE        (2)

/*** Touch Screen ***/
#define TOUCH_DISABLE           ((DWORD)0)
#define TOUCH_ENABLE            ((DWORD)1)

/*** Bluetooth ***/
/* Power Status */
#define BHT_BT_POWER_OFF        ((DWORD)0)
#define BHT_BT_POWER_ON         ((DWORD)1)

/*** Window Messages ***/
#define MSG_BHT_WARNING     (TEXT("BHTWarning"))

/*+-------------------------------------+*/
/*|     TYPE DECLARE                    |*/
/*+-------------------------------------+*/
/* Serial Config */
struct ST_SERIAL {
    long        lBaudRate;      /* BaudRate     */
    short       sDatabit;       /* Databit      */
    short       sParity;        /* Parity       */
    short       sStopBit;       /* StopBit      */
    short       sFlow;          /* Flow control */
#ifdef __cplusplus
    BOOL operator != (ST_SERIAL& stSerial){
        return  (lBaudRate != stSerial.lBaudRate) ||
                (sDatabit  != stSerial.sDatabit ) ||
                (sParity   != stSerial.sParity  ) ||
                (sStopBit  != stSerial.sStopBit ) ||
                (sFlow     != stSerial.sFlow    );
    }
#endif  /* __cplusplus */
};

/* Information on the Reading Code */
struct ST_READ_CODE_INFO {
    DWORD dwType;               /* Code Mark        */
    DWORD dwLen;                /* Number of Digits */
};

/* Enumeration of code type for decode options */
typedef enum _EN_DCD_OPTIONS_CODE_TYPE {
    enOptionsUPCE,              /* UPC-E */
    enOptionsUPCA,              /* UPC-A */
    enOptionsEAN8,              /* EAN-8 */
} EN_DCD_OPTIONS_CODE_TYPE;

/* Decode options for UPC-E code */
typedef struct _ST_DCD_UPCE_OPTIONS {
    BOOL    bConvertToUPCA;     /* Convert the read data into UPC-A code            */
    BOOL    bReportNumsys;      /* Append character "0" to head of the read data    */
    BOOL    bReportChk;         /* Append the check digit to tail of the read data  */
} ST_DCD_UPCE_OPTIONS,  *PST_DCD_UPCE_OPTIONS;

/* Decode options for UPC-A code */
typedef struct _ST_DCD_UPCA_OPTIONS {
    BOOL    bReportNumsys;      /* Append character "0" to head of the read data    */
    BOOL    bReportChk;         /* Append the check digit to tail of the read data  */
} ST_DCD_UPCA_OPTIONS,  *PST_DCD_UPCA_OPTIONS;

/* Decode options for EAN-8 code */
typedef struct _ST_DCD_EAN8_OPTIONS {
    BOOL    bConvertToEAN13;    /* Convert the read data into EAN-8 code            */
} ST_DCD_EAN8_OPTIONS,  *PST_DCD_EAN8_OPTIONS;

/* Profile key */
typedef struct _ST_RF_PROFILE_KEY {
    TCHAR   szESSID[SSID_MAX+1];    // ESSID
    UCHAR   ucReserved[2];          
    DWORD   dwInfraMode;            // Infra-mode
} ST_RF_PROFILE_KEY, *PST_RF_PROFILE_KEY;

/*+-------------------------------------+*/
/*|     FUNCTION DECLARE                |*/
/*+-------------------------------------+*/
/*** System Property ***/
/* Set System Property */
DWORD BHT_SetSysSettingWCS(DWORD dwCtrlCode, TCHAR* pwchSysParam, DWORD dwLen);
DWORD BHT_SetSysSettingDW(DWORD dwCtrlCode, DWORD dwSysParam);
/* Get System Property */
DWORD BHT_GetSysSettingWCS(DWORD dwCtrlCode, TCHAR* pwchSysParam, DWORD dwLen, DWORD* pdwLenReturned);
DWORD BHT_GetSysSettingDW(DWORD dwCtrlCode, DWORD* pdwSysParam);

/*** BATTERY ***/
/* Get Information of Battery */
DWORD BHT_GetPowerStatus(WORD *CUOnLine, WORD *BatteryFlag, WORD *BatteryVoltage, WORD *BatteryChemistry);
/* Get Information of Battery in Grip */
DWORD BHT_GetPowerStatus2nd(WORD *CUOnLine, WORD *BatteryFlag, WORD *BatteryVoltage, WORD *BatteryChemistry);

/*** Backlight ***/
/* Set Backlight Status */
DWORD BHT_SetBltStatus(DWORD dwStatus);
/* Get Backlight Status */
DWORD BHT_GetBltStatus(DWORD* pdwStatus);

/*** LED ***/
/* Get LED Status */
DWORD BHT_GetNLedStatus(DWORD *pdwStatus);
/* Set LED Status */
DWORD BHT_SetNLedStatus(DWORD dwStatus);
/* Get LED Status Ex */
DWORD BHT_GetNLedStatusEx( DWORD dwLedDevice, DWORD *pdwStatus );
/* Set LED ON */
DWORD BHT_SetNLedOn( DWORD dwLedDevice, DWORD dwLedNum );
/* Set LED OFF */
DWORD BHT_SetNLedOff( DWORD dwLedDevice, DWORD dwLedNum );
/* Get LED Control Status */
DWORD BHT_GetNLedControl( DWORD dwLedDevice, DWORD *pdwUsage );
/* Set LED Control Status */
DWORD BHT_SetNLedControl( DWORD dwLedDevice, DWORD dwUsage );

/*** BEEP & VIBRATOR ***/
/* Start Beep & Vibrator Sound */
DWORD BHT_StartBeep(DWORD dwOnTime, DWORD dwOffTime, WORD wRepCnt, WORD wFreq);
DWORD BHT_StartBeeperOnly(DWORD dwOnTime, DWORD dwOffTime, WORD wRepCnt, WORD wFreq);
DWORD BHT_StartVibrationOnly(DWORD dwOnTime, DWORD dwOffTime, WORD wRepCnt);

/*** Other API ***/
/* Wait Statement */
DWORD BHT_WaitEvent(DWORD dwEvtNum, DWORD dwEvtMask, DWORD dwTimeOut, DWORD *pdwSignalEvent);
DWORD BHT_WaitStandbyEvent(DWORD dwEvtNum, DWORD dwEvtMask, DWORD* pdwSignalEvent);
/* Shutdown System */
DWORD BHT_ShutdownSystem(DWORD dwMode);
/* System Modify */
DWORD BHT_SystemModify( TCHAR *pwszFileName, DWORD dwMode );
/* Registry Store */
DWORD BHT_RegStore(void);

/*** Barcode Reading ***/
/* Enable Barcode Reading */
DWORD BHT_EnableBar(TCHAR* pwchRdMode, TCHAR* pwchRdCode);
/* Disable Barcode Reading */
DWORD BHT_DisableBar(void);
/* Read Bardata */
DWORD BHT_ReadBar(TCHAR* pwchBuffer, DWORD dwBarLen, DWORD* pdwActualBarLen);
/* Read Bardata Extended */
DWORD BHT_ReadBarEx(DWORD dwDataType, LPVOID lpBuffer, DWORD dwBarLen, DWORD* pdwActualBarLen);
/* Get Barcode Type */
DWORD BHT_GetBarType(DWORD* pdwCdMark, DWORD* pdwCdLen);
/* Get Barcode Information */
DWORD BHT_GetBarInfo(struct ST_READ_CODE_INFO* pstInfo, DWORD* pdwCodeNum);
/* Get Barcode Length */
DWORD BHT_GetBarNum(DWORD* pdwLen);
/* Get Check Digit */
DWORD BHT_GetBarChkdgt(TCHAR pwchBarbuf[], DWORD dwCodeMark, DWORD* pdwChkdgt);
/* Set Options of Decode */
DWORD BHT_BAR_SetDecodeOptions(EN_DCD_OPTIONS_CODE_TYPE enCodeType, LPVOID pOptions, DWORD dwLen);
/* Get Options of Decode */
DWORD BHT_BAR_GetDecodeOptions(EN_DCD_OPTIONS_CODE_TYPE enCodeType, LPVOID pOptions, DWORD* pdwLen);

/*** Wireless Device ***/
DWORD BHT_RF_Open(void);
DWORD BHT_RF_Close(void);
DWORD BHT_RF_OpenEx(DWORD dwOpt);
DWORD BHT_RF_CloseEx(DWORD dwOpt);
DWORD BHT_RF_Synchronize(long lTimeout, long* plSync);
DWORD BHT_RF_GetParamInt(DWORD dwParam, DWORD* pdwData, DWORD* pdwLen);
DWORD BHT_RF_SetParamInt(DWORD dwParam, const DWORD* pdwData, DWORD dwLen);
DWORD BHT_RF_GetParamStr(DWORD dwParam, TCHAR* ptcData, DWORD* pdwLen);
DWORD BHT_RF_SetParamStr(DWORD dwParam, const TCHAR* ptcData, DWORD dwLen);
DWORD BHT_RF_SetWepKey(DWORD dwWepIndex, TCHAR* ptcWepKey);
DWORD BHT_RF_GetTransmitWepKey(DWORD* pdwTransmitKey);
DWORD BHT_RF_SetTransmitWepKey(DWORD dwTransmitKey);
DWORD BHT_RF_GetInfoInt(DWORD dwType, DWORD* pdwInfo);
DWORD BHT_RF_GetInfoStr(DWORD dwType, TCHAR* ptcInfo);
DWORD BHT_RF_GetSiteSurvey(DWORD* pdwStrength, DWORD* pdwBeacon, DWORD* pdwLink);
DWORD BHT_RF_IoControl(DWORD dwCtrlCode, LPVOID lpInBuf, DWORD nInBufSize,
                       LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned);

/*** Bluetooth ***/
DWORD BHT_BT_PowerOn( void );
DWORD BHT_BT_PowerOff( void );
DWORD BHT_BT_GetPowerStatus( DWORD *pdwStatus );


#ifdef __cplusplus
}
#endif

#endif  // __BHTLIB_H__
