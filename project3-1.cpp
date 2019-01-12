class Student{
    public:
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            // Your Code
            
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
        int evaluate(int Record[5][6], Color color[5][6]) // evaluate the score of the board
        {
            int score = 0;

            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
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
                }
            }

            return score;
        }
        int MinMax(int Record[5][6], int depth, Color color)
        {
            int score = evaluate(Record);

            if(depth == 4) return score;
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
