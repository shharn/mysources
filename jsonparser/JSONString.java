/**
 * Created by shharn2 on 2017-01-09.
 */
public class JSONString extends JSONObject{
    private String values;
    JSONString(String value){
        values = value;
    }

    void print(String key){
        System.out.print("Print String - ");
        System.out.print(values);
    }

    JSONObject search(String key){
        return this;
    }
}
