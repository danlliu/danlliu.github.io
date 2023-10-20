
#include "filesystem.hpp"

#include <memory>
#include <string>
#include <vector>

FilesystemPath compute_path(const FilesystemPath &cwd, const std::string &path) {
  size_t i = 0;
  FilesystemPath result = cwd;
  if (path[0] == '/') {
    // absolute
    i = 1;
    result = {};
  }
  // relative
  std::string component;
  for (; i < path.size(); ++i) {
    if (path[i] == '/') {
      if (component == ".") {
      } else if (component == "..") {
        if (result.size())
          result.pop_back();
      } else {
        result.push_back(component);
      }
      component = "";
    } else {
      component += path[i];
    }
  }
  if (component == "") {
  } else if (component == ".") {
  } else if (component == "..") {
    if (result.size())
      result.pop_back();
  } else {
    result.push_back(component);
    component = "";
  }
  return result;
}

Filesystem::Filesystem() {
  root = std::make_unique<FSINode>(INodeType::INODE_DIR, nullptr, std::string{""}, 0777);
  root->parent = root.get();
}

FSINode *Filesystem::get_inode(const FilesystemPath &path) {
  FSINode *ptr = root.get();
  for (auto segment : path) {
    if (auto it = ptr->children.find(segment); it != ptr->children.end()) {
      ptr = it->second.get();
    } else {
      return nullptr;
    }
  }
  return ptr;
}
