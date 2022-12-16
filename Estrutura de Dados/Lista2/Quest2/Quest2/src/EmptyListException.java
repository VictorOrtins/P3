public class EmptyListException extends Exception{
    protected String message;

    public EmptyListException(){
        this.message = null;
    }
    
    public EmptyListException(String message){
        setMessage(message);
    }

    public String getMessage(){
        return message;
    }

    public void setMessage(String message){
        this.message = message;
    }
}
