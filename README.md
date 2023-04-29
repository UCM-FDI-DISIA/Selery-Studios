# The Fifth Element by Selery Studios
![Imagen Quinto Elemento](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/fifth_element.png)
---
## Enlaces
---
[Web del juego]()

[Enlace al release]()

[Enlace al vídeo]()

[Presentaciones](https://drive.google.com/drive/folders/1f_cQAVOkluKYBIAy_LxrGzPj3atoO3wp?usp=share_link)


## GDD
---
### AUTORES
● Pablo Cao Calvo

● Agustín Castro De Troya

● Pablo Cerrada Vega

● Francisco Miguel Galván Muñoz

● Dorjee Khampa Herrezuelo Blasco

● Sheila Julvez López

● Pablo Martínez Quesada

● Cristina Mora Velasco

● Jose Moreno Barbero

● Alberto Peñalba Martos

● Sofía Sánchez Fernández


### ÍNDICE
● Estructura grupal

● Estudio 

● Juego 

● Descripción	

● Público Objetivo 

● Género del videojuego 

● Cámara 		

● Mecánicas

● Diseño de Nivel y Puzzles

● Dinámica 

● Estética 

● Descripción partida típica 

● HUD

● Menús

● Historia y narrativa 

● Personajes y enemigos 

● Referencias 


### ESTRUCTURA GRUPAL
Cada miembro trabajará en todos los campos. Todas las decisiones se someterán a votación.
### ESTUDIO
Selery Studios
### JUEGO
The Fifth Element
### DESCRIPCIÓN DEL PROYECTO
Proyecto que combina navegación en un mapa TopDown con elementos de gestión de recursos, rompecabezas y un combate estilo beat em’ up.

### PÚBLICO OBJETIVO
**Clasificación PEGI**

**Perfil de jugador** 
El perfil de nuestro jugador encaja en personas tanto jóvenes adolescentes como adultos que quieran verse envueltos en una narrativa curiosa y poco común. Nuestro público objetivo también disfrutará de lo divertida que es la experiencia. Sobre todo buscamos un público abierto a afrontar retos que atentan contra los nervios.

### GÉNERO
**Aventura** 
Debido a su enfoque en la historia y en su forma de avanzar para ir desentramando la historia.

**Beat em’up** 
El género beat em’ up se encuentra en las escenas de lucha, en las cuales lucharemos contra un número de enemigos indefinido.

A su vez, al ser un juego con una narrativa tan fácil de seguir y  unas mecánicas tan intuitivas, los jugadores casuales, que no tienen tanto bagaje en el mundo del videojuego, pueden encontrar en nuestro juego una muy buena experiencia.

### CÁMARA
Dentro del juego existen dos tipos de cámara diferentes:
Mientras se explora el mundo la cámara será top-down, es decir, se observará el entorno desde arriba. La cámara seguirá al jugador, el cuál se colocará en el centro de la pantalla (se verá ligeramente más hacia donde mira el personaje) para tener una vista de todo el alrededor del jugador.
Durante el combate la cámara será 2.5 D, es decir, será un plano 2D pero con cierta profundidad.
Cámara en movimiento siguiendo al jugador dentro de los límites del escenario de combate, con el jugador notablemente a la izquierda del centro de la pantalla.

### MECÁNICAS
**Sistema de movimiento**
Tendremos dos tipos de movimientos, aunque estos serán muy similares entre sí.
Por una parte tenemos el movimiento en el modo TopDown, en este podremos movernos con AWSD en el eje X e Y. 
En el modo Beat Em Up también podremos movernos con WASD, con AD se realizan movimientos en horizontal y con WS en profundidad (habiendo límites en los bordes del mapa que no se pueden superar), además será posible saltar (tanto en el sitio como moviéndose horizontalmente).
Si en el modo TopDown, mientras nos movemos a la derecha, por ejemplo, pulsamos W, para movernos hacia arriba, la instrucción que impera es la primera.

**Sistema de combate**
Nuestro sistema de combate se basa en los elementos Fuego, Agua, Tierra y Aire, siendo este último el elemento neutro.
A continuación un grafo que explica la relación entre elementos:

| ATACANTE/DEFENSOR | AGUA | FUEGO | TIERRA | AIRE |
|-----------|:-----------:|:----:|:----------:|------:|
| **AGUA** | x1 | x1.5 | x0.5 | x1 |
| **FUEGO** | x0.5 | x1 | x1.5 | x1 |
| **TIERRA** | x1.5 | x0.5 | x1 | x1 |
| **AIRE** | x1 | x1 | x1 | x1|

![Imagen de elementos](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/elements.png)

Cuando un elemento afecta a otro, este le hace una cantidad de daño equivalente a:

Daño = CaracterísticaDaño*1,5

En caso de que ataquemos a nuestro elemento counter, el multiplicador del daño será 0.5.

Daño = CaracterísticaDaño*0,5

Cuando la relación no es ni a favor ni contraria, por ejemplo cuando atacamos con aire a cualquier otro elemento, este multiplicador es 1.

Daño = CaracterísticaDaño

**Habilidades**

**Comunes:** Salto

**Aire**: 
- Ataque básico: Katanazo. (pulsando 1 vez)
- Ataque básico 2: Katanazo + ráfaga de katanazos (pulsando 2 veces)
- Ataque básico 3: Katanazo + ráfaga de katanazos + tornado (pulsando 3 veces)
- Habilidad especial: Ataque rápido que atraviesa al enemigo 

**Fuego:**
- Ataque básico: Espadazo. (pulsando 1 vez) 
- Ataque básico 2: Espadazo + pirueta. (pulsando 2 veces)
- Ataque básico 3: Espadazo + pirueta + explosión (pulsando 3 veces)
- Habilidad especial: El personaje se queda 1 segundo parado cargando la espada (se queda expuesto), cuando está cargada, al soltar el botón se lanza un ataque que proyecta una llamarada de fuego.
La habilidad especial tendrá un multiplicador mayor en enemigos de Tierra.
Daño= CaracterísticaDaño*2

**Agua:** 
- Ataque básico: Estocada. (pulsando 1 vez)
- Ataque básico 2: Estocada + estocada larga (pulsando 2 veces)
- Ataque básico 3: Estocada + estocada larga + ola (pulsando 3 veces)
- Habilidad especial: Creas una burbuja que aplasta al enemigo. Deja un rastro de pìnchos de hielo (doble hit)
- La habilidad especial tendrá un multiplicador mayor en enemigos de Fuego
Daño = CaracterísticaDaño * 2

**Tierra:**
- Ataque básico: Puñetazo. (pulsando 1 vez)
- Ataque básico 2: Puñetazo + doble puñetazo. (pulsando 2 veces)
-  básico 3: Puñetazo + doble puñetazo + terremoto. (pulsando 3 veces)
- Habilidad especial: El personaje se queda parado e invoca dos manos gigantes de roca que machacan el suelo, (doble hit)
- La habilidad especial tendrá un multiplicador mayor en enemigos de Agua..
Daño = CaracterísticaDaño*2

### DISEÑO DE NIVEL Y PUZZLES
A lo largo del juego se van a poder ir desbloqueando a los distintos personajes jugables. Estos te van a proporcionar también la posibilidad de utilizarlos en modo exploración (intercambiándolos de la misma forma que el en modo Beat Em Up). Cada uno proporcionará una mecánica distinta una vez desbloqueados:

**Fuego** 
A lo largo del mapa habrá distintos altares apagados alrededor de un cofre, con el personaje de fuego podrás acercarte y encenderlos. Para poder desbloquear el cofre tendrás que encender los distintos altares (como máximo cuatro) en un orden específico, que es tarea del jugador descubrir, podrá estar señalado en el mapa el orden en el que deben ser.

![Imagen pedestales](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/altares.png)

**Agua**
Funciona de la misma forma que con el personaje de fuego pero en vez de altares con “copas”.

![Imagen copas1](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/copas1.png)

![Imagen copas2](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/copas2.png)


**Roca** 
El mapa tendrá zonas bloqueadas a las que no se puede acceder por estar bloqueadas por una roca. Con el personaje de piedra se podrá destruir esta y acceder a esta nueva zona, la cual será una pequeña zona que podrá contar con cofres y enemigos.

![Imagen Rocas](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/rocas.png)


### DINÁMICA
**Sistema de detección**
Para empezar el combate, en el modo exploración, los enemigos tendrán una ruta predeterminada. Cada enemigo tendrá dos zonas, será un cuadrado dentro de otro como se muestra en siguiente imagen:

![Imagen detección](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/deteccion.png)

El enemigo está representado como un punto negro. El cuadrado más grande representa la primera zona donde detecta, en esta avisará al jugador mediante una música distinta y una representación gráfica (exclamación en la cabeza). Si el jugador pasa a la segunda zona (la del color más intenso) el enemigo detectará al jugador, aparecerá una exclamación y posteriormente iniciará el modo combate.

**Sistema de combate**
El combate será de tipo beat em’ up, en el que nuestro personaje se colocará a la izquierda y los enemigos a la derecha. El personaje, independientemente de quien sea, tendrá un combo de tres ataques y un ataque especial, el cuál contará con un cooldown entre usos. Se podrá cambiar de personaje en medio del combate, con un cooldown establecido.

**Dinámica de combate contra jefes** 
Los jefes presentarán distintas dinámicas de combate con respecto a los enemigos normales, a continuación especificaremos cada uno de ellos. Todos ellos tendrán una barra de vida en la parte superior de nuestra pantalla.
**Jefe de Tierra (golems y ciervo)**
Se encontrará al final del reino de Tierra.
Al comienzo de la pelea, nos encontraremos con un golem normal cuyo único comportamiento es ir hacia el jugador y golpearle con un puñetazo. Este golem será fácil de derrotar. Al derrotarlo, dejará rocas en el lugar de su muerte. 
Tras este aparecerá otro golem (skin con yerbajos), a diferenciar del otro, este puede protegerse, lo que nos complicará a la hora de derrotarlo. Dejará sus restos al ser derrotado.
Por último aparecerá del cielo un ciervo, caerá en medio del campo de batalla y deberemos utilizar las rocas de los golems anteriores para lanzárselas y hacerle mucho daño, además de ralentizar su velocidad de movimiento y su velocidad de ataque. Cuando recolectamos una roca, nuestro próximo ataque la lanzará, y después de lanzarla podremos volver a los ataques normales.

Acciones Golem:
Ataca hacia el lado en el que mira, golpeando ambos puños
El segundo golem puede protegerse de nuestros golpes. Si está protegido, no recibe daño y aumentará su ataque si es atacado.

![Imagen Golem](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/golem.gif)

Acciones Ciervo:
Ataque con martillo hacia la dirección donde mira.
Velocidad de movimiento y velocidad de ataque progresiva cuando baja su salud.

![Imagen Ciervo](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/ciervo.gif)

**Jefe de Fuego**
Este jefe se ubicará en la parte derecha del escenario, su forma de ataque será: moverse desde la esquina derecha hacia el jugador, quedarse quieto y atacar para luego volver a su esquina derecha.

Cuando pierde el 25% de su vida invocará dos pilares de fuego y el jefe pasará a un estado donde se quedará quieto, no se le podrá hacer daño y recuperará vida, esto continuará así hasta que el jugador elimine los pilares.

Al 50% de vida perdida, invoca a 3 enemigos de fuego y sale de la pantalla, una vez derrotados este vuelve.

Al perder el 75% de la vida, vuelve a invocar pilares, esta vez tres, y pasar al estado anterior.

**Jefe de Agua(golem de hielo)**
La mecánica principal de esta batalla es esquivar. El jefe contará con una armadura de hielo que le hará invulnerable a los ataques del jugador, por lo que se deberá evitar el daño de sus dos ataques hasta detectar una ventana en la que realizarle daño.

El jefe solo se moverá para realizar sus ataques (no seguirá al jugador). Para realizar el primer ataque se colocará cerca del borde derecho de la pantalla, mientras que para realizar el segundo ataque caminará a una posición más cerca del centro de la pantalla (en el eje horizontal).

Durante el primer ataque  el jugador solo se tendrá que dedicar a esquivar los ataques que le lanza el boss en forma de “olas”. La intención de esta fase de ataques es dividir el escenario en carriles y forzar al jugador a que tenga que moverse al carril que quede libre. La idea es que se lancen tres ráfagas de este ataque dando poco tiempo al jugador para moverse entre ráfagas.

![Mockup boss Agua](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/mockupWaterBoss1.png)

El segundo ataqué consistirá en lanzar una lluvia de carámbanos de hielo por todo el escenario. Para realizar este ataque el jefe deberá desprenderse de su armadura gélida, momento que el jugador debe aprovechar para realizarle daño, este es el único momento del combate en el que podrá reducirle la vida al jefe.

![Imagen boss Agua](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/animationWaterBoss.png)

Después de realizar esta animación aparecerán varias sombras (que serán los lugares donde caerán los carámbanos) y comenzarán a caer los carámbanos desde la parte superior de la pantalla.
Mientras caen los carámbanos el jefe se mantendrá en esta posición, (animación creada usando los frames 4, 5 y 6) en la que será vulnerable a los ataques del jugador.

![Imagen posición boss agua](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/posicion.png)

Caerán carámbanos con bastante frecuencia (antes de que se destruyan los de una oleada ya se habrán generado los siguientes).

Al terminar el ataque realizará la animación del principio de forma inversa (recuperando el hielo de su armadura y volviéndose invulnerable de nuevo).

![Mockup boss agua 2](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/mockupWaterBoss1.png)

**Jefe de Luz( hermano de Luz)** 
Primer ataque: bola de luz (se puede devolver)

![Primer ataque](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/mockupLightBoss1.png)

Segundo ataque: rayo de luz que ocupa toda la pantalla

![Segundo ataque](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/mockupLightBoss2.png)

Al perder el 75% de vida podrá teletransportarse (en casos aleatorios) y al hacerlo disparará una bola de luz. Siempre que se teletransporte acabará mirando al jugador y disparando la bola hacia él.
Entre un 40% y un 20% de la vida si el jugador se acerca demasiado el boss se teletransportará y disparará la bola.
Al perder un 80% de la vida las luces empezarán a apagarse y encenderse cada pocos segundos y el combate seguirá como antes.

**Puzzles**

**Tienda**
El jugador podrá comprar mejoras en una tienda para mejorar sus estadísticas tanto de ataque como de salud a cambio de monedas obtenidas como recompensas en los combates. Estas mejoras son independientes de cada personaje elemental, es decir, podemos obtener mejoras de ataque y/o de salud para cada uno de los 4 personajes que podremos conseguir durante el juego.



### ESTÉTICA
**Estilo gráfico** 
El estilo gráfico de nuestro proyecto es de tipo Pixel-Art. 
Desde el punto de vista artístico existirán dos tipos de entorno, uno para el mundo abierto (con más detalle) y otro para las escenas de combate (menos pixeles).

**Recursos** 
Los recursos han sido tomados de itchi.io. Algunos los hemos adquirido de forma gratuita y otros los hemos comprado, por lo que, tenemos plena potestad, sobre su uso según el Real Decreto Legislativo 1/1996, de 12 de abril, por el que se aprueba el texto refundido de la Ley de Propiedad Intelectual, regularizando, aclarando y armonizando las disposiciones legales vigentes sobre la materia.

### DESCRIPCIÓN PARTIDA TÍPICA
Al abrir el juego, se encontrará con un menú inicial. Al pulsar el botón de Play entrará al mundo de exploración con el personaje de aire. Tendrá solo esta zona desbloqueada. Deberá luchar contra distintos enemigos iniciales, moverse por el mundo e ir resolviendo algunos puzzles iniciales. Para el movimiento usará las teclas WASD y para interactuar con el mundo la tecla E. La narrativa guiará al jugador desde el primer momento, iniciando con la historia, controles y terminando con pistas para ayudar al jugador.
En el modo de combate, el movimiento también será con las teclas WASD además de un salto con la tecla SPACE y podrá cambiar de jugador siempre que estén disponibles con las teclas 1, 2, 3 y 4.

Se podrá mejorar las estadísticas de ataque y salud máxima en los mercaderes que se encontrarán repartidos por el mundo.

### HUD

**Modo exploración**
**Rueda de personajes:** aparece en la esquina superior izquierda. Muestra al personaje que tenemos seleccionado actualmente(en grande), además también los personajes que tenemos desbloqueados(en pequeño). En adición podemos ver las estadísticas actuales de cada personaje(también en la rueda y en pequeño).
**Monedas:** aparecen en el mismo layout de la rueda y muestran las monedas actuales que tenemos.


**Beat em’up**
**Barra de vida:** aparece en la esquina superior izquierda, mostrando la salud actual de cada personaje. También, encima de cada enemigo, aparece su respectiva barra de vida.
**Rueda de personajes:** se diferencia de la del modo exploración en que no contiene las estadísticas de ataque y salud, y las monedas.

![Mockup pantalla 1](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/UI.png)


### MENÚS
**Menú principal**
Menú de inicio que consta de un botón PLAY, un botón EXIT, y una rueda para cambiar los ajustes. 
**Pantalla de ajustes** 
En esta pantalla podemos cambiar el volumen del juego, los SFX, y ver los controles.
**Menú pausa** 
En esta pantalla el juego estará en pausa. Podemos volver al juego con un botón RESUME, salir al menú principal con un botón MENÚ, además de la rueda para cambiar los ajustes.
**Menú Game Over** 
Cuando nos debiliten aparece un menú de Game Over con un botón de MENÚ para volver al menú principal y otro botón EXIT para salir del juego.
**Menú de tienda**
Este menú aparece al interactuar con un comerciante. Consta de 8 botones de mejora, 4 para las mejoras de ataque y 4 para las mejoras de salud.

![Tienda](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/Tienda.png)

### HISTORIA Y NARRATIVA
Nos situamos en Pivo, una tierra donde hay heraldos. Estos están encargados del equilibrio del mundo. Tras una trifulca entre los hermanos, el mundo se divide en cinco partes: fuego, agua, aire, tierra y Sondeluz, una por cada hermano. 

Tras unos años, el hermano Aire recibe la carta de un siervo de Sondeluz, el quinto hermano, el cual ha fallecido. Como última voluntad pidió reunir a todos los hermanos para despedirle, dada la situación entre los hermanos, será tarea de Aire encontrar por el bosque al resto de hermanos  y convencerles de ir juntos, resolviendo las diferencias que tienen entre ellos.

Por el camino se van encontrando enemigos y puzzles, los cuales solo se pueden resolver con la ayuda de la colaboración de los hermanos, SondeLuz lo planeó para que trabajaran juntos y se reconciliasen.

Cada zona representa una etapa del duelo
Etapa de la negación: Aire
Etapa de la ira: Fuego
Etapa de la negociación: Tierra
Etapa de la depresión: Agua
Etapa de la aceptación: Luz

### PERSONAJES Y ENEMIGOS
**Modo exploración**
**Personaje principal:** el personaje principal será un hermano (Fuego, Agua, Tierra o Aire). 
Se iniciará con el hermano de aire (Aire).
El jugador podrá moverse con las teclas (W,A,S,D) y explorar el entorno.
Existirá la posibilidad de cambiar de hermano, siempre que se le tenga desbloqueado. Se cambia con las teclas 1, 2, 3 y 4 .
**Enemigos:** Su función será detectar al jugador mediante un área para empezar el modo Beat em’up. 

**Beat em’up**
Personaje principal: podrá cambiarse en mitad de la partida con las teclas 1,2,3 y 4 (igual que en el mundo abierto). Constará de un combo de tres ataques y uno especial
Enemigos: serán de diferentes elementos, al igual que el personaje principal. Perseguirán y atacarán al jugador. El daño que ejercen, así como el que reciben, dependen de las mecánicas del combate.
Aparecerán en oleadas (más o menos numerosas en función del nivel).

### REFERENCIAS
Hemos usado varias fuentes como referencias:

Pokemon(Desde 1996, GameFreak)

![Imagen Pokemon](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/pokemon.png)

Streets of Rage(1992, Ancient/Sega)

![Imagen Streets of Rage](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/streetrage.png)

Monkey Delivery (2022,Moon Key)

![Imagen Monkey Delivery](https://github.com/UCM-FDI-DISIA/Selery-Studios/raw/main/imgs/monkeydelivery.jpg)


**Este trabajo es académico, no tenemos ninguna intención de sacar crédito con el proyecto, es meramente educativo.**



## UML
---

## QA
---
**1. Prueba de funcionalidad del modo Beat Em Up**

Resultado Esperado:

- El jugador realiza combos (bien sea de un ataque, o de dos, o de tres) y
usa el ataque especial.
- El jugador cambia de personaje para tener cierta ventaja contra los
enemigos. 
- El usuario cambia de personaje cuando tenga poca vida (entiende el IU del
modo Beat Em Up).

**2. Prueba de funcionalidad del modo Top Down y de la tienda**

Resultado Esperado:

- El jugador compra mejoras para “beneficiarse” en el modo Beat Em Up.
- El jugador usa los portales para hacer viajes rápidos.
- El jugador sabe la cantidad de monedas que posee, gracias al HUD del modo
Top Down.
- El usuario se da cuenta de que puede dialogar con los NPC con la tecla “E”.

**3. Prueba de integración del modo Top Down y el Beat Em Up**

Resultado esperado:

- El jugador se da cuenta que si está en el rango de visión de los enemigos
entra en batalla.
- Comprobar si intenta esquivar el rango de visión de los enemigos.

**4. Prueba de Menús**

Resultado esperado:

- El jugador sabe como acceder al juego.
- El usuario sabe como entrar al menú de configuraciones.
- Si le molesta el brillo o el sonido, hará uso de los sliders.
- El jugador entiende los controles.


### **Preguntas del QA**

**Prueba de funcionalidad (ambos modos)**

1. ¿Todas las animaciones y movimientos de los personajes funcionan
correctamente, tanto en el modo Beat Em Up y en el Top Down?

2. ¿La interfaz de usuario del Beat Em Up es intuitiva y fácil de entender?

3. ¿La interfaz de usuario del modo Top Down es intuitiva y fácil de entender?

4. ¿El jugador puede regresar al modo Top Down en cualquier momento y sin
errores al acabar la fase de pelea en el Beat Em Up?

5. ¿Los portales funcionan correctamente y transportan al jugador al reino
correspondiente?

6. ¿La transición entre el modo Top Down y el Beat Em Up es suave y sin
problemas?

7. ¿Se activa correctamente el modo Beat Em Up si un enemigo ve al jugador
mientras está en el modo Top Down?

8. ¿El juego tiene problemas de visualización, en pantalla completa o al
escalar la resolución de la pantalla?

9. ¿El juego es fácil de entender y jugar para todos los usuarios?

**Prueba funcionalidad tienda**

1. ¿La mecánica de compra de mejoras para los personajes es clara y fácil de
entender?

2. ¿El HUD de la tienda es fácil de entender?


**Prueba de rendimiento**

1. ¿Los controles de los personajes principales son precisos y responden
adecuadamente?

2. ¿El sonido se solapa al pasar de una escena a otra (se solapan canciones)?

3. ¿El juego tiene problemas de rendimiento con muchos personajes en pantalla?

4. ¿El juego se ejecuta sin problemas en diferentes dispositivos con Windows?

5. ¿Hay problemas de lag o retraso en la respuesta de los controles?

6. ¿El juego cuenta con algún error o bug que impida el avance del jugador?

7. ¿El juego tiene tiempos de carga prolongados que afecten la experiencia de
juego?


**Prueba funcionalidad de menús**

1. ¿El menú de opciones tiene todas las funcionalidades necesarias para el
usuario?

2. ¿El menú de pausa funciona correctamente?

**Prueba de combate**

1. ¿La inteligencia artificial de los enemigos es desafiante pero justa?

2. ¿El jugador usa la ventaja de los elementos contra sus enemigos en el modo
Beat Em Up?

3. ¿El jugador abusa de algún ataque en especial, o de algún personaje?

**Prueba de contenido (agrado del usuario)**

1. ¿La música y los efectos de sonido son coherentes con el estilo y la
temática del juego?

2. ¿El juego tiene una buena relación entre la dificultad y la progresión del
jugador?

3. ¿Para ti cuál es la historia del juego?

4. ¿La calidad de audio se mantiene constante durante todo el juego?

5. ¿El juego tiene una buena variedad de enemigos, personajes y habilidades?

6. ¿El juego tiene una buena duración y no se siente demasiado corto o
demasiado largo?

7. ¿El juego cuenta con algún tipo de logro o sistema de recompensa para
incentivar la repetición del juego (monedas, desbloqueo de personajes)?


**Datos del tester**

Edad:

Sexo: (H/M)

Experiencia como jugador:

Experiencia en juegos Beat Em Up:

Tiempo jugado:

Contador de muertes: