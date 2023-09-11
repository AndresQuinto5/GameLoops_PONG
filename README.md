# Laboratorio de Desarrollo de Juego Pong

## Objetivo

El objetivo de este laboratorio es preparar y configurar tu ambiente de desarrollo, así como establecer el esqueleto base para tu motor de juego ("engine").

## Requisitos de Lenguaje y Librerías

- Debes utilizar un lenguaje de programación de nivel relativamente bajo como C++ o Lua. Si deseas utilizar un lenguaje diferente, es necesario que te comuniques con el instructor para obtener aprobación.
- Puedes utilizar librerías base como SDL2, SFML o GLFW. Si deseas utilizar otras librerías, también debes someterlas a aprobación.

## Especificaciones del Juego

Utilizando el "engine" que hayas preparado y en base a lo aprendido en clase, debes crear un pequeño juego de Pong con las siguientes características:

### Jugadores y Controles

- Debe haber dos jugadores.
- Cada jugador controlará un "paddle" que se podrá mover solo verticalmente en la pantalla.
- Los controles deben ser a través del teclado.

### Mecánicas de Juego

- El juego debe utilizar movimiento frame-based.
- Debe existir una "pelota" que se moverá continuamente por la pantalla.

#### Interacciones con "Paddle"

- Cuando la pelota toque un "paddle", su dirección en el eje X debe invertirse y su velocidad debe aumentar.

#### Interacciones con Paredes

- Si la pelota toca la pared superior o inferior, su movimiento en el eje Y debe invertirse y su velocidad debe aumentar.
- Si la pelota toca la pared izquierda o derecha, el juego debe cerrarse y se debe mostrar un mensaje en la consola indicando qué jugador ha ganado (el jugador opuesto a la pared que causó que el juego terminara).
