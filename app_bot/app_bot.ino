char cmd[8] = {'n','2','0','0','0','2','0','0'};
int x_val = 200;
int y_val = 200;
int cmd_x[3] = {};
int cmd_y[3] = {};
boolean stringComplete = false; // 用于判断数据是否读取完成

int INA = 4;  //电机A正反转控制端
int PWMA = 5; //电机A调速端
int INB = 7;  //电机B正反转控制端
int PWMB = 6; //电机B调速端

// void serialEvent()
// {
//   while (Serial.available())
//   {

//     char inChar = Serial.read();
//     if (inChar == 'x')
//     {
//         cmd_x[] += inChar;
//     }

//     if (inChar == 'y')
//     {
//         cmd_y[] += inChar;
//     }
//     else if (inChar == '\n')
//     {
//       stringComplete = true;
//       i = inString.toInt();
//     }
//     else
//       LED = inChar;
//   }
// }
void motion(int r_moto, int l_moto)
{
  r_moto-=x_val;  //方向相反交换
  l_moto+=x_val;

  if (r_moto >= 0)
  {
    digitalWrite(INA, 0);
  }
  else
  {
    digitalWrite(INA, 1);
  }
  if (l_moto >= 0)
  {
    digitalWrite(INB, 0);
  }
  else
  {
    digitalWrite(INB, 1);
  }
  analogWrite(PWMA, map(abs(r_moto), 0, 100, 0, 255));
  analogWrite(PWMB, map(abs(l_moto), 0, 100, 0, 255));
}

void serialEvent()
{
  while (Serial.available() >= 8)
  {
    if (Serial.read() == 'x')
    {
      cmd[0] = 'x';
      for (int i = 1; i <= 7; i++)
      {
        cmd[i] = Serial.read();
      }
    }
    
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
}

void loop()
{
  if (isDigit(cmd[1]))
  {
    for (int i = 1; i <= 3; i++)
    {
      cmd_x[i - 1] = cmd[i] - '0';
      cmd_y[i - 1] = cmd[i + 4] - '0';
    }
  }
  
  x_val = cmd_x[0] * 100 + cmd_x[1] * 10 + cmd_x[2];
  y_val = cmd_y[0] * 100 + cmd_y[1] * 10 + cmd_y[2];
  
  x_val -= 200;
  y_val -= 200;
  
  motion(y_val,y_val);

  // if (cmd[1] == '-')
  // {
  //   for (int i = 1; i <= 3; i++)
  //   {
  //     cmd[i] = cmd[i] << 1 ;
  //     cmd_x[i - 1] = cmd[i] - '0';
  //   }
  //   x_val = 0-(cmd_x[0] * 100 + cmd_x[1] * 10 + cmd_x[2]);
  // }

  Serial.print(' ');
  Serial.print(x_val);
  Serial.print(' ');
  Serial.print(y_val);
  Serial.print(' ');

  Serial.println();
}
