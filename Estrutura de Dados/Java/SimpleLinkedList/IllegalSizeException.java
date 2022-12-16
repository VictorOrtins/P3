package SimpleLinkedList;

public class IllegalSizeException extends Exception{
    protected String message;

    public IllegalSizeException(){
        this.message = null;
    }
    
    public IllegalSizeException(String message){
        setMessage(message);
    }

    public String getMessage(){
        return message;
    }

    public void setMessage(String message){
        this.message = message;
    }
}   
