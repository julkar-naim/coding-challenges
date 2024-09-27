#include <algorithm>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <locale>
#include <list>
#include <iomanip>

using namespace std;

typedef void (*Operation)(istream& inputStream);

list<int> out;

string input;

void executeOperation(Operation operationFunc, string filename, ios::openmode mode) {
  if (!filename.empty()) {
    ifstream file(filename, mode);
    if (!file.is_open()) {
      return;
    }
    operationFunc(file);
    file.close();
    return;
  }
  stringstream ss(input);
  operationFunc(ss);
}

void numberOfBytes(istream& inputStream) {
  inputStream.seekg(0, ios::end);
  std::streamsize inputStreamSizeInBytes = inputStream.tellg();
  out.push_back(inputStreamSizeInBytes);
}

void numberOfLines(istream& inputStream) {
  int lineCount = 0;
  string line;
  while(getline(inputStream, line)) {
    lineCount++;
  }
  out.push_back(lineCount);
}

void numberOfWords(istream& inputStream) {
  string line;
  int wordCount = 0;
  while(getline(inputStream, line)) {
    stringstream strStream(line);
    string word;
    while(strStream >> word)  wordCount++;
  }
  out.push_back(wordCount);
}

void numberOfCharacters(istream& inputStream) {
  ostringstream buffer;
  buffer << inputStream.rdbuf();
  string inputStreamContent = buffer.str();

  wstring_convert<codecvt_utf8<wchar_t>> converter;
  wstring wideString = converter.from_bytes(inputStreamContent);
  out.push_back(wideString.length());
}


void printOutput(string filename) {
  int maxElement = *max_element(out.begin(), out.end());
  int len = to_string(maxElement).length();
  for (int it: out) {
    cout << setw(len ) << it << " ";
  }
  cout << filename << endl;
}



int main(int args, char* argv[]) {
  bool byteCount = false;
  bool lineCount = false;
  bool charCount = false;
  bool wordCount = false;
  string filename;


  for (int i = 1; i < args; i++) {
    if (argv[i][0] != '-') {
      filename = argv[i];
    }
    string argOption = argv[i];
    for (char c: argOption) {
      byteCount |= c == 'c';
      lineCount |= c == 'l';
      wordCount |= c == 'w';
      charCount |= c == 'm';
    }
  }

  if (!byteCount && !lineCount && !charCount && !wordCount) {
    byteCount = true;
    lineCount = true;
    wordCount = true;
  }

  if (filename.empty()) {
    getline(cin, input, '\0');
  }


  if (lineCount) {
    executeOperation(numberOfLines, filename, ios::in);
  }
  if (wordCount) {
    executeOperation(numberOfWords, filename, ios::in);
  }
  if (charCount) {
    executeOperation(numberOfCharacters, filename, ios::in);
  }
  if (byteCount) {
    executeOperation(numberOfBytes, filename, ios::binary);
  }

  printOutput(filename);


  return 0;
}
