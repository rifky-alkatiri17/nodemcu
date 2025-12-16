document.addEventListener('DOMContentLoaded', () => {
  // cara 1
  document.querySelector('.on').onclick = () => fetch('/on');
  document.querySelector('.off').onclick = () => fetch('/off');

  // cara 2
  /*document.addEventListener('click', (e) => {
    if (e.target.classList.contains('on')) {
      e.preventDefault();
      fetch('/on');
    }

    if (e.target.classList.contains('off')) {
      e.preventDefault();
      fetch('/off');
    }
  });*/

  setInterval(() => {
    fetch('/sensor')
      .then(r => r.text())
      .then(d => sensor.innerText = d);
  }, 1000);
});
