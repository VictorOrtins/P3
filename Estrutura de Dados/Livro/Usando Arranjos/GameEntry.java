import java.util.Objects;

public class GameEntry{
    private String name;
    private int score;

    public GameEntry(){
        this.name = null;
        this.score = 0;
    }

    public GameEntry(String name, int score){
        this.name = name;
        this.score = score;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getScore() {
        return this.score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    @Override
    public String toString(){
        return String.format("Name: %s\nScore: %d\n", this.getName(), this.getScore());
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof GameEntry)) {
            return false;
        }
        GameEntry gameEntry = (GameEntry) o;
        return Objects.equals(name, gameEntry.name) && score == gameEntry.score;
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, score);
    }


}