/*
 This example reads audio data from an InvenSense ICS-43432 I2S microphone
 breakout board, and prints out the spectrum to the Serial Monitor. The
 Serial Plotter built into the Arduino IDE (Tools -> Serial Plotter) can be
 used to plot the audio amplitude data.

 Circuit:
 * Arduino Zero, MKR Zero or MKR1000 board
 * ICS-43432:
   * GND connected GND
   * 3.3V connected 3.3V (Zero) or VCC (MKR1000, MKR Zero)
   * WS connected to pin 0 (Zero) or pin 3 (MKR1000, MKR Zero)
   * CLK connected to pin 1 (Zero) or pin 2 (MKR1000, MKR Zero)
   * SD connected to pin 9 (Zero) or pin A6 (MKR1000, MKR Zero)

 created 21 November 2016
 by Sandeep Mistry
 */

#include <ArduinoSound.h>

// sample rate for the input
const int sampleRate = 8000;

// size of the FFT to compute
const int fftSize = 128;

// size of the spectrum output, half of FFT size
const int spectrumSize = fftSize / 2;

// array to store spectrum output
int spectrum[spectrumSize];

// create an FFT analyzer to be used with the I2S input
FFTAnalyzer fftAnalyzer(fftSize);

void setup() {
// Open serial communications and wait for port to open:
  // A baud rate of 115200 is used instead of 9600 for a faster data rate
  // on non-native USB ports
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // setup the I2S audio input for the sample rate with 32-bits per sample
  if (!AudioInI2S.begin(sampleRate, 32)) {
    Serial.println("Failed to initialize I2S input!");
    while (1); // do nothing
  }

  // configure the I2S input as the input for the FFT analyzer
  if (!fftAnalyzer.input(AudioInI2S)) {
    Serial.println("Failed to set FFT analyzer input!");
    while (1); // do nothing
  }
}

void loop() {
  if (fftAnalyzer.available()) {
    fftAnalyzer.read(spectrum, spectrumSize);

    for (int i = 0; i < spectrumSize; i++) {
      Serial.print((i * sampleRate) / fftSize); // Frequency
      Serial.print(","); // CSV delimiter
      Serial.println(spectrum[i]); // Amplitude
    }
  }
}
