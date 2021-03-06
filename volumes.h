#pragma once

#include <GL/glut.h>

#include <glm/glm.hpp>

float tick = 0.0f;

int vertSize = 6 * sizeof(float);
float vert[] = { // Front face
                 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
                 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

                 // Back face
                 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

                 // Top face
                 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                 0.5f, 0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                -0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,

                 // Bottom face
                 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

                 // Right face
                 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,

                 // Left face
                 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f};

GLint transUni;
GLint viewUni;
GLint projUni;

GLint camUni;

glm::vec3 cameraPos(0.0f, 0.0f, 5.0f);

char* readFileBytes(const char *name);
GLuint loadTexture3D(GLuint shaderProgram);
GLuint compileProgram(std::string vert, std::string frag);
void updateMatrix(GLuint uniform, glm::mat4 matrix);
void updateVec3(GLuint uniform, glm::vec3 vec);
void drawScene();
