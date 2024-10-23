#include <stdio.h>

// Game info
void inf(){
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-\n");
    printf("\n-=-=-=-=-=-=-=- STONE KILLER -=-=-=-=-=-=-=-\n\n");
    printf("Objetivo: Eliminar o máximo de pedras possíveis.\n\n");
    printf("Para eliminar as pedras, o jogador deve indicar\n");
    printf("a posição de uma pedra no tabuleiro e, depois,\n");
    printf("qual a posição de destino desta pedra.\n");
    printf("Toda pedra que estiver entre as posições será \n");
    printf("eliminada, lembrando que a pedra não pode pular \n");
    printf("casas vazias e a casa de destino deve estar vazia.\n\n");
    printf("Digite 0 para encerrar o jogo.\n\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-\n\n");
}

// Initializing the board 
void init_game(char board[8][8], int *moves, int *stones){
    // Initializing the game stats
    *stones = 0;
    *moves = 0;
    
    // Setting the stones
    for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                board[i][j] = '*';
            }
        }
    
    // Setting the empty boxes
    for(int i = 2; i < 6; i++){
            for(int j = 2; j < 6; j++){
                board[i][j] = '-';
            }
        }
    
}

// Printing the board
void print_board(char board[8][8]){
    printf("   ");
        for( int i = 0; i < 8; i++){
            printf("%d ", i + 1);
        }
        printf("\n");
        for(int i = 0; i < 8; i++){
            printf("%2d ", i + 1);
            for(int j = 0; j < 8; j++){
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
}

// Checking if the value is between 1 and 8 
int checker(int p){
    if(p != 0){
        while(p < 0 || p > 8){
            printf("Valor inválido! A posição deve estar entre 1 e 8.\n");
            printf("Digite um valor válido, jegue: ");
            scanf("%d", &p);
        }    
    }
    
    return p;
}


// Requesting the initial position
void req_init_pos(int *lin, int *col, char board[8][8]){
    int l, c;       // Auxiliary variable
    int havestone;  // Return value
    
    do{
        // Position Input
        printf("\n-=- POSIÇÃO DE ORIGEM -=-\n");
        printf("Digite a posição da linha: ");
        scanf("%d", &l);
        l = checker(l); // Checking the line
        if(l != 0){
            
             
            printf("Digite a posição da coluna: ");
            scanf("%d", &c);
            if(c != 0){
                c = checker(c); // Checking the column
                
                // Checking if there is a stone
                if(board[l - 1][c - 1] == '-'){ // Do not have a stone 
                    printf("\nA casa inicial deve conter uma pedra!\n");
                    printf("Tente novamente...\n");
                    havestone = 0;
                }
                else{ // In fact have a stone
                    havestone = 1;
                }
            }
            
        }    
        
    } while(havestone == 0 && l != 0 && c != 0); // Repeat the code if there isn't a stone 
    
    
    *col = c;       // Assign the checked value
    *lin = l;       // Assign the chekced value
    
    
}

// Checking if the move is diagonal
int isdiagonal(int *ol, int *oc, int dl, int dc, char board[8][8]){
    // Main diagonal down
    if((dl - *ol) == (dc - *oc) && dl - *ol > 1){
        // Checking if there is a empty square in the move
        for(int i = 1; i + *ol < dl; i++){
            if(board[i + *ol - 1][i + *oc - 1] == '-'){
            return 1;
            }    
        }
        
        return 0;        
        
        
    }
    
    // Main diagonal up
    else if((dl - *ol) == (dc - *oc) && *ol - dl > 1){
        // Checking if there is a empty square in the move
        for(int i = 1; i + dl < *ol; i++){
            if(board[*ol - i - 1][*oc - i - 1] == '-'){
            return 1;
            }    
        }
        
        return 0;        
        
        
    }
    // Secondary diagonal down
    else if((dl - *ol) == (*oc - dc) && *ol - dl > 1){
        // Checking if there is a empty square in the move
        for(int i = 1; i + dl < *ol; i++){
            if(board[*ol - i - 1][*oc + i - 1] == '-'){
            return 1;
            }    
        } 
        
        return 0;
    }
    
    // Secondary diagonal up 
    else if((dl - *ol) == (*oc - dc) && dl - *ol > 1){
        // Checking if there is a empty square in the move
        for(int i = 1; i + *ol < dl; i++){
            if(board[i + *ol - 1][*oc - i - 1] == '-'){
            return 1;
            }    
        }
        
        return 0;
    }
    // Not diagonal 
    else{
        return 1;
    }
    
}


// Requesting the destiny position
int req_dest_pos(int *dlin, int *dcol, int *ilin, int *icol, char board[8][8]){
    int l, c; // Auxiliary variable
    int isempty; // Return value if the square is empty 
    int dgn; // Return value of the function is diagonal 

    // Position Input
    printf("\n-=- POSIÇÃO DO DESTINO -=-\n");
    printf("Digite a posição da linha: ");
    scanf("%d", &l);
    l = checker(l); // Checking the line
    
    if(l != 0){
        printf("Digite a posição da coluna: ");
        scanf("%d", &c);  
        if(c != 0){
            c = checker(c); // Checking the column
            
            // Checking the diagonal 
            dgn = isdiagonal(ilin, icol, l, c, board);
            
            // Checking if the square is empty 
            if(board[l - 1][c - 1] == '*'){ // Is not empty  
                printf("\nA casa de destino deve estar vazia!\n");
                printf("Tente novamente...\n");
                return -1;
            }
            
            // If the origin and destiny are equal
            else if(l == *ilin && c == *icol){ 
                printf("\nA casa de destino deve estar vazia!\n");
                printf("Tente novamente...\n");
                return -1;
            }
            
            else if(dgn == 1){ // If is not diagonal 
                printf("Movimento inválido.\n");
                return -1;
            }
        }
    }
    
    *dcol = c;       // Assign the checked value
    *dlin = l;       // Assign the chekced value
    return 0;
}

// Moving the stone 
int move(int ol, int oc, int dl, int dc, char board[8][8], int error){
    int stone = 0; // Amount of eliminated stones
    
    if(dl != 0 && dc != 0 && error != -1){
        board[ol - 1][oc - 1] = '-'; // Setting the initial postion as empty 
        board[dl - 1][dc - 1] = '*'; // Setting a stone in the destiny
        
        // Setting the path squares
        
        
        // Main diagonal
        if((dl - ol) == (dc - oc)){
            // Down 
            for(int i = 1; i + ol < dl; i++){
                board[i + ol - 1][i + oc - 1] = '-';
                stone++;
                
            }
            
            // Up  
            for(int i = 1; i + dl < ol; i++){
                board[dl + i - 1][dc + i - 1] = '-';
                stone++;
                
            } 
            
        }
        
        // Secondary diagonal 
        else if((dl - ol) == (oc - dc)){
            // Down 
            for(int i = 1; i + dl < ol; i++){
                board[ol - i - 1][oc + i - 1] = '-';
                stone++;
            }
            // Up 
            for(int i = 1; i + ol < dl; i++){
                board[i + ol - 1][oc - i - 1] = '-';
                stone++;
            }  
        }
    
        return stone; // returning the number of eliminated stones
        
    }
    
    
    
}

// Printing the move stats
void print_mv_stats(int ol, int oc, int dl, int dc, int stone, int error){
    if(dl != 0 && dc != 0 && error != -1){
        printf("Da linha: %d coluna: %d para linha:  %d coluna: %d.\n", ol, oc, dl, dc);
        printf("Número de pedras eliminadas: %d.\n\n", stone);
    }
}
    
// Final stats 
void stats(int *moves, int stone, int *ttstone, int error, int fin_lin, int fin_col){
    if(fin_lin != 0 && fin_col != 0 && error != -1){
        *moves = *moves + 1;
        *ttstone = *ttstone + stone;    
    }
    
}

// Printing the game statistics 
void printstats(int *move, int *stone){
    printf("\n-=-=- FIM DA PARTIDA -=-=-\n\n");
    printf("Número de jogadas: %d\n", *move);
    printf("Pedras eliminadas: %d\n", *stone);
    if(*stone < 30){
        printf("Nível atingido: Extremamente fácil.\n");
    }
    else if(*stone > 29 && *stone < 40){
        printf("Nível atingido: Fácil.\n");
    }
    else if(*stone > 39 && *stone < 45){
        printf("Nível atingido: Difícil.\n");
    }
    else if(*stone > 44 && *stone < 48){
        printf("Nível atingido: Extremamente Difícil.\n");
    }
}

// Asking the user if he wants to play again 
void play_again(char *cont){
    char c;
    
    do{
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
        printf("Deseja jogar novamente? (S/N): ");
        scanf(" %c", &c);
        
        if(c != 's' && c != 'S' && c != 'n' && c != 'N'){
            printf("Opção inválida!\nDigite 'S' para sim ");
            printf("ou 'N' para não.\n");
            printf("Tente novamente...\n\n");
        }
    }while(c != 's' && c != 'S' && c != 'n' && c != 'N');
    
    
    *cont = c;
}

// Game workflow (Main function)
int main()
{
    char cont, // Play again
        board[8][8];   // Representation of the board 
    
    // Move data
    int error,           // if the user entered a invalid value 
        init_line,      // Line origin 
        init_col,       // Column origin 
        fin_lin,        // Line destiny 
        fin_col;        // Column destiny
        
    // Stats 
    int moves = 0,      // Number of moves
        stone,     // Amount of stones eliminated in the move 
        tt_stone;  // Total number of stones eliminated
        
    // Showing the rules
    inf();
    
    do{
        // Initializing the game 
        init_game(board, &moves, &tt_stone);
        do{
            // Printing the board 
            print_board(board);
            
            // Requesting the original position and the destiny (move)
            do{
                req_init_pos(&init_line, &init_col, board);
                
                if(init_line != 0 && init_col != 0){
                    error = req_dest_pos(&fin_lin, &fin_col, &init_line, &init_col, board);
                    
                    
                    // Processing the move 
                    stone = move(init_line, init_col, fin_lin, fin_col, board, error);
                    
                    stats(&moves, stone, &tt_stone, error, fin_lin, fin_col);
                    
                    // Display the information
                    print_mv_stats(init_line, init_col, fin_lin, fin_col, stone, error);  
                    
                }
            }while(error == -1); // repeat the input if the destiny position is invalid    
            
        }while(init_line != 0 && init_col != 0 && fin_lin && fin_col != 0);
        
        // Showing the the final stats
        printstats(&moves, &tt_stone);
        
        play_again(&cont);
    }while(cont == 's' || cont == 'S'); // Condition start a new game
    
    return 0;
}




