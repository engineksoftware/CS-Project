int pins[] = {2, 4, 8, 9, 10, 11, 12, 13};
int pinCount = 8;

void setup() {
  for (int x = 0; x < pinCount; x++) {
    pinMode(pins[x], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  convert(10);
  while (1) {}
}

void convert(int num) {

  int exponentMax = findExponent(num);
  int exponent = exponentMax;
  int binaryArray[exponentMax + 1];

  /*
   * Uses exponentMax as the comparing value for the loop.
   * Checks to see if the number is greater than or equal to 2^newE 
   */
  for (int x = 0; x <= exponentMax; x++) {
    if (num >= pow(2, exponent)) {

      binaryArray[x] = 1;
      num -= pow(2, exponent);
    }
    else {
      binaryArray[x] = 0;
    }

    exponent -= 1;
  }

  int pinIndex = 7;

  for (int x = (sizeof(binaryArray) / sizeof(int) - 1); x >= 0; x--) {
    if (binaryArray[x] == 1) {
      digitalWrite(pins[pinIndex], HIGH);
    } else {
      digitalWrite(pins[pinIndex], LOW);
    }

    pinIndex -= 1;

  }

}

/*
 * Finds the highest exponent value that can be taken out of num.
 */
int findExponent(int num) {
  int exponent = 0;
  boolean found = false;

  while (found == false) {
    if (pow(2, exponent) > num) {
      exponent -= 1;
      found = true;
    } else {
      exponent++;
    }

  }

  return exponent;

}


