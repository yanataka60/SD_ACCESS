#include <SD.h>
#define CABLESELECTPIN  (10)
// ファイル名は、8.3形式対応
boolean eflg;

void setup()
{
////  Serial.begin(9600);
// CS=pin10
// pin10 output
  pinMode(10,OUTPUT);
  pinMode( 6,INPUT);  //受信データ
  pinMode( 7,INPUT);  //CHK
  pinMode( 8,OUTPUT); //送信データ
  pinMode( 9,OUTPUT); //FLG
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
//LOWになるまでループ
  while(digitalRead(7) == HIGH){
  }
  // SD初期化
//  if( !SD.begin(CABLESELECTPIN) )
//  {
////    Serial.print("Failed : SD.begin()\n");
//    eflg = true;
//  } else {
//    eflg = false;
//  }
////  Serial.print("ND80 TEST\n");
}

//1BIT受信
//受信ビットをリターン
byte rcv1bit(void)
{
//HIGHになるまでループ
  while(digitalRead(7) != HIGH){
  }
//FLGをセット
  digitalWrite(9,HIGH);
//受信
  byte j_data = digitalRead(6);
////  Serial.print(j_data);
//LOWになるまでループ
  while(digitalRead(7) == HIGH){
  }
//FLGをリセット
  digitalWrite(9,LOW);
  return(j_data);
}

//1BYTE受信
//受信データをリターン
byte rcv1byte(void)
{
  byte i_data = 0;
//8回ループ
  for(int i=0;i<=7;i++){
    i_data=i_data+(rcv1bit()<<i);
  }
//  Serial.print("R:");
//  Serial.print(i_data,HEX);
//  Serial.print("\n");
  return(i_data);
}

//SDカードにSAVE
void f_save(void){
char f_name[9];
byte s_data[256];
  SD.begin(CABLESELECTPIN);
//ファイルネーム取得
  unsigned int ff_name = rcv1byte()+rcv1byte()*256;
//xxxx.btkに変換
  sprintf(f_name, "%04x.btk", ff_name);
////  Serial.println(f_name);
//スタートアドレス取得
  int s_adrs1 = rcv1byte();
  int s_adrs2 = rcv1byte();
//スタートアドレス算出
  unsigned int s_adrs = s_adrs1+s_adrs2*256;
////  Serial.println(s_adrs);
//エンドアドレス取得
  int e_adrs1 = rcv1byte();
  int e_adrs2 = rcv1byte();
//エンドアドレス算出
  unsigned int e_adrs = e_adrs1+e_adrs2*256;
////  Serial.println(e_adrs);
//ファイルサイズ算出
  unsigned int f_length = e_adrs - s_adrs;
////  Serial.print("\n");
////  Serial.println(f_length);
//ファイルが存在すればERROR
  if (SD.exists(f_name) == false){
//ファイルオープン
    File file = SD.open( f_name, FILE_WRITE );
    if( true == file ){
//状態コード送信(OK)
      snd1byte(0x00);
      file.write(s_adrs2);
      file.write(s_adrs1);
      file.write(e_adrs2);
      file.write(e_adrs1);

      long lp1 = 0;
      while (lp1 <= f_length){
        int i=0;
        while(i<=255 && lp1<=f_length){
          s_data[i]=rcv1byte();
          i++;
          lp1++;
        }
        file.write(s_data,i);
      }
      
//      for (long lp1 = 0;lp1 <= f_length;lp1++){
////  Serial.println(lp1);
//        file.write(rcv1byte());
//      }
      file.close();
////      Serial.print("SAVE END!\n");
    } else {
//状態コード送信(ERROR)
      snd1byte(0xFF);
////      Serial.print("SAVE ERROR!\n");
    }
  } else {
//状態コード送信(ERROR)
    snd1byte(0xF1);
    SD.begin(CABLESELECTPIN);
  }
}

