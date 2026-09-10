# 🏏 Mini IPL Management System

A C-based and web-based application that helps users manage IPL team rosters.

The project includes a **terminal application written in C** and an interactive **web interface** built using HTML, CSS, and JavaScript. Users can view teams, search players, add or remove players, and transfer players between IPL teams.

---

## 🎯 Project Objective

Managing player information across multiple IPL teams can be difficult when the data is stored in separate files.

The **Mini IPL Management System** provides a simple solution by storing each team’s player roster in a text file. It allows users to manage player details such as name, jersey number, and playing role.

---

## ✨ Features

* 🏟️ View all 10 IPL teams
* 👥 Display players for a selected team
* 🔎 Search players by name, jersey number, or role
* ➕ Add a player to a team
* 🗑️ Remove a player using jersey number
* 🔄 Transfer a player between teams
* 🧾 Store player name, jersey number, and role
* 📁 Use text files for team roster data
* 🌐 Interactive web interface
* 💾 Save web changes locally in the browser
* 💻 Terminal-based C application

---

The project also includes an interactive web page for IPL roster management.

### Website Features

* Select and view IPL teams
* Search players by name, jersey number, or role
* Add new players to a roster
* Remove players from a roster
* Transfer players between teams
* Reset browser-saved changes

### Open the Website

🔗 **[Click here to open the IPL Roster Manager](https://kshiteejkadnar22-ai.github.io/mini-ipl-management-system/)**

The web page is built using:

| File | Purpose |
| ---- | ------- |
| `index.html` | Website structure |
| `styles.css` | Website design |
| `app.js` | Player management features |
| `*.txt` | IPL team player data |


## 🛠️ Technologies Used

| Technology | Purpose |
| ---------- | ------- |
| **C** | Terminal application logic |
| **File Handling** | Store and update player rosters |
| **HTML** | Webpage structure |
| **CSS** | Webpage styling and responsive design |
| **JavaScript** | Web application functionality |
| **Local Storage** | Save browser roster changes |

---

## 📂 Project Structure

```text
mini-ipl-management-system/
│
├── ipl_manager.c
├── Makefile
├── README.md
├── index.html
├── styles.css
├── app.js
│
├── csk.txt
├── mi.txt
├── rcb.txt
├── kkr.txt
├── srh.txt
├── rr.txt
├── dc.txt
├── pbks.txt
├── gt.txt
└── lsg.txt
