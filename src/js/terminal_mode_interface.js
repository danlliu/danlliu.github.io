
document.addEventListener('keydown', (e) => {
  if (e.key.length == 1) {
    _key_pressed(e.key.charCodeAt(0), e.ctrlKey, e.altKey, e.shiftKey, e.metaKey);
  } else if (e.key == 'Enter') {
    _key_pressed('\n'.charCodeAt(0), false, false, false, false);
  } else if (e.key == 'Tab') {
    _key_pressed('\t'.charCodeAt(0), false, false, false, false);
  } else if (e.key == 'Backspace') {
    _key_pressed('\b'.charCodeAt(0), false, false, false, false);
  }
});
