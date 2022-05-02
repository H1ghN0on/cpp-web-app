const input = document.getElementById("input");
const btn = document.getElementById("btn");

const createBody = (...args) => {
  let body = "body? ";
  args.forEach((arg) => {
    body += arg.name + "=" + arg.value + "& ";
  });
  return body.slice(0, -1);
};

const checkName = async (name) => {
  const res = await fetch("http://localhost:3001/check", {
    method: "POST",
    body: createBody({
      name: "name",
      value: name,
    }),
  });
  return res;
};

const sendMessage = async (name, text) => {
  const res = await fetch("http://localhost:3001/new-message", {
    method: "POST",
    body: createBody(
      {
        name: "name",
        value: name,
      },
      {
        name: "message",
        value: text,
      }
    ),
  });
  return res;
};

window.onload = async () => {
  const name = localStorage.getItem("name");

  if (name) {
    const data = await checkName(name);
    if (data.status == 200) {
      alert("I greet you");
    } else if (data.status == 405) {
      location.href = "index.html";
    }
  } else {
    location.href = "index.html";
  }
};

btn.addEventListener("click", async () => {
  const name = localStorage.getItem("name");
  if (name) {
    const res = await sendMessage(name, input.value);
    if (res.status == 200) alert("Message sent!");
  } else {
    location.href = "index.html";
  }
});

async function subscribe() {
  let response = await fetch("http://localhost:3001/get-message");

  if (response.status == 502) {
    // Status 502 is a connection timeout error,
    // may happen when the connection was pending for too long,
    // and the remote server or a proxy closed it
    // let's reconnect
    await subscribe();
  } else if (response.status != 200) {
    // An error - let's show it
    showMessage(response.statusText);
    // Reconnect in one second
    await new Promise((resolve) => setTimeout(resolve, 1000));
    await subscribe();
  } else {
    // Get and show the message
    let message = await response.text();
    showMessage(message);
    // Call subscribe() again to get the next message
    await subscribe();
  }
}
