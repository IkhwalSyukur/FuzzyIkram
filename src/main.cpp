#include <Arduino.h>
#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();

int flame1=0;
int flame2=4000;
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
  FuzzySet *N4 = new FuzzySet(0, 0, 1024, 3072);
  flame4->addFuzzySet(N4);
  FuzzySet *T4 = new FuzzySet(1024, 3072, 4096, 4096);
  flame4->addFuzzySet(T4);
  fuzzy->addFuzzyInput(flame4);
  // Fuzzy Input 5
  FuzzyInput *flame5 = new FuzzyInput(5);
  FuzzySet *N5 = new FuzzySet(0, 0, 1024, 3072);
  flame5->addFuzzySet(N5);
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
  FuzzyRuleConsequent *thenServoNope_1 = new FuzzyRuleConsequent();
  thenServoNope_1->addOutput(Nope);
  FuzzyRule *fuzzyRule1 = new FuzzyRule(1,  NT1_NT2_1, thenServoNope_1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  //Fuzzy Rule 2
  FuzzyRuleAntecedent *T1_NT2_2 = new FuzzyRuleAntecedent();
  T1_NT2_2->joinWithAND(T1, NT2);
  FuzzyRuleConsequent *thenServoMin_2 = new FuzzyRuleConsequent();
  thenServoMin_2->addOutput(Min);
  FuzzyRule *fuzzyRule2 = new FuzzyRule(2,  T1_NT2_2, thenServoMin_2);
  fuzzy->addFuzzyRule(fuzzyRule2);

  //Fuzzy Rule 3
  FuzzyRuleAntecedent *NT1_T2_3 = new FuzzyRuleAntecedent();
  NT1_T2_3->joinWithAND(NT1, T2);
  FuzzyRuleConsequent *thenServoMax_3 = new FuzzyRuleConsequent();
  thenServoMax_3->addOutput(Max);
  FuzzyRule *fuzzyRule3 = new FuzzyRule(3,  NT1_T2_3, thenServoMax_3);
  fuzzy->addFuzzyRule(fuzzyRule3);

  //Fuzzy Rule 4
  FuzzyRuleAntecedent *T1_T2_4 = new FuzzyRuleAntecedent();
  T1_T2_4->joinWithAND(T1, T2);
  FuzzyRuleConsequent *thenServoNope_4 = new FuzzyRuleConsequent();
  thenServoNope_4->addOutput(Nope);
  FuzzyRule *fuzzyRule4 = new FuzzyRule(4,  T1_T2_4, thenServoNope_4);
  fuzzy->addFuzzyRule(fuzzyRule4);

}

void loop(){
fuzzy->setInput(1,flame1);
fuzzy->setInput(2,flame2);

fuzzy->fuzzify();

int out = fuzzy->defuzzify(1);
Serial.print("out fuzzy = ");
Serial.println(out);
}