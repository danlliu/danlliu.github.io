#pragma once

#include <map>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

// ok, we're not going to write up the full simulation lol

using FilesystemPath = std::vector<std::string>;

FilesystemPath compute_path(const FilesystemPath &cwd, const std::string &path);

enum INodeType : char {
  INODE_DIR = 'd',
  INODE_FILE = 'f',
};

struct FSINode {
  INodeType type;
  FSINode *parent;
  std::map<std::string, std::unique_ptr<FSINode>> children;
  std::string content;
  int perms;
  std::optional<size_t> override_size;

  FSINode(INodeType type, FSINode *parent, std::string content, int perms)
      : type(type), parent(parent), children{}, content(content), perms(perms), override_size{} {}

  FSINode(INodeType type, FSINode *parent, std::string content, int perms, size_t override_size)
      : type(type), parent(parent), children{}, content(content), perms(perms), override_size(override_size) {}
    
  std::vector<std::pair<std::string, FSINode*>> get_children() {
    std::vector<std::pair<std::string, FSINode*>> result;
    result.emplace_back(std::make_pair(".", this));
    result.emplace_back(std::make_pair("..", parent));
    for (auto &[k, v] : children) {
      result.emplace_back(std::make_pair(k, v.get()));
    }
    return result;
  }

  std::string file_size() {
    size_t size = override_size ? *override_size : content.size();
    size_t remainder = 0;
    size_t idx = 0;
    while (size >= 1000) {
      remainder = size % 1000;
      size /= 1000;
      ++idx;
    }
    static std::string suffixes[] = {"", "k", "M", "G"};
    std::ostringstream oss;
    if (idx == 0) {
      oss << size;
    } else if (size < 10) {
      oss << size << "." << remainder / 100 << suffixes[idx];
    } else {
      oss << size << suffixes[idx];
    }
    return oss.str();
  }
};

class Filesystem {
public:
  Filesystem();

  std::string read_file(const FilesystemPath &path);

  FSINode *get_root() {
    return root.get();
  }

  FSINode *get_inode(const FilesystemPath &path);

private:
  friend class Wash;

  std::unique_ptr<FSINode> root;
};
