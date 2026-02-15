#define TT_STEP 8
#define TT_DIR  9

#define SH_STEP 4
#define SH_DIR  5

#define EL_STEP 6
#define EL_DIR  7

const unsigned int TT_DELAY = 200;
const unsigned int SH_DELAY = 30;
const unsigned int EL_DELAY = 40;


volatile int tt = 0, sh = 0, el = 0;

bool ttState = LOW, shState = LOW, elState = LOW;

inline void runAxis(int cmd, int stepPin, int dirPin,
                    unsigned int delayUs,
                    unsigned long &tRef, bool &stepState)
{
  if (cmd == 0) {
    if (stepState != LOW) { stepState = LOW; digitalWrite(stepPin, LOW); }
    return;
  }

  digitalWrite(dirPin, (cmd > 0) ? HIGH : LOW);

  unsigned long now = micros();
  if ((unsigned long)(now - tRef) >= delayUs) {
    tRef = now;
    stepState = !stepState;
    digitalWrite(stepPin, stepState);
  }
}


void readCmd() {
  if (Serial.read() != 'T') return;
  int t = Serial.parseInt();
  if (Serial.read() != 'S') return;
  int s = Serial.parseInt();
  if (Serial.read() != 'E') return;
  int e = Serial.parseInt();
  if (Serial.read() != '\n') return;

  tt = (t > 0) ? 1 : (t < 0 ? -1 : 0);
  sh = (s > 0) ? 1 : (s < 0 ? -1 : 0);
  el = (e > 0) ? 1 : (e < 0 ? -1 : 0);
}

void setup() {
  pinMode(TT_STEP, OUTPUT); pinMode(TT_DIR, OUTPUT);
  pinMode(SH_STEP, OUTPUT); pinMode(SH_DIR, OUTPUT);
  pinMode(EL_STEP, OUTPUT); pinMode(EL_DIR, OUTPUT);

  Serial.begin(115200);
  Serial.setTimeout(1); 
}

void loop() {

  runAxis(tt, TT_STEP, TT_DIR, TT_DELAY, ttT, ttState);
  runAxis(sh, SH_STEP, SH_DIR, SH_DELAY, shT, shState);
  runAxis(el, EL_STEP, EL_DIR, EL_DELAY, elT, elState);


  if (Serial.available()) {
    if (Serial.peek() == 'T') readCmd();
    else Serial.read(); 
  }
}
