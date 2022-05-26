const NAME = localStorage.getItem("name");

if (NAME) {
  location.href = "http://localhost:3000/pages/index.html";
}

$(".submit").click((e) => {
  e.preventDefault();
  const name = $(".input").val();
  localStorage.setItem("name", name);
  location.href = "http://localhost:3000/pages/index.html";
});
