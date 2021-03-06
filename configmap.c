#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "ini.h"
#include "configmap.h"
/** @file*/
/**
@brief print_map Desenha o mapa
@param gridSizex tamanho x do mapa
@param gridSizey tamanho y do mapa
@param grid array do tipo UNIT que contem dados do mapa
*/
void print_map(int gridSizex, int gridSizey, UNIT *grid)
{

		int cellsize = 4;
		int totalx = gridSizex * cellsize; /**5 é o tamanho das células*/
		int totaly = gridSizey * cellsize;
    /* Iterate over each row */
    for(int i=0; i<=totalx; i++)
    {
        /* Iterate over each column */
        for(int j=0; j<=totaly; j++)
        {
        if(i % cellsize == 0 || j % cellsize == 0){

        	printf("* ");
				}else if((i%cellsize == 1 && j%cellsize == 2) && (1 + (i/cellsize) * gridSizex + (j/cellsize)) < 10){
					printf("%d ", (1 + (i/cellsize) * gridSizex + (j/cellsize) ));
				}else if((i%cellsize == 1 && j%cellsize == 2)){
					printf("%d", (1 + (i/cellsize) * gridSizex + (j/cellsize)));
        }else if (i%cellsize == 2 && j%cellsize == 2){
        	printf("%c ", grid[(i/cellsize)*gridSizex +(j/cellsize)].Material[0]);
				}else if (i%cellsize == 3 && j%cellsize == 2){
        	printf("%d ", grid[(i/cellsize)*gridSizex +(j/cellsize)].Building);
        }else{
					printf("  ");
					}
        }
        /* Move to the next line */
        printf("\n");
    }
}

/**
@brief atribuir_valores_ini funcao procura no ficheiro INI os valores e atribuios na grid, depois fecha o ficheiro.
@param grid array do tipo UNIT para receber os valores lidos
@param map estrutura com dimensoes x e y do mapa.
*/
void atribuir_valores_ini(UNIT *grid, MAP_CONFIG map, ini_t *config){
	char casa[3];
	char linha[12];
	for(int i = 0; i<map.ydim; i++){ //Itera sobre a dimensao do mapa e atribui os valores que le da INI na grid*/
		sprintf(linha,"linha %d", ((i%map.ydim)+1));
		for(int j =0; j<map.xdim;j++){
			sprintf(casa,"C%d", ((j%map.xdim)+1));
			ini_sget(config, linha, casa ,"%s", grid[i*map.xdim + j].Material);
			grid[i*map.xdim + j].Quantidade = (int) strtol(strpbrk(grid[i*map.xdim + j].Material, "0123456789"), (char **)NULL, 10);
		}
	}
	ini_free(config); /**fechar ini*/
}
