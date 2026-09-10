#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_ROLE 200
#define MAX_LINE 300

#define TEAM_COUNT 10
#define ROLE_COUNT 14

char teamNames[TEAM_COUNT][40] = {
    "Chennai Super Kings",
    "Mumbai Indians",
    "Royal Challengers Bengaluru",
    "Kolkata Knight Riders",
    "Sunrisers Hyderabad",
    "Rajasthan Royals",
    "Delhi Capitals",
    "Punjab Kings",
    "Gujarat Titans",
    "Lucknow Super Giants"
};

char teamFiles[TEAM_COUNT][30] = {
    "teams/csk.txt",
    "teams/mi.txt",
    "teams/rcb.txt",
    "teams/kkr.txt",
    "teams/srh.txt",
    "teams/rr.txt",
    "teams/dc.txt",
    "teams/pbks.txt",
    "teams/gt.txt",
    "teams/lsg.txt"
};

char rolesList[ROLE_COUNT][40] = {
    "Right Handed Batsman",
    "Left Handed Batsman",
    "Wicketkeeper",
    "Right Arm Fast",
    "Left Arm Fast",
    "Right Arm Medium",
    "Left Arm Medium",
    "Right Arm Medium Fast",
    "Left Arm Medium Fast",
    "Right Arm Off Spin",
    "Left Arm Off Spin",
    "Left Arm Orthodox Spin",
    "Right Arm Leg Spin",
    "Left Arm Wrist Spin (Chinaman)"
};

