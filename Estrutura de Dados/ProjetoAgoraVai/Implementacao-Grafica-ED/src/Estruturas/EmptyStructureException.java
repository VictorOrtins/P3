package Estruturas;

public class EmptyStructureException extends Exception{
    protected String message;

    public EmptyStructureException(){
        this.message = null;
    }
    
    public EmptyStructureException(String message){
        setMessage(message);
    }

    public String getMessage(){
        return message;
    }

    public void setMessage(String message){
        this.message = message;
    }
}
