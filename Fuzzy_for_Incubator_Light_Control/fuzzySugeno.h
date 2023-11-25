#include "fuzzyMP.h"

class fuzzy {

public:
  float error, deltaError;
  float pwmOuput;
  fuzzy(float error, float deltaError) {
    this->error = error;
    this->deltaError = deltaError;
    this->pwmOuput = fuzzyProcess();
  };

  void testing() // FOR PRINTING ALL VALUES IN CPP PROGRAM (DEBUG)
  {
      for (int i = 0; i < 3; i++)
      {
          for (int j = 0; j < 5; j++)
          {
              std::cout << float(valueRule[i][j]) << "\t |";
          }
          std::cout << std::endl;
      }
      std::cout << deltaError << " " << error<<std::endl;
      std::cout << std::endl << "ERROR :\n";
      for (int i = 0; i < 5; i++)
      {
          std::cout << valueError[i] << std::endl;
      }
      std::cout << "---------------" << std::endl;
      std::cout << std::endl << "Delta Error  :\n";
      for(int i=0; i<3;i++){
          std::cout << valueDeltaError[i] << std::endl;
      }
  }

  void testingOnDevice() { //FOR PRINTTING ALL VALUE IN DECICE(.ino) PROGRAM
    Serial.println("<<<<<<<<>>>>>>>>>>");
    Serial.println("Value From Fuzzy Lib");
    Serial.println("---------------");
    Serial.println("Value Rule :");
    Serial.println(" ");
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 5; j++) {
        Serial.print(float(valueRule[i][j]));
        Serial.print(" | ");
      }
      Serial.println(" ");
    }
    Serial.println("---------------");
    Serial.println("ERROR Value :");
    for (int i = 0; i < 5; i++) {
      Serial.println(valueError[i]);
    }
    Serial.println("---------------");
    Serial.println("Delta Error  :");
    for (int i = 0; i < 3; i++) {
      Serial.println(valueDeltaError[i]);
    }
    Serial.println("---------------");
    Serial.print("Output : ");
    Serial.println(this->pwmOuput);
    Serial.println("<<<<<<<<>>>>>>>>>>");
  }

private:
  const float THi = 160, Hi = 140, N = 120, Lo = 80, TLo = 60;
  // float rule[3][5] = {
  //   // Constant Value
  //   { Hi, N, N, N, Lo },   // [H, H, H, N, L] H = HIGH
  //   { Hi, N, N, N, Lo },   // [H, N, N, N, L] N = NOMRAL
  //   { Hi, Hi, N, Lo, Lo }  // [H, N, L, L, L] L = LOW
  // };

  float rule[4][5] = {
    // Constant Value
    { THi, THi, N, TLo, TLo },
    { THi, Hi, N, Lo, TLo },   // [H, H, H, N, L] H = HIGH
    { THi, Hi, N, Lo, TLo },   // [H, N, N, N, L] N = NOMRAL
    { THi, Hi, Hi, Hi, TLo }  // [H, N, L, L, L] L = LOW
  };

  // float rule[3][5] = {
  //   // Constant Value
  //   { Lo, N, N, N, Hi },   // [H, H, H, N, L] H = HIGH
  //   { Lo, N, N, N, Hi },   // [H, N, N, N, L] N = NOMRAL
  //   { Lo, Lo, N, Hi, Hi }  // [H, N, L, L, L] L = LOW
  // };
  float valueRule[4][5];
  float valueError[5];
  float valueDeltaError[4];
  float output;

  float minX(float a, float b) {
    return (a < b) ? a : b; // if a < b return a; else return b
  }

  void calculateValue() {
    // FOR Error
    valueError[0] = error_MN(error);
    valueError[1] = error_N(error);
    valueError[2] = error_Z(error);
    valueError[3] = error_P(error);
    valueError[4] = error_MP(error);

    // FOR Delta Error
    valueDeltaError[0] = deltaError_DN(deltaError);
    valueDeltaError[1] = deltaError_DS(deltaError);
    valueDeltaError[2] = deltaError_DN(deltaError);
    valueDeltaError[3] = deltaError_DP(deltaError);
  }

  void setValueRule() {  // With AND Operator;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        valueRule[i][j] = minX(valueDeltaError[i], valueError[j]);  // AND find the Min Between 2
      }
    }
  }

  float defuzz() {
    float x = 0, y = 0;  // DEFUZ with x/y
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 5; j++) {
        x += rule[i][j] * valueRule[i][j];
        y += valueRule[i][j];
      }
    }
    return (x / y);
  }

  float fuzzyProcess() {
    calculateValue();
    setValueRule();
    return defuzz();
  }
};