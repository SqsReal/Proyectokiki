//ahhh guardate yaaaaaaa
//osea yaaaaa
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>
#include <cmath>
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(184.2/255.0f, 134.0/255.0f, 11.0/255.0f, 1.0f);\n"
//Acuerdate que el color es en RGB 
//cabe aclaear que el rango solo va de 0.0 a 1.0, por lo que si queremos un color mas intenso debemos dividirlo entre 255.0f
"}\n";
std::vector<float> vertices;

// VBO Y VAO
GLuint VBO, VAO;

// Variables para los clicks
bool primerClick = true;

int ultimoX = 0;
int ultimoY = 0;


// Declaramos Bresenham antes de utilizarla
void Bresenham(int x1, int y1, int x2, int y2, std::vector<float>& vertices);

void actualizarVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),vertices.data(),GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;

		// Obtenemos la posicion del mouse
		glfwGetCursorPos(window, &xpos, &ypos);

		int x = (int)xpos;
		int y = (int)ypos;


		// Si es el primer click solamente guardamos el punto
		if (primerClick)
		{
			ultimoX = x;
			ultimoY = y;

			primerClick = false;

			std::cout << "Primer punto: ("
				<< x << ", " << y << ")" << std::endl;
		}


		// Si ya teniamos un punto anterior
		else
		{
			// Dibujamos una linea desde el punto anterior
			// hasta el nuevo punto
			Bresenham(ultimoX, ultimoY, x, y, vertices);

			// Actualizamos el VBO para que OpenGL
			// conozca los nuevos vertices
			actualizarVBO();

			std::cout << "Linea: ("
				<< ultimoX << ", " << ultimoY
				<< ") -> ("
				<< x << ", " << y << ")" << std::endl;


			// El nuevo punto se convierte en el punto anterior
			ultimoX = x;
			ultimoY = y;
		}
	}
}
void Bresenham(int x1, int y1, int x2, int y2, std::vector<float>& vertices)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int error = dx - dy;
	while (true)
	{
		// Convertimos el pixel a coordenadas de OpenGL
		float x = (2.0f * x1 / 799.0f) - 1.0f;
		float y = 1.0f - (2.0f * y1 / 799.0f);
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);
		if (x1 == x2 && y1 == y2)
			break;
		int error2 = 2 * error;
		if (error2 > -dy)
		{
			error -= dy;
			x1 += sx;
		}
		if (error2 < dx)
		{
			error += dx;
			y1 += sy;
		}
	}
}

