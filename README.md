# **<ins>Abschlussprojekt</ins>**
### _Mondrian Blocks_

&nbsp;

# Spielregeln

Mondrian Blocks ist ein Einzelspieler Spiel. Das Spiel besteht darin, 8 verschiedene Rechtecke passend in ein 8x8 Spielfeld zu puzzeln.
Bei Spielbeginn sind in dem Spielfeld 3 Spielblöcke enthalten. 

Es gibt die Auswahl zwischen unterschiedlichsten Spielfeldern, die vom Spieler gelöst werden können. 
Dabei sind in jedem Spielfeld die Anfangsblöcke unterschiedlich plaziert.

Beispiel:
&nbsp;

<img src = "/pictures/EasyGrid.png"
	width = "200"
	height = "200"/> &nbsp;&nbsp;&nbsp;&#129154;&nbsp;&nbsp;&nbsp; <img src = "/pictures/FinishedGrid.png"
	width = "200"
	height = "200"/>
 

&nbsp;
[MondrianBlocks](https://mondrianblocks.com/) - Offizielle Seite des Spiels
&nbsp;
# Umsetzung
&nbsp;
### Klassen

|**Klassenname**|**Funktion**|
|----------|--------|
|Blocks| - Charakterisierung der Blöcke, mit denen gespielt wird|
|Grid| - Spielfeld, in dem gespielt wird|
|Game| - Ausführen des Spiels|
|Solver| - automatisches Lösen eines Spielfeldes|
|UserInterface| - zuständig für die Menüführung des Spiels|
|Renderer| - Erstellung graphical user interfaces (GUI)|
|Filehandler| - Einlesen der Größe des Spielfeldes und vorgegebener Spielfelder aus einer Textdatei|

### Bibliotheken

Für die Erstellung eines User Inferfaces wurden folgende Bibliotheken eingebunden:

- [SDL](https://github.com/libsdl-org/SDL):
	- Erstellen eines graphical user interfaces (GUI), auf dem gespielt wird.
- [SDL_ttf](https://github.com/libsdl-org/SDL_ttf):
	- Einbinden von Textfeldern in die GUI.
	

### Umsetzung Spielfeld

Es gibt **11** verschiedene Blöcke, die in einem Spielfeld plaziert werden müssen: 3 schwarze Blöcke, die zu Beginn plaziert sind; 8 farbige Blöcke, die vom Spieler plaziert werden.
Ein Spielfeld wird implementiert in der Klasse _Grid_. Jedes Spielfeld beinhaltet:
&nbsp;- Vector an Blöcken, die sich im Grid befinden
&nbsp;- Vector an Blöcken, die noch nicht plaziert wurden
&nbsp;- Vector an SDL-Rechtecken (werden für die Umsetzung der GUI benötigt)
&nbsp;- ein Vector _grid_, der aus den plazierten Blöcken besteht

SDL arbeitet mit Rechtecken, die in der GUI angezeigt werden. Es gibt die Möglichkeit verschiedene Aktionen mit diesen Rechtecken auszuführen (z.B. auf sie zu klicken).
Die Rechtecke werden in der Klasse _Blocks_ erstellt, sodass jedem Block ein Rechteck zugeordnet ist, das in der GUI angezeigt und verschoben werden kann.

Aus einer Textdatei werden im _Filehandler_ vorgegebene Spielfelder ausgelesen und erstellt. In diesen wurden bereits die 3 schwarzen Blöcke plaziert.
Wird ein Spielfeld in einem anderen Zusammenhang erstellt, ohne dass die Plazierung der schwarzen Blöcke bekannt ist, wird ein leeres Spielfeld erstellt. Die schwarzen Blöcke befinden sich entspechend noch in dem Vector der nicht plazierten Blöcken.

### Ablauf des Programms

Das Startmenü wird durch die Klasse UserInterface erstellt: "UserInterface::_showMenu_". Von dort aus gibt es die Möglichkeit zwischen den Modi _Play_ und _Solve_. 
Die Menüführung gelingt über Buttons, die durch die Renderer-Klasse erstellt werden. Alle Aktionen, die der Nutzer ausführt, werden mit Hilfe von sogenanten SDL-Events gehandelt. In diesen Events wird überprüft, ob der Spieler auf einen der Buttons gedrückt hat und wenn ja, auf welchen. Im Anschluss wird der Spieler zum nächsten Menü weitergeleitet:

Es folgt in beiden Modi der Aufruf der Funktion _chooseGrid_ in der Klasse user Interface. Hier hat der Spieler die Möglichkeit eines der vorgegebenen Spielfeldern auszuwählen. Es kann auch ein neues Spielfeld automatisch oder von Hand erstellt werden. Nach Auswahl eines Spielfeldes wird der Spieler, abhängig vom zuvor ausgewählten Spielmodus, weitergeleitet.

**Button Play &rarr;** &nbsp;Das Spiel wird nun gestartet. Für diesen Spielmodus ist die Klasse _Game_ zuständig. 
Die Funktion _run_ wird so lange ausgeführt, bis das Spiel gewonnen wurde. Die Funktion ist für das Handeln des Spielers zuständig, bzw das Auswerten der Aktionen, die er ausführt. Darunter fallen das Auswählen und  Plazieren eines Blockes. Die Aktionen, die der Spieler tätigen kann, werden durch einzelne _Eventtypen_ repräsentiert. Diese führen widerum Funktionen aus, die das Handeln des Spielers umsetzten.
Nach beenden des Spiels folgt eine UserIterface-Funktion _wonGame_, die den Spieler fragt, ob erneut gespielt werden möchte. Die Auswahl wird zurück an _showMenu_ gegeben. Je nach Auswahl wird das Spiel beendet und das Fenster durch beenden des Renderers geschlossen, oder derselbe Ablauf folgt erneut.

**Button Solver &rarr;** &nbsp;Die Solver-Funktion wird nun gestartet. Für diesen Spielmodus ist die Klasse UserInterface selbst zuständig. Ausgeführt wird das automatische Finden einer Lösung von der Klasse _Solver_. Die Funktion _createSolverMenu_ generiert ein neues Menü, welches die Auswahlmöglichkeiten mehrerer Spielfelder erlaubt. Es ist dasselbe Menü, wie auch im Spielmodus **Play**. Mit dem Unterschied, dass bei Auswahl eines Spielfeldes direkt die Lösung und die Abfrage, ob erneut gespielt werden soll, erscheint. Die getätigte Auswahl wird an _showMenu_ zurückgegeben. Abhängig von der Auswahl wird erneut gespielt oder das Spiel wird beendet.

<ins>Ablauf der Funktionen:</ins>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;_showMenu_ (& choose grid)\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&#129159;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&#129158;\
_Game::run_&nbsp;&nbsp;_createSolverMenu_\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&#129158;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&#129159;\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;_showMenu_

Alle Funtionen, die ein User Interface bzw. ein Menü erstellen, verlaufen nach demselben Prinzip:
 Die Funktion besteht aus einer _while-Schleife_, die abhängig ist von einer Variablen _quit_, die in den beiden Spielfunktionen auf _true_ gesetzte wird, wenn das Spielfeld gelöst wurde. In der Hauptfunktion _showMenu_ wird sie dann auf _true_ gesetzt, wenn ausgewählt wurde, dass nicht erneut gespielt werden soll, oder wenn der Button _Exit_ gedrückt wird.

# Komplexität eines Spielfeldes feststellen

Die Komplexität ist in 4 Stufen unterteilt: _Easy, Medium, Hard, Impossible_. Die Schwierigkeit ist abhängig davon, wie viele Lücken in der Größe von einem Kästchen existieren. Bei Lücken dieser Größe ist klar, dass dort einer der Blöcke mit der Breite _**1**_ plaziert werden müssen. Dies erleichert den Start und weiteren Verlauf des Spiels. 

**Easy:** &nbsp;Es existieren zwei Lücken der Größe 1. Darum können beide Blöcke mit der Breite 1 direkt zu Beginn plaziert werden.\
<ins> Beispiel: </ins>\
<img src = "/pictures/EasyGrid.png"
	width = "200"
	height = "200"/>
 
**Medium:**&nbsp; Es existiert eine Lücke der Größe 1. Es kann zu Beginn einer der beiden Blöcke plaziert werden.\
<ins>Beispiel: </ins>\
<img src = "/pictures/MediumGrid.png"
	width = "200"
	height = "200"/>
 
**Hard:**&nbsp; Es existiert keine Lücke der Größe 1. Keiner der beiden Blöcke kann zu Beginn plaziert werden.\
<ins>Beispiel: </ins>\
<img src = "/pictures/HardGrid.png"
	width = "200"
	height = "200"/>
 
**Impossible:** Es existieren 3 oder mehr Lücken der Größe 1, die nicht mit den beiden Blöcken befüllt werden können. Somit gibt es immer eine Lücke, die durch keinen Block gefüllt werden kann. das Spielfeld ist somit unlösbar.\
<ins>Beispiel</ins>:\
<img src = "/pictures/ImpossibleGrid.png"
	width = "200"
	height = "200"/>

Die Ermittlung der Schwierigkeit findet in einer eigenen Klasse _Difficulty_ statt. Logisch kann sie jedoch der Klasse _Grid_ zugeordnet werden. 

### Hinweis zu unit tests
Zu allen Klassen, die eine Art von logikbehafteten Funktionen beinhalten, wurden unit tests geschrieben.
Sämtliche graphischen Klassen bzw. Funktionen besitzen keine Tests, da dahinter keine Logik steckt, sondern nur Aktionen in der GUI umgesetzt werden.

# Spielanleitung

1. Bei Start des Programms öffnet sich das Spielfenster und es kann zwischen zwei Modi gewählte werden : _Play, Solve_.\
**Play** &rarr; der Spieler hat die Möglichekit eigenständig ein Spielfeld zu lösen.\
**Solver** &rarr; der Spieler kann ein Spielfeld von einem automatischen Solver "_Löser_ " lösen lassen.

2. Bei beiden Optionen öffnet sich ein neues Menü. Es gibt die Möglichkeit eines der vorgegebenen Spielfelder zu lösen bzw. lösen zu lassen. 
Es können auch beliebig viele neue Spielfelder entweder automatisch oder von Hand generiert werden. 
Das Spiel funktioniert nach einem drag and drop System. 
Jeder Block wird hochkant angezeigt, kann aber rotiert werden durch Drücken der rechten Maustaste oder _"R"_ auf der Tastatur.

3. Nach Lösen eines Spielfeldes kommt der Spieler zurück in das Startmenü. Es kann erneut gespielt werden. Beendet wird das Spiel durch _Exit_.

# Projektinstallation

### Projekt ausführen

1. Git Repository klonen
2. CMake builden
3. Für Tests das Projekt Tests ausführen
4. Für das Spiel das Projekt MondrianBlocks ausführen

CTests funktionieren nicht, es müssen GoogleTests ausgeführt werden!

### Hinweise

1. Das erste Ausführen des Projekt kann unter Umständen ein paar Minuten in Anspruch nehmen, 
da zunächst alle Bibliotheken gebuildet werden müssen.
2. Die nötigen Bibliotheken, sowie GoogleTests werden im building-Prozess von GitHub geklont.
3. Das Projekt sollte im *release* ausgeführt, werden, da die Performance deutlich besser ist im Vergleich zu *debug*.

### Team
Benni Stauder: [Github](https://github.com/Benni-Stauder)\
Concetta Lanza: [Github](https://github.com/lanzaco)\
Annika Jung: [Github](https://github.com/annikajung)


