# The Fifth Element by Selery Studios (PARTE 2 by PABLO CAO)
![Imagen Quinto Elemento](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/fifth_element.png)
---
## Enlaces
---
[Web del juego](https://ucm-fdi-disia.github.io/Selery-Studios/)

## GDD NUEVA EXTENSIÓN
---

### ÍNDICE

● Nuevo modo de juego

● Cartas

● Mecánicas

● Dinámica

● Estética 

● Descripción partida típica 

● HUD

● Menús 

● Referencias 

### Nuevo modo de juego
Este nuevo modo consistirá en una partida de cartas al estilo Legends of Runeterra, Skyweaver y Hearthstone. Siendo un 1vs1 contra el personaje de la muerte cada uno contará con una baraja de 20 cartas donde se podrán encontrar todos los personajes, bosses y enemigos del juego.

### Cartas
Las cartas serán todos los elementos del juego original pudiendo ser: enemigos, personajes, bosses y hasta ataques del jugador. Los enemigos a su vez podrán ser de cualquiera de los 4 elementos que pueden ser en el juego siendo: tierra, fuego, aire y agua. Los personajes y los bosses también podrán ser de los elementos del juego a excepción del boss de luz, que dado que el jugador juega siendo el hermano de luz no se incluirá en los bosses. El oponente, que será la muerte, contará con una baraja compuesta únicamente de bosses y de enemigos mientras que el jugador contará con personajes, enemigos y ataques del jugador del juego original (los ataques serán también de un elemento excepto de luz). Cada carta cuenta con un valor para su ataque y un valor para su vida a excepción de las cartas de ataques que no contarán con vida pero al ser usadas para atacar se eliminarán de la partida al igual que cualquier otra carta que pierda sus puntos de vida por completo.

### Mecánicas
Las mecánicas de este modo se reducen a 2 pero con el mismo control: el click izquierdo del ratón. Las 2 mecánicas son las de colocación y la de ataque, la de colocación será para las cartas que tengamos en nuestra mano y la de ataque será para las cartas que ya hayan sido colocadas en la mesa.

### Dinámica
Este modo cuenta con varias dinámicas: los turnos, las rondas, la colocación de cartas y energía, el ataque, la vida del personaje y la baraja de cartas. Los turnos tienen una duración de 2 minutos y el primer turno de la partida se decidirá de manera aleatoria, en estos turnos se podrá colocar cartas y usarlas para el ataque, una vez finalicemos el turno pasará a ser el del oponente y así sucesivamente hasta finalizar la partida. Las rondas comienzan en la número 1 y a los jugadores se les otorgará esa cantidad de energía para colocar cartas (explicación más detallada en la dinámica de colocación) hasta la ronda número 10 en la cual dejará de otorgarse un punto de energía por cada ronda pasada a ser únicamente 10. La colocación de cartas cuenta con el sistema de energñia donde cada carta tendrá un coste energético para poder ser colocada y que no podrán colocarse más cartas con mayor coste energético que energía se tenga en ese momento; la energía que no se gaste en una ronda será eliminada y al comienzo del siguiente turno se recibirá la misma energía que rondas se hayan pasado hasta un máximo de 10. El ataque no nos costará energía pero seguirá ciertas normas: 1º no se podrá atacar al personaje enemigo si este tiene cartas en la mesa, 2º una carta no podrá atacar más de 1 vez por turno, 3º las cartas cuenta con el mismo sistema de multiplicador de daño entre elementos que el juego original, 4º la carta que ataque a otra enemiga inflingirá daño pero también lo recibirá, 5º varias cartas pueden atacar a la misma carta enemiga. La vida del personaje tanto como la del oponente serán 15 puntos de vida y que al llegar a 0 resultaría en la derrota para ese jugador. La baraja de cartas se generará de manera aleatoria al inicio de cada partida y como se menciona en el apartado de cartas cada jugador contará con 20 de estas sacadas de una pool de cartas disponibles para cada jugador; si en algún momento de la partida el jugador se quedara sin cartas ya no podrá obtener más.

### Estética
Siguiendo la estética del juego original se usarán recursos de pixelart para dar vida al modo de juego. Cada carta contará con un reverso con el logo del juego y un anverso que mostrará el tipo de carta que es y sus puntos de vida, ataque y coste de energía.

### Descripción partida típica
Una partida típica comenzaría con la selección del turno de inicio de manera aleatoria entre jugador y máquina y en la ronda número 1. Para la descirción tomaremos que el jugador cuenta con el primer turno. Al empezar a jugar veríamos en la parte inferior de nuestra pantalla 5 cartas y un icono que nos mostraría la energía de la que disponemos. Siendo la primera ronda solo contamos con 1 punto de energía por lo que solo podríamos colocar una carta de ese coste, tras colocar deberíamos finalizar el turno ya que la carta colocada no ha pasado ningún turno estando en la mesa y no podría ser usada para atacar. A continuación la máquina realiza su turno y al igual que nosotros coloca una carta de coste 1 y finaliza su turno. 2ª ronda y contamos con 2 puntos para colocar cartas, decidimos colocar primero todas la cartas posibles y con carta que ya lleva un turno sobre la mesa atacamos a la carta del oponente, matándola pero perdiendo la nuestra en el proceso (por la regla de los ataques que a la vez que inflijimos daño la carta enemiga contraataca y esta vez ha quitado toda la vida de nuestra carta). En el segundo turno de la máquina coloca una carta de coste 2 y al no poder atacar finaliza su turno. 3ª ronda y hacemos uso de toda nuestra energía para colocar más cartas y con las 2 que ya llevan un turno en mesa atacamos a la única carta enemiga que muere tras el ataque de la primera carta y aprovechamos para atacar directamente al personaje de la máquina con nuestra segunda carta. La partida continuaría de esta manera hasta que uno de los 2 personajes pierda por completo la vida resultando en la victoria del contrario.

### HUD
El HUD en este modo tendrá: un contador de tiempo para cada turno reduciendo de 2:00 minutos hasta 0:00 significando el paso al turno del contrario, los puntos de energía que indicarán al jugador cuanta energía les queda en todo momento, un botón de pausa para acceder al menú de pausa, la baraja de cartas que tendrá un número indicando cuantas cartas quedan en el mazo y al lado de la imagen de cada personaje un número que represente la vida de cada jugador.

### Menús
Se usará el menú de inicio que ya viene implementado con el juego original y también el menú de pausa del mismo pero con alguna modificación para excluir información innecesaria respectiva al modo historia.

### Referencias
Hearthstone - Blizzard (2014)
Legends of Runeterra - Riot Games (2020)
Skyweaver - Horizon Blockchain Games (2019)