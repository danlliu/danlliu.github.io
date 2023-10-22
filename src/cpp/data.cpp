
#include "data.hpp"

#include "string"
#include <vector>

#define LIST(...) {__VA_ARGS__}

#define TITLE(title) title
#define CONCEPTS(...) {__VA_ARGS__}
#define COURSE(...) Course{__VA_ARGS__}

std::vector<Course> get_relevant_courses() {
  std::vector<Course> courses
#include "education"
  ;
  return courses;
}

#define NAME(name) name
#define ID(id) id
#define TAGS(...) {__VA_ARGS__}
#define GITHUB(link) link
#define DESCRIPTION(desc) desc
#define PROJECT(...) Project{__VA_ARGS__}

std::vector<Project> get_personal_projects() {
  std::vector<Project> projects
#include "projects"
  ;
  return projects;
}

#define COMPANY(company) company
#define LOCATION(loc) loc
#define START(s) s
#define END(e) e
#define NOEND() ""
#define POSITION(pos) pos
#define BULLETS(...) {__VA_ARGS__}

#define WORK_EXP(...) WorkExp{__VA_ARGS__}

std::vector<WorkExp> get_work_experience() {
  std::vector<WorkExp> exp
#include "work_exp"
  ;
  return exp;
}

#define INSTITUTION(i) i
#define ADVISOR(a) a
#define START(s) s
#define END(e) e
#define BULLETS(...) {__VA_ARGS__}

#define RESEARCH_EXP(...) ResearchExp{__VA_ARGS__}

std::vector<ResearchExp> get_research_experience() {
  std::vector<ResearchExp> exp
#include "research_exp"
  ;
  return exp;
}
