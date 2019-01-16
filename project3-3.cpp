class Student{
public:
    void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
        // Your Code
        int bestVal;
        int a = -10000, b = 10000;
        if(inputColor == Blue) bestVal = -10000;
        else bestVal = 10000;
        x = -1, y = -1;

        int record[5][6], rec[5][6];
        Color C[5][6], c[5][6];
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                record[i][j] = Record[i][j];
                rec[i][j] = Record[i][j];
                C[i][j] = color[i][j];
                c[i][j] = color[i][j];
            }
        }

        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                if((C[i][j] == White || C[i][j] == Blue) && inputColor == Blue){
                    //make the move
                    chain(i, j, Blue, record, C);
                    int moveVal = MiniMax(record, C, 0, Blue, Max, a, b);

                    //undo the move
                    for(int i=0; i<5; i++){
                        for(int j=0; j<6; j++){
                            record[i][j] = rec[i][j];
                            C[i][j] = c[i][j];
                        }
                    }

                    if(moveVal > bestVal){
                        x = i, y = j;
                        bestVal = moveVal;
                    }
                }
                if((C[i][j] == White || C[i][j] == Red) && inputColor == Red){
                    //make the move
                    chain(i, j, Red, record, C);
                    int moveVal = MiniMax(record, C, 0, Red, Max, a, b);

                    //undo the move
                    for(int i=0; i<5; i++){
                        for(int j=0; j<6; j++){
                            record[i][j] = rec[i][j];
                            C[i][j] = c[i][j];
                        }
                    }

                    if(moveVal < bestVal){
                        x = i, y = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

    }
    // Any Code You Want to Add
    bool isMoveLeft(int Record[5][6])
    {
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                if(Record[i][j] == White) return true;
            }
        }
        return false;
    }
    bool isCritical(int x, int y, int Record[5][6])
    {
        if((x == 0 || x == 4) && (y == 0 || y == 5)){
            if(Record[x][y] == 1) return true;
        }else if((x == 0 || x == 4) && (y>0 && y<5)){
            if(Record[x][y] == 2) return true;
        }else if((y == 0 || y == 5) && (x>0 && x<4)){
            if(Record[x][y] == 2) return true;
        }else if((x>0 && x<4) && (y>0 && y<5)){
            if(Record[x][y] == 3) return true;
        }

        return false;
    }
    int evaluate(int Record[5][6], Color color[5][6], int Max[5][6]) // evaluate the score of the board
    {
        int score = 0;

        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                //aviod splitting
                if(color[i][j] == Blue) score += Record[i][j]*3;
                else if(color[i][j] == Red) score -= Record[i][j]*3;
                //if there are adjacent opponents
                if(color[i][j] == Blue){
                    if(i>0 && color[i-1][j] == Red) score -= (5-Max[i][j]);
                    if(i<4 && color[i+1][j] == Red) score -= (5-Max[i][j]);
                    if(j>0 && color[i][j-1] == Red) score -= (5-Max[i][j]);
                    if(j<5 && color[i][j+1] == Red) score -= (5-Max[i][j]);
                }else if(color[i][j] == Red){
                    if(i>0 && color[i-1][j] == Blue) score += (5-Max[i][j]);
                    if(i<4 && color[i+1][j] == Blue) score += (5-Max[i][j]);
                    if(j>0 && color[i][j-1] == Blue) score += (5-Max[i][j]);
                    if(j<5 && color[i][j+1] == Blue) score += (5-Max[i][j]);
                }
                //at corner or on edge without adjacent critical enemies
                if(color[i][j] == Blue){
                    if(i==0 && j==0){
                        if( (color[1][0] == Red && Record[1][0] == 2)
                           || (color[0][1] == Red && Record[0][1] == 2) ) score -= 3;
                        score += 3;
                    }else if(i==0 && j==5){
                        if( (color[1][5] == Red && Record[1][5] == 2)
                           || (color[0][4] == Red && Record[0][4] == 2) ) score -= 3;
                        score += 3;
                    }else if(i==4 && j==5){
                        if( (color[4][4] == Red && Record[4][4] == 2)
                           || (color[3][5] == Red && Record[3][5] == 2) ) score -= 3;
                        score += 3;
                    }else if(i==4 && j==0){
                        if( (color[3][0] == Red && Record[3][0] == 2)
                           || (color[4][1] == Red && Record[4][1] == 2) ) score -= 3;
                        score += 3;
                    }else if(i>0 && i<4 && j==0){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Red)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Red)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Red)) score -= 2;
                        score += 2;
                    }else if(i>0 && i<4 && j==5){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Red)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Red)
                            || (isCritical(i, j-1, Record) && color[i][j-1] == Red)) score -= 2;
                        score += 2;
                    }else if(j>0 && j<5 && i==0){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Red)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Red)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Red)) score -= 2;
                        score += 2;
                    }else if(j>0 && j<5 && i==4){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Red)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Red)
                            || (isCritical(i-1, j, Record) && color[i-1][j] == Red)) score -= 2;
                        score += 2;
                    }
                }else if(color[i][j] == Red){
                    if(i==0 && j==0){
                        if( (color[1][0] == Blue && Record[1][0] == 2)
                           || (color[0][1] == Blue && Record[0][1] == 2) ) score += 3;
                        score -= 3;
                    }else if(i==0 && j==5){
                        if( (color[1][5] == Blue && Record[1][5] == 2)
                           || (color[0][4] == Blue && Record[0][4] == 2) ) score += 3;
                        score -= 3;
                    }else if(i==4 && j==5){
                        if( (color[4][4] == Blue && Record[4][4] == 2)
                           || (color[3][5] == Blue && Record[3][5] == 2) ) score += 3;
                        score -= 3;
                    }else if(i==4 && j==0){
                        if( (color[3][0] == Blue && Record[3][0] == 2)
                           || (color[4][1] == Blue && Record[4][1] == 2) ) score += 3;
                        score -= 3;
                    }else if(i>0 && i<4 && j==0){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Blue)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Blue)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Blue)) score += 2;
                        score -= 2;
                    }else if(i>0 && i<4 && j==5){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Blue)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Blue)
                            || (isCritical(i, j-1, Record) && color[i][j-1] == Blue)) score += 2;
                        score -= 2;
                    }else if(j>0 && j<5 && i==0){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Blue)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Blue)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Blue)) score += 2;
                        score -= 2;
                    }else if(j>0 && j<5 && i==4){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Blue)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Blue)
                            || (isCritical(i-1, j, Record) && color[i-1][j] == Blue)) score += 2;
                        score -= 2;
                    }
                }
                //if critical without adjacent critacal enemies
                if(isCritical(i, j, Record) && color[i][j] == Blue){
                    if(i==0 && j==0){
                        if( (color[1][0] == Red && Record[1][0] == 2)
                           || (color[0][1] == Red && Record[0][1] == 2) ) score -= 2;
                        score += 2;
                    }else if(i==0 && j==5){
                        if( (color[1][5] == Red && Record[1][5] == 2)
                           || (color[0][4] == Red && Record[0][4] == 2) ) score -= 2;
                        score += 2;
                    }else if(i==4 && j==5){
                        if( (color[4][4] == Red && Record[4][4] == 2)
                           || (color[3][5] == Red && Record[3][5] == 2) ) score -= 2;
                        score += 2;
                    }else if(i==4 && j==0){
                        if( (color[3][0] == Red && Record[3][0] == 2)
                           || (color[4][1] == Red && Record[4][1] == 2) ) score -= 2;
                        score += 2;
                    }else if(i>0 && i<4 && j==0){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Red)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Red)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Red)) score -= 2;
                        score += 2;
                    }else if(i>0 && i<4 && j==5){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Red)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Red)
                            || (isCritical(i, j-1, Record) && color[i][j-1] == Red)) score -= 2;
                        score += 2;
                    }else if(j>0 && j<5 && i==0){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Red)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Red)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Red)) score -= 2;
                        score += 2;
                    }else if(j>0 && j<5 && i==4){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Red)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Red)
                            || (isCritical(i-1, j, Record) && color[i-1][j] == Red)) score -= 2;
                        score += 2;
                    }else if(i>0 && i<4 && j>0 && j<5){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Red)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Red)
                            || (isCritical(i-1, j, Record) && color[i-1][j] == Red)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Red)) score -= 2;
                        score += 2;
                    }
                }else if(isCritical(i, j, Record) && color[i][j] == Red){
                    if(i==0 && j==0){
                        if( (color[1][0] == Blue && Record[1][0] == 2)
                           || (color[0][1] == Blue && Record[0][1] == 2) ) score += 2;
                        score -= 2;
                    }else if(i==0 && j==5){
                        if( (color[1][5] == Blue && Record[1][5] == 2)
                           || (color[0][4] == Blue && Record[0][4] == 2) ) score += 2;
                        score -= 2;
                    }else if(i==4 && j==5){
                        if( (color[4][4] == Blue && Record[4][4] == 2)
                           || (color[3][5] == Blue && Record[3][5] == 2) ) score += 2;
                        score -= 2;
                    }else if(i==4 && j==0){
                        if( (color[3][0] == Blue && Record[3][0] == 2)
                           || (color[4][1] == Blue && Record[4][1] == 2) ) score += 2;
                        score -= 2;
                    }else if(i>0 && i<4 && j==0){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Blue)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Blue)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Blue)) score += 2;
                        score -= 2;
                    }else if(i>0 && i<4 && j==5){
                        if((isCritical(i-1, j, Record) && color[i-1][j] == Blue)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Blue)
                            || (isCritical(i, j-1, Record) && color[i][j-1] == Blue)) score += 2;
                        score -= 2;
                    }else if(j>0 && j<5 && i==0){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Blue)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Blue)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Blue)) score += 2;
                        score -= 2;
                    }else if(j>0 && j<5 && i==4){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Blue)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Blue)
                            || (isCritical(i-1, j, Record) && color[i-1][j] == Blue)) score += 2;
                        score -= 2;
                    }else if(i>0 && i<4 && j>0 && j<5){
                        if((isCritical(i, j-1, Record) && color[i][j-1] == Blue)
                            || (isCritical(i, j+1, Record) && color[i][j+1] == Blue)
                            || (isCritical(i-1, j, Record) && color[i-1][j] == Blue)
                            || (isCritical(i+1, j, Record) && color[i+1][j] == Blue)) score += 2;
                        score -= 2;
                    }
                }
                //get the corners
                if(color[i][j] == Blue && ((i==0 && j==0) || (i==0 && j==5) 
                   ||(i==4 && j==0) || (i==4 && j==5))) score += Record[i][j];
                else if(color[i][j] == Red && ((i==0 && j==0) || (i==0 && j==5) 
                   ||(i==4 && j==0) || (i==4 && j==5))) score -= Record[i][j];
            }
        }

        for(int i=0; i<5; i++){
            int cnt = 0;
            for(int j=0; j<6; j++){
                if(isCritical(i, j, Record)){
                    int k;
                    for(k=j; k<6; k++){
                        if(isCritical(i, k, Record)) cnt++;
                        else break;
                    }
                    if(color[i][j] == Blue) score += 3*cnt;
                    else if(color[i][j] == Red) score -= 3*cnt;
                    j = k;
                }
            }
        }
        for(int j=0; j<6; j++){
            int cnt = 0;
            for(int i=0; i<5; i++){
                if(isCritical(i, j, Record)){
                    int k;
                    for(k=i; k<5; k++){
                        if(isCritical(k, j, Record)) cnt++;
                        else break;
                    }
                    if(color[i][j] == Blue) score += 3*cnt;
                    else if(color[i][j] == Red) score -= 3*cnt;
                    i = k;
                }
            }
        }

        return score;
    } // end of evaluation

    //adjustment of board
    void chain(int x, int y, Color c, int Record[][6], Color color[][6])
    {
        if(x<0 || x>4 || y<0 || y>5 || color[x][y] == Black) return;
        Record[x][y] += 1;
        color[x][y] = c;
        if((x==0 && (y==0 || y==5)) || (x==4 && (y==0 || y==5))){
            if(Record[x][y] < 2) return;
            else{
                Record[x][y] = 0, color[x][y] = Black;
                chain(x-1, y, c, Record, color);
                chain(x+1, y, c, Record, color);
                chain(x, y-1, c, Record, color);
                chain(x, y+1, c, Record, color);
            }
        }else if( ((x==0 || x==4) && (y>0 && y<5)) || ((y==0 || y==5) && (x>0 && x<4)) ){
            if(Record[x][y] < 3) return;
            else{
                Record[x][y] = 0, color[x][y] = Black;
                chain(x-1, y, c, Record, color);
                chain(x+1, y, c, Record, color);
                chain(x, y-1, c, Record, color);
                chain(x, y+1, c, Record, color);
            }
        }else{
            if(Record[x][y] < 4) return;
            Record[x][y] = 0, color[x][y] = Black;
            chain(x-1, y, c, Record, color);
            chain(x+1, y, c, Record, color);
            chain(x, y-1, c, Record, color);
            chain(x, y+1, c, Record, color);
        }
    }
    //pick the larger value
    int max(int a, int b)
    {
        return (a>b)?a:b;
    }
    //pick the smaller value
    int min(int a, int b)
    {
        return (a<b)?a:b;
    }

    // return the board value
    int MiniMax(int Record[5][6], Color color[5][6], int depth, Color inputColor, int Max[5][6], int a, int b)
    {
        int score = evaluate(Record, color, Max);

        if(depth == 2) return score;

        if(!isMoveLeft(Record)) return 0;
        //keep the initial board
        int rec[5][6];
        Color c[5][6];
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                rec[i][j] = Record[i][j];
                c[i][j] = color[i][j];
            }
        }

        if(inputColor == Blue){
            int best = -10000;

            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
                    //make the move
                    if(color[i][j] == White || color[i][j] == Blue){
                        chain(i, j, Blue, Record, color);
                    }
                    //choose the maximum value
                    best = max(best, MiniMax(Record, color, depth+1, Red, Max, a, b));
                    a = max(a, best);//
                    if(b <= a) break;//

                    // undo the move
                    for(int k=0; k<5; k++){
                        for(int l=0; l<6; l++){
                            Record[i][j] = rec[i][j];
                            color[i][j] = c[i][j];
                        }
                    }

                }
                if(b <= a) break;//
            }
            return best;
        }
        if(inputColor == Red){
            int best = 10000;

            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
                    //make the move
                    if(color[i][j] == White || color[i][j] == Red){
                        chain(i, j, Red, Record, color);
                    }
                    //choose the maximum value
                    best = min(best, MiniMax(Record, color, depth+1, Blue, Max, a, b));
                    b = min(b, best);
                    if(b <= a) break;

                    // undo the move
                    for(int k=0; k<5; k++){
                        for(int l=0; l<6; l++){
                            Record[i][j] = rec[i][j];
                            color[i][j] = c[i][j];
                        }
                    }

                }
                if(b <= a) break;
            }
            return best;
        }
    }

    int getX(){
        // Your Code
        return x;
    }
    int getY(){
        // Your Code
        return y;
    }
private:
    int x;
    int y;
};