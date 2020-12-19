#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct Hijo {
  char name[20];
  int age;
};

struct Person
{
  char name[20];
  int age;
  struct Hijo hijo;
};

void printPerson(struct Person p)
{
  printf("Name: %s\nAge: %i\n", p.name, p.age);
  printf("Hijo: %s, Edad: %i\n", p.hijo.name, p.hijo.age);
}

void printPersonPointer(struct Person *p)
{
  printf("Name: %s\nAge: %i\n", p->name, p->age);
}

int main(int argc, char const *argv[])
{
  /* code */

  struct Person person;

  char padre[] = {"ShompiFlen"};
  char hijo[] = {"Muki"};

  strncpy(person.name, padre, sizeof(char) * 20);
  strncpy(person.hijo.name, hijo, sizeof(char) * 20);
  person.age = 22;
  person.hijo.age = 4;

  printPerson(person);
  return 0;
}
