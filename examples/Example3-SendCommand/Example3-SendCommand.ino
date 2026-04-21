/*
  Send arbitrary commands undocumented in the library
  By: SparkFun Electronics (revised from original DE2120 library by Nick Poole @SparkFun)
  SparkFun Electronics
  Date: January 2026
  MIT License: This code is public domain.

  This example demonstrates how to use the "sendCommand()" method to send arbitrary serial commands to the barcode
  reader. It also demonstrates the "CIDENA" or "Code ID Enable" function, which includes the barcode type when
  transmitting the decoded string.

  sendCommand() takes two strings as arguments, concatenates them, adds the command prefix and the command suffix
  and then transmits the command to the module.

  NOTE: You must put the module into TTL mode by scanning the POR232. barcode in the datasheet.
  This will put the module in the correct mode to receive and transmit serial. The baud rate in POR232
  defaults to 115200 which is too fast for software serial. This library will automatically set the baud rate to
  9600bps.

  To connect the barcode scanner to an Arduino:

  (Arduino pin) = (Scanner pin)
  2 = TX pin on scanner
  3 = RX pin on scanner
  GND = GND
  3.3V = 3.3V
*/

#include "SoftwareSerial.h"
#include "SparkFun_DE2290D_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_DE2290D
DE2290D scanner;

#define BUFFER_LEN 40
char scanBuffer[BUFFER_LEN];

void setup()
{
    Serial.begin(115200);
    Serial.println("DE2290D Scanner Example");

    // --------- Older Arduino UNO style boards ----------
    // Uncomment the lines below and comment out the "Modern Boards" section if you are using an older board
    // with softSerial. Update the pins to match the connections on your board.
    // SoftwareSerial softSerial(2, 3); //RX, TX: Connect Arduino pin 2 to scanner TX pin. Connect Arduino pin 3 to
    // scanner RX pin. bool result = scanner.begin(softSerial);

    // ------------------- Modern Boards -----------------
    // Pass UART/SERIAL1
    // You can pass other serials if they are available on your board (i.e. Serial2)
    // Look up the pins corresponding to the Serial that you pass
    // for example, on the IoT RedBoard RP2350, UART0 corresponds to SERIAL1, with TX on pin 0 and RX on pin 1
    // You can also initialize a HardwareSerial however, your specific board/architecture allows and pass it to begin.
    bool result = scanner.begin(Serial1);
    // ---------------------------------------------------

    if (result == false)
    {
        Serial.println("Scanner did not respond. Please check wiring. Did you scan the POR232 barcode? Freezing...");
        while (1)
            ;
    }
    Serial.println("Scanner online!");
}

void loop()
{
    flushRx(); // Clear the serial rx buffer to avoid line endings

    Serial.println();
    Serial.println("Transmit Code ID with Barcode? (y/n)");
    Serial.println("-------------------------------------");
    Serial.println("Type 'y' or 'n' or scan a barcode: ");

    // Wait for the user to reply but look for barcodes in the meantime
    while (Serial.available() == false)
    {
        if (scanner.readBarcode(scanBuffer, BUFFER_LEN))
        {
            Serial.println("...");
            Serial.print("Code found: ");
            for (int i = 0; i < strlen(scanBuffer); i++)
                Serial.print(scanBuffer[i]);
            Serial.println();
        }

        delay(200);
    }

    // The "Code ID" is a character representing which barcode encoding is used in the code scanned
    // It will be prepended to the code itself read. For example, reading code SparkFun encoded in Code-128 will return
    // ASparkFun and reading code ABC-1234 in Code-39 will return IABC-1234.

    // For a full list of supported codes as well as a list of commands you can send with "sendCommand" check out the 2D
    // barcode scanner setting manual in this repo. The commands we found most useful (such as kCmdEnableTransferCodeId)
    // have been included in the SparkFun_DE2290D_Constants.h file in this repo have another command you found necessary
    // for your project? Open a pull request! :)
    switch (Serial.read())
    {

    case 'y':
        Serial.println("Code ID will be displayed on scan");
        scanner.sendCommand(kCmdEnableTransferCodeId);
        break;

    case 'n':
        Serial.println("Code ID will NOT be displayed on scan");
        scanner.sendCommand(kCmdDisableTransferCodeId);
        break;

    default:
        Serial.println("Command not recognized");
        break;
    }
}

void flushRx()
{
    while (Serial.available())
    {
        Serial.read();
        delay(1);
    }
}
