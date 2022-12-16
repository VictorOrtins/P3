public class BestScores {
    public final static int MAX_ENTRIES = 5;

    private GameEntry[] scores;

    public BestScores(){
        this.scores = new GameEntry[MAX_ENTRIES];
    }

    public int scoresLength(){

        int scoresLength;
        for (scoresLength = 0; scoresLength < MAX_ENTRIES; scoresLength++){
            if (scores[scoresLength] == null){
                break;
            }
        }
        return scoresLength;
    }

    public boolean removeEntry(int entryNumber){
        if (entryNumber >= MAX_ENTRIES || entryNumber < 0){
            throw new ArrayIndexOutOfBoundsException();
        }

        int scoresLength = scoresLength();

        scores[entryNumber] = null;

        for (int i = entryNumber; i < scoresLength; i++){
            if (i + 1 < MAX_ENTRIES){
                scores[i] = scores[i+1];
            }
        }

        scores[scoresLength() - 1] = null;

        return true;

    }

    public boolean addEntry(GameEntry score){
        boolean ret = false;
        int scoresLength = scoresLength();


        if (scoresLength == 0){
            scores[scoresLength] = score;
            return true;
        }

        for(int i = scoresLength - 1; i >= 0; i--){
            if (score.getScore() > scores[i].getScore()){
                GameEntry temp = scores[i];
                scores[i] = score;
                if (i + 1 < MAX_ENTRIES){
                    scores[i + 1] = temp;
                }
                ret = true;
                
            }
            else if (scoresLength < MAX_ENTRIES){
                scores[i + 1] = score;
                ret = true;
                break;
            }
        }

        return ret;
    }

    public String toString(){
        String ret = "";

        for (int i = 0; i < scoresLength(); i++){
            System.out.format("%s\n", scores[i].toString());
        }

        return ret;
    }


}
