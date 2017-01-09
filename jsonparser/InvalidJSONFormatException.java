/**
 * Created by shharn2 on 2017-01-09.
 */
public class InvalidJSONFormatException extends Exception{
    String message;
    InvalidJSONFormatException(String msg){
        message = msg;
    }

    void print(){
        System.out.println(message);
    }
}
