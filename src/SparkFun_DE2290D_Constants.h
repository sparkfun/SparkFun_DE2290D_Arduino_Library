/*
  This is a library written for the DE2290D 2D Barcode Scanner Engine

  SparkFun sells these at its website: www.sparkfun.com
  
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/TBD

  Written by SparkFun Electronics, January, 2026
  
  The DE2290D is a camera-based barcode scanner
  https://github.com/sparkfun/SparkFun_DE2290D_Arduino_Library
  Development environment specifics:
  
  Arduino IDE 1.8.7
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// ---------------- Device Responses ---------------
#define kDE2290DResponseAck 0x06
#define kDE2290DResponseNack 0x15

// ----------------  Metacharacters ----------------
#define kDE2290DMetaCharPrefix "\x16"
#define kDE2290DMetaCharSuffix "\x2E"

// ----------------    Commands    -----------------
// General
#define kCmdStartScan "\x42\x65\x52\x65\x51\x62"
#define kCmdStopScan "\x42\x65\x52\x65\x52\x62"
#define kCmdRestoreDefaults "BeQeCe"
#define kCmdGetVersion "BeReCd"
#define kCmdEnableAll1D "GbYaZa"
#define kCmdDisableAll1D "GbYaJb"
#define kCmdEnableAll2D "GbYaBb"
#define kCmdDisableAll2D "GbYaLb"
#define kCmdEnableTransferCodeId "WaFbBb"
#define kCmdDisableTransferCodeId "WaFbRa"

// Serial Communication
#define kCmdSerialModeCOM "VbZcXag"
#define kCmdSerialModeHID "VbZcYag"
#define kCmdSerialModeTTL "VbZcNc"

#define kCmdSerialBaud4800 "VbCdRdc"
#define kCmdSerialBaud9600 "VbCdSdc"
#define kCmdSerialBaud19200 "VbCdUdc"
#define kCmdSerialBaud38400 "VbCdVdc"
#define kCmdSerialBaud57600 "VbCdWdc"
#define kCmdSerialBaud115200 "VbCdVac"

// Scanning Modes
#define kCmdScanningModeTrigger "VbBeJb"
#define kCmdScanningModeContinuous "VbBeZa"
#define kCmdScanningModeMotionSense "VbBePa"

#define kCmdScanningIntervalInfinite "UaZcCb"
#define kCmdScanningInterval3s "MdZcAbc"
#define kCmdScanningInterval5s "MdZcKbc"
#define kCmdScanningInterval10s "MdZcJcc"
#define kCmdScanningInterval15s "MdZcIdc"
#define kCmdScanningInterval20s "MdZcVaHa"

#define kCmdMotionSenseSensitivityLow "AcDbPb"
#define kCmdMotionSenseSensitivityMedium "AcDbFb"
#define kCmdMotionSenseSensitivityHigh "AcDbVa"

// Reversal
#define kCmdEnable1DReversal "PdZdQbc"
#define kCmdDisable1DReversal "PdAeQbc"
#define kCmdEnable2DReversal "PdBeQbc"
#define kCmdDisable2DReversal "PdCeQbc"

// Sound
#define kCmdEnableAllSound "WaZaCb"
#define kCmdDisableAllSound "WaZaSa"
#define kCmdEnableBootSound "RaOdNa"
#define kCmdDisableBootSound "RaOdXa"
#define kCmdEnableSettingSound "WaZaZa"
#define kCmdDisableSettingSound "WaZaPa"
#define kCmdEnableDecodeSound "RaDeXa"
#define kCmdDisableDecodeSound "RaDeNa"

#define kCmdVolumeLow "BbDeFb"
#define kCmdVolumeMedium "BbDeVa"
#define kCmdVolumeHigh "BbDeLa"

#define kCmdDecodingSuccessFreqLow "LbDeUb"
#define kCmdDecodingSuccessFreqMedium "LbDeEc"
#define kCmdDecodingSuccessFreqHigh "LbDeKb"

#define kCmdErrorFreqLow "GbZaNa"
#define kCmdErrorFreqMedium "GbZaXa"
#define kCmdErrorFreqHigh "GbZaHb"

// Lighting
#define kCmdEnableFlashlight "GbWaHb"
#define kCmdDisableFlashlight "GbWaNa"
#define kCmdEnableReticle "GbWaZa"
#define kCmdDisableReticle "GbWaPa"


// ----------------      Enums      ----------------
typedef enum
{
    DE2290D_ResponseCode_Ack = kDE2290DResponseAck,
    DE2290D_ResponseCode_Nack = kDE2290DResponseNack
} DE2290D_ResponseCode_t;

typedef enum
{
    DE2290D_Baud_4800 = 4800,
    DE2290D_Baud_9600 = 9600,
    DE2290D_Baud_19200 = 19200,
    DE2290D_Baud_38400 = 38400,
    DE2290D_Baud_57600 = 57600,
    DE2290D_Baud_115200 = 115200
} DE2290D_Baud_t;

typedef enum
{
    DE2290D_SerialMode_COM = 0,
    DE2290D_SerialMode_HID = 1,
    DE2290D_SerialMode_TTL = 2
} DE2290D_SerialMode_t;

typedef enum
{
    DE2290D_ScanningMode_Trigger = 0,
    DE2290D_ScanningMode_Continuous = 1,
    DE2290D_ScanningMode_MotionSense = 2
} DE2290D_ScanningMode_t;

typedef enum
{
    DE2290D_ScanningInterval_Infinite = 0,
    DE2290D_ScanningInterval_3s = 3,
    DE2290D_ScanningInterval_5s = 5,
    DE2290D_ScanningInterval_10s = 10,
    DE2290D_ScanningInterval_15s = 15,
    DE2290D_ScanningInterval_20s = 20
} DE2290D_ScanningInterval_t;

typedef enum
{
    DE2290D_MotionSensitivity_Low = 0,
    DE2290D_MotionSensitivity_Medium = 1,
    DE2290D_MotionSensitivity_High = 2
} DE2290D_MotionSensitivity_t;

typedef enum
{
    DE2290D_Volume_Low = 0,
    DE2290D_Volume_Medium = 1,
    DE2290D_Volume_High = 2
} DE2290D_Volume_t;

typedef enum
{
    DE2290D_Frequency_Low = 0,
    DE2290D_Frequency_Medium = 1,
    DE2290D_Frequency_High = 2
} DE2290D_Frequency_t;