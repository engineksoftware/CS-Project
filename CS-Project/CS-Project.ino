/*
 * Converts a base-10 number into binary form, and lights the correct LEDs starting from the right.
 * Used with an Arudino UNO, and 8 LEDs.
 */


 
/* 
 *  Can change these to different pins.
 *  
 * NOTE: The pins in the array is equal to the LED configuration from left to right.
 *       Pin 2 LED is farthest to the left, and Pin 13 LED is farthest to the right.
 */
int pins[] = {2, 4, 8, 9, 10, 11, 12, 13}; 
int pinIndex = 7; /* Used to select last index of pins. The pins array will never exceed 8 unless more LEDs are added. */
int pinCount = 8;

void setup() {
  for (int x = 0; x < pinCount; x++) {
    pinMode(pins[x], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  //convert(10);

  int test[6];
  test[0] = 1;
  test[1] = 0;
  test[2] = 1;
  test[3] = 1;
  test[4] = 0;
  test[5] = 1;

  twosComplement(test, 6);
  
  while (1) {}
}

/*
  * Converts num to a array of 1s and 0s.
  * 
  * If num is greater than or equal to 2^exponent, that value can be taken from num and a 1
  * can be added to the array. If not, that value can't be taken from num which means a 0
  * needs to be added to the array.
  * 
  * 1 will then be taken from exponent, so on the next iteration the next proper value 
  * will be compared.         
  */
void convert(int num) {

  int exponentMax = findExponent(num);
  int exponent = exponentMax;
  int arraySize = exponentMax + 1;
  int binaryArray[arraySize];
  
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

  light(binaryArray, arraySize);

}

/*
 * Finds the highest exponent value that can be taken out of num. 
 * 
 * That same value can be used as the condition for the loop that
 * assigns 1s and 0s to the binaryArray.
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


/*
 * Iterates through the binary array backwards, so that the LEDs can be lit starting from the right.
 * If the value at the index of the binaryArray equals 1, a HIGH bit will be sent to the correct
 * pin which will turn that LED on. If the value equals 0, a LOW bit will be sent to the correct 
 * pin whcih will turn that LED off.
 * 
 * 1 will then be taken from pinIndex, so that you can move left through the array of pins.
 */
void light(int *binArray, int arraySize){
  for (int x = (arraySize - 1); x >= 0; x--) {
    if (binArray[x] == 1) {
      digitalWrite(pins[pinIndex], HIGH);
    } else {
      digitalWrite(pins[pinIndex], LOW);
    }

    pinIndex -= 1;

  }
}

void twosComplement(int *binArray, int arraySize){

  int newArray[8];
  int index = arraySize -1;
  boolean hitOne = false;

  for(int x = 7; x >= 0; x--){
    if(index < 0){
      newArray[x] = 1;
    }else
    if(binArray[index] == 0 && hitOne == false){
      newArray[x] = binArray[index];
    }else
    if(binArray[index] == 1 && hitOne == false){
      newArray[x] = binArray[index];
      hitOne = true;
    }else
    if(binArray[index] == 0 && hitOne == true){
      newArray[x] = 1;
    }else{
      newArray[x] = 0;
    }

    index -= 1;
  }

  for(int x = 0; x < 8; x++){
    Serial.print(newArray[x]);
  }
  
}


