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
  



}

void loop(){
fuzzy->setInput(1,flame1);
fuzzy->setInput(2,flame2);

fuzzy->fuzzify();

int out = fuzzy->defuzzify(1);
Serial.print("out fuzzy = ");
Serial.println(out);
}