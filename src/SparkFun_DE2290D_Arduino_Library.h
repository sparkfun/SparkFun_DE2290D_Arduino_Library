/*
    This is a library written for the DE2290D 2D Barcode Scanner Engine

    SparkFun sells these at its website: www.sparkfun.com

    Do you like this library? Help support SparkFun. Buy a board!
    https://www.sparkfun.com/products/30942

    Written by SparkFun Electronics, January, 2026

    The DE2290D is a camera-based barcode scanner
    https://github.com/sparkfun/SparkFun_DE2290D_Arduino_Library

    This is a rework of the original library written by Nick Poole @SparkFun in 2020 for the DE2120:
    https://github.com/sparkfun/SparkFun_DE2120_Arduino_Library

    Licenced under The MIT License (MIT)

    Copyright (c) 2026 SparkFun Electronics
*/

#ifndef _SPARKFUN_DE2290D_ARDUINO_LIBRARY_H
#define _SPARKFUN_DE2290D_ARDUINO_LIBRARY_H
#include "Arduino.h"

#include "SparkFun_DE2290D_Constants.h"

#ifndef ESP32
#include <SoftwareSerial.h>
#endif

class DE2290D
{
  public:
    /**
     * @brief Constructor for DE2290D class.
     */
    DE2290D();

    /**
     * @brief Initializes the device with a HardwareSerial port.
     * @param serialPort Reference to the HardwareSerial object.
     * @return True if initialization was successful, false otherwise.
     */
    bool begin(HardwareSerial &serialPort);

/**
 * @brief Initializes the device with a SoftwareSerial port.
 * @param serialPort Reference to the SoftwareSerial object.
 * @return True if initialization was successful, false otherwise.
 */
#ifndef ESP32
    bool begin(SoftwareSerial &serialPort);
#endif

    /**
     * @brief Checks if the device is connected and has the correct ID.
     * @return True if connected, false otherwise.
     */
    bool isConnected();

    /**
     * @brief Resets the device to factory default settings.
     * @return True if successful, false otherwise.
     */
    bool factoryDefault();

    /**
     * @brief Sends a command to the device.
     * @param cmd Command string.
     * @param arg Optional argument string (default is empty).
     * @param maxWaitInms Maximum wait time in milliseconds (default is 3000).
     * @return True if command was sent successfully, false otherwise.
     */
    bool sendCommand(const char *cmd, const char *arg = "", uint32_t maxWaitInms = 3000);

    /**
     * @brief Reads a barcode from the device.
     * @param resultBuffer Buffer to store the barcode result.
     * @param size Size of the result buffer.
     * @return True if barcode was read successfully, false otherwise.
     */
    bool readBarcode(char *resultBuffer, uint8_t size);

    /**
     * @brief Checks if data is available to read from the device.
     * @return True if data is available, false otherwise.
     */
    bool available();

    /**
     * @brief Reads a byte of data from the device.
     * @return The byte read, or -1 if no data is available.
     */
    int read();

    /**
     * @brief Changes the baud rate of the device.
     * @param baud Baud rate enum value.
     * @return True if baud rate was changed successfully, false otherwise.
     */
    bool changeBaudRate(DE2290D_Baud_t baud);

    /**
     * @brief Changes the buzzer volume of the device.
     * @param volume Volume enum value.
     * @return True if volume was changed successfully, false otherwise.
     */
    bool changeBuzzerVolume(DE2290D_Volume_t volume);

    /**
     * @brief Changes the frequency of the success beep.
     * @param frequency Frequency enum value.
     * @return True if frequency was changed successfully, false otherwise.
     */
    bool changeSuccessBeepFrequency(DE2290D_Frequency_t frequency);

    /**
     * @brief Changes the frequency of the error beep.
     * @param frequency Frequency enum value.
     * @return True if frequency was changed successfully, false otherwise.
     */
    bool changeErrorBeepFrequency(DE2290D_Frequency_t frequency);

