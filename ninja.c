// author: Vinicius Pittigliani Perego
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
void selec_alg(long *vetor,long  tam);
void quicksort (long v[], long  p, long  r);
long separa(long v[],long p,long r);
long binarySearch(long a[], long item, long low, long high);
void BinaryInsertionSort (long a[], long n);
long bubblesort(long vetor[], long tamanho);
long particiona(long *vetor, long esq, long dir);
void mostra_vetor(long v[]);
void swap(long *n1, long *n2);
void le_vetor();
long shellSort(long arr[], long n);
void mergeSort(long vec[], long vecSize);
void merge(long vec[], long vecSize);
void insertionSort(long arr[], long n);
void salvaArquivo(int algoritmo,int ordem,long  tam,unsigned long  tempExec);
unsigned long  troca=0,comparacao=0;
long main()
{
    le_vetor(); // inicio do programa, le o vetor de um arquivo binario
}
void le_vetor()
{
    /*
        Funcao le_vetor: solicita um arquivo .bin de entrada e
        o tamanho de inteiros que deseja ser lido do arquivo.
    */
    long  *vetor;
    long  tamArray=0;
    char nomeArq[100];
    FILE *arq;
    printf("Insira um arquivo binario .bin com o array:");
    gets(nomeArq);
    arq=fopen(nomeArq,"rb");

    if(!arq)
    {
        printf("Erro ao abrir o arquivo!");

    }
    else
    {
        printf("Insira o tamanho do array:");
        scanf("%d",&tamArray);
        vetor = (long  *) malloc(sizeof(long  *) * tamArray);
        fread(vetor,4,tamArray,arq);
        fclose(arq);
        selec_alg(vetor,tamArray); //apos concluir a leitura do vetor, chama a funcao que seleciona o algoritmo de ordenacao
    }
    fclose(arq);
}

/*
1-Ordenado
2-Randomico
3-Inverso
*/
void selec_alg(long  *vetor,long  tam)
{
    /*
        funcao selec_alg: recebe como parametro o vetor o seu tamanho,
        a funcao solicita a escolha do algoritmo de ordenacao e
        qual a ordem do arquivo de entrada(ordenado,randomico ou inverso).
        Executa a ordenacao, calculando o tempo de execucao do algoritmo.

    */

    struct _timeb start,end; // estrutura para calcular o tempo de execucao

    int alg,ordemAlg;
    printf("Escolha o algoritmo de ordenacao desejado:");
    printf("\n0-insertionsort com busca linear\n1-insertionsort com busca binaria\n"
           "2-shellsort \n3-bubblesort\n4-quicksort\n5-mergesort");

    printf("\nAlgoritmo:");
    scanf("%d",&alg);
    printf("\nQual a ordem do array?"
           "\n0-Ordenado \n1-Randomico \n2-Inverso");
    printf("\nOrdem:");
    scanf("%d",&ordemAlg);
    _ftime(&start); //inicia a contagem do tempo
    switch(alg)
    {
    case 0:
        insertionSort(vetor,tam);
        break;
    case 1:
        BinaryInsertionSort(vetor,tam);
        break;
    case 2:
        shellSort(vetor,tam);
        break;
    case 3:
        bubblesort(vetor,tam);
        break;
    case 4:
        quicksort(vetor,0,tam-1);
        break;
    case 5:
        mergeSort(vetor,tam);
        break;
    default:
        break;
    }
    _ftime(&end); // pega o tempo final da execucao.
    free(vetor);
    unsigned long   tempoExecucao = (unsigned long ) (1000 * (end.time - start.time)  + (end.millitm - start.millitm)); // calcula o tempo do execucao(final-inicial)


    salvaArquivo(alg,ordemAlg,tam,tempoExecucao); //chama a funcao para salvar as informacoes no arquivo de saida



}
void salvaArquivo(int algoritmo,int ordem,long  tam,unsigned long  tempExec)
{
    /*
        funcao salvaArquivo: recebe como parametro a chave do algoritmo e a sua ordem junto com o tamanho e o tempo
        de execucao
    */
    const char *algString[6];
    const char *ordemString[3];
    ordemString[0]="ordenado";
    ordemString[1]="randomico";
    ordemString[2]="inverso";
    algString[0]="insertionsort busca linear";
    algString[1]="insertionsort busca binaria";
    algString[2]="shellsort";
    algString[3]="bubblesort";
    algString[4]="quicksort";
    algString[5]="mergesort";
    FILE *saida=fopen("resultados_00242287.txt","a");
    fprintf(saida,"\n%s,%s,%d,%u,%u,%u",algString[algoritmo],ordemString[ordem],tam,troca,comparacao,tempExec); //salva as informacoes no arquivo de saida
    fclose(saida);
}

