import java.util.ArrayList;
import java.util.List;

/**
 * Created by shharn2 on 2017-01-09.
 */
public class JSONList extends JSONObject {
    private List<JSONObject> values;

    JSONList(){
        values = new ArrayList<JSONObject>();
    }

    void print(){
        System.out.print("Print List - ");
        for(JSONObject member : values)
            member.print();
    }

    JSONObject search(String key){
        return this;
    }

    List<JSONObject> getList(){
        return this.values;
    }
}
