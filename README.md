## 🌟 Screensaver - Proyecto de Pantalla de Descanso

¡Bienvenido al proyecto de Pantalla de Descanso (Screensaver)!

### 📄 Descripción

Este proyecto se centra en la creación de un programa de pantalla de descanso (screensaver) interactivo y atractivo utilizando C++ y la biblioteca SDL (Simple DirectMedia Layer). Nuestra aplicación mostrará círculos en movimiento en una ventana gráfica y proporcionará información de FPS (cuadros por segundo) en tiempo real.

### ✨ Características Principales

- 🎨 Animación Atractiva: Los círculos se mueven y rebotan en la pantalla, lo que crea una experiencia visual interesante.

- 🌈 Colores Aleatorios: Los círculos se generan con colores pseudoaleatorios, lo que añade variedad y atractivo visual.

- 🎯 Física Simulada: Incorporamos elementos de física y trigonometría para simular el movimiento y las colisiones de los círculos.

- 🚀 Optimización Paralela: Utilizamos OpenMP para acelerar y mejorar gradualmente el programa, lo que permite aprovechar múltiples recursos mediante la ejecución en paralelo.


## 📁 Módulo `main.cpp`

El módulo `main.cpp` es el punto de entrada principal de nuestro proyecto de Pantalla de Descanso (Screensaver). Este archivo de código fuente contiene la función `main`, que coordina la ejecución del programa. A continuación, se explica esta función y su funcionalidad:

### 📋 Función Principal (`main`)

- **`main(int argc, char* argv[])`**: La función `main` es la función principal del programa. Toma argumentos de línea de comandos y coordina la ejecución del screensaver.

### 🚀 Cómo Usar

Para ejecutar el programa, sigue estos pasos:

1. Abre una terminal.
2. Navega al directorio donde se encuentra el proyecto.
3. Compila el código fuente, por ejemplo, usando el comando `g++ main.cpp screensaver.cpp -o screensaver -lSDL2 -lSDL2_ttf -fopenmp`.
4. Ejecuta el programa con el número deseado de círculos como argumento, por ejemplo, `./screensaver 50`.

### 🧾 Argumentos de Línea de Comandos

- **`<Number of circles>`**: Debes proporcionar un número entero positivo como argumento para determinar la cantidad de círculos que se mostrarán en la pantalla. Por ejemplo, `./screensaver 50` mostrará 50 círculos.

### 🌐 Funcionamiento

La función `main` se encarga de:

1. Verificar si se proporciona el número de círculos como argumento y si es válido.
2. Inicializar SDL y SDL_ttf para la creación de ventanas y la representación de texto.
3. Cargar una fuente TTF (TrueType Font) para el texto.
4. Crear una ventana y un renderizador SDL para la representación gráfica.
5. Inicializar la generación de números aleatorios.
6. Crear un vector de círculos y establecer sus posiciones y colores iniciales.
7. Iniciar un bucle principal que maneja eventos de usuario, renderiza los círculos y muestra los FPS.
8. Calcular y actualizar los cuadros por segundo (FPS).
9. Limpia y libera recursos al finalizar.




## 📄 Archivo de Encabezado (screensaver.h)

El archivo de encabezado `screensaver.h` es una parte crucial de nuestro proyecto de screensaver. A continuación, te proporcionamos una descripción de su contenido:

- **`BALL` (Estructura)**: Representa las propiedades de las pelotas en nuestro screensaver. 🎾

- **Funciones**: Declara varias funciones que desempeñan roles esenciales en el programa, como inicializar SDL, cargar fuentes, crear ventanas y renderizadores, manejar eventos, renderizar elementos y limpiar recursos. 🛠️

Este archivo sirve como un plano fundamental que organiza nuestras funciones y estructuras, evitando la duplicación de código y proporcionando una visión general de la estructura de nuestro programa. 📝

## 📁 Módulo `screensaver.cpp`

El módulo `screensaver.cpp` es una parte esencial de nuestro proyecto de Pantalla de Descanso (Screensaver). Este archivo de código fuente contiene la implementación de las funciones principales que controlan el comportamiento del screensaver. A continuación, se describen las funciones y su funcionalidad:

