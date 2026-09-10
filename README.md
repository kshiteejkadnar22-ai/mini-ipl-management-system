# 🏏 Mini IPL Management System

A C-based and web-based application for managing IPL team rosters.

The project includes a **terminal application written in C** and an interactive **web application** built with HTML, CSS, and JavaScript. Users can view teams, search players, add or remove players, and transfer players between IPL teams.

---

## 🎯 Project Objective

Managing player information across multiple IPL teams can be difficult when the data is stored in separate files.

The **Mini IPL Management System** provides a simple solution by storing each team's player roster in a text file. It allows users to manage player details such as player name, jersey number, and playing role.

---

## ✨ Project Highlights

* 🏟️ Includes all **10 IPL teams**
* 💻 Provides both a **C terminal program** and a **web interface**
* 📁 Uses text files to store roster data
* 🔎 Supports player search by name, jersey number, or role
* ➕ Allows adding new players
* 🗑️ Allows removing players from a team
* 🔄 Supports player transfers between teams
* 💾 Saves web changes locally in the browser
* 🎨 Includes a responsive and user-friendly design
* ⚡ Lightweight project with no external dependencies

---

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
```

---

## 🏏 IPL Teams Included

| No. | Team |
| --- | ---- |
| 1 | Chennai Super Kings |
| 2 | Mumbai Indians |
| 3 | Royal Challengers Bengaluru |
| 4 | Kolkata Knight Riders |
| 5 | Sunrisers Hyderabad |
| 6 | Rajasthan Royals |
| 7 | Delhi Capitals |
| 8 | Punjab Kings |
| 9 | Gujarat Titans |
| 10 | Lucknow Super Giants |

---

## 🧾 Player Data Format

```text
Player Name: Virat Kohli | Jersey Number: 18 | Role: Right Handed Batsman
```

Each team has its own roster file.

---

## 🔄 How the Application Works

```text
              ┌──────────────────┐
              │       User       │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │  Select a Team   │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │  Load Team File  │
              └────────┬─────────┘
                       │
          ┌────────────┼────────────┐
          │            │            │
          ▼            ▼            ▼
     View Players  Add Player   Remove Player
          │            │            │
          └────────────┴────────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Transfer Player  │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Update Roster    │
              └──────────────────┘
```

---

## 🌐 Web Application

The project includes an interactive website for IPL roster management.

### Website Features

* Select and view IPL teams
* Search players by name, jersey number, or role
* Add new players to a roster
* Remove players from a roster
* Transfer players between teams
* Reset browser-saved changes

### Open the Website

🔗 **[Click here to open the IPL Roster Manager](https://kshiteejkadnar22-ai.github.io/mini-ipl-management-system/)**

| File | Purpose |
| ---- | ------- |
| `index.html` | Website structure |
| `styles.css` | Website design |
| `app.js` | Player management functionality |
| `*.txt` | IPL team player data |

---

## 💻 C Terminal Application

```text
1. View Teams
2. Search a Team
3. Add Player to a Team
4. Remove Player from a Team
5. Transfer Player
6. Exit
```

---

## ⚙️ How to Run the C Program

```bash
make
./ipl_manager
```

Or use:

```bash
make run
```

---

## 🚀 Future Scope

The project can be improved in the future by adding:

* User login and authentication
* A database such as MySQL or MongoDB
* Player profile photos
* Team logos and IPL-themed visuals
* Player statistics such as runs, wickets, and matches
* Sorting players by role, age, or jersey number
* A dashboard with team-wise charts and analytics
* Cloud-based storage for roster updates
* Admin and user roles
* Mobile application support

---

## 👨‍💻 Author

**Kshiteej Kadnar**

Mini project created for IPL team and player roster management.

---

## 📄 License

This project is created for **educational purposes**.

No formal open-source license has been added yet.
