# ELOtoHTML
---

Trans the <a href="https://github.com/EbTech/Elo-MMR" target="_blank">ELO-MMR</a> system's result to a HTML page.

Demo site: <a href="https://beta.ac.cn/rank/" target="_blank">BETA RANK</a>


## How to use

1. Prepare and paste the `result.csv` to this folder.
2. Compile `trans_to_json.cpp` and run it.
3. Rename the new file `*.json` and move it into ELO-MMR system, then run the system.
4. Copy `all_players.csv` to this folder, compile `make_index.cpp` and run it.
