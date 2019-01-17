#include <MsTimer2.h>

const int segments_array[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 1, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

const int anode_pins[] = {2, 3, 4, 5, 6, 7, 8};
const int cathode_pins[] = {9, 10, 11, 12};
const int anode_pins_length = sizeof(anode_pins) / sizeof(anode_pins[0]);
const int cathode_pins_length = sizeof(cathode_pins) / sizeof(cathode_pins[0]);

int currentNum = 0;

void setup()
{
  // 2~8番ピンを出力ピンにする(アノード用)
  for (int i = 0; i < anode_pins_length; i++)
  {
    pinMode(anode_pins[i], OUTPUT);
  }

  // 9~12番ピンを出力ピンにする(カソード用)
  for (int i = 0; i < cathode_pins_length; i++)
  {
    pinMode(cathode_pins[i], OUTPUT);
  }

  MsTimer2::set(1000, countUp);
  MsTimer2::start();
}

void clearSegments()
{
  for (int i = 0; i < cathode_pins_length; i++) {
    digitalWrite(cathode_pins[i], HIGH);
  }
  for (int i = 0; i < anode_pins_length; i++) {
    digitalWrite(anode_pins[i], LOW);
  }
}

void displayNumbers() {
  for (int i = 0; i < cathode_pins_length;i++){
    clearSegments();
    digitalWrite(cathode_pins[i], LOW);
    for (int j = 0; j < anode_pins_length;j++) {
      digitalWrite(anode_pins[j], segments_array[getNum(i)][j]);
    }
    delay(1);
    // delayMicroseconds(500);
  }
}

int getNum(int id) {
  char parsed[24] = "";
  sprintf(parsed, "%04d", currentNum);

  String parsed_num = String(parsed);

  return String(parsed_num[id]).toInt();
}

void countUp()
{
  currentNum++;
}

void loop()
{
  displayNumbers();
}
