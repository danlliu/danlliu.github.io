#pragma once

#include <string>
#include <vector>

struct Course {
  std::string title;
  std::vector<std::string> concepts;
};
std::vector<Course> get_relevant_courses();

struct Project {
  std::string name;
  std::string id;
  std::vector<const char*> tags;
  std::string github;
  std::string description;
};
std::vector<Project> get_personal_projects();

struct WorkExp {
  std::string company;
  std::string location;
  std::string start;
  std::string end;
  std::string position;
  std::vector<const char*> bullets;
};
std::vector<WorkExp> get_work_experience();

struct ResearchExp {
  std::string institution;
  std::string advisor;
  std::string start;
  std::string end;
  std::vector<const char*> bullets;
};
std::vector<ResearchExp> get_research_experience();

struct Award {
  std::string name;
  std::string timeline;
  std::string description;
};
std::vector<Award> get_awards();
