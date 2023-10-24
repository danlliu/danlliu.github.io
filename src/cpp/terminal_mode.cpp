
#include <emscripten/proxying.h>
#include <sstream>
#include <string>
#include <pthread.h>

#include "data.hpp"
#include "filesystem.hpp"
#include "terminal_emulator.hpp"
#include "terminal_mode_interface.hpp"
#include "wash.hpp"

#ifndef __EMSCRIPTEN_PTHREADS__
static_assert(false, "thread support required");
#endif

pthread_t main_thread;
std::mutex proxy_queue_mutex;
em_proxying_queue* proxy_queue = nullptr;

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
      auto home_education = std::make_unique<FSINode>(INodeType::INODE_DIR, home.get(), std::string{""}, 0755);
      {
        std::ostringstream oss;
        oss << "# University of Michigan: Ann Arbor\n\n";
        oss << "## College of Literature, Science, and the Arts\n";
        oss << "B.S.Chem in Computer Science and Chemistry **anticipated May 2024**\n\n";
        oss << "## Ross School of Business\n";
        oss << "Bachelors of Business Administration **anticipated May 2024**\n\n";
        auto home_education_umich = std::make_unique<FSINode>(INodeType::INODE_FILE, home_education.get(), oss.str(), 0644);
        home_education->children.emplace(std::make_pair("umich", std::move(home_education_umich)));
      }
      {
        std::ostringstream oss;
        oss << "# Relevant Coursework\n\n";
        for (auto course : get_relevant_courses()) {
          oss << "## " << course.title << "\n";
          for (auto concept : course.concepts) {
            oss << "- " << concept << "\n";
          }
          oss << "\n";
        }
        auto home_education_rel_course = std::make_unique<FSINode>(INodeType::INODE_FILE, home_education.get(), oss.str(), 0644);
        home_education->children.emplace(std::make_pair("relevant_coursework.txt", std::move(home_education_rel_course)));
      }
      home->children.emplace(std::make_pair("education", std::move(home_education)));
    }
    // /home/projects
    {
      auto home_projects = std::make_unique<FSINode>(INodeType::INODE_DIR, home.get(), std::string{""}, 0755);
      for (auto project : get_personal_projects()) {
        std::ostringstream oss;
        oss << "# " << project.name << "\n\n";

        for (auto tag : project.tags) {
          oss << "[" << tag << "] ";
        }
        oss << "\n\n";
        
        oss << "[GitHub repository](" << project.github << ")\n\n";

        oss << project.description << "\n";
        auto proj_node = std::make_unique<FSINode>(INodeType::INODE_FILE, home_projects.get(), oss.str(), 0644);
        home_projects->children.emplace(std::make_pair(project.id, std::move(proj_node)));
      }
      home->children.emplace(std::make_pair("projects", std::move(home_projects)));
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

  main_thread = pthread_self();
  proxy_queue = em_proxying_queue_create();

  update_terminal(emulator);
}
