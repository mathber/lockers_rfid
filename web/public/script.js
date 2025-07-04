firebase.initializeApp(firebaseConfig);

const db = firebase.database();
const lockersRef = db.ref("lockers");

lockersRef.on("value", (snapshot) => {
    const data = snapshot.val();
    const lockersDiv = document.getElementById("lockers");
    lockersDiv.innerHTML = "";

    if (data) {
        for (const key in data) {
            const locker = data[key];
            const status = locker.status === "closed" ? "closed" : "open";
            const imageSrc = `${status}.jpg`;

            const div = document.createElement("div");
            div.className = "locker";
            div.innerHTML = `
      <img src="${imageSrc}" alt="${status}" />
      <p><b>Armário:</b> ${locker.id}</p>
      <p><b>UID:</b> ${locker.uid}</p>
      `;
            lockersDiv.appendChild(div);
        }
    } else {
        lockersDiv.innerHTML = "<p>Nenhum armário cadastrado.</p>";
    }
});
