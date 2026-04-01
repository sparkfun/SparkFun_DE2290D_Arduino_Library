/*
  This is a library written for the DE2290D 2D Barcode Scanner Engine

  SparkFun sells these at its website: www.sparkfun.com

  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/TBD

  Written by SparkFun Electronics, January, 2026

  The DE2290D is a camera-based barcode scanner
  https://github.com/sparkfun/SparkFun_DE2290D_Arduino_Library

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

#include "SparkFun_DE2290D_Arduino_Library.h"
#include "Arduino.h"

#include <SoftwareSerial.h>

//Constructor
DE2290D::DE2290D(void)
{
}  

//Initializes the device with basic settings
//Returns false if device is not detected
bool DE2290D::begin(HardwareSerial &serialPort)
{
  //Trick comes from: https://forum.arduino.cc/index.php?topic=503782.msg3435988#msg3435988
  hwStream = &serialPort;
  swStream = NULL;
  _serial = hwStream;

  if (isConnected() == false)
    return false; //No device detected

  //Clear any remaining incoming chars. The prevents a mis-read of the first barcode.
  while (_serial->available())
    _serial->read();

  return true; //We're all setup!
}

bool DE2290D::begin(SoftwareSerial &serialPort)
{
  //Serial.println("I am software");
  swStream = &serialPort;
  hwStream = NULL;
  _serial = swStream;

  if (isConnected() == false)
    return false; //No device detected

  //Clear any remaining incoming chars. The prevents a mis-read of the first barcode.
  while (_serial->available())
    _serial->read();

  return true; //We're all setup!
}

// Try to retrieve the firmware version number as a
// test to determine whether the module is connected.
// We're only testing to see if we got an ACK response,
// We don't ever check the actual firmware number.
bool DE2290D::isConnected()
{
  //Attempt initial comm at 9600
  if (hwStream)
    hwStream->begin(9600);
  else
    swStream->begin(9600);

  if (sendCommand(kCmdGetVersion, "", 800)) //Takes ~430ms to get firmware version response
    return true;

  //If we failed, try again at the factory default of 115200bps
  if (hwStream)
    hwStream->begin(115200);
  else
    swStream->begin(115200);

  delay(10);

  // Go to 9600bps
  if (!changeBaudRate(DE2290D_Baud_9600)) {
    return false;
  }
  //300ms is too quick for module to switch to new setting

  //Return to 9600bps
  if (hwStream)
    hwStream->begin(9600);
  else if (swStream)
    swStream->begin(9600);

  delay(10);

  if (sendCommand(kCmdGetVersion, "", 800)) //Takes ~430ms to get firmware version response
    return true;

  return false;
}

// Revert module to all factory default settings
// THIS WILL DISCONNECT THE MODULE FROM SERIAL
bool DE2290D::factoryDefault()
{
  return (sendCommand(kCmdRestoreDefaults));
}

bool DE2290D::available()
{
  return _serial->available();
}

int DE2290D::read()
{
  return _serial->read();
}

// Construct a command or parameter and send it to the
// module, then check the serial buffer for a response.
// Return TRUE if response contains ACK character, else
// return FALSE
bool DE2290D::sendCommand(const char *cmd, const char *arg, uint32_t maxWaitInms)
{
  char commandString[14] = {'\0'};
  char start[] = kDE2290DMetaCharPrefix;
  char end[] = kDE2290DMetaCharSuffix;

  strcat(commandString, start);
  strcat(commandString, cmd);
  strcat(commandString, arg);
  strcat(commandString, end);

  _serial->print(commandString);

  uint32_t timeout = millis() + maxWaitInms;

  while (millis() < timeout)
  {
    if (_serial->available())
    {
      while (_serial->available())
      {
        byte incoming = _serial->read();
        if (incoming == kDE2290DResponseAck)
          return true;
        else if (incoming == kDE2290DResponseNack)
          return false;
      }
    }
    delay(1);
  }

  return false;
}

// Check the receive buffer for serial data
// from the barcode scanner. If there's data,
// check the result buffer for a CR (marks a
// complete scan) If a CR is found, we overwrite the
// result buffer until either it's full or we
// reach a CR in the receive buffer.
bool DE2290D::readBarcode(char *resultBuffer, uint8_t size)
{
  if (!_serial->available())
    return false;

  bool crFound = false;
  for (uint8_t idx = 0; idx < size; idx++)
  {
    if (resultBuffer[idx] == '\r')
      crFound = true;
  }

  if (crFound)
    resultBuffer[0] = '\0';

  for (uint8_t idx = strlen(resultBuffer); idx < size; idx++)
  {
    if (_serial->available())
    {
      resultBuffer[idx] = _serial->read();
      if (resultBuffer[idx] == '\r')
      {
        resultBuffer[idx+1] = '\0';
        return true;
      }
    }
    else
      return false;
  }

  return false;
}

// Change the module's baud rate
bool DE2290D::changeBaudRate(DE2290D_Baud_t baud){
  switch(baud){
    case DE2290D_Baud_4800:
      return (sendCommand(kCmdSerialBaud4800));
    case DE2290D_Baud_9600:
      return (sendCommand(kCmdSerialBaud9600));
    case DE2290D_Baud_19200:
      return (sendCommand(kCmdSerialBaud19200));
    case DE2290D_Baud_38400:
      return (sendCommand(kCmdSerialBaud38400));
    case DE2290D_Baud_57600:
      return (sendCommand(kCmdSerialBaud57600));
    case DE2290D_Baud_115200:
      return (sendCommand(kCmdSerialBaud115200));
    default:
      return false;
  }
}

// Enable Decode Beep
bool DE2290D::enableDecodeBeep(bool enable)
{
  if (enable)
    return (sendCommand(kCmdEnableDecodeSound));
  
  return (sendCommand(kCmdDisableDecodeSound));
}

// Disable Decode Beep
bool DE2290D::disableDecodeBeep()
{
  return enableDecodeBeep(false);
}

// Enable and Disable Beep sound on setting changes
bool DE2290D::enableSettingBeep(bool enable)
{
  if (enable)
    return (sendCommand(kCmdEnableSettingSound));
  
  return (sendCommand(kCmdDisableSettingSound));
}

bool DE2290D::disableSettingBeep()
{
  return enableSettingBeep(false);
}

// Enable and Disable Beed sound on startup
bool DE2290D::enableBootBeep(bool enable)
{
  if (enable)
    return (sendCommand(kCmdEnableBootSound));
  
  return (sendCommand(kCmdDisableBootSound));
}
bool DE2290D::disableBootBeep()
{
  return enableBootBeep(false);
}

bool DE2290D::enableAllBeep(bool enable)
{
  if (enable){
    if (!sendCommand(kCmdEnableAllSound))
      return false;
    if (!enableBootBeep())
      return false;
    if (!enableSettingBeep())
      return false;
    if (!enableDecodeBeep())
      return false;
  }

  else{
    if (!sendCommand(kCmdDisableAllSound))
      return false;
    if (!disableBootBeep())
      return false;
    if (!disableSettingBeep())
      return false;
    if (!disableDecodeBeep())
      return false;
  }

  return true;
}

bool DE2290D::disableAllBeep()
{
  return enableAllBeep(false);
}

// Change Buzzer Volume
bool DE2290D::changeBuzzerVolume(DE2290D_Volume_t volume)
{
  if (volume > DE2290D_Volume_High)
    return false;

  if (volume == DE2290D_Volume_Low)
    return (sendCommand(kCmdVolumeLow));
  else if (volume == DE2290D_Volume_Medium)
    return (sendCommand(kCmdVolumeMedium));
  else if (volume == DE2290D_Volume_High)
    return (sendCommand(kCmdVolumeHigh));

  return false;
}

// Change Success Beep Frequency
bool DE2290D::changeSuccessBeepFrequency(DE2290D_Frequency_t frequency)
{
  if (frequency > DE2290D_Frequency_High)
    return false;

  if (frequency == DE2290D_Frequency_Low)
    return (sendCommand(kCmdDecodingSuccessFreqLow));
  else if (frequency == DE2290D_Frequency_Medium)
    return (sendCommand(kCmdDecodingSuccessFreqMedium));
  else if (frequency == DE2290D_Frequency_High)
    return (sendCommand(kCmdDecodingSuccessFreqHigh));

  return false;
}

// Change Error Beep Frequency
bool DE2290D::changeErrorBeepFrequency(DE2290D_Frequency_t frequency)
{
  if (frequency > DE2290D_Frequency_High)
    return false;

  if (frequency == DE2290D_Frequency_Low)
    return (sendCommand(kCmdErrorFreqLow));
  else if (frequency == DE2290D_Frequency_Medium)
    return (sendCommand(kCmdErrorFreqMedium));
  else if (frequency == DE2290D_Frequency_High)
    return (sendCommand(kCmdErrorFreqHigh));

  return false;
}

// Control the white illumination LED
bool DE2290D::lightOn(bool on)
{
  if (on)
    return (sendCommand(kCmdEnableFlashlight));
  
  return (sendCommand(kCmdDisableFlashlight));
}
bool DE2290D::lightOff()
{
  return lightOn(false);
}

// Control the red scan line
bool DE2290D::reticleOn(bool on)
{
  if (on)
    return (sendCommand(kCmdEnableReticle));
  
  return (sendCommand(kCmdDisableReticle));
}
bool DE2290D::reticleOff()
{
  return reticleOn(false);
}

// Enable and Disable Mirror Image reading
bool DE2290D::enableReverseScan(bool enable)
{
  if (enable){
    if (!sendCommand(kCmdEnable1DReversal))
      return false;
    if (!sendCommand(kCmdEnable2DReversal))
      return false;
  }

  else {
    if (!sendCommand(kCmdDisable1DReversal))
      return false;
    if (!sendCommand(kCmdDisable2DReversal))
      return false;
  }

  return true;
}

bool DE2290D::disableReverseScan()
{
  return enableReverseScan(false);
}

// Enable USB Communication and set the mode
// THIS WILL MAKE THE MODULE STOP RESPONDING ON TTL
bool DE2290D::SerialMode(DE2290D_SerialMode_t mode)
{
  if (mode > DE2290D_SerialMode_TTL)
    return false;
  
  if (mode == DE2290D_SerialMode_COM)
    return (sendCommand(kCmdSerialModeCOM));
  else if (mode == DE2290D_SerialMode_HID)
    return (sendCommand(kCmdSerialModeHID));
  else if (mode == DE2290D_SerialMode_TTL)
    return (sendCommand(kCmdSerialModeTTL));

  return false;
}

// Enable and disable motion sensitive read mode
// if enabling, set the sensitivity level
bool DE2290D::enableMotionSense(DE2290D_MotionSensitivity_t sensitivity)
{
  if (sensitivity > DE2290D_MotionSensitivity_High)
    return false;

  if (!sendCommand(kCmdScanningModeMotionSense))
    return false;

  if (sensitivity == DE2290D_MotionSensitivity_Low)
    return (sendCommand(kCmdMotionSenseSensitivityLow));
  else if (sensitivity == DE2290D_MotionSensitivity_Medium)
    return (sendCommand(kCmdMotionSenseSensitivityMedium));
  else if (sensitivity == DE2290D_MotionSensitivity_High)
    return (sendCommand(kCmdMotionSenseSensitivityHigh));

  return false;
}

bool DE2290D::enableManualTrigger()
{
  return (sendCommand(kCmdScanningModeTrigger));
}

bool DE2290D::enableContinuousRead()
{
  return (sendCommand(kCmdScanningModeContinuous));
}

bool DE2290D::changeScanningMode(DE2290D_ScanningMode_t mode)
{
  if (mode > DE2290D_ScanningMode_MotionSense)
    return false;

  if (mode == DE2290D_ScanningMode_Trigger)
    return (enableManualTrigger());
  else if (mode == DE2290D_ScanningMode_Continuous)
    return (enableContinuousRead());
  else if (mode == DE2290D_ScanningMode_MotionSense)
    return (enableMotionSense());

  return false;
}

// Enable or Disable decoding of all 1D symbologies
bool DE2290D::enableAll1D(bool enable)
{
  if (enable)
    return (sendCommand(kCmdEnableAll1D));
  
  return (sendCommand(kCmdDisableAll1D));
}
bool DE2290D::disableAll1D()
{
  return enableAll1D(false);
}

// Enable or Disable decoding of all 2D symbologies
bool DE2290D::enableAll2D(bool enable)
{
  if (enable)
    return (sendCommand(kCmdEnableAll2D));
  
  return (sendCommand(kCmdDisableAll2D));
}

bool DE2290D::disableAll2D()
{
  return enableAll2D(false);
}

// Start or stop reading when in Trigger Mode (DEFAULT)
// Module will automatically stop reading after a few seconds
bool DE2290D::startScan()
{
  return (sendCommand(kCmdStartScan));
}
bool DE2290D::stopScan()
{
  return (sendCommand(kCmdStopScan));
}