//1BIT送信
void snd1bit(byte j_data)
{
////  Serial.print(j_data);
  if(j_data==1){
    digitalWrite(8,HIGH);
    }else{
    digitalWrite(8,LOW);
    }
  digitalWrite(9,HIGH);
//HIGHになるまでループ
  while(digitalRead(7) != HIGH){
  }
  digitalWrite(9,LOW);
//LOWになるまでループ
  while(digitalRead(7) == HIGH){
  }
}

//1BYTE送信
void snd1byte(byte i_data)
{
//  Serial.print("S:");
//  Serial.print(i_data,HEX);
//  Serial.print("\n");
//下位ビットから送信
  for(int i=0;i<=7;i++){
    snd1bit((i_data>>i)&0x01);
  }
}

//SDカードから読込
void f_load(void){
char f_name[9];
  SD.begin(CABLESELECTPIN);
//ファイルネーム取得
  unsigned int ff_name = rcv1byte()+rcv1byte()*256;
//xxxx.btkに変換
  sprintf(f_name, "%04x.btk", ff_name);
////  Serial.println(f_name);
//ファイルが存在しなければERROR
  if (SD.exists(f_name) == true){
//ファイルオープン
    File file = SD.open( f_name, FILE_READ );
    if( true == file ){
//状態コード送信(OK)
      snd1byte(0x00);
//スタートアドレス取得
      int s_adrs1 = file.read();
      snd1byte(s_adrs1);
//      Serial.println(s_adrs1,HEX);
      int s_adrs2 = file.read();
      snd1byte(s_adrs2);
//      Serial.println(s_adrs2,HEX);
      unsigned int s_adrs = s_adrs1*256+s_adrs2;
//      Serial.println(s_adrs,HEX);
//エンドアドレス取得
      int e_adrs1 = file.read();
      snd1byte(e_adrs1);
//      Serial.println(e_adrs1,HEX);
      int e_adrs2 = file.read();
      snd1byte(e_adrs2);
//      Serial.println(e_adrs2,HEX);
      unsigned int e_adrs = e_adrs1*256+e_adrs2;
//      Serial.println(e_adrs,HEX);
//ファイルサイズ算出
      unsigned int f_length = e_adrs - s_adrs;
//      Serial.println(f_length,HEX);
//データ送信
      for (unsigned int lp1 = 0;lp1 <= f_length;lp1++){
//        Serial.print("lp1:");
//        Serial.print(lp1);
        byte i_data = file.read();
        snd1byte(i_data);
      }
      file.close();
////      Serial.print("READ END!\n");
    } else {
//状態コード送信(ERROR)
      snd1byte(0xFF);
////      Serial.print("READ ERROR!\n");
    }  
  } else {
//状態コード送信(ERROR)
    snd1byte(0xF1);
    SD.begin(CABLESELECTPIN);
  }
}

void loop()
{
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  // SD初期化
  if( !SD.begin(CABLESELECTPIN) )
  {
////    Serial.print("Failed : SD.begin()\n");
    eflg = true;
  } else {
    eflg = false;
  }
//コマンド取得待ち
  byte cmd = rcv1byte();
////  Serial.println(cmd,HEX);
  if (eflg == false){
//80hでSDカードにsave
    if (cmd ==0x80){
////  Serial.println("SAVE START\n");
//LKIT-16は処理が間に合わず状態コードの受信に失敗していたためちょっとだけWait
      delay(1);
//状態コード送信(OK)
      snd1byte(0x00);
      f_save();
    }
//81hでSDカードからload
    if (cmd ==0x81){
////  Serial.println("LOAD START\n");
//LKIT-16は処理が間に合わず状態コードの受信に失敗していたためちょっとだけWait
      delay(1);
//状態コード送信(OK)
      snd1byte(0x00);
      f_load();
    }
  } else {
//状態コード送信(ERROR)
    snd1byte(0xF0);
  }
}
