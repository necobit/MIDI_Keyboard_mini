#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();

int kp[20] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 18,
              14, 15,
              16, 17,
              19, 22, 23
             };
int n[20];
int chatak[20];
int oct = 5;
int ch = 1;
int pc[17];
#define chata 20

void allnoteoff()
{
  for ( int i = 0; i <= 13; i++) {
    MIDI.sendNoteOff(oct * 12 + i , 100, ch);
  }
}


void setup()
{
  MIDI.begin(MIDI_CHANNEL_OMNI);
  for (int i = 0; i <= 19 ; i ++) {
    pinMode(kp[i], INPUT_PULLUP);
  }
}


void loop()
{
  //ノート部分スキャン
  for (int p = 0; p <= 12; p++) {
    if (digitalRead(kp[p]) == LOW && n[p] == 0) {
      if (chatak[p] > chata) {
        MIDI.sendNoteOn(oct * 12 + p, 100, ch);
        n[p] = 1;
        chatak[p] = 0;
        //     break;
      }
      else {
        chatak[p] ++;
      }
    }
    if (digitalRead(kp[p]) == HIGH && n[p] == 1) {
      MIDI.sendNoteOff(oct * 12 + p , 100, ch);
      n[p] = 0;
    }
  }

  //オクターブ
  if (digitalRead(kp[13]) == LOW && n[13] == 0) {
    if (chatak[13] > chata) {
      if (oct > 0 && oct <= 10) {
        allnoteoff();
        oct --;
      }
      n[13] = 1;
      chatak[13] = 0;
      //     break;
    }
    else {
      chatak[13] ++;
    }
  }
  if (digitalRead(kp[13]) == HIGH && n[13] == 1) {
    n[13] = 0;
  }

  if (digitalRead(kp[14]) == LOW && n[14] == 0) {
    if (chatak[14] > chata) {
      if (oct >= 0 && oct < 10) {
        allnoteoff();
        oct ++;
      }
      n[14] = 1;
      chatak[14] = 0;
      //     break;
    }
    else {
      chatak[14] ++;
    }
  }
  if (digitalRead(kp[14]) == HIGH && n[14] == 1) {
    n[14] = 0;
  }

  //チャンネル変更
  if (digitalRead(kp[15]) == LOW && n[15] == 0) {
    if (chatak[15] > chata) {
      if (ch > 1 && ch <= 16) {
        allnoteoff();
        ch --;
      }
      n[15] = 1;
      chatak[15] = 0;
      //     break;
    }
    else {
      chatak[15] ++;
    }
  }
  if (digitalRead(kp[15]) == HIGH && n[15] == 1) {
    n[15] = 0;
  }

  if (digitalRead(kp[16]) == LOW && n[16] == 0) {
    if (chatak[16] > chata) {
      if (ch >= 1 && ch < 16) {
        allnoteoff();
        ch ++;
      }
      n[16] = 1;
      chatak[16] = 0;
      //     break;
    }
    else {
      chatak[16] ++;
    }
  }
  if (digitalRead(kp[16]) == HIGH && n[16] == 1) {
    n[16] = 0;
  }

  //プログラムチェンジ

  if (digitalRead(kp[17]) == LOW && n[17] == 0) {
    if (chatak[17] > chata) {
      if (pc[ch] > 0 ) {
        allnoteoff();
        pc[ch] --;
        MIDI.sendProgramChange(pc[ch], ch);
      }
      n[17] = 1;
      chatak[17] = 0;
      //     break;
    }
    else {
      chatak[17] ++;
    }
  }
  if (digitalRead(kp[17]) == HIGH && n[17] == 1) {
    n[17] = 0;
  }

  if (digitalRead(kp[18]) == LOW && n[18] == 0) {
    if (chatak[18] > chata) {
      if (pc[ch] < 127) {
        allnoteoff();
        pc[ch] ++;
        MIDI.sendProgramChange(pc[ch], ch);
      }
      n[18] = 1;
      chatak[18] = 0;
      //     break;
    }
    else {
      chatak[18] ++;
    }
  }
  if (digitalRead(kp[18]) == HIGH && n[18] == 1) {
    n[18] = 0;
  }

  //モジュレーション
  if (digitalRead(kp[19]) == LOW && n[19] == 0) {
    if (chatak[19] > chata) {
      MIDI.sendControlChange(1, 127, ch);
      n[19] = 1;
      chatak[19] = 0;
      //     break;
    }
    else {
      chatak[19] ++;
    }
  }
  if (digitalRead(kp[19]) == HIGH && n[19] == 1) {
    MIDI.sendControlChange(1, 0, ch);
    n[19] = 0;
  }

}
