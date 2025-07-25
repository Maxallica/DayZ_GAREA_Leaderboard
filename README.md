## GAREA_Leaderboard ##
# GAREA Leaderboard

A lightweight leaderboard system for Day-Z that supports both **PVP** and **PVE** modes.  
✅ Completely free for the Day-Z Community ♥  
✅ No cloud service required — all processing done directly by the Day-Z server.

---

## 📌 Features

### 🧍‍♂️ PVP Leaderboard
- Position
- Player name
- Survived time
- Longest distance
- Kills
- Deaths
- Kill/Death ratio
- Points

### 🌲 PVE Leaderboard
- Position
- Player name
- Deaths
- Survived time
- AI Survivor kills
- Zombie kills
- Animal kills (broken down by type)
- Total NPC kills
- Points

### 📊 Shared Functionality
- Compare your stats with **Top X** players (X = 1–100)

---

## 🎯 Tracking System

- **Kill types:**
  - Grenade (distance included)
  - Trap (BearTrap and LandMine – includes trap-to-victim distance)
  - Car (CarScript – distance not included)
  - Weapon (distance included)
  - Unarmed (distance not included)
  - Unknown (distance not included)

- **Death types:**
  - Suicide, grenade, trap, zombie, animal, car, weapon, unarmed, unknown  
  _(Distance tracked only for PVP deaths)_

---

## 🎮 Controls

- Press **O** to open the PVP leaderboard  
- Press **I** to open the PVE leaderboard  
- Customize these keys via control settings

➡️ Look for:
- `"Open PVP Leaderboard"`
- `"Open PVE Leaderboard"`

---

## 🗂️ Player Database

Each player gets a dedicated JSON file.

