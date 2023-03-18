#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class File {

public:
  /// <summary>
  /// Opens file for reading and returns the file contents
  /// </summary>
  /// <param name="path">File path</param>
  /// <returns>string contents of the file</returns>
  static std::string readFile(const char* path);

};