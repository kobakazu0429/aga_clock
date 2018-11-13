#define SRCLK (5)
#define RCLK (6)
#define SER (7)

void setup() {
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SER, OUTPUT);
}

// 点灯パターン(1=点灯)
const uint8_t PATTERNS[] = {
    0b01100000,
    0b01010000,
    0b00010000,
};

void loop() {
  for (uint8_t i = 0; i < 3; i++) {
    // 8ビット分のデータをシフトレジスタへ送る
    shiftOut(SER, SRCLK, LSBFIRST, PATTERNS[i]);

    // シフトレジスタの状態をストアレジスタへ反映させる
    digitalWrite(RCLK, LOW);
    digitalWrite(RCLK, HIGH);

    delay(800);
  }
}