- **Location:**  
  `...\Steam\steamapps\common\DayZServer\profiles\GAREALeaderboard\PlayerDB\`

---

## ⚙️ Server Configuration

- **Config File Path:**  
  `..\Steam\steamapps\common\DayZServer\profiles\GAREALeaderboard\GAREALeaderboardConfig.json`

- Reloads:
  - On server restart
  - In-game via **Admin Panel** ➜ `Reload config` button

- Manual creation requirements:
  - Must be encoded as **ASCII**
  - Each property must end with a **single line break `/n`**
  - No trailing line break after the closing `}` character

---

## 🧮 Point System

| Event                        | Points |
|-----------------------------|--------|
| Player kills another player | +100   |
| Player kills NPC (animal/zombie/AI) | +10   |
| Player gets killed          | –1     |

---

## 🛡️ Admin Panel Functions

- `Reload config`: Apply config changes made directly in the config file
- `Reload all player files`: Apply changes made to player stats files
- `Reset all players (PVP)`: Wipe all PVP leaderboard stats
- `Reset all players (PVE)`: Wipe all PVE leaderboard stats
- `Delete obsolete offline players (0 K/D)`: Cleanup players with no activity

---

## 🛠️ Development Guide (for Mod Developers)

### 🧩 Required Installations
- Install **DayZ**
- Install **DayZServer**
- Install **DayZ Tools**
- Install **Hard-Link Shell Extension**:  
  [Link Shell Extension](https://schinagl.priv.at/nt/hardlinkshellext/linkshellextension.html)
- Install **PBO Manager** (for unpacking `.pbo` files):  
  [PBO Manager GitHub](https://github.com/winseros/pboman3/releases)

---

### ⚙️ DayZ Tools Setup
Open **DayZ Tools** and go to **Settings**:
- Set `Drive Letter`: `P:\`
- Set `Path to the Project Drive`: ➜ to a folder of your choice
- Set `Path to the Game Directory`: ➜ your DayZ installation path
- Enable `[X] Automatic mount of the Project Drive`

Under **Tools**, run:
- `Mount Drive P:\`
- `Extract Game Data` (⚠️ may take some time)

---

### 🔄 Batch File Setup
Copy the necessary `.bat` files into the following paths:

| Application   | Destination Path                                       |
|---------------|--------------------------------------------------------|
| DayZ          | `..\Steam\steamapps\common\DayZ`                       |
| DayZServer    | `..\Steam\steamapps\common\DayZServer`                 |
| Workshop      | `..\Steam\steamapps\common\DayZ Tools\Bin\Workbench`   |

Then create shortcuts for each `.bat` file in the mounted `P:\` directory.

---

### 🔗 Symbolic Links
Create symbolic links:
- Your mod ➜ root of DayZ folder
- Your mod ➜ root of DayZServer folder
- `!Workshop` folder ➜ root of DayZServer folder

To debug DayZ internal classes:
- Link the `scripts` folder ➜ root of both DayZ and DayZServer folders

---

### 📝 Batch File Preparation
- Right-click the `.bat` files or shortcuts ➜ open with Notepad
- Add your mod under `mods`
- For `WorkbenchCurrentMod`, insert `-mod=` followed by your mod folder path

> ⚠️ For packed `.pbo` files:  
Copy the mod folder to `P:\`, then create symbolic links to DayZ and DayZServer root directories.  
Update the `.bat` files afterwards.

---

### 🐞 Debugging
- Launch `WorkbenchCurrentMod.bat`
- Double-click a `.c` file to open it in the Script Editor
- Set breakpoints in the file

Select the mode from the Debug menu:
- `Debug Server` or `Debug Client`

Then:
- Launch **DayZ**
- Launch **DayZServer**

Use **Recompile File on Host** to apply live changes while server/client is running.

---

### 📦 Building & Packing Mods
- Open **Addon Builder**
- Select your mod directory
- Build a `.pbo` with `.bikey`

The `.bikey` is found at:  
`..\Steam\steamapps\common\DayZ Tools\Bin\DsUtils\`

**Mod structure:**

@YourMod/
├── addons/
├── keys/
└── mod.cpp

---

### 🖼️ Image Conversion
Use **Image To PAA** via **DayZ Tools** to convert textures.

---

### 🧰 Troubleshooting

#### Workbench Error
**Error:** "Game is not installed... Exiting"  
👉 Launch DayZ once up to the main menu, then close it.

#### VPPAdminTools Crash
**Fix:** Add launch parameter to DayZDiag_x64:
```bash
-newErrorsAreWarnings=1
```

## 📦 Miscellaneous / Other Settings

### 🚫 `mod.cpp` Warning
- The file `mod.cpp` can block mod loading when `-filePatching` is active.
- Always **move or remove** `mod.cpp` when using file patching for debugging.

---

### 🔁 Key Game Files
| File            | Purpose                                      |
|-----------------|----------------------------------------------|
| `config.cpp`    | Entry point for Workbench, DayZ, and DayZServer |
| `stringtable.csv` | Localization / translation file               |
| `mod.cpp`       | Contains mod metadata (shown in client)      |
| `input.xml`     | Mod-specific input bindings for main menu    |

---

### 🧩 Server Configuration

Located at:  
`..\Steam\steamapps\common\DayZServer\serverDZ.cfg`

```cfg
BattlEye = 0;             // Disable BE, diagnostic exe won’t run with it
verifySignatures = 0;     // Use if testing unsigned mods
allowFilePatching = 1;    // Enable file patching for mod dev
```

### 🐾 Animal Spawn Rate
Adjust animal population by editing:  
`..\Steam\steamapps\common\DayZServer\mpmissions\dayzOffline.chernarusplus\db\events.xml`

---

### 🌍 Global Server Settings
Modify settings in:  
`..\Steam\steamapps\common\DayZServer\mpmissions\dayzOffline.chernarusplus\db\globals.xml`

Key parameters:
```xml
<var name="TimeLogin" type="15" value="0"/>    // Sets login delay to 0 seconds
<var name="TimeLogout" type="15" value="0"/>   // Sets logout delay to 0 seconds
```

---

## 🔐 VPP Admin Configuration

Set up administrator access for VPPAdminTools by editing the following files and settings:

---

### 📁 Permissions File Paths

| File Location                                                                                          | Description                              |
|--------------------------------------------------------------------------------------------------------|------------------------------------------|
| `..\Steam\steamapps\common\DayZServer\profiles\VPPAdminTools\Permissions\SuperAdmins\SuperAdmins.txt` | ✅ Defines super administrator accounts   |
| `..\Programme\Steam\steamapps\common\DayZServer\profiles\VPPAdminTools\Permissions\credentials.txt`   | 🔑 Stores login credentials for VPP tool |

> 🧭 Note: The `Programme` path may vary based on system language or Steam directory — check both locations if unsure.

---

### 🔑 Admin Password in serverDZ.cfg

Configure the server’s admin password in:
..\Steam\steamapps\common\DayZServer\serverDZ.cfg

Set the following parameter:
```cfg
passwordAdmin = "yourSecureAdminPassword";
```

## ⏱️ Login/Logout Time Configuration

To modify the login and logout time settings for your DayZ server:

### 📂 File Location
..\Steam\steamapps\common\DayZServer\mpmissions\dayzOffline.chernarusplus\db\globals.xml

### ⚙️ XML Variables
Inside the `globals.xml` file, locate or add the following entries:
```xml
<var name="TimeLogin" type="15" value="0"/>    <!-- Time for login (in seconds) -->
<var name="TimeLogout" type="15" value="0"/>   <!-- Time for logout (in seconds) -->
```
---

Thanks for supporting the Day-Z community! ❤