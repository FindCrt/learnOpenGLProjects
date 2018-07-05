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

#include "TFSphere.hpp"

#include "ConvienceFunc.h"

#define LogPoint(p) printf("%.2f, %.2f, %.2f,  ",*(p),*(p+1),*(p+2));

void logRectange(GLfloat *start){
    for (int i = 0; i<4; i++) {
        LogPoint(start)
        start += 3;
    }
    printf("\n");
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
    
    TFSphere *sphere1 = new TFSphere(0.2f);
    TFSphere *sphere2 = new TFSphere(0.2f);
    if (!sphere1->isInitFine() || !sphere2->isInitFine()) {
        return -1;
    }
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 mat1 = glm::translate(glm::mat4(1.0), glm::vec3(-0.5f, -0.5f, 0.f));
        mat1 = glm::rotate(mat1, (float)(glfwGetTime()*M_PI*3.0f), glm::vec3(0.2f,0.3f,1.f));
        mat1 = glm::translate(mat1, glm::vec3(-0.3f, 0.f, 0.f));
        
        sphere1->activate();
        sphere1->applyMatrix(mat1);
        sphere1->draw();
        
        
//        sphere2->activate();
//        glm::mat4 mat2 = glm::translate(rotate, glm::vec3(0.3f, 0.f, 0.f));
//        sphere2->applyMatrix(mat2);
//        sphere2->draw();
        
        GLenum err = glGetError(); //GL_INVALID_OPERATION
        if (err != 0) {
            printf("error: %d\n",err);
            break;
        }
        
        glfwSwapBuffers(window);
    }
    
    return 0;
}
