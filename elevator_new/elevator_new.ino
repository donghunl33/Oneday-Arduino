// Segment
int digits[10][7]
{
  {0, 1, 1, 0, 0, 0, 0}, // digit 1
  {1, 1, 0, 1, 1, 0, 1}, // digit 2
  {1, 1, 1, 1, 0, 0, 1}, // digit 3
  {0, 1, 1, 0, 0, 1, 1}, // digit 4
};

void displayDigit(int d)
{
  // A
  if(digits[d][0] == 1)
  {
    digitalWrite(8, HIGH);
  }
  else
  {
    digitalWrite(8, LOW);
  }

  // B
  if(digits[d][1] == 1)
  {
    digitalWrite(7, HIGH);
  }
  else
  {
    digitalWrite(7, LOW);
  }

  // C
  if(digits[d][2] == 1)
  {
    digitalWrite(6, HIGH);
  }
  else
  {
    digitalWrite(6, LOW);
  }

  // D
  if(digits[d][3] == 1)
  {
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
  }

  // E
  if(digits[d][4] == 1)
  {
    digitalWrite(4, HIGH);
  }
  else
  {
    digitalWrite(4, LOW);
  }

  // F
  if(digits[d][5] == 1)
  {
    digitalWrite(3, HIGH);
  }
  else
  {
    digitalWrite(3, LOW);
  }

  // G
  if(digits[d][6] == 1)
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
  }
}

// 버튼
const int BTN[4] = {13, 12, 11, 10};

int btnPress(int i) {
  int press;
  int btnState;
  static int prevBtnState = LOW;
  btnState = digitalRead(BTN[i]);
  press = (btnState == HIGH && prevBtnState == LOW);
  prevBtnState = btnState;
  return press; 
}

void pressed() {
  // 1층
  if (btnPress[0]) {
    if (first == false) {
      first = true;
      digitalWrite(LED[0], HIGH);
    }
    else {
      first = false;
      digitalWrite(LED[0], LOW);
    }
  }

  // 2층
  if (btnPress[1]) {
    if (first == false) {
      first = true;
      digitalWrite(LED[1], HIGH);
    }
    else {
      first = false;
      digitalWrite(LED[1], LOW);
    }
  }

  // 3층
  if (btnPress[2]) {
    if (first == false) {
      first = true;
      digitalWrite(LED[2], HIGH);
    }
    else {
      first = false;
      digitalWrite(LED[2], LOW);
    }
  }

  // 4층
  if (btnPress[3]) {
    if (first == false) {
      first = true;
      digitalWrite(LED[3], HIGH);
    }
    else {
      first = false;
      digitalWrite(LED[3], LOW);
    }
  }
}

bool first = false;
bool second = false;
bool third = false;
bool fourth = false;

bool dir = true; // true going up/ false going down

//LED
const int LED[4] = {A0, A1, A2, A3, A4, A5} // Floor : A0~A3, Mid : step1 = A4, step2 = A5

//location
double prev = 1.0;
double loc = 1.0;
int floor = 1;

// loc - floor == 0.3 => step1
// loc - floor == 0.6 => step2

// 우선 순위
int rank[4] = {0, 0, 0, 0};

int rank_in(int i){
  if (rank[0] == 0) {
    rank[0] = i;
    return rank;
  }
  else if (rank[1] == 0) {
    rank[1] = i;
    return rank;
  }
  else if (rank[2] == 0) {
    rank[2] = i;
    return rank;
  }
  else if (rank[3] == 0) {
    rank[3] = i;
    return rank;
  }
}

int rank_out(int i) {
    if (rank[0] == i) {
    rank[0] = 0;
    return rank;
  }
  else if (rank[1] == i) {
    rank[1] = 0;
    return rank;
  }
  else if (rank[2] == i) {
    rank[2] = 0;
    return rank;
  }
  else if (rank[3] == i) {
    rank[3] = 0;
    return rank;
  }
}

int rank_update(int i, int m = 0, ) {
  if (i == 0 && m == 0) {  // 한칸 씩 앞으로
    rank[0] = rank[1];
    rank[1] = rank[2];
    rank[3] = rank[2];
  }
  else if (i == 1 && m == 0) {  // 중간에 0 없애기
    for (int j = sizeof(rank)-1; j > 0; j--) {
      if (rank[j-1] == 0) {
        rank[j-1] = rank[j];
        rank[j] = 0
      }
    }
  }
  else if (i == 2) { // 중간에 넣기
    for (int j = 0; j < sizeof(rank)-1; j++) {
      if (rank[j] == m) {
        
      }
    }
  }
  else if (i == 3) { // 한캉씩 뒤로 밀기
    for()
  }
}

// timer
unsigned long prevMillis = 0;
long delayTime = 1000;

void setup() {
  // put your setup code here, to run once:
  // segment
  for(int i = 2; i < 9; i++)
  {
    pinMode(i, OUTPUT); // segment from A to G
  }

  // LED
  for(int i = 0; i < 5; i++)
  {
    pinMode(LED[i], OUTPUT);
  }

  // Button
  for(int i = 0; i < 4; i++)
  {
    pinMode(BTN[i], INPUT);
  }

  displayDigit(floor);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 버튼 인식
  pressed();

  // rank
  

  unsigned long curMillis = millis();

  if(curMillis - prevMillis >= delayTime) {
    //code
    //움직임

    //dir
    if(prev <= loc)
    {
      dir = true;
    }
    else
    {
      dir = false;
    }
    
    prevMillis = curMillis;
  }
}


// 움직임
void UP() {
  prev = loc;

  if (loc == floor) {
    loc += 0.3;
    digitalWrite(LED[4], HIGH);
  }
  else if (loc - floor == 0.3) {
    loc += 0.3;
    digitalWrite(LED[4], LOW);
    digitalWrite(LED[5], HIGH);
  }
  else if (loc - floor == 0.6) {
    loc += 0.4;
    digitalWrite(LED[5], LOW);
    displayDigital(floor);
  }
}

void DOWN() {
  prev = loc;

  if (loc == floor) {
    loc -= 0.4;
    digitalWrite(LED[5], HIGH);
  }
  else if (abs(loc - floor) == 0.6) {
    loc -= 0.3;
    digitalWrite(LED[5], LOW);
    digitalWrite(LED[4], HIGH);
  }
  else if (abs(loc - floor) == 0.3) {
    loc -= 0.3;
    digitalWrite(LED[4], LOW);
    displayDigital(floor);
  }
}

void STOP() {
  for (int i = 0; i < sizeof(rank/4); i++) {
    if (rank[i] != 0) {
      return;
    }
  }

  if (abs(loc - floor) == 0.3) {
    floor = abs(loc - 0.3);
  }
  else if (abs(loc - floor) == 0.6) {
    floor = abs(loc + 0.4);
  }
}
