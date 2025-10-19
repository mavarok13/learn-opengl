#include <iostream>

#include <SFML/Window.hpp>
#include <glad/glad.h>

#include <stb_image.h>

#include "shader_loader.hpp"

const char * vertex_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL3/vertex.glsl";
const char * fragment_shader_path = "D:/dev/source/learn-opengl/HelloOpenGL3/fragment.glsl";

const char * texture_image_path = "D:/dev/source/learn-opengl/resources/SBSTinyTexturePack2/512x512/Plaster/Plaster_14-512x512.png";
const char * texture2_image_path = "D:/dev/source/learn-opengl/resources/SBSTinyTexturePack2/512x512/Tile/Tile_03-512x512.png";

int main() {
    unsigned window_width = 720u;
    unsigned window_height = 480u;

    sf::Window window(sf::VideoMode{sf::Vector2u{ window_width, window_height }}, L"Texture", sf::Style::Titlebar | sf::Style::Close);
    window.setActive(true);

    if (!gladLoadGL()) {
        std::cerr << "Couldn't load GL" << std::endl;
        return EXIT_FAILURE;
    }

    stbi_set_flip_vertically_on_load(true);

// * PREPARE DATA AND SHADER PROGRAM * //

    float attribs[] = {
        // vertices         //colors                                        //texture coords
        .5f, .5f, .0f,      (0.f/255.f), (252.f/255.f), (252.f/255.f),      1.f, 1.f,
        -.5f, .5f, .0f,     (0.f/255.f), (122.f/255.f), (252.f/255.f),      0.f, 1.f,
        -.5f, -.5f, .0f,    (109.f/255.f), (0.f/255.f), (252.f/255.f),      0.f, 0.f,
        .5f, -.5f, .0f,     (252.f/255.f), (210.f/255.f), (0.f/255.f),      1.f, 0.f
    };

    unsigned indices[] = {
        0, 1, 3,
        3, 1, 2
    };

    shader_loader::ShaderProgram program(vertex_shader_path, fragment_shader_path);

    unsigned VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(attribs), attribs, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(6*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    int texture_width, texture_height, texture_image_channels;
    unsigned char * image_data = stbi_load(texture_image_path, &texture_width, &texture_height,  &texture_image_channels, STBI_rgb_alpha);

    unsigned texture;
    glGenTextures(1, &texture);
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::cout << "[INFO]: Loading texture..." << std::endl;
    if(image_data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "[INFO]: Texture loaded successfuly" << std::endl;
        stbi_image_free(image_data);
    } else {
        std::cerr << "[ERROR]: Couldn't load texture" << std::endl;
    }

    unsigned texture2;
    glGenTextures(1, &texture2);
    // glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texture2_width, texture2_height, texture2_channels;
    unsigned char * image2_data = stbi_load(texture2_image_path, &texture2_width, &texture2_height, &texture2_channels, STBI_rgb_alpha);

    std::cout << "[INFO]: Loading texture..." << std::endl;
    if(image2_data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2_width, texture2_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "[INFO]: Texture loaded successfuly" << std::endl;
        stbi_image_free(image2_data);
    } else {
        std::cerr << "[ERROR]: Couldn't load texture" << std::endl;
    }


    program.SetUniform1i("base_texture", 1);
    program.SetUniform1i("noise_texture", 0);

    // * =============================== * //
    
    std::cout << "[INFO]: Start program" << std::endl;
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    bool is_running = true;
    while (is_running) {
        while(const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                is_running = false;
            } else if (const auto * resized = event->getIf<sf::Event::Resized>()) {
                glViewport(0, 0, resized->size.x, resized->size.y);
            }
        }

        glClearColor(.0f, .0f, .0f, 1.0f);
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.display();
    }

    window.close();

    return 0;
}