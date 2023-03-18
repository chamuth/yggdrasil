#include "file.h"

std::string File::readFile(const char* path) {
  std::ifstream in(path, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    return contents;
  }

  throw(errno);
}
