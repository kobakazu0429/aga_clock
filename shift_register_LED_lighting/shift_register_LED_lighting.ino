#define SRCLK (5)
#define RCLK (6)
#define SER (7)

void setup() {
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SER, OUTPUT);
}

void loop() {
  // 入力状態をHIGHにする
  digitalWrite(SER, HIGH);

  for (int i = 0; i < 3; i++) {
    // シフトレジスタをシフトさせてSERの状態を記憶させる
    digitalWrite(SRCLK, LOW);
    digitalWrite(SRCLK, HIGH);

    // シフトレジスタの状態をストアレジスタへ反映させる
    digitalWrite(RCLK, LOW);
    digitalWrite(RCLK, HIGH);

    delay(200);

    // 以降の入力状態をLOWにする
    digitalWrite(SER, LOW);
  }
}