int main()
{
	glfwInit();
	//le dice al glfw que queremos usar la version 3.3 de opengl y que queremos usar el perfil core

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//TODO este codigo que puse en comentarios es para
	// generar la grilla automaticamente
	//std::vector<float> vertices;
	//y alamacenamos los vertices con este de arriba, creciendo automaticamente con el ciclo for
	//const int Filas = 2;
	//const int Columnas = 2;
	//float espaciado = 0.1f;//aqui agregamos un pequeño espacio para que los cuadrso bo esten tan pegados
	//float ancho = 2.0f / Columnas - espaciado;
	//el ancho seria el ancho de cada cuadrado
	//el alto seria el alto de cada cuadrado
	//float alto = 2.0f / Filas - espaciado;
	//for (int fila = 0; fila < Filas; fila++)
	//{
		// Posicion Y de cada linea horizontal
		//float y = -1.0f + fila * alto;

		// Convertimos la coordenada Y de OpenGL a pixel
		//int yPixel = (int)((1.0f - y) * 799.0f / 2.0f);

		// Dibujamos la linea horizontal completa
		//Bresenham(0, yPixel, 799, yPixel, vertices);
	//}
	//for (int columna = 0; columna < Columnas; columna++)
	//{
		// Posicion X de cada linea vertical
		//float x = -1.0f + columna * ancho;

		// Convertimos la coordenada X de OpenGL a pixel
		//int xPixel = (int)((x + 1.0f) * 799.0f / 2.0f);

		// Dibujamos la linea vertical completa
		//Bresenham(xPixel, 0, xPixel, 799, vertices);
	//}
	//este es para el cuadrado
	//GLfloat vertices[] = {
		//-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //primer vertice 
		// 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  //segundo vertice
		//0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f   //tercer vertice
		// eso es para generar un triangulo equilatero
		//-0.5f, -0.5f, 0.0f, //primer vertice
		//0.5f, -0.5f, 0.0f, //segundo vertice
		//0.5f,0.5f, 0.0f, //tercer vertice
		//para el primer triangulo invertido
		//0.5f, 0.5f, 0.0f, //primer vertice para el triangulo invertido
		//-0.5, 0.5f, 0.0f, //el segundo vertice para el triangulo invertido
		//-0.5F, -0.5f, 0.0f,//el tercer vertice para el triangulo invertido
		//Y este para el segundo triangulo invertido
	//};
	//(aqui estamos creando una matriz de datos que va a contener los vertices de nuestro triangulo, cada 3 numeros representan un vertice, el primer numero es la coordenada x, el segundo es la coordenada y y el tercero es la coordenada z)

	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Funcion que detecta los clicks del mouse
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//introduce la ventana que creamos como contexto actual de opengl, es decir, que todo lo que hagamos a partir de ahora se va a dibujar en esa ventana
	glfwMakeContextCurrent(window);

	gladLoadGL();

	//esto indica de donde a donde queremos que open gl se renderize
	glViewport(0, 0, 800, 800);

	//shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//el shader program es un programa que contiene los shaders que vamos a usar para dibujar, en este caso el vertex shader y el fragment shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//El linking es el proceso de unir los shaders en un programa que pueda ser ejecutado por la GPU, es decir, que pueda ser usado para dibujar
	//para eso lo pasamos a la funcion glLinkProgram, y lo pasamos a la referencia del sistema de sombreado
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//(los eliminamos porque ya estan en el programa y no los necesitamos mas, ademas de que nos ahorramos memoria)
	//El VBO Y VBA
	//el VBO es un objeto que contiene los datos de los vertices, es decir, la posicion de cada vertice, el color de cada vertice, etc. y se usa para dibujar los objetos en la pantalla
	//el VAO es un objeto que contiene la configuracion de los atributos de los vertices, es decir, como se van a interpretar los datos del VBO, y se usa para dibujar los objetos en la pantalla

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//el glGenBuffers es el que genera el buffer, y el 1 es el numero de buffers que queremos generar(es el que le dice a opengl que vamos a usar ese buffer para dibujar)
	//y el GL_ARRAY_BUFFER es el tipo de buffer que vamos a usar,
	//en este caso un buffer de vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//el glBindBuffer es el que le dice a opengl que vamos a usar ese buffer para dibujar, y el GL_ARRAY_BUFFER es el tipo de buffer que vamos a usar, en este caso un buffer de vertices

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);//con esta funcion se alamacena los vertices en el VBO, y el sizeof(vertices) es el tamaño del buffer, y el vertices es el puntero a los datos del buffer, 
	//y el GL_DYNAMIC_DRAW porque ahora los vertices van a cambiar
	//cada vez que hagamos click
	//y ten encuenta que el vertices.data es que da los datos del vector

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//con esta funcion le decimos a opengl como interpretar los datos del VBO, el primer parametro es el indice del atributo, el segundo es el numero de componentes del atributo, el tercero es el tipo de dato del atributo, el cuarto es si queremos normalizar los datos o no, el quinto es el tamaño del stride, y el sexto es el offset del atributo
	//es una forma de comunicarse con un shader de vertices con el exterior
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//con esta funcion le decimos a opengl que ya no vamos a usar el VBO, y el 0 es el id del buffer que queremos desactivar
	glBindVertexArray(0);//con esta funcion le decimos a opengl que ya no vamos a usar el VAO, y el 0 es el id del vertex array que queremos desactivar

	//el ultimo numero es la transparencia, 1.0f es opaco y 0.0f es transparente
	glClearColor(55.0f, 0.0f, 0.0f, 1.0f);
	//elClearColor sirve para definir el color de fondo de la ventana, y el glClear sirve para limpiar la ventana con ese color de fondo
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.02f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);//enlazamos el vao
		glPointSize(2.0f);
		glDrawArrays(GL_POINTS, 0, vertices.size() / 3);//dibujamos el triangulo, el primer parametro es el tipo de primitiva que vamos a dibujar, el segundo es el indice del primer vertice que vamos a dibujar, y el tercero es el numero de vertices que vamos a dibujar)
		//en este caso el vertices.size()/3 es porque cada vertice tiene 3 componentes, x, y, z, y el vertices.size() es el numero total de componentes, por lo que si dividimos entre 3 obtenemos el numero de vertices
		//AQUI YA dibujamos los vertices generados por bresenham
		glfwSwapBuffers(window);
		// funcion que permite que procese todos los eventos extraidos, como que la ventana cambie de tamaño, que se cierre, etc.
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
