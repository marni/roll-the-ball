//
//  ShaderLoader.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "glshaders.h"
#include "ResourcePath.h"

#include <iostream>
#include <fstream>




//////////////////////////////////////////////////////////////////////////////////
///
///     GLShader
///
//////////////////////////////////////////////////////////////////////////////////


GLShader::GLShader() {
    isLoaded = false;
}


bool GLShader::loadFromFile(std::string filename, int aType) {
    
    // vector of strings of the program Text
    std::vector<std::string> inputText;
    
    if(!readFile(filename, &inputText)) {
        isLoaded = false;
        return isLoaded;
    }
    
    // char* array of the program Text
    const char** programText = new const char*[inputText.size()];
    for (int i = 0; i < inputText.size(); i++) {
        programText[i] = inputText[i].c_str();
    }
    
    shaderId = glCreateShader(aType);
    
    glShaderSource(shaderId, inputText.size(), programText, NULL);
    glCompileShader(shaderId);
    
    delete[] programText;
    
    int compilationStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);
    
    if(compilationStatus == GL_FALSE)
    {
        char infoLog[1024];
        char infoMessage[1536];
        int logLength;
        glGetShaderInfoLog(shaderId, 1024, &logLength, infoLog);
        sprintf(infoMessage, "Error when compiling %s shader.\n\n%s", filename.c_str(), infoLog);
        std::cerr << infoMessage << std::endl;
        return false;
    }
    isLoaded = true;
    return isLoaded;
}


void GLShader::deleteShader() {
    if (!isLoaded) return;
    isLoaded = false;
    glDeleteShader(shaderId);
}




//////////////////////////////////////////////////////////////////////////////////
///
///     GLProgram
///
//////////////////////////////////////////////////////////////////////////////////

GLProgram::GLProgram() {
    isLinked = false;
}

void GLProgram::create() {
    programId = glCreateProgram();
}


void GLProgram::deleteProgram() {
    if (!isLinked) return;
    isLinked = false;
    glDeleteProgram(programId);
}


bool GLProgram::addShader(GLShader *aShader) {
    if (!aShader->isLoaded) return false;
    
    glAttachShader(programId, aShader->shaderId);
    return true;
}


bool GLProgram::linkShaders()
{
    glLinkProgram(programId);
    GLint status;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

        //std::cout << infoLog. << std::endl;
        /* Print vector to console */
        std::copy(infoLog.begin(), infoLog.end(), std::ostream_iterator<char>(std::cout, ""));
        isLinked = false;
        return false;
    }
    
    isLinked = true;
    return status == GL_TRUE;
}


void GLProgram::useProgram()
{
    glUseProgram(programId);
}




void GLProgram::setUniform(std::string aName, glm::mat4* data, int counter)
{
    const int loc = glGetUniformLocation(programId, aName.c_str());
    glUniformMatrix4fv(loc, counter, GL_FALSE, (GLfloat*)data);
}

void GLProgram::setUniform(std::string aName, const glm::mat4 aMatrix)
{
    const int loc = glGetUniformLocation(programId, aName.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat*)&aMatrix);
}


void GLProgram::setUniform(std::string aName, glm::vec3* data, int counter)
{
    const int loc = glGetUniformLocation(programId, aName.c_str());
    glUniform3fv(loc, counter, (GLfloat*)data);
}

void GLProgram::setUniform(std::string aName, const glm::vec3 aMatrix)
{
    const int loc = glGetUniformLocation(programId, aName.c_str());
    glUniform3fv(loc, 1, (GLfloat*)&aMatrix);
}


void GLProgram::setUniform(std::string aName, glm::vec4* data, int counter)
{
    const int loc = glGetUniformLocation(programId, aName.c_str());
    glUniform4fv(loc, counter, (GLfloat*)data);
}

void GLProgram::setUniform(std::string aName, const glm::vec4 aMatrix)
{
    const int loc = glGetUniformLocation(programId, aName.c_str());
    glUniform4fv(loc, 1, (GLfloat*)&aMatrix);
}
