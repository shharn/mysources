import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * Created by shharn2 on 2017-01-09.
 */
public class JSONObject {
    private LinkedHashMap<String, JSONObject> values;
    JSONObject(){
        values = new LinkedHashMap<String, JSONObject>();
    }

    void print(){
        // print all the child elements
        System.out.print("Print object - ");
        for(Map.Entry<String, JSONObject> entry : values.entrySet()) {
            System.out.print(entry.getKey() + " : ");
            JSONObject value = entry.getValue();
            value.print();
            System.out.println();
        }
    }

    JSONObject search(String key){
        JSONObject obj = values.get(key);
        return obj.search(key);
    }

    LinkedHashMap<String, JSONObject> getContainer(){
        return this.values;
    }
}
