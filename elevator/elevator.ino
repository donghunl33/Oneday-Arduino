const int LED[10] = {7, 6, 5, 4, 3, 2, A0, 10, 9, 8}; // LED
const int BTN[3] = {13, 12, 11}; // 버튼

bool first = false; // 1층 호출상태
bool second = false; // 2층 호출상태
bool third = false; // 3층 호출상태

int prev = 0; // 이전위치
int loc = 0; // 현재위치

bool moved = false; // 루프당 움직임 여부
bool dir = true; // 현재 진행 방향 true : 상향 / false : 하향

unsigned long prevMillis = 0;
long delayTime = 1000;

void setup() {

  for(int i = 0; i < 10; i++)
  {
    pinMode(LED[i], OUTPUT);
  }

  for(int i = 0; i < 3; i++)
  {
    pinMode(BTN[i], INPUT);
  }
}

void loop() {
  unsigned long curMillis = millis();
  digitalWrite(LED[loc], HIGH); // 초기상태 loc=0 -> 1층에 위치

// 호출 인식
// 1층 호출 인식
  if(btnPress(0)) 
  {
    if(first == false)
    {
      first = true;
      digitalWrite(LED[7], HIGH);
    }
    else
    {
      first = false;
      digitalWrite(LED[7], LOW);
    }
  }

// 2층 호출 인식
  if(btnPress(1)) 
  {
    if(second == false)
    {
      second = true;
      digitalWrite(LED[8], HIGH);
    }
    else
    {
      second = false;
      digitalWrite(LED[8], LOW);
    }
  }

// 3층 호출 인식
  if(btnPress(2)) 
  {
    if(third == false)
    {
      third = true;
      digitalWrite(LED[9], HIGH);
    }
    else
    {
      third = false;
      digitalWrite(LED[9], LOW);
    }
  }

/////////////////////////////

// 엘리베이터 이동 
  if(curMillis - prevMillis >= delayTime)
  {
    if(dir == true)
    {
      floor_3();
      floor_2();
      floor_1();
    }
    else
    {
      floor_1();
      floor_2();
      floor_3();
    }

// 이동하는 방향 설정    
    if(prev <= loc)
    {
      dir = true;
    }
    else
    {
      dir = false;
    }

////////////////////////////
// 호출 취소시
    if(first == false && second == false && third == false)
    {
      prev = loc;

      if(loc == 1 || loc == 4)
      {
        loc--;
      }
      else if(loc == 2 || loc == 5)
      {
        loc++;
      }
      
      digitalWrite(LED[prev],LOW);
      digitalWrite(LED[loc], HIGH);
    }

// 엘리베이터 이동 표시
    digitalWrite(LED[prev], LOW);
    digitalWrite(LED[loc], HIGH);

    prevMillis = curMillis;
  }

// 움직임 여부 리셋
  moved = false;
}

// functions
// 1. 버튼 인식 함수
int btnPress(int i) {
  int press;
  int btnState;
  static int prevBtnState = LOW;
  btnState = digitalRead(BTN[i]);
  press = (btnState == HIGH && prevBtnState == LOW);
  prevBtnState = btnState;
  return press;
}

// 2. 층에 도착했거나 3층에서 호출해 이동
void floor_3() {
  if(third == true)
  {
    if(moved == false)
    {
      if(loc == 6)
      {
        digitalWrite(LED[9], LOW);
        third = false;
      }
      else if(loc < 6)
      {
        prev = loc;
        loc++;
        moved = true;
      }
    }
  }
}
  
// 3. 2층에 도착했거나 2층에서 호출해 이동
void floor_2() {
  if(second == true)
  {
    if(loc == 3)
    {
      digitalWrite(LED[8], LOW);
      second = false;
    }
    else if(loc > 3)
    {
      if(moved == false)
      {
        prev = loc;
        loc--;
        moved = true;
      }
    }
    else
    {
      if(moved == false)
      {
        prev = loc;
        loc++;
        moved = true;
      }
    }
  }
}

// 4. 1층에 도착했거나 1층에서 호출해 이동
void floor_1() {
  if(first == true)
  {
    if(loc == 0)
    {
      digitalWrite(LED[7], LOW);
      first = false;
    }
    else if(loc > 0)
    {
      if(moved == false)
      {
        prev = loc;
        loc--;
        moved = true;
      }
    }
  }
}