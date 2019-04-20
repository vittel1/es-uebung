#include <stdio.h>
#include <string.h>
#include <regex.h>

void testString(char testValue[]) {

  printf("%s: ", testValue);

  regex_t regex;
  int reti;

  reti = regcomp(&regex, "^setRGB\\([[:digit:]].[[:digit:]]\\, [[:space:][:digit:]].[[:digit:]]\\, [[:space:][:digit:]].[[:digit:]]\\)", REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
  }

  reti = regexec(&regex, testValue , 0, NULL, 0);
  if (!reti) {
    printf("Correct Format!\n");
  } else {
    printf("Wrong Format!\n");
  }
  regfree(&regex);
}

int main() {

  testString("setRGB"); //WRONG
  testString("setRGB()"); //WRONG
  testString("setRGB(1.0,0.0,0.0)"); //WRONG
  testString("setRGB(1.0, 0.0,     0.0)"); //WRONG
  testString("setRGB(10.0, 0.09999, 123123.0)"); //WRONG
  testString("setRGB(0.0, 0.0, 1.0)"); //CORRECT
  testString("setRGB(1.0, 5.0, 9.0)"); //CORRECT

  return 0;
}
