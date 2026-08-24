#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
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
"    FragColor = vec4(0.5f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

int main()
{
	glfwInit();
	//le dice al glfw que queremos usar la version 3.3 de opengl y que queremos usar el perfil core

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //primer vertice 
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  //segundo vertice
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f   //tercer vertice  
	};
	//(aqui estamos creando una matriz de datos que va a contener los vertices de nuestro triangulo, cada 3 numeros representan un vertice, el primer numero es la coordenada x, el segundo es la coordenada y y el tercero es la coordenada z)

	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//introduce la ventana que creamos como contexto actual de opengl, es decir, que todo lo que hagamos a partir de ahora se va a dibujar en esa ventana
	glfwMakeContextCurrent(window);

	gladLoadGL();

	//esto indica de donde a donde queremos que open gl se renderize
	glViewport(0, 0, 800, 800);
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

	//el VBO es un objeto que contiene los datos de los vertices, es decir, la posicion de cada vertice, el color de cada vertice, etc. y se usa para dibujar los objetos en la pantalla
	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//el glBindBuffer es el que le dice a opengl que vamos a usar ese buffer para dibujar, y el GL_ARRAY_BUFFER es el tipo de buffer que vamos a usar, en este caso un buffer de vertices

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//con esta funcion se alamacena los vertices en el VBO, y el sizeof(vertices) es el tamaño del buffer, y el vertices es el puntero a los datos del buffer, y el GL_STATIC_DRAW es el tipo de uso del buffer, en este caso un buffer estatico es el que se me va modificar solo una vez y se va a usar muchas veces veces)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//con esta funcion le decimos a opengl como interpretar los datos del VBO, el primer parametro es el indice del atributo, el segundo es el numero de componentes del atributo, el tercero es el tipo de dato del atributo, el cuarto es si queremos normalizar los datos o no, el quinto es el tamaño del stride, y el sexto es el offset del atributo
	//es una forma de comunicarse con un shader de vertices con el exterior
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//con esta funcion le decimos a opengl que ya no vamos a usar el VBO, y el 0 es el id del buffer que queremos desactivar
	glBindVertexArray(0);//con esta funcion le decimos a opengl que ya no vamos a usar el VAO, y el 0 es el id del vertex array que queremos desactivar

	//el ultimo numero es la transparencia, 1.0f es opaco y 0.0f es transparente
	glClearColor(0.02f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.02f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);//enlazamos el vao
		glDrawArrays(GL_TRIANGLES, 0, 3);//dibujamos el triangulo, el primer parametro es el tipo de primitiva que vamos a dibujar, el segundo es el indice del primer vertice que vamos a dibujar, y el tercero es el numero de vertices que vamos a dibujar)
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