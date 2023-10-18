
let projects_shown = [];
let projects_selected_index = 0;

function projectsearch_generate_line(name, index, selected) {
  if (selected) {
    return `<pre class="p-1 cursor-pointer bg-white/30" onclick="set_active(${index})"><span class="text-red font-bold">&gt;</span> ${name}</pre>`;
  } else {
    return `<pre class="p-1 cursor-pointer" onclick="set_active(${index})">  ${name}</pre>`;
  }
}

function projectsearch_generate_lines() {
  let content = '';
  for (let index of projects_shown) {
    content += projectsearch_generate_line(projects_projectdata[index].name, index, index === projects_selected_index) + "\n";
  }
  document.querySelector('#projects_results').innerHTML = content;
  document.querySelector('#projects_result_count').innerHTML = `${projects_shown.length} / ${projects_projectdata.length}`
}

function set_active(index) {
  projects_selected_index = index;
  for (let i = 0; i < projects_projectdata.length; ++i) {
    if (i == index) {
      document.querySelector(`#project_${projects_projectdata[i].id}`).classList = [];
    } else {
      document.querySelector(`#project_${projects_projectdata[i].id}`).classList = ['hidden'];
    }
  }
  projectsearch_generate_lines();
}

function projectsearch(e) {
  projects_selected_index = -1;
  projects_shown = []

  let query = document.querySelector('#project_search_bar').value;

  for (let i = 0; i < projects_projectdata.length; ++i) {
    let project = projects_projectdata[i];
    contents = project.name + ';' + project.tags.reduce((a, b) => a + ';' + b, '') + ';' + project.description;
    if (contents.includes(query)) {
      projects_shown.push(i);
    }
  }
  if (projects_shown.length > 0) {
    set_active(projects_shown[0]);
  } else {
    set_active(-1);
  }
  return true;
}

function projectsearch_keydown(e) {
  if (e.keyCode === 38) {
    // arrow up
    let currIdx = projects_shown.findIndex((x) => x === projects_selected_index);
    if (currIdx != 0) {
      set_active(projects_shown[currIdx - 1]);
    }
    e.preventDefault();
    return false;
  } else if (e.keyCode === 40) {
    // arrow down
    let currIdx = projects_shown.findIndex((x) => x === projects_selected_index);
    if (currIdx != projects_shown.length - 1) {
      set_active(projects_shown[currIdx + 1]);
    }
    e.preventDefault();
    return false;
  }
  return true;
}

for (let i = 0; i < projects_projectdata.length; ++i) {
  projects_shown.push(i);
}
set_active(0);

document.querySelector('#project_search_bar').addEventListener('keydown', projectsearch_keydown);
document.querySelector('#project_search_bar').addEventListener('input', projectsearch);
