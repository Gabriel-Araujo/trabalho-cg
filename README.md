# Trabalho de computação gráfica

Esse projeto visa desenvolver um ambiente gráfico 3d para
o trabalho da disciplina de Computação Gráfica.

Buscamos desenvolver um ambiente gráfico que se assemelha a um cockpit de um 
veículo, mais precisamente de um carro ou caminhão.

### Integrantes
- Bruno Soares De Oliveira Lopes;
- Gabriel Souza Cruz Araujo;
- Luccas Matheus Torres Freitas.

# Pacotes necessários

Para compilar esse programa é necessário os pacotes:

- OpenGL Utility Toolkit (GLUT);
- Miscellaneous Mesa GL;
- X11 miscellaneous utility library;
- X11 Input extension library.

Que foram instaladas usando os comandos:

    sudo apt install freeglut3-dev && \
    sudo apt install mesa-utils && \
    sudo apt install libxmu-dev libxi-dev && \
    sudo apt-get install libglm-dev && \
    sudo apt install cmake
# Utilidades

Foi utilizado o _cmake_ (v. min. 3.22) como software de build, e o _wsl_ (ubuntu) para compilar
o código para o linux.

# Teste
Execute o comando seguinte comando para verificar se está tudo configurado:
    
    mkdir build && cd build && cmake .. && make && ./trabalhocg


# Referencias

- [OpenGL](https://www.opengl.org/)
- [SkyBox / CubeMap](https://www.youtube.com/watch?v=8sVvxeKI9Pk)
