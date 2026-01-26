/*
  This is a library written for the DE2290H 2D Barcode Scanner Engine

  SparkFun sells these at its website: www.sparkfun.com
  
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/TBD

  Written by SparkFun Electronics, January, 2026
  
  The DE2290H is a camera-based barcode scanner
  https://github.com/sparkfun/SparkFun_DE2290H_Arduino_Library

  This is a rework of the original library written by Nick Poole @SparkFun in 2020 for the DE2120:
  https://github.com/sparkfun/SparkFun_DE2120_Arduino_Library

  Development environment specifics:
  
  Arduino IDE 1.8.7
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SPARKFUN_DE2290H_ARDUINO_LIBRARY_H
#define _SPARKFUN_DE2290H_ARDUINO_LIBRARY_H
#include "Arduino.h"

#include <SoftwareSerial.h>
#include "SparkFun_DE2290H_Constants.h"

class DE2290H
{
public:
  DE2290H();

  bool begin(HardwareSerial &serialPort);
  bool begin(SoftwareSerial &serialPort);

  bool isConnected();   //Returns true if device's ID is what it should be
  bool factoryDefault();
  bool sendCommand(const char *cmd, const char *arg = "", uint32_t maxWaitInms = 3000);
  bool readBarcode(char *resultBuffer, uint8_t size);
  bool available();
  int read();
  bool changeBaudRate(DE2290H_Baud_t baud);
  bool changeBuzzerVolume(DE2290H_Volume_t volume);
  bool changeSuccessBeepFrequency(DE2290H_Frequency_t frequency);
  bool changeErrorBeepFrequency(DE2290H_Frequency_t frequency);
  bool enableReverseScan(bool enable=true);
  bool disableReverseScan();
  bool enableAllBeep(bool enable=true);
  bool disableAllBeep();
  bool enableDecodeBeep(bool enable=true);
  bool disableDecodeBeep();
  bool enableSettingBeep(bool enable=true);
  bool disableSettingBeep();
  bool enableBootBeep(bool enable=true);
  bool disableBootBeep();
  bool lightOn(bool on=true);
  bool lightOff();
  bool reticleOn(bool on=true);
  bool reticleOff();
  bool SerialMode(DE2290H_SerialMode_t mode);
  bool changeScanningMode(DE2290H_ScanningMode_t mode);
  bool enableManualTrigger();
  bool enableContinuousRead();
  bool enableMotionSense(DE2290H_MotionSensitivity_t sensitivity = DE2290H_MotionSensitivity_Medium);
  bool enableAll1D(bool enable=true);
  bool disableAll1D();
  bool enableAll2D(bool enable=true);
  bool disableAll2D();
  bool startScan();
  bool stopScan();

private:
  //char _responseBuffer[]

  HardwareSerial *hwStream;
  SoftwareSerial *swStream;
  Stream *_serial;
};

#endif