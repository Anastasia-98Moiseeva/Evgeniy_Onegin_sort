/**
 * MIPT, 695 group, home-work1
 *
 * @file
 * @author Moiseeva Anastasia
 */

#include <fstream>
#include <iostream>
#include <algorithm>

/**
 * Comporator for sort from left to right
 *
 * @param [out] x1    first parameter
 * @param [out] x2    second parameter
 *
 * @return result of comparation
 */
int comparator1(const void *x1_, const void *x2_) {
   char *x1 = *(char **) x1_;
   char *x2 = *(char **) x2_;

  while (!((*x1 >= 'a') && (*x1 <= 'z')) && !((*x1 >= 'A') && (*x1 <= 'Z')) && *x1 != '\n') {
    x1++;
  }
  while (!((*x2 >= 'a') && (*x2 <= 'z')) && !((*x2 >= 'A') && (*x2 <= 'Z')) && *x2 != '\n') {
    x2++;
  }
  while (*x1 != '\n' && *x2 != '\n') {

    if (*x1 == *x2) {
      x1++;
      x2++;
    } else {
      return *x1 > *x2;
    }
  }
  return *x1 != '\n';
}

/**
 * Comporator for sort from right to left
 *
 * @param [out] x1    first parameter
 * @param [out] x2    second parameter
 *
 * @return result of comparation
 */
int comparator2(const void *x1_, const void *x2_) {
  char *x1 = *(char **) x1_;
  char *x2 = *(char **) x2_;

  while (!((*x1 >= 'a') && (*x1 <= 'z')) && !((*x1 >= 'A') && (*x1 <= 'Z'))) {
    x1--;
  }
  while (!((*x2 >= 'a') && (*x2 <= 'z')) && !((*x2 >= 'A') && (*x2 <= 'Z'))) {
    x2--;
  }
  while (*x1 != '\n' && *x2 != '\n') {

    if (*x1 == *x2) {
      x1--;
      x2--;
    } else {
      return *x1 > *x2;
    }
  }
  return *x1 != '\n';
}

/**
 * Counting Symbols in text
 *
 * @param [in] file    file with text
 *
 * @return the number of symbols
 */
int CountSymbols(std::ifstream &file) {
  std::streampos size = file.tellg();
  file.seekg(0, std::ios::end);
  size = file.tellg() - size;
  file.seekg(0, std::ios::beg);
  return size;
}

/**
* Counting lines in text
*
* @param [in] text
* @param [in] text_size
 *
* @return the number of lines
*/
int CountLines(const char *text, const int text_size) {
  int number_of_lines = 0;
  for (int i = 0; i < text_size; i++) {
    if (text[i] == '\n') {
      number_of_lines++;
    }
  }
  return number_of_lines;
}

/**
 * Filling arrays of pointers
 *
 * @param [in] array_of_pointers1    pointers to the begin of lines
 * @param [in] array_of_pointers2    pointers to the end of lines
 * @param [in] text
 * @param [in] text_size
 */
void FillingArrays(char **array_of_pointers1, char **array_of_pointers2, char *text, const int text_size) {
  bool flag = false;
  int j = 0;
  array_of_pointers1[j] = &text[0];
  j++;
  for (int i = 1; i < text_size; i++) {
    if (flag) {
      array_of_pointers1[j] = &text[i];
      array_of_pointers2[j-1] = &text[i-2];
      j++;
      flag = false;
    }
    if (text[i] == '\n') {
      flag = true;
      if (i == text_size - 1) {
        array_of_pointers2[j-1] = &text[i-1];
      }
    }
  }
}

/**
 * Write one string in file (for sort from left to right)
 *
 * @param [in] file        file with result
 * @param [in] element     one symbol
 */
void WriteOneString1(std::ofstream &file, char *element) {
  while (*element != '\n') {
    file << *element;
    element++;
  }
  file << '\n';
}

/**
 * Write one string in file (for sort from right to left)
 *
 * @param [in] file       file with result
 * @param [in] element    one symbol
 */
void WriteOneString2(std::ofstream &file, char *element) {
  std::string str = "";
  while (*element != '\n') {
    str = *element + str;
    element--;
  }
  str += '\n';
  file << str;
}


/**
 * Write text in file
 *
 * @param [in] array_of_pointers1    pointers to the begin of lines
 * @param [in] array_of_pointers2    pointers to the end of lines
 * @param [in] number_of_lines
 * @param [in] text
 * @param [in] text_size
 */
void WriteInFile(char **array_of_pointers1, char **array_of_pointers2,
                 const int number_of_lines, const char *text, const int text_size) {
  std::ofstream file_out("/home/anastasia/CLionProjects/SortEvgenyiOnegin/result.txt"/*, std::ios_base::out | std::ios_base::trunc*/); // std::ios::app
  if (!file_out.is_open()) {
    std::cout << "Файл не может быть открыт или создан\n";
  } else {
    file_out << "ОТСОРТИРОВАННО СЛЕВА НАПРАВО.\n";
    for (int i = 0; i < number_of_lines; i++) {
      if (*array_of_pointers1[i] != '\n') {
        WriteOneString1(file_out, array_of_pointers1[i]);
      }
    }
    file_out << std::endl << "ОТСОРТИРОВАННО СПРАВА НАЛЕВО.\n";
    for (int i = 0; i < number_of_lines; i++) {
      if (*array_of_pointers1[i] != '\n') {
        WriteOneString2(file_out, array_of_pointers2[i]);
      }
    }
    file_out << std::endl << "ОРИГИНАЛ.\n";
    for (int i = 0; i < text_size; i++) {
      file_out << text[i];
    }
  }
}


int main(int argc, char* argv[])
{
  std::string file_name = "/home/anastasia/CLionProjects/SortEvgenyiOnegin/EvgenyiOnegin.txt";

  std::ifstream file_in(file_name);
  if (!file_in.is_open()) {
    std::cout << "Файл не может быть открыт\n";
    return 1;
  }

  int text_size = CountSymbols(file_in);
  text_size += 2;
  char *text = new char[text_size];
  text[0] = '\n';
  file_in.read(text + 1, text_size-1);
  if (text[text_size - 2] != '\n') {
    text[text_size - 1] = '\n';
  } else {
    text_size--;
  }

  file_in.close();
  int number_of_lines = CountLines(text + 1, text_size-1);

  char **array_of_pointers1 = new char *[number_of_lines];
  char **array_of_pointers2 = new char *[number_of_lines];

  FillingArrays(array_of_pointers1, array_of_pointers2, text + 1, text_size - 1);

  std::qsort(array_of_pointers1, number_of_lines, sizeof(char *), comparator1);
  std::qsort(array_of_pointers2, number_of_lines, sizeof(char *), comparator2);

  WriteInFile(array_of_pointers1, array_of_pointers2, number_of_lines, text, text_size);

  return 0;
}

