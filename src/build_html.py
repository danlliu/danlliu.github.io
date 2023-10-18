
from jinja2 import Environment, FileSystemLoader, select_autoescape

env = Environment(loader=FileSystemLoader("./src/templates"),
                  autoescape=select_autoescape())

class RenderedTemplate:
  def __init__(self, contents):
    self.contents = contents
  
  def __gt__(self, path):
    with open(path, 'w') as f:
      f.write(self.contents)

def render_template(file, **kwargs):
  template = env.get_template(file)
  return RenderedTemplate(template.render(**kwargs))
  
