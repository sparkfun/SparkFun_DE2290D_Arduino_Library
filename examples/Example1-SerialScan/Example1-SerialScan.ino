/*
  Begin scanning for barcodes
  By: SparkFun Electronics (revised from original DE2120 library by Nick Poole
  @SparkFun) Date: January 2026 License: This code is in the public domain, MIT License.

  This example demonstrates how to get the scanner connected and will output any
  barcode it sees.

  NOTE: You must put the module into TTL mode by scanning the POR232. barcode in
  the datasheet. This will put the module in the correct mode to receive and
  transmit serial. The baud rate in POR232 defaults to 115200 which is too fast
  for software serial. This library will automatically set the baud rate to
  9600bps.

  To connect the barcode scanner to an Arduino:

  (Arduino pin) = (Scanner pin)
  RX pin on Arduino = TX pin on scanner
  TX pin on Arduino = RX pin on scanner
  GND = GND
  3.3V = 3.3V

*/

#ifdef ESP32
#define ESP_RX 16
#define ESP_TX 17
#else
#include "SoftwareSerial.h"
#endif
#include "SparkFun_DE2290D_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_DE2290D
DE2290D scanner;

#define BUFFER_LEN 40
char scanBuffer[BUFFER_LEN];

void setup()
{
    Serial.begin(115200);
    Serial.println("DE2290D Scanner Example");
#ifdef ESP32
    Serial1.begin(115200, SERIAL_8N1, ESP_RX, ESP_TX);
#endif

    // --------- Older Arduino UNO style boards ----------
    // Uncomment the lines below and comment out the "Modern Boards" section
    // if you are using an older board with softSerial. Update the pins to
    // match the connections on your board. SoftwareSerial softSerial(2, 3);
    // //RX, TX: Connect Arduino pin 2 to scanner TX pin. Connect Arduino pin
    // 3 to scanner RX pin. bool result = scanner.begin(softSerial);

    // ------------------- Modern Boards -----------------
    // Pass UART/SERIAL1
    // You can pass other serials if they are available on your board (i.e.
    // Serial2) Look up the pins corresponding to the Serial that you pass for
    // example, on the IoT RedBoard RP2350, UART0 corresponds to SERIAL1, with
    // TX on pin 0 and RX on pin 1 You can also initialize a HardwareSerial
    // however, your specific board/architecture allows and pass it to begin.
    bool result = scanner.begin(Serial1);
    // ---------------------------------------------------

    if (result == false)
    {
        Serial.println("Scanner did not respond. Please check wiring. Did you scan "
                       "the POR232 barcode? Freezing...");
        while (1)
        {
            // Do nothing.
        }
    }
    Serial.println("Scanner online!");
}

void loop()
{
    if (scanner.readBarcode(scanBuffer, BUFFER_LEN))
    {
        Serial.print("Code found: ");
        for (int i = 0; i < strlen(scanBuffer); i++)
            Serial.print(scanBuffer[i]);
        Serial.println();
    }

    delay(200);
}