### 📋 Funciones Principales

- **`initializeSDL()`**: Esta función inicializa SDL (Simple DirectMedia Layer) para la gestión de la ventana gráfica y devuelve un valor booleano que indica si la inicialización fue exitosa.

- **`initializeTTF()`**: Inicializa SDL_ttf para la representación de texto y devuelve un valor booleano que indica si la inicialización fue exitosa.

- **`loadFont(const char* fontPath, int fontSize)`**: Carga una fuente TrueType (TTF) desde un archivo dado y devuelve un puntero a la fuente cargada.

- **`createWindow(const char* title, int width, int height)`**: Crea una ventana SDL con el título y las dimensiones especificadas.

- **`createRenderer(SDL_Window* window)`**: Crea un renderizador SDL asociado a la ventana proporcionada.

- **`initializeCircles(vector<BALL>& circles)`**: Inicializa las posiciones y colores de los círculos que se mostrarán en el screensaver.

- **`handleEvents(bool& quit)`**: Maneja eventos de SDL, como la solicitud de cierre de la ventana, y actualiza la variable `quit` en consecuencia.

- **`render(SDL_Renderer* renderer, const vector<BALL>& circles, TTF_Font* font, int displayedFPS)`**: Renderiza los círculos y el texto de FPS en la ventana gráfica utilizando el renderizador proporcionado.

- **`calculateFPS(Uint32 frameTime, int& displayedFPS)`**: Calcula y actualiza los cuadros por segundo (FPS) basados en el tiempo de cuadro proporcionado.

- **`cleanup(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font)`**: Limpia los recursos utilizados por SDL, incluyendo el renderizador, la ventana y la fuente TTF.

### 🌐 Funcionamiento

Este módulo es responsable de la configuración inicial de SDL, la gestión de eventos de usuario, la representación gráfica de círculos y texto, y el cierre ordenado del programa. La optimización y la simulación de movimiento de los círculos se logran utilizando otras funciones y estructuras definidas en el proyecto.

El archivo `screensaver.cpp` trabaja en conjunto con otros módulos y el archivo de encabezado `screensaver.h` para crear una experiencia de pantalla de descanso interactiva y visualmente atractiva.

### 📄 Archivo Relacionado

- [**`screensaver.h`**](screensaver.h): El archivo de encabezado que contiene las declaraciones de funciones y la estructura utilizada en este módulo.

Este módulo es esencial para el funcionamiento del proyecto de Pantalla de Descanso y asegura que la aplicación sea atractiva y responda a eventos de usuario de manera adecuada.


### 🚀 Cómo Usar

1. Clona este repositorio en tu máquina local. [Enlace](https://github.com/aleg001/Proyecto1-Paralela)
2. Compila el código fuente en tu entorno de desarrollo preferido.
3. Ejecuta el programa con el número deseado de círculos como parámetro (por ejemplo, `./screensaver 50`).

### 📦 Dependencias

Asegúrate de tener instaladas las siguientes dependencias antes de compilar y ejecutar el proyecto:

- SDL2 (Simple DirectMedia Layer)
- OpenMP (para la optimización paralela)

### 📖 Bibliografía

Si deseas profundizar en la programación paralela y la optimización de código, aquí hay algunos libros recomendados:

- 📚 "Programación en paralelo con OpenMP" - Pacheco, B. (2007).
- 📚 "Programación paralela y distribuida en C++" - Carretero, J. (2006).
- 📚 "Computación de Alto Rendimiento" - Wilkinson, B. & Allen, M. (2004).

### 🙏 Contribuciones

¡Agradecemos cualquier contribución o sugerencia para mejorar este proyecto! Siéntete libre de enviar pull requests.

### 📝 Licencia

Este proyecto está bajo la Licencia MIT. Puedes encontrar más detalles en el archivo LICENSE.

¡Disfruta explorando y experimentando con nuestro proyecto de Pantalla de Descanso! 👾




