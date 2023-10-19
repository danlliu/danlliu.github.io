
// `.` link easter egg

DOT_CLICKED = 5;
function click_dot() {
  DOT_CLICKED += 1;
  if (DOT_CLICKED === 10) {
    let toc = document.querySelector('#banner_tableofcontents');
    toc.innerHTML += `  <span>.</span><span class="text-yellow">r</span><span class="text-red">w</span><span class="text-green">x</span><span class="text-yellow">r</span><span class="text-gray">-</span><span class="text-green">x</span><span class="text-yellow">r</span><span class="text-gray">-</span><span class="text-green">x</span> 1.4M <span>root  </span> <a href="/terminal_mode.html"><span class="text-darkgreen underline">.terminal_mode</span></a>`
    let terminal = document.querySelector('#banner_terminal');
    terminal.innerHTML = 'web terminal? &#x1F440;'
  }
}

console.log("why hello there!");