void remove_newline(char *s) {
    int len = (int)strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

int read_int() {
    char buf[50];
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;
    return atoi(buf);
}

void show_teams() {
    int i;
    printf("\nTeams:\n");
    for (i = 0; i < TEAM_COUNT; i++) {
        printf("%d. %s\n", i + 1, teamNames[i]);
    }
    printf("\n");
}

int select_team() {
    int t;
    show_teams();
    printf("Enter team number: ");
    t = read_int();
    if (t < 1 || t > TEAM_COUNT) {
        printf("Invalid team number.\n");
        return -1;
    }
    return t - 1;
}

int jersey_from_line(char *line) {
    char *p;
    int jersey = -1;
    p = strstr(line, "Jersey Number:");
    if (p == NULL) {
        return -1;
    }
    p = p + strlen("Jersey Number:");
    while (*p == ' ' || *p == '\t') {
        p++;
    }
    jersey = atoi(p);
    return jersey;
}

int jersey_exists_in_team(int teamIndex, int jersey) {
    FILE *f;
    char line[MAX_LINE];
    int j;

    f = fopen(teamFiles[teamIndex], "r");
    if (f == NULL) {
        return 0;
    }
    while (fgets(line, sizeof(line), f) != NULL) {
        j = jersey_from_line(line);
        if (j == jersey) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void show_team_players(int teamIndex) {
    FILE *f;
    char line[MAX_LINE];
    int count = 0;

    f = fopen(teamFiles[teamIndex], "r");
    if (f == NULL) {
        printf("Could not open file %s\n", teamFiles[teamIndex]);
        return;
    }

    printf("\n=== %s ===\n", teamNames[teamIndex]);
    while (fgets(line, sizeof(line), f) != NULL) {
        remove_newline(line);
        if (strlen(line) == 0) {
            continue;
        }
        printf("%s\n", line);
        count++;
    }
    fclose(f);
    printf("Total players: %d\n\n", count);
}

void build_roles_string(char *outRoles) {
    int i;
    int howMany;
    int roleNo;

    outRoles[0] = '\0';

    printf("\nSelect roles for the player.\n");
    printf("You can choose multiple roles.\n\n");
    for (i = 0; i < ROLE_COUNT; i++) {
        printf("%2d. %s\n", i + 1, rolesList[i]);
    }

    printf("\nHow many roles do you want to add? ");
    howMany = read_int();

    if (howMany <= 0) howMany = 1;
    if (howMany > ROLE_COUNT) howMany = ROLE_COUNT;

    for (i = 1; i <= howMany; i++) {
        printf("Enter role number %d: ", i);
        roleNo = read_int();

        if (roleNo < 1 || roleNo > ROLE_COUNT) {
            printf("Invalid role number. Default role added.\n");
            roleNo = 1;
        }

        if (strlen(outRoles) > 0) strcat(outRoles, ", ");
        strcat(outRoles, rolesList[roleNo - 1]);
    }
}

void add_player(int teamIndex) {
    char name[MAX_NAME];
    char roles[MAX_ROLE];
    int jersey;
    FILE *f;

    printf("Enter player name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        return;
    }
    remove_newline(name);
    if (strlen(name) == 0) {
        printf("Name cannot be empty.\n");
        return;
    }

    printf("Enter jersey number: ");
    jersey = read_int();
    if (jersey <= 0) {
        printf("Invalid jersey number.\n");
        return;
    }
    if (jersey_exists_in_team(teamIndex, jersey)) {
        printf("Jersey number already exists in this team.\n");
        return;
    }

    build_roles_string(roles);

    f = fopen(teamFiles[teamIndex], "a");
    if (f == NULL) {
        printf("Could not open file %s\n", teamFiles[teamIndex]);
        return;
    }
    fprintf(f, "Player Name: %s | Jersey Number: %d | Role: %s\n", name, jersey, roles);
    fclose(f);
    printf("Player added to %s.\n", teamNames[teamIndex]);
}

int remove_player_from_team(int teamIndex, int jersey, char *removedLine) {
    FILE *in;
    FILE *out;
    char tmpFile[40];
    char line[MAX_LINE];
    int removed = 0;

    in = fopen(teamFiles[teamIndex], "r");
    if (in == NULL) {
        return 0;
    }

    strcpy(tmpFile, "teams/temp.txt");
    out = fopen(tmpFile, "w");
    if (out == NULL) {
        fclose(in);
        return 0;
    }

    while (fgets(line, sizeof(line), in) != NULL) {
        int j = jersey_from_line(line);
        if (!removed && j == jersey) {
            removed = 1;
            if (removedLine != NULL) {
                remove_newline(line);
                strcpy(removedLine, line);
            }
            continue;
        }
        fputs(line, out);
    }

    fclose(in);
    fclose(out);

    if (!removed) {
        remove(tmpFile);
        return 0;
    }

    remove(teamFiles[teamIndex]);
    rename(tmpFile, teamFiles[teamIndex]);
    return 1;
}

void remove_player_menu() {
    int teamIndex;
    int jersey;

    teamIndex = select_team();
    if (teamIndex == -1) {
        return;
    }

    printf("Enter jersey number to remove: ");
    jersey = read_int();

    if (remove_player_from_team(teamIndex, jersey, NULL)) {
        printf("Player removed from %s.\n", teamNames[teamIndex]);
    } else {
        printf("Player not found in %s.\n", teamNames[teamIndex]);
    }
}

void transfer_player_menu() {
    int fromIndex;
    int toIndex;
    int jersey;
    char line[MAX_LINE];

    printf("Select FROM team:\n");
    fromIndex = select_team();
    if (fromIndex == -1) {
        return;
    }

    printf("Select TO team:\n");
    toIndex = select_team();
    if (toIndex == -1) {
        return;
    }

    if (fromIndex == toIndex) {
        printf("Source and destination team cannot be same.\n");
        return;
    }

    printf("Enter jersey number to transfer: ");
    jersey = read_int();

    if (jersey_exists_in_team(toIndex, jersey)) {
        printf("Destination team already has this jersey number.\n");
        return;
    }

    if (!remove_player_from_team(fromIndex, jersey, line)) {
        printf("Player not found in source team.\n");
        return;
    }

    FILE *f = fopen(teamFiles[toIndex], "a");
    if (f == NULL) {
        printf("Could not open destination file.\n");
        return;
    }
    fprintf(f, "%s\n", line);
    fclose(f);

    printf("Player transferred from %s to %s.\n",
           teamNames[fromIndex], teamNames[toIndex]);
}

void ensure_files_exist() {
    int i;
    for (i = 0; i < TEAM_COUNT; i++) {
        FILE *f = fopen(teamFiles[i], "r");
        if (f == NULL) {
            f = fopen(teamFiles[i], "w");
        }
        if (f != NULL) {
            fclose(f);
        }
    }
}

void menu() {
    printf("=== Mini IPL Management System (Basic C, File Handling) ===\n");
    printf("1. View Teams\n");
    printf("2. View Players of a Team\n");
    printf("3. Add Player to a Team\n");
    printf("4. Remove Player from a Team\n");
    printf("5. Transfer Player between Teams\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}

int main() {
    int choice;
    int t;

    ensure_files_exist();

    while (1) {
        menu();
        choice = read_int();

        if (choice == 1) {
            show_teams();
        } else if (choice == 2) {
            t = select_team();
            if (t != -1) {
                show_team_players(t);
            }
        } else if (choice == 3) {
            t = select_team();
            if (t != -1) {
                add_player(t);
            }
        } else if (choice == 4) {
            remove_player_menu();
        } else if (choice == 5) {
            transfer_player_menu();
        } else if (choice == 6) {
            printf("Goodbye.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

