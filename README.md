# CPU Scheduling Simulator - Tarea 2
# Autor: Andres Felipe Cruz

Simulador de algoritmos de planificación de CPU desarrollado en **C++** para la asignatura de **Sistemas Operativos**.

El programa permite leer procesos desde archivos de texto y ejecutar distintos algoritmos de planificación para simular el comportamiento de un scheduler de CPU.

---

# Formato del archivo de entrada

Cada línea del archivo representa un proceso y debe seguir el siguiente formato:

# etiqueta; burst time (BT); arrival time (AT); Queue (Q); Priority (5 > 1)

Ejemplo:

A; 6; 0; 1; 5  
B; 9; 0; 1; 4  
C; 10; 0; 2; 3  
D; 15; 0; 2; 3  
E; 8; 0; 3; 2  

## Descripción de los campos

Etiqueta → identificador del proceso  
Burst Time (BT) → tiempo de CPU requerido por el proceso  
Arrival Time (AT) → momento en que el proceso llega al sistema  
Queue (Q) → cola a la que pertenece el proceso  
Priority → prioridad del proceso (5 es la mayor prioridad)

---

# Queue (Q)

El campo **Queue (Q)** indica a qué cola pertenece el proceso.

El simulador soporta **un máximo de 3 colas**, por lo que los valores válidos son:

1 → Cola 1  
2 → Cola 2  
3 → Cola 3  

Ejemplo:

A; 6; 0; 1; 5  
B; 8; 1; 2; 4  
C; 5; 2; 3; 3  

---

# Convención de archivos de prueba

Los archivos de prueba deben cumplir con las siguientes reglas:

- Deben tener extensión `.txt`
- Cada línea representa un proceso
- Deben seguir exactamente el formato:

etiqueta; BT; AT; Q; Priority

Archivos incluidos en el proyecto:

processes.txt  
processes1.txt  
processes2.txt  

---

# Compilación

Para compilar el programa utilizar **g++**:

g++ main.cpp algorithms.cpp input.cpp -o scheduler
ó
g++ *.cpp -o scheduler

---

# Ejecución

Los archivos de prueba ya se encuentran **definidos directamente en el código (hardcoded)**.

Por lo tanto, el programa **no recibe archivos como argumento desde la línea de comandos**.

Para ejecutar el simulador simplemente se debe correr el programa compilado:

./scheduler

El programa leerá automáticamente los archivos de prueba incluidos en el proyecto.

Si se desea utilizar nuevos conjuntos de pruebas, se debe:

1. Crear un nuevo archivo `.txt` con el mismo formato.
2. Colocar el archivo en el proyecto.
3. Asegurarse de que el nombre del archivo coincida con el utilizado dentro del código.

---

# Algoritmos implementados

El simulador implementa los siguientes algoritmos de planificación de CPU:

- First Come First Serve (FCFS)
- Shortest Job First (SJF)
- Shortest Time to Completion First (STCF) / Preemptive Shortest Job First (PSJF)
- Round Robin (RR)
- Priority Scheduling
- Multi-Level Queue (MLQ)
- Multi-Level Feedback Queue (MLFQ)

Estos algoritmos permiten analizar diferentes estrategias utilizadas en sistemas operativos para la gestión de procesos.

---

# Restricciones del simulador

Para el algoritmo **MLQ (Multi-Level Queue)**:

- El sistema soporta **un máximo de 3 colas de planificación**.
- Los archivos de entrada deben respetar esta limitación.

---

# Posibles mejoras futuras

- Implementar más algoritmos de planificación.
- Permitir configuraciones dinámicas de colas.
- Agregar visualización del diagrama de Gantt.
- Reorganizar el código para evitar duplicación y mejorar la modularidad.
