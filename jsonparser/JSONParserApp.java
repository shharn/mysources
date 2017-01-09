/**
 * Created by shharn2 on 2017-01-09.
 */
public class JSONParserApp {
    public static void main(String... args){
        JSONParserApp app = new JSONParserApp();
        JSONParser parser = new JSONParser("sample_json.json");
        JSONObject obj = app.run(parser);
    }

    public static JSONObject run(JSONParser parser){
        return parser.parse();
    }
}
