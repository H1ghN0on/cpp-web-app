let isAdding = false;
let isEditing = false;

const NAME = localStorage.getItem("name");
const Item = (item) => `
  <li id=${item.id} class="item">
    <div class="item__wrapper">
      <span class="item__name">${item.text}</span>
      <div class="item__controls">
        <div class="item__control item__check">
          <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-check2" viewBox="0 0 16 16">
            <path d="M13.854 3.646a.5.5 0 0 1 0 .708l-7 7a.5.5 0 0 1-.708 0l-3.5-3.5a.5.5 0 1 1 .708-.708L6.5 10.293l6.646-6.647a.5.5 0 0 1 .708 0z"/>
          </svg>
        </div>
        <div class="item__control item__edit">
          <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-pen" viewBox="0 0 16 16">
            <path d="m13.498.795.149-.149a1.207 1.207 0 1 1 1.707 1.708l-.149.148a1.5 1.5 0 0 1-.059 2.059L4.854 14.854a.5.5 0 0 1-.233.131l-4 1a.5.5 0 0 1-.606-.606l1-4a.5.5 0 0 1 .131-.232l9.642-9.642a.5.5 0 0 0-.642.056L6.854 4.854a.5.5 0 1 1-.708-.708L9.44.854A1.5 1.5 0 0 1 11.5.796a1.5 1.5 0 0 1 1.998-.001zm-.644.766a.5.5 0 0 0-.707 0L1.95 11.756l-.764 3.057 3.057-.764L14.44 3.854a.5.5 0 0 0 0-.708l-1.585-1.585z"/>
          </svg>
        </div>
        <div class="item__control item__remove">
          <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-trash" viewBox="0 0 16 16">
            <path d="M5.5 5.5A.5.5 0 0 1 6 6v6a.5.5 0 0 1-1 0V6a.5.5 0 0 1 .5-.5zm2.5 0a.5.5 0 0 1 .5.5v6a.5.5 0 0 1-1 0V6a.5.5 0 0 1 .5-.5zm3 .5a.5.5 0 0 0-1 0v6a.5.5 0 0 0 1 0V6z"/>
            <path fill-rule="evenodd" d="M14.5 3a1 1 0 0 1-1 1H13v9a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V4h-.5a1 1 0 0 1-1-1V2a1 1 0 0 1 1-1H6a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1h3.5a1 1 0 0 1 1 1v1zM4.118 4 4 4.059V13a1 1 0 0 0 1 1h6a1 1 0 0 0 1-1V4.059L11.882 4H4.118zM2.5 3V2h11v1h-11z"/>
          </svg>
        </div>
      </div>
    </div>
  </li>`;

const NewItem = (item) => `<li id=${item && item.id} class="item new_item">
  <div class="item__wrapper">
      <input class="item__name_input" value="${
        item && item.text ? item.text : ""
      }" type="text"></input>
      <div class="item__controls">
        <div class="item__control item__check_add">
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-check2" viewBox="0 0 16 16">
              <path d="M13.854 3.646a.5.5 0 0 1 0 .708l-7 7a.5.5 0 0 1-.708 0l-3.5-3.5a.5.5 0 1 1 .708-.708L6.5 10.293l6.646-6.647a.5.5 0 0 1 .708 0z"/>
            </svg>
        </div>
      </div>
  </div>
</li>`;

const getItemControls = (node) => {
  const controls = $(node).find(".item__controls").children();
  return {
    check: controls[0],
    edit: controls[1],
    remove: controls[2],
  };
};

const getNewItemInput = (node) => {
  return $(node).find(".item__name_input");
};

const getItemNameNode = (node) => {
  return $(node).find(".item__name");
};

const getNewItemControls = (node) => {
  const controls = $(node).find(".item__controls").children();
  return {
    add: controls[0],
  };
};

const replaceWithEditItem = async (item, node) => {
  $(node).replaceWith(NewItem(item));
  const newNode = $("ul").find("#" + item.id);
  const newControls = getNewItemControls(newNode);
  $(newControls.add).click(async () => {
    const text = getNewItemInput(newNode).val();

    if (text) {
      const newItem = {
        id: item.id,
        text: text,
        isChecked: false,
      };
      const id = content.findIndex((item) => item.id == newItem.id);
      content[id] = newItem;
      await editNote(NAME, item.id, "text", newItem.text);
      $(newNode).replaceWith(Item(newItem));
      const oneMoreNode = $("ul").find("#" + newItem.id);
      setItemListeners(newItem, oneMoreNode);
    }
  });
};

const setItemListeners = (item, node) => {
  const controls = getItemControls(node);
  console.log(controls);
  $(controls.check).click(async () => {
    const id = content.findIndex((cont) => cont.id == item.id);
    await editNote(
      NAME,
      item.id,
      "isChecked",
      content[id].isChecked ? "false" : "true"
    );
    $(getItemNameNode(node)).css({
      textDecoration: content[id].isChecked ? "none" : "line-through",
    });
    content[id] = { ...content[id], isChecked: !content[id].isChecked };
  });

  $(controls.edit).click(async () => {
    await replaceWithEditItem(item, node);
  });

  $(controls.remove).click(async () => {
    await removeNote(NAME, item.id);

    node.remove();
  });
};

const renderContent = async () => {
  content = await getNotes();

  content.forEach((item) => {
    $(".list").append(Item(item));

    const node = $("ul").find("#" + item.id);
    $(getItemNameNode(node)).css({
      textDecoration: item.isChecked === "true" ? "line-through" : "none",
    });
    setItemListeners(item, node);
  });
};

const logout = () => {
  localStorage.removeItem("name");
  location.href = "http://localhost:3000/pages/profile.html";
};

$(".logout_btn").click(() => {
  logout();
});

$(".add_btn").click(() => {
  $(".list").append(NewItem());
  const node = $("ul").children().last();
  const controls = getNewItemControls(node);
  $(controls.add).click(async () => {
    const text = getNewItemInput(node).val();
    const submitBtn = $(".item__check_add");
    submitBtn.prop("disabled", true);
    const res = await addNote(text);
    if (text) {
      const newItem = {
        id: content.length + 1,
        text: text,
        isChecked: false,
      };
      content.push(newItem);

      $(node).replaceWith(Item(newItem));
      const oneMoreNode = $("ul").find("#" + newItem.id);
      setItemListeners(newItem, oneMoreNode);
    }
    submitBtn.prop("disabled", false);
  });
});

const editNote = async (name, id, field, value) => {
  const res = await fetch("http://localhost:3001/edit-note", {
    method: "POST",
    body:
      "body? name=" + NAME + "&id=" + id + "&field=" + field + "&text=" + value,
  });
  return res.status === 200;
};

const removeNote = async (name, id) => {
  const res = await fetch("http://localhost:3001/remove-note", {
    method: "POST",
    body: "body? name=" + NAME + "&id=" + id,
  });
  return res.status === 200;
};

const addNote = async (text) => {
  const res = await fetch("http://localhost:3001/add-note", {
    method: "POST",
    body: "body? name=" + NAME + "&text=" + text,
  });
  return res.status === 200;
};

const getNotes = async () => {
  if (!NAME) {
    location.href = "http://localhost:3000/pages/profile.html";
    return;
  }
  const res = await fetch("http://localhost:3001/get-notes", {
    method: "POST",
    body: `body? name=${NAME}`,
  });
  if (res.status === 200) {
    const json = await res.json();
    return await json.notes;
  } else {
    return [];
  }
};

let content = [];

renderContent();
