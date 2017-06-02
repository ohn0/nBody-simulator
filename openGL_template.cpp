#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/common.hpp>
#include <glm/detail/func_matrix.hpp>
#include <glm/detail/func_common.hpp>
#include "Shader.h"
#include "NBody.h"
#include "particle.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
void key_callback(GLFWwindow*, int, int, int, int);
void mouse_callback(GLFWwindow*, double, double);
void keyInteraction();
bool keys[1024];
bool firstMouse = true;
GLFWwindow* window;
int main(){
    glfwInit();
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "n body simulator", nullptr, nullptr);
    int width, height;
    double cursorX, cursorY;
    if(window == nullptr)
    {
        std::cout << "Failed to create GLFW window " << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0,0,width, height);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initializeGLEW" << std::endl;
        return -1;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Shader shader("vertex1", "fragment1");
    NBody N("nBodies.txt");
    std::vector<Particle>::iterator nBodyIterator = N.bodies.begin();
    GLfloat vertices[N.bodies.size() * 2]; //Each body has an x,y coord
    int i = 0;
    while(nBodyIterator != N.bodies.end()){
        vertices[i++] = nBodyIterator->Rx;
        vertices[i++] = nBodyIterator->Ry;
        nBodyIterator++;
    }
    GLuint VBO;
    GLuint VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)  0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    std::cout << N.bodies.size() * 2<< std::endl;
    glm::mat4 orthoProj = glm::ortho(-100.0f, 100.f, -100.f, 100.f, 0.1f, 2.f);
    for(i = 0; i < N.bodies.size() * 2; i++){
        std::cout << vertices[i] << " x " <<  std::endl;
    }
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        keyInteraction();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Use();
        int projLoc = glGetUniformLocation(shader.Program, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(orthoProj));
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINT, 0, N.bodies.size() * 2);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    return 0;
}

void keyInteraction()
{
    if(keys[GLFW_KEY_ESCAPE]){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape kye, we set the WindowShouldClose property to true.
    if(action == GLFW_PRESS){
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE){
        keys[key] = false;
    }
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

//    GLfloat sensitivity = 0.05f;
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//    yaw += xoffset;
//    pitch += yoffset;
//    if(pitch > 89.0f){
//        pitch = 89.0f;
//    }
//    if(pitch < -89.0f){
//        pitch = -89.0f;
//    }
//    glm::vec3 front;
//    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
//    front.y = sin(glm::radians(pitch));
//    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
//    cameraFront = glm::normalize(front);
}
