#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ctime>
#include <iostream>
#include <fstream>

#include "volumes.h"

int main(int argc, char** argv) {
    // Set up windowing system
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("volumes");
    glutDisplayFunc(drawScene);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_3D);

    // Set up glew
    glewInit();

    // Set up attributes
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Set up vertices
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    // Read in shaders
    GLuint shaderProgram = compileProgram("shader.vert", "shader.frag");
    glUseProgram(shaderProgram);

    GLuint tex = loadTexture3D(shaderProgram);

    // MVP matrix
    transUni = glGetUniformLocation(shaderProgram, "trans");
    viewUni = glGetUniformLocation(shaderProgram, "view");
    projUni = glGetUniformLocation(shaderProgram, "proj");

    // Bind attributes
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, vertSize, 0);
    glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, vertSize, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(texAttrib);

    // Begin
    glutIdleFunc(drawScene);
    glClearColor(0.5, 0.25, 0.75, 1.0);
    glutMainLoop();
    return 0;
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the box
    tick += 1.0f;
    glm::mat4 trans = glm::rotate(glm::mat4(), glm::radians(tick), glm::vec3(0.0f, 1.0f, 1.0f));
    updateMatrix(transUni, trans);

    // Do view and projection
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    updateMatrix(viewUni, view);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    updateMatrix(projUni, proj);

    // Draw the scene
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vert) / vertSize);
    glutSwapBuffers();
}

// Taken from codecodex
char* readFileBytes(const char *name) {
    std::ifstream fl(name);
    fl.seekg(0, std::ios::end);
    size_t len = fl.tellg();
    char *ret = new char[len + 1];
    fl.seekg(0, std::ios::beg);
    fl.read(ret, len);
    fl.close();
    ret[len] = '\0';
    return ret;
}

GLuint loadTexture3D(GLuint shaderProgram) {
    // Set up textures
    glActiveTexture(GL_TEXTURE0);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_3D, tex);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load in image
    int width = 2, height = 2, depth = 2;
    float cube[] = {0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,
                    0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 1.0f,
                    0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 1.0f};
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB8, width, height, depth, 0, GL_RGB, GL_FLOAT, cube);
    glUniform1i(glGetUniformLocation(shaderProgram, "sampler"), 0);
    return tex;
}

GLuint compileProgram(std::string vert, std::string frag) {
    char* vertChar = readFileBytes(vert.c_str());
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertChar, NULL);
    glCompileShader(vertexShader);
    delete[] vertChar;

    char* fragChar = readFileBytes(frag.c_str());
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragChar, NULL);
    glCompileShader(fragShader);
    delete[] fragChar;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);

    // Link shaders
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);

    return shaderProgram;
}

void updateMatrix(GLuint uniform, glm::mat4 matrix) {
    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
}
