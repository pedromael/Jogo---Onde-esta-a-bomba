#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGTH 600

typedef struct {
    int x,y,size;
    int jogador;
} tentativa;

typedef struct{
    int x,y;
    int size;
} bomba;

int numeroDeTentativas = 0;
int jogadorSelecionado = 1;//rand() % 2;
tentativa *tentativas;

void desenhar(int x, int y, int size, SDL_Renderer *render){
    SDL_Rect *rect;
    rect->x = x;
    rect->y = y;
    rect->h = size;
    rect->w = size;
    SDL_RenderDrawRect(render,rect);
}

void aplicar(int *lugarSelecionado) {
    ++numeroDeTentativas;
    tentativas[numeroDeTentativas-1].x = lugarSelecionado[0];
    tentativas[numeroDeTentativas-1].y = lugarSelecionado[1];
    tentativas[numeroDeTentativas-1].size = lugarSelecionado[2]*10;
    tentativas[numeroDeTentativas-1].jogador = jogadorSelecionado;

    if(jogadorSelecionado) jogadorSelecionado--;
    else jogadorSelecionado++;
}

int main()
{
    SDL_Init;
    SDL_Window* janela = SDL_CreateWindow("Find Bomb", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    tentativas = malloc(100 * sizeof(tentativa));
    int lugarSelecionado[3] = {0,0,1}; //0 e X, 1 e Y e 2 a area
    int velocidade = 10;
    int x,y,s;
    bomba *bombas;

    int rodando = 1;
    while (rodando)
    {
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
                rodando = 0;
            else if (evento.type == SDL_KEYDOWN)
            {
                switch (evento.key.keysym.sym)
                {
                    case SDLK_w:
                        lugarSelecionado[1] -= velocidade;
                        break;
                    case SDLK_s:
                        lugarSelecionado[1] += velocidade;
                        break;
                    case SDLK_a:
                        lugarSelecionado[0] -= velocidade;
                        break;
                    case SDLK_d:
                        lugarSelecionado[0] += velocidade;
                        break;
                    case SDLK_UP:
                        lugarSelecionado[2] += velocidade;
                        break;
                    case SDLK_DOWN:
                        lugarSelecionado[2] -= velocidade;
                        break;
                    case SDLK_SPACE:
                        aplicar(lugarSelecionado);
                        lugarSelecionado[2] = 1;
                        break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(render,0,0,0,255);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render,255,255,255,255);
        // Extraindo as coordenadas iniciais e o tamanho
        x = lugarSelecionado[0];
        y = lugarSelecionado[1];
        s = lugarSelecionado[2]; // Tamanho

        // Calculando as coordenadas finais para o retângulo
        int xFinal = x + s * 10;
        int yFinal = y + s * 10;

        // Desenhando as linhas do retângulo
        SDL_RenderDrawLine(render, x, y, xFinal, y);            // Canto superior esquerdo para canto superior direito
        SDL_RenderDrawLine(render, x, yFinal, xFinal, yFinal);  // Canto inferior esquerdo para canto inferior direito
        SDL_RenderDrawLine(render, x, y, x, yFinal);            // Canto superior esquerdo para canto inferior esquerdo
        SDL_RenderDrawLine(render, xFinal, y, xFinal, yFinal);  // Canto superior direito para canto inferior direito


        for (int i = 0; i < numeroDeTentativas; i++)
        { 
            printf("n\n");
            SDL_SetRenderDrawColor(render,0,255,0,255);
            desenhar(tentativas[i].x, tentativas[i].y, tentativas[i].size, render);
        }
        
        SDL_RenderPresent(render);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}