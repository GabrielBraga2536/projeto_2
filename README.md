# projeto_2
## Descrição

Este projeto é uma simulação de batalha de Pokémon utilizando conceitos de orientação a objetos em C++. O projeto inclui diferentes tipos de Pokémon, treinadores e batalhas entre eles.

## Estrutura do Projeto
- **objs/**: Contém os arquivos de cabeçalho e implementação das classes principais, como `Pokemon`, `Treinador`, `Batalha`, e os diferentes tipos de Pokémon (`PokemonAgua`, `PokemonFogo`, etc.).
- **main.cpp**: Arquivo principal que inicializa o jogo e gerencia a lógica da batalha.
- **main_teste.cpp**: Arquivo de teste para verificar o funcionamento das classes e métodos implementados.
- **imgs/**: Contém os arquivos das imagens utilizadas no projeto.
- **font/**: Contém os arquivos tff das fontes utilizadas no projeto.
- **Ataque.hpp**: Define a classe `Ataque`, que representa os ataques dos Pokémon.
- **Treinador.hpp**: Define a classe `Treinador`, que representa um treinador de Pokémon.
- **Batalha.hpp**: Define a classe `Batalha`, que gerencia a batalha entre dois treinadores.
- **Itens.hpp**: Define a classe `Itens`, que representa os itens que um treinador pode usar.
- **PokemonFogo.hpp**: Define a classe `PokemonFogo`, que representa um Pokémon do tipo Fogo.
- **PokemonAgua.hpp**: Define a classe `PokemonAgua`, que representa um Pokémon do tipo Água.
- **PokemonPlanta.hpp**: Define a classe `PokemonPlanta`, que representa um Pokémon do tipo Planta.
- **PokemonDragao.hpp**: Define a classe `PokemonDragao`, que representa um Pokémon do tipo Dragão.
- **PokemonFantasma.hpp**: Define a classe `PokemonFantasma`, que representa um Pokémon do tipo Fantasma.

## Classes Principais
- **PokemonAgua**: Representa um Pokémon do tipo Água.
- **PokemonFogo**: Representa um Pokémon do tipo Fogo.
- **PokemonPlanta**: Representa um Pokémon do tipo Planta.
- **PokemonDragao**: Representa um Pokémon do tipo Dragão.
- **PokemonFantasma**: Representa um Pokémon do tipo Fantasma.
- **Itens**: Representa os itens que um treinador pode usar.
- **Ataque**: Representa os ataques dos Pokémon.
- **Pokemon**: Classe base para todos os tipos de Pokémon.
- **Treinador**: Representa um treinador de Pokémon, contendo uma equipe de Pokémon e itens.
- **Batalha**: Gerencia a batalha entre dois treinadores.

## Como Compilar

Para compilar o projeto, utilize um compilador C++ como g++. Navegue até o diretório do projeto e execute o seguinte comando:

```sh
g++ main.cpp -I objs -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
```

## Como Executar

Após a compilação, execute o arquivo gerado:

```sh
./a.exe
```

## Dependências

- SDL2
- SDL2_image
- SDL2_ttf

Essas bibliotecas já estão presente no projeto base ao puxá-lo do github. Contudo, certifique-se de ter essas bibliotecas presentes na pasta principal do projeto em seu sistema antes de compilar o projeto.

## Contribuição

Sinta-se à vontade para contribuir com o projeto. Para isso, faça um fork do repositório para utiliza-lo a vontade.

## Licença

