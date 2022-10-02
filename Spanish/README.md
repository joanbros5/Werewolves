# Hombres Lobo

_________________
-- Descripción --
_________________

Esta es una herramienta para el narrador del juego de "Los hombres lobo de castronegro" en el formato y roles de "Best Of".

El programa se encarga de manejar las cosas de la partida para que el narrador no tenga tanto trabajo. En el archivo "Notas" está la lista de personajes que de momento están hechos.

_________________
-- Compilación --
_________________

 >Estos pasos solo funcionan en un Sistema Operativo Linux.

1. Primero de todo ir con la terminal a la carpeta donde se encuentran los archivos.

2. Se puede ejecutar directamente el archivo .exe ya creado en una terminal (./Poble_i_Llop.exe) para comenzar una partida o bien, si se modifica el código del archivo .cc, escribir en la terminal:

	#g++ -std=c++11 -o Poble_i_Llop.exe Poble_i_Llop.cc

3. Y luego ejecutar el archivo .exe con 

	#./Poble_i_Llop.exe
	
4. Se puede salir en cualquier momento del programa con Ctrl + C

____________________
-- Funcionamiento --
____________________

1. Al ejecutar el programa se pedirá una lista de los nombres de las personas en la partida. Se han de introducir una serie de nombres separados con espacios y terminando con un guión (-). Se pueden hacer saltos de línea sin problemas.

Por ejemplo:

	#Juanito Ana Alba Marcos Pepe Albin Maria Pepa -
	
2. Después el programa pedirá que introduzcas los roles de la partida en un formato concreto ([número] [rol]) y terminando con un zero. Esto es para determinar cuántos roles habrá en la partida. Se pueden intercalar mayúsculas y minúsculas sin problema. Por ejemplo:

	#5 Aldeano 2 Cazador 2 Lobo 1 niña 1 vidente 0
	
En el ejemplo de arriba, habrá 5 personas con el rol de Aldeano, 2 con Cazador, 2 con Lobo... etc

	PERSONAJES JUGABLES DE MOMENTO:
	
	Vidente
	Lobo
	Lobo_albino
	Cazador
	Perro_lobo
	Niña
	Aldeano
	Flautista
	Domador_osos


Si el número total de roles es más alto que el número de personas en la partida, se pueden dar situaciones que haya un desbalance. Esto sirve para hacer partidas que dependan de la estadística. Por ejemplo, en esta partida: 

	#A B C D E F -		//6 personas
	#6 Aldeano 2 Lobo 0	//8 roles

Quizá en la partida haya 0, 1 o 2 Lobos. Puede ser injusto para los lobos, pero la partida también es más misteriosa y divertida.

3. Una vez introducidos los roles, saldrá una lista con los resultados y comenzará la partida con las fases de cada rol.

Si a la hora de escribir un nombre no está en la lista, en esa fase no se hará nada. Por ejemplo, si los lobos deben matar a una persona de esta lista:

	Joan
	Pablo
	Ana
	Rosa
	
Y el usuario escribe "Maria" no ocurrirá nada. De la misma manera, si se escribe un nombre con fallos ortográficos (Juan) o con diferentes mayúsculas o minúsculas (joan) (JOAN) no ocurrirá nada.

4. La partida termina y funciona con las normas de "Best Of Hombres lobos de Castronegro".
