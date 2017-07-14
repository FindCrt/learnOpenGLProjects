//
//  main.m
//  triangle
//
//  Created by wei shi on 2017/7/13.
//  Copyright © 2017年 wei shi. All rights reserved.
//

#define GLEW_STATIC
#include "glew.h"
#include "SOIL.h"
#include "glfw3.h"

#include <unistd.h>
#include <iostream>

const GLchar *vertexShaderSource =
"#version 330 core                          \n\
layout (location = 0) in vec3 position;     \n\
void main(){                                \n\
    gl_Position = vec4(position, 1.0f);     \n\
}                                           \n\
";
const GLchar *fragmentShaderSource =
"#version 330 core                          \n\
out vec4 color;                             \n\
void main(){                                \n\
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);   \n\
}                                           \n\
";

GLuint program;
GLuint VAO;

int loadShadersAndLinkProgram(){
    
    //load and compile shaders
    
    //vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
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
    
    return 0;
}

void configData(){
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    GLfloat vertices[] = {
        -0.5f, -0.3f, 0.0f,
        0.5f, -0.3f, 0.0f,
        0.0f, 0.8f, 0.0f
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
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
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
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
        
        glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
    }
    
    return 0;
}
