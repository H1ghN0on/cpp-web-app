const btn = document.getElementById("btn");
const input = document.getElementById("input");
const block = document.getElementById("block");

var oReq = new XMLHttpRequest();

//TODO DISCONNECTS

const createBody = (...args) => {
  let body = "body? ";

  args.forEach((arg) => {
    body += arg.name + "=" + arg.value + "&";
  });
  return body.slice(0, -1);
};

const login = async (name) => {
  const res = await fetch("http://localhost:3001/login", {
    method: "POST",
    body: createBody({
      name: "name",
      value: input.value,
    }),
  });
  return res;
};

btn.addEventListener("click", async () => {
  const data = await login(input.value);
  if (data.status == 405) {
    localStorage.removeItem("name");
    alert("That username already exists");
  } else if (data.status == 200) {
    localStorage.setItem("name", input.value);
    location.href = "chat.html";
  }
});
