
#include "filesystem.hpp"

#include <memory>
#include <string>
#include <vector>

Filesystem::Filesystem() {
  root = std::make_unique<FSINode>();
  root->type = INodeType::INODE_DIR;
} 


