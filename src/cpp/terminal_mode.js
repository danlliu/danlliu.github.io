addToLibrary({
  set_terminal: function(str) {
    document.querySelector('#text-content').innerHTML = UTF8ToString(str);
    _free(str);
  }
})