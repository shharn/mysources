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
        if(values.containsKey(key))
            return values.get(key);
        else {
            for(Map.Entry<String, JSONObject> entry : values.entrySet()) {
                // We need to fix it
                // only traveling into JSONObject object
                JSONObject value = entry.getValue();
                if(value.search(key) != null)
                    return value.search(key);
            }
        }
        return null;
    }

    LinkedHashMap<String, JSONObject> getContainer(){
        return this.values;
    }
}
