//Projede gecen serv3 motoru kolun asagi yukari hareket etmesini saglar.
//Diger iki motor serv1 ve serv2 ise parmaklarin hareketi icin kullanilacaktir.




#include <Servo.h> //Servo motoru kütüphanesi 

//Servo motorlari tanimlanir.
Servo serv1;
Servo serv2;
Servo serv3;

//Ultrasonik sensörün trigger ve echo pinleri tanimlanir.
const int trig = 3;
const int echo = 9;

void setup() {

//Gerekli tum tanimlamalar
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);

serv1.attach(5);
serv2.attach(6);
serv3.attach(7);
Serial.begin(9600);
}

void loop() {

serv3.write(90);  //Baslangicta serv3 motoru 90 dereceye tanimlanir

//Diger iki motor 180 dereceye tanimlanir.
serv1.write(180);   
serv2.write(180);
delay(50);

int number = random(0,6);     //robot kolun tas,kagit,makas üclüsünden hangisini yapacagini 0'dan 6'ya kadar olusturdugumuz random sayilarin olasiligiyla yapacagiz.

//Trigger belirli araliklarla aktif edilir.
digitalWrite(trig,HIGH);
delay(500);
digitalWrite(trig,LOW);

//Echo'ya gelen dalganin süresi ikiye bölünerek aradaki mesafe ilgili formül uygulanarak hesaplanir.
int duration = pulseIn(echo,HIGH);
int distance = (duration/2)/29.1;

//Robot kol, karsisina gecen eli farketmesi icin 20 cm'lik bir deger belirledik. Distance 20'den kucukse tıpkı gercektekı gibi kol asagı yukarı hareket edecek.
if(distance < 20){

  serv3.write(60);
  delay(200);
  serv3.write(90);
  delay(200);
  serv3.write(60);
  delay(200);
  serv3.write(90);
  delay(200);
  serv3.write(60);
  delay(200);
  serv3.write(90);    
  delay(200);

//Kolun asagı yukarı hareketı sonrası number hangı sayıysa, ılgılı motorlar calısacak.
  if(number == 0 || number == 1){
   //Burada tum motorlar calisir ve tas hali olusur.
    serv1.write(0);
    serv2.write(0);
    delay(2000);
    serv1.write(180);
    serv2.write(180);
    delay(50);    
  }else if(number == 2 || number == 3){
    //Hicbir kol calismaz, kagit 
    serv1.write(180);
    serv2.write(180);
    delay(2000);
    serv1.write(180);
    serv2.write(180);
    delay(50);
  }else if(number == 4 || number == 5){
    //Sadece serv1 calisir ve makas hali olusur.
    serv1.write(0);
    serv2.write(180);
    delay(2000);
    serv1.write(180);
    serv2.write(180);
    delay(50);
  }
}
//Olayların akisini izlemek icin serial print fonksiyonu tanimlanir.
Serial.print(distance);
Serial.println(" cm");
delay(50);
}