/**
    A partir daqui estao as implementacoes dos algoritmos de ordenacao
*/
void merge(long vec[], long vecSize)
{
    long mid;
    long i, j, k;
    int* tmp;

    tmp = (int*) malloc(vecSize * sizeof(int));
    if (tmp == NULL)
    {
        exit(1);
    }
    comparacao++;
    mid = vecSize / 2;

    i = 0;
    j = mid;
    k = 0;
    while (i < mid && j < vecSize)
    {
        if (vec[i] <= vec[j])
        {
            troca++;
            comparacao++;
            tmp[k] = vec[i++];
        }
        else
        {
            troca++;
            comparacao++;
            tmp[k] = vec[j++];
        }
        ++k;
    }

    comparacao++;
    if (i == mid)
    {
        while (j < vecSize)
        {
            tmp[k++] = vec[j++];
            troca++;
            comparacao++;
        }

    }
    else
    {
        while (i < mid)
        {
            troca++;
            comparacao++;
            tmp[k++] = vec[i++];

        }
    }

    for (i = 0; i < vecSize; ++i)
    {
        vec[i] = tmp[i];
        troca++;
        comparacao++;
    }

    free(tmp);
}

void mergeSort(long vec[], long vecSize)
{
    long mid;

    if (vecSize > 1)
    {
        mid = vecSize / 2;
        mergeSort(vec, mid);
        mergeSort(vec + mid, vecSize - mid);
        merge(vec, vecSize);
    }
}
void quicksort (long v[], long p, long r)
{
    long j;
    if (p < r)
    {
        j = particiona (v, p, r);
        quicksort (v, p, j-1);
        quicksort (v, j+1, r);
    }


}

long particiona(long *vetor, long esq, long dir)
{
    long i=esq+1, j=dir, pivo=esq;
    while(j>i)
    {
        while(vetor[i]<vetor[pivo] && i<dir)
        {
            i++;
            comparacao++;
        }
        while(vetor[j]>=vetor[pivo] && j>esq)
        {
            j--;
            comparacao++;
        }

        if(i<j && vetor[i]>vetor[j])
        {
            swap(&vetor[i], &vetor[j]);
            troca++;
            comparacao++;
        }
    }
    if(vetor[j]<vetor[pivo])
    {
        troca++;
        comparacao++;
        swap(&vetor[pivo], &vetor[j]);
    }
    return j;
}

void insertionSort(long arr[], long n)
{


    long i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i-1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
            troca++;
            comparacao++;
        }
        arr[j+1] = key;
    }

}

long binarySearch(long a[], long item, long low, long high)
{
    comparacao++;
    if (high <= low)
        return (item > a[low])?  (low + 1): low;

    long mid = (low + high)/2;

    comparacao++;
    if(item == a[mid])
        return mid+1;

    comparacao++;
    if(item > a[mid])
        return binarySearch(a, item, mid+1, high);
    return binarySearch(a, item, low, mid-1);
}

// Function to sort an array a[] of size 'n'
void BinaryInsertionSort (long a[], long n)
{
    long i, loc, j, k, selected;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];

        // find location where selected sould be inseretd
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc)
        {
            comparacao++;
            troca++;
            a[j+1] = a[j];
            j--;
        }
        troca++;
        a[j+1] = selected;
    }
}
long bubblesort(long vetor[], long tamanho)
{


    long i,j;
    for(i=tamanho-1; i >=1; i--)
    {

        for(j=0; j < i ; j++)
        {
            comparacao++;
            if(vetor[j]>vetor[j+1])
            {
                swap(&vetor[j], &vetor[j+1]);
                troca++;

            }

        }
    }

}

/*
Recebe um vetor de numeros desordenados e sem elementos repetidos e os ordena em ordem crescente.
long p->pivo
long r->fim do vetor.
*/


void swap(long *n1, long *n2)
{
    long troca = *n1;
    *n1 = *n2;
    *n2 = troca;
}

long shellSort(long arr[], long n)
{


    long gap,i;
    // Start with a big gap, then reduce the gap
    for (gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            long temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            long j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                comparacao++;
                arr[j] = arr[j - gap];
                troca++;
            }
            //  put temp (the original a[i]) in its correct location
            troca++;
            arr[j] = temp;

        }
    }


}
