#include <Arduino.h>
#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();

int flame1=0;
int flame2=0;
int flame3=0;
int flame4=0;
int flame5=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Fuzzy Input 1
  FuzzyInput *flame1 = new FuzzyInput(1);
  FuzzySet *NT1 = new FuzzySet(0, 0, 1024, 3072);
  flame1->addFuzzySet(NT1);
  FuzzySet *T1 = new FuzzySet(1024, 3072, 4096, 4096);
  flame1->addFuzzySet(T1);
  fuzzy->addFuzzyInput(flame1);
  // Fuzzy Input 2
  FuzzyInput *flame2 = new FuzzyInput(2);
  FuzzySet *NT2 = new FuzzySet(0, 0, 1024, 3072);
  flame2->addFuzzySet(NT2);
  FuzzySet *T2 = new FuzzySet(1024, 3072, 4096, 4096);
  flame2->addFuzzySet(T2);
  fuzzy->addFuzzyInput(flame2);
  // Fuzzy Input 3
  FuzzyInput *flame3 = new FuzzyInput(3);
  FuzzySet *NT3 = new FuzzySet(0, 0, 1024, 3072);
  flame3->addFuzzySet(NT3);
  FuzzySet *T3 = new FuzzySet(1024, 3072, 4096, 4096);
  flame3->addFuzzySet(T3);
  fuzzy->addFuzzyInput(flame3);
  // Fuzzy Input 4
  FuzzyInput *flame4 = new FuzzyInput(4);
  FuzzySet *NT4 = new FuzzySet(0, 0, 1024, 3072);
  flame4->addFuzzySet(NT4);
  FuzzySet *T4 = new FuzzySet(1024, 3072, 4096, 4096);
  flame4->addFuzzySet(T4);
  fuzzy->addFuzzyInput(flame4);
  // Fuzzy Input 5
  FuzzyInput *flame5 = new FuzzyInput(5);
  FuzzySet *NT5 = new FuzzySet(0, 0, 1024, 3072);
  flame5->addFuzzySet(NT5);
  FuzzySet *T5 = new FuzzySet(1024, 3072, 4096, 4096);
  flame5->addFuzzySet(T5);
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

  //Fuzzy Rule 1
  FuzzyRuleAntecedent *NT1_NT2_1 = new FuzzyRuleAntecedent();
  NT1_NT2_1->joinWithAND(NT1, NT2);
  FuzzyRuleAntecedent *NT1_NT2_NT3_1 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_1->joinWithAND(NT1_NT2_1, NT3);
  FuzzyRuleAntecedent *NT1_NT2_NT3_NT4_1 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_NT4_1->joinWithAND(NT1_NT2_NT3_1, NT4);
  FuzzyRuleAntecedent *NT1_NT2_NT3_NT4_NT5_1 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_NT4_NT5_1->joinWithAND(NT1_NT2_NT3_NT4_1, NT5);
  FuzzyRuleConsequent *ServoNope_1 = new FuzzyRuleConsequent();
  ServoNope_1->addOutput(Nope);
  FuzzyRule *fuzzyRule1 = new FuzzyRule(1,NT1_NT2_NT3_NT4_NT5_1, ServoNope_1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  //Fuzzy Rule 2
  FuzzyRuleAntecedent *T1_NT2_2 = new FuzzyRuleAntecedent();
  T1_NT2_2->joinWithAND(T1, NT2);
  FuzzyRuleAntecedent *T1_NT2_NT3_2 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_2->joinWithAND(T1_NT2_2, NT3);
  FuzzyRuleAntecedent *T1_NT2_NT3_NT4_2 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_NT4_2->joinWithAND(T1_NT2_NT3_2, NT4);
  FuzzyRuleAntecedent *T1_NT2_NT3_NT4_NT5_2 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_NT4_NT5_2->joinWithAND(T1_NT2_NT3_NT4_2, NT5);
  FuzzyRuleConsequent *ServoMin_2 = new FuzzyRuleConsequent();
  ServoMin_2->addOutput(Min);
  FuzzyRule *fuzzyRule2 = new FuzzyRule(2,T1_NT2_NT3_NT4_NT5_2, ServoMin_2);
  fuzzy->addFuzzyRule(fuzzyRule2);

  //Fuzzy Rule 3
  FuzzyRuleAntecedent *T1_T2_3 = new FuzzyRuleAntecedent();
  T1_T2_3->joinWithAND(T1, T2);
  FuzzyRuleAntecedent *T1_T2_NT3_3 = new FuzzyRuleAntecedent();
  T1_T2_NT3_3->joinWithAND(T1_T2_3, NT3);
  FuzzyRuleAntecedent *T1_T2_NT3_NT4_3 = new FuzzyRuleAntecedent();
  T1_T2_NT3_NT4_3->joinWithAND(T1_T2_NT3_3,NT4);
  FuzzyRuleAntecedent *T1_T2_NT3_NT4_NT5_3 = new FuzzyRuleAntecedent();
  T1_T2_NT3_NT4_NT5_3->joinWithAND(T1_T2_NT3_NT4_3, NT5);
  FuzzyRuleConsequent *ServoMin_3 = new FuzzyRuleConsequent();
  ServoMin_3->addOutput(Min);
  FuzzyRule *fuzzyRule3 = new FuzzyRule(3,T1_T2_NT3_NT4_NT5_3, ServoMin_3);
  fuzzy->addFuzzyRule(fuzzyRule3);

  //Fuzzy Rule 4
  FuzzyRuleAntecedent *T1_NT2_4 = new FuzzyRuleAntecedent();
  T1_NT2_4->joinWithAND(T1,NT2);
  FuzzyRuleAntecedent *T1_NT2_T3_4 = new FuzzyRuleAntecedent();
  T1_NT2_T3_4->joinWithAND(T1_NT2_4,T3);
  FuzzyRuleAntecedent *T1_NT2_T3_NT4_4 = new FuzzyRuleAntecedent();
  T1_NT2_T3_NT4_4->joinWithAND(T1_NT2_T3_4,NT4);
  FuzzyRuleAntecedent *T1_NT2_T3_NT4_NT5_4 = new FuzzyRuleAntecedent();
  T1_NT2_T3_NT4_NT5_4->joinWithAND(T1_NT2_T3_NT4_4, NT5);
  FuzzyRuleConsequent *ServoNope_4 = new FuzzyRuleConsequent();
  ServoNope_4->addOutput(Nope);
  FuzzyRule *fuzzyRule4 = new FuzzyRule(4,T1_NT2_T3_NT4_NT5_4, ServoNope_4);
  fuzzy->addFuzzyRule(fuzzyRule4);

  //Fuzzy Rule 5
  FuzzyRuleAntecedent *T1_NT2_5 = new FuzzyRuleAntecedent();
  T1_NT2_5->joinWithAND(T1,NT2);
  FuzzyRuleAntecedent *T1_NT2_NT3_5 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_5->joinWithAND(T1_NT2_5,NT3);
  FuzzyRuleAntecedent *T1_NT2_NT3_T4_5 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_T4_5->joinWithAND(T1_NT2_NT3_5,T4);
  FuzzyRuleAntecedent *T1_NT2_NT3_T4_NT5_5 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_T4_NT5_5->joinWithAND(T1_NT2_NT3_T4_5, NT5);
  FuzzyRuleConsequent *ServoNope_5 = new FuzzyRuleConsequent();
  ServoNope_5->addOutput(Nope);
  FuzzyRule *fuzzyRule5 = new FuzzyRule(5,T1_NT2_NT3_T4_NT5_5, ServoNope_5);
  fuzzy->addFuzzyRule(fuzzyRule5);

  //Fuzzy Rule 6
  FuzzyRuleAntecedent *T1_NT2_6 = new FuzzyRuleAntecedent();
  T1_NT2_6->joinWithAND(T1,NT2);
  FuzzyRuleAntecedent *T1_NT2_NT3_6 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_6->joinWithAND(T1_NT2_6,NT3);
  FuzzyRuleAntecedent *T1_NT2_NT3_NT4_6 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_NT4_6->joinWithAND(T1_NT2_NT3_6,NT4);
  FuzzyRuleAntecedent *T1_NT2_NT3_NT4_T5_6 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_NT4_T5_6->joinWithAND(T1_NT2_NT3_NT4_6,T5);
  FuzzyRuleConsequent *ServoNope_6 = new FuzzyRuleConsequent();
  ServoNope_6->addOutput(Nope);
  FuzzyRule *fuzzyRule6 = new FuzzyRule(6,T1_NT2_NT3_NT4_T5_6, ServoNope_6);
  fuzzy->addFuzzyRule(fuzzyRule6);

  //Fuzzy Rule 7
  FuzzyRuleAntecedent *NT1_T2_7 = new FuzzyRuleAntecedent();
  NT1_T2_7->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_NT3_7 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_7->joinWithAND(NT1_T2_7,NT3);
  FuzzyRuleAntecedent *NT1_T2_NT3_NT4_7 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_NT4_7->joinWithAND(NT1_T2_NT3_7,NT4);
  FuzzyRuleAntecedent *NT1_T2_NT3_NT4_NT5_7 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_NT4_NT5_7->joinWithAND(NT1_T2_NT3_NT4_7,NT5);
  FuzzyRuleConsequent *ServoMin_7 = new FuzzyRuleConsequent();
  ServoMin_7->addOutput(Min);
  FuzzyRule *fuzzyRule7 = new FuzzyRule(7,NT1_T2_NT3_NT4_NT5_7, ServoMin_7);
  fuzzy->addFuzzyRule(fuzzyRule7);

  //Fuzzy Rule 8
  FuzzyRuleAntecedent *NT1_T2_8 = new FuzzyRuleAntecedent();
  NT1_T2_8->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_T3_8 = new FuzzyRuleAntecedent();
  NT1_T2_T3_8->joinWithAND(NT1_T2_8,T3);
  FuzzyRuleAntecedent *NT1_T2_T3_NT4_8 = new FuzzyRuleAntecedent();
  NT1_T2_T3_NT4_8->joinWithAND(NT1_T2_T3_8,NT4);
  FuzzyRuleAntecedent *NT1_T2_T3_NT4_NT5_8 = new FuzzyRuleAntecedent();
  NT1_T2_T3_NT4_NT5_8->joinWithAND(NT1_T2_T3_NT4_8,NT5);
  FuzzyRuleConsequent *ServoCenter_8 = new FuzzyRuleConsequent();
  ServoCenter_8->addOutput(Center);
  FuzzyRule *fuzzyRule8 = new FuzzyRule(8,NT1_T2_T3_NT4_NT5_8, ServoCenter_8);
  fuzzy->addFuzzyRule(fuzzyRule8);

  //Fuzzy Rule 9
  FuzzyRuleAntecedent *NT1_T2_9 = new FuzzyRuleAntecedent();
  NT1_T2_9->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_NT3_9 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_9->joinWithAND(NT1_T2_9,NT3);
  FuzzyRuleAntecedent *NT1_T2_NT3_T4_9 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_T4_9->joinWithAND(NT1_T2_NT3_9,T4);
  FuzzyRuleAntecedent *NT1_T2_NT3_T4_NT5_9 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_T4_NT5_9->joinWithAND(NT1_T2_NT3_T4_9,NT5);
  FuzzyRuleConsequent *ServoNope_9 = new FuzzyRuleConsequent();
  ServoNope_9->addOutput(Nope);
  FuzzyRule *fuzzyRule9 = new FuzzyRule(9,NT1_T2_NT3_T4_NT5_9, ServoNope_9);
  fuzzy->addFuzzyRule(fuzzyRule9);

  //Fuzzy Rule 10
  FuzzyRuleAntecedent *NT1_T2_10 = new FuzzyRuleAntecedent();
  NT1_T2_10->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_NT3_10 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_10->joinWithAND(NT1_T2_10,NT3);
  FuzzyRuleAntecedent *NT1_T2_NT3_NT4_10 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_NT4_10->joinWithAND(NT1_T2_NT3_10,NT4);
  FuzzyRuleAntecedent *NT1_T2_NT3_NT4_T5_10 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_NT4_T5_10->joinWithAND(NT1_T2_NT3_NT4_10,T5);
  FuzzyRuleConsequent *ServoNope_10 = new FuzzyRuleConsequent();
  ServoNope_10->addOutput(Nope);
  FuzzyRule *fuzzyRule10 = new FuzzyRule(10,NT1_T2_NT3_NT4_T5_10, ServoNope_10);
  fuzzy->addFuzzyRule(fuzzyRule10);

  //Fuzzy Rule 11
  FuzzyRuleAntecedent *NT1_NT2_11 = new FuzzyRuleAntecedent();
  NT1_NT2_11->joinWithAND(NT1,NT2);
  FuzzyRuleAntecedent *NT1_NT2_T3_11 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_11->joinWithAND(NT1_NT2_11,T3);
  FuzzyRuleAntecedent *NT1_NT2_T3_NT4_11 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_NT4_11->joinWithAND(NT1_NT2_T3_11,NT4);
  FuzzyRuleAntecedent *NT1_NT2_T3_NT4_NT5_11 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_NT4_NT5_11->joinWithAND(NT1_NT2_T3_NT4_11,NT5);
  FuzzyRuleConsequent *ServoCenter_11 = new FuzzyRuleConsequent();
  ServoCenter_11->addOutput(Center);
  FuzzyRule *fuzzyRule11 = new FuzzyRule(11,NT1_NT2_T3_NT4_NT5_11, ServoCenter_11);
  fuzzy->addFuzzyRule(fuzzyRule11);

  //Fuzzy Rule 12
  FuzzyRuleAntecedent *NT1_NT2_12 = new FuzzyRuleAntecedent();
  NT1_NT2_12->joinWithAND(NT1,NT2);
  FuzzyRuleAntecedent *NT1_NT2_T3_12 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_12->joinWithAND(NT1_NT2_12,T3);
  FuzzyRuleAntecedent *NT1_NT2_T3_T4_12 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_T4_12->joinWithAND(NT1_NT2_T3_12,T4);
  FuzzyRuleAntecedent *NT1_NT2_T3_T4_NT5_12 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_T4_NT5_12->joinWithAND(NT1_NT2_T3_T4_12,NT5);
  FuzzyRuleConsequent *ServoCenter_12 = new FuzzyRuleConsequent();
  ServoCenter_12->addOutput(Center);
  FuzzyRule *fuzzyRule12 = new FuzzyRule(12,NT1_NT2_T3_T4_NT5_12, ServoCenter_12);
  fuzzy->addFuzzyRule(fuzzyRule12);

  //Fuzzy Rule 13
  FuzzyRuleAntecedent *NT1_NT2_13 = new FuzzyRuleAntecedent();
  NT1_NT2_13->joinWithAND(NT1,NT2);
  FuzzyRuleAntecedent *NT1_NT2_T3_13 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_13->joinWithAND(NT1_NT2_13,T3);
  FuzzyRuleAntecedent *NT1_NT2_T3_NT4_13 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_NT4_13->joinWithAND(NT1_NT2_T3_13,NT4);
  FuzzyRuleAntecedent *NT1_NT2_T3_NT4_T5_13 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_NT4_T5_13->joinWithAND(NT1_NT2_T3_NT4_13,T5);
  FuzzyRuleConsequent *ServoNope_13 = new FuzzyRuleConsequent();
  ServoNope_13->addOutput(Nope);
  FuzzyRule *fuzzyRule13 = new FuzzyRule(13,NT1_NT2_T3_NT4_T5_13, ServoNope_13);
  fuzzy->addFuzzyRule(fuzzyRule13);

  //Fuzzy Rule 14
  FuzzyRuleAntecedent *NT1_NT2_14 = new FuzzyRuleAntecedent();
  NT1_NT2_14->joinWithAND(NT1,NT2);
  FuzzyRuleAntecedent *NT1_NT2_NT3_14 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_14->joinWithAND(NT1_NT2_14,NT3);
  FuzzyRuleAntecedent *NT1_NT2_NT3_T4_14 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_T4_14->joinWithAND(NT1_NT2_NT3_14,T4);
  FuzzyRuleAntecedent *NT1_NT2_NT3_T4_NT5_14 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_T4_NT5_14->joinWithAND(NT1_NT2_NT3_T4_14,NT5);
  FuzzyRuleConsequent *ServoMax_14 = new FuzzyRuleConsequent();
  ServoMax_14->addOutput(Max);
  FuzzyRule *fuzzyRule14 = new FuzzyRule(14,NT1_NT2_NT3_T4_NT5_14, ServoMax_14);
  fuzzy->addFuzzyRule(fuzzyRule14);

  //Fuzzy Rule 15
  FuzzyRuleAntecedent *NT1_NT2_15 = new FuzzyRuleAntecedent();
  NT1_NT2_15->joinWithAND(NT1,NT2);
  FuzzyRuleAntecedent *NT1_NT2_NT3_15 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_15->joinWithAND(NT1_NT2_15,NT3);
  FuzzyRuleAntecedent *NT1_NT2_NT3_T4_15 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_T4_15->joinWithAND(NT1_NT2_NT3_15,T4);
  FuzzyRuleAntecedent *NT1_NT2_NT3_T4_T5_15 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_T4_T5_15->joinWithAND(NT1_NT2_NT3_T4_15,T5);
  FuzzyRuleConsequent *ServoMax_15 = new FuzzyRuleConsequent();
  ServoMax_15->addOutput(Max);
  FuzzyRule *fuzzyRule15 = new FuzzyRule(15,NT1_NT2_NT3_T4_T5_15, ServoMax_15);
  fuzzy->addFuzzyRule(fuzzyRule15);

  //Fuzzy Rule 16
  FuzzyRuleAntecedent *NT1_NT2_16 = new FuzzyRuleAntecedent();
  NT1_NT2_16->joinWithAND(NT1,NT2);
  FuzzyRuleAntecedent *NT1_NT2_NT3_16 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_16->joinWithAND(NT1_NT2_16,NT3);
  FuzzyRuleAntecedent *NT1_NT2_NT3_NT4_16 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_NT4_16->joinWithAND(NT1_NT2_NT3_16,NT4);
  FuzzyRuleAntecedent *NT1_NT2_NT3_NT4_T5_16 = new FuzzyRuleAntecedent();
  NT1_NT2_NT3_NT4_T5_16->joinWithAND(NT1_NT2_NT3_NT4_16,T5);
  FuzzyRuleConsequent *ServoMax_16 = new FuzzyRuleConsequent();
  ServoMax_16->addOutput(Max);
  FuzzyRule *fuzzyRule16 = new FuzzyRule(16,NT1_NT2_NT3_NT4_T5_16, ServoMax_16);
  fuzzy->addFuzzyRule(fuzzyRule16);

  //Fuzzy Rule 17
  FuzzyRuleAntecedent *T1_T2_17 = new FuzzyRuleAntecedent();
  T1_T2_17->joinWithAND(T1,T2);
  FuzzyRuleAntecedent *T1_T2_T3_17 = new FuzzyRuleAntecedent();
  T1_T2_T3_17->joinWithAND(T1_T2_17,T3);
  FuzzyRuleAntecedent *T1_T2_T3_NT4_17 = new FuzzyRuleAntecedent();
  T1_T2_T3_NT4_17->joinWithAND(T1_T2_T3_17,NT4);
  FuzzyRuleAntecedent *T1_T2_T3_NT4_NT5_17 = new FuzzyRuleAntecedent();
  T1_T2_T3_NT4_NT5_17->joinWithAND(T1_T2_T3_NT4_17,NT5);
  FuzzyRuleConsequent *ServoNope_17 = new FuzzyRuleConsequent();
  ServoNope_17->addOutput(Nope);
  FuzzyRule *fuzzyRule17 = new FuzzyRule(17,T1_T2_T3_NT4_NT5_17, ServoNope_17);
  fuzzy->addFuzzyRule(fuzzyRule17);

  //Fuzzy Rule 18
  FuzzyRuleAntecedent *T1_T2_18 = new FuzzyRuleAntecedent();
  T1_T2_18->joinWithAND(T1,T2);
  FuzzyRuleAntecedent *T1_T2_NT3_18 = new FuzzyRuleAntecedent();
  T1_T2_NT3_18->joinWithAND(T1_T2_18,NT3);
  FuzzyRuleAntecedent *T1_T2_NT3_T4_18 = new FuzzyRuleAntecedent();
  T1_T2_NT3_T4_18->joinWithAND(T1_T2_NT3_18,T4);
  FuzzyRuleAntecedent *T1_T2_NT3_T4_NT5_18 = new FuzzyRuleAntecedent();
  T1_T2_NT3_T4_NT5_18->joinWithAND(T1_T2_NT3_T4_18,NT5);
  FuzzyRuleConsequent *ServoNope_18 = new FuzzyRuleConsequent();
  ServoNope_18->addOutput(Nope);
  FuzzyRule *fuzzyRule18 = new FuzzyRule(18,T1_T2_NT3_T4_NT5_18, ServoNope_18);
  fuzzy->addFuzzyRule(fuzzyRule18);

  //Fuzzy Rule 19
  FuzzyRuleAntecedent *T1_T2_19 = new FuzzyRuleAntecedent();
  T1_T2_19->joinWithAND(T1,T2);
  FuzzyRuleAntecedent *T1_T2_NT3_19 = new FuzzyRuleAntecedent();
  T1_T2_NT3_19->joinWithAND(T1_T2_19,NT3);
  FuzzyRuleAntecedent *T1_T2_NT3_NT4_19 = new FuzzyRuleAntecedent();
  T1_T2_NT3_NT4_19->joinWithAND(T1_T2_NT3_19,NT4);
  FuzzyRuleAntecedent *T1_T2_NT3_NT4_T5_19 = new FuzzyRuleAntecedent();
  T1_T2_NT3_NT4_T5_19->joinWithAND(T1_T2_NT3_NT4_19,T5);
  FuzzyRuleConsequent *ServoNope_19 = new FuzzyRuleConsequent();
  ServoNope_19->addOutput(Nope);
  FuzzyRule *fuzzyRule19 = new FuzzyRule(19,T1_T2_NT3_NT4_T5_19, ServoNope_19);
  fuzzy->addFuzzyRule(fuzzyRule19);

  //Fuzzy Rule 20
  FuzzyRuleAntecedent *T1_NT2_20 = new FuzzyRuleAntecedent();
  T1_NT2_20->joinWithAND(T1,NT2);
  FuzzyRuleAntecedent *T1_NT2_T3_20 = new FuzzyRuleAntecedent();
  T1_NT2_T3_20->joinWithAND(T1_NT2_20,T3);
  FuzzyRuleAntecedent *T1_NT2_T3_T4_20 = new FuzzyRuleAntecedent();
  T1_NT2_T3_T4_20->joinWithAND(T1_NT2_T3_20,T4);
  FuzzyRuleAntecedent *T1_NT2_T3_T4_NT5_20 = new FuzzyRuleAntecedent();
  T1_NT2_T3_T4_NT5_20->joinWithAND(T1_NT2_T3_T4_20,NT5);
  FuzzyRuleConsequent *ServoNope_20 = new FuzzyRuleConsequent();
  ServoNope_20->addOutput(Nope);
  FuzzyRule *fuzzyRule20 = new FuzzyRule(20,T1_NT2_T3_T4_NT5_20, ServoNope_20);
  fuzzy->addFuzzyRule(fuzzyRule20);

  //Fuzzy Rule 21
  FuzzyRuleAntecedent *T1_NT2_21 = new FuzzyRuleAntecedent();
  T1_NT2_21->joinWithAND(T1,NT2);
  FuzzyRuleAntecedent *T1_NT2_T3_21 = new FuzzyRuleAntecedent();
  T1_NT2_T3_21->joinWithAND(T1_NT2_21,T3);
  FuzzyRuleAntecedent *T1_NT2_T3_NT4_21 = new FuzzyRuleAntecedent();
  T1_NT2_T3_NT4_21->joinWithAND(T1_NT2_T3_21,NT4);
  FuzzyRuleAntecedent *T1_NT2_T3_NT4_T5_21 = new FuzzyRuleAntecedent();
  T1_NT2_T3_NT4_T5_21->joinWithAND(T1_NT2_T3_NT4_21,T5);
  FuzzyRuleConsequent *ServoNope_21 = new FuzzyRuleConsequent();
  ServoNope_21->addOutput(Nope);
  FuzzyRule *fuzzyRule21 = new FuzzyRule(21,T1_NT2_T3_NT4_T5_21, ServoNope_21);
  fuzzy->addFuzzyRule(fuzzyRule21);

  //Fuzzy Rule 22
  FuzzyRuleAntecedent *T1_NT2_22 = new FuzzyRuleAntecedent();
  T1_NT2_22->joinWithAND(T1,NT2);
  FuzzyRuleAntecedent *T1_NT2_NT3_22 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_22->joinWithAND(T1_NT2_22,NT3);
  FuzzyRuleAntecedent *T1_NT2_NT3_T4_22 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_T4_22->joinWithAND(T1_NT2_NT3_22,T4);
  FuzzyRuleAntecedent *T1_NT2_NT3_T4_T5_22 = new FuzzyRuleAntecedent();
  T1_NT2_NT3_T4_T5_22->joinWithAND(T1_NT2_NT3_T4_22,T5);
  FuzzyRuleConsequent *ServoNope_22 = new FuzzyRuleConsequent();
  ServoNope_22->addOutput(Nope);
  FuzzyRule *fuzzyRule22 = new FuzzyRule(22,T1_NT2_NT3_T4_T5_22, ServoNope_22);
  fuzzy->addFuzzyRule(fuzzyRule22);

  //Fuzzy Rule 23
  FuzzyRuleAntecedent *NT1_T2_23 = new FuzzyRuleAntecedent();
  NT1_T2_23->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_T3_23 = new FuzzyRuleAntecedent();
  NT1_T2_T3_23->joinWithAND(NT1_T2_23,T3);
  FuzzyRuleAntecedent *NT1_T2_T3_T4_23 = new FuzzyRuleAntecedent();
  NT1_T2_T3_T4_23->joinWithAND(NT1_T2_T3_23,T4);
  FuzzyRuleAntecedent *NT1_T2_T3_T4_NT5_23 = new FuzzyRuleAntecedent();
  NT1_T2_T3_T4_NT5_23->joinWithAND(NT1_T2_T3_T4_23,NT5);
  FuzzyRuleConsequent *ServoCenter_23 = new FuzzyRuleConsequent();
  ServoCenter_23->addOutput(Center);
  FuzzyRule *fuzzyRule23 = new FuzzyRule(23,NT1_T2_T3_T4_NT5_23, ServoCenter_23);
  fuzzy->addFuzzyRule(fuzzyRule23);

  //Fuzzy Rule 24
  FuzzyRuleAntecedent *NT1_T2_24 = new FuzzyRuleAntecedent();
  NT1_T2_24->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_T3_24 = new FuzzyRuleAntecedent();
  NT1_T2_T3_24->joinWithAND(NT1_T2_24,T3);
  FuzzyRuleAntecedent *NT1_T2_T3_NT4_24 = new FuzzyRuleAntecedent();
  NT1_T2_T3_NT4_24->joinWithAND(NT1_T2_T3_24,NT4);
  FuzzyRuleAntecedent *NT1_T2_T3_NT4_T5_24 = new FuzzyRuleAntecedent();
  NT1_T2_T3_NT4_T5_24->joinWithAND(NT1_T2_T3_NT4_24,T5);
  FuzzyRuleConsequent *ServoNope_24 = new FuzzyRuleConsequent();
  ServoNope_24->addOutput(Nope);
  FuzzyRule *fuzzyRule24 = new FuzzyRule(24,NT1_T2_T3_NT4_T5_24, ServoNope_24);
  fuzzy->addFuzzyRule(fuzzyRule24);

  //Fuzzy Rule 25
  FuzzyRuleAntecedent *NT1_T2_25 = new FuzzyRuleAntecedent();
  NT1_T2_25->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_NT3_25 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_25->joinWithAND(NT1_T2_25,NT3);
  FuzzyRuleAntecedent *NT1_T2_NT3_T4_25 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_T4_25->joinWithAND(NT1_T2_NT3_25,T4);
  FuzzyRuleAntecedent *NT1_T2_NT3_T4_T5_25 = new FuzzyRuleAntecedent();
  NT1_T2_NT3_T4_T5_25->joinWithAND(NT1_T2_NT3_T4_25,T5);
  FuzzyRuleConsequent *ServoNope_25 = new FuzzyRuleConsequent();
  ServoNope_25->addOutput(Nope);
  FuzzyRule *fuzzyRule25 = new FuzzyRule(25,NT1_T2_NT3_T4_T5_25, ServoNope_25);
  fuzzy->addFuzzyRule(fuzzyRule25);

  //Fuzzy Rule 26
  FuzzyRuleAntecedent *NT1_NT2_26 = new FuzzyRuleAntecedent();
  NT1_NT2_26->joinWithAND(NT1,NT2);
  FuzzyRuleAntecedent *NT1_NT2_T3_26 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_26->joinWithAND(NT1_NT2_26,T3);
  FuzzyRuleAntecedent *NT1_NT2_T3_T4_26 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_T4_26->joinWithAND(NT1_NT2_T3_26,T4);
  FuzzyRuleAntecedent *NT1_NT2_T3_T4_T5_26 = new FuzzyRuleAntecedent();
  NT1_NT2_T3_T4_T5_26->joinWithAND(NT1_NT2_T3_T4_26,T5);
  FuzzyRuleConsequent *ServoNope_26 = new FuzzyRuleConsequent();
  ServoNope_26->addOutput(Nope);
  FuzzyRule *fuzzyRule26 = new FuzzyRule(26,NT1_NT2_T3_T4_T5_26, ServoNope_26);
  fuzzy->addFuzzyRule(fuzzyRule26);

  //Fuzzy Rule 27
  FuzzyRuleAntecedent *T1_T2_27 = new FuzzyRuleAntecedent();
  T1_T2_27->joinWithAND(T1,T2);
  FuzzyRuleAntecedent *T1_T2_T3_27 = new FuzzyRuleAntecedent();
  T1_T2_T3_27->joinWithAND(T1_T2_27,T3);
  FuzzyRuleAntecedent *T1_T2_T3_T4_27 = new FuzzyRuleAntecedent();
  T1_T2_T3_T4_27->joinWithAND(T1_T2_T3_27,T4);
  FuzzyRuleAntecedent *T1_T2_T3_T4_NT5_27 = new FuzzyRuleAntecedent();
  T1_T2_T3_T4_NT5_27->joinWithAND(T1_T2_T3_T4_27,NT5);
  FuzzyRuleConsequent *ServoNope_27 = new FuzzyRuleConsequent();
  ServoNope_27->addOutput(Nope);
  FuzzyRule *fuzzyRule27 = new FuzzyRule(27,T1_T2_T3_T4_NT5_27, ServoNope_27);
  fuzzy->addFuzzyRule(fuzzyRule27);

  //Fuzzy Rule 28
  FuzzyRuleAntecedent *T1_T2_28 = new FuzzyRuleAntecedent();
  T1_T2_28->joinWithAND(T1,T2);
  FuzzyRuleAntecedent *T1_T2_T3_28 = new FuzzyRuleAntecedent();
  T1_T2_T3_28->joinWithAND(T1_T2_28,T3);
  FuzzyRuleAntecedent *T1_T2_T3_NT4_28 = new FuzzyRuleAntecedent();
  T1_T2_T3_NT4_28->joinWithAND(T1_T2_T3_28,NT4);
  FuzzyRuleAntecedent *T1_T2_T3_NT4_T5_28 = new FuzzyRuleAntecedent();
  T1_T2_T3_NT4_T5_28->joinWithAND(T1_T2_T3_NT4_28,NT5);
  FuzzyRuleConsequent *ServoNope_28 = new FuzzyRuleConsequent();
  ServoNope_28->addOutput(Nope);
  FuzzyRule *fuzzyRule28 = new FuzzyRule(28,T1_T2_T3_NT4_T5_28, ServoNope_28);
  fuzzy->addFuzzyRule(fuzzyRule28);

  //Fuzzy Rule 29
  FuzzyRuleAntecedent *T1_NT2_29 = new FuzzyRuleAntecedent();
  T1_NT2_29->joinWithAND(T1,NT2);
  FuzzyRuleAntecedent *T1_NT2_T3_29 = new FuzzyRuleAntecedent();
  T1_NT2_T3_29->joinWithAND(T1_NT2_29,T3);
  FuzzyRuleAntecedent *T1_NT2_T3_T4_29 = new FuzzyRuleAntecedent();
  T1_NT2_T3_T4_29->joinWithAND(T1_NT2_T3_29,T4);
  FuzzyRuleAntecedent *T1_NT2_T3_T4_T5_29 = new FuzzyRuleAntecedent();
  T1_NT2_T3_T4_T5_29->joinWithAND(T1_NT2_T3_T4_29,T5);
  FuzzyRuleConsequent *ServoNope_29 = new FuzzyRuleConsequent();
  ServoNope_29->addOutput(Nope);
  FuzzyRule *fuzzyRule29 = new FuzzyRule(29,T1_NT2_T3_T4_T5_29, ServoNope_29);
  fuzzy->addFuzzyRule(fuzzyRule29);

  //Fuzzy Rule 30
  FuzzyRuleAntecedent *T1_T2_30 = new FuzzyRuleAntecedent();
  T1_T2_30->joinWithAND(T1,T2);
  FuzzyRuleAntecedent *T1_T2_NT3_30 = new FuzzyRuleAntecedent();
  T1_T2_NT3_30->joinWithAND(T1_T2_30,NT3);
  FuzzyRuleAntecedent *T1_T2_NT3_T4_30 = new FuzzyRuleAntecedent();
  T1_T2_NT3_T4_30->joinWithAND(T1_T2_NT3_30,T4);
  FuzzyRuleAntecedent *T1_T2_NT3_T4_T5_30 = new FuzzyRuleAntecedent();
  T1_T2_NT3_T4_T5_30->joinWithAND(T1_T2_NT3_T4_30,T5);
  FuzzyRuleConsequent *ServoNope_30 = new FuzzyRuleConsequent();
  ServoNope_30->addOutput(Nope);
  FuzzyRule *fuzzyRule30 = new FuzzyRule(30,T1_T2_NT3_T4_T5_30, ServoNope_30);
  fuzzy->addFuzzyRule(fuzzyRule30);

  //Fuzzy Rule 31
  FuzzyRuleAntecedent *NT1_T2_31 = new FuzzyRuleAntecedent();
  NT1_T2_31->joinWithAND(NT1,T2);
  FuzzyRuleAntecedent *NT1_T2_T3_31 = new FuzzyRuleAntecedent();
  NT1_T2_T3_31->joinWithAND(NT1_T2_31,T3);
  FuzzyRuleAntecedent *NT1_T2_T3_T4_31 = new FuzzyRuleAntecedent();
  NT1_T2_T3_T4_31->joinWithAND(NT1_T2_T3_31,T4);
  FuzzyRuleAntecedent *NT1_T2_T3_T4_T5_31 = new FuzzyRuleAntecedent();
  NT1_T2_T3_T4_T5_31->joinWithAND(NT1_T2_T3_T4_31,T5);
  FuzzyRuleConsequent *ServoNope_31 = new FuzzyRuleConsequent();
  ServoNope_31->addOutput(Nope);
  FuzzyRule *fuzzyRule31 = new FuzzyRule(31,NT1_T2_T3_T4_T5_31, ServoNope_31);
  fuzzy->addFuzzyRule(fuzzyRule31);

  //Fuzzy Rule 32
  FuzzyRuleAntecedent *T1_T2_32 = new FuzzyRuleAntecedent();
  T1_T2_32->joinWithAND(T1,T2);
  FuzzyRuleAntecedent *T1_T2_T3_32 = new FuzzyRuleAntecedent();
  T1_T2_T3_32->joinWithAND(T1_T2_32,T3);
  FuzzyRuleAntecedent *T1_T2_T3_T4_32 = new FuzzyRuleAntecedent();
  T1_T2_T3_T4_32->joinWithAND(T1_T2_T3_32,T4);
  FuzzyRuleAntecedent *T1_T2_T3_T4_T5_32 = new FuzzyRuleAntecedent();
  T1_T2_T3_T4_T5_32->joinWithAND(T1_T2_T3_T4_32,T5);
  FuzzyRuleConsequent *ServoNope_32 = new FuzzyRuleConsequent();
  ServoNope_32->addOutput(Nope);
  FuzzyRule *fuzzyRule32 = new FuzzyRule(32,T1_T2_T3_T4_T5_32, ServoNope_32);
  fuzzy->addFuzzyRule(fuzzyRule32);



}

void loop(){
fuzzy->setInput(1,flame1);
fuzzy->setInput(2,flame2);
fuzzy->setInput(3,flame3);
fuzzy->setInput(4,flame4);
fuzzy->setInput(5,flame5);

fuzzy->fuzzify();

int out = fuzzy->defuzzify(1);
Serial.print("out fuzzy = ");
Serial.println(out);
}