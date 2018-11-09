// https://fabkura.gitbooks.io/arduino-docs/content/chapter17.html
// 可変抵抗なし回路のスケッチ(電池なしもOK)

void setup(){
  pinMode(1, OUTPUT); //信号用ピン 6番ピン
  pinMode(2, OUTPUT); //信号用ピン 5番ピン
}

void loop(){
  //モーターの強さ指定
  // int val = 50; //0~255の値にする

  //アナログ入力:0番ピンの値を4で割る
  int val = analogRead(0) / 4; // 0~255の値にする

  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);

  analogWrite(3, val);
}