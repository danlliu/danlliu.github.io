#pragma once

#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

// ok, we're not going to write up the full simulation lol

using FilesystemPath = std::stack<std::string>;

enum INodeType : char {
  INODE_DIR = 'd',
  INODE_FILE = 'f',
};

struct FSINode {
  INodeType type;
  std::map<std::string, std::unique_ptr<FSINode>> children;
  std::string content;
};

class Filesystem {
 public:
  Filesystem();

  std::string read_file(const FilesystemPath& path);
 private:
  std::unique_ptr<FSINode> root;
};
