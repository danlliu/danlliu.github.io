
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
          'Developed a new WebAssembly interpreter for Apple\'s JavaScriptCore framework, improving startup time and memory usage by 7% compared to existing WebAssembly infrastructure',
          'Shipped over 14,000 lines of C++ and handwritten assembly to implement the core WebAssembly specification, giving the new interpreter similar runtime performance to the existing WebAssembly runtime environment',
          'Check out my commits at <a class="text-blue underline" href="https://github.com/WebKit/WebKit/pulls?q=is%3Apr+author%3Adanlliu" target="_blank">WebKit\'s GitHub repository</a>!',
        ]
      },
      {
        'company': 'Caesar Creek Software',
        'location': 'Miamisburg, OH',
        'start': 'May 2023',
        'end': 'Jun 2023',
        'position': 'Software Engineering Intern',
        'bullets': [
          'Performed control flow vulnerability research, binary reverse engineering, and hardware firmware extraction',
          'Collaborated with a team of interns to discover vulnerabilities in existing commercial products',
        ]
      },
      {
        'company': 'Amazon',
        'location': 'Sunnyvale, CA',
        'start': 'May 2022',
        'end': 'Jul 2022',
        'position': 'Software Engineering Intern: Lab126',
        'bullets': [
          'Collaborated with full time SDEs and other interns to integrate a front-end Android app developed in Kotlin with existing APIs and new ML models to provide users with a wide range of responsive and intelligent functionalities',
          'Developed and updated user-facing content to improve user experience and incorporate new technical features',
          'Added quality assurance and user engagement code to provide engineers with meaningful data about what features of the app were engaged with the most',
        ]
      },
      {
        'company': 'University of Michigan',
        'location': 'Ann Arbor, MI',
        'start': 'Sep 2020',
        'position': 'Instructional Aide',
        'bullets': [
          'Served on the teaching staff of three main-track (Programming and Introductory Data Structures; Data Structures and Algorithms; Introduction to Computer Organization), and one upper-level (Introduction to Computer Security) computer science courses, teaching roughly 5500 students across nine semesters',
          'Helped students debug coding projects involving C++, C, Python, x86, and Go; understand lecture material through regularly scheduled office hours and lab sections; and build confidence in their coding abilities',
          'Developed lab assignments, coding projects, course notes, and exam questions to reinforce and measure student understanding of course material',
          'Collaborated with course staff and professors to ensure a seamless student experience, leading effort on key tasks such as exam creation, grading, and new project development',
        ]
      }
    ]
  },
  'research_exp': {
    'experiences': [
      {
        'institution': 'University of Michigan',
        'advisor': 'Advisor: Dr. Paul Grubbs',
        'start': 'Sep 2023',
        'bullets': [
          'Analyzed the security of cryptographic protocols used in zero-knowledge proofs, examining the security and integrity of zero-knowledge proof-based blockchain systems'
        ]
      },
      {
        'institution': 'University of Michigan',
        'advisor': 'Advisors: Dr. Trevor Mudge, Dr. Ronald Dreslinski',
        'start': 'Jan 2022',
        'end': 'Jun 2022',
        'bullets': [
          'Developed C++ simulators for validating a new hardware accelerator specialized for handling pattern matching in temporal graphs',
          'Demonstrated a performance increase of up to three orders of magnitude compared to state-of-the-art algorithms run on GPUs',
          '<a class="text-blue" href="https://tnm.engin.umich.edu/wp-content/uploads/sites/353/2023/03/2022.10.Mint_An_Accelerator_For_Mining_Temporal_Motifs.pdf" target="_blank">Published in MICRO 2022</a>'
        ]
      },
      {
        'institution': 'University of Michigan',
        'advisor': 'Advisor: Dr. Manos Kapritsos',
        'start': 'May 2021',
        'end': 'Dec 2021',
        'bullets': [
          'Improved Dafny, a formal verification language, to implement detection of matching loops, a condition where the proof engine times out on an ever-expanding set of facts',
          'Worked towards detecting time-consuming matching loops early on through runtime dtection of patterns that may generate matching loops'
        ]
      },
      {
        'institution': 'University of Michigan',
        'advisor': 'Advisor: Dr. Melanie Sanford',
        'start': 'Aug 2019',
        'bullets': [
          'Developed a combined compuational and experimental method to expand the substrate scope of transannular C–H activation and functionalization',
          'Utilized Python and Bash scripting to create high-throughput infrastructure allowing the screening of hundres of structures computationally and confirmed these results through experimental methodology'
        ]
      }
    ]
  },
  'awards': {
    'awards': [
      {
        'name': 'Goldwater Scholarship',
        'timeline': '2022',
        'description': 'The Goldwater Scholarship is awarded annualy to less than 500 undergraduate students across the nation for students who intend to pursue research careers in STEM disciplines and demonstrate potential as leaders in research.'
      }
    ]
  }
}

import json
index_env['projects']['project_json'] = json.dumps(index_env['projects']['projects'])

render_template("index.html", **index_env) > BUILD / "index.html"

render_template("terminal_mode.html") > BUILD / "terminal_mode.html"
