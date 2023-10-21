
#include <iostream>

#include "filesystem.hpp"
#include "terminal_emulator.hpp"
#include "terminal_mode_interface.hpp"
#include "wash.hpp"

TerminalEmulator emulator;
Filesystem filesystem;
Wash shell(emulator, filesystem);

extern "C" {
void key_pressed(char key, bool ctrl, bool alt, bool shift, bool meta) {
  shell.input_key(key, ctrl, alt, shift, meta);
}
}

void setup_fs() {
  auto root = filesystem.get_root();
  // /bin
  {
    auto bin = std::make_unique<FSINode>(INodeType::INODE_DIR, root, std::string{""}, 0777);
    // /bin/ls
    {
      auto bin_ls = std::make_unique<FSINode>(INodeType::INODE_FILE, bin.get(), std::string{"<binary>"}, 0555, 187000);
      bin->children.emplace(std::make_pair("ls", std::move(bin_ls)));
    }
    root->children.emplace(std::make_pair("bin", std::move(bin)));
  }
  // /home
  {
    auto home = std::make_unique<FSINode>(INodeType::INODE_DIR, root, std::string{""}, 0755);
    // /home/education
    {
      auto home_education = std::make_unique<FSINode>(INodeType::INODE_DIR, root, std::string{""}, 0755);
      home->children.emplace(std::make_pair("education", std::move(home_education)));
    }
    // /home/projects
    {
      auto home_education = std::make_unique<FSINode>(INodeType::INODE_DIR, root, std::string{""}, 0755);
      home->children.emplace(std::make_pair("education", std::move(home_education)));
    }
    // /home/
    {
      auto home_education = std::make_unique<FSINode>(INodeType::INODE_DIR, root, std::string{""}, 0755);
      home->children.emplace(std::make_pair("education", std::move(home_education)));
    }
    {
      auto home_education = std::make_unique<FSINode>(INodeType::INODE_DIR, root, std::string{""}, 0755);
      home->children.emplace(std::make_pair("education", std::move(home_education)));
    }
    root->children.emplace(std::make_pair("home", std::move(home)));
  }
}

int main() {
  setup_fs();

  update_terminal(emulator);
}
