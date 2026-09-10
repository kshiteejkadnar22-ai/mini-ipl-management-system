async function loadInitialRosters() {
  const saved = localStorage.getItem(storageKey);
  if (saved) return JSON.parse(saved);

  const responses = await Promise.all(teams.map(async ({ id }) => {
    let response = await fetch(`teams/${id}.txt`);

    if (!response.ok) {
      response = await fetch(`${id}.txt`);
    }

    if (!response.ok) throw new Error(`Could not load ${id}.txt`);

    return [
      id,
      (await response.text()).split("\n").map(parsePlayer).filter(Boolean)
    ];
  }));

  return Object.fromEntries(responses);
}function render() {
  const team = currentTeam();
  const query = $("#search-input").value.trim().toLowerCase();
  const players = rosters[activeTeam] || [];
  const shown = players.filter((player) => `${player.name} ${player.jersey} ${player.roles}`.toLowerCase().includes(query));
  $("#team-title").textContent = team.name;
  $("#team-code").textContent = team.id;
  $("#player-count").textContent = players.length;
  roster.innerHTML = shown.length ? shown.map((player) => `
    <article class="player-card">
      <span class="jersey">Jersey no. ${player.jersey}</span>
      <h3>${escapeHtml(player.name)}</h3>
      <p class="roles">${escapeHtml(player.roles)}</p>
      <div class="card-actions">
        <button class="text-button" data-transfer="${player.jersey}" type="button">Transfer</button>
        <button class="text-button danger" data-remove="${player.jersey}" type="button">Remove</button>
      </div>
    </article>`).join("") : `<p class="empty">No players match this search.</p>`;
}

function populateSelects() {
  select.innerHTML = teams.map((team) => `<option value="${team.id}">${team.name}</option>`).join("");
  $("#destination-team").innerHTML = teams.map((team) => `<option value="${team.id}">${team.name}</option>`).join("");
  select.value = activeTeam;
}

$("#add-button").addEventListener("click", () => { $("#form-error").textContent = ""; $("#player-form").reset(); $("#player-dialog").showModal(); });
document.querySelectorAll("[data-close]").forEach((button) => {
  button.addEventListener("click", () => document.getElementById(button.dataset.close).close());
});
$("#player-form").addEventListener("submit", (event) => {
  event.preventDefault();
  const form = new FormData(event.currentTarget);
  const player = { name: form.get("name").trim(), jersey: Number(form.get("jersey")), roles: form.get("roles").trim() };
  const error = $("#form-error");
  if (!player.name || !player.roles || player.jersey < 1) { error.textContent = "Please provide a name, a positive jersey number, and at least one role."; return; }
  if (rosters[activeTeam].some((item) => item.jersey === player.jersey)) { error.textContent = "That jersey number already exists in this team."; return; }
  rosters[activeTeam].push(player); save(); $("#player-dialog").close(); render(); flash(`${player.name} was added to ${currentTeam().name}.`);
});

roster.addEventListener("click", (event) => {
  const jersey = Number(event.target.dataset.remove || event.target.dataset.transfer);
  if (!jersey) return;
  const player = rosters[activeTeam].find((item) => item.jersey === jersey);
  if (event.target.dataset.remove) {
    if (confirm(`Remove ${player.name} from ${currentTeam().name}?`)) { rosters[activeTeam] = rosters[activeTeam].filter((item) => item.jersey !== jersey); save(); render(); flash(`${player.name} was removed.`); }
  } else { pendingTransfer = player; $("#transfer-player-name").textContent = `Transfer ${player.name}`; $("#transfer-error").textContent = ""; $("#destination-team").value = teams.find((team) => team.id !== activeTeam).id; $("#transfer-dialog").showModal(); }
});

$("#transfer-form").addEventListener("submit", (event) => {
  event.preventDefault(); const destination = $("#destination-team").value; const error = $("#transfer-error");
  if (destination === activeTeam) { error.textContent = "Choose a different destination team."; return; }
  if (rosters[destination].some((item) => item.jersey === pendingTransfer.jersey)) { error.textContent = "The destination team already uses this jersey number."; return; }
  rosters[activeTeam] = rosters[activeTeam].filter((item) => item.jersey !== pendingTransfer.jersey); rosters[destination].push(pendingTransfer); save(); $("#transfer-dialog").close(); render(); flash(`${pendingTransfer.name} was transferred to ${teams.find((team) => team.id === destination).name}.`);
});

select.addEventListener("change", () => { activeTeam = select.value; render(); });
$("#search-input").addEventListener("input", render);
$("#reset-button").addEventListener("click", () => { if (confirm("Reset all roster changes saved in this browser?")) { localStorage.removeItem(storageKey); location.reload(); } });

(async function init() {
  try { rosters = await loadInitialRosters(); populateSelects(); render(); }
  catch (error) { $("#team-title").textContent = "Unable to load roster data"; roster.innerHTML = `<p class="empty">Run this project from a local web server (for example, <code>python3 -m http.server</code>) instead of opening the file directly.</p>`; console.error(error); }
})();
