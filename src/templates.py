
from build_html import render_template

from pathlib import Path

SRC = Path('src')
BUILD = Path('build')

resume_size = (SRC/'assets/resume.pdf').stat().st_size

def format_size(size):
  suffixes = ['', 'k', 'M', 'G']
  suffix_idx = 0

  while size >= 1000:
    suffix_idx += 1
    size /= 1000

  size_str = ''

  if suffix_idx == 0:
    size_str = f'{size}'
  elif size >= 1000:
    size_str = f'{size / 1024:.01f}{suffixes[suffix_idx+1]}'
  else:
    size_str = f'{size:.00f}{suffixes[suffix_idx]}'
  return size_str

resume_size_str = format_size(resume_size)

def get_relevant_coursework():
  def TITLE(name):
    return name
  def CONCEPTS(*a):
    return [*a]
  def COURSE(title, concepts):
    return {
      'title': title,
      'concepts': concepts
    }
  def LIST(*a):
    return [*a]
  return eval(open(SRC/'data/education').read())

def get_projects():
  def NAME(name):
    return name
  def ID(_id):
    return _id 
  def TAGS(*a):
    return [*a]
  def GITHUB(link):
    return link
  def DESCRIPTION(desc):
    return desc
  def PROJECT(name, _id, tags, github, description):
    return {
      'name': name,
      'id': _id,
      'tags': tags,
      'github': github,
      'description': description
    }
  def LIST(*a):
    return [*a]
  return eval(open(SRC/'data/projects').read())

def get_work_exp():
  def TAG(_id):
    return _id 
  def COMPANY(x):
    return x
  def LOCATION(x):
    return x
  def START(x):
    return x
  def END(x):
    return x
  def NOEND():
    return None
  def POSITION(x):
    return x
  def BULLETS(*a):
    return [*a]
  def WORK_EXP(tag, company, location, start, end, position, bullets):
    return {
      'company': company,
      'location': location,
      'start': start,
      'end': end,
      'position': position,
      'bullets': bullets
    }
  def LIST(*a):
    return [*a]
  return eval(open(SRC/'data/work_exp').read())

def get_research_exp():
  def INSTITUTION(x):
    return x
  def ADVISOR(x):
    return x
  def START(x):
    return x
  def END(x):
    return x
  def NOEND():
    return None
  def BULLETS(*a):
    return [*a]
  def RESEARCH_EXP(institution, advisor, start, end, bullets):
    return {
      'institution': institution,
      'advisor': advisor,
      'start': start,
      'end': end,
      'bullets': bullets
    }
  def LIST(*a):
    return [*a]
  return eval(open(SRC/'data/research_exp').read())

def get_awards():
  def NAME(x):
    return x
  def TIMELINE(x):
    return x
  def DESCRIPTION(x):
    return x
  def AWARD(name, timeline, description):
    return {
      'name': name,
      'timeline': timeline,
      'description': description
    }
  def LIST(*a):
    return [*a]
  return eval(open(SRC/'data/awards').read())

index_env = {
  'banner': {
    'asciiart': open(SRC/'assets/dl_ascii.txt').read(),
    'sections': [
      {
        'type': 'symlink',
        'perm_bits': 'lrwxr--r--',
        'name': 'education',
        'tag': 'education'
      },
      {
        'type': 'symlink',
        'perm_bits': 'lrwxr--r--',
        'name': 'personal_projects',
        'tag': 'projects'
      },
      {
        'type': 'symlink',
        'perm_bits': 'lrwxr--r--',
        'name': 'work_experience',
        'tag': 'work_experience'
      },
      {
        'type': 'symlink',
        'perm_bits': 'lrwxr--r--',
        'name': 'research_experience',
        'tag': 'research_experience'
      },
      {
        'type': 'symlink',
        'perm_bits': 'lrwxr--r--',
        'name': 'awards',
        'tag': 'awards'
      },
      {
        'type': 'symlink',
        'perm_bits': 'lrwxr--r--',
        'name': 'contact',
        'tag': 'contact'
      },
      {
        'type': 'file',
        'perm_bits': '.rwxr--r--',
        'name': 'resume',
        'size': resume_size_str,
        'url': '/resume.pdf'
      },
    ]
  },
  'education': {
    'relevant_coursework': get_relevant_coursework()
  },
  'projects': {
    'projects': get_projects()
  },
  'work_exp': {
    'experiences': get_work_exp()
  },
  'research_exp': {
    'experiences': get_research_exp()
  },
  'awards': {
    'awards': get_awards()
  }
}

import json
index_env['projects']['project_json'] = json.dumps(index_env['projects']['projects'])

render_template("index.html", **index_env) > BUILD / "index.html"

render_template("terminal_mode.html") > BUILD / "terminal_mode.html"
