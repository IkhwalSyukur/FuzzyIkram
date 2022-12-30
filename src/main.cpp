#include <Arduino.h>
#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();

int flame1=0;
int flame2=0;
int flame3=4000;
int flame4=0;
int flame5=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Fuzzy Input 1
  FuzzyInput *flame1 = new FuzzyInput(1);
  FuzzySet *No_Terbaca1 = new FuzzySet(0, 0, 1024, 3072);
  flame1->addFuzzySet(No_Terbaca1);
  FuzzySet *Terbaca1 = new FuzzySet(1024, 3072, 4096, 4096);
  flame1->addFuzzySet(Terbaca1);
  fuzzy->addFuzzyInput(flame1);
  // Fuzzy Input 2
  FuzzyInput *flame2 = new FuzzyInput(2);
  FuzzySet *No_Terbaca2 = new FuzzySet(0, 0, 1024, 3072);
  flame2->addFuzzySet(No_Terbaca2);
  FuzzySet *Terbaca2 = new FuzzySet(1024, 3072, 4096, 4096);
  flame2->addFuzzySet(Terbaca2);
  fuzzy->addFuzzyInput(flame2);
  // Fuzzy Input 3
  FuzzyInput *flame3 = new FuzzyInput(3);
  FuzzySet *No_Terbaca3 = new FuzzySet(0, 0, 1024, 3072);
  flame3->addFuzzySet(No_Terbaca3);
  FuzzySet *Terbaca3 = new FuzzySet(1024, 3072, 4096, 4096);
  flame3->addFuzzySet(Terbaca3);
  fuzzy->addFuzzyInput(flame3);
  // Fuzzy Input 4
  FuzzyInput *flame4 = new FuzzyInput(4);
  FuzzySet *No_Terbaca4 = new FuzzySet(0, 0, 1024, 3072);
  flame4->addFuzzySet(No_Terbaca4);
  FuzzySet *Terbaca4 = new FuzzySet(1024, 3072, 4096, 4096);
  flame4->addFuzzySet(Terbaca4);
  fuzzy->addFuzzyInput(flame4);
  // Fuzzy Input 5
  FuzzyInput *flame5 = new FuzzyInput(5);
  FuzzySet *No_Terbaca5 = new FuzzySet(0, 0, 1024, 3072);
  flame5->addFuzzySet(No_Terbaca5);
  FuzzySet *Terbaca5 = new FuzzySet(1024, 3072, 4096, 4096);
  flame5->addFuzzySet(Terbaca5);
  fuzzy->addFuzzyInput(flame5);

  // Fuzzy Output
  FuzzyOutput *servo = new FuzzyOutput(1);
  FuzzySet *Nope = new FuzzySet(0, 0, 0, 0);
  servo->addFuzzySet(Nope);
  FuzzySet *Min = new FuzzySet(0, 0, 45, 90);
  servo->addFuzzySet(Min);
  FuzzySet *Center = new FuzzySet(45, 80, 100, 135);
  servo->addFuzzySet(Center);
  FuzzySet *Max = new FuzzySet(90, 135, 180, 180);
  servo->addFuzzySet(Max);
  fuzzy->addFuzzyOutput(servo);

  // Fuzzy Rule 01
  FuzzyRuleAntecedent *ifNT1_NT2_1 = new FuzzyRuleAntecedent();
  ifNT1_NT2_1->joinWithAND(No_Terbaca1, No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_1 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_1->joinWithAND(ifNT1_NT2_1,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_NT4_1 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_NT4_1->joinWithAND(ifNT1_NT2_NT3_1,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_NT4_NT5_1 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_NT4_NT5_1->joinWithAND(ifNT1_NT2_NT3_NT4_1,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope1 = new FuzzyRuleConsequent();
  thenServoNope1->addOutput(Nope);
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifNT1_NT2_NT3_NT4_NT5_1, thenServoNope1);

  // Fuzzy Rule 02
  FuzzyRuleAntecedent *ifT1_NT2_2 = new FuzzyRuleAntecedent();
  ifT1_NT2_2->joinWithAND(Terbaca1, No_Terbaca2);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_2 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_2->joinWithAND(ifT1_NT2_2,No_Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_NT4_2 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_NT4_2->joinWithAND(ifT1_NT2_NT3_2,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_NT4_NT5_2 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_NT4_NT5_2->joinWithAND(ifT1_NT2_NT3_NT4_2,No_Terbaca5);
  FuzzyRuleConsequent *thenServoMin2 = new FuzzyRuleConsequent();
  thenServoMin2->addOutput(Min);
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifT1_NT2_NT3_NT4_NT5_2, thenServoMin2);

  // Fuzzy Rule 03
  FuzzyRuleAntecedent *ifT1_T2_3 = new FuzzyRuleAntecedent();
  ifT1_T2_3->joinWithAND(Terbaca1, Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_NT3_3 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_3->joinWithAND(ifT1_T2_3,No_Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_NT3_NT4_3 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_NT4_3->joinWithAND(ifT1_T2_NT3_3,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_NT3_NT4_NT5_3 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_NT4_NT5_3->joinWithAND(ifT1_T2_NT3_NT4_3,No_Terbaca5);
  FuzzyRuleConsequent *thenServoMin3 = new FuzzyRuleConsequent();
  thenServoMin3->addOutput(Min);
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifT1_T2_NT3_NT4_NT5_3, thenServoMin3);

  // Fuzzy Rule 04
  FuzzyRuleAntecedent *ifT1_NT2_4 = new FuzzyRuleAntecedent();
  ifT1_NT2_4->joinWithAND(Terbaca1, No_Terbaca2);
  FuzzyRuleAntecedent *ifT1_NT2_T3_4 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_4->joinWithAND(ifT1_NT2_4,Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_T3_NT4_4 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_NT4_4->joinWithAND(ifT1_NT2_T3_4,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_T3_NT4_NT5_4 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_NT4_NT5_4->joinWithAND(ifT1_NT2_T3_NT4_4,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope4 = new FuzzyRuleConsequent();
  thenServoNope4->addOutput(Nope);
  FuzzyRule *fuzzyRule04 = new FuzzyRule(4, ifT1_NT2_T3_NT4_NT5_4, thenServoNope4);

  // Fuzzy Rule 5
  FuzzyRuleAntecedent *ifT1_NT2_5 = new FuzzyRuleAntecedent();
  ifT1_NT2_5->joinWithAND(Terbaca1, No_Terbaca2);  
  FuzzyRuleAntecedent *ifT1_NT2_NT3_5 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_5->joinWithAND(ifT1_NT2_5,No_Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_T4_5 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_T4_5->joinWithAND(ifT1_NT2_NT3_5,Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_T4_NT5_5 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_T4_NT5_5->joinWithAND(ifT1_NT2_NT3_T4_5,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope5 = new FuzzyRuleConsequent();
  thenServoNope5->addOutput(Nope);
  FuzzyRule *fuzzyRule05 = new FuzzyRule(5, ifT1_NT2_NT3_T4_NT5_5, thenServoNope5);

  // Fuzzy Rule 6
  FuzzyRuleAntecedent *ifT1_NT2_6 = new FuzzyRuleAntecedent();
  ifT1_NT2_6->joinWithAND(Terbaca1, No_Terbaca2);  
  FuzzyRuleAntecedent *ifT1_NT2_NT3_6 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_6->joinWithAND(ifT1_NT2_6,No_Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_NT4_6 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_NT4_6->joinWithAND(ifT1_NT2_NT3_6,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_NT4_T5_6 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_NT4_T5_6->joinWithAND(ifT1_NT2_NT3_NT4_6,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope6 = new FuzzyRuleConsequent();
  thenServoNope6->addOutput(Nope);  
  FuzzyRule *fuzzyRule06 = new FuzzyRule(6, ifT1_NT2_NT3_NT4_T5_6, thenServoNope6);

  //Fuzzy Rule 7
  FuzzyRuleAntecedent *ifNT1_T2_7 = new FuzzyRuleAntecedent();
  ifNT1_T2_7->joinWithAND(No_Terbaca1,Terbaca2);  
  FuzzyRuleAntecedent *ifNT1_T2_NT3_7 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_7->joinWithAND(ifNT1_T2_7,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_NT4_7 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_NT4_7->joinWithAND(ifNT1_T2_NT3_7,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_NT4_NT5_7 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_NT4_NT5_7->joinWithAND(ifNT1_T2_NT3_NT4_7,No_Terbaca5);
  FuzzyRuleConsequent *thenServoMin7 = new FuzzyRuleConsequent();
  thenServoMin7->addOutput(Min);
  FuzzyRule *fuzzyRule07 = new FuzzyRule(7, ifNT1_T2_NT3_NT4_NT5_7, thenServoMin7);

  //Fuzzy Rule 8
  FuzzyRuleAntecedent *ifNT1_T2_8 = new FuzzyRuleAntecedent();
  ifNT1_T2_8->joinWithAND(No_Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifNT1_T2_T3_8 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_8->joinWithAND(ifNT1_T2_8,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_T3_NT4_8 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_NT4_8->joinWithAND(ifNT1_T2_T3_8,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_T3_NT4_NT5_8 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_NT4_NT5_8->joinWithAND(ifNT1_T2_T3_NT4_8,No_Terbaca5);
  FuzzyRuleConsequent *thenServoCenter8 = new FuzzyRuleConsequent();
  thenServoCenter8->addOutput(Center);
  FuzzyRule *fuzzyRule08 = new FuzzyRule(8, ifNT1_T2_T3_NT4_NT5_8, thenServoCenter8);

  //Fuzzy Rule 9
  FuzzyRuleAntecedent *ifNT1_T2_9 = new FuzzyRuleAntecedent();
  ifNT1_T2_9->joinWithAND(No_Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_9 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_9->joinWithAND(ifNT1_T2_9,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_T4_9 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_T4_9->joinWithAND(ifNT1_T2_NT3_9,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_T4_NT5_9 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_T4_NT5_9->joinWithAND(ifNT1_T2_NT3_T4_9,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope9 = new FuzzyRuleConsequent();
  thenServoNope9->addOutput(Nope);
  FuzzyRule *fuzzyRule09 = new FuzzyRule(9, ifNT1_T2_NT3_T4_NT5_9, thenServoNope9);

  //Fuzzy Rule 10
  FuzzyRuleAntecedent *ifNT1_T2_10 = new FuzzyRuleAntecedent();
  ifNT1_T2_10->joinWithAND(No_Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_10 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_10->joinWithAND(ifNT1_T2_10,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_NT4_10 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_NT4_10->joinWithAND(ifNT1_T2_NT3_10,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_NT4_T5_10 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_NT4_T5_10->joinWithAND(ifNT1_T2_NT3_NT4_10,Terbaca5);
  FuzzyRuleConsequent *thenServoNope10 = new FuzzyRuleConsequent();
  thenServoNope10->addOutput(Nope);
  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, ifNT1_T2_NT3_NT4_T5_10, thenServoNope10);

  //Fuzzy Rule 11
  FuzzyRuleAntecedent *ifNT1_NT2_11 = new FuzzyRuleAntecedent();
  ifNT1_NT2_11->joinWithAND(No_Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_11 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_11->joinWithAND(ifNT1_NT2_11,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_NT4_11 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_NT4_11->joinWithAND(ifNT1_NT2_T3_11,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_NT4_NT5_11 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_NT4_NT5_11->joinWithAND(ifNT1_NT2_T3_NT4_11,No_Terbaca5);
  FuzzyRuleConsequent *thenServoCenter11 = new FuzzyRuleConsequent();
  thenServoCenter11->addOutput(Center);
  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, ifNT1_NT2_T3_NT4_NT5_11, thenServoCenter11);

  //Fuzzy Rule 12
  FuzzyRuleAntecedent *ifNT1_NT2_12 = new FuzzyRuleAntecedent();
  ifNT1_NT2_12->joinWithAND(No_Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_12 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_12->joinWithAND(ifNT1_NT2_12,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_T4_12 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_T4_12->joinWithAND(ifNT1_NT2_T3_12,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_T4_NT5_12 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_T4_NT5_12->joinWithAND(ifNT1_NT2_T3_T4_12,No_Terbaca5);
  FuzzyRuleConsequent *thenServoCenter12 = new FuzzyRuleConsequent();
  thenServoCenter12->addOutput(Center);
  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, ifNT1_NT2_T3_T4_NT5_12, thenServoCenter12);

  //Fuzzy Rule 13
  FuzzyRuleAntecedent *ifNT1_NT2_13 = new FuzzyRuleAntecedent();
  ifNT1_NT2_13->joinWithAND(No_Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_13 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_13->joinWithAND(ifNT1_NT2_13,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_NT4_13 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_NT4_13->joinWithAND(ifNT1_NT2_T3_13,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_NT4_T5_13 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_NT4_T5_13->joinWithAND(ifNT1_NT2_T3_NT4_13,Terbaca5);
  FuzzyRuleConsequent *thenServoNope13 = new FuzzyRuleConsequent();
  thenServoNope10->addOutput(Nope);
  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, ifNT1_NT2_T3_NT4_T5_13, thenServoNope13);

  //Fuzzy Rule 14
  FuzzyRuleAntecedent *ifNT1_NT2_14 = new FuzzyRuleAntecedent();
  ifNT1_NT2_14->joinWithAND(No_Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_14 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_14->joinWithAND(ifNT1_NT2_14,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_T4_14 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_T4_14->joinWithAND(ifNT1_NT2_NT3_14,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_T4_NT5_14 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_T4_NT5_14->joinWithAND(ifNT1_NT2_NT3_T4_14,No_Terbaca5);
  FuzzyRuleConsequent *thenServoMax14 = new FuzzyRuleConsequent();
  thenServoMax14->addOutput(Max);
  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, ifNT1_NT2_NT3_T4_NT5_14, thenServoMax14);

  //Fuzzy Rule 15
  FuzzyRuleAntecedent *ifNT1_NT2_15 = new FuzzyRuleAntecedent();
  ifNT1_NT2_15->joinWithAND(No_Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_15 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_15->joinWithAND(ifNT1_NT2_15,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_T4_15 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_T4_15->joinWithAND(ifNT1_NT2_NT3_15,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_T4_T5_15 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_T4_T5_15->joinWithAND(ifNT1_NT2_NT3_T4_15,Terbaca5);
  FuzzyRuleConsequent *thenServoMax15 = new FuzzyRuleConsequent();
  thenServoMax15->addOutput(Max);
  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, ifNT1_NT2_NT3_T4_T5_15, thenServoMax15);

  //Fuzzy Rule 16
  FuzzyRuleAntecedent *ifNT1_NT2_16 = new FuzzyRuleAntecedent();
  ifNT1_NT2_16->joinWithAND(No_Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_16 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_16->joinWithAND(ifNT1_NT2_16,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_NT4_16 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_NT4_16->joinWithAND(ifNT1_NT2_NT3_16,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_NT3_NT4_T5_16 = new FuzzyRuleAntecedent();
  ifNT1_NT2_NT3_NT4_T5_16->joinWithAND(ifNT1_NT2_NT3_NT4_16,Terbaca5);
  FuzzyRuleConsequent *thenServoMax16 = new FuzzyRuleConsequent();
  thenServoMax16->addOutput(Max);
  FuzzyRule *fuzzyRule16 = new FuzzyRule(16, ifNT1_NT2_NT3_NT4_T5_16, thenServoMax16);

  //Fuzzy Rule 17
  FuzzyRuleAntecedent *ifT1_T2_17 = new FuzzyRuleAntecedent();
  ifT1_T2_17->joinWithAND(Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_T3_17 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_17->joinWithAND(ifT1_T2_17,Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_T3_NT4_17 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_NT4_17->joinWithAND(ifT1_T2_T3_17,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_T3_NT4_NT5_17 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_NT4_NT5_17->joinWithAND(ifT1_T2_T3_NT4_17,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope17 = new FuzzyRuleConsequent();
  thenServoNope17->addOutput(Nope);
  FuzzyRule *fuzzyRule17 = new FuzzyRule(17, ifT1_T2_T3_NT4_NT5_17, thenServoNope17);

  //Fuzzy Rule 18
  FuzzyRuleAntecedent *ifT1_T2_18 = new FuzzyRuleAntecedent();
  ifT1_T2_18->joinWithAND(Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_NT3_18 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_18->joinWithAND(ifT1_T2_18,No_Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_NT3_T4_18 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_T4_18->joinWithAND(ifT1_T2_NT3_18,Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_NT3_T4_NT5_18 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_T4_NT5_18->joinWithAND(ifT1_T2_NT3_T4_18,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope18 = new FuzzyRuleConsequent();
  thenServoNope18->addOutput(Nope);
  FuzzyRule *fuzzyRule18 = new FuzzyRule(18, ifT1_T2_NT3_T4_NT5_18, thenServoNope18);

  //Fuzzy Rule 19
  FuzzyRuleAntecedent *ifT1_T2_19 = new FuzzyRuleAntecedent();
  ifT1_T2_19->joinWithAND(Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_NT3_19 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_19->joinWithAND(ifT1_T2_19,No_Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_NT3_NT4_19 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_NT4_19->joinWithAND(ifT1_T2_NT3_19,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_NT3_NT4_T5_19 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_NT4_T5_19->joinWithAND(ifT1_T2_NT3_NT4_19,Terbaca5);
  FuzzyRuleConsequent *thenServoNope19 = new FuzzyRuleConsequent();
  thenServoNope19->addOutput(Nope);
  FuzzyRule *fuzzyRule19 = new FuzzyRule(19, ifT1_T2_NT3_NT4_T5_19, thenServoNope19);

  //Fuzzy Rule 20
  FuzzyRuleAntecedent *ifT1_NT2_20 = new FuzzyRuleAntecedent();
  ifT1_NT2_20->joinWithAND(Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifT1_NT2_T3_20 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_20->joinWithAND(ifT1_NT2_20,Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_T3_T4_20 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_T4_20->joinWithAND(ifT1_NT2_T3_20,Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_T3_T4_NT5_20 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_T4_NT5_20->joinWithAND(ifT1_NT2_T3_T4_20,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope20 = new FuzzyRuleConsequent();
  thenServoNope20->addOutput(Nope);
  FuzzyRule *fuzzyRule20 = new FuzzyRule(20, ifT1_NT2_T3_T4_NT5_20, thenServoNope20);

  //Fuzzy Rule 21
  FuzzyRuleAntecedent *ifT1_NT2_21 = new FuzzyRuleAntecedent();
  ifT1_NT2_21->joinWithAND(Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifT1_NT2_T3_21 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_21->joinWithAND(ifT1_NT2_21,Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_T3_NT4_21 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_NT4_21->joinWithAND(ifT1_NT2_T3_21,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_T3_NT4_T5_21 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_NT4_T5_21->joinWithAND(ifT1_NT2_T3_NT4_21,Terbaca5);
  FuzzyRuleConsequent *thenServoNope21 = new FuzzyRuleConsequent();
  thenServoNope21->addOutput(Nope);
  FuzzyRule *fuzzyRule21 = new FuzzyRule(21, ifT1_NT2_T3_NT4_T5_21, thenServoNope21);

  //Fuzzy Rule 22
  FuzzyRuleAntecedent *ifT1_NT2_22 = new FuzzyRuleAntecedent();
  ifT1_NT2_22->joinWithAND(Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_22 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_22->joinWithAND(ifT1_NT2_22,Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_T4_22 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_T4_22->joinWithAND(ifT1_NT2_NT3_22,Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_NT3_T4_T5_22 = new FuzzyRuleAntecedent();
  ifT1_NT2_NT3_T4_T5_22->joinWithAND(ifT1_NT2_NT3_T4_22,Terbaca5);
  FuzzyRuleConsequent *thenServoNope22 = new FuzzyRuleConsequent();
  thenServoNope22->addOutput(Nope);
  FuzzyRule *fuzzyRule22 = new FuzzyRule(22, ifT1_NT2_NT3_T4_T5_22, thenServoNope22);

  //Fuzzy Rule 23
  FuzzyRuleAntecedent *ifNT1_T2_23 = new FuzzyRuleAntecedent();
  ifNT1_T2_23->joinWithAND(No_Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifNT1_T2_T3_23 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_23->joinWithAND(ifNT1_T2_23,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_T3_T4_23 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_T4_23->joinWithAND(ifNT1_T2_T3_23,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_T3_T4_NT5_23 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_T4_NT5_23->joinWithAND(ifNT1_T2_T3_T4_23,No_Terbaca5);
  FuzzyRuleConsequent *thenServoCenter23 = new FuzzyRuleConsequent();
  thenServoCenter23->addOutput(Center);
  FuzzyRule *fuzzyRule23 = new FuzzyRule(23, ifNT1_T2_T3_T4_NT5_23, thenServoCenter23);

  //Fuzzy Rule 24
  FuzzyRuleAntecedent *ifNT1_T2_24 = new FuzzyRuleAntecedent();
  ifNT1_T2_24->joinWithAND(No_Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifNT1_T2_T3_24 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_24->joinWithAND(ifNT1_T2_24,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_T3_NT4_24 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_NT4_24->joinWithAND(ifNT1_T2_T3_24,No_Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_T3_NT4_T5_24 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_NT4_T5_24->joinWithAND(ifNT1_T2_T3_NT4_24,Terbaca5);
  FuzzyRuleConsequent *thenServoNope24 = new FuzzyRuleConsequent();
  thenServoNope24->addOutput(Nope);
  FuzzyRule *fuzzyRule24 = new FuzzyRule(24, ifNT1_T2_T3_NT4_T5_24, thenServoNope24);

  //Fuzzy Rule 25 
  FuzzyRuleAntecedent *ifNT1_T2_25 = new FuzzyRuleAntecedent();
  ifNT1_T2_25->joinWithAND(No_Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_25 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_25->joinWithAND(ifNT1_T2_25,No_Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_T4_25 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_T4_25->joinWithAND(ifNT1_T2_NT3_25,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_NT3_T4_T5_25 = new FuzzyRuleAntecedent();
  ifNT1_T2_NT3_T4_T5_25->joinWithAND(ifNT1_T2_NT3_T4_25,Terbaca5); 
  FuzzyRuleConsequent *thenServoNope25 = new FuzzyRuleConsequent();
  thenServoNope25->addOutput(Nope);
  FuzzyRule *fuzzyRule25 = new FuzzyRule(25, ifNT1_T2_NT3_T4_T5_25, thenServoNope25);

  //Fuzzy Rule 26
  FuzzyRuleAntecedent *ifNT1_NT2_26 = new FuzzyRuleAntecedent();
  ifNT1_NT2_26->joinWithAND(No_Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_26 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_26->joinWithAND(ifNT1_NT2_26,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_T4_26 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_T4_26->joinWithAND(ifNT1_NT2_T3_26,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_NT2_T3_T4_T5_26 = new FuzzyRuleAntecedent();
  ifNT1_NT2_T3_T4_T5_26->joinWithAND(ifNT1_NT2_T3_T4_26,Terbaca5); 
  FuzzyRuleConsequent *thenServoNope26 = new FuzzyRuleConsequent();
  thenServoNope26->addOutput(Nope);
  FuzzyRule *fuzzyRule26 = new FuzzyRule(26, ifNT1_NT2_T3_T4_T5_26, thenServoNope26);

  //Fuzzy Rule 27
  FuzzyRuleAntecedent *ifT1_T2_27 = new FuzzyRuleAntecedent();
  ifT1_T2_27->joinWithAND(Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_T3_27 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_27->joinWithAND(ifT1_T2_27,Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_T3_T4_27 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_T4_27->joinWithAND(ifT1_T2_T3_27,Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_T3_T4_NT5_27 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_T4_NT5_27->joinWithAND(ifT1_T2_T3_T4_27,No_Terbaca5);
  FuzzyRuleConsequent *thenServoNope27 = new FuzzyRuleConsequent();
  thenServoNope27->addOutput(Nope);
  FuzzyRule *fuzzyRule27 = new FuzzyRule(27, ifT1_T2_T3_T4_NT5_27, thenServoNope27);

  //Fuzzy Rule 28
  FuzzyRuleAntecedent *ifT1_T2_28 = new FuzzyRuleAntecedent();
  ifT1_T2_28->joinWithAND(Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_T3_28 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_28->joinWithAND(ifT1_T2_28,Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_T3_NT4_28 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_NT4_28->joinWithAND(ifT1_T2_T3_28,No_Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_T3_NT4_T5_28 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_NT4_T5_28->joinWithAND(ifT1_T2_T3_NT4_28,Terbaca5);
  FuzzyRuleConsequent *thenServoNope28 = new FuzzyRuleConsequent();
  thenServoNope28->addOutput(Nope);
  FuzzyRule *fuzzyRule28 = new FuzzyRule(28, ifT1_T2_T3_NT4_T5_28, thenServoNope28);

  //Fuzzy Rule 29
  FuzzyRuleAntecedent *ifT1_NT2_29 = new FuzzyRuleAntecedent();
  ifT1_NT2_29->joinWithAND(Terbaca1,No_Terbaca2);
  FuzzyRuleAntecedent *ifT1_NT2_T3_29 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_29->joinWithAND(ifT1_NT2_29,Terbaca3);
  FuzzyRuleAntecedent *ifT1_NT2_T3_T4_29 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_T4_29->joinWithAND(ifT1_NT2_T3_29,Terbaca4);
  FuzzyRuleAntecedent *ifT1_NT2_T3_T4_T5_29 = new FuzzyRuleAntecedent();
  ifT1_NT2_T3_T4_T5_29->joinWithAND(ifT1_NT2_T3_T4_29,Terbaca5);
  FuzzyRuleConsequent *thenServoNope29 = new FuzzyRuleConsequent();
  thenServoNope29->addOutput(Nope);
  FuzzyRule *fuzzyRule29 = new FuzzyRule(29, ifT1_NT2_T3_T4_T5_29, thenServoNope29);

  //Fuzzy Rule 30
  FuzzyRuleAntecedent *ifT1_T2_30 = new FuzzyRuleAntecedent();
  ifT1_T2_30->joinWithAND(Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_NT3_30 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_30->joinWithAND(ifT1_T2_30,No_Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_NT3_T4_30 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_T4_30->joinWithAND(ifT1_T2_NT3_30,Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_NT3_T4_T5_30 = new FuzzyRuleAntecedent();
  ifT1_T2_NT3_T4_T5_30->joinWithAND(ifT1_T2_NT3_T4_30,Terbaca5);
  FuzzyRuleConsequent *thenServoNope30 = new FuzzyRuleConsequent();
  thenServoNope30->addOutput(Nope);
  FuzzyRule *fuzzyRule30 = new FuzzyRule(30, ifT1_T2_NT3_T4_T5_30, thenServoNope30);

  //Fuzzy Rule 31
  FuzzyRuleAntecedent *ifNT1_T2_31 = new FuzzyRuleAntecedent();
  ifNT1_T2_31->joinWithAND(No_Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifNT1_T2_T3_31 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_31->joinWithAND(ifNT1_T2_31,Terbaca3);
  FuzzyRuleAntecedent *ifNT1_T2_T3_T4_31 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_T4_31->joinWithAND(ifNT1_T2_T3_31,Terbaca4);
  FuzzyRuleAntecedent *ifNT1_T2_T3_T4_T5_31 = new FuzzyRuleAntecedent();
  ifNT1_T2_T3_T4_T5_31->joinWithAND(ifNT1_T2_T3_T4_31,Terbaca5);
  FuzzyRuleConsequent *thenServoNope31 = new FuzzyRuleConsequent();
  thenServoNope31->addOutput(Nope);
  FuzzyRule *fuzzyRule31 = new FuzzyRule(31, ifNT1_T2_T3_T4_T5_31, thenServoNope31);

  //Fuzzy Rule 32
  FuzzyRuleAntecedent *ifT1_T2_32 = new FuzzyRuleAntecedent();
  ifT1_T2_32->joinWithAND(Terbaca1,Terbaca2);
  FuzzyRuleAntecedent *ifT1_T2_T3_32 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_32->joinWithAND(ifT1_T2_32,Terbaca3);
  FuzzyRuleAntecedent *ifT1_T2_T3_T4_32 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_T4_32->joinWithAND(ifT1_T2_T3_32,Terbaca4);
  FuzzyRuleAntecedent *ifT1_T2_T3_T4_T5_32 = new FuzzyRuleAntecedent();
  ifT1_T2_T3_T4_T5_32->joinWithAND(ifT1_T2_T3_T4_32,Terbaca5);
  FuzzyRuleConsequent *thenServoNope32 = new FuzzyRuleConsequent();
  thenServoNope32->addOutput(Nope);
  FuzzyRule *fuzzyRule32 = new FuzzyRule(32, ifT1_T2_T3_T4_T5_32, thenServoNope32);


}

void loop() {
  // put your main code here, to run repeatedly:
fuzzy->setInput(1,flame1);
fuzzy->setInput(2,flame2);
fuzzy->setInput(3,flame3);
fuzzy->setInput(4,flame4);
fuzzy->setInput(5,flame5);

fuzzy->fuzzify();

int out = fuzzy->defuzzify(1);
Serial.print("out fuzzy = ");
Serial.println(out);
delay(10);
}