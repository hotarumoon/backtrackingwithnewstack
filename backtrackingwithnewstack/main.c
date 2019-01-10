#define N 8
#include<stdio.h>
#include<stdlib.h>

typedef int bool;
#define true 1
#define false 0
int stack[N];
int top=-1;



void printSolution(int board[N][N]);
bool isSafe(int board[N][N], int row, int col, int * sayac);
bool solveNQUtil(int board[N][N], int col, int *sayac);
bool solveNQ(int *sayac);
void push(int x,int *sayac);
void pop(int *sayac);
int returntop();
bool isEmpty();
void print_stack();

void push(int x,int *sayac)
{
    if(top==N)
    {
        printf("Error, stack overflow ");
        return;
    }
    top++;
    stack[top]=x;
     *sayac+= 1;;
}

void pop(int *sayac)
{	if(top==-1){
    printf("Error, no element to pop");
    return;
    }
    top --;
    sayac -=1;
}

int returntop()
{
    return stack[top];
}

bool isEmpty()
{
    if(top==-1)
        return true;
    else
        return false;
}
void print_stack(){
    int i;
    printf("\n Stack:");
    for(i=0;i<=top;i++)
        printf("%d",stack[i]);
    printf("\n");
}



//Satranc tahtasının son halini yazdırır
void printSolution(int board[N][N])
{
    int i,j;
    printf("\n");
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
            printf(" %d ", board[i][j]);
        printf("\n");
    }
}
//verilen konumdaki vezirin tahtaya yerlestirilip yerlestirilemeyeceğini kontrol eden fonksiyondur.
//Bu fonksiyon çağrıldığında col vezirleri 0 dan col-1 e kadar yerleştirildiği düşünülür,
//Yani yerleşip yerleşemediğine bakarken sol tarafına bakmak yeterlidir.
bool isSafe(int board[N][N], int row, int col, StackNodePtr stackPtr,int * sayac)
{
    int i, j;
    
    push(row,col,sayac);
    /* Bu satır için sol tarafı kontrol et */
    for (i = 0; i < col; i++)
    {
        if (board[row][i]){
            pop(stackPtr,sayac);
            return false;
        }
        
    }
    
    /* Sol taraftaki üst diyagonali kontrol et */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j]){
            pop(&stackPtr,sayac);
            return false;
        }
    }
    
    /* Sol taraftaki alt diyagonali kontrol et */
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j]){
            pop(&stackPtr,sayac);
            return false;
        }
        
    }
    return true;
}


bool solveNQUtil(int board[N][N], int col, StackNodePtr stackPtr,int *sayac)
{
    int i;
    /* base case: Tüm vezirler yerleşmişse, true döndür */
    if (col >= N)
        return true;
    
    /* Parametre olarak verilen sütun için işlem yap ve hangi satıra yerleştirilebilir olduğunu döngü içinde bul*/
    for ( i = 0; i<N; i++)
    {
        /* Verizin board[i][col] pozisyonuna yerleşip yerleşemeyeceğini kontro et*/
        if ( isSafe(board, i, col,&stackPtr,sayac) )
        {
            /* true dönmüşse board[i][col] pozisyonuna yerleştir. */
            board[i][col] = 1;
            //push(stackPtr,i,col,sayac);//isSafe de zaten push ediyor
            
            /* Kalan veziirler için fonksiyonu recursive bir sonraki columndan başlayacak şekilde çağır */
            if ( solveNQUtil(board,(col+1),&stackPtr,sayac) == true )
                return true;
            
            /* board[i][col] pozisyonuna yerleştirilen vezir ile N vezir yerleştirileilecek sonuç bulunamıyorsa o pozisyondan
             veziri kaldır ve backtracking yap*/
            board[i][col] = 0; // BACKTRACK
            pop(&stackPtr,sayac); //yerlestirilebilir ama backtrackten dolayı geri alınacak bir eleman oldugu icin pop
        }
    }
    
    /* Eğer vezir o pozisyondaki hiçbir yere yerleşemiyorsa false döndür */
    return false;
}

/* Backtracking yapan fonksiyon. Vezir yerleştirilemiyorsa false döndürür, yerleşebiliyorsa true döndürerek
 vezirlerin yerleşimini gösterir. Bulduğu ilk doğru sonucu gösterir, diğer olası sonuçları aramaz*/
bool solveNQ(StackNodePtr stackPtr,int *sayac)
{
    int board[N][N] ={0};
    
    if ( solveNQUtil(board, 0,&stackPtr,sayac) == false )
    {
        printf("Solution does not exist");
        return false;
    }
    
    printSolution(board);
    return true;
}


int main()
{
    int sayac=0;
    //int *sayacptr=&sayac;
    //  int x=5,y=6;
    StackNodePtr stackPtr=NULL;
    
    //push(&stackPtr,x,y,&sayac);//sayacptr);
    // push(&stackPtr,6,7,&sayac);//,sayacptr);
    printStack(stackPtr);
    if(!isEmpty(stackPtr)){
        pop(&stackPtr,&sayac);//,sayacptr);
        printf("Value is popped\n");
        
    }
    
    solveNQ(&stackPtr,&sayac);
    printf("sayac:%d\n",sayac);
    
    
    getchar();
    return 0;
}
