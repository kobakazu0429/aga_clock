#include <Wire.h>

#define SRCLK (5)
#define RCLK (6)
#define SER (7)

const int cathode_pins[] = {9, 10, 11, 12};
const int cathode_pins_length = sizeof(cathode_pins) / sizeof(cathode_pins[0]);

const uint8_t PATTERNS[] = {0b11111100, 0b01100000, 0b11011010, 0b11110010,
                            0b01100110, 0b10110110, 0b10111110, 0b11100100,
                            0b11111110, 0b11110110};

String currentNum = "0000";

// 外部割り込みの状態
volatile int interruptState = LOW;

// 外部割り込みが発生した時に動作します。
void changeInterruptState() { interruptState = !interruptState; }

// RTCのレジスタテーブル(16byte)
int RegTbl[16];

// デバイスアドレス(スレーブ)
// ※Arduinoの仕様では8bitのアドレスを右に1bitシフトした「7bit」を使用する
// ※[8bit]Write : 0xA2 = 10100010 Read : 0xA3 = 10100011
byte DEVICE_ADDRESS = 0x51;

// 2進化10進数(BCD)を10進数に変換
byte BCDtoDec(byte value) {
  return ((value >> 4) * 10) + (value & 0x0F);
}

void setup() {
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SER, OUTPUT);

  for (int i = 0; i < cathode_pins_length; i++) {
    pinMode(cathode_pins[i], OUTPUT);
  }

  // 2ピンの状態がLOWからHIGHに変化した場合に外部割り込みを発生させる
  attachInterrupt(digitalPinToInterrupt(2), changeInterruptState, RISING);

  // マスタとしてI2Cバスに接続する
  Wire.begin();

  // I2Cスレーブに対して送信処理を開始する
  Wire.beginTransmission(DEVICE_ADDRESS);

  // レジスタのアドレスを指定する(0-15の内、先頭から)
  Wire.write(0x00);

  // ---------------------------------
  //  コントロールレジスタ
  // ---------------------------------
  // [00]Control1
  Wire.write(0x00);
  // [01]Control2
  // 0x02:アラーム割り込み時に3ピン[INT]をLOWにする
  Wire.write(0x02);

  // ---------------------------------
  //  時計・カレンダーレジスタ
  // ---------------------------------
  // アドレスの[02-05]及び[08-11]は2進化10進数(BCD)で指定します。

  // [02]Seconds(15秒)
  Wire.write(0x15);
  // [03]Minutes(20分)
  Wire.write(0x20);
  // [04]Hours(12時)
  Wire.write(0x12);
  // [05]Days(25日)
  Wire.write(0x25);
  // [06]Weekdays(月)
  // 0:日 1:月 2:火 3:水 4:木 5:金 6:土
  Wire.write(0x01);
  // [07]Month/Century(21世紀の12月)
  // ・Month(01-12) BCD形式
  // ・Century(先頭bit 0:20世紀[19xx年代],1(0x80):21世紀[20xx年代])
  Wire.write(0x12 | 0x80);
  // [08]Years(2017年)
  Wire.write(0x17);

  // ---------------------------------
  //  クロック出力レジスタ
  // ---------------------------------

  // [0D]CLKOUT Frequency
  // ・クロック出力機能を有効にする。
  //   ※有効:0x80 無効 :0x00
  // ・クロック周波数は1Hz(1秒間に1回)とする
  //   ※0x00:32768Hz, 0x01:1024Hz, 0x02:32Hz, 0x03:1Hz
  //
  // 次の設定だと2ピン[CLKOUT]から1秒に1回、クロック出力される
  Wire.write(0x80 | 0x03);

  // I2Cスレーブへの送信完了
  Wire.endTransmission();
}

void clearSegments() {
  sendSerialData(0b00000000);

  for (int i = 0; i < cathode_pins_length; i++) {
    digitalWrite(cathode_pins[i], HIGH);
  }
}

void sendSerialData(uint8_t data) {
  shiftOut(SER, SRCLK, LSBFIRST, data);
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH);
}

void displayNumbers() {
  for (int i = 0; i < cathode_pins_length; i++){
    clearSegments();
    digitalWrite(cathode_pins[i], LOW);
    int num = getNum(i);
    sendSerialData(PATTERNS[num]);
    delay(1);
  }
}

int getNum(int id) {
  return String(currentNum[id]).toInt();
}

void loop() {
  currentNum = String(BCDtoDec(RegTbl[4] & 0x3F)) + String(BCDtoDec(RegTbl[3] & 0x7F));
  displayNumbers();

  // 外部割込みが発生した場合
  if (interruptState == HIGH) {
    // レジスタのアドレスを先頭にする
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();

    // I2Cスレーブに16byteのレジスタデータを要求する
    Wire.requestFrom(DEVICE_ADDRESS, 16);

    // 16byteのデータを取得する
    for (int i = 0; i < 16; i++) {
      while (Wire.available() == 0) {}
      RegTbl[i] = Wire.read();
    }
    interruptState = !interruptState;
  }
}