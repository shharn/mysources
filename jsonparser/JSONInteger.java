/**
 * Created by shharn2 on 2017-01-09.
 */
public class JSONInteger extends JSONObject {
    private int values;

    JSONInteger(int n){
        this.values = n;
    }

    void print(){
        System.out.print("Print JSONInteger - ");
        System.out.print(values);
    }

    JSONObject search(String key){
        return this;
    }
}
