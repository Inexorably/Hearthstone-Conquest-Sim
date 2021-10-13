# Hearthstone-Conquest-Sim
This was created in Qt c++.  Note than when you are creating a release version that will be run outside of the Qt enviorment you will need to include the required dlls for your platform of choice.

Download: https://drive.google.com/file/d/0B6ssju5UMOQ-Y1BPQTd3Tmd2dFU/view?usp=sharing

Allows you to simulate any number of tournaments (swiss into top cut, conquest, best of 5), and then will order the different possible deck choice combinations by percentage of tournaments topped.

With this tool you are able to set your own tournament compositions (bias) and match up data, load compositions and match up data which other people have provided, and export the results table (the one in the gui) as a csv (openable in excel). If you do not add any extra tournament composition bias or change the default match up data, combinations of decks will be generated randomly with a Bernoulli distribution (so each combination will have the same chance of being played).

If you set a bias for a deck combination of 33%, then when generating the players for each tournament, each player will have a 33% of using that combination. If it does not use that combination, it will generate a random deck combination.

The available decks and default match up data are from TempoStorm's meta snapshot 42 (the latest).

When two players play, they each select the deck with the best overall matchup based on their and their opponent's remaining decks. When a player wins, that player may not use the winning deck again in a given round (conquest rules).

You can also change the number of players in a tournament. The top cut and number of swiss rounds are adjusted accordingly.

Clicking "highlight selected bias" will select the row with the selected bias in the results table.

![image](https://user-images.githubusercontent.com/16945020/137111102-1011e184-b605-4c37-939d-4d7bf6e5ed36.png)

![image](https://user-images.githubusercontent.com/16945020/137111121-7b5aeb4a-527f-4e97-8002-8638ac1c4f34.png)

![image](https://user-images.githubusercontent.com/16945020/137111137-ba287991-9031-4841-b1f2-530ba6f7eba1.png)
