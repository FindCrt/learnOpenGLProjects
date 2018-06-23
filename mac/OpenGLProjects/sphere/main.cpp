//
//  main.m
//  triangle
//
//  Created by wei shi on 2017/7/13.
//  Copyright © 2017年 wei shi. All rights reserved.
//

#define GLEW_STATIC
#include "glew.h"
#include <SOIL/SOIL.h>
#include "glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <unistd.h>
#include <iostream>

#include "ConvienceFunc.h"

const GLchar *vertexShaderSource = ShaderString
(
version 330 core
layout (location = 0) in vec3 position;
void main(){
    gl_Position = vec4(position, 1.0f);
}
);

const GLchar *VSSource_matrix = ShaderString
(
 version 330 core
 layout (location = 0) in vec3 position;
 uniform mat4 matrix;
 void main(){
     gl_Position = matrix * vec4(position, 1.0f);
 }
 );

const GLchar *fragmentShaderSource = ShaderString(
version 330 core
out vec4 color;
void main(){
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
);

GLuint program;
GLuint VAO;
GLuint matrixLoc;

int loadShadersAndLinkProgram(){
    
    //vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VSSource_matrix, 0);
    glCompileShader(vertexShader);
    
    GLint succeed;
    GLchar infoLog[256];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succeed);
    if (!succeed) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog),NULL, infoLog);
        std::cout<< "compile vertex shader error: "<< infoLog << std::endl;
        return -1;
    }
    
    //fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succeed);
    if (!succeed) {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog),NULL, infoLog);
        std::cout<< "compile fragment shader error: "<< infoLog << std::endl;
        return -1;
    }
    
    //attach shaders and link program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &succeed);
    if (!succeed) {
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        std::cout<< "link program error: "<< infoLog << std::endl;
        return -1;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    matrixLoc = glGetUniformLocation(program, "matrix");
    
    return 0;
}

inline void copyVertex(GLfloat *v1, GLfloat *v2){
    for (int i = 0; i<3; i++) {
        *v1 = *v2;
        v1++;
        v2++;
    }
}

GLfloat *genSphereVertices(int count, GLfloat radius, int *actualSize){
    int row = sqrtf(count);
    int column = count/row;
    
    *actualSize = (row-1)*(column-1)*4;
    GLfloat *vertices = new GLfloat[*actualSize*3];
    
    GLfloat pureVertices[row][column*3];
    
    //原始的每个定，不重复也不缺少
    GLfloat rowAngleStep = M_PI/(row+1);
    for (int i = 0; i<row; i++) {
        GLfloat rowAngle = rowAngleStep*(i+1)-M_PI_2;
        
        GLfloat HProjectRadius = cosf(rowAngle)*radius;
        GLfloat z = sinf(rowAngle)*radius;
        
        int index = 0;
        GLfloat columnAngleStep = 2*M_PI/column;
        for (int j = 0; j<column; j++) {
            GLfloat columnAngle = columnAngleStep*j;
            
            pureVertices[i][index++] = cosf(columnAngle)*HProjectRadius;
            pureVertices[i][index++] = sinf(columnAngle)*HProjectRadius;
            pureVertices[i][index++] = z;
        }
    }
    
    //为了使用GL_TRIANGLE_STRIP绘制四边形，重新排列顶点，会有一部分顶点重复
    int index = 0;
    for (int i = 0; i<row-1; i++) {
        GLfloat *row1 = pureVertices[i];
        GLfloat *row2 = pureVertices[i+1];
        
        for (int j = 0; j<column-1; j++) {
            copyVertex(vertices+index++, row1+j);
            copyVertex(vertices+index++, row2+j);
            copyVertex(vertices+index++, row1+j+1);
            copyVertex(vertices+index++, row2+j+1);
        }
    }
    
    return vertices;
}

int actualSize = 0;

void configData(){
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    GLfloat *vertices = genSphereVertices(100, 0.8f, &actualSize);
    for (int i = 0; i<20; i++) {
        printf("%.1f, %.1f, %.1f\n",vertices[3*i],vertices[3*i+1],vertices[3*i+2]);
    }
//    GLfloat vertices[] = standardRectangle;

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //不能解绑EBO
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int main(int argc, const char * argv[]) {
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(400, 400, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        std::cout<< "Failed to create GLFW window" <<std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //glew
    glewExperimental = GLFW_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout<< "Failed to initilize GLEW" <<std::endl;
        return -1;
    }
    
    if (loadShadersAndLinkProgram() < 0) {
        return -1;
    }
    configData();
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        glBindVertexArray(VAO);
        
        
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0), (float)(glfwGetTime()*M_PI/6.0f), glm::vec3(1.f,0.f,0.f));
//        glm::mat4 rotate = glm::mat4(1.0);
        glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, &rotate[0][0]);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, actualSize);
        GLenum err = glGetError(); //GL_INVALID_OPERATION
        if (err != 0) {
            printf("error: %d\n",err);
            break;
        }
        
        glfwSwapBuffers(window);
    }
    
    return 0;
}
