
from build_html import render_template

from pathlib import Path

SRC = Path('src')
BUILD = Path('build')

resume_size = (SRC/'assets/resume.pdf').stat().st_size
suffixes = ['', 'k', 'M', 'G']
suffix_idx = 0

while resume_size >= 1000:
  suffix_idx += 1
  resume_size /= 1000

resume_size_str = ''

if suffix_idx == 0:
  resume_size_str = f'{resume_size}'
elif resume_size >= 1000:
  resume_size_str = f'{resume_size / 1024:.01f}{suffixes[suffix_idx+1]}'
else:
  resume_size_str = f'{resume_size:.00f}{suffixes[suffix_idx]}'

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
        'type': 'file',
        'perm_bits': '.rwxr--r--',
        'name': 'resume',
        'size': resume_size_str,
        'url': '/resume.pdf'
      },
    ]
  },
  'education': {
    'relevant_coursework': [
      {
        'title': 'Introduction to Operating Systems',
        'concepts': [
          'threads and synchronization',
          'virtual memory management',
          'socket programming'
        ]
      },
      {
        'title': 'Compiler Construction',
        'concepts': [
          'x64 assembly',
          'abstract syntax tree manipulation',
          'register allocation'
        ]
      },
      {
        'title': 'Introduction to Computer Security',
        'concepts': [
          'cryptography',
          'web security: SQLi, XSS, CSRF',
          'application security: buffer overflows'
        ]
      },
      {
        'title': 'Web Systems',
        'concepts': [
          'dynamic web applications',
          'JavaScript programming',
          'search engine algorithms'
        ]
      },
      {
        'title': 'User Interface Development',
        'concepts': [
          'responsive web design',
          'human-centered design',
          'Bootstrap CSS framework'
        ]
      },
      {
        'title': 'Introduction to Computer Organization',
        'concepts': [
          'ARM assembly',
          'processor design',
          'low-level code optimization'
        ]
      },
    ]
  },
  'projects': {
    'projects': [
      {
        'name': 'danlliu.github.io',
        'id': 'personalweb',
        'tags': ['web', 'html', 'css', 'js', 'tailwind'],
        'github': 'https://github.com/danlliu/danlliu.github.io',
        'description': 'The third iteration of my personal website!'
      },
      {
        'name': 'dvim',
        'id': 'dvim',
        'tags': ['c++', 'cpp'],
        'github': 'https://github.com/danlliu/dvim',
        'description': 'A homegrown terminal text editor'
      },
      {
        'name': 'cppserver',
        'id': 'cppserver',
        'tags': ['c++', 'cpp', 'web', 'socket'],
        'github': 'https://github.com/danlliu/cppserver',
        'description': 'A webserver written in C++'
      },
      {
        'name': 'armstdlib',
        'id': 'armstdlib',
        'tags': ['armv8', 'asm'],
        'github': 'https://github.com/danlliu/armstdlib',
        'description': 'A collection of data structures and algorithms written in ARMv8 assembly'
      },
      {
        'name': 'flasm',
        'id': 'flasm',
        'tags': ['x86', 'x64', 'asm'],
        'github': 'https://github.com/danlliu/flasm',
        'description': 'A collection of data structures and algorithms written in x86_64 assembly'
      },
      {
        'name': 'pdp',
        'id': 'pdp',
        'tags': ['asm', 'c++', 'cpp'],
        'github': 'https://github.com/danlliu/pdp',
        'description': 'An assembler and simulator for the PDP-1 computer\'s assembly language'
      },
      {
        'name': 'beepboop',
        'id': 'beepboop',
        'tags': ['js', 'programming language', 'esolang'],
        'github': 'https://github.com/danlliu/beepboop',
        'description': 'An esoteric programming language where you only have "beep" and "boop"'
      }
    ]
  },
  'work_exp': {
    'experiences': [
      {
        'company': 'Apple',
        'location': 'Cupertino, CA',
        'start': 'Jun 2023',
        'end': 'Aug 2023',
        'position': 'Software Engineering Intern: WebKit / JavaScriptCore',
        'bullets': [
          'ABC',
          'DEF',
          'GHI',
        ]
      },
      {
        'company': 'Caesar Creek Software',
        'location': 'Miamisburg, OH',
        'start': 'May 2023',
        'end': 'Jun 2023',
        'position': 'Software Engineering Intern',
        'bullets': [
          'ABC',
          'DEF',
          'GHI',
        ]
      },
      {
        'company': 'Amazon',
        'location': 'Sunnyvale, CA',
        'start': 'May 2022',
        'end': 'Jul 2022',
        'position': 'Software Engineering Intern: Lab126',
        'bullets': [
          'ABC',
          'DEF',
          'GHI',
        ]
      },
      {
        'company': 'University of Michigan',
        'location': 'Ann Arbor, MI',
        'start': 'Sep 2020',
        'position': 'Instructional Aide',
        'bullets': [
          'ABC',
          'DEF',
          'GHI',
        ]
      }
    ]
  }
}

import json
index_env['projects']['project_json'] = json.dumps(index_env['projects']['projects'])

render_template("index.html", **index_env) > BUILD / "index.html"
