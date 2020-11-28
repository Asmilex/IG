# Examen prácticas 1

Programar un método dentro de la clase mallaInd que calcule la esfera envolvente de la malla, para ello:
1. Añadir tres atributos privados a la clase:
- vector<Tupla3f> esferaXZ
- vector<Tupla3f> esferaYZ
- vector<Tupla3f> esferaXY
que contendrán las coordenadas de los puntos que compongan, respectivamente, el ecuador, el meridiano paralelo al plano x=0 y el meridiano paralelo al plano z=0
2. Hallar el centro geométrico de la malla, para ello, calcular la media aritmética de todos los vértices que la componen (caso de haber al menos uno, en otro caso se supone el (0,0,0) )
3. Hallar la máxima de las distancias del centro geométrico calculado anteriormente a un vértice de la malla.
El punto calculado en 2 será el centro de la esfera envolvente y la distancia máxima calculada en 3 será el radio de dicha esfera.
4. Calcular una cantidad representativa de puntos que pertenezcan al plano paralelo a y=0 que pasa por el centro geométrico y que están a una distancia igual al radio calculado en 3 y almacenarlos en esferaXZ, análogamente con puntos paralelos a x=0 en esferaYZ y con puntos paralelos a z=0 en esferaXY.
Programar el método de forma que una vez estos vértices estén calculados no se vuelvan a calcular a no ser que la malla haya cambiado.

Programar la visualización de la esfera envolvente usando funciones de modo inmediato (creo), como GLDrawArrays o GLDrawElements uniendo cada vértice de cada vector con el siguiente, y los últimos con los primeros, usando la "primitiva" GL_LINES, utilizando líneas naranjas de 0'5 px de grosor. Se pide además que se permita activar o desactivar la visualización de la esfera pulsando la tecla U (creo recordar que era la U)