    /**
     * @brief Enables or disables reverse scan mode.
     * @param enable Set to true to enable, false to disable (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool enableReverseScan(bool enable = true);

    /**
     * @brief Disables reverse scan mode.
     * @return True if operation was successful, false otherwise.
     */
    bool disableReverseScan();

    /**
     * @brief Enables or disables all beep sounds.
     * @param enable Set to true to enable, false to disable (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool enableAllBeep(bool enable = true);

    /**
     * @brief Disables all beep sounds.
     * @return True if operation was successful, false otherwise.
     */
    bool disableAllBeep();

    /**
     * @brief Enables or disables decode beep sound.
     * @param enable Set to true to enable, false to disable (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool enableDecodeBeep(bool enable = true);

    /**
     * @brief Disables decode beep sound.
     * @return True if operation was successful, false otherwise.
     */
    bool disableDecodeBeep();

    /**
     * @brief Enables or disables setting beep sound.
     * @param enable Set to true to enable, false to disable (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool enableSettingBeep(bool enable = true);

    /**
     * @brief Disables setting beep sound.
     * @return True if operation was successful, false otherwise.
     */
    bool disableSettingBeep();

    /**
     * @brief Enables or disables boot beep sound.
     * @param enable Set to true to enable, false to disable (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool enableBootBeep(bool enable = true);

    /**
     * @brief Disables boot beep sound.
     * @return True if operation was successful, false otherwise.
     */
    bool disableBootBeep();

    /**
     * @brief Turns the light on or off.
     * @param on Set to true to turn on, false to turn off (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool lightOn(bool on = true);

    /**
     * @brief Turns the light off.
     * @return True if operation was successful, false otherwise.
     */
    bool lightOff();

    /**
     * @brief Turns the reticle on or off.
     * @param on Set to true to turn on, false to turn off (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool reticleOn(bool on = true);

    /**
     * @brief Turns the reticle off.
     * @return True if operation was successful, false otherwise.
     */
    bool reticleOff();

    /**
     * @brief Sets the serial mode of the device.
     * @param mode Serial mode enum value.
     * @return True if mode was set successfully, false otherwise.
     */
    bool SerialMode(DE2290D_SerialMode_t mode);

    /**
     * @brief Changes the scanning mode of the device.
     * @param mode Scanning mode enum value.
     * @return True if mode was changed successfully, false otherwise.
     */
    bool changeScanningMode(DE2290D_ScanningMode_t mode);

    /**
     * @brief Enables manual trigger mode.
     * @return True if operation was successful, false otherwise.
     */
    bool enableManualTrigger();

    /**
     * @brief Enables continuous read mode.
     * @return True if operation was successful, false otherwise.
     */
    bool enableContinuousRead();

    /**
     * @brief Enables motion sense mode with specified sensitivity.
     * @param sensitivity Motion sensitivity enum value (default is Medium).
     * @return True if operation was successful, false otherwise.
     */
    bool enableMotionSense(DE2290D_MotionSensitivity_t sensitivity = DE2290D_MotionSensitivity_Medium);

    /**
     * @brief Enables or disables all 1D barcode types.
     * @param enable Set to true to enable, false to disable (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool enableAll1D(bool enable = true);

    /**
     * @brief Disables all 1D barcode types.
     * @return True if operation was successful, false otherwise.
     */
    bool disableAll1D();

    /**
     * @brief Enables or disables all 2D barcode types.
     * @param enable Set to true to enable, false to disable (default is true).
     * @return True if operation was successful, false otherwise.
     */
    bool enableAll2D(bool enable = true);

    /**
     * @brief Disables all 2D barcode types.
     * @return True if operation was successful, false otherwise.
     */
    bool disableAll2D();

    /**
     * @brief Starts a scan operation.
     * @return True if operation was successful, false otherwise.
     */
    bool startScan();

    /**
     * @brief Stops a scan operation.
     * @return True if operation was successful, false otherwise.
     */
    bool stopScan();

  private:
    // char _responseBuffer[]
    HardwareSerial *hwStream;
#ifndef ESP32
    SoftwareSerial *swStream;
#endif
    Stream *_serial;
};

#endif
