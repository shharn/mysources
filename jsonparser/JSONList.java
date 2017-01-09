import java.util.List;

/**
 * Created by shharn2 on 2017-01-09.
 */
public class JSONList extends JSONObject {
    private List<JSONObject> values;
    void print(){
        System.out.print("Print List - ");
        for(JSONObject member : values)
            System.out.print(member + " ");
    }

    JSONObject search(String key){
        return this;
    }

    List<JSONObject> getList(){
        return this.values;
    }
}
